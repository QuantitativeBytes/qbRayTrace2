/* ***********************************************************
	valnoisegenerator.hpp
	
	A class to handle value noise generation.
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
	The whole series may be found on the QuantitativeBytes 
	YouTube channel at:
	www.youtube.com/c/QuantitativeBytes
	
	GPLv3 LICENSE
	Copyright (c) 2022 Michael Bennett
	
***********************************************************/

#ifndef VALNOISEGENERATOR_H
#define VALNOISEGENERATOR_H

#include <vector>
#include <random>
#include "noisebase.hpp"

namespace qbRT
{
	namespace Noise
	{
		class ValNoiseGenerator : public NoiseBase
		{
			public:
				// Constructor destructor.
				ValNoiseGenerator();
				virtual ~ValNoiseGenerator() override;
				
				// Function to get the value at a specific location.
				virtual double GetValue(double x, double y) override;
				
				// Function to setup the grid.
				virtual void SetupGrid(int scale) override;
				
			private:				
				
			/* Note that these are declared public for debug purposes only. */
			public:
				// Store the grid of vectors.
				std::vector<std::vector<double>> m_valueGrid;
				
				bool m_wrap = false;

		};
	}
}

#endif
