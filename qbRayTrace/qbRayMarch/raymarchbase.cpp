/* ***********************************************************
	raymarchbase.cpp
	
	The base class for implementation of ray marching
	methods.
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
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

#include "raymarchbase.hpp"
#include "../qbutils.hpp"

// Constructor.
qbRT::RM::RayMarchBase::RayMarchBase()
{
	// Define the tolerance.
	m_epsilon = 1e-12;
	
	// Define the maximum number of steps allowed.
	m_maxSteps = 100;
}

// Destructor.
qbRT::RM::RayMarchBase::~RayMarchBase()
{

}

// Test for intersections.
bool qbRT::RM::RayMarchBase::TestIntersection(	const qbRT::Ray &castRay, qbRT::DATA::hitData &hitData	)
{
	// Check if an object function has been defined.
	if (m_haveObjectFcn)
	{
		// Check if the object is visible.
		if (!m_isVisible)
			return false;
			
		// Copy the ray and apply the backwards transform.
		qbRT::Ray bckRay = m_transformMatrix.Apply(castRay, qbRT::BCKTFORM);
		
		// Test for intersections with the bounding box.
		if (m_boundingBox.TestIntersection(bckRay))
		{
			// Extract ray direction.
			qbVector3<double> vhat = bckRay.m_lab;
			vhat.Normalize();		
		
			qbVector3<double> currentLoc = bckRay.m_point1;
			int stepCount = 0;
			double dist = EvaluateSDF(&currentLoc, &m_parms);
			
			// Main loop
			while ((dist > m_epsilon) && (stepCount < m_maxSteps))
			{
				currentLoc = currentLoc + (vhat * dist);
				
				dist = EvaluateSDF(&currentLoc, &m_parms);
				if (dist > 1e6)
				{
					stepCount = m_maxSteps;
					break;
				}
				
				stepCount++;
			}
			
			// If m_maxSteps exceeded, then no valid intersection found.
			if (stepCount == m_maxSteps)
			{
				return false;
			}
		
			// Otherwise, we have a valid intersection at currentLoc.
			// Transform the intersection point back into world coordinates.
			hitData.poi = m_transformMatrix.Apply(currentLoc, qbRT::FWDTFORM);
			
			// Compute the local normal.
			qbVector3<double> surfaceNormal;

			/*
			 Note the extra code here to compute an offset location from which
			to compute the normal. The reason to do this is that in some cases,
			especially with more complex distance functions, the point of intersection
			can be computed as being very slightly inside the surface. This would
			obviously result in a normal vector pointing in the wrong direction.
			By tracing back along the intersecting ray a short distance and then using
			that location instead, we can avoid this problem.
			*/

			// Determine an offset point.
			qbVector3<double> normalLoc = currentLoc - (vhat * 0.01);

			qbVector3<double> x1 = normalLoc - m_xDisp;
			qbVector3<double> x2 = normalLoc + m_xDisp;
			qbVector3<double> y1 = normalLoc - m_yDisp;
			qbVector3<double> y2 = normalLoc + m_yDisp;
			qbVector3<double> z1 = normalLoc - m_zDisp;
			qbVector3<double> z2 = normalLoc + m_zDisp;
			surfaceNormal.SetElement(0, EvaluateSDF(&x2, &m_parms) - EvaluateSDF(&x1, &m_parms));
			surfaceNormal.SetElement(1, EvaluateSDF(&y2, &m_parms) - EvaluateSDF(&y1, &m_parms));
			surfaceNormal.SetElement(2, EvaluateSDF(&z2, &m_parms) - EvaluateSDF(&z1, &m_parms));
		
			// Transform the local normal.
			surfaceNormal.Normalize();
			hitData.normal = m_transformMatrix.ApplyNorm(surfaceNormal);
			
			// Return the base color.
			hitData.color = m_baseColor;
			
			// Return a pointer to this object.
			//hitData.hitObject = std::make_shared<qbRT::ObjectBase> (*this);			
			hitData.hitObject = this -> shared_from_this();
			
			// Return the local point of intersection.
			hitData.localPOI = currentLoc;			
			
			// Compute UV.		
			ComputeUV(currentLoc, m_uvCoords);
			hitData.uvCoords = m_uvCoords;				
		
			return true;
		}
	
	}
	
	return false;
}

// Function to set the object function.
void qbRT::RM::RayMarchBase::SetObjectFcn( std::function<double(qbVector3<double>*, qbVector3<double>*)> objectFcn )
{
	m_objectFcn = objectFcn;
	m_haveObjectFcn = true;
}

// Function to evaluate the Signed Distance Function (SDF) at the given coordinates.
double qbRT::RM::RayMarchBase::EvaluateSDF(	qbVector3<double> *location, qbVector3<double> *parms )
{
	return m_objectFcn(location, parms);
}
