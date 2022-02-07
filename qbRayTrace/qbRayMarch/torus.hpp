/* ***********************************************************
	torus.hpp
	
	A class that implements a ray marched torus shape.
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
	The whole series may be found on the QuantitativeBytes 
	YouTube channel at:
	www.youtube.com/c/QuantitativeBytes
	
	GPLv3 LICENSE
	
***********************************************************/

#ifndef RM_TORUS_H
#define RM_TORUS_H

#include "raymarchbase.hpp"

namespace qbRT
{
	namespace RM
	{
		class Torus : public RayMarchBase
		{
			public:
				// Constructor.
				Torus();
				
				// Destructor.
				virtual ~Torus() override;
				
				// Function to set the radii.
				void SetRadii(double r1, double r2);
				
			private:
				// Private object function.
				double ObjectFcn(qbVector<double> *location, qbVector<double> *parms);
				
				// Function to update the bounding box.
				void UpdateBounds();
				
			private:
				// Radii.
				double m_r1 = 1.0;
				double m_r2 = 0.25;
		
		};
	}
}

#endif
