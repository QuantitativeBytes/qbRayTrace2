/* ***********************************************************
	qbutils.hpp
	
	A collection of useful functions and definitions for qbRAY.
	
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

#ifndef QBRT_UTILS_H
#define QBRT_UTILS_H

#include <memory>
#include <SDL2/SDL.h>
#include "./qbLinAlg/qbVector.h"
#include "./qbLinAlg/qbVector2.hpp"
#include "./qbLinAlg/qbVector3.hpp"
#include "./qbLinAlg/qbVector4.hpp"
#include "./qbLinAlg/qbMatrix33.hpp"
#include "./qbLinAlg/qbMatrix44.hpp"

namespace qbRT
{
	// Forward-declare the object base class.
	class ObjectBase;

	namespace DATA
	{
		struct hitData
		{
			qbVector3<double> poi;
			qbVector3<double> normal;
			qbVector3<double> color;
			qbVector3<double> localPOI;
			qbVector2<double> uvCoords;
			std::shared_ptr<qbRT::ObjectBase> hitObject;
		};
		
		// Structure for handling rendering tiles.
		struct tile
		{
			int x;
			int y;
			int xSize;
			int ySize;
			int renderComplete = 0;
			bool textureComplete = false;
			SDL_Texture *pTexture;
			std::vector<qbVector3<double>> rgbData;
		};			
	}

	namespace UTILS
	{
		void PrintVector(const qbVector3<double> &inputVector);
		void PrintMatrix(const qbMatrix33<double> &inputMatrix);
		void PrintMatrix(const qbMatrix44<double> &inputMatrix);
	}
}

#endif
