/* ***********************************************************
	objectsphere.hpp
	
	The objectsphere class definition - A class to implement
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

// objsphere.hpp

#ifndef OBJSPHERE_H
#define OBJSPHERE_H

#include "objectbase.hpp"
#include "box.hpp"
#include "../gtfm.hpp"

namespace qbRT
{
	class ObjSphere : public ObjectBase, public std::enable_shared_from_this<qbRT::ObjSphere>
	{
		public:
			/* The default constructor.
				Note that this will define a unit sphere at the origin. */
			ObjSphere();
			
			// Override the destructor.
			virtual ~ObjSphere() override;
			
			// Override the function to test for intersections.
			//virtual bool TestIntersection(const qbRT::Ray &castRay, qbVector3<double> &intPoint, qbVector3<double> &localNormal, qbVector3<double> &localColor) override;
			virtual bool TestIntersection(const qbRT::Ray &castRay, qbRT::DATA::hitData &hitData) override;
			
		private:
		
		
	};
}

#endif
