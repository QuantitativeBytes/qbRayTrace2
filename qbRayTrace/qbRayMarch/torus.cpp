/* ***********************************************************
	torus.cpp
	
	A class that implements a ray marched torus shape.
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
	The whole series may be found on the QuantitativeBytes 
	YouTube channel at:
	www.youtube.com/c/QuantitativeBytes
	
	GPLv3 LICENSE
	
***********************************************************/
#include "torus.hpp"

qbRT::RM::Torus::Torus()
{
	// Create a function pointer for our object function.
	std::function<double(qbVector<double>*, qbVector<double>*)> f = [=](qbVector<double> *location, qbVector<double> *parms)
	{
  	return this->ObjectFcn(location, parms);
	};
	
	// Assign the object function.
	SetObjectFcn(f);

	// Modify the bounding box.
	m_boundingBox.SetTransformMatrix(qbRT::GTform { qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
																									qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
																									qbVector<double>{std::vector<double>{1.3, 1.3, 1.3}} } );
}

qbRT::RM::Torus::~Torus()
{

}

// Function to set the radii.
void qbRT::RM::Torus::SetRadii(double r1, double r2)
{
	m_parms.SetElement(0, r1);
	m_parms.SetElement(1, r2);
	UpdateBounds();
}

// Function to update the bounding box.
void qbRT::RM::Torus::UpdateBounds()
{
	m_boundingBox.SetTransformMatrix(qbRT::GTform { qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
																									qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
																									qbVector<double>{std::vector<double>{m_r1+m_r2+0.3, m_r1+m_r2+0.3, m_r2 + 0.2}} } );	
}

// The private object function.
double qbRT::RM::Torus::ObjectFcn(qbVector<double> *location, qbVector<double> *parms)
{	
	qbVector<double> center = std::vector<double>{0.0, 0.0, 0.0};
	return qbRT::RM::SDF::Torus(*location, center, *parms);	

}
