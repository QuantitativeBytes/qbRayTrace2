/* ***********************************************************
	sdfunc.hpp
	
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

#ifndef SDFUNC_H
#define SDFFUNC_H

#include "../qbLinAlg/qbVector.h"
#include "../qbLinAlg/qbVector2.hpp"
#include "../qbLinAlg/qbVector3.hpp"
#include "../qbLinAlg/qbVector4.hpp"

namespace qbRT
{
	namespace RM
	{
		namespace SDF
		{
			double Sphere(const qbVector3<double> &p, const qbVector3<double> &center, const qbVector3<double> &parms);
			double Torus(const qbVector3<double> &p, const qbVector3<double> &center, const qbVector3<double> &parms);
			double Box(const qbVector3<double> &p, const qbVector3<double> &center, const qbVector3<double> &parms);
		}
	}
}

#endif
