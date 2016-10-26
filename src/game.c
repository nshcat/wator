

/* Global variables are declared in this file. */
#define GLOBAL_H_MAIN
#include <global.h>
#undef GLOBAL_H_MAIN

#include <game.h>



// TODO implement options for alternative rule sets (sharks breed when reaching certain energy level, split up energy between 
//      shark and new shark

// TODO implement cleanup() to cleanly shut down SDL

// Interessting settings: {1,2,2,10,1} Equilibirum, but the fishe population tends to "explode" and then collapse again

// {2,3,1,10,1} : very pulsing


int run()
{
	if(init() > 0)
		return 1;


	// MAIN LOOP
	SDL_Event evnt;
	while(!gPendingQuit)
	{
		while(SDL_PollEvent(&evnt))
		{
			switch(evnt.type)
			{
				/* SDL_QUIT event (window close) */
			case SDL_QUIT:
				gPendingQuit = TRUE;
				break;
			case SDL_KEYUP:
				gKeyboardState[evnt.key.keysym.scancode] = FALSE;
				gKeyIsRepeat[evnt.key.keysym.scancode] = FALSE;
				break;
			case SDL_KEYDOWN:
			
				if(evnt.key.repeat) gKeyIsRepeat[evnt.key.keysym.scancode] = TRUE;
				gKeyboardState[evnt.key.keysym.scancode] = TRUE;

				// Modifiers
				processModifiers(evnt.key.keysym.mod);
				
				break;
			default:
				break;
			}
		}
		mouse();

		logic();

		render();

		// Every key press which is not markes as REPEATED will be revoked after one frame
		resetKeys();

		calculateFps();

		if(!gUseVsync) SDL_Delay(5);
	}



	return 0;
}


// TODO nicht bei jeder Unterfunktion die Configfile neu laden.. das ist dumm
int init()
{
	out("WATOR v0.1 by nshcat\n");
	out("Debug output is enabled.");

	initSystemSettings();

	if(initSDL() || initTextures()) return 1;

	initColors();

	initGlobals();


	initNewSimulation();


	out("Setup done.");
	return 0;
}

void initSystemSettings()
{	
	// Open cfg file
	bttfileptr_t cfgfile = bttfile_create(CONFIGFILE);
	bttfile_read(cfgfile);

	// VSync
	gUseVsync = bttfile_get(cfgfile, "SystemSettings.useVSync")->payload.TypeBoolean.value;

	// Read texture path if it is not overridden by commandline
	if(!gTexOverride)
	{
		tagptr_t textag = bttfile_get(cfgfile, "SystemSettings.textureName");
		SDL_strlcpy(gTexName, textag->payload.TypeString.data, 127);
	}



	bttfile_destroy(cfgfile);
}


int initSDL()
{
	out("Initializing SDL..");
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		error("Could not initialize SDL.");
		return 1;
	}

	out("Creating window and renderer..");
	// Create window
	gMainWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 100, 100, SDL_WINDOW_SHOWN);

	if(gMainWindow == NULL)
	{
		error("Could not create main window.");
		return 1;
	}


	// Create renderer
	gMainRenderer = SDL_CreateRenderer(gMainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | (gUseVsync ? SDL_RENDERER_PRESENTVSYNC : 0));

	if(gMainRenderer == NULL)
	{
		error("Could not create main renderer.");
		return 1;
	}

	
	// Get format from window surface
	gFormat = SDL_GetWindowSurface(gMainWindow)->format;


	// TODO this is not needed anymore
	// Create draw surface and screen texture
	gDrawSurface = SDL_CreateRGBSurface(0, gScrW, gScrH, gFormat->BitsPerPixel, gFormat->Rmask, gFormat->Gmask, gFormat->Bmask, gFormat->Amask);

	gScreenTexture = SDL_CreateTexture(gMainRenderer, gFormat->format, SDL_TEXTUREACCESS_STREAMING, gScrW, gScrH);


	return 0;
}

