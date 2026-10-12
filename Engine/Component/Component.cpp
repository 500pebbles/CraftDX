#include "Component.h"

namespace Craft
{
    Component::Component()
    {
    }

    void Component::BeginPlay()
    {
        hasBeganPlay = true;
    }

    void Component::Tick(float deltaTime)
    {
    }

    void Component::Draw()
    {
    }

    void Component::Destroy()
    {
        hasExpired = true;
        OnDestroyed();
    }

    void Component::OnDestroyed()
    {
    }
}