/* ***********************************************************
	materialbase.cpp
	
	The material base class implementation - A class for handling 
	materials.
	
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

// materialbase.cpp

#include "materialbase.hpp"

// Constructor / destructor.
qbRT::MaterialBase::MaterialBase()
{
	m_maxReflectionRays = 3;
	m_reflectionRayCount = 0;
}

qbRT::MaterialBase::~MaterialBase()
{

}

// Function to compute the color of the material.
qbVector3<double> qbRT::MaterialBase::ComputeColor(	const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
																										const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
																										const std::shared_ptr<qbRT::ObjectBase> &currentObject,
																										const qbVector3<double> &intPoint, const qbVector3<double> &localNormal,
																										const qbVector3<double> &localPOI, const qbVector2<double> &uvCoords,
																										const qbRT::Ray &cameraRay)
{
	// Define an initial material color.
	qbVector3<double> matColor;
	
	return matColor;
}

// Function to compute the diffuse color.
qbVector3<double> qbRT::MaterialBase::ComputeDiffuseColor(	const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
																													const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
																													const std::shared_ptr<qbRT::ObjectBase> &currentObject,
																													const qbVector3<double> &intPoint, const qbVector3<double> &localNormal,
																													const qbVector3<double> &baseColor)
{
	// Compute the color due to diffuse illumination.
	qbVector3<double> diffuseColor;
	double intensity;
	qbVector3<double> color;
	double red = 0.0;
	double green = 0.0;
	double blue = 0.0;
	bool validIllum = false;
	bool illumFound = false;
	for (auto currentLight : lightList)
	{
		validIllum = currentLight -> ComputeIllumination(intPoint, localNormal, objectList, NULL, color, intensity);
		if (validIllum)
		{
			illumFound = true;
			red += color.GetElement(0) * intensity;
			green += color.GetElement(1) * intensity;
			blue += color.GetElement(2) * intensity;
		}
	}
	
	if (illumFound)
	{
		diffuseColor.SetElement(0, red * baseColor.GetElement(0));
		diffuseColor.SetElement(1, green * baseColor.GetElement(1));
		diffuseColor.SetElement(2, blue * baseColor.GetElement(2));
	}
	else
	{
		// The ambient light condition.
		for (int i=0; i<3; ++i)
			diffuseColor.SetElement(i, (m_ambientColor.GetElement(i) * m_ambientIntensity) * baseColor.GetElement(i));
	}
	
	// Return the material color.
	return diffuseColor;
	
}

// Function to compute the color due to reflection.
qbVector3<double> qbRT::MaterialBase::ComputeReflectionColor(	const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
																															const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
																															const std::shared_ptr<qbRT::ObjectBase> &currentObject,
																															const qbVector3<double> &intPoint, const qbVector3<double> &localNormal,
																															const qbRT::Ray &incidentRay)
{
	qbVector3<double> reflectionColor;
	
	// Compute the reflection vector.
	qbVector3<double> d = incidentRay.m_lab;
	qbVector3<double> reflectionVector = d - (2.0 * qbVector3<double>::dot(d, localNormal) * localNormal);
	
	// Construct the reflection ray.
	qbVector3<double> startPoint = intPoint + (localNormal * 0.001);
	qbRT::Ray reflectionRay (startPoint, startPoint + reflectionVector);
	
	/* Cast this ray into the scene and find the closest object that it intersects with. */
	std::shared_ptr<qbRT::ObjectBase> closestObject;
	qbRT::DATA::hitData closestHitData;
	bool intersectionFound = CastRay(reflectionRay, objectList, NULL, closestObject, closestHitData);
	
	/* Compute illumination for closest object assuming that there was a
		valid intersection. */
	qbVector3<double> matColor;
	if ((intersectionFound) && (m_reflectionRayCount < m_maxReflectionRays))
	{
		// Increment the reflectionRayCount.
		m_reflectionRayCount++;
		
		// Check if a material has been assigned.
		if (closestHitData.hitObject -> m_hasMaterial)
		{
			// Use the material to compute the color.
			matColor = closestHitData.hitObject -> m_pMaterial -> ComputeColor(	objectList, lightList, 
																																					closestHitData.hitObject, closestHitData.poi, 
																																					closestHitData.normal, 
																																					closestHitData.localPOI,
																																					closestHitData.uvCoords, reflectionRay);
		}
		else
		{
			matColor = qbRT::MaterialBase::ComputeDiffuseColor(	objectList, lightList, closestHitData.hitObject, 
																													closestHitData.poi, closestHitData.normal, 
																													closestObject->m_baseColor);			
		}
	}
	else
	{
		// Leave matColor as it is.
	}
	
	reflectionColor = matColor;
	return reflectionColor;
}

