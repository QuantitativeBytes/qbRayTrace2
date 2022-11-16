/* ***********************************************************
	objectplane.cpp
	
	The ObjPlane class implementation - A class derived from
	ObjectBase to implement finite planes.
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
	This code corresponds specifically to Episode 6 of the series,
	which may be found here:
	https://youtu.be/9K9ZYq6KgFY
	
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

// objplane.cpp

#include "objplane.hpp"
#include "../qbutils.hpp"
#include <cmath>

// The default constructor.
qbRT::ObjPlane::ObjPlane()
{

}

// The destructor.
qbRT::ObjPlane::~ObjPlane()
{

}

// The function to test for intersections.
bool qbRT::ObjPlane::TestIntersection(	const qbRT::Ray &castRay, qbRT::DATA::hitData &hitData)
{
	if (!m_isVisible)
		return false;
		
	// Copy the ray and apply the backwards transform.
	qbRT::Ray bckRay = m_transformMatrix.Apply(castRay, qbRT::BCKTFORM);
	
	// Copy the m_lab vector from bckRay and normalize it.
	qbVector<double> k = bckRay.m_lab;
	k.Normalize();
	
	/* Check if there is an intersection, ie. if the castRay is not parallel
		to the plane. */
	if (!CloseEnough(k.GetElement(2), 0.0))
	{
		// There is an intersection.
		double t = bckRay.m_point1.GetElement(2) / -k.GetElement(2);
		
		/* If t is negative, then the intersection point must be behind
			the camera and we can ignore it. */
		if (t > 0.0)
		{
			// Compute the values for u and v.
			double u = bckRay.m_point1.GetElement(0) + (k.GetElement(0) * t);
			double v = bckRay.m_point1.GetElement(1) + (k.GetElement(1) * t);
			
			/* If the magnitude of both u and v is less than or equal to one
				then we must be in the plane. */
			if ((abs(u) < 1.0) && (abs(v) < 1.0))
			{
				// Compute the point of intersection.
				qbVector<double> poi = bckRay.m_point1 + t * k;
				
				// Transform the intersection point back into world coordinates.
				hitData.poi = m_transformMatrix.Apply(poi, qbRT::FWDTFORM);
				
				// Compute the local normal.
				//qbVector<double> localOrigin {std::vector<double> {0.0, 0.0, 0.0}};
				//qbVector<double> globalOrigin = m_transformMatrix.Apply(localOrigin, qbRT::FWDTFORM);
				//localNormal = m_transformMatrix.Apply(normalVector, qbRT::FWDTFORM) - globalOrigin;
				//localNormal.Normalize();
								
				qbVector<double> normalVector {std::vector<double> {0.0, 0.0, -1.0}};
				hitData.normal = m_transformMatrix.ApplyNorm(normalVector);
				hitData.normal.Normalize();
				
				// Return the base color.
				hitData.color = m_baseColor;
				
				// Store the (u,v) coordinates for possible later use.
				//m_uvCoords.SetElement(0, u);
				//m_uvCoords.SetElement(1, v);
				ComputeUV(poi, m_uvCoords);
				hitData.uvCoords = m_uvCoords;
				
				// Return a reference to this object.
				hitData.hitObject = std::make_shared<qbRT::ObjectBase> (*this);	
				
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	
	return false;
}

















