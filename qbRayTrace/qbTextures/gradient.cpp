/* ***********************************************************
	gradient.cpp
	
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
qbVector4<double> qbRT::Texture::Gradient::GetColor(const qbVector2<double> &uvCoords)
{
	// Apply the local transform to the (u,v) coordinates.
	qbVector2<double> inputLoc = uvCoords;
	qbVector2<double> newLoc = ApplyTransform(inputLoc);
	double newU = std::min((newLoc.GetElement(1) + 1.0) / 2.0, 1.0);
	return m_colorMap.GetColor(newU);
}

// Function to return the value.
double qbRT::Texture::Gradient::GetValue(const qbVector2<double> &uvCoords)
{
	// Apply the local transform to the (u,v) coordinates.
	qbVector2<double> inputLoc = uvCoords;
	qbVector2<double> newLoc = ApplyTransform(inputLoc);
	return std::min((newLoc.GetElement(0) + 1.0) / 2.0, 1.0);	
}

// Function to set the stops for the color map
void qbRT::Texture::Gradient::SetStop(double position, const qbVector4<double> &value)
{
	m_colorMap.SetStop(position, value);
}
