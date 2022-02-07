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
	
***********************************************************/

#ifndef H_BOX
#define H_BOX

#include "objectbase.hpp"
#include "../gtfm.hpp"

namespace qbRT
{
	class Box : public ObjectBase
	{
		public:
			/* The default constructor.
				Note that this will define a unit sphere at the origin. */
			Box();
			
			// Override the destructor.
			virtual ~Box() override;
			
			// Override the function to test for intersections.
			virtual bool TestIntersection(const qbRT::Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor) override;
			
		private:
			std::array<double, 6> t;
			std::array<double, 6> u;
			std::array<double, 6> v;
	};
}

#endif
