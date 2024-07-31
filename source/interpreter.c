#include <citro2d.h>
#include <math.h>
#include <stdlib.h>
// #include "globals.c"
#include "editor.c"

static bool initframe=true;
static int framecount=0;

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

static void runBlock(struct Block* block) {
	switch(block->id) {
		case MOVESTEPS:
			spriteX=spriteX+sin(spriteRot/180*M_PI)*10;
			spriteY=spriteY+cos(spriteRot/180*M_PI)*10;
			break;
		case TURNCLOCKWISE:
			spriteRot=spriteRot+15;
			break;
		case TURNCOUNTERCLOCKWISE:
			spriteRot=spriteRot-15;
			break;
		case GOTORANDOMPOS:
			spriteX=(rand()%320)-160;
			spriteY=(rand()%240)-120;
			break;
		case GOTOORIGIN:
			spriteX=0;
			spriteY=0;
			break;
	}

	if (block->hasAfter) {
		runBlock(block->after);
	}
}

static void startProject(){
	// must be ran when the green flag is clicked
	
	// get green flags and add it to runtime blocks
	for(int i=0;i<blockMatrixSize;i++){
		if(blockMatrixDynamic[i].id==47){ // corresponds to the "when flag clicked" block
			// insertRuntimeBlock(blockMatrixDynamic[i]);
			runBlock(blockMatrixDynamic[i].after);
		}
	}

	// initialise randomness
	srand(0);
	for(int i=0;i<(rand()%6)+2;i++)
		srand(rand());
	for(int i=0;i<(rand()%32)+16;i++)
		rand();
}

// static void projectTick(){
// 	// must be ran 30 times per second (every 2 frames)
// 	// TODO: redo this function a little bit
// 	for(int i=0;i<runtimeBlocksSize;i++){
// 		runBlock(runtimeBlocks[i].id);
// 		runtimeBlocks[i]=(*runtimeBlocks[i].after);
// 	}
	
// }

static void clamp(float* val, float max, float min) {
	// a segfault is waiting to happen here :trol:
	if (*val>max)
		*val = max;
	else if (*val<min)
		*val = min;
}

static void projectFrame(bool scr, u32 kDown) {
	// framecount++;
	// if(framecount==2) {
	// 	framecount=0;
	// 	projectTick();
	// }

	// if(spriteX>240.0f) {
	// 	spriteX=240.0f;
	// } if(spriteX<-240.0f) {
	// 	spriteX=-240.0f;
	// } if(spriteY>180.0f) {
	// 	spriteY=180.0f;
	// } if(spriteY<-180.0f) {
	// 	spriteY=-180.0f;
	// }

	clamp(&spriteX, 240.0f, -240.0f);// a lil simplification
	clamp(&spriteY, 180.0f, -180.0f);
	if(spriteRot>=360.0f) {
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
	if(kDown&KEY_START) {
		startProject();
	}
}