/* ***********************************************************
	CApp.cpp
	
	The application class implementation.
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
	This code corresponds specifically to Episode 2 of the series,
	which may be found here:
	https://youtu.be/KBK6g6RFgdA
	
	The whole series may be found on the QuantitativeBytes 
	YouTube channel at:
	www.youtube.com/c/QuantitativeBytes
	
	GPLv3 LICENSE
	Copyright (c) 2023 Michael Bennett
	
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.	
	
**********************************************************/

// CApp.cpp
#include "CApp.h"
#include "./qbRayTrace/qbLinAlg/qbVector.h"
#include "./qbRayTrace/qbLinAlg/qbVector2.hpp"
#include "./qbRayTrace/qbLinAlg/qbVector3.hpp"
#include "./qbRayTrace/qbLinAlg/qbVector4.hpp"

// The constructor (default)
CApp::CApp()
{
	isRunning = true;
	pWindow = NULL;
	pRenderer = NULL;
	
	// ***********
	// We have to initialize the thread counter here in the class constructor.
	m_threadCounter = new std::atomic<int> (0);
}

bool CApp::OnInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}
	
	m_xSize = 1280;
	m_ySize = 720;	
	
	pWindow = SDL_CreateWindow("qbRayTracer - Don't forget to subscribe!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_xSize, m_ySize, SDL_WINDOW_SHOWN);
	
	if (pWindow != NULL)
	{
		pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
		
		// Initialize the qbImage instance.
		//m_image.Initialize(m_xSize, m_ySize, pRenderer);
		
		/*
			We now initialize the scene with the window dimensions and
			then generate a tile grid with tiles of the specified size.
		*/
		// Initialize the scene.
		m_scene.m_xSize = m_xSize;
		m_scene.m_ySize = m_ySize;
		
		// Initialize the tile grid.
		if (!GenerateTileGrid(128, 90))
		{
			std::cout << "Failed to generate tile grid." << std::endl;
			return false;
		}
		
		// ****
		// Initialize the thread counter.
		m_maxThreads = 12;
		m_threadCounter -> store(0, std::memory_order_release);		
		
		/*
			Following the introduction of tile-based rendering, the code
			to actual render the image has moved from here. In 
			general it doesn't make sense to have the code in the
			OnInit() function in any case.
			22/02/23
		*/
		
		// Set the background color to white.
		SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
		SDL_RenderClear(pRenderer);
		
		// Show the result.
		SDL_RenderPresent(pRenderer);
		
	}
	else
	{
		return false;
	}
	
	return true;
}

int CApp::OnExecute()
{
	SDL_Event event;
	
	if (OnInit() == false)
	{
		return -1;
	}
	
	while (isRunning)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			OnEvent(&event);
		}
		
		OnLoop();
		OnRender();
		
		/*
			The delay here seems counterintuitive, but it actually makes the
			rendering faster (with multi-threading). The reason for this, 
			I think, is that it reduces the load imposed by looping through 
			this code allowing more of the CPU time to be used for actual 
			rendering. I have tried different values, reducing it below 1 
			seems to slow things down and increasing it above 4 also slows 
			things down. It would seem that somewhere between 1 and 4 is the
			'sweet spot', so I have left it at 1.
		*/
		SDL_Delay(1);		
	}
	
	OnExit();
	return 0;
}

void CApp::OnEvent(SDL_Event *event)
{
	if (event->type == SDL_QUIT)
	{
		isRunning = false;
	}
}

