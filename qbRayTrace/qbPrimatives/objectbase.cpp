/* ***********************************************************
	objectbase.cpp
	
	The objectbase class implementation - A base class from which
	all other object classes will inherit.
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
	This code corresponds specifically to Episode 2 of the series,
	which may be found here:
	https://youtu.be/8fWZM8hCX5E
	
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

// objectbase.cpp

#include "objectbase.hpp"
#include <math.h>

#define EPSILON 1e-21f;

// Default constructor.
qbRT::ObjectBase::ObjectBase()
{

}

// The destructor.
qbRT::ObjectBase::~ObjectBase()
{

}

// Function to test for intersections.
//bool qbRT::ObjectBase::TestIntersection(const Ray &castRay, qbVector<double> &intPoint, qbVector<double> &localNormal, qbVector<double> &localColor)
bool qbRT::ObjectBase::TestIntersection(const Ray &castRay, qbRT::DATA::hitData_t &hitData)
{
	return false;
}

void qbRT::ObjectBase::SetTransformMatrix(const qbRT::GTform &transformMatrix)
{
	m_transformMatrix = transformMatrix;
}

qbRT::GTform qbRT::ObjectBase::GetTransformMatrix()
{
	return m_transformMatrix;
}

// Function to assign a material.
bool qbRT::ObjectBase::AssignMaterial(const std::shared_ptr<qbRT::MaterialBase> &objectMaterial)
{
	m_pMaterial = objectMaterial;
	m_hasMaterial = true;
	return m_hasMaterial;
}

// Function to test whether two floating-point numbers are close to being equal.
bool qbRT::ObjectBase::CloseEnough(const double f1, const double f2)
{
	return fabs(f1-f2) < EPSILON;
}






