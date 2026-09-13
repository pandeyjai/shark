#include "progress.h"
#include <raylib.h>
#include <math.h>
static float timeAlive = 0;
static float baseSpeed = 500;
static int multiplier = 1;
static int lives = 3;
static float hitCooldown = 0;
static float invTimer = 0;

void Progress_Reset(void) {
    timeAlive = 0;
    baseSpeed = 500;
    multiplier = 1;
}
void Progress_Update(float dt) {
    timeAlive += dt;
    baseSpeed = fminf(1000, 500 + timeAlive*20);
    multiplier = 1 + (int)(timeAlive/10);
    if (invTimer > 0) invTimer -= dt;
    if (hitCooldown > 0) hitCooldown -= dt;
}
float Progress_GetScoreDelta(float dt) {
    return 5 * multiplier * dt;
}
float Progress_GetEnemySpeed(void) {
    return baseSpeed;
}
int Progress_GetMultiplier(void) {
    return multiplier;
}

void Progress_ResetLives(void) {
    lives = 3;
    hitCooldown = 0.5f;
    invTimer = 0.5f;
}
void Progress_Hit(void) {
    if (invTimer > 0 || hitCooldown > 0) return;
    lives--;
    hitCooldown = 0.5f;
    invTimer = 0.5f;
}
int Progress_GetLives(void) { return lives; }
int Progress_GetMaxLives(void) { return 3; }
bool Progress_HasLives(void) { return lives > 0; }

void Progress_DrawLives(void) {
    int max = Progress_GetMaxLives();
    float spacing = 65;
    float startX = 1920 - max * spacing - 10;
    float cy = 90;
    float s = 26;
    for (int i = 0; i < max; i++) {
        bool alive = i < Progress_GetLives();
        float cx = startX + i * spacing;
        float r = s * 0.28f;
        Color col;
        if (!alive) col = Fade(RED, 0.22f);
        else if (invTimer > 0 && fmodf(invTimer * 12.0f, 2.0f) > 1.0f) col = RED;
        else if (invTimer > 0 && fmodf(invTimer * 12.0f, 2.0f) <= 1.0f) col = Fade(RED, 0.35f);
        else col = RED;
        DrawCircleV((Vector2){ cx - r*0.7f, cy - r*0.3f }, r, col);
        DrawCircleV((Vector2){ cx + r*0.7f, cy - r*0.3f }, r, col);
        DrawTriangle((Vector2){ cx - s*0.5f, cy - r*0.1f },
                     (Vector2){ cx + s*0.5f, cy - r*0.1f },
                     (Vector2){ cx, cy + s*0.55f }, col);
    }
}
