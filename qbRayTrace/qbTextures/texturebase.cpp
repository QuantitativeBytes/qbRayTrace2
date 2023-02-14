/* ***********************************************************
	texturebase.cpp
	
	The texturebase class implementation - a simple base class for
	handling textures.
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
	This code corresponds specifically to Episode 9 of the series,
	which may be found here:
	https://youtu.be/d35gDi98gEY
	
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

#include "texturebase.hpp"
#include <cmath>

// Constructor / destructor.
qbRT::Texture::TextureBase::TextureBase()
{

}

qbRT::Texture::TextureBase::~TextureBase()
{

}

// Function to return the color at a given (U,V) location.
qbVector4<double> qbRT::Texture::TextureBase::GetColor(const qbVector2<double> &uvCoords)
{
	// Setup the output vector.
	qbVector4<double> outputColor;
	
	// Return the output.
	return outputColor;
}

// *** Function to return the actual texture value at a given (u,v) location.
double qbRT::Texture::TextureBase::GetValue(const qbVector2<double> &uvCoords)
{
	// Return a default value.
	return 0.0;
}

// Function to set the transform matrix.
void qbRT::Texture::TextureBase::SetTransform(const qbVector2<double> &translation, const double &rotation, const qbVector2<double> &scale)
{
	// Build the transform matrix.
/*	
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
*/

	
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

// Function to blend colors.
qbVector3<double> qbRT::Texture::TextureBase::BlendColors(const std::vector<qbVector3<double>> &inputColorList)
{
	// Setup the output color.
	qbVector3<double> outputColor;
	
	// Return the output.
	return outputColor;
}

// Function to apply the transform.
qbVector2<double> qbRT::Texture::TextureBase::ApplyTransform(const qbVector2<double> &inputVector)
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





















