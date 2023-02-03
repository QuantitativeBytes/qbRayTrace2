/* ***********************************************************
	colormap.hpp
	
	The colormap class definition. A class to handle color
	maps with any number of stops.
	
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

#ifndef COLORMAP_H
#define COLORMAP_H

#include "../qbLinAlg/qbVector.h"
#include "../qbLinAlg/qbVector2.hpp"
#include "../qbLinAlg/qbVector3.hpp"
#include "../qbLinAlg/qbVector4.hpp"

namespace qbRT
{
	namespace Texture
	{
		class ColorMap
		{
			public:
				// Constructor / destructor.
				ColorMap();
				~ColorMap();
				
				// Function to set a stop as a color.
				void SetStop(double position, const qbVector4<double> &value);
				
				// Function to get the color at a particular position.
				qbVector4<double> GetColor(double position);
				
			private:
				std::vector<double> m_stopPositions;
				std::vector<qbVector4<double>> m_stopValues;
		};
	}
}

#endif
