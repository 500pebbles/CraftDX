#pragma once
#include "GameFramework/Actor.h"

using namespace Craft;

class TestActor : public Actor
{
public:
    virtual void Tick(float deltaTime) override;
};
