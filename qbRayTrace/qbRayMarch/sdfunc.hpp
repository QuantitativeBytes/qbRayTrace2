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
