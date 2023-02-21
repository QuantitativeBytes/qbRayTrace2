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
	Copyright (c) 2021 Michael Bennett
	
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
		
		// Intialize the qbImage instance.
		m_image.Initialize(m_xSize, m_ySize, pRenderer);
		
		// Initialize the tile grid.
		if (!GenerateTileGrid(128, 128))
		{
			std::cout << "Failed to generate tile grid." << std::endl;
			return false;
		}
		
		// Set the background color to white.
		SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
		SDL_RenderClear(pRenderer);
		
		// Render the scene.
		m_scene.Render(m_image);
		
		// Display the image.
		m_image.Display();
		
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
	// Loop through all tiles and find the first one that hasn't been rendered yet.
	for (int i=0; i<m_tiles.size(); ++i)
	{
		if (m_tileFlags.at(i) == 0)
		{
			// This tile has not been rendered, so render it now.
			// m_scene.RenderTile(tile);
			
			// Set the tile flag to indicate that this tile has been rendered.
			m_tileFlags.at(i) == 2;
			
			// Once complete, break out of the loop.
			// This is tempory and will be removed once we implement multi-threading.
			break;
		}
	}
}

void CApp::OnRender()
{
	// Converstion factors from screen width/height to window width/height.
	// For future versions.
	double widthFactor = 1.0;
	double heightFactor = 1.0;
	
	// Render the tiles.
	for (int i=0; i<m_tiles.size(); ++i)
	{
		// Only render the tile if it is complete.
		if (m_tileFlags.at(i) == 2)
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
			/*
			if (!m_tiles.at(i).textureComplete)
			{
				ConvertImageToTexture(m_tiles.at(i));
				m_tiles.at(i).textureComplete = true;
				SDL_RenderCopy(pRenderer, m_tiles.at(i).pTexture, &srcRect, &dstRect);			
			}	
			*/				
		}
	}
	
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
	
	// Add end-of-row and end-of-column tiles that might be smaller.
	// First end-of-column.
	if ((numTilesY * tileSizeY) < m_ySize)
	{
		int newTileSizeY = m_ySize - (numTilesY * tileSizeY);
		SDL_Surface *eocY = SDL_CreateRGBSurface(0, tileSizeX, newTileSizeY, 32, rmask, gmask, bmask, amask);
		for (int x=0; x<numTilesX; ++x)
		{
			qbRT::DATA::tile tempTile;
			tempTile.x = x*tileSizeX;
			tempTile.y = numTilesY * tileSizeY;
			tempTile.xSize = tileSizeX;
			tempTile.ySize = newTileSizeY;
			tempTile.renderComplete = 0;
			tempTile.pTexture = SDL_CreateTextureFromSurface(pRenderer, eocY);
			tempTile.rgbData.resize(tempTile.xSize * tempTile.ySize);			
			m_tiles.push_back(tempTile);				
		}
		SDL_FreeSurface(eocY);
	}
	
	// And then end-of-row.
	if ((numTilesX * tileSizeX) < m_xSize)
	{
		int newTileSizeX = m_xSize - (numTilesX * tileSizeX);
		SDL_Surface *eocX = SDL_CreateRGBSurface(0, newTileSizeX, tileSizeY, 32, rmask, gmask, bmask, amask);
		for (int y=0; y<numTilesY; ++y)
		{
			qbRT::DATA::tile tempTile;
			tempTile.x = numTilesX * tileSizeX;
			tempTile.y = y*tileSizeY;
			tempTile.xSize = newTileSizeX;
			tempTile.ySize = tileSizeY;
			tempTile.renderComplete = 0;
			tempTile.pTexture = SDL_CreateTextureFromSurface(pRenderer, eocX);
			tempTile.rgbData.resize(tempTile.xSize * tempTile.ySize);			
			m_tiles.push_back(tempTile);				
		}
		SDL_FreeSurface(eocX);
	}	
				
	// Set all the tile flags to zero.
	for (int i=0; i<m_tiles.size(); ++i)
	{
		m_tileFlags.push_back(0);
	}
				
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


























