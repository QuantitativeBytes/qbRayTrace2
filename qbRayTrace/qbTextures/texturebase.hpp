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
	
***********************************************************/
#ifndef TEXTUREBASE_H
#define TEXTUREBASE_H

#include <memory>
#include "../qbLinAlg/qbMatrix.h"
#include "../qbLinAlg/qbVector.h"
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
				virtual qbVector<double> GetColor(const qbVector<double> &uvCoords);
				
				// *** Function to return the actual texture value at a given point in the (u,v) coordinate system.
				virtual double GetValue(const qbVector<double> &uvCoords);				
				
				// Function to set transform.
				void SetTransform(const qbVector<double> &translation, const double &rotation, const qbVector<double> &scale);
				
				// Function to blend RGBA colors, returning a 3-dimensional (RGB) result.
				static qbVector<double> BlendColors(const std::vector<qbVector<double>> &inputColorList);
				
				// Function to apply the local transform to the given input vector.
				qbVector<double> ApplyTransform(const qbVector<double> &inputVector);
				
			private:
			
			private:
				// Initialise the transform matrix to the identity matrix.
				qbMatrix2<double> m_transformMatrix {3, 3, std::vector<double>{1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0}};
				
		};
	}
}

#endif
