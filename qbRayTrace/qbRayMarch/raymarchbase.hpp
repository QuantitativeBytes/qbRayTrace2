/* ***********************************************************
	raymarchbase.hpp
	
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

#ifndef RAYMARCHBASE_H
#define RAYMARCHBASE_H

#include <functional>
#include "sdfunc.hpp"
#include "../qbPrimatives/objectbase.hpp"
#include "../qbPrimatives/box.hpp"
#include "../qbLinAlg/qbVector2.hpp"
#include "../qbLinAlg/qbVector3.hpp"
#include "../qbLinAlg/qbVector4.hpp"

namespace qbRT
{
	namespace RM
	{
		class RayMarchBase : public ObjectBase, public std::enable_shared_from_this<qbRT::RM::RayMarchBase>
		{
			public:
				// Default constructor.
				RayMarchBase();
				
				// Destructor.
				virtual ~RayMarchBase() override;
				
				// Override the function to test for intersections.
				virtual bool TestIntersection(	const qbRT::Ray &castRay, qbRT::DATA::hitData &hitData) override;
				
				// Function to set the object function.
				void SetObjectFcn( std::function<double(qbVector3<double>*, qbVector3<double>*)> objectFcn);
				
				// Function to evaluate the Signed Distance Function (SDF) at the given coordinates.
				double EvaluateSDF(	qbVector3<double> *location, qbVector3<double> *parms );
												
			public:
				// Bounding box.
				qbRT::Box m_boundingBox = qbRT::Box();
				
				// Parameters.
				qbVector3<double> m_parms {3};
				
			private:
				// Pointer to object function.
				std::function<double(qbVector3<double> *, qbVector3<double> *)> m_objectFcn;			
			
				bool m_haveObjectFcn = false;
				double m_epsilon;
				int m_maxSteps;
				
				const double m_h = 0.001;
				qbVector3<double> m_xDisp {m_h, 0.0, 0.0};
				qbVector3<double> m_yDisp {0.0, m_h, 0.0};
				qbVector3<double> m_zDisp {0.0, 0.0, m_h};
																						
		};
	}
}

#endif
