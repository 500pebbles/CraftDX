#include "Level.h"

namespace Craft
{
    Level::Level()
    {
    }

    void Level::Initialized()
    {
        /* 레벨 생성이 끝난 직후에 호출. 
         * 액터->레벨로 오너십을 설정할 때, 레벨의 생성이 완전히 끝나야 함
         * 생성자에서 이를 호출한다면 생성이 완료되지 않은 상태, 따라서 직후에 호출하는 용도로 사용 */
    }

    void Level::BeginPlay()
    {
        for (const auto& actor : actorList)
        {
            if (!actor->IsActive() || actor->HasBeganPlay()) continue;
            actor->BeginPlay();
        }
    }

    void Level::Tick(float deltaTime)
    {
        for (const auto& actor : actorList)
        {
            if (!actor->IsActive()) continue;
            actor->Tick(deltaTime);
        }
    }

    void Level::Draw()
    {
        for (const auto& actor : actorList)
        {
            if (!actor->IsActive()) continue;
            actor->Draw();
        }
    }

    void Level::ProcessAddAndDestroyActors()
    {
        // 액터의 컴포넌트 추가/제거 처리.
        for (const auto& actor : actorList)
        {
            actor->ProcessAddAndDestroyComponents();
        }

        // 삭제 요청된 액터 제거 처리.
        for (auto iterator = actorList.begin(); iterator != actorList.end();)
        {
            // 삭제 요청 여부 확인.
            if ((*iterator)->HasExpired())
            {
                iterator = actorList.erase(iterator);
                continue;
            }

            ++iterator;
        }

        // 액터 추가 요청 처리.
        if (addRequestedActorList.empty()) return;
        for (const auto& actor : addRequestedActorList)
        {
            actor->ProcessAddAndDestroyComponents();
            actorList.emplace_back(actor);
        }

        // 추가 처리한 목록 정리.
        addRequestedActorList.clear();
    }
}