void CApp::OnLoop()
{
	/*
		The actual rendering is now handled here, each time we come through
		this loop. At the moment, before implementing multi-threading, we
		proceed by looping through all of the tiles and finding the first
		one that has not been rendered yet (as indicated by m_tileFlags).
		We then call the RenderTile function from the scene base class and
		pass a reference to the relevent tile as the only parameter. Finally,
		we update m_tileFlags for this tile to indicate that it has now been
		rendered and then break out of the loop. We don't want to end up
		rendering every tile all at once, we want to one tile each time
		we come through the OnLoop() function.
	*/
	// Loop through all tiles and find the first one that hasn't been rendered yet.
	/*for (int i=0; i<m_tiles.size(); ++i)
	{
		if (m_tileFlags.at(i) == 0)
		{
			// This tile has not been rendered, so render it now.
			m_scene.RenderTile(&m_tiles.at(i));
			
			// Set the tile flag to indicate that this tile has been rendered.
			m_tileFlags.at(i) = 2;
			
			// Once complete, break out of the loop.
			// This is tempory and will be removed once we implement multi-threading.
			break;
		}
	}*/
	for (int i=0; i<m_tiles.size(); ++i)
	{
			if (m_tileFlags.at(i) -> load(std::memory_order_acquire) == 0)
			{
				// This tile is waiting to be rendered.
				// Check if any threads are available.
				if (m_threadCounter -> load(std::memory_order_acquire) < m_maxThreads)
				{
					// We have a thread available, so launch it to render this tile.
					int numActiveThreads = m_threadCounter -> load(std::memory_order_acquire);					
					m_threadCounter -> store(numActiveThreads+1, std::memory_order_release);
					std::thread renderThread (&CApp::RenderTile, this, &m_tiles.at(i), m_threadCounter, m_tileFlags.at(i));
					renderThread.detach();
				}
			}	
	}
}

void CApp::OnRender()
{
	// Converstion factors from screen width/height to window width/height.
	// For future versions.
	double widthFactor = 1.0;
	double heightFactor = 1.0;
	
	/*
		The actual display is now generated here. We loop over all of the tiles
		and wherever we find one that has been rendered (tileFlags == 2), then
		we check if we have already display this tile (textureComplete) and if
		not we convert the image data to an SDL texture and then use SDL_RenderCopy
		to copy that texture to the right place in the window.
		
		In a single-thread implementation, this approach doesn't necessarily make
		much sense, but it forms the foundation on which we can build our multi-threaded
		version.
	*/
	
	// Render the tiles.
	for (int i=0; i<m_tiles.size(); ++i)
	{
		// Only render the tile if it is complete.
		//if (m_tileFlags.at(i) == 2)
		if (m_tileFlags.at(i) -> load(std::memory_order_acquire) == 2)
		{
			SDL_Rect srcRect, dstRect;
			srcRect.x = 0;
			srcRect.y = 0;
			srcRect.w = m_tiles.at(i).xSize;
			srcRect.h = m_tiles.at(i).ySize;
			dstRect.x = static_cast<int>(std::round(static_cast<double>(m_tiles.at(i).x) * widthFactor));
			dstRect.y = static_cast<int>(std::round(static_cast<double>(m_tiles.at(i).y) * heightFactor));
			dstRect.w = static_cast<int>(std::round(static_cast<double>(m_tiles.at(i).xSize) * widthFactor));
			dstRect.h = static_cast<int>(std::round(static_cast<double>(m_tiles.at(i).ySize) * heightFactor));
			
			/*
				If the textureComplete flag for this tile is not set, then it means that the tile
				has been rendered, but not yet converted to a texture. So we do that here and
				then set the textureComplete flag and blit the texture into the renderer.
				Note that once this is done, we don't do this again for this tile meaning
				that we don't keep updating each tile every time we go through this loop.
				This helps to keep things as efficient as possible.
			*/
			if (!m_tiles.at(i).textureComplete)
			{
				ConvertImageToTexture(m_tiles.at(i));
				m_tiles.at(i).textureComplete = true;
				SDL_RenderCopy(pRenderer, m_tiles.at(i).pTexture, &srcRect, &dstRect);			
			}					
		}
	}
	
	// Show the result.
	SDL_RenderPresent(pRenderer);		
	
}

void CApp::OnExit()
{
	// Tidy up the tile grid.
	bool result = DestroyTileGrid();

	// Tidy up SDL2 stuff.
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	pWindow = NULL;
	SDL_Quit();
}

// PRIVATE FUNCTIONS.
void CApp::PrintVector(const qbVector3<double> &inputVector)
{
	int nRows = inputVector.GetNumDims();
	for (int row=0; row<nRows; ++row)
	{
		std::cout << std::fixed << std::setprecision(3) << inputVector.GetElement(row) << std::endl;
	}
}

