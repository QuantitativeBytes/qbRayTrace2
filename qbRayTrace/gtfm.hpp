/* ***********************************************************
	gtfm.hpp
	
	The GTform class implementation - A class to handle geometric
	transforms.
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
	This code corresponds specifically to Episode 5 of the series,
	which may be found here:
	https://youtu.be/-Apu2BNp3t8
	
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

#ifndef GTFM_H
#define GTFM_H

#include "./qbLinAlg/qbVector.h"
#include "./qbLinAlg/qbVector2.hpp"
#include "./qbLinAlg/qbVector3.hpp"
#include "./qbLinAlg/qbVector4.hpp"
#include "./qbLinAlg/qbMatrix.h"
#include "./qbLinAlg/qbMatrix33.hpp"
#include "./qbLinAlg/qbMatrix44.hpp"
#include "ray.hpp"

namespace qbRT
{
	// Define direction flag values.
	constexpr bool FWDTFORM = true;
	constexpr bool BCKTFORM = false;
	
	class GTform
	{
		public:
			// Constructor & destructor.
			GTform();
			~GTform();
			
			// Construct from three vectors.
			GTform(const qbVector3<double> &translation, const qbVector3<double> &rotation, const qbVector3<double> &scale);
			
			// Construct from a pair of matrices.
			GTform(const qbMatrix44<double> &fwd, const qbMatrix44<double> &bck);
			
			// Function to set translation, rotation and scale components.
			void SetTransform(	const qbVector3<double> &translation,
													const qbVector3<double> &rotation,
													const qbVector3<double> &scale);
													
			void SetTransform(	const qbMatrix44<double> &fwd, const qbMatrix44<double> &bck);
													
			// Functions to return the transform matrices.
			qbMatrix44<double> GetForward();
			qbMatrix44<double> GetBackward();
			
			// Function to apply the transform.
			qbRT::Ray Apply(const qbRT::Ray &inputRay, bool dirFlag);
			qbVector3<double> Apply(const qbVector3<double> &inputVector, bool dirFlag);
			qbVector3<double> ApplyNorm(const qbVector3<double> &inputVector);
			
			// Function to return the normal transform matrix.
			qbMatrix33<double> GetNormalTransform();
			
			// Overload operators.
			friend GTform operator* (const qbRT::GTform &lhs, const qbRT::GTform &rhs);
			
			// Overload the assignment operator.
			GTform operator= (const GTform &rhs);
			
			// Function to print transform matrix to STDOUT.
			void PrintMatrix(bool dirFlag);
			
			// Function to allow printing of vectors.
			static void PrintVector(const qbVector3<double> &vector);
			
		private:
			void Print(const qbMatrix44<double> &matrix);
			void ExtractLinearTransform();
			
		private:
			qbMatrix44<double> m_fwdtfm;
			qbMatrix44<double> m_bcktfm;
			qbMatrix33<double> m_lintfm;
			//qbMatrix2<double> m_fwdtfm {4, 4};
			//qbMatrix2<double> m_bcktfm {4, 4};
			//qbMatrix2<double> m_lintfm {3, 3};
	};
}

#endif
