/* ***********************************************************
	scene.cpp
	
	The scene class implementation - A class to handle information
	about the scene and rendering to an image.
	
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

// scene.cpp

#include <chrono>
#include "scene.hpp"
#include "./qbMaterials/simplematerial.hpp"
#include "./qbMaterials/simplerefractive.hpp"
#include "./qbTextures/checker.hpp"
#include "./qbTextures/image.hpp"
#include "./qbTextures/gradient.hpp"
#include "./qbTextures/basicvalnoise.hpp"
#include "./qbTextures/basicnoise.hpp"
#include "./qbTextures/marble.hpp"
#include "./qbTextures/qbStone1.hpp"

// The constructor.
qbRT::Scene::Scene()
{
	// Setup the scene.
	SetupSceneObjects();

	/*
		This is now a base class that is intended to be inherited
		by a specific scene class that implements the
		SetupSceneObjects() function to define all of the objects,
		lights and camera configuration for the scene.
	*/

}

// Destructor.
qbRT::Scene::~Scene()
{

}

// Function to perform the rendering.
bool qbRT::Scene::Render(qbImage &outputImage)
{
	// Record the start time.
	auto startTime = std::chrono::steady_clock::now();

	// Get the dimensions of the output image.
	int xSize = outputImage.GetXSize();
	int ySize = outputImage.GetYSize();
	
	// Loop over each pixel in our image.
	for (int y=0; y<ySize; ++y)
	{
		// Display progress.
		std::cout << "Processing line " << y << " of " << ySize << "." << " \r";
		std::cout.flush();
		
		for (int x=0; x<xSize; ++x)
		{
			qbVector3<double> pixelColor = RenderPixel(x, y, xSize, ySize);
			outputImage.SetPixel(x, y, pixelColor.GetElement(0), pixelColor.GetElement(1), pixelColor.GetElement(2));
		}
	}
	
	// Record the end time.
	auto endTime = std::chrono::steady_clock::now();
	
	// Compute the time it took to render.
	std::chrono::duration<double> renderTime = endTime - startTime;
	std::cout.flush();
	std::cout << "\n\nRendering time: " << renderTime.count() << "s" << std::endl;
	
	std::cout << std::endl;
	return true;
}

// Function to cast a ray into the scene.
bool qbRT::Scene::CastRay(	qbRT::Ray &castRay, std::shared_ptr<qbRT::ObjectBase> &closestObject,
														qbRT::DATA::hitData &closestHitData)
{
	qbRT::DATA::hitData hitData;
	double minDist = 1e6;
	bool intersectionFound = false;
	for (auto currentObject : m_objectList)
	{
		bool validInt = currentObject -> TestIntersection(castRay, hitData);
		
		// If we have a valid intersection.
		if (validInt)
		{
			// Set the flag to indicate that we found an intersection.
			intersectionFound = true;
					
			// Compute the distance between the camera and the point of intersection.
			double dist = (hitData.poi - castRay.m_point1).norm();
					
			/* If this object is closer to the camera than any one that we have
				seen before, then store a reference to it. */
			if (dist < minDist)
			{
				minDist = dist;
				closestObject = currentObject;
				//closestIntPoint = intPoint;
				//closestLocalNormal = localNormal;
				//closestLocalColor = localColor;
				closestHitData = hitData;
			}
		}
	}
	
	return intersectionFound;
}

// Function to handle rendering a tile.
void qbRT::Scene::RenderTile(qbRT::DATA::tile *tile)
{

	// Loop over each pixel in the tile.
	qbVector3<double> pixelColor;
	
	for (int y=0; y<tile->ySize; ++y)
	{
		for (int x=0; x<tile->xSize; ++x)
		{
			pixelColor = RenderPixel(tile->x + x, tile->y + y, m_xSize, m_ySize);
			tile->rgbData.at(Sub2Ind(x, y, tile->xSize, tile->ySize)) = pixelColor;
		}
	}
	
	tile->renderComplete = true;
}

// Function to render an actual pixel.
qbVector3<double> qbRT::Scene::RenderPixel(int x, int y, int xSize, int ySize)
{
	std::shared_ptr<qbRT::ObjectBase> closestObject;	
	qbRT::Ray cameraRay;
	qbRT::DATA::hitData closestHitData;
	double xFact = 1.0 / (static_cast<double>(xSize) / 2.0);
	double yFact = 1.0 / (static_cast<double>(ySize) / 2.0);
	double minDist = 1e6;
	double maxDist = 0.0;
	qbVector3<double> outputColor {3};
	
	// Normalize the x and y coordinates.
	double normX = (static_cast<double>(x) * xFact) - 1.0;
	double normY = (static_cast<double>(y) * yFact) - 1.0;
			
	// Generate the ray for this pixel.
	m_camera.GenerateRay(normX, normY, cameraRay);
			
	// Test for intersections with all objects in the scene.
	bool intersectionFound = CastRay(cameraRay, closestObject, closestHitData);

	/* Compute the illumination for the closest object, assuming that there
		was a valid intersection. */
	if (intersectionFound)
	{
		// Check if the object has a material.
		if (closestHitData.hitObject -> m_hasMaterial)
		{
			// Use the material to compute the color.
			qbRT::MaterialBase::m_reflectionRayCount = 0;
			outputColor = closestHitData.hitObject -> m_pMaterial -> ComputeColor(	m_objectList, m_lightList,
																																							closestHitData.hitObject, closestHitData.poi,
																																							closestHitData.normal,
																																							closestHitData.localPOI,
																																							closestHitData.uvCoords, cameraRay);
		}
		else
		{
			// Use the basic method to compute the color.
			outputColor = qbRT::MaterialBase::ComputeDiffuseColor(m_objectList, m_lightList,
																																					closestHitData.hitObject, closestHitData.poi,
																																					closestHitData.normal, closestObject->m_baseColor);
		}
	}
	
	return outputColor;
}	

// Function to convert to a linear index.
int qbRT::Scene::Sub2Ind(int x, int y, int xSize, int ySize)
{
	if ((x < xSize) && (x >= 0) && (y < ySize) && (y >= 0))
		return (y * xSize) + x;
	else
		return -1;	
}

// Function to setup the scene (to be overriden)
void qbRT::Scene::SetupSceneObjects()
{

}








