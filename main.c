#include <raylib.h> 
#include "menu.h"
#include "progress.h"
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif
#define MAX 15
typedef struct { float x, y, speed; } Enemy;

// globals so UpdateDrawFrame(void) can see them on web
static float x = 870, y = 880, speed = 300, score = 0;
static Enemy e[MAX];
static State state = MENU;

static void ResetGame(void) {
    x = 870;
    y = 880;
    speed = 300;
    score = 0;
    Progress_Reset();
    Progress_ResetLives();
    for (int i = 0; i < MAX; i++) {
        e[i].x = (float)GetRandomValue(0, 1880);
        e[i].y = -40 - i * 250;
        e[i].speed = Progress_GetEnemySpeed();
    }
}

static void UpdateDrawFrame(void) {
    float dt = GetFrameTime();
    if (state == MENU) {
        int action = MenuClick();
        if (action == 1) {
            ResetGame();
            state = PLAYING;
        } else if (action == 2) {
            UnloadMenuFont();
            CloseWindow();
#ifdef __EMSCRIPTEN__
            emscripten_cancel_main_loop();
#endif
            return;
        }
        BeginDrawing();
        DrawMenu();
        EndDrawing();
        return;
    }
    if (state == GAMEOVER) {
        if (GameOverDone()) state = MENU;
        BeginDrawing();
        DrawGameOver(score);
        EndDrawing();
        return;
    }
    if (IsKeyDown(KEY_RIGHT)) x += speed * dt;
    if (IsKeyDown(KEY_LEFT)) x -= speed * dt;
    Progress_Update(dt);
    score += Progress_GetScoreDelta(dt);
    for (int i = 0; i < MAX; i++) {
        e[i].y += e[i].speed * dt;
        if (e[i].y > 1080) {
            e[i].y = -40;
            e[i].x = (float)GetRandomValue(0, 1880);
            e[i].speed = Progress_GetEnemySpeed();
        }
    }
    Rectangle player = { x, y, 40, 40 };
    for (int i = 0; i < MAX; i++) {
        Rectangle er = { e[i].x, e[i].y, 40, 40 };
        if (CheckCollisionRecs(player, er)) {
            Progress_Hit();
            if (!Progress_HasLives()) { state = GAMEOVER; break; }
            player = (Rectangle){ x, y, 40, 40 };
        }
    }
    if (state != PLAYING) return;
    BeginDrawing();
    ClearBackground(BLACK);
    const char *stext = TextFormat("%d", (int)score);
    int sw = MeasureText(stext, 50);
    DrawText(stext, 1920 - sw - 60, 30, 50, GRAY);
    Progress_DrawLives();
    DrawRectangle((int)x, (int)y, 40, 40, WHITE);
    for (int i = 0; i < MAX; i++) {
        DrawRectangle((int)e[i].x, (int)e[i].y, 40, 40, RED);
    }
    EndDrawing();
}

int main(void) {
    InitWindow(1920, 1080, "shark");
    LoadMenuFont();
    ResetGame();
    state = MENU;
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    while (!WindowShouldClose()) UpdateDrawFrame();
#endif
    UnloadMenuFont();
    CloseWindow();
    return 0;
}
