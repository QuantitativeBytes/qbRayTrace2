/* ***********************************************************
	cylinder.hpp
	
	The cylinder class definition - A class for creating 
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

#ifndef CYLINDER_H
#define CYLINDER_H

#include "objectbase.hpp"
#include "../gtfm.hpp"

namespace qbRT
{
	class Cylinder : public ObjectBase, public std::enable_shared_from_this<qbRT::Cylinder>
	{
		public:
			// Default constructor.
			Cylinder();
			
			// Override the destructor.
			virtual ~Cylinder() override;
			
			// Override the function to test for intersections.
			virtual bool TestIntersection(	const qbRT::Ray &castRay, qbRT::DATA::hitData &hitData) override;
	};
}

#endif
