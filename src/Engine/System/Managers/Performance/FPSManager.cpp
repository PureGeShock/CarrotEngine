#include "FPSManager.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace Carrot
{

/* Constants */
const float FPSManager::kTimeBeforeFPSCalulations = 1.0f;

void FPSManager::Update(float dt)
{
    FPSTimer -= dt;
    if (FPSTimer < 0.0f)
    {
        CalculateFPS();
        FPSTimer = kTimeBeforeFPSCalulations;
    }

    float CurrentFPS = dt > 0.0f ? 1.0f / dt : 60.0f;
    CurrentFPSData.TotalFPSBeforeCalculations += CurrentFPS;
    CurrentFPSData.LastMinFPS = std::min(CurrentFPSData.LastMinFPS, static_cast<int32_t>(CurrentFPS));

    FramesCounter++;
}

void FPSManager::CalculateFPS()
{
    /* Avg FPS calculations */
    CurrentFPSData.AvgFPS = 
        static_cast<int32_t>(CurrentFPSData.TotalFPSBeforeCalculations / std::max(float(FramesCounter - CurrentFPSData.LastFrameNumber), 1.0f));
    CurrentFPSData.TotalFPSBeforeCalculations = 0.0f;
    CurrentFPSData.LastFrameNumber = FramesCounter;

    /* Min FPS calculations */
    CurrentFPSData.MinFPS = CurrentFPSData.LastMinFPS;
    CurrentFPSData.LastMinFPS = std::numeric_limits<int32_t>::max();
}

} 