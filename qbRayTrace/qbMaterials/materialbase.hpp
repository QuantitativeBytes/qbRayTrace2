/* ***********************************************************
	materialbase.hpp
	
	The material base class definition - A class for handling 
	materials.
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
	The whole series may be found on the QuantitativeBytes 
	YouTube channel at:
	www.youtube.com/c/QuantitativeBytes
	
	GPLv3 LICENSE
	Copyright (c) 2022 Michael Bennett
	
***********************************************************/

// materialbase.hpp

#ifndef MATERIALBASE_H
#define MATERIALBASE_H

#include <memory>
#include "../qbTextures/texturebase.hpp"
#include "../qbPrimatives/objectbase.hpp"
#include "../qbLights/lightbase.hpp"
#include "../qbLinAlg/qbVector.h"
#include "../ray.hpp"

namespace qbRT
{
	class MaterialBase
	{
		public:
			MaterialBase();
			virtual ~MaterialBase();
			
			// Function to return the color of the material.
			virtual qbVector<double> ComputeColor(	const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
																							const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
																							const std::shared_ptr<qbRT::ObjectBase> &currentObject,
																							const qbVector<double> &intPoint, const qbVector<double> &localNormal,
																							const qbRT::Ray &cameraRay);
																							
			// Function to compute diffuse color.
			static qbVector<double> ComputeDiffuseColor(	const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
																										const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
																										const std::shared_ptr<qbRT::ObjectBase> &currentObject,
																										const qbVector<double> &intPoint, const qbVector<double> &localNormal,
																										const qbVector<double> &baseColor);
																										
			// Function to compute the reflection color.
			qbVector<double> ComputeReflectionColor(	const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
																								const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
																								const std::shared_ptr<qbRT::ObjectBase> &currentObject,
																								const qbVector<double> &intPoint, const qbVector<double> &localNormal,
																								const qbRT::Ray &incidentRay);
																										
			// Function to cast a ray into the scene.
			bool CastRay(	const qbRT::Ray &castRay, const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
										const std::shared_ptr<qbRT::ObjectBase> &thisObject,
										std::shared_ptr<qbRT::ObjectBase> &closestObject,
										qbVector<double> &closestIntPoint, qbVector<double> &closestLocalNormal,
										qbVector<double> &closestLocalColor);
										
			// Function to assign a texture.
			void AssignTexture(const std::shared_ptr<qbRT::Texture::TextureBase> &inputTexture);
			
			// Function to return the color due to the textures at the given (u,v) coordinate.
			qbVector<double> GetTextureColor(const qbVector<double> &uvCoords);
			
			// Function to blend RGBA colors (blends into color1).
			void BlendColors(qbVector<double> &color1, const qbVector<double> &color2);			
										
		public:
			// Counter for the number of relection rays.
			inline static int m_maxReflectionRays;
			inline static int m_reflectionRayCount;
			
			// The ambient lighting conditions.
			inline static qbVector<double> m_ambientColor {std::vector<double> {1.0, 1.0, 1.0}};
			inline static double m_ambientIntensity = 0.2;
			
			// List of texures assigned to this material.
			std::vector<std::shared_ptr<qbRT::Texture::TextureBase>> m_textureList;
			
			// Flat to indicate whether at least one texture has been assigned.
			bool m_hasTexture = false;
		
		private:
		
	};
}

#endif
