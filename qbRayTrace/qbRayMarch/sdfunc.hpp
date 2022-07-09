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

namespace qbRT
{
	namespace RM
	{
		namespace SDF
		{
			double Sphere(const qbVector<double> &p, const qbVector<double> &center, const qbVector<double> &parms);
			double Torus(const qbVector<double> &p, const qbVector<double> &center, const qbVector<double> &parms);
			double Box(const qbVector<double> &p, const qbVector<double> &center, const qbVector<double> &parms);
		}
	}
}

#endif
