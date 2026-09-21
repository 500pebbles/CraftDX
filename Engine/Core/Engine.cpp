#include "Engine.h"

#include "Win32Window.h"
#include "Graphics/Renderer.h"
#include <iostream>

namespace Craft
{
    Engine::Engine(uint32_t width, uint32_t height, const std::wstring title)
    {
        // 창 객체 생성
        window = std::make_unique<Win32Window>(width, height, this,title);
        
        // 렌더러 객체 생성
        renderer = std::make_unique<Renderer>(*window);
    }

    Engine::~Engine()
    {
    }

    void Engine::Run()
    {
        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);        
        auto GetDeltaTime = [&frequency](int64_t& current, int64_t& previous)
        {
            LARGE_INTEGER counter;
            QueryPerformanceCounter(&counter);
            current = counter.QuadPart;
            
            return static_cast<float>(current - previous) / static_cast<float>(frequency.QuadPart);
        };
        
        int64_t current = 0;
        int64_t previous = 0;
        
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
                // 프레임 시간 구하기   
                float deltaTime = GetDeltaTime(current, previous);
                
                // 대기 시간 계산
                
#if _DEBUG
                std::cout << "deltaTime: " << deltaTime
                << "| FPS: " << (1.f / deltaTime) << '\n';
#endif
                
                
                Draw();
                previous = current;
            }
        }
    }

    void Engine::Quit()
    {
    }

    void Engine::Draw()
    {
        if (renderer) renderer->Draw(0.6f, 0.7f, 0.8f, 0);
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
