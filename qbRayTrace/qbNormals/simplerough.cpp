/* ***********************************************************
	simplerough.cpp
	
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

#include "simplerough.hpp"

// Constructor / destructor.
qbRT::Normal::SimpleRough::SimpleRough()
{
	std::random_device randDev;
	std::seed_seq seed{randDev(), randDev(), randDev(), randDev()};
	m_p_randGen = std::make_shared<std::mt19937> (seed);	
}

qbRT::Normal::SimpleRough::~SimpleRough()
{

}

qbVector3<double> qbRT::Normal::SimpleRough::ComputePerturbation(const qbVector3<double> &normal, const qbVector2<double> &uvCoords)
{
	std::uniform_real_distribution<double> randomDist (-m_amplitudeScale, m_amplitudeScale);
	double x = randomDist(*m_p_randGen);
	double y = randomDist(*m_p_randGen);
	double z = randomDist(*m_p_randGen);
	
	//double x = uvCoords.GetElement(0) * 0.5;
	//double y = 0.0;
	//double z = 0.0;
	
	qbVector3<double> perturbation = std::vector<double> {x, y, z};
	return PerturbNormal(normal, perturbation);
}
