#pragma once

#include <Component/Component.h>
#include <memory>
#include <vector>
#include <__msvc_ranges_to.hpp>

#include "Math/Transform.h"

namespace Craft
{
	class Level;
	class Transform;
	class TransformComponent;

	class Actor : public std::enable_shared_from_this<Actor>
	{
		friend class Level;

	public:
		Actor();
		virtual ~Actor();
		
	public:

		virtual void Initialized();
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		void QuitGame();

		void Destroy();
		virtual void OnDestroyed();

		// 컴포넌트 추가 함수.
		template<typename T, typename... Args,
		typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
		std::shared_ptr<T> AddComponent(Args&&... args)
		{
			std::shared_ptr<T> newComponent = std::make_shared<T>(std::forward<Args>(args)...);
			newComponent->SetOwner(weak_from_this());
			addRequestedComponentList.emplace_back(newComponent);

			return newComponent;
		}

		// 컴포넌트 검색 함수.
		template<typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
		std::shared_ptr<T> GetComponent()
		{
			for (const auto& component : componentList)
			{
				std::shared_ptr<T> targetComponent = std::dynamic_pointer_cast<T>(component);
				if (targetComponent) return targetComponent;
			}

			for (const auto& component : addRequestedComponentList)
			{
				std::shared_ptr<T> targetComponent = std::dynamic_pointer_cast<T>(component);
				if (targetComponent) return targetComponent;
			}

			// 찾지 못하면 null 반환.
			return nullptr;
		}

		// 특정 컴포넌트를 소유했는지 확인.
		template<typename T, typename = std::enable_if_t<std::is_base_of<Component, T>::value>>
		bool HasComponent()
		{
			return GetComponent<T>() != nullptr;
		}

		// Getter/Setter.
		inline std::shared_ptr<Level> GetOwner() const { return owner.lock(); }
		inline void SetOwner(std::weak_ptr<Level> newOwner) { owner = newOwner; }
		inline bool HasBeganPlay() const { return hasBeganPlay; }
		inline bool IsActive() const { return isActive && !hasExpired; }
		inline bool HasExpired() const { return hasExpired; }

		Transform& GetTransform();
		const Transform& GetTransform() const;
		
	private:
		// 컴포넌트 추가/제거를 처리하는 함수.
		// 현재 프레임이 아니라 다음 프레임에서 안정적으로 처리하도록.
		void ProcessAddAndDestroyComponents();

	protected:
		std::weak_ptr<Level> owner;

		bool hasBeganPlay = false;
		bool isActive = true;
		bool hasExpired = false;
		
	protected:
		std::vector<std::shared_ptr<Component>> componentList;
		std::vector<std::shared_ptr<Component>> addRequestedComponentList;
		
		std::shared_ptr<TransformComponent> transformComponent;
	};
}
