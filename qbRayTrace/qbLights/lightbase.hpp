/* ***********************************************************
	lightbase.hpp
	
	The light base class definition - A base class for handling
	lights.
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
	This code corresponds specifically to Episode 4 of the series,
	which may be found here:
	https://youtu.be/dUtkihuUvvo
	
	The whole series may be found on the QuantitativeBytes 
	YouTube channel at:
	www.youtube.com/c/QuantitativeBytes
	
	GPLv3 LICENSE
	Copyright (c) 2021 Michael Bennett
	
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
#ifndef LIGHTBASE_H
#define LIGHTBASE_H

#include <memory>
#include "../qbLinAlg/qbVector.h"
#include "../ray.hpp"
#include "../qbPrimatives/objectbase.hpp"

namespace qbRT
{
	class LightBase
	{
		public:
			// Constructor / destructor.
			LightBase();
			virtual ~LightBase();
			
			// Function to compute illumination contribution.
			virtual bool ComputeIllumination(	const qbVector3<double> &intPoint, const qbVector3<double> &localNormal,
																				const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
																				const std::shared_ptr<qbRT::ObjectBase> &currentObject,
																				qbVector3<double> &color, double &intensity);
																				
		public:
			qbVector3<double>	m_color			{3};
			qbVector3<double>	m_location	{3};
			double						m_intensity;
	};
}

#endif
