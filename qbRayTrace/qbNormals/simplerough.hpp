/* ***********************************************************
	simplerough.hpp
	
	The simplerough class definition. A very simple random
	noise based normal map.
	
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

#ifndef SIMPLEROUGH_H
#define SIMPLEROUGH_H

#include "normalbase.hpp"
#include <random>

namespace qbRT
{
	namespace Normal
	{
		class SimpleRough : public NormalBase
		{
			public:
				// Constructor / Destructor.
				SimpleRough();
				virtual ~SimpleRough() override;
			
				// Function to compute the perturbation.
				virtual qbVector3<double> ComputePerturbation(const qbVector3<double> &normal, const qbVector2<double> &uvCoords) override;
				
			public:
				
			private:
				std::shared_ptr<std::mt19937> m_p_randGen;
				
		};
	}
}

#endif
