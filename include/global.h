#pragma once

/* ======== Includes ======== */
#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

// GUIDELINE:	Header files which declare new structs and types ("libs") not related to the game should NOT include 
//				the global header. All other structs are declared/defined in this header file. All other files should include
//				this global header.
//				Furthermore, header files like draw.h ( headers only declaring routines, => all other game related headers, as all 
//				structs/types are in this file ) should NOT be included here. They should be included in each file that needs them.


/* Libs - these do not include global.h */
#include <tagtree.h>
#include <ptrmap.h>
/**/

/**/



/* ======== Typedefs ======== */
typedef Uint32 color_t;
typedef char* charptr_t;
typedef int bool_t;
typedef uint8_t* uint8ptr_t;
typedef const uint8_t* cuint8ptr_t;
typedef uint32_t keycode_t;
typedef uint32_t ctrlid_t;


typedef enum _primaryState
{
	HOME,
	NEWGAME,
	CONFIRMEXIT,
} primaryState_t;
/**/




/* ======== Defines ======== */ 

/* Extern definition/declaration macro. The file defining GLOBAL_H_MAIN before including global.h IMPLEMENTS globals. */
#ifdef GLOBAL_H_MAIN
#define EXTERN
#else
#define EXTERN extern
#endif
/**/

/* Boolean expressions */
#define TRUE 1
#define FALSE 0
/**/

/* How many frames of input are skipped after each input */
#define SKIPINPUT 0//10

/* Length of the moving average fps filter */
#define FPSFILTERLEN 25

/* Length of the keystate array aka max scancode */
#define KEYSTATELEN 256

/* Default config file name */
#define CONFIGFILE "config.bin"

/* Maximum */
#define MAX(x,y) ((x > y) ? x : y)

/* Minimum */
#define MIN(x,y) ((x > y) ? y : x)

#define CLAMP(x, min, max) (MAX(min, MIN(max, (x))))

/* Adds MOD to VAL respecting given boundaries */
#define MODVAL(val, mod, min, max) val = (CLAMP(val+mod, min, max))

/* Applies MODVAL with either 1 (sgnexpr) or -1 (!sgnexpr) as mod */
#define MODVAL_SGN(val, sgnexpr, min, max) MODVAL(val, (sgnexpr ? 1 : -1), min, max)

/* Checks if the control with id x is currently selected */
#define ISSELECTED(x) gCurrentState.selectedControl == x

/* Sets selected control */
#define SETSELECTED(x) gCurrentState.selectedControl = x

/* Selected control id */
#define SELECTEDCTRL gCurrentState.selectedControl

/* Sets current state */
#define SETSTATE(x) gCurrentState.pState = x

/* Checks if x is current state */
#define ISSTATE(x) gCurrentState.pState == x

/* A dark gray color if the control is selected and a bright one if not */
#define CLRSELECTED(x) (ISSELECTED(x) ? gcClrGrayDark : gcClrGray)

/* A dark gray color if the key is down and control is selected and a bright one if not */
#define CLRONKEY(x,y) (ISSELECTED(x) && KEYDOWN(y) ? gcClrGrayDark : gcClrGray)

/* Checks if a key is pressed or not */
#define KEYDOWN(x) gKeyboardState[x]

/* Checks if KEY is pressed. If it is, selects control with id ID */
#define SHORTCUT(key, id) if(KEYDOWN(key)) { SETSELECTED(id); }

/* Show debug output in console or not */
#define DEBUGOUTPUT

/* Width of screen in chars */
#define SCR_W_CHR gScrW / gCharW

/* Height of screen in chars */
#define SCR_H_CHR gScrH / gCharH

/* How many frames have to pass until a key is recognized as hold */
#define KEY_DELAY 5

/* Simulation width */
#define SIM_X 150
/* Simulation height */
#define SIM_Y 67//50



/* Control IDs */
#define ID_NONE 0
#define ID_OVERVIEW_FRAMEDELAY 1

#define ID_NEWGAME_SPERC 2
#define ID_NEWGAME_SSENER 3
#define ID_NEWGAME_SEGAIN 4
#define ID_NEWGAME_SREPT 5
#define ID_NEWGAME_FREPT 6
#define ID_NEWGAME_OK 7
#define ID_NEWGAME_CANCEL 8

