/* ***********************************************************
	camera.hpp
	
	The camera class definition - A class to handle the camera
	and compute camera geometry.
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
	This code corresponds specifically to Episode 2 of the series,
	which may be found here:
	https://youtu.be/KBK6g6RFgdA
	
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

// camera.hpp

#ifndef CAMERA_H
#define CAMERA_H

#include "./qbLinAlg/qbVector.h"
#include "./qbLinAlg/qbVector2.hpp"
#include "./qbLinAlg/qbVector3.hpp"
#include "./qbLinAlg/qbVector4.hpp"
#include "ray.hpp"

namespace qbRT
{
	class Camera
	{
		public:
			// The default constructor.
			Camera();
			
			// Functions to set camera parameters.
			void SetPosition	(const qbVector3<double> &newPosition);
			void SetLookAt		(const qbVector3<double> &newLookAt);
			void SetUp				(const qbVector3<double> &upVector);
			void SetLength		(double newLength);
			void SetHorzSize	(double newSize);
			void SetAspect		(double newAspect);
			
			// Functions to return camera parameters.
			qbVector3<double>	GetPosition();
			qbVector3<double>	GetLookAt();
			qbVector3<double>	GetUp();
			qbVector3<double>	GetU();
			qbVector3<double>	GetV();
			qbVector3<double>	GetScreenCentre();
			double						GetLength();
			double						GetHorzSize();
			double						GetAspect();
			
			// Function to generate a ray.
			bool GenerateRay(float proScreenX, float proScreenY, qbRT::Ray &cameraRay);
			
			// Function to update the camera geometry.
			void UpdateCameraGeometry();
			
		private:
			qbVector3<double> m_cameraPosition	{3};
			qbVector3<double> m_cameraLookAt		{3};
			qbVector3<double> m_cameraUp				{3};
			double m_cameraLength;
			double m_cameraHorzSize;
			double m_cameraAspectRatio;
			
			qbVector3<double> m_alignmentVector				{3};
			qbVector3<double> m_projectionScreenU			{3};
			qbVector3<double> m_projectionScreenV			{3};
			qbVector3<double> m_projectionScreenCentre	{3};
			
	};
}

#endif
