/* ***********************************************************
	texturebase.hpp
	
	The texturebase class definition - a simple base class for
	handling textures.
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
	This code corresponds specifically to Episode 9 of the series,
	which may be found here:
	https://youtu.be/d35gDi98gEY
	
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
#ifndef TEXTUREBASE_H
#define TEXTUREBASE_H

#include <memory>
#include "../qbLinAlg/qbMatrix.h"
#include "../qbLinAlg/qbMatrix33.hpp"
#include "../qbLinAlg/qbVector.h"
#include "../qbLinAlg/qbVector2.hpp"
#include "../qbLinAlg/qbVector3.hpp"
#include "../qbLinAlg/qbVector4.hpp"
#include "../ray.hpp"

namespace qbRT
{
	namespace Texture
	{
		class TextureBase
		{
			public:
				// Constructor / destructor.
				TextureBase();
				virtual ~TextureBase();
				
				// Function to retrun the color at a given point in the (u,v) coordinate system.
				// Note that the color is returned as a 4-dimensional vector (RGBA).
				virtual qbVector4<double> GetColor(const qbVector2<double> &uvCoords);
				
				// *** Function to return the actual texture value at a given point in the (u,v) coordinate system.
				virtual double GetValue(const qbVector2<double> &uvCoords);				
				
				// Function to set transform.
				void SetTransform(const qbVector2<double> &translation, const double &rotation, const qbVector2<double> &scale);
				
				// Function to blend RGBA colors, returning a 3-dimensional (RGB) result.
				static qbVector3<double> BlendColors(const std::vector<qbVector3<double>> &inputColorList);
				
				// Function to apply the local transform to the given input vector.
				qbVector2<double> ApplyTransform(const qbVector2<double> &inputVector);
				
			private:
			
			private:
				// Initialise the transform matrix to the identity matrix.
				qbMatrix33<double> m_transformMatrix {std::vector<double>{1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0}};
				
		};
	}
}

#endif
