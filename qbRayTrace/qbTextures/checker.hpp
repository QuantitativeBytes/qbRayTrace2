/* ***********************************************************
	checker.hpp
	
	The checker class definition - The 'classic' ray tracer
	checkerboard pattent.
	
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

#ifndef CHECKER_H
#define CHECKER_H

#include "texturebase.hpp"

namespace qbRT
{
	namespace Texture
	{
		class Checker : public TextureBase
		{
			public:
				// Constructor / destructor.
				Checker();
				virtual ~Checker() override;
			
				// Function to return the color.
				virtual qbVector4<double> GetColor(const qbVector2<double> &uvCoords) override;
			
				// Function to set the colors.
				void SetColor(const qbVector4<double> &inputColor1, const qbVector4<double> &inputColor2);
				void SetColor(const std::shared_ptr<qbRT::Texture::TextureBase> &inputColor1, const std::shared_ptr<qbRT::Texture::TextureBase> &inputColor2);
			
		private:
			std::shared_ptr<qbRT::Texture::TextureBase> m_p_color1;
			std::shared_ptr<qbRT::Texture::TextureBase> m_p_color2;
			
		};
	}
}

#endif
