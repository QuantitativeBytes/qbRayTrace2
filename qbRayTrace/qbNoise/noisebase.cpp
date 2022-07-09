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
