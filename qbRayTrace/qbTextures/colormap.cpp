/* ***********************************************************
	colormap.cpp
	
	The colormap class implementation. A class to handle color
	maps with any number of stops.
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
	The whole series may be found on the QuantitativeBytes 
	YouTube channel at:
	www.youtube.com/c/QuantitativeBytes
	
	GPLv3 LICENSE
	
***********************************************************/

#include "colormap.hpp"

// Constructor.
qbRT::Texture::ColorMap::ColorMap()
{

}

// Destructor.
qbRT::Texture::ColorMap::~ColorMap()
{

}

// Function to set a stop.
void qbRT::Texture::ColorMap::SetStop(double position, const qbVector<double> &value)
{
	m_stopPositions.push_back(position);
	m_stopValues.push_back(value);
}

// Function to get the color at a specified position.
qbVector<double> qbRT::Texture::ColorMap::GetColor(double position)
{
	// Find the closest stops to the current position.
	int numStops = m_stopPositions.size();
	int firstStop = 0;
	int secondStop = 0;
	double diff = 2.0;
	for (int i=0; i<numStops; ++i)
	{
		double t = m_stopPositions.at(i) - position;
		if (fabs(t) < diff)
		{
			diff = fabs(t);
			firstStop = i;
			if (t < 0.0)
				secondStop = std::min(numStops, (i + 1));
			else if (t > 0.0)
				secondStop = std::max((i - 1), 0);
			else
				secondStop = i;
		}
	}
	
	// If the position was exactly at a stop, we simply return that value.
	if (firstStop == secondStop)
		return m_stopValues.at(firstStop);
		
	// Otherwise we need to interpolate between the first and second stops.
	// Make sure the stops are in the right order.
	if (secondStop < firstStop)
		std::swap(firstStop, secondStop);
		
	// Perform linear interpolation of the values between the two stops.
	// y0 + ((x - x0)*((y1 - y0)/(x1 - x0)))
	double x = position;
	double x0 = m_stopPositions.at(firstStop);
	double x1 = m_stopPositions.at(secondStop);
	return m_stopValues.at(firstStop) + (x - x0) * ((m_stopValues.at(secondStop) - m_stopValues.at(firstStop)) * (1.0 / (x1 - x0)));
}
