/* ***********************************************************
	ray.hpp
	
	The ray class implementation - A class to handle rays that can
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
	Copyright (c) 2023 Michael Bennett	
	
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

// ray.cpp

#include "ray.hpp"

qbRT::Ray::Ray()
{
	//m_point1 = qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}};
	//m_point2 = qbVector3<double>{std::vector<double>{0.0, 0.0, 1.0}};
	//m_lab = m_point2 - m_point1;
	m_point1 = qbVector3<double>{0.0, 0.0, 0.0};
	m_point2 = qbVector3<double>{0.0, 0.0, 1.0};
	m_lab = qbVector3<double>{0.0, 0.0, 1.0};
}

qbRT::Ray::Ray(const qbVector3<double> &point1, const qbVector3<double> &point2)
{
	m_point1 = point1;
	m_point2 = point2;
	m_lab = m_point2 - m_point1;
}

qbVector3<double> qbRT::Ray::GetPoint1() const
{
	return m_point1;
}

qbVector3<double> qbRT::Ray::GetPoint2() const
{
	return m_point2;
}
