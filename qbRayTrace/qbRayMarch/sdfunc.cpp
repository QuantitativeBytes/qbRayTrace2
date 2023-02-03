/* ***********************************************************
	sdfunc.cpp
	
	A series of functions that implement the signed distance
	functions for a number of different shapes.
	
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

#include "sdfunc.hpp"

// Sphere
double qbRT::RM::SDF::Sphere(const qbVector3<double> &p, const qbVector3<double> &center, const qbVector3<double> &parms)
{
	return (p - center).norm() - parms.GetElement(0);
}

// Torus
double qbRT::RM::SDF::Torus(const qbVector3<double> &p, const qbVector3<double> &center, const qbVector3<double> &parms)
{
	double x = p.GetElement(0) - center.GetElement(0);
	double y = p.GetElement(1) - center.GetElement(1);
	double z = p.GetElement(2) - center.GetElement(2);
	
	double t1 = sqrtf((x*x) + (y*y)) - parms.GetElement(0);
	double t2 = sqrtf((t1*t1) + (z*z)) - parms.GetElement(1);
	
	return t2;
}

// Box
double qbRT::RM::SDF::Box(const qbVector3<double> &p, const qbVector3<double> &center, const qbVector3<double> &parms)
{
	qbVector3<double> location = (p - center);
	double ax = fabs(location.GetElement(0)) - parms.GetElement(0);
	double ay = fabs(location.GetElement(1)) - parms.GetElement(1);
	double az = fabs(location.GetElement(2)) - parms.GetElement(2);
	
	double bx = std::max(ax, 0.0);
	double by = std::max(ay, 0.0);
	double bz = std::max(az, 0.0);
	
	double internalDist = std::min(std::max(ax, std::max(ay, az)), 0.0);
	double externalDist = sqrt((bx*bx)+(by*by)+(bz*bz));
	
	return internalDist + externalDist;
}
