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
qbVector<double> qbRT::Texture::BasicValNoise::GetColor(const qbVector<double> &uvCoords)
{
	// Apply the local transform to the (u,v) coordinates.
	qbVector<double> inputLoc = uvCoords;
	qbVector<double> newLoc = ApplyTransform(inputLoc);
	double newU = newLoc.GetElement(0);
	double newV = newLoc.GetElement(1);
	
	qbVector<double> localColor {4};
	/* If no color map has been provided, then output purple. This should be
		easily recognizable in the scene, indicating that something is wrong. */
	if (!m_haveColorMap)
	{
		localColor = qbVector<double>{std::vector<double>{1.0, 0.0, 1.0, 1.0}};
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
