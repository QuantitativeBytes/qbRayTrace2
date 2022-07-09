/* ***********************************************************
	basicvalnoise.hpp
	
	A class to implement a basic value noise texture
	
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

#ifndef BASICVALNOISE_H
#define BASICVALNOISE_H

#include "../qbNoise/valnoisegenerator.hpp"
#include "texturebase.hpp"
#include "colormap.hpp"

namespace qbRT
{
	namespace Texture
	{
		class BasicValNoise : public TextureBase
		{
			public:
				// Constructor / destructor.
				BasicValNoise();
				virtual ~BasicValNoise() override;
				
				// Function to return the color.
				virtual qbVector<double> GetColor(const qbVector<double> &uvCoords) override;
				
				// Function to set the color map.
				void SetColorMap(const std::shared_ptr<qbRT::Texture::ColorMap> &colorMap);
				
				// Function to set the amplitude.
				void SetAmplitude(double amplitude);
				
				// Function to set the scale.
				void SetScale(int scale);
				
			public:
				// Store the color map.
				std::shared_ptr<qbRT::Texture::ColorMap> m_colorMap;
				bool m_haveColorMap = false;
				
				// We need a NoiseGenerator instance.
				qbRT::Noise::ValNoiseGenerator m_noiseGenerator;
				
				// Store the amplitude.
				double m_amplitude = 8.0;
				
				// Store the scale.
				int m_scale = 3;
				
		};
	}
}

#endif
