#include "Win32Window.h"

#include "Interface/IMessageHandler.h"

namespace Craft
{
    Win32Window::Win32Window(uint32_t width, uint32_t height, IMessageHandler* messageHandler, const std::wstring title)
        : width(width), height(height), title(title), messageHandler(messageHandler), instance(GetModuleHandle(nullptr))
    {
        // 창 만들때 사용되는 정보 구조체
        WNDCLASS wc = { };
        wc.lpfnWndProc = Win32MessageHandler;
        wc.hInstance = instance;
        wc.lpszClassName = className.c_str();
        wc.style = CS_HREDRAW | CS_VREDRAW;

        // 창 만들때 사용할 클래스 등록
        if (!RegisterClass(&wc))
        {
            __debugbreak();
            return ;
        }
    
        // 창 크기 클라이언트로 조절 (창사이즈 읽고 자동조절)
        RECT rect = { 0, 0, static_cast<long>(width), static_cast<long>(height) };
        AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
    
        // 창 크기 계산
        uint32_t windowWidth = rect.right - rect.left;
        uint32_t windowHeight = rect.bottom - rect.top;
    
        // 창 중앙정렬
        uint32_t screenWidthX = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2;
        uint32_t screenWidthY = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2;
    
        // Window 창 생성
        handle = CreateWindow(
            className.c_str(),        // Window class
            title.c_str(),            // Window text
            WS_OVERLAPPEDWINDOW,      // Window style

            // Position and Size
            screenWidthX, screenWidthY, windowWidth, windowHeight,

            nullptr,       // Parent window    
            nullptr,       // Menu
            instance,      // Instance handle
            this           // Additional application data
        );

        if (!handle)
        {
            __debugbreak();
            return;
        }

        GetClientRect(handle, &rect);
    
        // 창 보이기 모드 설정
        ShowWindow(handle, SW_SHOW);
    }

    Win32Window::~Win32Window()
    {
        // 클래스 등록 해제
        UnregisterClass(className.c_str(), instance);
    }

    LRESULT Win32Window::Win32MessageHandler(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
    {
        /* 메시지 생성 */
        if (message == WM_CREATE)
        {
            // 윈도우 파라미터 설정
            CREATESTRUCT* createStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
            if (createStruct)
            {
                // 임시 저장
                Win32Window* win32Window = reinterpret_cast<Win32Window*>(createStruct->lpCreateParams);
                
                if (win32Window && win32Window->messageHandler)
                {
                    SetWindowLongPtr(window, GWLP_USERDATA, (LONG_PTR)win32Window);
                }
            }
            
            return 0;
        }
        
        /* 생성 이후의 이벤트 처리 */
        Win32Window* win32Window = reinterpret_cast<Win32Window*>(GetWindowLongPtr(window, GWLP_USERDATA));
        if (win32Window && win32Window->messageHandler)
        {
            // 인터페이스를 통해서 이벤트 전달
            return win32Window->messageHandler->HandleMessage(window, message, wParam, lParam);
        }
        
        /* 메시지를 찾지 못했을 경우 윈도우 기본이벤트 함수 호출 */
        return DefWindowProc(window, message, wParam, lParam);
        
        /* 메시지 처리 */
        
    }
}
