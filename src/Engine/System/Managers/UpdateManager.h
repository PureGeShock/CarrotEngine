#include "src/Engine/System/Managers/Manager.h"

namespace Carrot
{

PTR(UpdateManager);

class UpdateManager : public Manager
{
public:
    virtual void Update(float dt) override {}
};

} 