int initTextures()
{
	out("Loading textures..");

	// Load ASCII into surface
	SDL_Surface* temp = SDL_LoadBMP(gTexName);

	if(temp == NULL)
	{
		error("Could not load ASCII texture file.");
		return 1;
	}

	// Convert texture format
	gCursesSurface = SDL_ConvertSurfaceFormat(temp, gFormat->format, 0);

	// Free temporary surface
	SDL_FreeSurface(temp);

	// Calculate char size SDL_ConvertSurfaceFormat
	gCharH = gCursesSurface->h/16;
	gCharW = gCursesSurface->w/16;

	// Init screen size
	gScrW = gCharW * 200;
	gScrH = gCharH * 75;


	// Set window position according to texture tile size
	SDL_SetWindowSize(gMainWindow, gScrW, gScrH);

	out("Loaded textures.");
	char buf[128];
	sprintf_s(buf, 128, "Tile size is %dx%d",gCharW, gCharH);
	out(buf);
	sprintf_s(buf, 128, "Screen size is %dx%d", gScrW, gScrH);
	out(buf);

	return 0;
}


color_t loadColor(const charptr_t clrName, bttfileptr_t file)
{
	// Get RGB components
	char buf[128];
	uint8_t r, g, b;

	sprintf_s(buf, 128, "ColorScheme.clr%s.R", clrName);
	r = bttfile_get(file, buf)->payload.TypeByte.value;

	sprintf_s(buf, 128, "ColorScheme.clr%s.G", clrName);
	g = bttfile_get(file, buf)->payload.TypeByte.value;

	sprintf_s(buf, 128, "ColorScheme.clr%s.B", clrName);
	b = bttfile_get(file, buf)->payload.TypeByte.value;

	// Create color
	return SDL_MapRGB(gFormat, r, g, b);
}

void initColors()
{
	// Open config file
	bttfileptr_t cfgfile = bttfile_create(CONFIGFILE);
	bttfile_read(cfgfile);

	// Read colors
#define LC(x) loadColor( x , cfgfile)
	gcClrWhite = LC("White");
	gcClrBlack = LC("Black");
	gcClrBlackDark = LC("BlackDark");
	gcClrAbsoluteBlack = LC("AbsoluteBlack");
	gcClrTransparent = LC("Transparent");
	gcClrBlue = LC("Blue");
	gcClrBlueDark = LC("BlueDark");
	gcClrRed = LC("Red");
	gcClrRedDark = LC("RedDark");
	gcClrCyan = LC("Cyan");
	gcClrCyanDark = LC("CyanDark");
	gcClrGray = LC("Gray");
	gcClrGrayDark = LC("GrayDark");
	gcClrGreen = LC("Green");
	gcClrGreenDark = LC("GreenDark");
	gcClrYellow = LC("Yellow");
	gcClrYellowDark = LC("YellowDark");
	gcClrMagenta = LC("Magenta");
	gcClrMagentaDark = LC("MagentaDark");
#undef LC

	// Set color key
	SDL_SetColorKey(gCursesSurface, SDL_TRUE, gcClrTransparent);
		
	// Close config file
	bttfile_destroy(cfgfile);

	return;
}


void processModifiers(uint16_t mod)
{
	gKeyboardState[KEY_LALT] = mod & KMOD_LALT;
	

	return;
}

void initGlobals()
{
	// Init ptrmaps
	for(size_t i = 0; i < 255; i++)
		gTexMap[i] = ptrmap_create(5000);




	gPendingQuit = FALSE;
	gStartTime = SDL_GetTicks();
	gFPS = 0.0;
	gLastTime = gStartTime;

	for(size_t i = 0; i < FPSFILTERLEN; i++)
		gFPSArray[i] = 0.0;


	gTexCount = 0;

	// TODO WIEDER NUTZBAR MACHEN gKeyboardState = SDL_GetKeyboardState(NULL);

	gMouseState = (mouseState_t){0};

	gCurrentState = (gameState_t){0};
	gCurrentState.pState = HOME;
	
	
	SETSELECTED(ID_OVERVIEW_FRAMEDELAY);

	gCurrentState.simFrames = 40;
	gCurrentState.paused = TRUE;

	/*gCurrentState.gsSharkPercent = 1;
	gCurrentState.gsFishReproductionTime = 1;
	gCurrentState.gsSharkReproductionTime = 10;
	gCurrentState.gsSimFrameDelay = 1;
	gCurrentState.gsSharkStartEnergy = 2;
	gCurrentState.gsSharkEnergyGain = 2;*/

	gCurrentState.gsSharkPercent = 2;
	gCurrentState.gsFishReproductionTime = 1;
	gCurrentState.gsSharkReproductionTime = 10;
	gCurrentState.gsSimFrameDelay = 1;
	gCurrentState.gsSharkStartEnergy = 3;
	gCurrentState.gsSharkEnergyGain = 1;

	
	for(size_t i = 0; i < KEYSTATELEN; i++)
	{
		gKeyboardState[i] = 0;
		gKeyIsRepeat[i] = 0;
	}

	SDL_memset(gCurrentState.dataSet, 0, sizeof(cellInfo_t)*SIM_X*SIM_Y);

	return;
}



