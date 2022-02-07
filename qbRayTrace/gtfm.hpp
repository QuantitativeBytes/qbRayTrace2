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
	
***********************************************************/

#ifndef GTFM_H
#define GTFM_H

#include "./qbLinAlg/qbVector.h"
#include "./qbLinAlg/qbMatrix.h"
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
			GTform(const qbVector<double> &translation, const qbVector<double> &rotation, const qbVector<double> &scale);
			
			// Construct from a pair of matrices.
			GTform(const qbMatrix2<double> &fwd, const qbMatrix2<double> &bck);
			
			// Function to set translation, rotation and scale components.
			void SetTransform(	const qbVector<double> &translation,
													const qbVector<double> &rotation,
													const qbVector<double> &scale);
													
			void SetTransform(	const qbMatrix2<double> &fwd, const qbMatrix2<double> &bck);
													
			// Functions to return the transform matrices.
			qbMatrix2<double> GetForward();
			qbMatrix2<double> GetBackward();
			
			// Function to apply the transform.
			qbRT::Ray Apply(const qbRT::Ray &inputRay, bool dirFlag);
			qbVector<double> Apply(const qbVector<double> &inputVector, bool dirFlag);
			qbVector<double> ApplyNorm(const qbVector<double> &inputVector);
			
			// Function to return the normal transform matrix.
			qbMatrix2<double> GetNormalTransform();
			
			// Overload operators.
			friend GTform operator* (const qbRT::GTform &lhs, const qbRT::GTform &rhs);
			
			// Overload the assignment operator.
			GTform operator= (const GTform &rhs);
			
			// Function to print transform matrix to STDOUT.
			void PrintMatrix(bool dirFlag);
			
			// Function to allow printing of vectors.
			static void PrintVector(const qbVector<double> &vector);
			
		private:
			void Print(const qbMatrix2<double> &matrix);
			void ExtractLinearTransform();
			
		private:
			qbMatrix2<double> m_fwdtfm {4, 4};
			qbMatrix2<double> m_bcktfm {4, 4};
			qbMatrix2<double> m_lintfm {3, 3};
	};
}

#endif
