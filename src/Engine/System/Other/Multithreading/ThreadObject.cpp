#include "ThreadObject.h"

namespace Carrot
{

void ThreadObject::Main_Loop()
{
    OnThreadCalled.BroadcastIfBound();
}

void ThreadObject::Main()
{
    OnThreadCalled.BroadcastIfBound();
}

}