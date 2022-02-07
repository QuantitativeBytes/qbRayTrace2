/* ***********************************************************
	cube.hpp
	
	A class that implements a ray marched cube shape.
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
	The whole series may be found on the QuantitativeBytes 
	YouTube channel at:
	www.youtube.com/c/QuantitativeBytes
	
	GPLv3 LICENSE
	
***********************************************************/

#ifndef RM_CUBE
#define RM_CUBE

#include "raymarchbase.hpp"

namespace qbRT
{
	namespace RM
	{
		class Cube : public RayMarchBase
		{
			public:
				// Constructor.
				Cube();
				
				// Destructor.
				virtual ~Cube() override;
				
			private:
				// Private object function.
				double ObjectFcn(qbVector<double> *location, qbVector<double> *parms);				
		};
	}
}

#endif
