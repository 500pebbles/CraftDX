#include <Windows.h>
#include "LaunchApplication.h"

/* DEBUG MODE */
#if _DEBUG

int main()
{
    return LaunchApplication();
}

/* RELEASE MODE */
#else

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,_In_ int nShowCmd)
{
    return LaunchApplication();
}

#endif