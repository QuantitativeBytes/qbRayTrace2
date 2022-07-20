/* ***********************************************************
	grdnoisegenerator.cpp
	
	A class to handle gradient noise generation.
	
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

#include "grdnoisegenerator.hpp"
#include <cmath>
#include <iostream>

// Constructor function.
qbRT::Noise::GrdNoiseGenerator::GrdNoiseGenerator()
{
	// Configure the default grid.
	SetupGrid(2);
}

// Destructor.
qbRT::Noise::GrdNoiseGenerator::~GrdNoiseGenerator()
{

}

// Function to return the value at a given location.
double qbRT::Noise::GrdNoiseGenerator::GetValue(double x, double y)
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
	
	// Extract the four vectors.
	std::vector<double> v1 {m_vectorGridX.at(c1Xi).at(c1Yi), m_vectorGridY.at(c1Xi).at(c1Yi)};
	std::vector<double> v2 {m_vectorGridX.at(c2Xi).at(c2Yi), m_vectorGridY.at(c2Xi).at(c2Yi)};
	std::vector<double> v3 {m_vectorGridX.at(c3Xi).at(c3Yi), m_vectorGridY.at(c3Xi).at(c3Yi)};
	std::vector<double> v4 {m_vectorGridX.at(c4Xi).at(c4Yi), m_vectorGridY.at(c4Xi).at(c4Yi)};			
	
	// Compute locations of the four corners.
	double c1X = static_cast<double>(c1Xi) * gridSpacing;
	double c1Y = static_cast<double>(c1Yi) * gridSpacing;
	double c2X = static_cast<double>(c2Xi) * gridSpacing;
	double c2Y = static_cast<double>(c2Yi) * gridSpacing;	
	double c3X = static_cast<double>(c3Xi) * gridSpacing;
	double c3Y = static_cast<double>(c3Yi) * gridSpacing;
	double c4X = static_cast<double>(c4Xi) * gridSpacing;
	double c4Y = static_cast<double>(c4Yi) * gridSpacing;		
	
	// Compute the displacement vectors.
	std::vector<double> d1 = ComputeNormDisp(x, y, c1X, c1Y);
	std::vector<double> d2 = ComputeNormDisp(x, y, c2X, c2Y);
	std::vector<double> d3 = ComputeNormDisp(x, y, c3X, c3Y);
	std::vector<double> d4 = ComputeNormDisp(x, y, c4X, c4Y);
														
	// Compute the dot products.
	double dp1 = (v1.at(0) * d1.at(0)) + (v1.at(1) * d1.at(1));
	double dp2 = (v2.at(0) * d2.at(0)) + (v2.at(1) * d2.at(1));
	double dp3 = (v3.at(0) * d3.at(0)) + (v3.at(1) * d3.at(1));
	double dp4 = (v4.at(0) * d4.at(0)) + (v4.at(1) * d4.at(1));
	
	// And interpolate.
	double xWeight = localX * static_cast<double>(m_scale);
	double yWeight = localY * static_cast<double>(m_scale);
	double t1 = Lerp(dp1, dp3, yWeight);
	double t2 = Lerp(dp2, dp4, yWeight);
	return Lerp(t1, t2, xWeight);
}

// Function to configure the grid.
void qbRT::Noise::GrdNoiseGenerator::SetupGrid(int scale)
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
	m_vectorGridX.clear();
	m_vectorGridY.clear();
	m_vectorGridX.resize(m_scale+1, std::vector<double>(m_scale+1, 0.0));
	m_vectorGridY.resize(m_scale+1, std::vector<double>(m_scale+1, 0.0));
	for (int x=0; x <= m_scale; ++x)
	{
		for (int y=0; y <= m_scale; ++y)
		{
			// Compute a random theta.
			double theta = randomDist(randGen) * 2.0 * M_PI;
			
			// Convert this to Cartessian coordinates (assuming r = 1.0).
			double vX = cos(theta);
			double vY = sin(theta);
			
			// And store at the appropriate grid location.
			m_vectorGridX.at(x).at(y) = vX;
			m_vectorGridY.at(x).at(y) = vY;
		}
	}
	
	if (m_wrap)
	{
		for (int x=0; x <= m_scale; ++x)
		{
			m_vectorGridX.at(x).at(m_scale) = m_vectorGridX.at(x).at(0);
			m_vectorGridY.at(x).at(m_scale) = m_vectorGridY.at(x).at(0);
		}
		
		for (int y=0; y <= m_scale; ++y)
		{
			m_vectorGridX.at(m_scale).at(y) = m_vectorGridX.at(0).at(y);
			m_vectorGridY.at(m_scale).at(y) = m_vectorGridY.at(0).at(y);
		}
	}
}

// Function to compute the normalized displacement vector.
std::vector<double> qbRT::Noise::GrdNoiseGenerator::ComputeNormDisp(double x1, double y1, double x2, double y2)
{
	double xComp = x1 - x2;
	double yComp = y1 - y2;

	return std::vector<double> {xComp, yComp};
		
}












