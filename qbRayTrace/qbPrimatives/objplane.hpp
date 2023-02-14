/* ***********************************************************
	objectplane.hpp
	
	The ObjPlane class definition - A class derived from
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

// objplane.hpp

#ifndef OBJPLANE_H
#define OBJPLANE_H

#include "objectbase.hpp"
#include "../gtfm.hpp"

namespace qbRT
{
	class ObjPlane : public ObjectBase, public std::enable_shared_from_this<qbRT::ObjPlane>
	{
		public:
			// Default constructor.
			ObjPlane();
		
			// Override the destructor.
			virtual ~ObjPlane() override;
		
			// Override the function to test for intersections.
			virtual bool TestIntersection(	const qbRT::Ray &castRay, qbRT::DATA::hitData &hitData) override;
																			
		private:
		
		
	};
}

#endif
