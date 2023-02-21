#ifndef QBRT_UTILS_H
#define QBRT_UTILS_H

#include <memory>
#include <SDL2/SDL.h>
#include "./qbLinAlg/qbVector.h"
#include "./qbLinAlg/qbVector2.hpp"
#include "./qbLinAlg/qbVector3.hpp"
#include "./qbLinAlg/qbVector4.hpp"
#include "./qbLinAlg/qbMatrix33.hpp"
#include "./qbLinAlg/qbMatrix44.hpp"

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
		
		// Structure for handling rendering tiles.
		struct tile
		{
			int x;
			int y;
			int xSize;
			int ySize;
			int renderComplete = 0;
			bool textureComplete = false;
			SDL_Texture *pTexture;
			std::vector<qbVector3<double>> rgbData;
		};			
	}

	namespace UTILS
	{
		void PrintVector(const qbVector3<double> &inputVector);
		void PrintMatrix(const qbMatrix33<double> &inputMatrix);
		void PrintMatrix(const qbMatrix44<double> &inputMatrix);
	}
}

#endif
