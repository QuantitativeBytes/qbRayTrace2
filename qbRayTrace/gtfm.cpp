/* ***********************************************************
	gtfm.cpp
	
	The GTform class definition - A class to handle geometric
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
	Copyright (c) 2021 Michael Bennett
	
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

#include "gtfm.hpp"
#include "qbutils.hpp"

// Constructor / destructor.
qbRT::GTform::GTform()
{
	/* Set forward and backward transforms to
		identity matrices. */
	m_fwdtfm.SetToIdentity();
	m_bcktfm.SetToIdentity();
	ExtractLinearTransform();
}

qbRT::GTform::~GTform()
{

}

// Construct from three vectors.
qbRT::GTform::GTform(const qbVector3<double> &translation, const qbVector3<double> &rotation, const qbVector3<double> &scale)
{
	SetTransform(translation, rotation, scale);
	ExtractLinearTransform();
}

// Construct from a pair of matrices.
qbRT::GTform::GTform(const qbMatrix2<double> &fwd, const qbMatrix2<double> &bck)
{
	// Verify that the inputs are 4x4.
	if (	(fwd.GetNumRows() != 4) || (fwd.GetNumCols() != 4) ||
				(bck.GetNumRows() != 4) || (bck.GetNumCols() != 4))
	{
		throw std::invalid_argument("Cannot construct GTform, inputs are not all 4x4.");
	}
	
	m_fwdtfm = fwd;
	m_bcktfm = bck;
	ExtractLinearTransform();
}

// Function to set the transform.
void qbRT::GTform::SetTransform(	const qbVector3<double> &translation,
																	const qbVector3<double> &rotation,
																	const qbVector3<double> &scale)
{
	// Define a matrix for each component of the transform.
	qbMatrix2<double> translationMatrix	{4, 4};
	qbMatrix2<double> rotationMatrixX		{4, 4};
	qbMatrix2<double>	rotationMatrixY		{4, 4};
	qbMatrix2<double> rotationMatrixZ		{4, 4};
	qbMatrix2<double>	scaleMatrix				{4, 4};
	
	// Set these to identity.
	translationMatrix.SetToIdentity();
	rotationMatrixX.SetToIdentity();
	rotationMatrixY.SetToIdentity();
	rotationMatrixZ.SetToIdentity();
	scaleMatrix.SetToIdentity();
	
	// Populate these with the appropriate values.
	// First the translation matrix.
	translationMatrix.SetElement(0, 3, translation.GetElement(0));
	translationMatrix.SetElement(1, 3, translation.GetElement(1));
	translationMatrix.SetElement(2, 3, translation.GetElement(2));
	
	// Rotation matrices.
	rotationMatrixZ.SetElement(0, 0, cos(rotation.GetElement(2)));
	rotationMatrixZ.SetElement(0, 1, -sin(rotation.GetElement(2)));
	rotationMatrixZ.SetElement(1, 0, sin(rotation.GetElement(2)));
	rotationMatrixZ.SetElement(1, 1, cos(rotation.GetElement(2)));
	
	rotationMatrixY.SetElement(0, 0, cos(rotation.GetElement(1)));
	rotationMatrixY.SetElement(0, 2, sin(rotation.GetElement(1)));
	rotationMatrixY.SetElement(2, 0, -sin(rotation.GetElement(1)));
	rotationMatrixY.SetElement(2, 2, cos(rotation.GetElement(1)));
	
	rotationMatrixX.SetElement(1, 1, cos(rotation.GetElement(0)));
	rotationMatrixX.SetElement(1, 2, -sin(rotation.GetElement(0)));
	rotationMatrixX.SetElement(2, 1, sin(rotation.GetElement(0)));
	rotationMatrixX.SetElement(2, 2, cos(rotation.GetElement(0)));
	
	// And the scale matrix.
	scaleMatrix.SetElement(0, 0, scale.GetElement(0));
	scaleMatrix.SetElement(1, 1, scale.GetElement(1));
	scaleMatrix.SetElement(2, 2, scale.GetElement(2));
	
	// Combine to give the final forward transform matrix.
	m_fwdtfm =	translationMatrix * 
							rotationMatrixX *
							rotationMatrixY *
							rotationMatrixZ *
							scaleMatrix;
							
	// Compute the backwards transform.
	m_bcktfm = m_fwdtfm;
	m_bcktfm.Inverse();		
}

void qbRT::GTform::SetTransform(const qbMatrix2<double> &fwd, const qbMatrix2<double> &bck)
{
	m_fwdtfm = fwd;
	m_bcktfm = bck;
	ExtractLinearTransform();
}

// Functions to return the transform matrices.
qbMatrix2<double> qbRT::GTform::GetForward()
{
	return m_fwdtfm;
}
qbMatrix2<double> qbRT::GTform::GetBackward()
{
	return m_bcktfm;
}

