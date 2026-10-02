#pragma once
#include <memory>
#include <string>

#include "Interface/IMessageHandler.h"

namespace Craft
{
    class Win32Window;
    class Renderer;
    
    class Engine : public IMessageHandler
    {
    public:
        Engine(uint32_t width = 1280, uint32_t height = 800, const std::wstring title = L"Craft Render Engine");
        virtual ~Engine();        
        
    public:
        void Run();
        void Quit();
        
    protected:
        void Draw();
        void OnResize(uint32_t width, uint32_t height); // 창 크기 변경 이벤트 함수
        
    protected:
        virtual LRESULT HandleMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam) override;

        
    protected: 
        std::unique_ptr<Win32Window> window;    
        std::unique_ptr<Renderer> renderer;
    };    
}
