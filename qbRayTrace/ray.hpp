/* ***********************************************************
	ray.hpp
	
	The ray class definition - A class to handle rays that can
	be cast around the scene.
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
	This code corresponds specifically to Episode 2 of the series,
	which may be found here:
	https://youtu.be/KBK6g6RFgdA
	
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

// ray.hpp

#ifndef RAY_H
#define RAY_H

#include "./qbLinAlg/qbVector.h"

namespace qbRT
{
	class Ray
	{
		public:
			Ray();
			Ray(const qbVector<double> &point1, const qbVector<double> &point2);
			
			qbVector<double> GetPoint1() const;
			qbVector<double> GetPoint2() const;
			
		public:
			qbVector<double> m_point1	{3};
			qbVector<double> m_point2 {3};
			qbVector<double> m_lab		{3};
			
	};
}

#endif
