#include "LaunchApplication.h"

#include <cstdint>


LRESULT Win32MessageHandler(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    // 메시지 처리
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
    }
    
    return DefWindowProc(window, message, wParam, lParam);
}

int LaunchApplication(HINSTANCE instance)
{
    const wchar_t* className = L"Craft_DX_Engine_Class";

    // 창 만들때 사용되는 정보 구조체
    WNDCLASS wc = { };
    wc.lpfnWndProc = Win32MessageHandler;
    wc.hInstance = instance;
    wc.lpszClassName = className;
    wc.style = CS_HREDRAW | CS_VREDRAW;

    // 창 만들때 사용할 클래스 등록
    if (!RegisterClass(&wc)) return -1;

    // 프레임 크기 기본설정
    uint32_t width = 1280;
    uint32_t height = 800;
    
    // 창 크기 클라이언트로 조절(창사이즈 읽고 자동조절)
    RECT rect = { 0, 0, static_cast<long>(width), static_cast<long>(height) };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
    
    // 창 크기 계산
    uint32_t windowWidth = rect.right - rect.left;
    uint32_t windowHeight = rect.bottom - rect.top;
    
    // 창 중앙정렬
    uint32_t screenWidthX = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2;
    uint32_t screenWidthY = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2;
    
    // Window 창 생성
    HWND hwnd = CreateWindow(
        className,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Position and Size
        screenWidthX, screenWidthY, windowWidth, windowHeight,

        nullptr,       // Parent window    
        nullptr,       // Menu
        instance,  // Instance handle
        nullptr        // Additional application data
    );

    if (hwnd == nullptr) return 0;

    GetClientRect(hwnd, &rect);
    
    // 창 보이기 모드 설정
    ShowWindow(hwnd, SW_SHOW);
    
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
    return 0;
}
