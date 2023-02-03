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

#include "checker.hpp"
#include "./flat.hpp"

// Constructor / destructor.
qbRT::Texture::Checker::Checker()
{
	qbRT::Texture::Flat color1;
	qbRT::Texture::Flat color2;
	
	color1.SetColor(qbVector4<double>{std::vector<double>{1.0, 1.0, 1.0, 1.0}});
	color2.SetColor(qbVector4<double>{std::vector<double>{0.2, 0.2, 0.2, 1.0}});
	
	m_p_color1 = std::make_shared<qbRT::Texture::Flat> (color1);
	m_p_color2 = std::make_shared<qbRT::Texture::Flat> (color2);
}

qbRT::Texture::Checker::~Checker()
{

}

// Function to return the color.
qbVector4<double> qbRT::Texture::Checker::GetColor(const qbVector2<double> &uvCoords)
{
	// Apply the local transform to the (u,v) coordinates.
	qbVector2<double> inputLoc = uvCoords;
	qbVector2<double> newLoc = ApplyTransform(inputLoc);
	double newU = newLoc.GetElement(0);
	double newV = newLoc.GetElement(1);
	
	qbVector4<double> localColor;
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
void qbRT::Texture::Checker::SetColor(const qbVector4<double> &inputColor1, const qbVector4<double> &inputColor2)
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
