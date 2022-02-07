/* ***********************************************************
	sphere.hpp
	
	A class that implements a ray marched sphere shape.
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
	The whole series may be found on the QuantitativeBytes 
	YouTube channel at:
	www.youtube.com/c/QuantitativeBytes
	
	GPLv3 LICENSE
	
***********************************************************/

#ifndef RM_SPHERE_H
#define RM_SPHERE_H

#include "raymarchbase.hpp"

namespace qbRT
{
	namespace RM
	{
		class Sphere : public RayMarchBase
		{
			public:
				// Constructor.
				Sphere();
				
				// Destructor.
				virtual ~Sphere() override;
				
			private:
				// Private object function.
				double ObjectFcn(qbVector<double> *location, qbVector<double> *parms);
				
		};
	}
}

#endif
