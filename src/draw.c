#include <draw.h>


SDL_Texture* getTexture(int chr, color_t back, color_t fore)
{
	// TODO check for existence and get can be done in one operation.

	// Check if there is a colour entry for back
	if(!ptrmap_contains_key((ptrmapptr_t)gTexMap[chr], back))
	{
		// Create it
		ptrmapptr_t x = ptrmap_create(5000);

		// Add it
		ptrmap_add((ptrmapptr_t)gTexMap[chr], back, x);
	}

	// Get the entry
	ptrmapptr_t foreMap = (ptrmapptr_t)ptrmap_get((ptrmapptr_t)gTexMap[chr], back);


	// Check if there is a colour entry for fore
	if(!ptrmap_contains_key(foreMap, fore))
	{
		// We have to create the Texture

		SDL_Texture* x = createTexture(chr, back, fore);		

		// Insert it
		ptrmap_add(foreMap, fore, x);
	}

	// Get the texture
	SDL_Texture* x = (SDL_Texture*)ptrmap_get(foreMap, fore);

	return x;
}




SDL_Texture* createTexture(int chr, color_t back, color_t fore)
{
	gTexCount++;
	SDL_Surface* h = getAsciiSurface(chr, back, fore);

	SDL_Texture* x = SDL_CreateTextureFromSurface(gMainRenderer, h);

	SDL_FreeSurface(h);

	return x;
}



SDL_Surface* getAsciiSurface(int chr, color_t backClr, color_t foreClr)
{
	SDL_Surface* temp;
	SDL_Surface* dest;
	int srcx = gCharW*(chr%16);
	int srcy = gCharH*(chr/16);

	SDL_Rect srcrect = { srcx, srcy, gCharW, gCharH };
	SDL_Rect destrect = { 0, 0, gCharW, gCharH };


	// Create temporary surfaces
	temp = SDL_CreateRGBSurface(0, gCharW, gCharH, gFormat->BitsPerPixel, gFormat->Rmask, gFormat->Gmask, gFormat->Bmask, gFormat->Amask);
	dest = SDL_CreateRGBSurface(0, gCharW, gCharH, gFormat->BitsPerPixel, gFormat->Rmask, gFormat->Gmask, gFormat->Bmask, gFormat->Amask);

	SDL_SetColorKey(dest, SDL_TRUE, gcClrTransparent);

	SDL_FillRect(dest, &destrect, foreClr);
	SDL_BlitSurface(gCursesSurface, &srcrect, dest, &destrect);

	SDL_FillRect(temp, NULL, backClr);

	SDL_SetColorKey(gCursesSurface, SDL_TRUE, gcClrAbsoluteBlack);

	// Blit it
	SDL_BlitSurface(gCursesSurface, &srcrect, temp, NULL);

	SDL_SetColorKey(gCursesSurface, SDL_TRUE, gcClrTransparent);
	SDL_SetColorKey(temp, SDL_TRUE, gcClrTransparent);

	// Blit temp to dest
	SDL_BlitSurface(temp, NULL, dest, &destrect);

	SDL_FreeSurface(temp);

	return dest;
}


void drawAscii(size_t chr, size_t x, size_t y, color_t backClr, color_t foreClr)
{
	SDL_Rect destrect = { x*gCharW, y*gCharH, gCharW, gCharH};


	// Get Texture
	SDL_Texture* x_ = getTexture(chr, backClr, foreClr);

	// Render it
	SDL_RenderCopy(gMainRenderer, x_, NULL, &destrect);

	return;
}


void drawString(charptr_t str, size_t x, size_t y, color_t backClr, color_t foreClr)
{
	while(*str)
	{
		drawAscii(*str, x, y, backClr, foreClr);

		str++;
		x++;
	}

	return;
}


void drawRect(int chr, SDL_Rect rect, bool_t fill, color_t backClr, color_t foreClr)
{
	size_t ix,iy;


	for(ix = rect.x; ix < rect.x+rect.w; ix++)
	{
		for(iy = rect.y; iy < rect.y+rect.h; iy++)
		{
			/* if <fill> then everything is filled, if not then only the border is filled. */
			if(fill || ((iy == rect.y || iy == rect.y+rect.h-1) || ((ix == rect.x || ix == rect.x+rect.w-1))))
			{
				drawAscii(chr, ix, iy, backClr, foreClr);
			}
		}
	}

	return;
}

