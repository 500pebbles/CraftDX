#pragma once
#include "GameFramework/Actor.h"


namespace Craft
{
    class Shader;
    class StaticMesh;
};

class TestActor : public Craft::Actor
{
public:
    virtual void Tick(float deltaTime) override;
    
    virtual void Draw() override;
    
public:
    inline void SetStaticMesh(const std::shared_ptr<Craft::StaticMesh>& newMesh) { staticMesh = newMesh; }
    
    inline void SetShader(const std::shared_ptr<Craft::Shader>& newShader) { shader = newShader; }
    
private:
    std::shared_ptr<Craft::StaticMesh> staticMesh;
    
    std::shared_ptr<Craft::Shader> shader;
};