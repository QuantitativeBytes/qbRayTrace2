/* ***********************************************************
	image.cpp
	
	The image class implementation - A class to implement
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

#include "image.hpp"

// Constructor / destructor.
qbRT::Texture::Image::Image()
{

}

qbRT::Texture::Image::~Image()
{
	if (m_imageLoaded)
	{
		// Make sure that we free the image surface.
		SDL_FreeSurface(m_imageSurface);
		m_imageLoaded = false;
	}
}

qbVector4<double> qbRT::Texture::Image::GetColor(const qbVector2<double> &uvCoords)
{
	qbVector4<double> outputColor;
	
	if (!m_imageLoaded)
	{
		/* If no image has been loaded yet,
			set the color to the default purple 
			regardless of the (u,v) position. */
		outputColor = qbVector4<double>{std::vector<double>{1.0, 0.0, 1.0, 1.0}};
	}
	else
	{
		// Apply the local transform to the (u,v) coordinates.
		qbVector2<double> inputLoc = uvCoords;
		qbVector2<double> newLoc = ApplyTransform(inputLoc);		
		double u = newLoc.GetElement(0);
		double v = newLoc.GetElement(1);
		
		// Modulo arithmetic to account for possible tiling.
		u = fmod(u, 1.0);
		v = fmod(v, 1.0);	
		
		// Convert (u,v) to image dimensions (x,y).
		double xsd = static_cast<double>(m_xSize);
		double ysd = static_cast<double>(m_ySize);
		double xF = ((u + 1.0) / 2.0) * xsd;
		double yF = ysd - (((v + 1.0) / 2.0) * ysd);
		int x = static_cast<int>(round(xF));
		int y = static_cast<int>(round(yF));
		int xMin = static_cast<int>(floor(xF));
		int yMin = static_cast<int>(floor(yF));
		int xMax = static_cast<int>(ceil(xF));
		int yMax = static_cast<int>(ceil(yF));		
		
		// Verify that we are within the image.
		// Probably not necessary, but seems like a good idea just in case.
		if ((x >= 0) && (x < m_xSize) && (y >= 0) && (y < m_ySize))
		{
			// Perform bilinear interpolation.
			double r0, g0, b0, a0;
			double r1, g1, b1, a1;
			double r2, g2, b2, a2;
			double r3, g3, b3, a3;
			GetPixelValue(xMin, yMin, r0, g0, b0, a0);
			GetPixelValue(xMax, yMin, r1, g1, b1, a1);
			GetPixelValue(xMin, yMax, r2, g2, b2, a2);
			GetPixelValue(xMax, yMax, r3, g3, b3, a3);
			double interpR = BilinearInterp(xMin, yMin, r0, xMax, yMin, r1, xMin, yMax, r2, xMax, yMax, r3, xF, yF);
			double interpG = BilinearInterp(xMin, yMin, g0, xMax, yMin, g1, xMin, yMax, g2, xMax, yMax, g3, xF, yF);
			double interpB = BilinearInterp(xMin, yMin, b0, xMax, yMin, b1, xMin, yMax, b2, xMax, yMax, b3, xF, yF);	
			double interpA = BilinearInterp(xMin, yMin, a0, xMax, yMin, a1, xMin, yMax, a2, xMax, yMax, a3, xF, yF);		
			
			// Set the outputColor vector accordingly.
			outputColor.SetElement(0, interpR / 255.0);
			outputColor.SetElement(1, interpG / 255.0);
			outputColor.SetElement(2, interpB / 255.0);
			outputColor.SetElement(3, interpA / 255.0);
		}
	}
	
	return outputColor;
}

bool qbRT::Texture::Image::LoadImage(std::string fileName)
{
	if (m_imageLoaded)
		SDL_FreeSurface(m_imageSurface);
	
	m_fileName = fileName;
	m_imageSurface = SDL_LoadBMP(fileName.c_str());
	
	if (!m_imageSurface)
	{
		std::cout << "Failed to load image. " << SDL_GetError() << "." << std::endl;
		m_imageLoaded = false;
		return false;
	}

	// Extract useful information.
	m_xSize = m_imageSurface->w;
	m_ySize = m_imageSurface->h;
	m_pitch = m_imageSurface->pitch;
	m_pixelFormat = m_imageSurface->format;
	m_bytesPerPixel = m_pixelFormat->BytesPerPixel;
	m_rMask = m_pixelFormat->Rmask;
	m_gMask = m_pixelFormat->Gmask;
	m_bMask = m_pixelFormat->Bmask;
	m_aMask = m_pixelFormat->Amask;
	
	std::cout << "Loaded " << m_imageSurface->w << " by " << m_imageSurface->h << "." << std::endl;
	std::cout << "Bytes per pixel = " << +m_bytesPerPixel << std::endl;
	std::cout << "Pitch = " << m_pitch << std::endl;

	m_imageLoaded = true;
	return true;
}

// ************************************************************************
// Function to return the value (RGBA) of a pixel in the image surface.
// Note that the RGBA values are scaled to be between -1 and 1.
// (0 to -1 for the z axis of the perturbation)
// ************************************************************************
void qbRT::Texture::Image::GetPixelValue(int x, int y, double &red, double &green, double &blue, double &alpha)
{
	if ((x >= 0) && (x < m_xSize) && (y >= 0) && (y < m_ySize))
	{	
		// Convert (x,y) to a linear index, in bytes.
		int pixelIndex = (x * m_bytesPerPixel) + (y * m_pitch);
			
		// Get a pointer to the pixel data.
		uint8_t *pixels = (uint8_t *)m_imageSurface->pixels;
			
		// Extract the current pixel value.
		std::array<uint8_t, 4> byteValues;
		uint32_t currentPixel = 0;
		for (int i=0; i<m_bytesPerPixel; ++i)
		{
			byteValues.at(i) = pixels[pixelIndex+i];
		}

		// Assemble the final pixel value, according to the number of bytes per pixel.
		switch (m_bytesPerPixel)
		{
			case 3:
				currentPixel = byteValues.at(0) | (byteValues.at(1) << 8) | (byteValues.at(2) << 16);
				break;
				
			case 4:
				currentPixel = byteValues.at(0) | (byteValues.at(1) << 8) | (byteValues.at(2) << 16) | (byteValues.at(3) << 24);
				break;
		}
			
		// Convert to RGB.
		uint8_t r, g, b, a;
		SDL_GetRGBA(currentPixel, m_imageSurface->format, &r, &g, &b, &a);
			
		// Return the color.		
		red = static_cast<double>(r);
		green = static_cast<double>(g);
		blue = static_cast<double>(b);
	}	
}
// ************************************************************************
// Functions to handle interpolation.
// ************************************************************************
double qbRT::Texture::Image::LinearInterp(const double &x0, const double &y0, const double &x1, const double &y1, const double &x)
{
	double output;
	
	if ((x1-x0) == 0.0)
		output = y0;
	else
		output = y0 + ((x - x0)*((y1 - y0)/(x1 - x0)));
		
	return output;
}

double qbRT::Texture::Image::BilinearInterp(const double &x0, const double &y0, const double &v0,
																						const double &x1, const double &y1, const double &v1,
																						const double &x2, const double &y2, const double &v2,
																						const double &x3, const double &y3, const double &v3,
																						const double &x, const double &y)
{
	double p1 = LinearInterp(x0, v0, x1, v1, x);
	double p2 = LinearInterp(x2, v2, x3, v3, x);
	double p3 = LinearInterp(y0, p1, y2, p2, y);
	return p3;
}

