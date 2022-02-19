/* ***********************************************************
	gradient.hpp
	
	The gradient class implementation. An implementation of a simple
	gradient texture.
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
	The whole series may be found on the QuantitativeBytes 
	YouTube channel at:
	www.youtube.com/c/QuantitativeBytes
	
	GPLv3 LICENSE
	Copyright (c) 2022 Michael Bennett
	
***********************************************************/
#include "gradient.hpp"

// Constructor.
qbRT::Texture::Gradient::Gradient()
{

}

// Destructor.
qbRT::Texture::Gradient::~Gradient()
{

}

// Function to return the color.
qbVector<double> qbRT::Texture::Gradient::GetColor(const qbVector<double> &uvCoords)
{
	// Apply the local transform to the (u,v) coordinates.
	qbVector<double> inputLoc = uvCoords;
	qbVector<double> newLoc = ApplyTransform(inputLoc);
	double newU = std::min((newLoc.GetElement(1) + 1.0) / 2.0, 1.0);
	return m_colorMap.GetColor(newU);
}

// Function to set the stops for the color map
void qbRT::Texture::Gradient::SetStop(double position, const qbVector<double> &value)
{
	m_colorMap.SetStop(position, value);
}
