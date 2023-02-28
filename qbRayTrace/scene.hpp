/* ***********************************************************
	scene.hpp
	
	The scene class definition - A class to handle information
	about the scene and rendering to an image.
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
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
	
***********************************************************/

// scene.hpp

#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "qbutils.hpp"
#include "qbImage.hpp"
#include "camera.hpp"
#include "./qbPrimatives/objsphere.hpp"
#include "./qbPrimatives/objplane.hpp"
#include "./qbPrimatives/cylinder.hpp"
#include "./qbPrimatives/cone.hpp"
#include "./qbPrimatives/box.hpp"
#include "./qbLights/pointlight.hpp"
#include "./qbRayMarch/sphere.hpp"
#include "./qbRayMarch/torus.hpp"
#include "./qbRayMarch/cube.hpp"
#include "./qbNormals/simplerough.hpp"
#include "./qbNormals/texturenormal.hpp"
#include "./qbNormals/image.hpp"

namespace qbRT
{
	class Scene
	{
		public:
			// The default constructor.
			Scene();
			
			// ***
			// Destructor.
			virtual ~Scene();
			
			// Function to perform the rendering.
			bool Render(qbImage &outputImage);
			
			/*
				New function to handle rendering a specified tile.
			*/
			// Function to handle rendering a tile.
			void RenderTile(qbRT::DATA::tile *tile);
			
			// Function to cast a ray into the scene.
			bool CastRay(	qbRT::Ray &castRay, std::shared_ptr<qbRT::ObjectBase> &closestObject,
										qbRT::DATA::hitData &closestHitData);
										
			// Function to handle setting up the scene (to be overriden).
			virtual void SetupSceneObjects();
			
		// Private functions.
		private:
			// Function to handle rendering a pixel.
			qbVector3<double> RenderPixel(int x, int y, int xSize, int ySize);
			
			// Function to convert coordinates to a linear index.
			int Sub2Ind(int x, int y, int xSize, int ySize);
		
		
		public:
			// The camera that we will use.
			qbRT::Camera m_camera;
			
			// The list of objects in the scene.
			std::vector<std::shared_ptr<qbRT::ObjectBase>> m_objectList;
	
			// The list of lights in the scene.
			std::vector<std::shared_ptr<qbRT::LightBase>> m_lightList;
			
			// Scene parameters.
			int m_xSize, m_ySize;
	};
}

#endif
