#ifndef PROGRESS_H
#define PROGRESS_H

void Progress_Reset(void);
void Progress_Update(float dt);
float Progress_GetScoreDelta(float dt);
float Progress_GetEnemySpeed(void);
int   Progress_GetMultiplier(void);

void Progress_ResetLives(void);
void Progress_Hit(void);
int   Progress_GetLives(void);
int   Progress_GetMaxLives(void);
void Progress_DrawLives(void);
bool  Progress_HasLives(void);

#endif
