/* ***********************************************************
	simplematerial.cpp
	
	The SimpleMaterial class implementation - A class for handling 
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

// simplematerial.cpp

#include "simplematerial.hpp"

qbRT::SimpleMaterial::SimpleMaterial()
{

}

qbRT::SimpleMaterial::~SimpleMaterial()
{

}

// Function to return the color.
/* Note the addition of two extra inputs to the ComputeColor function, for the local POI
 and the UV coords respectively. */
qbVector3<double> qbRT::SimpleMaterial::ComputeColor(	const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
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
	
	// *** Apply any normals maps that may have been assigned.
	qbVector3<double> newNormal = localNormal;
	if (m_hasNormalMap)
	{
		qbVector3<double> upVector = std::vector<double> {0.0, 0.0, -1.0};
		//newNormal = PerturbNormal(newNormal, currentObject -> m_uvCoords, upVector);
		/* We modify this code to get the UV coords directly from the hitData structure,
			as they are no longer stored in the object itself. */
		newNormal = PerturbNormal(newNormal, uvCoords, upVector);
		
	}
	
	// *** Store the current local normal, in case it is needed elsewhere.
	m_localNormal = newNormal;	
	
	/* Note the change of localNormal to newNormal wherever the normal is used
		in the code below. */
	
	// Compute the diffuse component.
	if (!m_hasTexture)
	{
		difColor = ComputeSpecAndDiffuse(objectList, lightList, currentObject, intPoint, newNormal, m_baseColor, cameraRay);
	}
	else
	{
		//qbVector3<double> textureColor = GetTextureColor(currentObject->m_uvCoords);
		/* We modify this code to get the UV coords directly from the hitData structure,
			as they are no longer stored in the object itself. */
		qbVector3<double> textureColor = GetTextureColor(uvCoords);		
		difColor = ComputeSpecAndDiffuse(objectList, lightList, currentObject, intPoint, newNormal, textureColor, cameraRay);		
	}
	
	// Compute the reflection component.
	if (m_reflectivity > 0.0)
		refColor = ComputeReflectionColor(objectList, lightList, currentObject, intPoint, newNormal, cameraRay);
		
	// Combine reflection and diffuse components.
	matColor = (refColor * m_reflectivity) + (difColor * (1 - m_reflectivity));
	
	/*
	// Compute the specular component.
	if (m_shininess > 0.0)
		spcColor = ComputeSpecular(objectList, lightList, intPoint, newNormal, cameraRay);
		
	// Add the specular component to the final color.
	matColor = matColor + spcColor;
	*/
	
	return matColor;
}

// Function to compute the specular highlights.
qbVector3<double> qbRT::SimpleMaterial::ComputeSpecular(	const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
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





























