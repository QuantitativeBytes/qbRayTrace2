/* ***********************************************************
	normalbase.hpp
	
	The normalbase class definition - a simple base class for
	handling normal maps.
	
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

#ifndef NORMALBASE_H
#define NORMALBASE_H

#include <memory>
#include "../qbLinAlg/qbMatrix.h"
#include "../qbLinAlg/qbMatrix33.hpp"
#include "../qbLinAlg/qbVector.h"
#include "../qbLinAlg/qbVector2.hpp"
#include "../qbLinAlg/qbVector3.hpp"
#include "../qbLinAlg/qbVector4.hpp"
#include "../ray.hpp"
#include "../qbTextures/texturebase.hpp"

namespace qbRT
{
	namespace Normal
	{
		class NormalBase
		{
			public:
				// Constructor / destructor.
				NormalBase();
				virtual ~NormalBase();
				
				// Function to compute the perturbation.
				virtual qbVector3<double> ComputePerturbation(const qbVector3<double> &normal, const qbVector2<double> &uvCoords);
				
				// Function to perturb the given normal.
				qbVector3<double> PerturbNormal(const qbVector3<double> &normal, const qbVector3<double> &perturbation);
				
				// *** Function to perform numerical differentiation of a texture in UV space.
				qbVector2<double> TextureDiff(const std::shared_ptr<qbRT::Texture::TextureBase> &inputTexture, const qbVector2<double> &uvCoords);				
				
				// Function to set the amplitude scale.
				void SetAmplitude(double amplitude);
				
				// Function to set transform.
				void SetTransform(const qbVector2<double> &translation, const double &rotation, const qbVector2<double> &scale);				
				
				// Function to apply the local transform to the given input vector.
				qbVector2<double> ApplyTransform(const qbVector2<double> &inputVector);				
				
			public:
				// Store the amplitude scale factor.
				double m_amplitudeScale = 1.0;	
			
			private:
				// Initialise the transform matrix to the identity matrix.
				qbMatrix33<double> m_transformMatrix {std::vector<double>{1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0}};
				
		};
	}
}

#endif
