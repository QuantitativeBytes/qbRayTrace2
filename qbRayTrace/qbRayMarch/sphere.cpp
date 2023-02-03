/* ***********************************************************
	sphere.cpp
	
	A class that implements a ray marched sphere shape.
	
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

#include "sphere.hpp"

// Constructor.
qbRT::RM::Sphere::Sphere()
{
	// Create a function pointer for our object function.
	std::function<double(qbVector3<double>*, qbVector3<double>*)> f = [=](qbVector3<double> *location, qbVector3<double> *parms)
	{
  	return this->ObjectFcn(location, parms);
	};
	
	// Assign the object function.
	SetObjectFcn(f);

	// Modify the bounding box.
	m_boundingBox.SetTransformMatrix(qbRT::GTform { qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}},
																									qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}},
																									qbVector3<double>{std::vector<double>{1.2, 1.2, 1.2}} } );

}

// Destructor.
qbRT::RM::Sphere::~Sphere()
{

}

// The private object function.
double qbRT::RM::Sphere::ObjectFcn(qbVector3<double> *location, qbVector3<double> *parms)
{
	qbVector3<double> center = std::vector<double>{0.0, 0.0, 0.0};
	qbVector3<double> intParms = std::vector<double>{1.0, 0.0, 0.0};
	return qbRT::RM::SDF::Sphere(*location, center, intParms);
}