// Function to cast a ray into the scene.
bool qbRT::MaterialBase::CastRay( const qbRT::Ray &castRay, const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
																	const std::shared_ptr<qbRT::ObjectBase> &thisObject,
																	std::shared_ptr<qbRT::ObjectBase> &closestObject,
																	qbRT::DATA::hitData &closestHitData)
{
	// Test for intersections with all of the objects in the scene.
	qbRT::DATA::hitData hitData;
	
	double minDist = 1e6;
	bool intersectionFound = false;
	for (auto currentObject : objectList)
	{
		if (currentObject != thisObject)
		{
			bool validInt = currentObject -> TestIntersection(castRay, hitData);
			
			// If we have a valid intersection.
			if (validInt)
			{
				// Set the flag to show that we found an intersection.
				intersectionFound = true;
				
				// Compute the distance between the source and the intersection point.
				double dist = (hitData.poi - castRay.m_point1).norm();
				
				// Store a reference to this object if it is the closest.
				if (dist < minDist)
				{
					minDist = dist;
					closestObject = currentObject;
					closestHitData = hitData;
				}
			}
		}
	}
	
	return intersectionFound;
}

// Function to assign a texture.
void qbRT::MaterialBase::AssignTexture(const std::shared_ptr<qbRT::Texture::TextureBase> &inputTexture)
{
	m_textureList.push_back(inputTexture);
	m_hasTexture = true;
}

// *** Function to assign a normal map.
void qbRT::MaterialBase::AssignNormalMap(const std::shared_ptr<qbRT::Normal::NormalBase> &inputNormalMap)
{
	m_normalMapList.push_back(inputNormalMap);
	m_hasNormalMap = true;
}

// Function to return the color due to textures at the given (u,v) coordinate.
qbVector3<double> qbRT::MaterialBase::GetTextureColor(const qbVector2<double> &uvCoords)
{
	qbVector4<double> outputColor;
	qbVector3<double> finalColor;
	
	if (m_textureList.size() > 1)
	{
		outputColor = m_textureList.at(0)->GetColor(uvCoords);
		for (int i=1; i<m_textureList.size(); ++i)
		{
			BlendColors(outputColor, m_textureList.at(i)->GetColor(uvCoords));
		}
	}
	else
	{
		outputColor = m_textureList.at(0)->GetColor(uvCoords);
	}
	
	finalColor.m_x = outputColor.m_v1;
	finalColor.m_y = outputColor.m_v2;
	finalColor.m_z = outputColor.m_v3;
	return finalColor;
}

// Function to blend colors.
void qbRT::MaterialBase::BlendColors(qbVector4<double> &color1, const qbVector4<double> &color2)
{
	color1 = (color2 * color2.GetElement(3)) + (color1 * (1.0 - color2.GetElement(3)));
}

// *** Function to perturb the object normal to give the material normal.
qbVector3<double> qbRT::MaterialBase::PerturbNormal(const qbVector3<double> &normal, const qbVector2<double> &uvCoords, const qbVector3<double> &upVector)
{
	// Copy the original normal.
	qbVector3<double> newNormal = normal;
	
	// Perturb the new normal with each normal map in turn.
	for (int i=0; i<m_normalMapList.size(); ++i)
	{
		newNormal = m_normalMapList.at(i) -> ComputePerturbation(newNormal, uvCoords);
	}

	// And return the output.
	return newNormal;
}

