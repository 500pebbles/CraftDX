#include "Engine.h"

#include "Win32Window.h"

namespace Craft
{
    Engine::Engine(uint32_t width, uint32_t height, const std::wstring title)
    {
        // 창 객체 생성
        window = std::make_unique<Win32Window>(width, height, this,title);
    }

    Engine::~Engine()
    {
    }

    void Engine::Run()
    {
        // 이벤트(창 메시지) 처리 루프
        MSG message = {};
        while (message.message != WM_QUIT)
        {
            // 창에 메세지가 발생한 경우의 처리
            if (PeekMessage(&message,nullptr,0,0,PM_REMOVE))
            {
                TranslateMessage(&message);
                DispatchMessage(&message);
            }
            // 엔진 루프
            else
            {
            
            }
        }
    }

    void Engine::Quit()
    {
    }

    LRESULT Engine::HandleMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_CLOSE:      // 창 닫기 요청
            {
                DestroyWindow(window);
            }
            return 0;
        case WM_DESTROY:    // 창 삭제 이벤트받고 프로그램 종료 요청
            {
                PostQuitMessage(0);
            }
            return 0;
        case WM_KEYDOWN:
            {
                if (wParam == VK_ESCAPE)
                {
                    DestroyWindow(window);
                }
            }
        return 0;
        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(window, &ps);
                FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
                EndPaint(window, &ps);
            }
        return 0;
        }
    
        return DefWindowProc(window, message, wParam, lParam);
    }
}