#define ID_CONFIRMEXIT_NO 9
#define ID_CONFIRMEXIT_YES 10
/**/


/**/




/* ======== Structs ======== */

typedef struct _cellInfo_t
{
	// Type: 0:Empty, 1:Fish, 2:Shark
	uint8_t type;

	// Number of rounds since last reproduction
	uint32_t reproductionTime;

	// Energy of this unit. This only applies to sharks.
	uint32_t energy;

	// This is set to TRUE if the fish was just born this step. It will be ignored.
	// bool_t newBorn;
} cellInfo_t;


typedef struct _keyList_t
{
	struct _keyList_t* prev;
	struct _keyList_t* next;
	int scanCode;
	bool_t flash;
	int frameDelay;
} keyList_t;

typedef struct _mouseState_t 
{
	bool_t LMT; bool_t RMT; int32_t x; int32_t y; size_t chrx; size_t chry; 
} mouseState_t;


typedef struct _borderStyle_t 
{
	int br,bl,tr,tl,vert,horz;
} borderStyle_t;


typedef struct _gameState
{
	/* Current primary state of the application */
	primaryState_t pState;

	/* Currently selected control ID */
	size_t selectedControl;


	/* Simulation dataset */
	cellInfo_t dataSet[SIM_Y][SIM_X]; 

	/* Frames since last simulation step */
	size_t simFrames;

	/* Is the simulation paused or not */
	bool_t paused;


	/* GAME SETTINGS */

	/* Simulation will be done every X frames */
	size_t gsSimFrameDelay;

	/* How much energy a new shark will have */
	size_t gsSharkStartEnergy;

	/* How many steps a fish must wait inbetween reproductions */
	size_t gsFishReproductionTime;

	/* How many steps a shark must wait inbetween reproductions */
	size_t gsSharkReproductionTime;

	/* Procentage of shark on screen at beginning of simulation */
	size_t gsSharkPercent;

	/* Amount of energy a shark will gain upon devouring a fish */
	size_t gsSharkEnergyGain;

	/**/


	/* GAME OVERVIEW */
	size_t sharkCount;
	size_t fishCount;
	/**/

} gameState_t;

/**/







/* ======== Global const ======== */
/* TODO: gc->g */
EXTERN color_t gcClrTransparent;
EXTERN color_t gcClrWhite;

EXTERN color_t gcClrBlack;
EXTERN color_t gcClrBlackDark;

EXTERN color_t gcClrAbsoluteBlack;

EXTERN color_t gcClrRed;
EXTERN color_t gcClrRedDark;

EXTERN color_t gcClrGreen;
EXTERN color_t gcClrGreenDark;

EXTERN color_t gcClrBlue;
EXTERN color_t gcClrBlueDark;

EXTERN color_t gcClrYellow;
EXTERN color_t gcClrYellowDark;

EXTERN color_t gcClrMagenta;
EXTERN color_t gcClrMagentaDark;

EXTERN color_t gcClrCyan;
EXTERN color_t gcClrCyanDark;

EXTERN color_t gcClrGray;
EXTERN color_t gcClrGrayDark;
/**/




/* ======== Global variables ======== */

/* Char size: WIDTH */
EXTERN size_t gCharW;

/* Char size: height */
EXTERN size_t gCharH;

/* Screen size: WIDTH */
EXTERN size_t gScrW;

/* Screen size: HEIGHT */
EXTERN size_t gScrH;

/* main sets this to true if the texture path is already set by the commandline */
EXTERN bool_t gTexOverride;

/* Texture file name */
EXTERN char gTexName[128];

/* Texture map */
EXTERN ptrmapptr_t gTexMap[255];

/* Number of cached textures */
EXTERN size_t gTexCount;

/* Main game window */
EXTERN SDL_Window* gMainWindow;

/* Main renderer */
EXTERN SDL_Renderer* gMainRenderer;

/* Main texture representing the screen */
EXTERN SDL_Texture* gScreenTexture;

/* The Pixelformat used by all surfaces */
EXTERN SDL_PixelFormat* gFormat;

/* The buffer every draw call function draws on to. Will be written to screen texture at the end of each render step. */
EXTERN SDL_Surface* gDrawSurface;

