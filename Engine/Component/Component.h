#pragma once

#include <memory>

namespace Craft
{
    class Actor;

    class Component
    {
    public:
        Component();
        virtual ~Component() = default;

    public:
        virtual void BeginPlay();
        virtual void Tick(float deltaTime);
        virtual void Draw();

        void Destroy();
        virtual void OnDestroyed();

    public:
        inline std::shared_ptr<Actor> GetOwner() const { return owner.lock(); }
        inline void SetOwner(std::weak_ptr<Actor> newOwner) { owner = newOwner; }
        inline bool HasBeganPlay() const { return hasBeganPlay; }
        inline bool IsActive() const { return isActive && !hasExpired; }
        inline bool HasExpired() const { return hasExpired; }

    protected:
        std::weak_ptr<Actor> owner;

        bool hasBeganPlay = false;
        bool isActive = true;
        bool hasExpired = false;
    };
}