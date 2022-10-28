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

// materialbase.hpp

#ifndef MATERIALBASE_H
#define MATERIALBASE_H

#include <memory>
#include "../qbNormals/normalbase.hpp"
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
										qbRT::DATA::hitData &closestHitData);
										
			// Function to assign a texture.
			void AssignTexture(const std::shared_ptr<qbRT::Texture::TextureBase> &inputTexture);
			
			// Function to assign a normal map.
			void AssignNormalMap(const std::shared_ptr<qbRT::Normal::NormalBase> &inputNormalMap);			
			
			// Function to return the color due to the textures at the given (u,v) coordinate.
			qbVector<double> GetTextureColor(const qbVector<double> &uvCoords);

			// *** Function to perturb the object normal to give the material normal.
			qbVector<double> PerturbNormal(const qbVector<double> &normal, const qbVector<double> &uvCoords, const qbVector<double> &upVector);			
			
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
			
			// *** List of normal maps assigned to this material.
			std::vector<std::shared_ptr<qbRT::Normal::NormalBase>> m_normalMapList;			
			
			// Flat to indicate whether at least one texture has been assigned.
			bool m_hasTexture = false;
			
			// *** Flag to indicate whether at least one normal map has been assigned.
			bool m_hasNormalMap = false;
		
			// *** Store the material normal at the current point.
			qbVector<double> m_localNormal;			
		
		private:
		
	};
}

#endif
