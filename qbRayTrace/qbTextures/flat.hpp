/* ***********************************************************
	flat.hpp
	
	The flat class definition - The simplest possible texture
	definition consisting of just a single color.
	
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

#ifndef FLAT_H
#define FLAT_H

#include "texturebase.hpp"

namespace qbRT
{
	namespace Texture
	{
		class Flat : public TextureBase
		{
			public:
				// Constructor / destructor.
				Flat();
				virtual ~Flat() override;
				
				// Function to return the color.
				virtual qbVector4<double> GetColor(const qbVector2<double> &uvCoords) override;
				
				// Function to set the color.
				void SetColor(const qbVector4<double> &inputColor);
				
			private:
				qbVector4<double> m_color;
				
		};
	}
}

#endif
