/* ***********************************************************
	noisebase.cpp
	
	A base class for implementing different types of noise.
	
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

#include "noisebase.hpp"

// Default constructor.
qbRT::Noise::NoiseBase::NoiseBase()
{

}

// The destructor.
qbRT::Noise::NoiseBase::~NoiseBase()
{

}

// Function to return the value at a given location.
double qbRT::Noise::NoiseBase::GetValue(double u, double v)
{
	// Return a default value.
	return 0.0;
}

// Function for linear interpolation.
double qbRT::Noise::NoiseBase::Lerp(double v1, double v2, double iPos)
{
	/* Note that here we are assuming the iPos will always be
		between 0 and 1. If we can't make that assumption, then
		we should ensure that it is between 0 and 1 before using
		it to compute fade. */
		
	// Smoothstep fade.
	double fade = iPos * iPos * (3 - 2 * iPos);
	
	// Linear fade.
	//double fade = iPos;
	
	// Implement the actual linear interpolation.
	return v1 + fade * (v2 - v1);	
}

// Function to setup the grid.
void qbRT::Noise::NoiseBase::SetupGrid(int scale)
{
	m_scale = scale;
}