// Function to generate the tile grid.
bool CApp::GenerateTileGrid(int tileSizeX, int tileSizeY)
{
	// How many tiles will fit horizontally?
	int numTilesX = std::floor(m_xSize / tileSizeX);
	m_numTilesX = numTilesX;
	
	// How many tiles will fit vertically?
	int numTilesY = std::floor(m_ySize / tileSizeY);
	m_numTilesY = numTilesY;
	
	// Setup an SDL surface from which we can generate the textures for each tile.
	Uint32 rmask, gmask, bmask, amask;
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
	#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
	#endif	
	SDL_Surface *tempSurface = SDL_CreateRGBSurface(0, tileSizeX, tileSizeY, 32, rmask, gmask, bmask, amask);
	
	// Generate the actual tiles.
	for (int y=0; y<numTilesY; ++y)
	{
		for (int x=0; x<numTilesX; ++x)
		{
			qbRT::DATA::tile tempTile;
			tempTile.x = x * tileSizeX;
			tempTile.y = y * tileSizeY;
			tempTile.xSize = tileSizeX;
			tempTile.ySize = tileSizeY;
			tempTile.renderComplete = 0;
			tempTile.pTexture = SDL_CreateTextureFromSurface(pRenderer, tempSurface);
			tempTile.rgbData.resize(tempTile.xSize * tempTile.ySize);
			m_tiles.push_back(tempTile);		
		}
	}
				
	// Set all the tile flags to zero.
	for (int i=0; i<m_tiles.size(); ++i)
	{
		m_tileFlags.push_back(new std::atomic<int> (0));
	}	
	/*
	for (int i=0; i<m_tiles.size(); ++i)
	{
		m_tileFlags.push_back(0);
	}*/
				
	// Tidy up before returning.
	SDL_FreeSurface(tempSurface);	
	return true;				
}

// Function to destroy the tile grid.
bool CApp::DestroyTileGrid()
{
	for (int i=0; i<m_tiles.size(); ++i)
	{
		if (m_tiles.at(i).pTexture != NULL)
			SDL_DestroyTexture(m_tiles.at(i).pTexture);
	
	}
	return true;
}

// Function to convert an RGB image to a texture.
void CApp::ConvertImageToTexture(qbRT::DATA::tile &tile)
{
	// Allocate memory for a pixel buffer.
	Uint32 *tempPixels = new Uint32[tile.xSize * tile.ySize];
	
	// Clear the pixel buffer.
	memset(tempPixels, 0, tile.xSize * tile.ySize * sizeof(Uint32));
	
	// Copy the image into tempPixels.
	for (int i=0; i<tile.xSize * tile.ySize; ++i)
	{
		tempPixels[i] = ConvertColor(tile.rgbData.at(i).m_x, tile.rgbData.at(i).m_y, tile.rgbData.at(i).m_z);
	}
	
	// Update the texture with the pixel buffer.
	SDL_UpdateTexture(tile.pTexture, NULL, tempPixels, tile.xSize * sizeof(Uint32));	
	
	// Delete the pixel buffer.
	delete[] tempPixels;
}

// Function to convert colours to Uint32
Uint32 CApp::ConvertColor(const double red, const double green, const double blue)
{
	// Convert the colours to unsigned integers.
	double newRed = std::max(std::min(std::pow(red, m_maxLevel), 1.0), 0.0);
	double newGreen = std::max(std::min(std::pow(green, m_maxLevel), 1.0), 0.0);
	double newBlue = std::max(std::min(std::pow(blue, m_maxLevel), 1.0), 0.0);
	
	unsigned char r = static_cast<unsigned char>(newRed * 255.0);
	unsigned char g = static_cast<unsigned char>(newGreen * 255.0);
	unsigned char b = static_cast<unsigned char>(newBlue * 255.0);
	
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		Uint32 pixelColor = (r << 24) + (g << 16) + (b << 8) + 255;
	#else
		Uint32 pixelColor = (255 << 24) + (b << 16) + (g << 8) + r;
	#endif
	
	return pixelColor;
}


// *******************
// Function to handle rendering a tile.
void CApp::RenderTile(qbRT::DATA::tile *tile, std::atomic<int> *threadCounter, std::atomic<int> *tileFlag)
{
	tileFlag -> store(1, std::memory_order_release);
	m_scene.RenderTile(tile);
	int numActiveThreads = threadCounter -> load(std::memory_order_acquire);
	threadCounter -> store(numActiveThreads-1, std::memory_order_release);
	tileFlag -> store(2, std::memory_order_release);
}

// Function to reset the tile flags.
void CApp::ResetTileFlags()
{
	for (int i=0; i<m_tiles.size(); ++i)
	{
		m_tileFlags.at(i) -> store(0, std::memory_order_release);
		m_tiles.at(i).textureComplete = false;
	}
}



















