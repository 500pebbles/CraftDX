#pragma once
#include "GameFramework/Actor.h"


namespace Craft
{
    class StaticMesh;
};

class TestActor : public Craft::Actor
{
public:
    virtual void Tick(float deltaTime) override;
    
    virtual void Draw() override;
    
public:
    void SetStaticMesh(const std::shared_ptr<Craft::StaticMesh>& newMesh) { staticMesh = newMesh; };
    
private:
    std::shared_ptr<Craft::StaticMesh> staticMesh;
    
};
