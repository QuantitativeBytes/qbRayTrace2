/* ***********************************************************
	qbutils.hpp
	
	A collection of useful functions and definitions for qbRAY.
	
	This file forms part of the qbRayTrace project as described
	in the series of videos on the QuantitativeBytes YouTube
	channel.
	
	The whole series may be found on the QuantitativeBytes 
	YouTube channel at:
	www.youtube.com/c/QuantitativeBytes
	
	GPLv3 LICENSE
	Copyright (c) 2023 Michael Bennett
	
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

#include "qbutils.hpp"

void qbRT::UTILS::PrintVector(const qbVector3<double> &inputVector)
{
	int nRows = inputVector.GetNumDims();
	for (int row=0; row<nRows; ++row)
	{
		std::cout << std::fixed << std::setprecision(3) << inputVector.GetElement(row) << std::endl;
	}
}

void qbRT::UTILS::PrintMatrix(const qbMatrix33<double> &inputMatrix)
{
	for (int row=0; row<3; ++row)
	{
		for (int col=0; col<3; ++col)
		{
			std::cout << std::fixed << std::setprecision(3) << inputMatrix.GetElement(row, col) << " ";
		} 
		std::cout << std::endl;
	}
}

void qbRT::UTILS::PrintMatrix(const qbMatrix44<double> &inputMatrix)
{
	for (int row=0; row<4; ++row)
	{
		for (int col=0; col<4; ++col)
		{
			std::cout << std::fixed << std::setprecision(3) << inputMatrix.GetElement(row, col) << " ";
		} 
		std::cout << std::endl;
	}
}
