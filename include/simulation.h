#pragma once

#include <global.h>

/* ======== Simulation ======== */
void doSimulationStep();
void initNewSimulation();

/* Returns a random adjacent free field. 0 if no free field is there. 1:N, 2:NE, 3:E, 4:SE, 5:S, 6:SW, 7:W, 8:NW */
size_t getAdjacentFree(size_t simX, size_t simY);

/* Returns a random adjacent fish field. 0 if no fish field is there. 1:N, 2:NE, 3:E, 4:SE, 5:S, 6:SW, 7:W, 8:NW */
size_t getAdjacentFish(size_t simX, size_t simY);

/* Moves the shark in the given direction. If there is a fish, the fish is devoured and the shark gains health. If shark can reproduce,
   this will leave a new shark in the old cell. */
void moveShark(size_t curX, size_t curY, size_t direction);

/* Moves a fish in the given direction. If fish can reproduce, this will leave a new fish in the old cell. */
void moveFish(size_t curX, size_t curY, size_t direction);
/**/




/* ======== Utility ======== */
size_t getNewPosX(size_t x, size_t direction);
size_t getNewPosY(size_t y, size_t direction);
int rand_lim(int limit);
/**/