void resetKeys()
{
	for(size_t i = 0; i < KEYSTATELEN; i++)
	{
		if(gKeyboardState[i] && !gKeyIsRepeat[i])
		{
			gKeyboardState[i] = FALSE;
		}
	}

	return;
}



void error(const charptr_t errprompt)
{
#ifdef DEBUGOUTPUT
	char buf[128];
	getTime(buf, 128);

	printf("%s [ERROR] %s. %s\n", buf, errprompt, SDL_GetError());
#endif
	return;
}

void out(const charptr_t outmsg)
{
	char buf[128];
	getTime(buf, 128);

	printf("%s [INFO] %s\n", buf, outmsg);

	return;
}


void getTime(charptr_t buf, size_t buflen)
{
	// Get time
	time_t timer;
	struct tm* tm_info;
	time(&timer);
	tm_info = localtime(&timer);

	strftime(buf, buflen, "[%Y:%m:%d|%H:%M:%S]", tm_info);

	return;
}


void drawMain()
{
	drawBorder((borderStyle_t){CURSES_SINGLECORNER_BR, CURSES_SINGLECORNER_BL, CURSES_SINGLECORNER_TR, CURSES_SINGLECORNER_TL, CURSES_SINGLEBAR_VERT, CURSES_SINGLEBAR_HORZ },
		(SDL_Rect){0,0,SCR_W_CHR,SCR_H_CHR}, gcClrBlueDark, gcClrGray);

	return;
}

void clearScreen()
{
	// Clear the screen
	uint8_t r,g,b,a;

	SDL_GetRGBA(gcClrBlueDark, gFormat, &r, &g, &b, &a);

	SDL_SetRenderDrawColor(gMainRenderer, r, g, b, a);
	SDL_RenderClear(gMainRenderer);

	return;
}

void render()
{
	clearScreen();
	
	drawMain();
	drawFps();
	drawStatusBar();

	drawSimulationScreen();
	drawOverviewScreen();




	if(ISSTATE(CONFIRMEXIT))
	{
		drawExitConfirmScreen();
	}
	else if(ISSTATE(NEWGAME))
	{
		drawNewGameScreen();
	}

	SDL_RenderPresent(gMainRenderer);
}

void drawFps()
{
	char fpsBuf[128];
	sprintf(fpsBuf, "FPS: %d, CT: %d", (int) gFPS, gTexCount);


	drawString(fpsBuf, SCR_W_CHR - 20, 0, gcClrGray, gcClrRed);

	return;
}


void calculateFps()
{
	static size_t pos = 0;
	/*static int numFrames = 1;

	gFPS = numFrames / ( (SDL_GetTicks() - gStartTime) / 1000.0);
	numFrames++;

	return;*/

	// Calculate current FPS based on time needed for this frame
	long newTime = SDL_GetTicks();
	long frameTimeMS = newTime-gLastTime;
	gLastTime = newTime;
	double fps = 1000.0 / (double)frameTimeMS;


	// Save it in the filter array
	gFPSArray[pos] = fps;
	pos = (pos+1)%FPSFILTERLEN;


	// Calculate moving average of all fps values to create current fps
	double fpsSmoothed = 0.0;

	for(size_t i = 0; i < FPSFILTERLEN; i++)
	{
		fpsSmoothed += gFPSArray[i];
	}
	fpsSmoothed /= ((double)FPSFILTERLEN);

	gFPS = fpsSmoothed;

	return;
}


void mouse()
{
	Uint32 state = SDL_GetMouseState(&gMouseState.x, &gMouseState.y);
	gMouseState.chrx = coordToCharsX(gMouseState.x);
	gMouseState.chry = coordToCharsY(gMouseState.y);
	gMouseState.LMT = state & SDL_BUTTON(SDL_BUTTON_LEFT);
	gMouseState.RMT = state & SDL_BUTTON(SDL_BUTTON_RIGHT);

	return;
}

