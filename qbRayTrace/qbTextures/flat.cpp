/* ***********************************************************
	flat.cpp
	
	The flat class implementation - The simplest possible texture
	definition consisting of just a single color.
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
	This code corresponds specifically to Episode 9 of the series,
	which may be found here:
	https://youtu.be/d35gDi98gEY
	
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

#include "flat.hpp"

// Constructor / destructor.
qbRT::Texture::Flat::Flat()
{
	m_color = qbVector4<double>{std::vector<double> {1.0, 0.0, 0.0, 1.0}};
}

qbRT::Texture::Flat::~Flat()
{

}

// Function to return the color.
qbVector4<double> qbRT::Texture::Flat::GetColor(const qbVector2<double> &uvCoords)
{
	return m_color;
}

// Function to set the color.
void qbRT::Texture::Flat::SetColor(const qbVector4<double> &inputColor)
{
	m_color = inputColor;
}
