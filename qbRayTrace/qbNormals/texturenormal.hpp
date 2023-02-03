/* ***********************************************************
	TextureNormal.hpp
	
	The simplerough class definition. A very simple random
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

#ifndef TEXTURENORMAL_H
#define TEXTURENORMAL_H

#include "normalbase.hpp"
#include <random>

namespace qbRT
{
	namespace Normal
	{
		class TextureNormal : public NormalBase
		{
			public:
				// Constructor / Destructor.
				TextureNormal();
				virtual ~TextureNormal() override;
			
				// Function to compute the perturbation.
				virtual qbVector3<double> ComputePerturbation(const qbVector3<double> &normal, const qbVector2<double> &uvCoords) override;
				
				// Function to assign the base texture.
				void AssignBaseTexture(const std::shared_ptr<qbRT::Texture::TextureBase> &inputTexture);
				
			public:
				double m_scale = 1.0;
				bool m_reverse = false;
				
			private:
				bool m_haveTexture = false;
				std::shared_ptr<qbRT::Texture::TextureBase> m_p_baseTexture;
				
		};
	}
}

#endif
