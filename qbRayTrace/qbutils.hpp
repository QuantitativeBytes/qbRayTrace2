#ifndef QBRT_UTILS_H
#define QBRT_UTILS_H

#include <memory>
#include "./qbLinAlg/qbVector.h"
#include "./qbLinAlg/qbVector2.hpp"
#include "./qbLinAlg/qbVector3.hpp"
#include "./qbLinAlg/qbVector4.hpp"

namespace qbRT
{
	// Forward-declare the object base class.
	class ObjectBase;

	namespace DATA
	{
		struct hitData
		{
			qbVector3<double> poi;
			qbVector3<double> normal;
			qbVector3<double> color;
			qbVector3<double> localPOI;
			qbVector2<double> uvCoords;
			std::shared_ptr<qbRT::ObjectBase> hitObject;
		};
	}

	namespace UTILS
	{
		void PrintVector(const qbVector3<double> &inputVector);
	}
}

#endif
