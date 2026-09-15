#include "LaunchApplication.h"
#include <Core/Win32Window.h>
#include <cstdint>

#include "Core/Engine.h"

int LaunchApplication()
{
   Craft::Engine engine;
   engine.Run();
   
   return 0;
}
