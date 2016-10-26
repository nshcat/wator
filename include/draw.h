#pragma once

#include <global.h>


/* ======== Texture Handling and Caching ======== */
SDL_Texture* getTexture(int chr, color_t back, color_t fore);
SDL_Texture* createTexture(int chr, color_t back, color_t fore);
SDL_Surface* getAsciiSurface(int chr, color_t backClr, color_t foreClr);
/**/


/* ======== Primitive Draw Routines ======== */
void drawCurses(size_t chrx, size_t chry, size_t x, size_t y, color_t backClr, color_t foreClr);
void drawAscii(size_t chr, size_t x, size_t y, color_t backClr, color_t foreClr);
void drawString(const charptr_t str, size_t x, size_t y, color_t backClr, color_t foreClr);
void drawRect(int chr, SDL_Rect rect, bool_t fill, color_t backClr, color_t foreClr);
void drawBorder(borderStyle_t style, SDL_Rect rect, color_t backClr, color_t foreClr);
/**/


/* ======== Complex Draw Routines ======== */
void drawWindow(size_t x, size_t y, size_t w, size_t h, bool_t filled, color_t borderClr, const charptr_t name);
void drawNumBox(size_t x, size_t y, size_t xfield, ctrlid_t controlID, bool_t changeable, int num, const charptr_t text);
void drawButton(size_t x, size_t y, size_t len, ctrlid_t controlID, int markedChar, const charptr_t text);
void drawCheckbox(size_t x, size_t y, size_t xfield, ctrlid_t controlID, bool_t val, const charptr_t text);
/**/

