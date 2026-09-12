#include "menu.h"

static Font font = { 0 };
static bool fontLoaded = false;

Rectangle PlayButton(void) {
    return (Rectangle){ 860, 500, 200, 60 };
}

Rectangle ExitButton(void) {
    return (Rectangle){ 860, 600, 200, 60 };
}

void LoadMenuFont(void) {
    font = LoadFont("assets/PressStart2P.ttf");
    fontLoaded = true;
}

void UnloadMenuFont(void) {
    if (fontLoaded) UnloadFont(font);
    fontLoaded = false;
}

static void DrawCentered(const char *text, float y, float size, Color color) {
    Vector2 dim = MeasureTextEx(font, text, size, 2);
    DrawTextEx(font, text, (Vector2){ (1920 - dim.x) / 2, y }, size, 2, color);
}

static void DrawButton(Rectangle btn, const char *label, bool hovered) {
    DrawRectangleRec(btn, BLANK);
    DrawRectangleLinesEx(btn, 1, hovered ? WHITE : Fade(WHITE, 0.25f));
    Vector2 dim = MeasureTextEx(font, label, 20, 2);
    DrawTextEx(font, label,
        (Vector2){ btn.x + (btn.width - dim.x) / 2, btn.y + (btn.height - dim.y) / 2 },
        20, 2, hovered ? WHITE : Fade(WHITE, 0.75f));
}

void DrawMenu(void) {
    ClearBackground(BLACK);
    Vector2 mouse = GetMousePosition();
    Rectangle play = PlayButton();
    Rectangle exit = ExitButton();
    bool hovPlay = CheckCollisionPointRec(mouse, play);
    bool hovExit = CheckCollisionPointRec(mouse, exit);
    DrawCentered("SHARK", 280, 96, WHITE);
    DrawCentered("dodge the red boxes", 400, 20, GRAY);
    DrawButton(play, "play", hovPlay);
    DrawButton(exit, "exit", hovExit);
    
}

int MenuClick(void) {
    if (IsKeyPressed(KEY_ENTER)) return 1;
    if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) return 0;
    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, PlayButton())) return 1;
    if (CheckCollisionPointRec(mouse, ExitButton())) return 2;
    return 0;
}

void DrawGameOver(float score) {
    ClearBackground(BLACK);
    DrawCentered("game over", 350, 72, RED);
    DrawCentered(TextFormat("score: %d", (int)score), 480, 24, WHITE);
    DrawCentered("press enter or click to continue", 560, 16, GRAY);
}

bool GameOverDone(void) {
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) return true;
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) return true;
    return false;
}
