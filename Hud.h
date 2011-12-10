#ifndef HUD_H
#define HUD_H

#include "Model.h"
#include "DrawableGeometry.h"

class Hud
{
public:
	Hud(void);
	~Hud(void);
	static void drawMeta();
	static void drawMini();
};

#endif