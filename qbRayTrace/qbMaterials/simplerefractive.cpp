/* ***********************************************************
	simplerefractive.cpp
	
	The SimpleRefractive class implementation - A class for transparent
	materials with a definable refractive index.
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
	This code corresponds specifically to Episode 10 of the series,
	which may be found here:
	https://youtu.be/6slB1euGMFw
	
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

#include "simplerefractive.hpp"

qbRT::SimpleRefractive::SimpleRefractive()
{

}

qbRT::SimpleRefractive::~SimpleRefractive()
{

}

// Function to return the color.
qbVector3<double> qbRT::SimpleRefractive::ComputeColor(	const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
																												const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
																												const std::shared_ptr<qbRT::ObjectBase> &currentObject,
																												const qbVector3<double> &intPoint, const qbVector3<double> &localNormal,
																												const qbVector3<double> &localPOI, const qbVector2<double> &uvCoords,
																												const qbRT::Ray &cameraRay)
{
	// Define the initial material colors.
	qbVector3<double> matColor;
	qbVector3<double> refColor;
	qbVector3<double> difColor;
	qbVector3<double> spcColor;
	qbVector3<double> trnColor;
	
	// Compute the diffuse component.
	if (!m_hasTexture)
	{
		difColor = ComputeDiffuseColor(objectList, lightList, currentObject, intPoint, localNormal, m_baseColor);
	}
	else
	{
		//qbVector3<double> textureColor = GetTextureColor(currentObject->m_uvCoords);
		qbVector3<double> textureColor = GetTextureColor(uvCoords);
		difColor = ComputeDiffuseColor(objectList, lightList, currentObject, intPoint, localNormal, textureColor);
	}
		
	// Compute the reflection component.
	if (m_reflectivity > 0.0)
		refColor = ComputeReflectionColor(objectList, lightList, currentObject, intPoint, localNormal, cameraRay);
		
	// Combine the reflection and diffuse components.
	matColor = (refColor * m_reflectivity) + (difColor * (1.0 - m_reflectivity));
	
	// Compute the refractive component.
	if (m_translucency > 0.0)
		trnColor = ComputeTranslucency(objectList, lightList, currentObject, intPoint, localNormal, cameraRay);
		
	// And combine with the current color.
	matColor = (trnColor * m_translucency) + (matColor * (1.0 - m_translucency));
	
	// And compute the specular component.
	if (m_shininess > 0.0)
		spcColor = ComputeSpecular(objectList, lightList, intPoint, localNormal, cameraRay);
		
	// Finally, add the specular component.
	matColor = matColor + spcColor;
	
	return matColor;
}

// Function to compute the color due to translucency.
qbVector3<double> qbRT::SimpleRefractive::ComputeTranslucency(	const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
																															const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
																															const std::shared_ptr<qbRT::ObjectBase> &currentObject,
																															const qbVector3<double> &intPoint, const qbVector3<double> &localNormal,
																															const qbRT::Ray &incidentRay)
{
	qbVector3<double> trnColor {3};
	
	// Compute the refracted vector.
	qbVector3<double> p = incidentRay.m_lab;
	p.Normalize();
	qbVector3<double> tempNormal = localNormal;
	double r = 1.0 / m_ior;
	double c = -qbVector3<double>::dot(tempNormal, p);
	if (c < 0.0)
	{
		tempNormal = tempNormal * -1.0;
		c = -qbVector3<double>::dot(tempNormal, p);
	}
	
	qbVector3<double> refractedVector = r*p + (r*c - sqrtf(1.0-pow(r,2.0) * (1.0-pow(c,2.0)))) * tempNormal;
	
	// Construct the refracted ray.
	qbRT::Ray refractedRay (intPoint + (refractedVector * 0.01), intPoint + refractedVector);
	
	// Test for secondary intersection with this object.
	std::shared_ptr<qbRT::ObjectBase> closestObject;
	qbRT::DATA::hitData closestHitData;
	qbRT::DATA::hitData hitData;	
	bool test = currentObject -> TestIntersection(refractedRay, hitData);
	bool intersectionFound = false;
	qbRT::Ray finalRay;
	if (test)
	{
		// Compute the refracted vector.
		qbVector3<double> p2 = refractedRay.m_lab;
		p2.Normalize();
		qbVector3<double> tempNormal2 = hitData.normal;
		double r2 = m_ior;
		double c2 = -qbVector3<double>::dot(tempNormal2, p2);
		if (c2 < 0.0)
		{
			tempNormal2 = tempNormal2 * -1.0;
			c2 = -qbVector3<double>::dot(tempNormal2, p2);
		}
		qbVector3<double> refractedVector2 = r2*p2 + (r2*c2 - sqrtf(1.0-pow(r2,2.0) * (1.0-pow(c2,2.0)))) * tempNormal2;
		
		// Compute the refracted ray.
		qbRT::Ray refractedRay2 (hitData.poi + (refractedVector2 * 0.01), hitData.poi + refractedVector2);
		
		// Cast this ray into the scene.
		intersectionFound = CastRay(refractedRay2, objectList, currentObject, closestObject, closestHitData);
		finalRay = refractedRay2;
	}
	else
	{
		/* No secondary intersections were found, so continue the original refracted ray. */
		intersectionFound = CastRay(refractedRay, objectList, currentObject, closestObject, closestHitData);
		finalRay = refractedRay;
	}
	
	// Compute the color for closest object.
	qbVector3<double> matColor	{3};
	if (intersectionFound)
	{
		// Check if a material has been assigned.
		if (closestObject -> m_hasMaterial)
		{
			matColor = closestHitData.hitObject -> m_pMaterial -> ComputeColor(	objectList, lightList, 
																																					closestHitData.hitObject, 
																																					closestHitData.poi, 
																																					closestHitData.normal, 
																																					closestHitData.localPOI,
																																					closestHitData.uvCoords,
																																					finalRay);
		}
		else
		{
			matColor = qbRT::MaterialBase::ComputeDiffuseColor(	objectList, lightList, 
																													closestHitData.hitObject, 
																													closestHitData.poi, 
																													closestHitData.normal, closestObject->m_baseColor);
		}
	}
	else
	{
		// Leave matColor as it is.
	}
	
	trnColor = matColor;
	return trnColor;
}

