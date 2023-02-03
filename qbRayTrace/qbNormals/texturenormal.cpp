/* ***********************************************************
	TextureNormal.cpp
	
	The TextureNormal class definition. A very simple random
	noise based normal map.
	
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

#include "texturenormal.hpp"

// Constructor / destructor.
qbRT::Normal::TextureNormal::TextureNormal()
{

}

qbRT::Normal::TextureNormal::~TextureNormal()
{

}

// Function to assign a base texture.
void qbRT::Normal::TextureNormal::AssignBaseTexture(const std::shared_ptr<qbRT::Texture::TextureBase> &inputTexture)
{
	m_p_baseTexture = inputTexture;
	m_haveTexture = true;
}

qbVector3<double> qbRT::Normal::TextureNormal::ComputePerturbation(const qbVector3<double> &normal, const qbVector2<double> &uvCoords)
{
	double x = 0.0;
	double y = 0.0;
	double z = 0.0;
	if (m_haveTexture)
	{
		qbVector2<double> uvGrad = TextureDiff(m_p_baseTexture, uvCoords);
		if (!m_reverse)
		{
			x = -uvGrad.GetElement(0) * m_scale;
			y = -uvGrad.GetElement(1) * m_scale;
		}
		else
		{
			x = uvGrad.GetElement(0) * m_scale;
			y = uvGrad.GetElement(1) * m_scale;		
		}
	}
	
	qbVector3<double> perturbation = std::vector<double> {x, y, z};
	return PerturbNormal(normal, perturbation);
}