void drawStatusBar()
{
	// Paused state
	if(gCurrentState.paused)
	{
		drawString("PAUSED", 2, 0, gcClrGray, gcClrRed);
	}


	// TODO make this automatic
	drawString("[ESC]", 2, SCR_H_CHR-1, gcClrGray, gcClrRed);
	drawString(" exit", 7, SCR_H_CHR-1, gcClrGray, gcClrBlack);


	drawString("[P]", 13, SCR_H_CHR-1, gcClrGray, gcClrRed);
	drawString(" pause", 16, SCR_H_CHR-1, gcClrGray, gcClrBlack);

	drawString("[N]", 23, SCR_H_CHR-1, gcClrGray, gcClrRed);
	drawString(" new", 26, SCR_H_CHR-1, gcClrGray, gcClrBlack);


	return;
}


size_t coordToCharsX(int x)
{
	return x/gCharW;
}


size_t coordToCharsY(int y)
{
	return y/gCharH;
}


void processShortcuts(const uint32_t keys[], const uint32_t ids[], size_t len)
{
	for(size_t i = 0; i < len; i++)
	{
		if(KEYDOWN(keys[i]))
		{
			SETSELECTED(ids[i]);
			return;
		}
	}

	return;
}



void drawNewGameScreen()
{
	drawWindow(80, 25, 40, 17, TRUE, gcClrBlue, "New Game");

	drawNumBox(83, 28, 80+3+28, ID_NEWGAME_SPERC, TRUE, gCurrentState.gsSharkPercent, "Shark Percentage:");
	drawNumBox(83, 30, 80+3+28, ID_NEWGAME_SSENER, TRUE, gCurrentState.gsSharkStartEnergy, "Shark Start Energy:");
	drawNumBox(83, 32, 80+3+28, ID_NEWGAME_SEGAIN, TRUE, gCurrentState.gsSharkEnergyGain, "Shark Energy Gain:");
	drawNumBox(83, 34, 80+3+28, ID_NEWGAME_SREPT, TRUE, gCurrentState.gsSharkReproductionTime, "Shark Reproduction Time:");
	drawNumBox(83, 36, 80+3+28, ID_NEWGAME_FREPT, TRUE, gCurrentState.gsFishReproductionTime, "Fish Reproduction Time:");

	drawButton(86, 39, 8, ID_NEWGAME_OK, 0, "Ok");
	drawButton(105,39, 8, ID_NEWGAME_CANCEL, 0, "Cancel");
}


void logic()
{
	static size_t frames = 0;


	inputLogic();


	if(!gCurrentState.paused && frames >= gCurrentState.gsSimFrameDelay)
	{
		frames = 0;

		doSimulationStep();
	}
	else
	{
		frames++;
	}



}

void drawExitConfirmScreen()
{
	drawWindow(80, 30, 40, 9, TRUE, gcClrBlue, "Confirm Exit");

	drawString("Do you really want to exit?", 86, 33, gcClrGray, gcClrBlack);

	drawButton(86, 36, 8, ID_CONFIRMEXIT_YES, 0, "Ok");
	drawButton(105, 36, 8, ID_CONFIRMEXIT_NO, 0, "No");

	return;
}


void drawOverviewScreen()
{
	drawWindow(SIM_X+12, 3, 30, 13, TRUE, gcClrBlue, "OVERVIEW");

	drawNumBox(SIM_X+15, 6, SIM_X+15+18, ID_NONE, FALSE, gCurrentState.sharkCount, "Current Sharks:");
	drawNumBox(SIM_X+15, 8, SIM_X+15+18, ID_NONE, FALSE, gCurrentState.fishCount, "Current Fish:");
	drawNumBox(SIM_X+15, 11, SIM_X+15+18, ID_OVERVIEW_FRAMEDELAY, TRUE, gCurrentState.gsSimFrameDelay, "Frame delay:");

	drawCheckbox(SIM_X+15, 13, SIM_X+15+18+1, ID_NONE, gUseVsync, "VSync:");

	return;
}

