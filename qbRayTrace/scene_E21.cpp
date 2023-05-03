/* ***********************************************************
	Scene_E21.cpp
	
	The Scene_E21 class implementation - A class to handle information
	about the Scene_E21.
	
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

// Scene_E21.cpp

#include <chrono>
#include "scene_E21.hpp"
#include "./qbMaterials/simplematerial.hpp"
#include "./qbMaterials/simplerefractive.hpp"
#include "./qbTextures/checker.hpp"
#include "./qbTextures/image.hpp"
#include "./qbTextures/gradient.hpp"
#include "./qbTextures/basicvalnoise.hpp"
#include "./qbTextures/basicnoise.hpp"
#include "./qbTextures/marble.hpp"
#include "./qbTextures/qbStone1.hpp"
#include "./qbLinAlg/qbMatrix33.hpp"
#include "./qbLinAlg/qbMatrix44.hpp"

// The constructor.
qbRT::Scene_E21::Scene_E21()
{
	SetupSceneObjects();
}

// Destructor.
qbRT::Scene_E21::~Scene_E21()
{

}

// Function to setup the scene.
void qbRT::Scene_E21::SetupSceneObjects()
{
	// **************************************************************************************
	// Configure the camera.
	// **************************************************************************************	
	m_camera.SetPosition(	qbVector3<double>{std::vector<double> {6.0, -10.0, -4.0}} );
	m_camera.SetLookAt	( qbVector3<double>{std::vector<double> {0.0, 0.0, 0.5}} );
	m_camera.SetUp			( qbVector3<double>{std::vector<double> {0.0, 0.0, 1.0}} );
	m_camera.SetHorzSize(1.0);
	m_camera.SetLength(3.0);
	m_camera.SetAspect(16.0 / 9.0);
	m_camera.UpdateCameraGeometry();	
	
	// **************************************************************************************
	// Setup ambient lightling.
	// **************************************************************************************		
	qbRT::MaterialBase::m_ambientColor = std::vector<double>{1.0, 1.0, 1.0};
	qbRT::MaterialBase::m_ambientIntensity = 0.25;

	// **************************************************************************************
	// Create the color maps.
	// **************************************************************************************	
	auto woodMap = std::make_shared<qbRT::Texture::ColorMap> (qbRT::Texture::ColorMap());
	woodMap -> SetStop(0.0, qbVector4<double>{std::vector<double>{200.0/255.0, 150.0/255.0, 120.0/255.0, 1.0}});
	woodMap -> SetStop(0.5, qbVector4<double>{std::vector<double>{100.0/255.0, 50.0/255.0, 30.0/255.0, 1.0}});
	woodMap -> SetStop(1.0, qbVector4<double>{std::vector<double>{200.0/255.0, 150.0/255.0, 120.0/255.0, 1.0}});	
	
	auto noiseMap = std::make_shared<qbRT::Texture::ColorMap> (qbRT::Texture::ColorMap());
	noiseMap -> SetStop(0.0, qbVector4<double>{std::vector<double>{1.0, 0.75, 0.0, 0.5}});
	noiseMap -> SetStop(0.5, qbVector4<double>{std::vector<double>{0.25, 0.25, 0.25, 0.25}});
	noiseMap -> SetStop(1.0, qbVector4<double>{std::vector<double>{0.0, 0.0, 0.0, 0.0}});

	auto fineMap = std::make_shared<qbRT::Texture::ColorMap> (qbRT::Texture::ColorMap());
	fineMap -> SetStop(0.0, qbVector4<double>{std::vector<double>{100.0/255.0, 50.0/255.0, 30.0/255.0, 0.25}});
	fineMap -> SetStop(0.2, qbVector4<double>{std::vector<double>{200.0/255.0, 150.0/255.0, 120.0/255.0, 0.25}});
	fineMap -> SetStop(0.4, qbVector4<double>{std::vector<double>{0.0, 0.0, 0.0, 0.25}});
	fineMap -> SetStop(1.0, qbVector4<double>{std::vector<double>{0.0, 0.0, 0.0, 0.0}});	

	// **************************************************************************************
	// Create the textures.
	// **************************************************************************************	
	// The spay image texture.
	auto sprayTexture = std::make_shared<qbRT::Texture::Image> (qbRT::Texture::Image());
	sprayTexture -> LoadImage("qbSpray1.bmp");
	sprayTexture -> SetTransform(	qbVector2<double>{std::vector<double>{0.0, 0.0}},
																0.0,
																qbVector2<double>{std::vector<double>{1.0, 1.0}} );
						
	// The box image texture.										
	auto boxTexture = std::make_shared<qbRT::Texture::Image> (qbRT::Texture::Image());
	boxTexture -> LoadImage("WoodBoxTexture.bmp");
	boxTexture -> SetTransform(	qbVector2<double>{std::vector<double>{0.0, 0.0}},
															0.0,
															qbVector2<double>{std::vector<double>{1.0, 1.0}} );																
	
	// The floor texture.
	auto floorTexture = std::make_shared<qbRT::Texture::Checker> (qbRT::Texture::Checker());
	floorTexture -> SetTransform(	qbVector2<double>{std::vector<double>{0.0, 0.0}},
																0.0,
																qbVector2<double>{std::vector<double>{8.0, 8.0}} );
	floorTexture -> SetColor(qbVector4<double>{std::vector<double>{0.2, 0.2, 0.2, 1.0}}, qbVector4<double>{std::vector<double>{0.4, 0.4, 0.4, 1.0}});
	
	// Textures for the wooden torus.
	auto qbWood = std::make_shared<qbRT::Texture::Marble> (qbRT::Texture::Marble());
	qbWood -> SetColorMap(woodMap);
	qbWood -> SetAmplitude(8.0, 1.0);
	qbWood -> SetScale(2.0, 10.0);
	qbWood -> SetSine(1.0, 8.0);
	qbWood -> SetMinMax(-1.0, 1.0);
	qbWood -> SetTransform(qbVector2<double>{std::vector<double>{0.0, 0.0}}, 0.0, qbVector2<double>{std::vector<double>{1.0, 1.0}});	
	
	auto dirtTexture1 = std::make_shared<qbRT::Texture::BasicValNoise> (qbRT::Texture::BasicValNoise());
	dirtTexture1 -> SetColorMap(noiseMap);
	dirtTexture1 -> SetAmplitude(2.0);
	dirtTexture1 -> SetScale(16.0);
	
	auto vertGrad1 = std::make_shared<qbRT::Texture::Gradient> (qbRT::Texture::Gradient());
	vertGrad1 -> SetStop(0.0, qbVector4<double>{std::vector<double>{1.0, 0.75, 0.0, 1.0}});
	vertGrad1 -> SetStop(0.5, qbVector4<double>{std::vector<double>{0.5, 0.5, 0.5, 0.25}});
	vertGrad1 -> SetStop(1.0, qbVector4<double>{std::vector<double>{0.5, 0.5, 0.5, 0.0}});
	vertGrad1 -> SetTransform(qbVector2<double>{std::vector<double>{0.0, 0.0}}, 0.0, qbVector2<double>{std::vector<double>{1.0, 1.0}});
											
	auto fineTexture = std::make_shared<qbRT::Texture::Marble> (qbRT::Texture::Marble());
	fineTexture -> SetColorMap(fineMap);
	fineTexture -> SetAmplitude(2.0, 1.0);
	fineTexture -> SetScale(20.0, 40.0);
	fineTexture -> SetSine(64.0, 128.0);
	fineTexture -> SetMinMax(-1.0, 1.0);
	fineTexture -> SetTransform(qbVector2<double>{std::vector<double>{0.0, 0.0}}, 0.0, qbVector2<double>{std::vector<double>{1.0, 1.0}});			
	
	// **************************************************************************************
	// Create and setup normal maps.
	// **************************************************************************************
	auto woodBoxNormal = std::make_shared<qbRT::Normal::Image> (qbRT::Normal::Image());
	woodBoxNormal -> LoadImage("WoodBoxNormal.bmp");
	woodBoxNormal -> SetTransform(	qbVector2<double>{std::vector<double>{0.0, 0.0}},
																	0.0,
																	qbVector2<double>{std::vector<double>{1.0, 1.0}} );
																	
	auto woodNorm1 = std::make_shared<qbRT::Normal::TextureNormal> (qbRT::Normal::TextureNormal());
	woodNorm1 -> AssignBaseTexture(qbWood);
	woodNorm1 -> m_scale = 0.0001;
	
	auto fineNorm1 = std::make_shared<qbRT::Normal::TextureNormal> (qbRT::Normal::TextureNormal());
	fineNorm1 -> AssignBaseTexture(fineTexture);
	fineNorm1 -> m_scale = 0.001;
	fineNorm1 -> m_reverse = false;				
	
	auto mirrorNorm = std::make_shared<qbRT::Normal::SimpleRough> (qbRT::Normal::SimpleRough());	
	mirrorNorm -> m_amplitudeScale = 0.01;										

	// **************************************************************************************
	// Create some materials.
	// **************************************************************************************
	auto floorMaterial = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());	
	floorMaterial -> m_baseColor = qbVector3<double>{std::vector<double>{1.0, 1.0, 1.0}};
	floorMaterial -> m_reflectivity = 0.25;
	floorMaterial -> m_shininess = 0.0;
	floorMaterial -> AssignTexture(floorTexture);
	
	auto sprayBodyMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	sprayBodyMat -> m_baseColor = qbVector3<double>{std::vector<double>{1.0, 1.0, 1.0}};
	sprayBodyMat -> m_reflectivity = 0.1;
	sprayBodyMat -> m_shininess = 16.0;;
	sprayBodyMat -> AssignTexture(sprayTexture);
	
	auto metalMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	metalMat -> m_baseColor = qbVector3<double>{std::vector<double>{0.5, 0.5, 0.5}};
	metalMat -> m_reflectivity = 0.5;
	metalMat -> m_shininess = 64.0;
	
	auto whitePlasticMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	whitePlasticMat -> m_baseColor = qbVector3<double>{std::vector<double>{1.0, 1.0, 1.0}};
	whitePlasticMat -> m_reflectivity = 0.0;
	whitePlasticMat -> m_shininess = 0.0;
	
	auto mirrorMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	mirrorMat -> m_baseColor = std::vector<double>{0.0, 0.0, 1.0};
	mirrorMat -> m_reflectivity = 0.5;
	mirrorMat -> m_shininess = 64.0;
	mirrorMat -> AssignNormalMap(mirrorNorm);
	
	auto mirrorMat2 = std::make_shared<qbRT::SimpleMaterial> (*mirrorMat);
	mirrorMat2 -> m_baseColor = std::vector<double>{1.0, 1.0, 0.0};
	
	auto boxMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	boxMat -> m_baseColor = std::vector<double>{1.0, 1.0, 0.0};
	boxMat -> m_reflectivity = 0.0;
	boxMat -> m_shininess = 32.0;
	boxMat -> AssignTexture(boxTexture);
	boxMat -> AssignNormalMap(woodBoxNormal);
	
	auto woodMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	woodMat -> m_baseColor = std::vector<double>{1.0, 1.0, 1.0};
	woodMat -> m_reflectivity = 0.0;
	woodMat -> m_shininess = 32.0;
	woodMat -> AssignTexture(qbWood);
	woodMat -> AssignTexture(fineTexture);
	woodMat -> AssignTexture(dirtTexture1);
	woodMat -> AssignTexture(vertGrad1);
	woodMat -> AssignNormalMap(woodNorm1);
	woodMat -> AssignNormalMap(fineNorm1);		
	
	// **************************************************************************************	
	// Create and setup objects.
	// **************************************************************************************
	auto floor = std::make_shared<qbRT::ObjPlane> (qbRT::ObjPlane());
	floor -> m_tag = "floor";
	floor -> m_isVisible = true;
	floor -> SetTransformMatrix(qbRT::GTform {	qbVector3<double>{std::vector<double>{0.0, 0.0, 0.5}},
																							qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}},
																							qbVector3<double>{std::vector<double>{6.0, 6.0, 1.0}}}	);	
	floor -> AssignMaterial(floorMaterial);	
	floor -> m_uvMapType = qbRT::uvPLANE;
	
	auto backWall = std::make_shared<qbRT::ObjPlane> (qbRT::ObjPlane());
	backWall -> m_tag = "backWall";
	backWall -> m_isVisible = true;
	backWall -> SetTransformMatrix(qbRT::GTform {	qbVector3<double>{std::vector<double>{0.0, 2.0, 0.0}},
																								qbVector3<double>{std::vector<double>{-M_PI/2.0, 0.0, 0.0}},
																								qbVector3<double>{std::vector<double>{4.0, 4.0, 1.0}}}	);	
	backWall -> AssignMaterial(mirrorMat);
	
	auto sideWall = std::make_shared<qbRT::ObjPlane> (*backWall);
	sideWall -> m_tag = "sideWall";
	sideWall -> SetTransformMatrix(qbRT::GTform {	qbVector3<double>{std::vector<double>{-2.0, 0.0, 0.0}},
																								qbVector3<double>{std::vector<double>{-M_PI/2.0, -M_PI/2.0, 0.0}},
																								qbVector3<double>{std::vector<double>{4.0, 4.0, 1.0}}}	);	
	sideWall -> AssignMaterial(mirrorMat2);

	double sprayX = 0.0;
	double sprayY = 0.0;
	auto sprayBody = std::make_shared<qbRT::Cylinder> (qbRT::Cylinder());
	sprayBody -> m_tag = "sprayBody";
	sprayBody -> m_isVisible = true;
	sprayBody -> SetTransformMatrix(qbRT::GTform {	qbVector3<double>{std::vector<double>{sprayX, sprayY, -0.5}},
																									qbVector3<double>{std::vector<double>{0.0, 0.0, M_PI/5.0}},
																									qbVector3<double>{std::vector<double>{0.4, 0.4, 1.0}}}	);
	sprayBody -> AssignMaterial(sprayBodyMat);
	sprayBody -> m_uvMapType = qbRT::uvCYLINDER;
	
	auto sprayTopCone = std::make_shared<qbRT::Cone> (qbRT::Cone());
	sprayTopCone -> m_tag = "sprayTopCone";
	sprayTopCone -> m_isVisible = true;
	sprayTopCone -> SetTransformMatrix(qbRT::GTform {	qbVector3<double>{std::vector<double>{sprayX, sprayY, -2.0}},
																										qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}},
																										qbVector3<double>{std::vector<double>{0.4, 0.4, 0.5}}}	);
	sprayTopCone -> AssignMaterial(metalMat);
	
	auto sprayTop = std::make_shared<qbRT::Cylinder> (qbRT::Cylinder());
	sprayTop -> m_tag = "sprayTop";
	sprayTop -> m_isVisible = true;
	sprayTop -> SetTransformMatrix(qbRT::GTform {	qbVector3<double>{std::vector<double>{sprayX, sprayY, -1.5}},
																								qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}},
																								qbVector3<double>{std::vector<double>{0.2, 0.2, 0.5}}}	);
	sprayTop -> AssignMaterial(whitePlasticMat);
	
	auto sprayCan = std::make_shared<qbRT::SHAPES::CompositeBase> (qbRT::SHAPES::CompositeBase());
	sprayCan -> m_tag = "sprayCan";
	sprayCan -> m_isVisible = true;
	sprayCan -> AddSubShape(sprayBody);
	sprayCan -> AddSubShape(sprayTopCone);
	sprayCan -> AddSubShape(sprayTop);
	sprayCan -> SetTransformMatrix(qbRT::GTform{	qbVector3<double>{std::vector<double>{1.0, -1.75, 0.0}},
																								qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}},
																								qbVector3<double>{std::vector<double>{1.0, 1.0, 1.0}}});
	
	auto box = std::make_shared<qbRT::Box> (qbRT::Box());
	box -> m_tag = "box";
	box -> m_isVisible = true;
	box -> SetTransformMatrix(qbRT::GTform {	qbVector3<double>{std::vector<double>{-1.0, -2.0, 0.0}},
																						qbVector3<double>{std::vector<double>{0.0, 0.0, -M_PI/6.0}},
																						qbVector3<double>{std::vector<double>{0.5, 0.5, 0.5}}}	);
	box -> AssignMaterial(boxMat);
	box -> m_uvMapType = qbRT::uvBOX;

	auto box2 = std::make_shared<qbRT::Box> (*box);
	box2 -> SetTransformMatrix(qbRT::GTform {	qbVector3<double>{std::vector<double>{-1.0, -0.75, -0.25}},
																						qbVector3<double>{std::vector<double>{M_PI/4.0, 0.0, M_PI/2.0}},
																						qbVector3<double>{std::vector<double>{0.5, 0.5, 0.5}}}	);
																						
	auto torus = std::make_shared<qbRT::RM::Torus> (qbRT::RM::Torus());
	torus -> m_tag = "torus";
	torus -> m_isVisible = true;
	torus -> SetRadii(0.7, 0.3);
	torus -> SetTransformMatrix(qbRT::GTform {	qbVector3<double>{std::vector<double>{2.5, -2.0, 0.2}},
																							qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}},
																							qbVector3<double>{std::vector<double>{1.0, 1.0, 1.0}}}	);
	torus -> AssignMaterial(woodMat);
	torus -> m_uvMapType = qbRT::uvSPHERE;

	// **************************************************************************************
	// Put the objects into the scene.	
	// **************************************************************************************
	m_objectList.push_back(sprayCan);
	m_objectList.push_back(box);
	m_objectList.push_back(box2);	
	m_objectList.push_back(floor);
	m_objectList.push_back(backWall);
	m_objectList.push_back(sideWall);
	m_objectList.push_back(torus);
	
	// **************************************************************************************	
	// Construct and setup the lights.
	// **************************************************************************************	
	auto leftLight = std::make_shared<qbRT::PointLight> (qbRT::PointLight());
	leftLight -> m_location = qbVector3<double> {std::vector<double> {0.0, -20.0, -20.0}};
	leftLight -> m_color = qbVector3<double> {std::vector<double> {1.0, 1.0, 1.0}};
	leftLight -> m_intensity = 0.33;
	
	auto rightLight = std::make_shared<qbRT::PointLight> (qbRT::PointLight());
	rightLight -> m_location = qbVector3<double> {std::vector<double> {8.0, -20.0, -20.0}};
	rightLight -> m_color = qbVector3<double> {std::vector<double> {1.0, 1.0, 1.0}};
	rightLight -> m_intensity = 0.33;
	
	auto topLight = std::make_shared<qbRT::PointLight> (qbRT::PointLight());
	topLight -> m_location = qbVector3<double> {std::vector<double> {0.0, 3.0, -20.0}};
	topLight -> m_color = qbVector3<double> {std::vector<double> {1.0, 1.0, 1.0}};
	topLight -> m_intensity = 0.33;
	
	m_lightList.push_back(leftLight);
	m_lightList.push_back(rightLight);
	m_lightList.push_back(topLight);
}











