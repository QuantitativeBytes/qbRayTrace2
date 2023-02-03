/* ***********************************************************
	basicvalnoise.cpp
	
	A class to implement a basic value noise texture.
	
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

#include "basicvalnoise.hpp"
#include <algorithm>

// Constructor / destructor.
qbRT::Texture::BasicValNoise::BasicValNoise()
{
	// Configure the noise generator.
	m_noiseGenerator.SetupGrid(m_scale);
	
}

qbRT::Texture::BasicValNoise::~BasicValNoise()
{

}

// Function to return the color.
qbVector4<double> qbRT::Texture::BasicValNoise::GetColor(const qbVector2<double> &uvCoords)
{
	// Apply the local transform to the (u,v) coordinates.
	qbVector2<double> inputLoc = uvCoords;
	qbVector2<double> newLoc = ApplyTransform(inputLoc);
	double newU = newLoc.GetElement(0);
	double newV = newLoc.GetElement(1);
	
	qbVector4<double> localColor;
	/* If no color map has been provided, then output purple. This should be
		easily recognizable in the scene, indicating that something is wrong. */
	if (!m_haveColorMap)
	{
		localColor = qbVector4<double>{std::vector<double>{1.0, 0.0, 1.0, 1.0}};
	}
	else
	{
		// Generate the base function.
		double mapPosition = std::clamp(m_noiseGenerator.GetValue(newU, newV) * m_amplitude, 0.0, 1.0);
		localColor = m_colorMap -> GetColor(mapPosition);
	}
	
	return localColor;
}

// Function to set the color map.
void qbRT::Texture::BasicValNoise::SetColorMap(const std::shared_ptr<qbRT::Texture::ColorMap> &colorMap)
{
	m_colorMap = colorMap;
	m_haveColorMap = true;
}

// Function to set the ammplitude.
void qbRT::Texture::BasicValNoise::SetAmplitude(double amplitude)
{
	m_amplitude = amplitude;
}

// Function to set the scale.
void qbRT::Texture::BasicValNoise::SetScale(int scale)
{
	m_scale = scale;
	m_noiseGenerator.SetupGrid(m_scale);
}
