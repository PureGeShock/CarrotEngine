#include "src/Engine/Core/Interfaces/Interface.h"

namespace Carrot
{

class IUpdateable : public Interface
{
public:
    virtual void Update(float dt) = 0;
};

}
