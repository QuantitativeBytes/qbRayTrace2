/* ***********************************************************
	objectbase.hpp
	
	The objectbase class definition - A base class from which
	all other object classes will inherit.
	
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

// objectbase.hpp

#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include <memory>
#include "../qbutils.hpp"
#include "../qbLinAlg/qbVector.h"
#include "../ray.hpp"
#include "../gtfm.hpp"

namespace qbRT
{
	/* Forward-declare the material base class. This will be
		overriden later. */
	class MaterialBase;
	
	// Define constants for UV mapping types.
	constexpr int uvSPHERE = 0;
	constexpr int uvPLANE = 1;
	constexpr int uvCYLINDER = 2;
	constexpr int uvBOX = 3;	

	class ObjectBase
	{
		public:
			// Constructor and destructor.
			ObjectBase();
			virtual ~ObjectBase();
			
			// Function to test for intersections.
			//virtual bool TestIntersection(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor);
			virtual bool TestIntersection(const Ray &castRay, qbRT::DATA::hitData &hitData);
			
			// Function to set the transform matrix.
			void SetTransformMatrix(const qbRT::GTform &transformMatrix);
			qbRT::GTform GetTransformMatrix();
			
			// Function to test whether two floating-point numbers are close to being equal.
			bool CloseEnough(const double f1, const double f2);
			
			// Function to assign a material.
			bool AssignMaterial(const std::shared_ptr<qbRT::MaterialBase> &objectMaterial);
			
			// Function to compute UV space.
			void ComputeUV(const qbVector<double> &localPOI, qbVector<double> &uvCoords);			
			
		// Public member variables.
		public:
			// The user-defined tag for this object.
			std::string m_tag;
		
			// The base colour of the object.
			qbVector<double> m_baseColor {3};
			
			// The geometric transform applied to the object.
			qbRT::GTform m_transformMatrix;
			
			// A reference to the material assigned to this object.
			std::shared_ptr<qbRT::MaterialBase> m_pMaterial;
			
			// A flag to indicate whether this object has a material or not.
			bool m_hasMaterial = false;
			
			// A flag to indicate whether this object is visible.
			bool m_isVisible = true;
			
			// Store the (u,v) coordinates from a detected intersection.
			qbVector<double> m_uvCoords {2};
			
			// Control what type of UV mapping to apply to this object.
			int m_uvMapType = qbRT::uvSPHERE;			
	};
}

#endif
