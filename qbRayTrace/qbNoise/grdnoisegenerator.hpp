/* ***********************************************************
	grdnoisegenerator.hpp
	
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

#ifndef GRDNOISEGENERATOR_H
#define GRDNOISEGENERATOR_H

#include <vector>
#include <random>
#include "noisebase.hpp"

namespace qbRT
{
	namespace Noise
	{
		class GrdNoiseGenerator : public NoiseBase
		{
			public:
				// Constructor destructor.
				GrdNoiseGenerator();
				virtual ~GrdNoiseGenerator() override;
				
				// Function to get the value at a specific location.
				virtual double GetValue(double x, double y) override;
				
				// Function to setup the grid.
				virtual void SetupGrid(int scale) override;
				
			private:				
				// Normalize vector.
				std::vector<double> ComputeNormDisp(double x1, double y1, double x2, double y2);
				
			/* Note that these are declared public for debug purposes only. */
			public:
				// Store the grid of vectors.
				std::vector<std::vector<double>> m_vectorGridX;
				std::vector<std::vector<double>> m_vectorGridY;
				
				bool m_wrap = false;

		};
	}
}

#endif