void drawBorder(borderStyle_t style, SDL_Rect rect, color_t backClr, color_t foreClr)
{
	size_t ix,iy;


	for(ix = rect.x; ix < rect.w+rect.x; ix++)
	{
		for(iy = rect.y; iy < rect.h+rect.y; iy++)
		{
			if(ix == rect.x || ix == rect.x+rect.w-1)
			{
				drawAscii(style.vert, ix, iy, backClr, foreClr);
			}
			else if(iy == rect.y || iy == rect.y+rect.h-1)
			{
				drawAscii(style.horz, ix, iy, backClr, foreClr);
			}
		}
	}

	drawAscii(style.tl, rect.x, rect.y, backClr, foreClr);
	drawAscii(style.br, rect.x+rect.w-1, rect.y+rect.h-1, backClr, foreClr);
	drawAscii(style.tr, rect.x+rect.w-1, rect.y, backClr, foreClr);
	drawAscii(style.bl, rect.x, rect.y+rect.h-1, backClr, foreClr);

	return;
}


void drawWindow(size_t x, size_t y, size_t w, size_t h, bool_t filled, color_t borderClr, const charptr_t name)
{
	// Shadow
	drawRect(' ', (SDL_Rect){x+1, y+1, w, h}, FALSE, gcClrBlack, gcClrBlack);

	// Window
	if(filled) drawRect(' ', (SDL_Rect){x, y, w, h}, TRUE,  gcClrGray, gcClrGray);

	// Border
	drawBorder((borderStyle_t){CURSES_SINGLECORNER_BR, CURSES_SINGLECORNER_BL, CURSES_SINGLECORNER_TR, CURSES_SINGLECORNER_TL, CURSES_SINGLEBAR_VERT, CURSES_SINGLEBAR_HORZ },
		(SDL_Rect){x, y, w, h}, borderClr, gcClrGray);

	// Title
	drawString(name, x+(w/2)-(SDL_strlen(name)/2)+1, y, gcClrGray, gcClrBlack);

	return;
}



void drawNumBox(size_t x, size_t y, size_t xfield, ctrlid_t controlID, bool_t changeable, int num, const charptr_t text)
{
	// Get string for number TODO cap the max size of number
	char buf[128];
	sprintf(buf, "%d", num);

	// Base
	drawString("     ", xfield, y, gcClrBlack, gcClrBlack);
	// Number
	drawString(buf, xfield, y, gcClrBlack, gcClrGray);
	// Text
	drawString(text, x, y, CLRSELECTED(controlID), gcClrBlack);

	if(changeable)
	{
		drawString("<", xfield-1, y, CLRONKEY(controlID, KEY_LEFT), gcClrBlack);
		drawString(">", xfield+5, y, CLRONKEY(controlID, KEY_RIGHT), gcClrBlack);
	}

	
	return;
}


void drawButton(size_t x, size_t y, size_t len, ctrlid_t controlID, int markedChar, const charptr_t text)
{
	



	char buf[128];
	sprintf(buf, "%*s%*s\n",((len-2)/2)+SDL_strlen(text)/2,text,((len-2)/2)-SDL_strlen(text)/2, "");
	drawString(buf, x+1, y,  CLRSELECTED(controlID), gcClrBlack);

	drawString("<", x, y, CLRSELECTED(controlID), gcClrBlack);
	drawString(">", x+len-1, y, CLRSELECTED(controlID), gcClrBlack);

	if(markedChar >= 0)
	{
		drawAscii(text[markedChar], x + ((len/2)-(SDL_strlen(text)/2) ) + markedChar, y, CLRSELECTED(controlID), gcClrAbsoluteBlack);
	}

	return;
}



void drawCheckbox(size_t x, size_t y, size_t xfield, ctrlid_t controlID, bool_t val, const charptr_t text)
{
	drawString(text, x, y, CLRSELECTED(controlID), gcClrBlack);
	drawString("[ ]", xfield, y, gcClrGray, gcClrBlack);
	drawString((val ? "X" : " "), xfield+1, y, gcClrGray, gcClrBlack);

	return;
}