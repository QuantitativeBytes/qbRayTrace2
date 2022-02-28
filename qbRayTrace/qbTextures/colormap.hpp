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
	
***********************************************************/

#ifndef COLORMAP_H
#define COLORMAP_H

#include "../qbLinAlg/qbVector.h"

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
				void SetStop(double position, const qbVector<double> &value);
				
				// Function to get the color at a particular position.
				qbVector<double> GetColor(double position);
				
			private:
				std::vector<double> m_stopPositions;
				std::vector<qbVector<double>> m_stopValues;
		};
	}
}

#endif