void inputLogic()
{
	switch (gCurrentState.pState)
	{
	case HOME:
		{
			if(KEYDOWN(KEY_ESC))
			{
				gCurrentState.paused = TRUE;

				SETSTATE(CONFIRMEXIT);
				SETSELECTED(ID_CONFIRMEXIT_NO);

				// Return to stop any more keypresses to come through
				return;
			}
			else if(KEYDOWN(KEY_N))
			{
				gCurrentState.paused = TRUE;
				SETSTATE(NEWGAME);
				SETSELECTED(ID_NEWGAME_SPERC);

				// Return to stop any more keypresses to come through
				return;
			}

			if(KEYDOWN(KEY_P))
			{
				gCurrentState.paused = !gCurrentState.paused;
			}

			if(ISSELECTED(ID_OVERVIEW_FRAMEDELAY))
			{
				if(KEYDOWN(KEY_LEFT) || KEYDOWN(KEY_RIGHT))
				{
					MODVAL_SGN(gCurrentState.gsSimFrameDelay, KEYDOWN(KEY_RIGHT), 1, 100);
				}
			}
			break;
		}
	case CONFIRMEXIT:
		{
			if(KEYDOWN(KEY_LALT))
			{
				SHORTCUT(KEY_O, ID_CONFIRMEXIT_YES);
				SHORTCUT(KEY_N, ID_CONFIRMEXIT_NO);
			}
			if(KEYDOWN(KEY_LEFT) || KEYDOWN(KEY_RIGHT))
			{
				MODVAL_SGN(SELECTEDCTRL, KEYDOWN(KEY_LEFT), 9, 10);
			}
			else if(KEYDOWN(KEY_RETURN))
			{
				if(ISSELECTED(ID_CONFIRMEXIT_YES)) gPendingQuit = TRUE;

				SETSTATE(HOME);
				SETSELECTED(ID_OVERVIEW_FRAMEDELAY);
			}
			break;
		}
	case NEWGAME:
		{
			if(KEYDOWN(KEY_LALT))
			{
				SHORTCUT(KEY_O, ID_NEWGAME_OK);
				SHORTCUT(KEY_C, ID_NEWGAME_CANCEL);
			}
			if(KEYDOWN(KEY_LEFT) || KEYDOWN(KEY_RIGHT))
			{
				int sign = KEYDOWN(KEY_LEFT) ? -1 : 1;

				switch (SELECTEDCTRL)
				{
				case ID_NEWGAME_FREPT:		MODVAL(gCurrentState.gsFishReproductionTime, sign, 1, 80); break;
				case ID_NEWGAME_SREPT:		MODVAL(gCurrentState.gsSharkReproductionTime, sign, 1, 80); break;
				case ID_NEWGAME_SEGAIN:		MODVAL(gCurrentState.gsSharkEnergyGain, sign, 1, 80); break;
				case ID_NEWGAME_SSENER:		MODVAL(gCurrentState.gsSharkStartEnergy, sign, 1, 80); break;
				case ID_NEWGAME_SPERC:		MODVAL(gCurrentState.gsSharkPercent, sign, 1, 95); break;
				default:					break;
				}
			}
			else if(KEYDOWN(KEY_UP) || KEYDOWN(KEY_DOWN))
			{
				MODVAL_SGN(SELECTEDCTRL, KEYDOWN(KEY_DOWN), 2, 8); 
			}
			else if(KEYDOWN(KEY_RETURN) && (ISSELECTED(ID_NEWGAME_CANCEL) || ISSELECTED(ID_NEWGAME_OK)))
			{
				if(ISSELECTED(ID_NEWGAME_OK)) initNewSimulation();

				SETSTATE(HOME);
				SETSELECTED(ID_OVERVIEW_FRAMEDELAY);
			}

			break;
		}	
	}
}



void drawDataSet()
{
	for(int ix = 0; ix < SIM_X; ix++)
	{
		for(int iy = 0; iy < SIM_Y; iy++)
		{
			uint8_t type = gCurrentState.dataSet[iy][ix].type;

			drawAscii(' ', ix+5, iy+4, (type == 1 ? gcClrGreen : (type == 2 ? gcClrRed : gcClrAbsoluteBlack)), gcClrBlack);
		}
	}
	return;
}





void drawSimulationScreen()
{
	// Simulation screen

	// Shadow
	/*drawRect(' ', (SDL_Rect){5,4, SIM_X+2, SIM_Y+2}, FALSE,  gcClrBlack, gcClrBlack);



	// Border
	drawBorder((borderStyle_t){CURSES_SINGLECORNER_BR, CURSES_SINGLECORNER_BL, CURSES_SINGLECORNER_TR, CURSES_SINGLECORNER_TL, CURSES_SINGLEBAR_VERT, CURSES_SINGLEBAR_HORZ },
		(SDL_Rect){4,3, SIM_X+2, SIM_Y+2}, gcClrBlue, gcClrGray);

	// Title
	drawString("SIMULATION WINDOW", (((SIM_X+2)/2)-5), 3, gcClrGray, gcClrBlack);*/

	drawWindow(4, 3, SIM_X+2, SIM_Y+2, FALSE, gcClrBlue, "SIMULATION WINDOW");

	// Data
	drawDataSet();
}