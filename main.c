#include <raylib.h>
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Random Walk");
  SetTargetFPS(60);

  Rectangle rect = (Rectangle){50, 50, 50, 50};
  while (!WindowShouldClose()) {

    BeginDrawing();
    ClearBackground(BLACK);
    rect.x += 20;
    rect.y += 20;
    DrawRectangle(rect.x, rect.y, rect.width, rect.height, RAYWHITE);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
