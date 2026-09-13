#include "progress.h"
#include <math.h>
static float timeAlive = 0;
static float baseSpeed = 500;
static int multiplier = 1;

void Progress_Reset(void) {
    timeAlive = 0;
    baseSpeed = 500;
    multiplier = 1;
}
void Progress_Update(float dt) {
    timeAlive += dt;
    baseSpeed = fminf(1000, 500 + timeAlive*20);
    multiplier = 1 + (int)(timeAlive/10);
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
