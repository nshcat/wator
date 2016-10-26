#include <simulation.h>
#include <global.h>




int rand_lim(int limit) {
	/* return a random number between 0 and limit inclusive.
	*/

	int divisor = RAND_MAX/(limit+1);
	int retval;

	do { 
		retval = rand() / divisor;
	} while (retval > limit);

	return retval;
}

void doSimulationStep()
{
	// Go through every cell
	for(int ix = 0; ix < SIM_X; ix++)
	{
		for(int iy = 0; iy < SIM_Y; iy++)
		{
			// Switch cell type
			switch (gCurrentState.dataSet[iy][ix].type)
			{
				// SHARK
				case 2:
				{
					// Decrement energy
					gCurrentState.dataSet[iy][ix].energy--;

					// Increment reproduction time
					gCurrentState.dataSet[iy][ix].reproductionTime++;

					// If energy <= 0, this shark has to die
					if(gCurrentState.dataSet[iy][ix].energy <= 0)
					{
						gCurrentState.dataSet[iy][ix].type = 0;
						gCurrentState.sharkCount--;
					}
					else
					{
						// Try to eat a fish
						size_t direction = getAdjacentFish(ix, iy);

						// If there was no fish, try to find an empty spot to move to
						if(direction <= 0) direction = getAdjacentFree(ix, iy);

						

						// Check if there was a position available
						if(direction > 0)
						{
							// MOVE and EAT are the same action essentially
							moveShark(ix, iy, direction);
						}

						// If not, nothing happens.
					}

					break;
				}

				// FISH
				case 1:
				{
					gCurrentState.dataSet[iy][ix].reproductionTime++;

					// Try to find empty spot to move to
					size_t direction = getAdjacentFree(ix, iy);

					// If there was a free spot: move to it; if not: do nothing
					if(direction > 0)
					{
						moveFish(ix, iy, direction);
					}

					break;
				}

				default:
					break;
			}
		}
	}
}


size_t getNewPosX(size_t x, size_t direction)
{
	// X change for directions (RIGHT: +1)
	int xrel[9] = { 0, 0, 1, 1, 1, 0, -1, -1, -1 };

	int newx = x + xrel[direction];

	// Check for bounds
	if(newx < 0) newx = (SIM_X-1);
	else if(newx > (SIM_X-1)) newx = 0;

	return (size_t)newx;
}

