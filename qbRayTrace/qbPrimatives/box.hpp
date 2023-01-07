/* ***********************************************************
	box.hpp
	
	The box class definition - A class to implement
	boxes. Inherits from objectbase.hpp
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
	The whole series may be found on the QuantitativeBytes 
	YouTube channel at:
	www.youtube.com/c/QuantitativeBytes
	
	GPLv3 LICENSE

	
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

#ifndef H_BOX
#define H_BOX

#include "objectbase.hpp"
#include "../gtfm.hpp"

namespace qbRT
{
	class Box : public ObjectBase, public std::enable_shared_from_this<qbRT::Box>
	{
		public:
			/* The default constructor.
				Note that this will define a unit sphere at the origin. */
			Box();
			
			// Override the destructor.
			virtual ~Box() override;
			
			// Override the function to test for intersections.
			virtual bool TestIntersection(const qbRT::Ray &castRay, qbRT::DATA::hitData &hitData) override;
			
			// Overloaded version of TestIntersection for the specific bounding box case.
			bool TestIntersection(const qbRT::Ray &castRay);
			
		private:
			// Moved these into the test intersection function as this is the only place they are used.
			//std::array<double, 6> t;
			//std::array<double, 6> u;
			//std::array<double, 6> v;
	};
}

#endif
