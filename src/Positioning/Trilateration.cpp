#include "Positioning/Trilateration.h"

TrilaterationManager::TrilaterationManager(float refRssiAt1m, float pathLossExponent)
    : m_refRssi1m(refRssiAt1m), m_n(pathLossExponent)
{
    for (int i = 0; i < 3; ++i)
    {
        m_anchors[i].x = 0.0f;
        m_anchors[i].y = 0.0f;
    }
}

void TrilaterationManager::SetAnchor(int index, float x, float y)
{
    if (index < 0 || index >= 3)
        return;
    m_anchors[index].x = x;
    m_anchors[index].y = y;
}

void TrilaterationManager::setModelParameters(float refRssiAt1m, float pathLossExponent)
{
    m_refRssi1m = refRssiAt1m;
    m_n = pathLossExponent;
}

Vec2 TrilaterationManager::estimatePosition(float rssi0, float rssi1, float rssi2) const
{
    float d0 = rssiToDistance(rssi0);
    float d1 = rssiToDistance(rssi1);
    float d2 = rssiToDistance(rssi2);

    const Vec2 &p0 = m_anchors[0];
    const Vec2 &p1 = m_anchors[1];
    const Vec2 &p2 = m_anchors[2];

    float A = 2.0f * (p1.x - p0.x);
    float B = 2.0f * (p1.y - p0.y);
    float C = (d0 * d0 - d1 * d1) - (p0.x * p0.x - p1.x * p1.x) - (p0.y * p0.y - p1.y * p1.y);

    float D = 2.0f * (p2.x - p0.x);
    float E = 2.0f * (p2.y - p0.y);
    float F = (d0 * d0 - d2 * d2) - (p0.x * p0.x - p2.x * p2.x) - (p0.y * p0.y - p2.y * p2.y);

    float denom = A * E - B * D;

    if (fabsf(denom) < 1e-6f)
    {
        return {NAN, NAN};
    }

    float x = (C * E - B * F) / denom;
    float y = (A * F - C * D) / denom;

    return {x, y};
}

float TrilaterationManager::rssiToDistance(float rssi) const
{
    float exponent = (m_refRssi1m - rssi) / (10.0f * m_n);
    return powf(10.0f, exponent);
}
