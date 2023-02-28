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

// Scene_E21.hpp

#ifndef Scene_E21_H
#define Scene_E21_H

#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "scene.hpp"
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
	class Scene_E21 : public Scene
	{
		public:
			// The default constructor.
			Scene_E21();
			
			// Destructor.
			virtual ~Scene_E21() override;
			
			// Function to setup the scene.
			virtual void SetupSceneObjects() override;
	};
}

#endif