// TODO combine this with getAdjacentFish. Just prioritize the fishes.
size_t getAdjacentFree(size_t simX, size_t simY)
{
	bool_t isEmpty[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	// Check for fish
	size_t count = 0;
	for(size_t i = 1; i < 9; i++)
	{
		if(gCurrentState.dataSet[getNewPosY(simY, i)][getNewPosX(simX, i)].type == 0 /* EMPTY */)
		{
			count++;
			isEmpty[i] = TRUE;
		}
	}

	if(count > 0)
	{
		// Get random cell
		size_t direction;

		do
		{
			direction = rand_lim(8);
		}
		while(direction <= 0 || !isEmpty[direction]);

		return direction;
	}
	else return 0;
}



size_t getAdjacentFish(size_t simX, size_t simY)
{
	bool_t isFish[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	// Check for fish
	size_t count = 0;
	for(size_t i = 1; i < 9; i++)
	{
		if(gCurrentState.dataSet[getNewPosY(simY, i)][getNewPosX(simX, i)].type == 1 /* FISH */)
		{
			count++;
			isFish[i] = TRUE;
		}
	}

	if(count > 0)
	{
		// Get random cell
		size_t direction;

		do
		{
			direction = rand_lim(8);
		}
		while(direction <= 0 || !isFish[direction]);

		return direction;
	}
	else return 0;
}


void moveShark(size_t curX, size_t curY, size_t direction)
{
	// Get new position
	size_t newx = getNewPosX(curX, direction);
	size_t newy = getNewPosY(curY, direction);


	// Check if we can breed
	bool_t breed = FALSE;

	if(gCurrentState.dataSet[curY][curX].reproductionTime >= gCurrentState.gsSharkReproductionTime)
	{
		breed = TRUE;

		// Reset the reproduction time
		gCurrentState.dataSet[curY][curX].reproductionTime = 0;
	}


	// Check if we devour something
	if(gCurrentState.dataSet[newy][newx].type == 1 /* FISH */)
	{
		// Increase sharks energy
		gCurrentState.dataSet[curY][curX].energy += gCurrentState.gsSharkEnergyGain;
		gCurrentState.fishCount--;
	}

	// Move shark to new position

	gCurrentState.dataSet[newy][newx].type = 2; // SHARK
	gCurrentState.dataSet[newy][newx].reproductionTime = gCurrentState.dataSet[curY][curX].reproductionTime;
	gCurrentState.dataSet[newy][newx].energy = gCurrentState.dataSet[curY][curX].energy;
	gCurrentState.dataSet[curY][curX].reproductionTime = 0;
	gCurrentState.dataSet[curY][curX].type = 0;
	gCurrentState.dataSet[curY][curX].energy = 0;


	// If we need to breed, create new shark
	if(breed)
	{
		gCurrentState.dataSet[curY][curX].type = 2; // SHARK
		gCurrentState.dataSet[curY][curX].energy = gCurrentState.gsSharkStartEnergy;
		gCurrentState.sharkCount++;
	}
}



void moveFish(size_t curX, size_t curY, size_t direction)
{
	// Get new position
	size_t newx = getNewPosX(curX, direction);
	size_t newy = getNewPosY(curY, direction);

	// Check if we can breed
	bool_t breed = FALSE;

	if(gCurrentState.dataSet[curY][curX].reproductionTime >= gCurrentState.gsFishReproductionTime)
	{
		breed = TRUE;

		// Reset the reproduction time
		gCurrentState.dataSet[curY][curX].reproductionTime = 0;
	}


	// Move fish
	gCurrentState.dataSet[newy][newx].type = 1; // FISH
	gCurrentState.dataSet[newy][newx].reproductionTime = gCurrentState.dataSet[curY][curX].reproductionTime;
	gCurrentState.dataSet[newy][newx].energy = 0; // FISH do not have energy
	gCurrentState.dataSet[curY][curX].reproductionTime = 0;
	gCurrentState.dataSet[curY][curX].type = 0;
	gCurrentState.dataSet[curY][curX].energy = 0;

	// If we need to breed, create new fish
	if(breed)
	{
		gCurrentState.dataSet[curY][curX].type = 1; // FISH
		gCurrentState.fishCount++;
	}
}



size_t getNewPosY(size_t y, size_t direction)
{
	// Y change for directions (DOWN : +1)
	int yrel[9] = { 0, -1, -1, 0, +1, +1, +1, 0, -1 };

	int newy = y + yrel[direction];

	// Check for bounds
	if(newy < 0) newy = (SIM_Y-1);
	else if(newy > (SIM_Y-1)) newy = 0;

	return (size_t)newy;
}



void initNewSimulation()
{

	// Clear the data Set
	SDL_memset(gCurrentState.dataSet, 0, sizeof(cellInfo_t)*SIM_X*SIM_Y);

	gCurrentState.fishCount = 0;
	gCurrentState.sharkCount = 0;


	// Seed random
	srand(time(NULL));

	// Spawn sharks
	for(int cnt = (SIM_X*SIM_Y)*(((float)gCurrentState.gsSharkPercent)/100.f); cnt > 0; cnt--)
	{
		bool_t spawned = FALSE;

		do
		{
			int x = rand_lim(SIM_X-1);
			int y = rand_lim(SIM_Y-1);

			if(gCurrentState.dataSet[y][x].type == 0)
			{
				gCurrentState.dataSet[y][x].type = 2;
				gCurrentState.dataSet[y][x].energy = gCurrentState.gsSharkStartEnergy;
				spawned = TRUE;
			}

		} while(!spawned);

		gCurrentState.sharkCount++;
	}


	// Spawn fish
	for(int ix = 0; ix < SIM_X; ix++)
	{
		for(int iy = 0; iy < SIM_Y; iy++)
		{
			if(gCurrentState.dataSet[iy][ix].type == 0)
			{
				gCurrentState.dataSet[iy][ix].type = 1;
				gCurrentState.fishCount++;
			}
		}
	}
}