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
	// **************************************************************************************
	// Configure the camera.
	// **************************************************************************************	
	m_camera.SetPosition(	qbVector3<double>{std::vector<double> {4.0, -8.0, -4.0}} );
	m_camera.SetLookAt	( qbVector3<double>{std::vector<double> {-0.5, 0.0, 0.0}} );
	m_camera.SetUp			( qbVector3<double>{std::vector<double> {0.0, 0.0, 1.0}} );
	m_camera.SetHorzSize(1.0);
	m_camera.SetLength(3.0);
	m_camera.SetAspect(16.0 / 9.0);
	m_camera.UpdateCameraGeometry();	
	
	// **************************************************************************************
	// Setup ambient lightling.
	// **************************************************************************************		
	qbRT::MaterialBase::m_ambientColor = std::vector<double>{1.0, 1.0, 1.0};
	qbRT::MaterialBase::m_ambientIntensity = 0.0;

	// **************************************************************************************
	// Create some color maps.
	// **************************************************************************************	
	auto noiseMap = std::make_shared<qbRT::Texture::ColorMap> (qbRT::Texture::ColorMap());
	noiseMap -> SetStop(0.0, qbVector4<double>{std::vector<double>{1.0, 0.4, 0.0, 1.0}});
	noiseMap -> SetStop(0.5, qbVector4<double>{std::vector<double>{0.2, 0.4, 0.8, 1.0}});
	noiseMap -> SetStop(1.0, qbVector4<double>{std::vector<double>{1.0, 0.8, 0.0, 1.0}});
	
	auto cloudMap = std::make_shared<qbRT::Texture::ColorMap> (qbRT::Texture::ColorMap());
	cloudMap -> SetStop(0.0, qbVector4<double>{std::vector<double>{0.2, 0.4, 0.8, 1.0}});
	cloudMap -> SetStop(0.75, qbVector4<double>{std::vector<double>{1.0, 1.0, 1.0, 1.0}});
	cloudMap -> SetStop(1.0, qbVector4<double>{std::vector<double>{0.7, 0.7, 0.7, 1.0}});
	
	auto marbleMap = std::make_shared<qbRT::Texture::ColorMap> (qbRT::Texture::ColorMap());
	marbleMap -> SetStop(0.0, qbVector4<double>{std::vector<double>{1.0, 1.0, 1.0, 1.0}});
	marbleMap -> SetStop(0.2, qbVector4<double>{std::vector<double>{1.0, 1.0, 1.0, 1.0}});
	marbleMap -> SetStop(0.5, qbVector4<double>{std::vector<double>{1.0, 0.4, 0.0, 1.0}});
	marbleMap -> SetStop(0.8, qbVector4<double>{std::vector<double>{1.0, 1.0, 1.0, 1.0}});
	marbleMap -> SetStop(1.0, qbVector4<double>{std::vector<double>{1.0, 1.0, 1.0, 1.0}});
	
	auto candyMap = std::make_shared<qbRT::Texture::ColorMap> (qbRT::Texture::ColorMap());
	candyMap -> SetStop(0.0, qbVector4<double>{std::vector<double>{1.0, 1.0, 1.0, 1.0}});
	candyMap -> SetStop(0.5, qbVector4<double>{std::vector<double>{1.0, 0.0, 0.0, 1.0}});
	candyMap -> SetStop(1.0, qbVector4<double>{std::vector<double>{1.0, 1.0, 1.0, 1.0}});
	
	auto woodMap = std::make_shared<qbRT::Texture::ColorMap> (qbRT::Texture::ColorMap());
	woodMap -> SetStop(0.0, qbVector4<double>{std::vector<double>{200.0/255.0, 150.0/255.0, 120.0/255.0, 1.0}});
	woodMap -> SetStop(0.5, qbVector4<double>{std::vector<double>{100.0/255.0, 50.0/255.0, 30.0/255.0, 1.0}});
	woodMap -> SetStop(1.0, qbVector4<double>{std::vector<double>{200.0/255.0, 150.0/255.0, 120.0/255.0, 1.0}});
	

	// **************************************************************************************
	// Create some textures.
	// **************************************************************************************	
	
	// *** An example image texture.
	auto imageTexture = std::make_shared<qbRT::Texture::Image> (qbRT::Texture::Image());
	imageTexture -> LoadImage("Voronoi.bmp");
	imageTexture -> SetTransform(	qbVector2<double>{std::vector<double>{0.0, 0.0}},
																0.0,
																qbVector2<double>{std::vector<double>{1.0, 1.0}} );
	
	
	auto floorTexture = std::make_shared<qbRT::Texture::Checker> (qbRT::Texture::Checker());
	floorTexture -> SetTransform(	qbVector2<double>{std::vector<double>{0.0, 0.0}},
																0.0,
																qbVector2<double>{std::vector<double>{16.0, 16.0}} );
	floorTexture -> SetColor(qbVector4<double>{std::vector<double>{0.2, 0.2, 0.2, 1.0}}, qbVector4<double>{std::vector<double>{0.4, 0.4, 0.4, 1.0}});
	
	// An instance of the stone texture.
	auto stoneTexture = std::make_shared<qbRT::Texture::qbStone1> (qbRT::Texture::qbStone1());
	stoneTexture -> SetTransform( qbVector2<double>{std::vector<double>{0.0, 0.0}},
																0.0,
																qbVector2<double>{std::vector<double>{4.0, 4.0}} );
	
	// Value noise texture from Episode 15.
	auto valNoiseTexture = std::make_shared<qbRT::Texture::BasicValNoise> (qbRT::Texture::BasicValNoise());
	valNoiseTexture -> SetColorMap(noiseMap);
	valNoiseTexture -> SetAmplitude(2.0);
	valNoiseTexture -> SetScale(16.0);	
	
	// qbMarble...
	auto qbMarble = std::make_shared<qbRT::Texture::Marble> (qbRT::Texture::Marble());
	qbMarble -> SetColorMap(marbleMap);
	qbMarble -> SetAmplitude(4.0, 2.0);
	qbMarble -> SetScale(6.0, 40.0);
	qbMarble -> SetSine(1.0, 4.0);
	qbMarble -> SetMinMax(-1.0, 1.0);
	
	// qbCloud...
	auto qbCloud = std::make_shared<qbRT::Texture::BasicNoise> (qbRT::Texture::BasicNoise());
	qbCloud -> SetColorMap(cloudMap);
	qbCloud -> SetAmplitude(12.0);
	qbCloud -> SetScale(10);
	
	// Spiral...
	auto qbSpiral = std::make_shared<qbRT::Texture::Marble> (qbRT::Texture::Marble());
	qbSpiral -> SetColorMap(candyMap);
	qbSpiral -> SetAmplitude(0.0, 0.0);
	qbSpiral -> SetScale(1.0, 10.0);
	qbSpiral -> SetSine(1.0, 8.0);
	qbSpiral -> SetMinMax(-1.0, 1.0);
	qbSpiral -> SetTransform(qbVector2<double>{std::vector<double>{0.0, 0.0}}, 0.0, qbVector2<double>{std::vector<double>{1.0, 1.0}});
	
	auto qbWood = std::make_shared<qbRT::Texture::Marble> (qbRT::Texture::Marble());
	qbWood -> SetColorMap(woodMap);
	qbWood -> SetAmplitude(8.0, 1.0);
	qbWood -> SetScale(2.0, 10.0);
	qbWood -> SetSine(1.0, 8.0);
	qbWood -> SetMinMax(-1.0, 1.0);
	qbWood -> SetTransform(qbVector2<double>{std::vector<double>{0.0, 0.0}}, 0.0, qbVector2<double>{std::vector<double>{1.0, 1.0}});	
	
	// **************************************************************************************
	// Create and setup a simple normal map.
	// **************************************************************************************	
	auto normMap = std::make_shared<qbRT::Normal::TextureNormal> (qbRT::Normal::TextureNormal());
	normMap -> AssignBaseTexture(stoneTexture);
	normMap -> m_scale = 0.015;
	
	// *** An image based normal map.
	auto imageNormal = std::make_shared<qbRT::Normal::Image> (qbRT::Normal::Image());
	imageNormal -> LoadImage("Voronoi_normal.bmp");
	imageNormal -> SetTransform(	qbVector2<double>{std::vector<double>{0.0, 0.0}},
																0.0,
																qbVector2<double>{std::vector<double>{1.0, 1.0}} );

	// **************************************************************************************
	// Create some materials.
	// **************************************************************************************
	auto floorMaterial = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());	
	floorMaterial -> m_baseColor = qbVector3<double>{std::vector<double>{1.0, 1.0, 1.0}};
	floorMaterial -> m_reflectivity = 0.5;
	floorMaterial -> m_shininess = 0.0;
	floorMaterial -> AssignTexture(imageTexture);
	floorMaterial -> AssignNormalMap(imageNormal);
	
	// *** The stone material.
	auto stoneMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	stoneMat -> m_baseColor = std::vector<double>{1.0, 1.0, 1.0};
	stoneMat -> m_reflectivity = 0.35;
	stoneMat -> m_shininess = 32.0;
	stoneMat -> AssignTexture(stoneTexture);
	stoneMat -> AssignNormalMap(normMap);		
	
	auto valNoiseMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	valNoiseMat -> m_baseColor = std::vector<double>{1.0, 1.0, 1.0};
	valNoiseMat -> m_reflectivity = 0.2;
	valNoiseMat -> m_shininess = 32.0;
	valNoiseMat -> AssignTexture(valNoiseTexture);
	
	auto qbMarbleMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	qbMarbleMat -> m_baseColor = std::vector<double>{1.0, 1.0, 1.0};
	qbMarbleMat -> m_reflectivity = 0.05;
	qbMarbleMat -> m_shininess = 32.0;
	qbMarbleMat -> AssignTexture(qbMarble);
	
	auto cloudMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	cloudMat -> m_baseColor = std::vector<double>{1.0, 1.0, 1.0};
	cloudMat -> m_reflectivity = 0.05;
	cloudMat -> m_shininess = 32.0;
	cloudMat -> AssignTexture(qbCloud);	
	
	auto candyMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	candyMat -> m_baseColor = std::vector<double>{1.0, 1.0, 1.0};
	candyMat -> m_reflectivity = 0.05;
	candyMat -> m_shininess = 32.0;
	candyMat -> AssignTexture(qbSpiral);		
	
	auto woodMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	woodMat -> m_baseColor = std::vector<double>{1.0, 1.0, 1.0};
	woodMat -> m_reflectivity = 0.05;
	woodMat -> m_shininess = 32.0;
	woodMat -> AssignTexture(qbWood);		
	
	// **************************************************************************************	
	// Create and setup objects.
	// **************************************************************************************
	auto sphere1 = std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere());
	sphere1 -> m_tag = "sphere1";
	sphere1 -> m_isVisible = true;
	sphere1 -> SetTransformMatrix(qbRT::GTform	{	qbVector3<double>{std::vector<double>{-0.5, 0.0, -0.75}}, 
																								qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}}, 
																								qbVector3<double>{std::vector<double>{0.5, 0.5, 0.5}}	});
	sphere1 -> AssignMaterial(qbMarbleMat);
	
	auto sphere2 = std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere());
	sphere2 -> m_tag = "sphere2";
	sphere2 -> m_isVisible = true;
	sphere2 -> SetTransformMatrix(qbRT::GTform	{	qbVector3<double>{std::vector<double>{0.5, 0.0, -0.75}}, 
																								qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}}, 
																								qbVector3<double>{std::vector<double>{0.5, 0.5, 0.5}}	});
	sphere2 -> AssignMaterial(cloudMat);	
	
	auto sphere3 = std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere());
	sphere3 -> m_tag = "sphere3";
	sphere3 -> m_isVisible = true;
	sphere3 -> SetTransformMatrix(qbRT::GTform	{	qbVector3<double>{std::vector<double>{1.0, 0.0, 0.0}}, 
																								qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}}, 
																								qbVector3<double>{std::vector<double>{0.5, 0.5, 0.5}}	});
	sphere3 -> AssignMaterial(valNoiseMat);		
	
	auto sphere4 = std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere());
	sphere4 -> m_tag = "sphere4";
	sphere4 -> m_isVisible = true;
	sphere4 -> SetTransformMatrix(qbRT::GTform	{	qbVector3<double>{std::vector<double>{-1.0, 0.0, 0.0}}, 
																								qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}}, 
																								qbVector3<double>{std::vector<double>{0.5, 0.5, 0.5}}	});
	sphere4 -> AssignMaterial(candyMat);	
	
	auto sphere5 = std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere());
	sphere5 -> m_tag = "sphere5";
	sphere5 -> m_isVisible = true;
	sphere5 -> SetTransformMatrix(qbRT::GTform	{	qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}}, 
																								qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}}, 
																								qbVector3<double>{std::vector<double>{0.5, 0.5, 0.5}}	});
	sphere5 -> AssignMaterial(woodMat);			
	
	auto torus = std::make_shared<qbRT::RM::Torus> (qbRT::RM::Torus());
	torus -> SetRadii(0.7, 0.3);
	torus -> SetTransformMatrix(qbRT::GTform	{	qbVector3<double>{std::vector<double>{0.0, -1.25, 0.5}}, 
																							qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}}, 
																							qbVector3<double>{std::vector<double>{1.0, 1.0, 1.0}}	});
	torus -> AssignMaterial(candyMat);
	torus -> m_uvMapType = qbRT::uvSPHERE;
	
	auto floor = std::make_shared<qbRT::ObjPlane> (qbRT::ObjPlane());
	floor -> m_tag = "floor";
	floor -> m_isVisible = true;
	floor -> SetTransformMatrix(qbRT::GTform {	qbVector3<double>{std::vector<double>{0.0, 0.0, 0.5}},
																							qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}},
																							qbVector3<double>{std::vector<double>{4.0, 4.0, 1.0}}}	);	
	floor -> AssignMaterial(floorMaterial);
	floor -> m_uvMapType = qbRT::uvPLANE;	

	// **************************************************************************************
	// Put the objects into the scene.	
	// **************************************************************************************
	m_objectList.push_back(sphere1);
	m_objectList.push_back(sphere2);
	m_objectList.push_back(sphere3);
	m_objectList.push_back(sphere4);
	m_objectList.push_back(sphere5);
	m_objectList.push_back(torus);
	m_objectList.push_back(floor);
	
	// **************************************************************************************	
	// Construct and setup the lights.
	// **************************************************************************************	
	auto leftLight = std::make_shared<qbRT::PointLight> (qbRT::PointLight());
	leftLight -> m_location = qbVector3<double> {std::vector<double> {-8.0, -20.0, -10.0}};
	leftLight -> m_color = qbVector3<double> {std::vector<double> {1.0, 1.0, 1.0}};
	leftLight -> m_intensity = 4.0;
	
	auto rightLight = std::make_shared<qbRT::PointLight> (qbRT::PointLight());
	rightLight -> m_location = qbVector3<double> {std::vector<double> {8.0, -20.0, -10.0}};
	rightLight -> m_color = qbVector3<double> {std::vector<double> {1.0, 1.0, 1.0}};
	rightLight -> m_intensity = 6.0;
	
	auto topLight = std::make_shared<qbRT::PointLight> (qbRT::PointLight());
	topLight -> m_location = qbVector3<double> {std::vector<double> {0.0, 0.0, -10.0}};
	topLight -> m_color = qbVector3<double> {std::vector<double> {1.0, 1.0, 1.0}};
	topLight -> m_intensity = 4.0;
	
	m_lightList.push_back(leftLight);
	m_lightList.push_back(rightLight);
	//m_lightList.push_back(topLight);

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
	qbRT::Ray cameraRay;
	qbVector3<double> intPoint			(3);
	qbVector3<double> localNormal	(3);
	qbVector3<double> localColor		(3);
	double xFact = 1.0 / (static_cast<double>(xSize) / 2.0);
	double yFact = 1.0 / (static_cast<double>(ySize) / 2.0);
	double minDist = 1e6;
	double maxDist = 0.0;
	for (int y=0; y<ySize; ++y)
	{
		// Display progress.
		std::cout << "Processing line " << y << " of " << ySize << "." << " \r";
		std::cout.flush();
		
		for (int x=0; x<xSize; ++x)
		{
			// Normalize the x and y coordinates.
			double normX = (static_cast<double>(x) * xFact) - 1.0;
			double normY = (static_cast<double>(y) * yFact) - 1.0;
			
			// Generate the ray for this pixel.
			m_camera.GenerateRay(normX, normY, cameraRay);
			
			// Test for intersections with all objects in the scene.
			std::shared_ptr<qbRT::ObjectBase> closestObject;
			qbVector3<double> closestIntPoint		{3};
			qbVector3<double> closestLocalNormal	{3};
			qbVector3<double> closestLocalColor	{3};
			qbRT::DATA::hitData closestHitData;
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
					qbVector3<double> color = closestHitData.hitObject -> m_pMaterial -> ComputeColor(	m_objectList, m_lightList,
																																														closestHitData.hitObject, closestHitData.poi,
																																														closestHitData.normal, cameraRay);
					outputImage.SetPixel(x, y, color.GetElement(0), color.GetElement(1), color.GetElement(2));
				}
				else
				{
					// Use the basic method to compute the color.
					qbVector3<double> matColor = qbRT::MaterialBase::ComputeDiffuseColor(m_objectList, m_lightList,
																																							closestHitData.hitObject, closestHitData.poi,
																																							closestHitData.normal, closestObject->m_baseColor);
					outputImage.SetPixel(x, y, matColor.GetElement(0), matColor.GetElement(1), matColor.GetElement(2));
				}
			}
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












