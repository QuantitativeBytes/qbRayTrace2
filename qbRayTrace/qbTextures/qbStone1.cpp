/* ***********************************************************
	qbStone1.cpp
	
	A class to implement a basic noise texture.
	
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

#include "qbStone1.hpp"
#include <algorithm>

// Constructor / destructor.
qbRT::Texture::qbStone1::qbStone1()
{
	// Initial configuration.
	m_amplitude1 = 1.0;
	m_amplitude2 = 1.0;
	m_scale1 = 32;
	m_scale2 = 64;
	m_minValue = -2.0;
	m_maxValue = 2.0;

	// Configure the noise generators.
	m_noiseGenerator1.SetupGrid(m_scale1);
	m_noiseGenerator2.SetupGrid(m_scale2);
	
	// Configure the color map.
	auto stoneMap = std::make_shared<qbRT::Texture::ColorMap> (qbRT::Texture::ColorMap());
	stoneMap -> SetStop(0.0, qbVector4<double>{std::vector<double>{0.2, 0.2, 0.2, 1.0}});
	stoneMap -> SetStop(0.25, qbVector4<double>{std::vector<double>{0.8, 0.8, 0.8, 1.0}});
	stoneMap -> SetStop(0.5, qbVector4<double>{std::vector<double>{0.5, 0.5, 0.5, 1.0}});
	stoneMap -> SetStop(0.75, qbVector4<double>{std::vector<double>{0.1, 0.1, 0.1, 1.0}});
	stoneMap -> SetStop(1.0, qbVector4<double>{std::vector<double>{0.2, 0.2, 0.2, 1.0}});
	SetColorMap(stoneMap);	
	
}

qbRT::Texture::qbStone1::~qbStone1()
{

}

// Function to return the color.
qbVector4<double> qbRT::Texture::qbStone1::GetColor(const qbVector2<double> &uvCoords)
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
		double mapPosition = 	m_noiseGenerator1.GetValue(newU, newV) * m_amplitude1 + 
													m_noiseGenerator2.GetValue(newU, newV) * m_amplitude2;
													
		mapPosition = std::clamp((mapPosition - m_minValue) / (m_maxValue - m_minValue), 0.0, 1.0);
		localColor = m_colorMap -> GetColor(mapPosition);
	}
	
	return localColor;
}

// Function to return the value.
double qbRT::Texture::qbStone1::GetValue(const qbVector2<double> &uvCoords)
{
	// Apply the local transform to the (u,v) coordinates.
	qbVector2<double> inputLoc = uvCoords;
	qbVector2<double> newLoc = ApplyTransform(inputLoc);
	double newU = newLoc.GetElement(0);
	double newV = newLoc.GetElement(1);
	
	double mapPosition = 	m_noiseGenerator1.GetValue(newU, newV) * m_amplitude1 + 
												m_noiseGenerator2.GetValue(newU, newV) * m_amplitude2;
										
	mapPosition = std::clamp((mapPosition - m_minValue) / (m_maxValue - m_minValue), 0.0, 1.0);
	return mapPosition;
}

// Function to set the color map.
void qbRT::Texture::qbStone1::SetColorMap(const std::shared_ptr<qbRT::Texture::ColorMap> &colorMap)
{
	m_colorMap = colorMap;
	m_haveColorMap = true;
}

// Function to set the ammplitude.
void qbRT::Texture::qbStone1::SetAmplitude(double amplitude)
{
	m_amplitude1 = amplitude;
}

// Function to set the scale.
void qbRT::Texture::qbStone1::SetScale(int scale)
{
	m_scale1 = scale;
	m_noiseGenerator1.SetupGrid(m_scale1);
}
