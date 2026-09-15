#pragma once

#include <Windows.h>

namespace Craft
{
    // Window에서 Engine으로 메시지 처리를 전달할 때 사용할 인터페이스
    class IMessageHandler
    {
    public:
        virtual LRESULT HandleMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam) = 0;
    };
}