/* ***********************************************************
	scene.cpp
	
	The scene class implementation - A class to handle information
	about the scene and rendering to an image.
	
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
	
***********************************************************/

// scene.cpp

#include "scene.hpp"
#include "./qbMaterials/simplematerial.hpp"
#include "./qbMaterials/simplerefractive.hpp"
#include "./qbTextures/checker.hpp"
#include "./qbTextures/image.hpp"
#include "./qbTextures/gradient.hpp"

// The constructor.
qbRT::Scene::Scene()
{
	// **************************************************************************************
	// Configure the camera.
	// **************************************************************************************	
	m_camera.SetPosition(	qbVector<double>{std::vector<double> {4.0, -8.0, -2.0}} );
	m_camera.SetLookAt	( qbVector<double>{std::vector<double> {-0.5, 0.0, 0.0}} );
	m_camera.SetUp			( qbVector<double>{std::vector<double> {0.0, 0.0, 1.0}} );
	m_camera.SetHorzSize(1.0);
	m_camera.SetAspect(16.0 / 9.0);
	m_camera.UpdateCameraGeometry();
	
	// **************************************************************************************
	// Setup ambient lightling.
	// **************************************************************************************		
	qbRT::MaterialBase::m_ambientColor = std::vector<double>{1.0, 1.0, 1.0};
	qbRT::MaterialBase::m_ambientIntensity = 0.2;

	// **************************************************************************************
	// Create some textures.
	// **************************************************************************************	
	auto floorTexture = std::make_shared<qbRT::Texture::Checker> (qbRT::Texture::Checker());
	floorTexture -> SetTransform(	qbVector<double>{std::vector<double>{0.0, 0.0}},
																0.0,
																qbVector<double>{std::vector<double>{16.0, 16.0}} );
	floorTexture -> SetColor(qbVector<double>{std::vector<double>{0.2, 0.2, 0.2, 1.0}}, qbVector<double>{std::vector<double>{0.4, 0.4, 0.4, 1.0}});
	
	auto gradientTexture = std::make_shared<qbRT::Texture::Gradient> (qbRT::Texture::Gradient());
	gradientTexture -> SetTransform(	qbVector<double>{std::vector<double>{0.0, 0.0}},
																		0.0,
																		qbVector<double>{std::vector<double>{1.0, 1.0}} );	
	gradientTexture -> SetStop(0.0, qbVector<double>{std::vector<double> {1.0, 0.0, 0.0, 1.0}});
	gradientTexture -> SetStop(0.5, qbVector<double>{std::vector<double> {0.0, 1.0, 0.0, 1.0}});
	gradientTexture -> SetStop(1.0, qbVector<double>{std::vector<double> {0.0, 0.0, 1.0, 1.0}});
	
	auto smallChecks1 = std::make_shared<qbRT::Texture::Checker> (qbRT::Texture::Checker());
	smallChecks1 -> SetTransform(	qbVector<double>{std::vector<double>{0.0, 0.0}},
																0.0,
																qbVector<double>{std::vector<double>{8.0, 8.0}} );
	smallChecks1 -> SetColor(qbVector<double>{std::vector<double>{1.0, 1.0, 1.0, 1.0}}, qbVector<double>{std::vector<double>{0.2, 0.2, 0.8, 1.0}});
	
	auto smallChecks2 = std::make_shared<qbRT::Texture::Checker> (qbRT::Texture::Checker());
	smallChecks2 -> SetTransform(	qbVector<double>{std::vector<double>{0.0, 0.0}},
																-M_PI/4.0,
																qbVector<double>{std::vector<double>{8.0, 8.0}} );
	smallChecks2 -> SetColor(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0, 1.0}}, qbVector<double>{std::vector<double>{1.0, 0.5, 0.1, 1.0}});	
	
	auto layeredChecks = std::make_shared<qbRT::Texture::Checker> (qbRT::Texture::Checker());
	layeredChecks -> SetTransform(	qbVector<double>{std::vector<double>{0.0, 0.0}},
																0.0,
																qbVector<double>{std::vector<double>{4.0, 4.0}} );
	layeredChecks -> SetColor(smallChecks1, smallChecks2);
	
	auto alphaGradient = std::make_shared<qbRT::Texture::Gradient> (qbRT::Texture::Gradient());
	alphaGradient -> SetTransform(	qbVector<double>{std::vector<double>{0.0, 0.0}},
																	M_PI/4.0,
																	qbVector<double>{std::vector<double>{1.0, 1.0}} );
	alphaGradient -> SetStop(0.0, qbVector<double>{std::vector<double>{0.0, 0.0, 1.0, 1.0}});
	alphaGradient -> SetStop(0.5, qbVector<double>{std::vector<double>{1.0, 1.0, 1.0, 0.0}});
	alphaGradient -> SetStop(1.0, qbVector<double>{std::vector<double>{1.0, 1.0, 0.0, 1.0}});	

	// **************************************************************************************
	// Create some materials.
	// **************************************************************************************
	auto floorMaterial = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());	
	floorMaterial -> m_baseColor = qbVector<double>{std::vector<double>{1.0, 1.0, 1.0}};
	floorMaterial -> m_reflectivity = 0.5;
	floorMaterial -> m_shininess = 0.0;
	floorMaterial -> AssignTexture(floorTexture);
	
	auto imageMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	imageMat -> m_baseColor = std::vector<double>{0.0, 0.0, 0.0};
	imageMat -> m_reflectivity = 0.2;
	imageMat -> m_shininess = 0.8;
	imageMat -> AssignTexture(gradientTexture);
	
	auto layeredMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	layeredMat -> m_reflectivity = 0.0;
	layeredMat -> m_shininess = 0.0;
	layeredMat -> AssignTexture(layeredChecks);
	layeredMat -> AssignTexture(alphaGradient);
	
	// **************************************************************************************	
	// Create and setup objects.
	// **************************************************************************************
	auto imageSphere = std::make_shared<qbRT::ObjSphere> (qbRT::ObjSphere());
	imageSphere -> m_tag = "imageSphere";
	imageSphere -> m_isVisible = true;
	imageSphere -> SetTransformMatrix(qbRT::GTform {	qbVector<double>{std::vector<double>{2.5, 0.0, 1.0}},
																										qbVector<double>{std::vector<double>{-M_PI/4.0, 0.0, 0.0}},
																										qbVector<double>{std::vector<double>{1.0, 1.0, 1.0}}}	);	
	imageSphere -> AssignMaterial(imageMat);
	
	auto imagePlane = std::make_shared<qbRT::ObjPlane> (qbRT::ObjPlane());
	imagePlane -> m_tag = "imagePlane";
	imagePlane -> m_isVisible = true;
	imagePlane -> SetTransformMatrix(qbRT::GTform {	qbVector<double>{std::vector<double>{-1.0, 0.0, 0.0}},
																									qbVector<double>{std::vector<double>{-M_PI/2.0, 0.0, 0.0}},
																									qbVector<double>{std::vector<double>{2.0, 2.0, 1.0}}}	);
	imagePlane -> AssignMaterial(layeredMat);
	
	auto imageBox = std::make_shared<qbRT::Box> (qbRT::Box());
	imageBox -> m_tag = "imageBox";
	imageBox -> m_isVisible = true;
	imageBox -> SetTransformMatrix(qbRT::GTform {	qbVector<double>{std::vector<double>{-5.0, 0.0, 1.0}},
																								qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
																								qbVector<double>{std::vector<double>{1.0, 1.0, 1.0}}}	);	
	imageBox -> AssignMaterial(imageMat);
	
	auto floor = std::make_shared<qbRT::ObjPlane> (qbRT::ObjPlane());
	floor -> m_tag = "floor";
	floor -> m_isVisible = true;
	floor -> SetTransformMatrix(qbRT::GTform {	qbVector<double>{std::vector<double>{0.0, 0.0, 2.0}},
																							qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
																							qbVector<double>{std::vector<double>{16.0, 16.0, 1.0}}}	);	
	floor -> AssignMaterial(floorMaterial);
	

	// **************************************************************************************
	// Put the objects into the scene.	
	// **************************************************************************************
	m_objectList.push_back(imageSphere);
	m_objectList.push_back(imagePlane);
	m_objectList.push_back(imageBox);
	m_objectList.push_back(floor);
	
	// **************************************************************************************	
	// Construct and setup the lights.
	// **************************************************************************************	
	m_lightList.push_back(std::make_shared<qbRT::PointLight> (qbRT::PointLight()));
	m_lightList.at(0) -> m_location = qbVector<double> {std::vector<double> {3.0, -10.0, -5.0}};
	m_lightList.at(0) -> m_color = qbVector<double> {std::vector<double> {1.0, 1.0, 1.0}};
	m_lightList.at(0) -> m_intensity = 4.0;
	
	m_lightList.push_back(std::make_shared<qbRT::PointLight> (qbRT::PointLight()));
	m_lightList.at(1) -> m_location = qbVector<double> {std::vector<double> {0.0, -10.0, -5.0}};
	m_lightList.at(1) -> m_color = qbVector<double> {std::vector<double> {1.0, 1.0, 1.0}};
	m_lightList.at(1) -> m_intensity = 2.0;

}

