/* ***********************************************************
	marble.cpp
	
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


#include "marble.hpp"
#include <algorithm>

// Constructor / destructor.
qbRT::Texture::Marble::Marble()
{
	// Configure the noise generators.
	m_noiseGeneratorList.push_back(qbRT::Noise::GrdNoiseGenerator());
	m_noiseGeneratorList.push_back(qbRT::Noise::GrdNoiseGenerator());
	
	m_noiseGeneratorList.at(0).SetupGrid(4);
	m_noiseGeneratorList.at(1).SetupGrid(40);
	
	m_minValue = -3.0;
	m_maxValue = 3.0;
	
}

qbRT::Texture::Marble::~Marble()
{

}

// Function to return the color.
qbVector4<double> qbRT::Texture::Marble::GetColor(const qbVector2<double> &uvCoords)
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
		double mapPosition = 	m_sineAmplitude * 
													sin(m_sineFrequency * M_PI *
													(((newU + newV) / 2.0) + 
													(m_noiseGeneratorList.at(0).GetValue(newU, newV) * m_amplitude1) + 
													(m_noiseGeneratorList.at(1).GetValue(newU, newV) * m_amplitude2) ));
													
		// Normalize to min and max values.
		mapPosition = std::clamp((mapPosition - m_minValue) / (m_maxValue - m_minValue), 0.0, 1.0);
		
		localColor = m_colorMap -> GetColor(mapPosition);
	}
	
	return localColor;	
	
}

// Function to set the color map.
void qbRT::Texture::Marble::SetColorMap(const std::shared_ptr<qbRT::Texture::ColorMap> &colorMap)
{
	m_colorMap = colorMap;
	m_haveColorMap = true;
}

// Function to set the ammplitude.
void qbRT::Texture::Marble::SetAmplitude(double amplitude1, double amplitude2)
{
	m_amplitude1 = amplitude1;
	m_amplitude2 = amplitude2;
}

// Function to set the scale.
void qbRT::Texture::Marble::SetScale(int scale1, int scale2)
{
	m_scale1 = scale1;
	m_scale2 = scale2;
	m_noiseGeneratorList.at(0).SetupGrid(m_scale1);
	m_noiseGeneratorList.at(1).SetupGrid(m_scale2);
}

// Function to set the min and max values.
void qbRT::Texture::Marble::SetMinMax(double minValue, double maxValue)
{
	m_minValue = minValue;
	m_maxValue = maxValue;
}

// Function to set the sine wave parameters.
void qbRT::Texture::Marble::SetSine(double amplitude, double frequency)
{
	m_sineAmplitude = amplitude;
	m_sineFrequency = frequency;
}
