#ifndef QBRT_UTILS_H
#define QBRT_UTILS_H

#include "./qbLinAlg/qbVector.h"

namespace qbRT
{
	// Forward-declare the object base class.
	class ObjectBase;

	namespace DATA
	{
		struct hitData_t
		{
			qbVector<double> poi			{3};
			qbVector<double> normal		{3};
			qbVector<double> color		{3};
			qbVector<double> localPOI	{3};
			qbVector<double> uvCoords	{2};
			std::shared_ptr<qbRT::ObjectBase> hitObject;
		};
	}

	namespace UTILS
	{
		void PrintVector(const qbVector<double> &inputVector);
	}
}

#endif
