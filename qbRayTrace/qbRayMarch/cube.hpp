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
				double ObjectFcn(qbVector3<double> *location, qbVector3<double> *parms);				
		};
	}
}

#endif
