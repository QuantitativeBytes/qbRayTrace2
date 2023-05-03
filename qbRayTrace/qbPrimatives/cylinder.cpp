/* ***********************************************************
	cylinder.cpp
	
	The cylinder class implementation - A class for creating 
	cylinder primitive shapes.
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
	This code corresponds specifically to Episode 6 of the series,
	which may be found here:
	https://youtu.be/UTz7ytMJ2yk
	
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

#include "cylinder.hpp"
#include <cmath>

// The default constructor.
qbRT::Cylinder::Cylinder()
{
	// Define the default uv mapping.
	m_uvMapType = qbRT::uvCYLINDER;
	
	// Construct the default bounding box.
	m_boundingBoxTransform.SetTransform(	qbVector3<double>{0.0, 0.0, 0.0},
																				qbVector3<double>{0.0, 0.0, 0.0},
																				qbVector3<double>{1.0, 1.0, 1.0});
}

// The destructor.
qbRT::Cylinder::~Cylinder()
{

}

// The function to test for intersections.
bool qbRT::Cylinder::TestIntersection(	const qbRT::Ray &castRay, qbRT::DATA::hitData &hitData)
{
	if (!m_isVisible)
		return false;
		
	// Copy the ray and apply the backwards transform.
	qbRT::Ray bckRay = m_transformMatrix.Apply(castRay, qbRT::BCKTFORM);
	
	// Copy the m_lab vector from bckRay and normalize it.
	qbVector3<double> v = bckRay.m_lab;
	v.Normalize();
	
	// Compute a, b and c.
	double a = (v.m_x * v.m_x) + (v.m_y * v.m_y);
	double b = 2.0 * (bckRay.m_point1.m_x * v.m_x + bckRay.m_point1.m_y * v.m_y);
	double c = ((bckRay.m_point1.m_x * bckRay.m_point1.m_x) + (bckRay.m_point1.m_y * bckRay.m_point1.m_y)) - 1.0;
	
	// Compute b^2 - 4ac.
	double numSQRT = sqrt((b*b) - 4.0 * a * c);
	
	// Test for intersections.
	// First with the cylinder itself.
	std::array<qbVector3<double>, 4> poi;
	std::array<double, 4> t;
	bool t1Valid, t2Valid, t3Valid, t4Valid;
	if (numSQRT > 0.0)
	{
		// There was an intersection.
		// Compute the values for t.
		t.at(0) = (-b + numSQRT) / (2 * a);
		t.at(1) = (-b - numSQRT) / (2 * a);
		
		// Compute the points of intersection.
		poi.at(0) = bckRay.m_point1 + (v * t[0]);
		poi.at(1) = bckRay.m_point1 + (v * t[1]);
		
		// Check if any of these are valid.
		if ((t.at(0) > 0.0) && (fabs(poi.at(0).GetElement(2)) < 1.0))
		{
			t1Valid = true;
		}
		else
		{
			t1Valid = false;
			t.at(0) = 100e6;
		}
		
		if ((t.at(1) > 0.0) && (fabs(poi.at(1).GetElement(2)) < 1.0))
		{
			t2Valid = true;
		}
		else
		{
			t2Valid = false;
			t.at(1) = 100e6;
		}
	}
	else
	{
		t1Valid = false;
		t2Valid = false;
		t.at(0) = 100e6;
		t.at(1) = 100e6;
	}
	
	// And test the end caps.
	if (CloseEnough(v.GetElement(2), 0.0))
	{
		t3Valid = false;
		t4Valid = false;
		t.at(2) = 100e6;
		t.at(3) = 100e6;
	}
	else
	{
		// Compute the values of t.
		t.at(2) = (bckRay.m_point1.GetElement(2) - 1.0) / -v.GetElement(2);
		t.at(3) = (bckRay.m_point1.GetElement(2) + 1.0) / -v.GetElement(2);
		
		// Compute the points of intersection.
		poi.at(2) = bckRay.m_point1 + t.at(2) * v;
		poi.at(3) = bckRay.m_point1 + t.at(3) * v;
		
		// Check if these are valid.
		if ((t.at(2) > 0.0) && (sqrtf(std::pow(poi.at(2).GetElement(0), 2.0) + std::pow(poi.at(2).GetElement(1), 2.0)) < 1.0))
		{
			t3Valid = true;
		}
		else
		{
			t3Valid = false;
			t.at(2) = 100e6;
		}
		
		if ((t.at(3) > 0.0) && (sqrtf(std::pow(poi.at(3).GetElement(0), 2.0) + std::pow(poi.at(3).GetElement(1), 2.0)) < 1.0))
		{
			t4Valid = true;
		}
		else
		{
			t4Valid = false;
			t.at(3) = 100e6;
		}
	}
	
	// If no valid intersections found, the we can stop.
	if ((!t1Valid) && (!t2Valid) && (!t3Valid) && (!t4Valid))
		return false;
		
	// Check for the smallest valid value of t.
	int minIndex = 0;
	double minValue = 10e6;
	for (int i=0; i<4; ++i)
	{
		if (t.at(i) < minValue)
		{
			minValue = t.at(i);
			minIndex = i;
		}
	}
	
	/* If minIndex is either 0 or 1, then we have a valid intersection
		with the cylinder itself. */
	qbVector3<double> validPOI = poi.at(minIndex);
	if (minIndex < 2)
	{
		// Transform the intersection point back into world coordinates.
		hitData.poi = m_transformMatrix.Apply(validPOI, qbRT::FWDTFORM);
		
		// Compute the local normal.
		qbVector3<double> orgNormal;
		orgNormal.SetElement(0, validPOI.m_x);
		orgNormal.SetElement(1, validPOI.m_y);
		orgNormal.SetElement(2, 0.0);
		hitData.normal = m_transformMatrix.ApplyNorm(orgNormal);
		hitData.normal.Normalize();

		// Return the base color.
		hitData.color = m_baseColor;
		
		// Return the local POI.
		hitData.localPOI = validPOI;
		
		// Compute the (u,v) coordinates.
		ComputeUV(validPOI, hitData.uvCoords);
		//hitData.uvCoords = m_uvCoords;
		
		// Return a reference to this object.
		hitData.hitObject = this -> shared_from_this();
		
		return true;
	}
	else
	{
		// Otherwise check the end caps.
		if (!CloseEnough(v.GetElement(2), 0.0))
		{
			// Check if we are inside the disk.
			if (sqrtf(std::pow(validPOI.GetElement(0), 2.0) + std::pow(validPOI.GetElement(1), 2.0)) < 1.0)
			{
				// Transform the intersection point back into world coordinates.
				hitData.poi = m_transformMatrix.Apply(validPOI, qbRT::FWDTFORM);
				
				qbVector3<double> normalVector {0.0, 0.0, validPOI.m_z};
				hitData.normal = m_transformMatrix.ApplyNorm(normalVector);
				hitData.normal.Normalize();
				
				// Return the base color.
				hitData.color = m_baseColor;
				
				// Return the local POI.
				hitData.localPOI = validPOI;
				
				// Compute the UV coordinates
				ComputeUV(validPOI, hitData.uvCoords);
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

























