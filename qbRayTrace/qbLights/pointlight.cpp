	
	/* ***********************************************************
	pointlight.cpp
	
	The point light class implementation - A class for handling point
	lights.
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
	This code corresponds specifically to Episode 6 of the series,
	which may be found here:
	https://youtu.be/9K9ZYq6KgFY
	
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

#include "pointlight.hpp"

// Default constructor.
qbRT::PointLight::PointLight()
{
	//m_color = qbVector3<double> {std::vector<double> {1.0, 1.0, 1.0}};
	m_color = qbVector3<double> {1.0, 1.0, 1.0};
	m_intensity = 1.0;
}

// Destructor.
qbRT::PointLight::~PointLight()
{

}

// Function to compute illumination.
bool qbRT::PointLight::ComputeIllumination(	const qbVector3<double> &intPoint, const qbVector3<double> &localNormal,
																						const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
																						const std::shared_ptr<qbRT::ObjectBase> &currentObject,
																						qbVector3<double> &color, double &intensity)
{
	// Construct a vector pointing from the intersection point to the light.
	qbVector3<double> lightDir = (m_location - intPoint).Normalized();
	double lightDist = (m_location - intPoint).norm();
	
	// Compute a starting point.
	qbVector3<double> startPoint = intPoint + (localNormal * 0.001);
	
	// Construct a ray from the point of intersection to the light.
	qbRT::Ray lightRay (startPoint, startPoint + lightDir);
	
	/* Check for intersections with all of the objects
		in the scene, except for the current one. */
	qbRT::DATA::hitData hitData;
	bool validInt = false;
	for (auto sceneObject : objectList)
	{
		if (sceneObject != currentObject)
		{
			validInt = sceneObject -> TestIntersection(lightRay, hitData);
			if (validInt)
			{
				double dist = (hitData.poi - startPoint).norm();
				if (dist > lightDist)
					validInt = false;
			}
		}
		
		/* If we have an intersection, then there is no point checking further
			so we can break out of the loop. In other words, this object is
			blocking light from this light source. */
		if (validInt)
			break;
	}

	/* Only continue to compute illumination if the light ray didn't
		intersect with any objects in the scene. Ie. no objects are
		casting a shadow from this light source. */
	if (!validInt)
	{
		// Compute the angle between the local normal and the light ray.
		// Note that we assume that localNormal is a unit vector.
		double angle = acos(qbVector3<double>::dot(localNormal, lightDir));
		
		// If the normal is pointing away from the light, then we have no illumination.
		if (angle > (M_PI/2.0))
		{
			// No illumination.
			color = m_color;
			intensity = 0.0;
			return false;
		}
		else
		{
			// We do have illumination.
			color = m_color;
			intensity = m_intensity * (1.0 - (2.0 * angle / M_PI));
			return true;
		}
	}
	else
	{
		// Shadow, so no illumination.
		color = m_color;
		intensity = 0.0;
		return false;
	}
}




