/* Surface that contains the ASCII characters */
EXTERN SDL_Surface* gCursesSurface;

/* Current delay on user input */
//EXTERN int gInputDelay;

/* Current FPS */
EXTERN double gFPS;

/* Holds FPS values to calculate moving average */
EXTERN double gFPSArray[FPSFILTERLEN];

/* Last end of frame */
EXTERN long gLastTime;

/* Vsync */
EXTERN bool_t gUseVsync;

/* Start time */
EXTERN int gStartTime;

/* Current key states. Index with scancodes. Only assign once using SDL_GetKeyboardState, SDL_PumpEvents updates this array. */
//EXTERN cuint8ptr_t gKeyboardState;
EXTERN bool_t gKeyboardState[KEYSTATELEN];

/* A key press will be reset after one frame if it is not marked as REPEAT. SDL gives repeat event after x sec of cont. press */
EXTERN bool_t gKeyIsRepeat[KEYSTATELEN];

/* Current mouse state. Has to be updated after SDL_PumpEvents using SDL_GetMouseState. */
EXTERN mouseState_t gMouseState;

/* If this is set to TRUE the main loop will shut down the game. */
EXTERN bool_t gPendingQuit;

/* Current state the game is in. */
EXTERN gameState_t gCurrentState;


/**/




/* CURSES */
#define CURSES_SINGLECORNER_BR 217
#define CURSES_SINGLECORNER_TR 191
#define CURSES_SINGLECORNER_BL 192
#define CURSES_SINGLECORNER_TL 218
#define CURSES_SINGLEBAR_VERT 179
#define CURSES_SINGLEBAR_HORZ 196
/**/


// TODO: is this good practice? Maybe remove this and just use scancodes directly
/* KEYS */
#define KEY_A SDL_SCANCODE_A
#define KEY_B SDL_SCANCODE_B
#define KEY_C SDL_SCANCODE_C
#define KEY_D SDL_SCANCODE_D
#define KEY_E SDL_SCANCODE_E
#define KEY_F SDL_SCANCODE_F
#define KEY_G SDL_SCANCODE_G
#define KEY_H SDL_SCANCODE_H
#define KEY_I SDL_SCANCODE_I
#define KEY_J SDL_SCANCODE_J
#define KEY_K SDL_SCANCODE_K
#define KEY_L SDL_SCANCODE_L
#define KEY_M SDL_SCANCODE_M
#define KEY_N SDL_SCANCODE_N
#define KEY_O SDL_SCANCODE_O
#define KEY_P SDL_SCANCODE_P
#define KEY_Q SDL_SCANCODE_Q
#define KEY_R SDL_SCANCODE_R
#define KEY_S SDL_SCANCODE_S
#define KEY_T SDL_SCANCODE_T
#define KEY_U SDL_SCANCODE_U
#define KEY_V SDL_SCANCODE_V
#define KEY_W SDL_SCANCODE_W
#define KEY_X SDL_SCANCODE_X
#define KEY_Y SDL_SCANCODE_Y
#define KEY_Z SDL_SCANCODE_Z


#define KEY_1 SDL_SCANCODE_1
#define KEY_2 SDL_SCANCODE_2
#define KEY_3 SDL_SCANCODE_3
#define KEY_4 SDL_SCANCODE_4
#define KEY_5 SDL_SCANCODE_5
#define KEY_6 SDL_SCANCODE_6
#define KEY_7 SDL_SCANCODE_7
#define KEY_8 SDL_SCANCODE_8
#define KEY_9 SDL_SCANCODE_9
#define KEY_0 SDL_SCANCODE_0

#define KEY_RIGHT SDL_SCANCODE_RIGHT
#define KEY_LEFT SDL_SCANCODE_LEFT
#define KEY_DOWN SDL_SCANCODE_DOWN
#define KEY_UP SDL_SCANCODE_UP
#define KEY_RETURN SDL_SCANCODE_RETURN
#define KEY_ESC SDL_SCANCODE_ESCAPE
#define KEY_BSPACE SDL_SCANCODE_BACKSPACE
#define KEY_TAB SDL_SCANCODE_TAB
#define KEY_SPACE SDL_SCANCODE_SPACE

#define KEY_LALT SDL_SCANCODE_LALT
/**/


