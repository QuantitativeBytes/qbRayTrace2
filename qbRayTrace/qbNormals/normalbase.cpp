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

#include "normalbase.hpp"

// Constructor / destructor.
qbRT::Normal::NormalBase::NormalBase()
{

}

qbRT::Normal::NormalBase::~NormalBase()
{

}

qbVector3<double> qbRT::Normal::NormalBase::ComputePerturbation(const qbVector3<double> &normal, const qbVector2<double> &uvCoords)
{
	// The default response.
	return qbVector3<double>{0.0, 0.0, 0.0};
}

qbVector3<double> qbRT::Normal::NormalBase::PerturbNormal(const qbVector3<double> &normal, const qbVector3<double> &perturbation)
{
	// Decide upon an appropriate up vector.
	qbVector3<double> newUpVector = std::vector<double> {0.0, 0.0, -1.0};
	if ((normal.GetElement(2) > 0.99) || (normal.GetElement(2) < -0.99))
		newUpVector = std::vector<double> {1.0, 0.0, 0.0};

	// Compute the directions (based on the tangent plane).
	qbVector3<double> pV = qbVector3<double>::cross(newUpVector, normal);
	pV.Normalize();
	qbVector3<double> pU = qbVector3<double>::cross(normal, pV);
	pU.Normalize();
	
	// Apply the perturbation.
	qbVector3<double> output = normal + (pU * perturbation.GetElement(0)) + (pV * perturbation.GetElement(1)) + (normal * perturbation.GetElement(2));
	
	// Normalize the output.
	output.Normalize();
	
	// And return.
	return output;
}

void qbRT::Normal::NormalBase::SetAmplitude(double amplitude)
{
	m_amplitudeScale = amplitude;
}

// Function to perform numerical differentiation of a texture in UV space.
qbVector2<double> qbRT::Normal::NormalBase::TextureDiff(const std::shared_ptr<qbRT::Texture::TextureBase> &inputTexture, const qbVector2<double> &uvCoords)
{
	// We will use the symmetric difference quotient to estimate the partial derivatives of the texture
	// at the point f(u,v).
	// uGrad = f(u+h, v) - f(u-h, v) / 2h
	// vGrad = f(u, v+h) - f(u, v-h) / 2h
	double h = 0.001;
	qbVector2<double> uDisp {h, 0.0};
	qbVector2<double> vDisp {0.0, h};
	double uGrad = (inputTexture->GetValue(uvCoords + uDisp) - inputTexture->GetValue(uvCoords - uDisp)) / (2.0 * h);
	double vGrad = (inputTexture->GetValue(uvCoords + vDisp) - inputTexture->GetValue(uvCoords - vDisp)) / (2.0 * h);
	
	/* Form a vector for the output. 
	*/
	qbVector2<double> output = std::vector<double> {uGrad, vGrad};
	return output;
}

// Function to apply the transform.
qbVector2<double> qbRT::Normal::NormalBase::ApplyTransform(const qbVector2<double> &inputVector)
{
	// Copy the input vector and modify to have three elements.
	qbVector3<double> newInput;
	newInput.SetElement(0, inputVector.GetElement(0));
	newInput.SetElement(1, inputVector.GetElement(1));
	
	// Apply the transform.
	qbVector3<double> result = m_transformMatrix * newInput;
	
	// Produce the output.
	qbVector2<double> output;
	output.SetElement(0, result.GetElement(0));
	output.SetElement(1, result.GetElement(1));
	
	return output;
}

// Function to set the transform matrix.
void qbRT::Normal::NormalBase::SetTransform(const qbVector2<double> &translation, const double &rotation, const qbVector2<double> &scale)
{
	// Build the transform matrix.
	qbMatrix33<double> rotationMatrix = {std::vector<double> {
																			cos(rotation), -sin(rotation), 0.0,
																			sin(rotation), cos(rotation), 0.0,
																			0.0, 0.0, 1.0}};
																			
	qbMatrix33<double> scaleMatrix = {std::vector<double> {
																		scale.GetElement(0), 0.0, 0.0,
																		0.0, scale.GetElement(1), 0.0,
																		0.0, 0.0, 1.0}};
																		
	qbMatrix33<double> translationMatrix = {std::vector<double> {
																					1.0, 0.0, translation.GetElement(0),
																					0.0, 1.0, translation.GetElement(1),
																					0.0, 0.0, 1.0}};
																					
	// And combine to form the final transform matrix.
	m_transformMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}


