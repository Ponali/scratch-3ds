#include <citro2d.h>
#include <math.h>

static bool initframe=true;

static C2D_Sprite sprite;
static C2D_SpriteSheet sillySheet;

static float spriteX = 0.0f;
static float spriteY = 0.0f;
static float spriteRot = 90.0f;

static void projectFrame(bool scr, u32 kDown) {
	if(spriteX>240.0f) {
		spriteX=240.0f;
	} if(spriteX<-240.0f) {
		spriteX=-240.0f;
	} if(spriteY>180.0f) {
		spriteY=180.0f;
	} if(spriteY<-180.0f) {
		spriteY=-180.0f;
	} if(spriteRot>=360.0f) {
		spriteRot=spriteRot-360.0f; //i would use the % operator here but it doesnt work on floats. yes, scratch rotation may not be a round number.
	} if(spriteRot<0.0f) {
		spriteRot=spriteRot+360.0f;
	}
	
	if(initframe==true) {
		initframe = false;
		sillySheet = C2D_SpriteSheetLoad("romfs:/sprites.t3x");
		C2D_SpriteFromSheet(&sprite, sillySheet, 0);
		C2D_SpriteSetCenter(&sprite, 0.5f, 0.5f);
	}
	C2D_DrawSprite(&sprite);
	if(scr) {
		C2D_SpriteSetPos(&sprite, spriteX/1.5f+200.0f, spriteY/1.5f+120.0f);
	} else {
		C2D_SpriteSetPos(&sprite, spriteX/1.5f+160.0f, spriteY/1.5f+120.0f);
	}
	C2D_SpriteSetRotationDegrees(&sprite, spriteRot-90.0f);
	
}

static void runBlock(int blockID) {
	switch(blockID) {
		case 1:
			spriteX=spriteX+sin(spriteRot)*10;
			spriteY=spriteY+cos(spriteRot)*10;
		case 2:
			spriteRot=spriteRot+15;
		case 3:
			spriteRot=spriteRot-15;
	}
}