#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCALE 2
#define MAX_TRAIL_LENGTH 1000 // Limit trail length to prevent memory issues

typedef struct {
  int vx, vy;
} Velocity;

typedef struct {
  float x, y;
  Color trail_color;
} Agent;

Velocity get_random_v() {
  int choice = rand() / (RAND_MAX / 4);
  switch (choice) {
  case 0: // up
    return (Velocity){0, -1};
  case 1: // down
    return (Velocity){0, 1};
  case 2: // left
    return (Velocity){-1, 0};
  case 3: // right
    return (Velocity){1, 0};
  }
  fprintf(stderr, "Invalid number: %d", choice);
  exit(-1);
}

int main(int argc, const char *argv[]) {
  int num_agents = (argc == 2) ? atoi(argv[1]) : 5;

  // Seed random number generator
  srand(time(NULL));

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Random Walk with Trails");
  SetTargetFPS(60);

  Agent *agents = malloc(num_agents * sizeof(Agent));

  // Initialize agents
  for (int i = 0; i < num_agents; i++) {
    agents[i].x = SCREEN_WIDTH / 2.0f;
    agents[i].y = SCREEN_HEIGHT / 2.0f;

    // Randomize trail color for each agent
    agents[i].trail_color = (Color){
        rand() % 256, rand() % 256, rand() % 256,
        200 // Slight transparency
    };
  }

  Vector2 trails[MAX_TRAIL_LENGTH][MAX_TRAIL_LENGTH];
  int trail_lengths[MAX_TRAIL_LENGTH] = {0};

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    // Move and draw each agent
    for (int i = 0; i < num_agents; i++) {
      Velocity v = get_random_v();

      agents[i].x += v.vx * SCALE;
      agents[i].y += v.vy * SCALE;

      agents[i].x = fmodf(agents[i].x + SCREEN_WIDTH, SCREEN_WIDTH);
      agents[i].y = fmodf(agents[i].y + SCREEN_HEIGHT, SCREEN_HEIGHT);

      DrawRectangle(agents[i].x, agents[i].y, 5, 5, agents[i].trail_color);

      if (trail_lengths[i] < MAX_TRAIL_LENGTH) {
        trails[i][trail_lengths[i]] = (Vector2){agents[i].x, agents[i].y};
        trail_lengths[i]++;
      }

      for (int j = 0; j < trail_lengths[i]; j++) {
        DrawPixel(trails[i][j].x, trails[i][j].y, agents[i].trail_color);
      }
    }

    EndDrawing();
  }

  free(agents);
  CloseWindow();
  return 0;
}
