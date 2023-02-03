/* ***********************************************************
	marble.hpp
	
	A class to implement a simple marble texture.
	
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


#ifndef MARBLE_H
#define MARBLE_H

#include "../qbNoise/grdnoisegenerator.hpp"
#include "texturebase.hpp"
#include "colormap.hpp"

namespace qbRT
{
	namespace Texture
	{
		class Marble : public TextureBase
		{
			public:
				// Constructor / destructor.
				Marble();
				virtual ~Marble() override;
				
				// Function to return the color.
				virtual qbVector4<double> GetColor(const qbVector2<double> &uvCoords) override;
				
				// Function to set the color map.
				void SetColorMap(const std::shared_ptr<qbRT::Texture::ColorMap> &colorMap);
				
				// Function to set the amplitude.
				void SetAmplitude(double amplitude1, double amplitude2);
				
				// Function to set the scale.
				void SetScale(int scale1, int scale2);
				
				// Function to set the min and max values.
				void SetMinMax(double minValue, double maxValue);
				
				// Function to set the sine wave parameters.
				void SetSine(double amplitude, double frequency);
				
			public:
				// Store the color map.
				std::shared_ptr<qbRT::Texture::ColorMap> m_colorMap;
				bool m_haveColorMap = false;
				
				// Store a list of noise generator instances.
				std::vector<qbRT::Noise::GrdNoiseGenerator> m_noiseGeneratorList;
				
				// Store the amplitude.
				double m_amplitude1 = 8.0;
				double m_amplitude2 = 8.0;
				
				// Store the scale.
				int m_scale1 = 4;		
				int m_scale2 = 40;
				
				// Define min and max values.
				double m_maxValue = 1.0;
				double m_minValue = -1.0;			
				
				// Define underlying sine wave parameters.
				double m_sineAmplitude = 0.25;
				double m_sineFrequency = 4.0;	
		};
	}
}

#endif
