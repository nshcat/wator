#include <game.h>

/* MAIN ENTRY POINT */
int main(int argc, char* args[])
{
	// Check for texture file override from command line
	if(argc > 1 && SDL_strcmp(args[1], "--tex") == 0)
	{
		SDL_strlcpy(gTexName, args[2], 127);
		gTexOverride = TRUE;
	}
	else
	{
		// Backup, may remove this since it will be loaded from config file
		SDL_strlcpy(gTexName, "ascii.bmp", 127);
		gTexOverride = FALSE;
	}


	// Run the game
	run();


#ifdef DEBUGOUTPUT
	out("Press any key to continue.");
	//getchar();
#endif

	return 0;
}
/**/