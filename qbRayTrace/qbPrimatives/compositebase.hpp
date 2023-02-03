/* ***********************************************************
	compositebase.hpp
	
	The compositbase class definition
	
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

#ifndef COMPOSITEBASE_H
#define COMPOSITEBASE_H

#include "../qbPrimatives/objectbase.hpp"
#include "../qbPrimatives/box.hpp"

namespace qbRT
{
	namespace SHAPES
	{
		class CompositeBase : public ObjectBase
		{
			public:
				// Default constructor.
				CompositeBase();
				
				// The destructor.
				virtual ~CompositeBase() override;
				
				// Function to add a sub-shape.
				void AddSubShape(std::shared_ptr<qbRT::ObjectBase> subShape);
				
				// Override the GetExtents function.
				virtual void GetExtents(qbVector2<double> &xLim, qbVector2<double> &yLim, qbVector2<double> &zLim) override;
				
				// Override the function to test for intersections.
				virtual bool TestIntersection(const qbRT::Ray &castRay, qbRT::DATA::hitData &hitData) override;
																
				// Function to update the bounds after sub-shapes have been modified.
				void UpdateBounds();
				
			private:
				// Test for intersections with the list of sub-objects.
				int TestIntersections(	const qbRT::Ray &castRay,
																const qbRT::Ray &bckRay,
																qbVector3<double> &intPoint,
																double &currentDist,
																qbRT::DATA::hitData &hitData	);			
																
			public:
				// Bounding box.
				qbRT::Box m_boundingBox = qbRT::Box();
				bool m_useBoundingBox = true;
			
				// List of sub-objects.
				std::vector<std::shared_ptr<qbRT::ObjectBase>> m_shapeList;

				// Object limits.
				qbVector2<double> m_xLim;
				qbVector2<double> m_yLim;
				qbVector2<double> m_zLim;
				
		};
	}
}

#endif
