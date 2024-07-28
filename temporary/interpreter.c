#include <citro2d.h>

static void initProject() {
	static C2D_SpriteSheet sillySheet = C2D_SpriteSheetLoad("filename");
	static C2D_Sprite spriteroni;
	C2D_SpriteFromSheet(&spriteroni, sillySheet, 0);
}

static void renderProject() {
	C2D_DrawSprite(&spriteroni);
}

//static void runBlock(int blockID) {
//	switch(blockID) {
//		case 1:
//			uhh...
//	}
//}