#pragma once

#include "Actor.h"
#include <memory>
#include <vector>

namespace Craft
{
    class Level : public std::enable_shared_from_this<Level>
    {
        friend class Engine;

    public:
        Level();
        virtual ~Level() = default;

    public:
        virtual void Initialized();
        virtual void BeginPlay();
        virtual void Tick(float deltaTime);
        virtual void Draw();

        template<typename T, typename ...Args, typename = std::enable_if_t<std::is_base_of<Actor, T>::value>>
        std::shared_ptr<T> SpawnActor(Args&& ...args)
        {
            std::shared_ptr<T> newActor = std::make_shared<T>(std::forward<Args>(args)...);
            newActor->Initialized();
            newActor->SetOwner(weak_from_this());
            addRequestedActorList.emplace_back(newActor);
            return newActor;
        }

        template<typename T, typename = std::enable_if_t<std::is_base_of<Actor, T>::value>>
        std::shared_ptr<T> FindActor()
        {
            for (std::shared_ptr<T> actor : actorList)
            {
                std::shared_ptr<T> targetActor = std::dynamic_pointer_cast<T>(actor);
                if (targetActor) return targetActor;
            }

            for (std::shared_ptr<T> actor : addRequestedActorList)
            {
                std::shared_ptr<T> targetActor = std::dynamic_pointer_cast<T>(actor);
                if (targetActor) return targetActor;
            }

            return nullptr;  // 검색 실패
        }

    private:
        void ProcessAddAndDestroyActors();

    protected:
        std::vector<std::shared_ptr<Actor>> actorList;
        std::vector<std::shared_ptr<Actor>> addRequestedActorList;
    };
}