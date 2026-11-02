#pragma once
#include <memory>
#include <string>

#include "GameFramework/Level.h"
#include "Interface/IMessageHandler.h"

namespace Craft
{
    class TextureManager;
    class ShaderManager;
    class Win32Window;
    class Renderer;
    
    class Engine : public IMessageHandler
    {
    public:
        Engine(uint32_t width = 1280, uint32_t height = 800, const std::wstring title = L"Craft Render Engine");
        virtual ~Engine();        
        
    public:
        static Engine& Get();
        
    public:
        void Run();
        void Quit();
        
    protected:
        void BeginPlay();
        void Tick(float deltaTime);
        void Draw();
        void OnResize(uint32_t width, uint32_t height);
        
    public:        
        uint32_t GetClientWidth() const;
        uint32_t GetClientHeight() const;
        
    protected:
        virtual LRESULT HandleMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam) override;

        
    protected: 
        std::unique_ptr<Win32Window> window;    
        std::unique_ptr<Renderer> renderer;
        std::shared_ptr<Level> mainLevel;
        std::shared_ptr<Level> nextLevel;
        std::unique_ptr<ShaderManager> shaderManager;
        std::unique_ptr<TextureManager> textureManager;

        
    protected:
        inline static Engine* instance = nullptr;
    
    protected:
        bool isQuit = false;
    
        
    public:
        template<typename T, typename = std::enable_if<std::is_base_of<Level, T>::value>>
        void AddNewLevel()
        {
            nextLevel = std::make_shared<T>();
        }
        
    };    
}
