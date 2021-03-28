#pragma once

#include "src/Engine/CarrotCore.h"
#include "src/Engine/System/Other/Multithreading/Thread.h"

namespace Carrot
{

/**
 * 
*/
class ThreadObject : public Thread
{
public:

    EventDelegate<> OnThreadCalled;

protected:

    /** 
     * Dont call it manually, just override. To run thread, call Run().
     */
    virtual void Main() override;
    virtual void Main_Loop() override;
};

}
