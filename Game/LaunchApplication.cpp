#include "LaunchApplication.h"
#include <Core/Win32Window.h>
#include <cstdint>

#include "Core/Engine.h"
#include "Test/TestLevel.h"

int LaunchApplication()
{
   Craft::Engine engine;
   engine.AddNewLevel<TestLevel>();
   engine.Run();
   
   return 0;
}