// Function to apply the transform.
qbRT::Ray qbRT::GTform::Apply(const qbRT::Ray &inputRay, bool dirFlag)
{
	// Create an output object.
	qbRT::Ray outputRay;
	
	if (dirFlag)
	{
		// Apply the forward transform.
		outputRay.m_point1 = this -> Apply(inputRay.m_point1, qbRT::FWDTFORM);
		outputRay.m_point2 = this -> Apply(inputRay.m_point2, qbRT::FWDTFORM);
		outputRay.m_lab = outputRay.m_point2 - outputRay.m_point1;
	}
	else
	{
		// Apply the backward transform.
		outputRay.m_point1 = this -> Apply(inputRay.m_point1, qbRT::BCKTFORM);
		outputRay.m_point2 = this -> Apply(inputRay.m_point2, qbRT::BCKTFORM);
		outputRay.m_lab = outputRay.m_point2 - outputRay.m_point1;
	}
	
	return outputRay;
}

qbVector3<double> qbRT::GTform::Apply(const qbVector3<double> &inputVector, bool dirFlag)
{
	// Convert inputVector to a 4-element vector.
	std::vector<double> tempData {	inputVector.GetElement(0),
																	inputVector.GetElement(1),
																	inputVector.GetElement(2),
																	1.0 };
	qbVector4<double> tempVector {tempData};
	
	// Create a vector for the result.
	qbVector4<double> resultVector;
	
	if (dirFlag)
	{
		// Apply the forward transform.
		resultVector = m_fwdtfm * tempVector;
	}
	else
	{
		// Apply the backward transform.
		resultVector = m_bcktfm * tempVector;
	}
	
	// Reform the output as a 3-element vector.
	qbVector3<double> outputVector {std::vector<double> {	resultVector.GetElement(0),
																												resultVector.GetElement(1),
																												resultVector.GetElement(2) }};
																					
	return outputVector;
}

qbVector3<double> qbRT::GTform::ApplyNorm(const qbVector3<double> &inputVector)
{

	// Apply the transform and return the result.
	qbVector3<double> result = m_lintfm * inputVector;
	return result;
	
}

// Overload operators.
namespace qbRT
{
	qbRT::GTform operator* (const qbRT::GTform &lhs, const qbRT::GTform &rhs)
	{
		// Form the product of the two forward transforms.
		qbMatrix2<double> fwdResult = lhs.m_fwdtfm * rhs.m_fwdtfm;
		
		// Compute the backward transform as the inverse of the forward transform.
		qbMatrix2<double> bckResult = fwdResult;
		bckResult.Inverse();
		
		// Form the final result.
		qbRT::GTform finalResult (fwdResult, bckResult);
		
		return finalResult;
	}
}

// Overload the assignment operator.
qbRT::GTform qbRT::GTform::operator= (const qbRT::GTform &rhs)
{
	// Make sure that we're not assigning to ourself.
	if (this != &rhs)
	{
		m_fwdtfm = rhs.m_fwdtfm;
		m_bcktfm = rhs.m_bcktfm;
		ExtractLinearTransform();
	}
	
	return *this;
}

// Function to print the transform matrix to STDOUT.
void qbRT::GTform::PrintMatrix(bool dirFlag)
{
	if (dirFlag)
	{
		Print(m_fwdtfm);
	}
	else
	{
		Print(m_bcktfm);
	}
}

void qbRT::GTform::Print(const qbMatrix2<double> &matrix)
{
	int nRows = matrix.GetNumRows();
	int nCols = matrix.GetNumCols();
	for (int row = 0; row<nRows; ++row)
	{
		for (int col = 0; col<nCols; ++col)
		{
			std::cout << std::fixed << std::setprecision(3) << matrix.GetElement(row, col) << " ";
		}
		std::cout << std::endl;
	}
}

// Function to print vectors.
void qbRT::GTform::PrintVector(const qbVector3<double> &inputVector)
{
	int nRows = inputVector.GetNumDims();
	for (int row = 0; row < nRows; ++row)
	{
		std::cout << std::fixed << std::setprecision(3) << inputVector.GetElement(row) << std::endl;
	}
}

// Function to extract the linear portion of the transform.
void qbRT::GTform::ExtractLinearTransform()
{
	// Copy the linear portion of the transform.
	for (int i=0; i<3; ++i)
	{
		for (int j=0; j<3; ++j)
		{
			m_lintfm.SetElement(i, j, m_fwdtfm.GetElement(i, j));
		}
	}
	
	// Invert and transpose.
	m_lintfm.Inverse();
	m_lintfm = m_lintfm.Transpose();
	
}

// Function to return the normal transform.
qbMatrix2<double> qbRT::GTform::GetNormalTransform()
{
	return m_lintfm;
}




































