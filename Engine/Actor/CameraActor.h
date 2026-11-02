#pragma once
#include "GameFramework/Actor.h"

namespace Craft
{
    class CameraComponent;

    class CameraActor : public Actor
    {
    public: 
        virtual void Initialized() override;
        
        void SetProjection(float fieldOfView, float nearDistance = 0.1f, float farDistance = 1000.f);
        
    private:
        std::shared_ptr<CameraComponent> cameraComponent;
        
        /* (WHAT'S THE STORY) MORNING GLORY ? 
         * 1 - Hello
         * 2 - Roll With It
         * 3 - Wonderwall
         * 4 - Don't Look Back In Anger
         * 5 - 
         * 6 -
         * 7 - Some Might Say
         * 8 - She's Electric 
         * 9 - Cast No Shadow
         * 10 - Morning Glory 
         * 11 - 
         * 12 - Champagne Supernova
         */
    };    
} 