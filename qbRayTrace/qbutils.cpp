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
