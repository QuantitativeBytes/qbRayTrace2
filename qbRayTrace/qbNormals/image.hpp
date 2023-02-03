/* ***********************************************************
	image.hpp
	
	The image normal class. A simple implementation of image
	based normal maps.
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
	The whole series may be found on the QuantitativeBytes 
	YouTube channel at:
	www.youtube.com/c/QuantitativeBytes
	
	GPLv3 LICENSE
	
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


#ifndef Image_H
#define Image_H

#include "normalbase.hpp"
#include <SDL2/SDL.h>
#include <random>

namespace qbRT
{
	namespace Normal
	{
		class Image : public NormalBase
		{
			public:
				// Constructor / Destructor.
				Image();
				virtual ~Image() override;
				
				// Function to load the image to be used.
				bool LoadImage(std::string fileName);
			
				// Function to compute the perturbation.
				virtual qbVector3<double> ComputePerturbation(const qbVector3<double> &normal, const qbVector2<double> &uvCoords) override;
				
			private:
				// Functions to handle interpolation.
				double LinearInterp(const double &x0, const double &y0, const double &x1, const double &y1, const double &x);
				double BilinearInterp(	const double &x0, const double &y0, const double &v0,
																const double &x1, const double &y1, const double &v1,
																const double &x2, const double &y2, const double &v2,
																const double &x3, const double &y3, const double &v3,
																const double &x, const double &y);
			
				// Function to return the value of a pixel in the image surface.													
				void GetPixelValue(int x, int y, double &red, double &green, double &blue, double &alpha);
				
			public:
				bool m_reverseXY = false;
				
			private:
				// Initialise the transform matrix to the identity matrix.
				qbMatrix2<double> m_transformMatrix {3, 3, std::vector<double>{1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0}};
				
				// TO BE DELETED.			
				std::shared_ptr<std::mt19937> m_p_randGen;
				
				// SDL2 stuff to handle the image.
				std::string m_fileName;
				SDL_Surface *m_imageSurface;
				SDL_PixelFormat *m_pixelFormat;
				bool m_imageLoaded = false;
				int m_xSize, m_ySize, m_pitch;
				uint8_t m_bytesPerPixel;				
				
		};
	}
}

#endif
