/* ***********************************************************
	qbStone1.hpp
	
	A class to implement a basic stone texture
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
	The whole series may be found on the QuantitativeBytes 
	YouTube channel at:
	www.youtube.com/c/QuantitativeBytes
	
	GPLv3 LICENSE
	
***********************************************************/

#ifndef QBSTONE1_H
#define QBSTONE1_H

#include "../qbNoise/valnoisegenerator.hpp"
#include "texturebase.hpp"
#include "colormap.hpp"

namespace qbRT
{
	namespace Texture
	{
		class qbStone1 : public TextureBase
		{
			public:
				// Constructor / destructor.
				qbStone1();
				virtual ~qbStone1() override;
				
				// Function to return the color.
				virtual qbVector<double> GetColor(const qbVector<double> &uvCoords) override;
				
				// Function to return the value.
				virtual double GetValue(const qbVector<double> &uvCoords) override;
				
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
				qbRT::Noise::ValNoiseGenerator m_noiseGenerator1;
				qbRT::Noise::ValNoiseGenerator m_noiseGenerator2;
				
				// Store the amplitude.
				double m_amplitude1 = 8.0;
				double m_amplitude2 = 4.0;
				
				// Store the scale.
				int m_scale1 = 6;
				int m_scale2 = 30;
				
				// Store the min and max values.
				double m_minValue, m_maxValue;
				
		};
	}
}

#endif
