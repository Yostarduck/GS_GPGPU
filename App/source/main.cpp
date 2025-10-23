#include "AppConfig.h"

#include <iostream>
#include <chrono>
#include <thread>

#include "raylib.h"

using Clock = std::chrono::steady_clock;

int
main(int argc, char* argv[]) {
  std::cout << "Executing " << APP_NAME << " from path: " << argv[0] << std::endl;
  
  InitWindow(1920, 1080, "Graphics Specialization GPGPU Module");

	bool quit = false;
  
  std::chrono::time_point<Clock> lastTime = Clock::now();
  std::chrono::time_point<Clock> newTime;
  std::chrono::milliseconds deltaTime;

  int fps = 60;
  std::chrono::milliseconds msPerFrame(1000 / fps);

  while (!quit) {
    quit = WindowShouldClose();
		if (quit) {
			break;
		}
    
    BeginDrawing();
      ClearBackground(RAYWHITE);
      DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
    EndDrawing();
    
    newTime = Clock::now();
    deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(newTime - lastTime);
    lastTime = newTime;

    std::chrono::milliseconds remainingTime = msPerFrame - deltaTime;
    if (remainingTime.count() > 0) {
      std::this_thread::sleep_for(std::chrono::milliseconds(remainingTime.count()));
    }
	}
  
  CloseWindow();
  
  return 0;
}