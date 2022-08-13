/* ***********************************************************
	normalbase.cpp
	
	The normalbase class definition - a simple base class for
	handling normal maps.
	
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

#include "normalbase.hpp"

// Constructor / destructor.
qbRT::Normal::NormalBase::NormalBase()
{

}

qbRT::Normal::NormalBase::~NormalBase()
{

}

qbVector<double> qbRT::Normal::NormalBase::ComputePerturbation(const qbVector<double> &normal, const qbVector<double> &uvCoords)
{
	// The default response.
	return qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}};
}

qbVector<double> qbRT::Normal::NormalBase::PerturbNormal(const qbVector<double> &normal, const qbVector<double> &perturbation)
{
	// Decide upon an appropriate up vector.
	qbVector<double> newUpVector = std::vector<double> {0.0, 0.0, -1.0};
	if ((normal.GetElement(2) > 0.99) || (normal.GetElement(2) < -0.99))
		newUpVector = std::vector<double> {1.0, 0.0, 0.0};

	// Compute the directions (based on the tangent plane).
	qbVector<double> pV = qbVector<double>::cross(newUpVector, normal);
	pV.Normalize();
	qbVector<double> pU = qbVector<double>::cross(normal, pV);
	pU.Normalize();
	
	// Apply the perturbation.
	qbVector<double> output = normal + (pU * perturbation.GetElement(0)) + (pV * perturbation.GetElement(1)) + (normal * perturbation.GetElement(2));
	
	// Normalize the output.
	output.Normalize();
	
	// And return.
	return output;
}

void qbRT::Normal::NormalBase::SetAmplitude(double amplitude)
{
	m_amplitudeScale = amplitude;
}

// Function to apply the transform.
qbVector<double> qbRT::Normal::NormalBase::ApplyTransform(const qbVector<double> &inputVector)
{
	// Copy the input vector and modify to have three elements.
	qbVector<double> newInput {3};
	newInput.SetElement(0, inputVector.GetElement(0));
	newInput.SetElement(1, inputVector.GetElement(1));
	
	// Apply the transform.
	qbVector<double> result = m_transformMatrix * newInput;
	
	// Produce the output.
	qbVector<double> output {2};
	output.SetElement(0, result.GetElement(0));
	output.SetElement(1, result.GetElement(1));
	
	return output;
}

// Function to set the transform matrix.
void qbRT::Normal::NormalBase::SetTransform(const qbVector<double> &translation, const double &rotation, const qbVector<double> &scale)
{
	// Build the transform matrix.
	qbMatrix2<double> rotationMatrix = {3, 3, std::vector<double> {
																			cos(rotation), -sin(rotation), 0.0,
																			sin(rotation), cos(rotation), 0.0,
																			0.0, 0.0, 1.0}};
																			
	qbMatrix2<double> scaleMatrix = {	3, 3, std::vector<double> {
																		scale.GetElement(0), 0.0, 0.0,
																		0.0, scale.GetElement(1), 0.0,
																		0.0, 0.0, 1.0}};
																		
	qbMatrix2<double> translationMatrix = {	3, 3, std::vector<double> {
																					1.0, 0.0, translation.GetElement(0),
																					0.0, 1.0, translation.GetElement(1),
																					0.0, 0.0, 1.0}};
																					
	// And combine to form the final transform matrix.
	m_transformMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}


