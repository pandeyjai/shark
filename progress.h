#ifndef PROGRESS_H
#define PROGRESS_H

void Progress_Reset(void);
void Progress_Update(float dt);
float Progress_GetScoreDelta(float dt);
float Progress_GetEnemySpeed(void);
int   Progress_GetMultiplier(void);

#endif