// **********************************************************************
// Function to compute combined specular and diffuse lighting components.
qbVector3<double> qbRT::MaterialBase::ComputeSpecAndDiffuse(	const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
																														const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
																														const std::shared_ptr<qbRT::ObjectBase> &currentObject,
																														const qbVector3<double> &intPoint, const qbVector3<double> &localNormal,
																														const qbVector3<double> &baseColor, const qbRT::Ray &cameraRay)
{
	// Compute the color due to diffuse illumination and specular highlights.
	qbVector3<double> outputColor;
	qbVector3<double> diffuseColor;
	qbVector3<double> spcColor;
	double intensity;
	double specIntensity = 0.0;
	qbVector3<double> color;
	double red = 0.0;
	double green = 0.0;
	double blue = 0.0;
	double specR = 0.0;
	double specG = 0.0;
	double specB = 0.0;
	bool validIllum = false;
	bool illumFound = false;
	for (auto currentLight : lightList)
	{
		validIllum = currentLight -> ComputeIllumination(intPoint, localNormal, objectList, NULL, color, intensity);
		if (validIllum)
		{
			illumFound = true;
			
			// The diffuse component.
			red += color.GetElement(0) * intensity;
			green += color.GetElement(1) * intensity;
			blue += color.GetElement(2) * intensity;
			
			// The specular component.
			if ((m_specular > 0.0) && (m_shininess > 0.0))
			{
				specIntensity = 0.0;
				
				// Construct a vector pointing from the intersection point to the light.
				qbVector3<double> lightDir = (currentLight->m_location - intPoint).Normalized();
				
				// Compute a start point.
				qbVector3<double> startPoint = intPoint + (lightDir * 0.001);
				
				// Construct a ray from the point of intersection to the light.
				qbRT::Ray lightRay (startPoint, startPoint + lightDir);	
				
				// Compute the reflection vector.
				qbVector3<double> d = lightRay.m_lab;
				qbVector3<double> r = d - (2.0 * qbVector3<double>::dot(d, localNormal) * localNormal);
				
				// Compute the dot product.
				qbVector3<double> v = cameraRay.m_lab;
				v.Normalize();
				double dotProduct = qbVector3<double>::dot(r, v);
				
				// Only proceed if the dot product is positive.
				if (dotProduct > 0.0)
				{
					specIntensity = (m_specular * std::pow(dotProduct, m_shininess));
				}
				
				specR += currentLight->m_color.GetElement(0) * specIntensity;
				specG += currentLight->m_color.GetElement(1) * specIntensity;
				specB += currentLight->m_color.GetElement(2) * specIntensity;	
			}				
		}
	}
	
	if (illumFound)
	{
		diffuseColor.SetElement(0, red * baseColor.GetElement(0));
		diffuseColor.SetElement(1, green * baseColor.GetElement(1));
		diffuseColor.SetElement(2, blue * baseColor.GetElement(2));
		spcColor.SetElement(0, specR);
		spcColor.SetElement(1, specG);
		spcColor.SetElement(2, specB);		
	}
	
	// Add the ambient light.
	diffuseColor.SetElement(0, diffuseColor.GetElement(0) + ((m_ambientColor.GetElement(0) * m_ambientIntensity) * baseColor.GetElement(0)));
	diffuseColor.SetElement(1, diffuseColor.GetElement(1) + ((m_ambientColor.GetElement(1) * m_ambientIntensity) * baseColor.GetElement(1)));
	diffuseColor.SetElement(2, diffuseColor.GetElement(2) + ((m_ambientColor.GetElement(2) * m_ambientIntensity) * baseColor.GetElement(2)));		
	
	// Compute the color due to specular highlights.
	outputColor = diffuseColor + spcColor;
	
	// Return the material color.
	return outputColor;	
}













