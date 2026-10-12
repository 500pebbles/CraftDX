#pragma once
#include "GameFramework/Level.h"

using namespace Craft;
class TestLevel : public Level
{
protected:
    virtual void Initialized() override;
    
};
