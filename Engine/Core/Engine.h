#pragma once
#include <memory>
#include <string>

#include "Interface/IMessageHandler.h"

namespace Craft
{
    class Win32Window;
    
    class Engine : public IMessageHandler
    {
    public:
        Engine(uint32_t width = 1280, uint32_t height = 800, const std::wstring title = L"Craft Render Engine");
        virtual ~Engine();        
        
    public:
        void Run();
        void Quit();
        
    protected:
        virtual LRESULT HandleMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam) override;

        
    protected:
        std::unique_ptr<Win32Window> window;    
    };

}
