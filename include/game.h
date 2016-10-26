#pragma once

#include <global.h>
#include <draw.h>
#include <simulation.h>




/* ======== Main Loop Functions ======== */
void render();
void mouse();
void logic();
void keyboard();
void inputLogic();
void calculateFps();
void resetKeys();
/**/


/* ======== Initialization ======== */
int run();
int init();
int initSDL();
void initColors();
int initTextures();
void initSystemSettings();
void initGlobals();
color_t loadColor(const charptr_t clrName, bttfileptr_t file);
/**/



/* ======== Drawing ======== */
void clearScreen();
void drawFps();
void drawStatusBar();
void drawSimulationScreen();
void drawOverviewScreen();
void drawExitConfirmScreen();
void drawNewGameScreen();
void drawDataSet();
void drawMain();
/**/



/* ======== Utility ======== */
void processShortcuts(const keycode_t keys[], const ctrlid_t ids[], size_t len);
void processModifiers(uint16_t mod);
void error(const charptr_t errprompt);
void out(const charptr_t outprompt);
size_t coordToCharsX(int x);
size_t coordToCharsY(int y);
void inputDelay();
void getTime(charptr_t buf, size_t buflen);
/**/

