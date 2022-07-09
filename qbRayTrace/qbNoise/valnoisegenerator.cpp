/* ***********************************************************
	valnoisegenerator.cpp
	
	A class to handle value noise generation.
	
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

#include "valnoisegenerator.hpp"
#include <cmath>
#include <iostream>

// Constructor function.
qbRT::Noise::ValNoiseGenerator::ValNoiseGenerator()
{
	// Configure the default grid.
	SetupGrid(2);
}

// Destructor.
qbRT::Noise::ValNoiseGenerator::~ValNoiseGenerator()
{

}

// Function to return the value at a given location.
double qbRT::Noise::ValNoiseGenerator::GetValue(double x, double y)
{
	// Ensure that x and y are cyclic.
	x = fmod(x, 1.0);
	y = fmod(y, 1.0);
	
	// Convert x and y to a range of 0 to 1.
	x = (x + 1.0) / 2.0;
	y = (y + 1.0) / 2.0;
	
	// Determine the spacing of the grid boundaries.
	double gridSpacing = 1.0 / static_cast<double>(m_scale);
	
	// Compute local x and y.
	double localX = fmod(x, gridSpacing);
	double localY = fmod(y, gridSpacing);
	
	// Compute the grid corner indices.
	int minX = static_cast<int>((x - localX) * m_scale);
	int minY = static_cast<int>((y - localY) * m_scale);
	
	int c1Xi = std::max(minX, 0);
	int c1Yi = std::max(minY, 0);
	int c2Xi = std::min(minX + 1, m_scale);
	int c2Yi = std::max(minY, 0);
	
	int c3Xi = std::max(minX, 0);
	int c3Yi = std::min(minY + 1, m_scale);
	int c4Xi = std::min(minX + 1, m_scale);
	int c4Yi = std::min(minY + 1, m_scale);
	
	// Extract the four values.
	double v1 = m_valueGrid.at(c1Xi).at(c1Yi);
	double v2 = m_valueGrid.at(c2Xi).at(c2Yi);
	double v3 = m_valueGrid.at(c3Xi).at(c3Yi);
	double v4 = m_valueGrid.at(c4Xi).at(c4Yi);		

	// And interpolate.
	double xWeight = localX * static_cast<double>(m_scale);
	double yWeight = localY * static_cast<double>(m_scale);
	double t1 = Lerp(v1, v3, yWeight);
	double t2 = Lerp(v2, v4, yWeight);
	return Lerp(t1, t2, xWeight);
}

// Function to configure the grid.
void qbRT::Noise::ValNoiseGenerator::SetupGrid(int scale)
{
	m_scale = scale;

	// Generate a seed for the random number generation.
	std::random_device randDev;
	std::seed_seq seed{randDev(), randDev(), randDev(), randDev()};

	// The random number generator
	
	/* Use the seed version if you want a different pattern everytime,
		or use without seed, or with a fixed seed, if you want the 
		pattern to remain the same every time. */
	
	//std::mt19937 randGen(seed);
	std::mt19937 randGen;

	// Setup the random number distribution.
	// (uniform real numbers betweeon 0 and 1).
	std::uniform_real_distribution<double> randomDist (0.0, 1.0);
	
	// Generate the grid of random vectors.
	/*
		'scale' defines how many grid squares we want, so a scale of
		1 means a single grid square, 2 means a 2x2 grid, 3 a 3x3 grid
		and so on.
	*/
	m_valueGrid.clear();
	m_valueGrid.resize(m_scale+1, std::vector<double>(m_scale+1, 0.0));
	for (int x=0; x <= m_scale; ++x)
	{
		for (int y=0; y <= m_scale; ++y)
		{
			// Store a random value.
			m_valueGrid.at(x).at(y) = randomDist(randGen);
		}
	}
	
	if (m_wrap)
	{
		for (int x=0; x <= m_scale; ++x)
		{
			m_valueGrid.at(x).at(m_scale) = m_valueGrid.at(x).at(0);
		}
		
		for (int y=0; y <= m_scale; ++y)
		{
			m_valueGrid.at(m_scale).at(y) = m_valueGrid.at(0).at(y);
		}
	}	
}











