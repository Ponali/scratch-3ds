#include <citro2d.h>

static initframe=true;

static C2D_Sprite spriteroni;
static C2D_SpriteSheet sillySheet;

static void renderProject() {
	if(initframe==true) {
		initframe=false;
		sillySheet = C2D_SpriteSheetLoad("romfs:/sprites.t3x");
		C2D_SpriteFromSheet(&spriteroni, sillySheet, 0);
	}
	C2D_DrawSprite(&spriteroni);
	C2D_SpriteSetPos(&spriteroni, 180.0f, 120.0f);
}

//static void runBlock(int blockID) {
//	switch(blockID) {
//		case 1:
//			uhh...
//	}
//}