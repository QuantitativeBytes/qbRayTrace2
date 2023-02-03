/* ***********************************************************
	image.hpp
	
	The image class definition - A class to implement
	image based textures.
	
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

#ifndef IMAGE_H
#define IMAGE_H

#include "texturebase.hpp"
#include <SDL2/SDL.h>

namespace qbRT
{
	namespace Texture
	{
		class Image : public TextureBase
		{
			public:
				Image();
				virtual ~Image() override;
				
				// Function to return the color.
				virtual qbVector4<double> GetColor(const qbVector2<double> &uvCoords) override;
			
				// Function to load the image to be used.
				bool LoadImage(std::string fileName);
				
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
				
			private:
				std::string m_fileName;
				SDL_Surface *m_imageSurface;
				SDL_PixelFormat *m_pixelFormat;
				bool m_imageLoaded = false;
				int m_xSize, m_ySize, m_pitch;
				uint8_t m_bytesPerPixel;
				uint32_t m_rMask, m_gMask, m_bMask, m_aMask;				
							
		};
	}
}

#endif
