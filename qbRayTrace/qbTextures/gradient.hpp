/* ***********************************************************
	gradient.hpp
	
	The gradient class definition. An implementation of a simple
	gradient texture.
	
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

#ifndef GRADIENT_H
#define GRADIENT_H

#include "texturebase.hpp"
#include "colormap.hpp"

namespace qbRT
{
	namespace Texture
	{
		class Gradient : public TextureBase
		{
			public:
				// Constructor / destructor.
				Gradient();
				virtual ~Gradient() override;
				
				// Function to return the color.
				virtual qbVector4<double> GetColor(const qbVector2<double> &uvCoords) override;
				
				// *** Function to return the value.
				virtual double GetValue(const qbVector2<double> &uvCoords) override;				
				
				// Function to set stops for the color map.
				void SetStop(double position, const qbVector4<double> &value);
				
			private:
				qbRT::Texture::ColorMap m_colorMap;
		};		
	}
}

#endif
