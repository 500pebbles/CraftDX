#include <Windows.h>
#include "LaunchApplication.h"

#if _DEBUG
// 디버그 모드에서는 main함수가 실행
int main()
{
    return LaunchApplication(GetModuleHandle(nullptr));
}

#else
// Windows 모드에서 사용하는 메인 함수
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,_In_ int nShowCmd)
{
    return LaunchApplication(hInstance);
}
#endif