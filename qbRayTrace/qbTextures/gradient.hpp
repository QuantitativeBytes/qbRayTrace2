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
				virtual qbVector<double> GetColor(const qbVector<double> &uvCoords) override;
				
				// Function to set stops for the color map.
				void SetStop(double position, const qbVector<double> &value);
				
			private:
				qbRT::Texture::ColorMap m_colorMap;
		};		
	}
}

#endif
