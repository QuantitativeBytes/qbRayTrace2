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

}

void CApp::OnRender()
{
	// Set the background color to white.
	//SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
	//SDL_RenderClear(pRenderer);
	
	// Render the scene.
	//m_scene.Render(m_image);
	
	// Display the image.
	//m_image.Display();
	
	// Show the result.
	//SDL_RenderPresent(pRenderer);
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


























