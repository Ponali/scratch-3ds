#include <citro2d.h>
#include <math.h>
#include "globals.c"

static bool initframe=true;

static C2D_Sprite sprite;
static C2D_SpriteSheet sillySheet;

static float spriteX = 0.0f;
static float spriteY = 0.0f;
static float spriteRot = 90.0f;

static int runtimeBlocksSize=0;
static struct Block* runtimeBlocks;

static void insertRuntimeBlock(struct Block newBlock){
	struct Block* temp=runtimeBlocks;
	runtimeBlocks = realloc(runtimeBlocks,runtimeBlocksSize*sizeof(struct Block));
	/*if(!runtimeBlocks){
		runtimeBlocks=temp;
	} else {
		struct Block newBlock;
		newBlock.id=id;newBlock.x=50;newBlock.y=50;newBlock.hasAfter=false;*/
	runtimeBlocks[runtimeBlocksSize]=newBlock;
	runtimeBlocksSize++;
	//}
}


static void startProject(){
	// must be ran when the green flag is clicked

	// get green flags and add it to runtime blocks
	for(int i=0;i<blockMatrixSize;i++){
		if(blockMatrixDynamic[i].id==47){ // corresponds to the "when flag clicked" block
			insertRuntimeBlock(blockMatrixDynamic[i]);
		}
	}

	// initialise randomness
	srand(0);
	for(int i=0;i<(rand()%6)+2;i++)
		srand(rand());
	for(int i=0;i<(rand()%32)+16;i++)
		rand();
}

static void projectTick(){
	// must be ran 30 times per second (every 2 frames)
	for(int i=0;i<runtimeBlocksSize;i++){
		runBlock(runtimeBlocks[i].id);
		runtimeBlocks[i]=(*runtimeBlocks[i].after)
	}
}

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
			break;
		case 2:
			spriteRot=spriteRot+15;break;
		case 3:
			spriteRot=spriteRot-15;break;
		case 4:
			spriteX=(rand()%320)-160;
			spriteY=(rand()%240)-120;
			break;
		case 5:
			spriteX=0;
			spriteY=0;
			break;
	}
}