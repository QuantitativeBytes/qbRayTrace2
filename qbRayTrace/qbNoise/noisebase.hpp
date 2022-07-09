/* ***********************************************************
	noisebase.hpp
	
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

#ifndef NOISEBASE_H
#define NOISEBASE_H

#include <vector>
#include <random>

namespace qbRT
{
	namespace Noise
	{
		class NoiseBase
		{
			public:
				// Constructor / destructor.
				NoiseBase();
				virtual ~NoiseBase();
				
				// Function to get the value at a specified location.
				virtual double GetValue(double u, double v);
				
				// Function for linear interpolation.
				double Lerp(double v1, double v2, double iPos);
				
				// Function to setup the grid.
				virtual void SetupGrid(int scale);
				
			public:
				// Store the scale.
				int m_scale;
				
		};
	}
}

#endif
