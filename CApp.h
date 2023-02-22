
/* ***********************************************************
	CApp.h
	
	The application class definition.
	
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
	Copyright (c) 2022 Michael Bennett
	
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
	
***********************************************************/

#ifndef CAPP_H
#define CAPP_H

#include <SDL2/SDL.h>
#include "./qbRayTrace/qbImage.hpp"
#include "./qbRayTrace/scene.hpp"
#include "./qbRayTrace/scene_E21.hpp"
#include "./qbRayTrace/camera.hpp"
#include "./qbRayTrace/qbTextures/flat.hpp"
#include "./qbRayTrace/qbTextures/checker.hpp"
#include "./qbRayTrace/qbTextures/image.hpp"
#include "./qbRayTrace/qbLinAlg/qbVector2.hpp"
#include "./qbRayTrace/qbLinAlg/qbVector3.hpp"
#include "./qbRayTrace/qbLinAlg/qbVector4.hpp"

class CApp
{
	public:
		CApp();
		
		int OnExecute();
		bool OnInit();
		void OnEvent(SDL_Event *event);
		void OnLoop();
		void OnRender();
		void OnExit();
		
	private:
		void PrintVector(const qbVector3<double> &inputVector);
		
		/*
			New functions here to handle tile based rendering. This isn't much use
			right now, but forms the basis for the multi-threading implementation
			that we will look at later.
			22/02/23
		*/
		// Function to generate the tile grid.
		bool GenerateTileGrid(int tileSizeX, int tileSizeY);
		
		// Function to handle destroying the tile grid.
		bool DestroyTileGrid();
		
	private:
		// An instance of the qbImage class to store the image.
		qbImage m_image;
		
		/*
			New code here to support tiles.
			22/02/23
		*/
		// Array to store tiles.
		std::vector<qbRT::DATA::tile> m_tiles;
		std::vector<int> m_tileFlags;
		int m_numTilesX, m_numTilesY;
		
		// An instance of the scene class.
		qbRT::Scene_E21 m_scene;
		
		// SDL2 stuff.
		bool isRunning;
		SDL_Window *pWindow;
		SDL_Renderer *pRenderer;
		
		/*
			New functions here to handle tile based rendering. This isn't much use
			right now, but forms the basis for the multi-threading implementation
			that we will look at later.
			22/02/23
		*/		
		// Display configuration.
		int m_xSize, m_ySize;
		
		// Function to convert tile image to texture.
		void ConvertImageToTexture(qbRT::DATA::tile &tile);
		
		// Function to handle converting colors from RGB to UINT32.
		Uint32 ConvertColor(const double red, const double green, const double blue);
		
		// The value to be used for gamma-correction.
		double m_maxLevel = 0.8;
		
};

#endif
