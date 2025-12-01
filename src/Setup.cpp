#include "Setup.h"

void SetupTrilaterationAnchors()
{
    // Example anchor positions (in meters)
    trilaterationManager.SetAnchor(0, 0.0f, 0.0f);   // Anchor 1 at (0,0)
    trilaterationManager.SetAnchor(1, 5.0f, 0.0f);   // Anchor 2 at (5,0)
    trilaterationManager.SetAnchor(2, 2.5f, 4.33f);  // Anchor 3 at (2.5,4.33) forming an equilateral triangle
}