// Function to perform the rendering.
bool qbRT::Scene::Render(qbImage &outputImage)
{
	// Get the dimensions of the output image.
	int xSize = outputImage.GetXSize();
	int ySize = outputImage.GetYSize();
	
	// Loop over each pixel in our image.
	qbRT::Ray cameraRay;
	qbVector<double> intPoint			(3);
	qbVector<double> localNormal	(3);
	qbVector<double> localColor		(3);
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
			qbVector<double> closestIntPoint		{3};
			qbVector<double> closestLocalNormal	{3};
			qbVector<double> closestLocalColor	{3};
			bool intersectionFound = CastRay(cameraRay, closestObject, closestIntPoint, closestLocalNormal, closestLocalColor);
			
			/* Compute the illumination for the closest object, assuming that there
				was a valid intersection. */
			if (intersectionFound)
			{
				// Check if the object has a material.
				if (closestObject -> m_hasMaterial)
				{
					// Use the material to compute the color.
					qbRT::MaterialBase::m_reflectionRayCount = 0;
					qbVector<double> color = closestObject -> m_pMaterial -> ComputeColor(	m_objectList, m_lightList,
																																									closestObject, closestIntPoint,
																																									closestLocalNormal, cameraRay);
					outputImage.SetPixel(x, y, color.GetElement(0), color.GetElement(1), color.GetElement(2));
				}
				else
				{
					// Use the basic method to compute the color.
					qbVector<double> matColor = qbRT::MaterialBase::ComputeDiffuseColor(m_objectList, m_lightList,
																																							closestObject, closestIntPoint,
																																							closestLocalNormal, closestObject->m_baseColor);
					outputImage.SetPixel(x, y, matColor.GetElement(0), matColor.GetElement(1), matColor.GetElement(2));
				}
			}
		}
	}
	
	std::cout << std::endl;
	return true;
}

// Function to cast a ray into the scene.
bool qbRT::Scene::CastRay(	qbRT::Ray &castRay, std::shared_ptr<qbRT::ObjectBase> &closestObject,
														qbVector<double> &closestIntPoint, qbVector<double> &closestLocalNormal,
														qbVector<double> &closestLocalColor)
{
	qbVector<double> intPoint			{3};
	qbVector<double> localNormal	{3};
	qbVector<double> localColor		{3};
	double minDist = 1e6;
	bool intersectionFound = false;
	for (auto currentObject : m_objectList)
	{
		bool validInt = currentObject -> TestIntersection(castRay, intPoint, localNormal, localColor);
		
		// If we have a valid intersection.
		if (validInt)
		{
			// Set the flag to indicate that we found an intersection.
			intersectionFound = true;
					
			// Compute the distance between the camera and the point of intersection.
			double dist = (intPoint - castRay.m_point1).norm();
					
			/* If this object is closer to the camera than any one that we have
				seen before, then store a reference to it. */
			if (dist < minDist)
			{
				minDist = dist;
				closestObject = currentObject;
				closestIntPoint = intPoint;
				closestLocalNormal = localNormal;
				closestLocalColor = localColor;
			}
		}
	}
	
	return intersectionFound;
}












