#pragma once

#include <cstdint>
#include <string>
#include "Windows.h"

namespace Craft
{    
    class IMessageHandler;
    
    class Win32Window
    {
    public:
        Win32Window(uint32_t width = 1280, uint32_t height = 800, IMessageHandler* messageHandler = nullptr, const std::wstring title = L"Craft Render Engine");
        ~Win32Window();
        
    public:
        void OnResize(uint32_t width, uint32_t height);
        
    public:
        inline uint32_t GetWidth() const { return width; }
        inline uint32_t GetHeight() const { return height; }
        inline HWND GetHandle() const { return handle; }
        
    private:
        // 창 메시지 처리 함수
        static LRESULT Win32MessageHandler(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
        
    private:
        // 프로그램 인스턴스
        HINSTANCE instance = nullptr;
        
        // 창 객체 핸들
        HWND handle = nullptr;
        
        // 창 크기 
        uint32_t width = 0;
        uint32_t height = 0;
        
        // 클래스&타이틀 이름
        std::wstring className = L"Craft_Render_Window_Class";
        std::wstring title;
        
        // 메시지 핸들러 포인터
        IMessageHandler* messageHandler = nullptr;
    };
}