// Function to compute the specular highlights.
qbVector3<double> qbRT::SimpleRefractive::ComputeSpecular(const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
																													const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
																													const qbVector3<double> &intPoint, const qbVector3<double> &localNormal,
																													const qbRT::Ray &cameraRay)
{
	qbVector3<double> spcColor	{3};
	double red = 0.0;
	double green = 0.0;
	double blue = 0.0;
	
	// Loop through all of the lights in the scene.
	for (auto currentLight : lightList)
	{
		/* Check for intersections with all objects in the scene. */
		double intensity = 0.0;
		
		// Construct a vector pointing from the intersection point to the light.
		qbVector3<double> lightDir = (currentLight->m_location - intPoint).Normalized();
		
		// Compute a start point.
		qbVector3<double> startPoint = intPoint + (lightDir * 0.001);
		
		// Construct a ray from the point of intersection to the light.
		qbRT::Ray lightRay (startPoint, startPoint + lightDir);
		
		/* Loop through all objects in the scene to check if any
			obstruct light from this source. */
		//qbVector3<double> poi				{3};
		//qbVector3<double> poiNormal	{3};
		//qbVector3<double> poiColor		{3};
		qbRT::DATA::hitData hitData;
		bool validInt = false;
		for (auto sceneObject : objectList)
		{
			validInt = sceneObject -> TestIntersection(lightRay, hitData);
			if (validInt)
				break;
		}
		
		/* If no intersections were found, then proceed with
			computing the specular component. */
		if (!validInt)
		{
			// Compute the reflection vector.
			qbVector3<double> d = lightRay.m_lab;
			qbVector3<double> r = d - (2 * qbVector3<double>::dot(d, localNormal) * localNormal);
			r.Normalize();
			
			// Compute the dot product.
			qbVector3<double> v = cameraRay.m_lab;
			v.Normalize();
			double dotProduct = qbVector3<double>::dot(r, v);
			
			// Only proceed if the dot product is positive.
			if (dotProduct > 0.0)
			{
				intensity = m_reflectivity * std::pow(dotProduct, m_shininess);
			}
		}
		
		red += currentLight->m_color.GetElement(0) * intensity;
		green += currentLight->m_color.GetElement(1) * intensity;
		blue += currentLight->m_color.GetElement(2) * intensity;
	}
	
	spcColor.SetElement(0, red);
	spcColor.SetElement(1, green);
	spcColor.SetElement(2, blue);
	return spcColor;
}















