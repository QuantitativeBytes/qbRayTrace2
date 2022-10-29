/* ***********************************************************
	objectsphere.cpp
	
	The objectsphere class implementation - A class to implement
	spheres. Inherits from objectbase.hpp
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
	This code corresponds specifically to Episode 2 of the series,
	which may be found here:
	https://youtu.be/8fWZM8hCX5E
	
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

// objsphere.cpp

#include "objsphere.hpp"
#include <cmath>

// The default constructor.
qbRT::ObjSphere::ObjSphere()
{

}

// The destructor.
qbRT::ObjSphere::~ObjSphere()
{

}

// Function to test for intersections.
bool qbRT::ObjSphere::TestIntersection(const qbRT::Ray &castRay, qbRT::DATA::hitData &hitData)
{
	if (!m_isVisible)
		return false;

	// Copy the ray and apply the backwards transform.
	qbRT::Ray bckRay = m_transformMatrix.Apply(castRay, qbRT::BCKTFORM);

	// Compute the values of a, b and c.
	qbVector<double> vhat = bckRay.m_lab;
	vhat.Normalize();
	
	/* Note that a is equal to the squared magnitude of the
		direction of the cast ray. As this will be a unit vector,
		we can conclude that the value of 'a' will always be 1. */
	// a = 1.0;
	
	// Calculate b.
	double b = 2.0 * qbVector<double>::dot(bckRay.m_point1, vhat);
	
	// Calculate c.
	double c = qbVector<double>::dot(bckRay.m_point1, bckRay.m_point1) - 1.0;
	
	// Test whether we actually have an intersection.
	double intTest = (b*b) - 4.0 * c;
	
	qbVector<double> poi;
	if (intTest > 0.0)
	{
		double numSQRT = sqrtf(intTest);
		double t1 = (-b + numSQRT) / 2.0;
		double t2 = (-b - numSQRT) / 2.0;
		
		//std::cout << "**** SPHERE t1, t2 = " << t1 << ", " << t2 << " ****" << std::endl;
		
		/* If either t1 or t2 are negative, then at least part of the object is
			behind the camera and so we will ignore it. */
		if ((t1 < 0.0) && (t2 < 0.0))
		{
			return false;
		}
		else
		{
			// Determine which point of intersection was closest to the camera.
			if (t1 < t2)
			{
				if (t1 > 0.0)
				{
					poi = bckRay.m_point1 + (vhat * t1);
				}
				else
				{
					if (t2 > 0.0)
					{
						poi = bckRay.m_point1 + (vhat * t2);
					}
					else
					{
						return false;
					}
				}
			}
			else
			{
				if (t2 > 0.0)
				{
					poi = bckRay.m_point1 + (vhat * t2);
				}
				else
				{
					if (t1 > 0.0)
					{
						poi = bckRay.m_point1 + (vhat * t1);
					}
					else
					{
						return false;
					}
				}
			}
			
			// Transform the intersection point back into world coordinates.
			//intPoint = m_transformMatrix.Apply(poi, qbRT::FWDTFORM);
			hitData.poi = m_transformMatrix.Apply(poi, qbRT::FWDTFORM);
			
			// Compute the local normal (easy for a sphere at the origin!).
			
			//qbVector<double> objOrigin = qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}};
			//qbVector<double> newObjOrigin = m_transformMatrix.Apply(objOrigin, qbRT::FWDTFORM);
			//localNormal = intPoint - newObjOrigin;
			//localNormal.Normalize();

			qbVector<double> normalVector = poi;
			//localNormal = m_transformMatrix.ApplyNorm(normalVector);
			//localNormal.Normalize();
			hitData.normal = m_transformMatrix.ApplyNorm(normalVector);
			hitData.normal.Normalize();

			
			// Return the base color.
			//localColor = m_baseColor;
			hitData.color = m_baseColor;
			
			// Compute and store (u,v) coordinates for possible later use.
			double x = poi.GetElement(0);
			double y = poi.GetElement(1);
			double z = poi.GetElement(2);
			double u = atan2(sqrtf(pow(x, 2.0) + pow(y, 2.0)), z);
			double v = atan2(y, x);
			
			//double u = atan(sqrtf(pow(x, 2.0) + pow(y, 2.0)) / z);
			//double v = atan(y/x);
			//if (x < 0)
			//	v += M_PI;
				
			//u /= M_PI;
			//v /= M_PI;
			
			//m_uvCoords.SetElement(0, u);
			//m_uvCoords.SetElement(1, v);
			
			// ***
			ComputeUV(poi, m_uvCoords);
			hitData.uvCoords = m_uvCoords;
			
			// Return a reference to this object.
			hitData.hitObject = std::make_shared<qbRT::ObjectBase> (*this);	
			// ***
			
		}
		
		return true;
	}
	else
	{
		return false;
	}
	
}

























