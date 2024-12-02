#pragma once

#include "Utils/Util.hpp"

class CrosshairManager
{
public:

	static float CrosshairShrink(float currentSize, float deltaTime)
	{
        const float shrinkTargets[] = { 0, 0, 0, 0 };
        const float shrinkSpeeds[] = { 0.7, 1.3, 2.5, 3.5 };
        const float thresholds[] = { 14, 9, 6, 0 };

        for (int i = 0; i < 4; ++i) {
            if (currentSize > thresholds[i]) {
                return Util::FInterpTo(currentSize, shrinkTargets[i], deltaTime, shrinkSpeeds[i]);
            }
        }

        return currentSize;
	}
};