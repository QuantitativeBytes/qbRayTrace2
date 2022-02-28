/* ***********************************************************
	checker.cpp
	
	The checker class implementation - The 'classic' ray tracer
	checkerboard patten.
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
	The whole series may be found on the QuantitativeBytes 
	YouTube channel at:
	www.youtube.com/c/QuantitativeBytes
	
	GPLv3 LICENSE
	
***********************************************************/

#include "checker.hpp"
#include "./flat.hpp"

// Constructor / destructor.
qbRT::Texture::Checker::Checker()
{
	qbRT::Texture::Flat color1;
	qbRT::Texture::Flat color2;
	
	color1.SetColor(qbVector<double>{std::vector<double>{1.0, 1.0, 1.0, 1.0}});
	color2.SetColor(qbVector<double>{std::vector<double>{0.2, 0.2, 0.2, 1.0}});
	
	m_p_color1 = std::make_shared<qbRT::Texture::Flat> (color1);
	m_p_color2 = std::make_shared<qbRT::Texture::Flat> (color2);
}

qbRT::Texture::Checker::~Checker()
{

}

// Function to return the color.
qbVector<double> qbRT::Texture::Checker::GetColor(const qbVector<double> &uvCoords)
{
	// Apply the local transform to the (u,v) coordinates.
	qbVector<double> inputLoc = uvCoords;
	qbVector<double> newLoc = ApplyTransform(inputLoc);
	double newU = newLoc.GetElement(0);
	double newV = newLoc.GetElement(1);
	
	qbVector<double> localColor {4};
	int check = static_cast<int>(floor(newU)) + static_cast<int>(floor(newV));
	
	if ((check % 2) == 0)
	{
		localColor = m_p_color1 -> GetColor(uvCoords);
	}
	else
	{
		localColor = m_p_color2 -> GetColor(uvCoords);
	}
	
	return localColor;
}

// Function to set the colors.
void qbRT::Texture::Checker::SetColor(const qbVector<double> &inputColor1, const qbVector<double> &inputColor2)
{
	auto color1 = std::make_shared<qbRT::Texture::Flat> (qbRT::Texture::Flat());
	auto color2 = std::make_shared<qbRT::Texture::Flat> (qbRT::Texture::Flat());
	
	color1 -> SetColor(inputColor1);
	color2 -> SetColor(inputColor2);
	
	m_p_color1 = color1;
	m_p_color2 = color2;
}

void qbRT::Texture::Checker::SetColor(const std::shared_ptr<qbRT::Texture::TextureBase> &inputColor1, const std::shared_ptr<qbRT::Texture::TextureBase> &inputColor2)
{
	m_p_color1 = inputColor1;
	m_p_color2 = inputColor2;
}
