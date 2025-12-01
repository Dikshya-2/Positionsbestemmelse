#pragma once
#include <math.h>

struct Vec2 {
    float x;
    float y;

    bool isValid() const {
        return !isnan(x) && !isnan(y);
    }
};

class TrilaterationManager {
public:
    // Constructor
    TrilaterationManager(float refRssiAt1m = -59.0f, float pathLossExponent = 2.0f);

    // Set anchor coordinate (index must be 0–2)
    void SetAnchor(int index, float x, float y);

    // Optional: adjust RSSI model
    void setModelParameters(float refRssiAt1m, float pathLossExponent);

    // MAIN API — returns estimated position as Vec2.
    // If trilateration fails (e.g., collinear anchors), Vec2.x/y = NAN.
    Vec2 estimatePosition(float rssi0, float rssi1, float rssi2) const;

    // Convert RSSI → distance (meters)
    float rssiToDistance(float rssi) const;

private:
    Vec2  m_anchors[3];
    float m_refRssi1m;
    float m_n;
};
