/* ***********************************************************
	simplerefractive.hpp
	
	The SimpleRefractive class definition - A class for transparent
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
	Copyright (c) 2021 Michael Bennett
	
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

#ifndef SIMPLEREFRACTIVE_H
#define SIMPLEREFRACTIVE_H

#include "materialbase.hpp"

namespace qbRT
{
	class SimpleRefractive : public MaterialBase
	{
		public:
			// Constructor / destructor.
			SimpleRefractive();
			virtual ~SimpleRefractive() override;
			
			// Function to return the color.
			virtual qbVector3<double> ComputeColor(	const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
																							const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
																							const std::shared_ptr<qbRT::ObjectBase> &currentObject,
																							const qbVector3<double> &intPoint, const qbVector3<double> &localNormal,
																							const qbVector3<double> &localPOI, const qbVector2<double> &uvCoords,
																							const qbRT::Ray &cameraRay) override;
																							
			// Function to compute specular highlights.
			qbVector3<double> ComputeSpecular(	const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
																				const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
																				const qbVector3<double> &intPoint, const qbVector3<double> &localNormal,
																				const qbRT::Ray &cameraRay);
																				
		 	// Function to compute translucency.
		 	qbVector3<double> ComputeTranslucency(	const std::vector<std::shared_ptr<qbRT::ObjectBase>> &objectList,
																						const std::vector<std::shared_ptr<qbRT::LightBase>> &lightList,
																						const std::shared_ptr<qbRT::ObjectBase> &currentObject,
																						const qbVector3<double> &intPoint, const qbVector3<double> &localNormal,
																						const qbRT::Ray &incidentRay);
																						
		public:
			qbVector3<double> m_baseColor {std::vector<double> {1.0, 0.0, 1.0}};
			double m_reflectivity = 0.0;
			double m_shininess = 0.0;
			double m_translucency = 0.0;
			double m_ior = 1.0;
																						
	};
}

#endif
