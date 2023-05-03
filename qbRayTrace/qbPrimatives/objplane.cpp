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

// objplane.cpp

#include "objplane.hpp"
#include "../qbutils.hpp"
#include <cmath>

// The default constructor.
qbRT::ObjPlane::ObjPlane()
{
	// Define the default uv mapping.
	m_uvMapType = qbRT::uvPLANE;
	
	// Construct the default bounding box.
	m_boundingBoxTransform.SetTransform(	qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}},
																				qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}},
																				qbVector3<double>{std::vector<double>{1.0, 1.0, 0.01}});
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
	
	/* Check if there is an intersection, ie. if the castRay is not parallel
		to the plane. */
	if (!CloseEnough(bckRay.m_lab.GetElement(2), 0.0))
	{
		// There is an intersection.
		double t = bckRay.m_point1.GetElement(2) / -bckRay.m_lab.GetElement(2);
		
		/* If t is negative, then the intersection point must be behind
			the camera and we can ignore it. */
		if (t > 0.0)
		{
			// Compute the values for u and v.
			double u = bckRay.m_point1.GetElement(0) + (bckRay.m_lab.GetElement(0) * t);
			double v = bckRay.m_point1.GetElement(1) + (bckRay.m_lab.GetElement(1) * t);
			
			/* If the magnitude of both u and v is less than or equal to one
				then we must be in the plane. */
			if ((abs(u) < 1.0) && (abs(v) < 1.0))
			{
				// Compute the point of intersection.
				qbVector3<double> poi = bckRay.m_point1 + t * bckRay.m_lab;
				
				// Transform the intersection point back into world coordinates.
				hitData.poi = m_transformMatrix.Apply(poi, qbRT::FWDTFORM);
								
				qbVector3<double> normalVector {0.0, 0.0, -1.0};
				hitData.normal = m_transformMatrix.ApplyNorm(normalVector);
				hitData.normal.Normalize();
				
				// Return the base color.
				hitData.color = m_baseColor;
				
				// Return the local point of intersection.
				hitData.localPOI = poi;				
				
				// Compute the UV coordinates.
				//m_uvCoords.SetElement(0, u);
				//m_uvCoords.SetElement(1, v);
				ComputeUV(poi, hitData.uvCoords);
				//hitData.uvCoords = m_uvCoords;
				
				// Return a reference to this object.
				hitData.hitObject = this -> shared_from_this();
				
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

















