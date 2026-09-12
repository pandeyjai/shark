#ifndef MENU_H
#define MENU_H

#include <raylib.h>

typedef enum { MENU, PLAYING, GAMEOVER } State;

Rectangle PlayButton(void);
Rectangle ExitButton(void);
void LoadMenuFont(void);
void UnloadMenuFont(void);
void DrawMenu(void);
int MenuClick(void);
void DrawGameOver(float score);
bool GameOverDone(void);

#endif
