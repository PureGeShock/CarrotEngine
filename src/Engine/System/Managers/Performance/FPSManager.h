#pragma once

#include "src/Engine/System/Managers/Manager.h"
#include "src/Engine/Includes/STLIncludes.h"
#include "src/Engine/Includes/SDLIncludes.h"
#include "src/Engine/System/Other/Delegate/Delegate.h"

namespace Carrot
{

enum class EFPSType
{
    None = 0,
    Average,
    Minimal
};

struct FPSData
{
    int32_t AvgFPS = 0;
    float TotalFPSBeforeCalculations = 0;
    uint64_t LastFrameNumber = 0ull;

    int32_t MinFPS = 0;
    int32_t LastMinFPS = std::numeric_limits<int32_t>::max();
};

PTR(FPSManager);

class FPSManager : public Manager
{
public:

    virtual void Initialize() override {}
    virtual void Update(float dt) override;

    FORCE_INLINE int32_t GetFPS(EFPSType Type = EFPSType::Average) const 
    {
        switch (Type)
        {
        case EFPSType::Average: return CurrentFPSData.AvgFPS;
        case EFPSType::Minimal: return CurrentFPSData.MinFPS;
        }

        return 0.0f;
    }

    FORCE_INLINE uint64_t GetCurrentFrameCount() const { return FramesCounter; }

private:

    void CalculateFPS();

    static const float kTimeBeforeFPSCalulations;
    float FPSTimer = kTimeBeforeFPSCalulations;

    FPSData CurrentFPSData;

    uint64_t FramesCounter = 0ull;
};

} 
