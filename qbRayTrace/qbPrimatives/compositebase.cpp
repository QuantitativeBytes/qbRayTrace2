/* ***********************************************************
	compositebase.cpp
	
	The compositbase class implementation.
	
	A class to allow multiple shapes to be combined together and
	treated as a single shape. Has no form of it's own and is
	therefore essentially an 'empty' object which can function
	as the parent of a list of other objects, with it's own
	geometric transform and bounding box.
	
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

#include "compositebase.hpp"

// Constructor.
qbRT::SHAPES::CompositeBase::CompositeBase()
{
	// Set default initial values for the limits.
	m_xLim = std::vector<double>{1e6, -1e6};
	m_yLim = std::vector<double>{1e6, -1e6};
	m_zLim = std::vector<double>{1e6, -1e6};
}

// Destructor.
qbRT::SHAPES::CompositeBase::~CompositeBase()
{

}

// Function to add a sub-shape.
void qbRT::SHAPES::CompositeBase::AddSubShape(std::shared_ptr<qbRT::ObjectBase> subShape)
{
	// Modify the extents of this shape to accomodate the new sub-shape.
	qbVector2<double> xLim;
	qbVector2<double> yLim;
	qbVector2<double> zLim;
	subShape -> GetExtents(xLim, yLim, zLim);
	if (xLim.GetElement(0) < m_xLim.GetElement(0))
		m_xLim.SetElement(0, xLim.GetElement(0));
	if (xLim.GetElement(1) > m_xLim.GetElement(1))
		m_xLim.SetElement(1, xLim.GetElement(1));
		
	if (yLim.GetElement(0) < m_yLim.GetElement(0))
		m_yLim.SetElement(0, yLim.GetElement(0));
	if (yLim.GetElement(1) > m_yLim.GetElement(1))
		m_yLim.SetElement(1, yLim.GetElement(1));
		
	if (zLim.GetElement(0) < m_zLim.GetElement(0))
		m_zLim.SetElement(0, zLim.GetElement(0));
	if (zLim.GetElement(1) > m_zLim.GetElement(1))
		m_zLim.SetElement(1, zLim.GetElement(1));
		
	// Modify the composite shape bounding box to fit the new extents.
	// Determine the size;
	double xSize = m_xLim.GetElement(1) - m_xLim.GetElement(0);
	double ySize = m_yLim.GetElement(1) - m_yLim.GetElement(0);
	double zSize = m_zLim.GetElement(1) - m_zLim.GetElement(0);		
	
	// Determine centre points.
	double xCentre = m_xLim.GetElement(0) + (xSize / 2.0);
	double yCentre = m_yLim.GetElement(0) + (ySize / 2.0);
	double zCentre = m_zLim.GetElement(0) + (zSize / 2.0);
	
	// Update the transform matrix.
	m_boundingBoxTransform.SetTransform(	qbVector3<double>{std::vector<double>{xCentre, yCentre, zCentre}},
																				qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}},
																				qbVector3<double>{std::vector<double>{xSize/2.0, ySize/2.0, zSize/2.0}});
																				
	// And modify the bounding box.
	m_boundingBox.SetTransformMatrix(m_boundingBoxTransform);

	// Add the sub-shape to the list of sub-shapes.
	m_shapeList.push_back(subShape);
}

// Function to update the bounds.
void qbRT::SHAPES::CompositeBase::UpdateBounds()
{
	// Set default initial values for the limits.
	m_xLim = std::vector<double>{1e6, -1e6};
	m_yLim = std::vector<double>{1e6, -1e6};
	m_zLim = std::vector<double>{1e6, -1e6};
	
	qbVector2<double> xLim;
	qbVector2<double> yLim;
	qbVector2<double> zLim;
	for (auto shape : m_shapeList)
	{
		shape -> GetExtents(xLim, yLim, zLim);
		if (xLim.GetElement(0) < m_xLim.GetElement(0))
			m_xLim.SetElement(0, xLim.GetElement(0));
		if (xLim.GetElement(1) > m_xLim.GetElement(1))
			m_xLim.SetElement(1, xLim.GetElement(1));
			
		if (yLim.GetElement(0) < m_yLim.GetElement(0))
			m_yLim.SetElement(0, yLim.GetElement(0));
		if (yLim.GetElement(1) > m_yLim.GetElement(1))
			m_yLim.SetElement(1, yLim.GetElement(1));
			
		if (zLim.GetElement(0) < m_zLim.GetElement(0))
			m_zLim.SetElement(0, zLim.GetElement(0));
		if (zLim.GetElement(1) > m_zLim.GetElement(1))
			m_zLim.SetElement(1, zLim.GetElement(1));
	}
	
	// Modify the composite shape bounding box to fit the new extents.
	// Determine the size;
	double xSize = m_xLim.GetElement(1) - m_xLim.GetElement(0);
	double ySize = m_yLim.GetElement(1) - m_yLim.GetElement(0);
	double zSize = m_zLim.GetElement(1) - m_zLim.GetElement(0);		
	
	// Determine centre points.
	double xCentre = m_xLim.GetElement(0) + (xSize / 2.0);
	double yCentre = m_yLim.GetElement(0) + (ySize / 2.0);
	double zCentre = m_zLim.GetElement(0) + (zSize / 2.0);
	
	// Update the transform matrix.
	m_boundingBoxTransform.SetTransform(	qbVector3<double>{std::vector<double>{xCentre, yCentre, zCentre}},
																				qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}},
																				qbVector3<double>{std::vector<double>{xSize/2.0, ySize/2.0, zSize/2.0}});
																				
	// And modify the bounding box.
	m_boundingBox.SetTransformMatrix(m_boundingBoxTransform);	
	
}

// Override the function to return the extents.
void qbRT::SHAPES::CompositeBase::GetExtents(qbVector2<double> &xLim, qbVector2<double> &yLim, qbVector2<double> &zLim)
{
	// Construct corners of a cube based on the current limits.
	std::vector<qbVector3<double>> cornerPoints = ConstructCube(	m_xLim.GetElement(0), m_xLim.GetElement(1), 
																															m_yLim.GetElement(0), m_yLim.GetElement(1), 
																															m_zLim.GetElement(0), m_zLim.GetElement(1));
	
	// Apply the transforms to the unit cube corner points and compute limits.
	double minX = 1e6;
	double minY = 1e6;
	double minZ = 1e6;
	double maxX = -1e6;
	double maxY = -1e6;
	double maxZ = -1e6;
	for (int i=0; i<8; ++i)
	{
		cornerPoints.at(i) = m_transformMatrix.Apply(cornerPoints.at(i), qbRT::FWDTFORM);
		
		if (cornerPoints.at(i).GetElement(0) < minX)
			minX = cornerPoints.at(i).GetElement(0);
		if (cornerPoints.at(i).GetElement(0) > maxX)
			maxX = cornerPoints.at(i).GetElement(0);
			
		if (cornerPoints.at(i).GetElement(1) < minY)
			minY = cornerPoints.at(i).GetElement(1);
		if (cornerPoints.at(i).GetElement(1) > maxY)
			maxY = cornerPoints.at(i).GetElement(1);
			
		if (cornerPoints.at(i).GetElement(2) < minZ)
			minZ = cornerPoints.at(i).GetElement(2);
		if (cornerPoints.at(i).GetElement(2) > maxZ)
			maxZ = cornerPoints.at(i).GetElement(2);					
	}
	
	// Return the limits.
	xLim.SetElement(0, minX);
	xLim.SetElement(1, maxX);
	yLim.SetElement(0, minY);
	yLim.SetElement(1, maxY);
	zLim.SetElement(0, minZ);
	zLim.SetElement(1, maxZ);	
}

// Test for intersections.
bool qbRT::SHAPES::CompositeBase::TestIntersection(	const qbRT::Ray &castRay, qbRT::DATA::hitData &hitData)
{
	// Check if the object is visible.
	if (!m_isVisible)
		return false;
		
	// Copy the ray and apply the backwards transform.
	qbRT::Ray bckRay = m_transformMatrix.Apply(castRay, qbRT::BCKTFORM);
	
	// Check for intersection with the bounding box.
	if (!m_useBoundingBox || m_boundingBox.TestIntersection(bckRay))
	{
		// We intersected with the bounding box, so check everything else.
		qbVector3<double> worldIntPoint;
		double currentDist = 100e6;
		qbRT::DATA::hitData tempHitData;
		int validShapeIndex = TestIntersections(castRay, bckRay, worldIntPoint, currentDist, tempHitData);
		if (validShapeIndex > -1)
		{
			// An intersection with an internal sub-shape.
			qbVector3<double> newNormal = m_transformMatrix.ApplyNorm(tempHitData.normal);
			newNormal.Normalize();
			tempHitData.hitObject -> ComputeUV(tempHitData.localPOI, hitData.uvCoords);
			//m_uvCoords = hitData.uvCoords;
			
			
			// Return these values.
			hitData.poi = worldIntPoint;
			hitData.normal = newNormal;
			hitData.color = tempHitData.color;
			hitData.localPOI = tempHitData.localPOI;
			hitData.hitObject = tempHitData.hitObject;
			
			return true;
		}
		else
		{
			// No intersections with internal sub-shapes.
			return false;
		}
	}
	else
	{
		// No intersection with the bounding box.
		return false;
	}
	
	return false;
}

// Test for intersections with the sub-object list.
int qbRT::SHAPES::CompositeBase::TestIntersections(	const qbRT::Ray &castRay,
																										const qbRT::Ray &bckRay,
																										qbVector3<double> &worldIntPoint,
																										double &currentDist,
																										qbRT::DATA::hitData &tempHitData	)
{
	// Test for intersections with the sub-shapes.
	int numShapes = m_shapeList.size();
	int validShapeIndex = -1;
	qbRT::DATA::hitData hitData;
	for (int i=0; i<numShapes; ++i)
	{
		if (m_shapeList.at(i) -> m_isVisible)
		{
			bool shapeTest = m_shapeList.at(i) -> TestIntersection(bckRay, hitData);
			if (shapeTest)
			{
				// Transform the intersection point back into world coordinates.
				qbVector3<double> intPoint = m_transformMatrix.Apply(hitData.poi, qbRT::FWDTFORM);
				
				// Compute the distance.
				double dist = (intPoint - castRay.m_point1).norm();
				
				// If closest, then this is the shape to use.
				if (dist < currentDist)
				{
					currentDist = dist;
					validShapeIndex = i;
					worldIntPoint = intPoint;
					tempHitData = hitData;
				}
			}
		}
	}
	
	return validShapeIndex;
}
