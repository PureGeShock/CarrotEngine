#include "Object.h"

namespace Carrot
{

std::string Object::GetClassName() const
{
    return typeid(this).name();
}

}
