/* ***********************************************************
	Scene_E21.hpp
	
	The Scene_E21 class definition - A class to handle information
	about the Scene_E21 and rendering to an image.
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
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

// Scene_E21.hpp

#ifndef Scene_E21_H
#define Scene_E21_H

#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "qbImage.hpp"
#include "camera.hpp"
#include "./qbPrimatives/objsphere.hpp"
#include "./qbPrimatives/objplane.hpp"
#include "./qbPrimatives/cylinder.hpp"
#include "./qbPrimatives/cone.hpp"
#include "./qbPrimatives/box.hpp"
#include "./qbPrimatives/compositebase.hpp"
#include "./qbLights/pointlight.hpp"
#include "./qbRayMarch/sphere.hpp"
#include "./qbRayMarch/torus.hpp"
#include "./qbRayMarch/cube.hpp"
#include "./qbNormals/simplerough.hpp"
#include "./qbNormals/texturenormal.hpp"
#include "./qbNormals/image.hpp"

namespace qbRT
{
	class Scene_E21
	{
		public:
			// The default constructor.
			Scene_E21();
			
			// Function to perform the rendering.
			bool Render(qbImage &outputImage);
			
			// Function to cast a ray into the Scene_E21.
			bool CastRay(	qbRT::Ray &castRay, std::shared_ptr<qbRT::ObjectBase> &closestObject,
										qbRT::DATA::hitData &closestHitData);
			
		// Private functions.
		private:
		
		// Private members.
		private:
			// The camera that we will use.
			qbRT::Camera m_camera;
			
			// The list of objects in the Scene_E21.
			std::vector<std::shared_ptr<qbRT::ObjectBase>> m_objectList;
	
			// The list of lights in the Scene_E21.
			std::vector<std::shared_ptr<qbRT::LightBase>> m_lightList;
	};
}

#endif
