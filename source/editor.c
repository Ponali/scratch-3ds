#include "block_data.c"
#include "render_block.c"

static float stylusDiffX = 0;
static float stylusDiffY = 0;
static bool currentlyMoving = false;
static int movingBlockIdx = 0;
static bool movingBlock=false;
static struct Block blockMatrix[2]={{0,0,0},{1,50,100}};
static int blockMatrixSize=2;
static struct Block* blockMatrixDynamic;
// static int blockMatrix[2][4] = {{0,0,0,0},{50,50,0,0}}; 3rd entry would be block index
static float blockSelectorScroll = 10.0f;
static int blockSelectorScrollSpeed= 0;
static bool blockSelectorTouchHold=false;
static bool editorInitiated=false;
static float editorX=0;
static float editorY=0;

static void editorRender(bool scr){
	setBlockRenderingOffset(editorX,editorY);
	if(currentlyMoving){
		for(int i=0;i<blockMatrixSize;i++){
			if(i!=movingBlockIdx){
				if(blockCollision(blockMatrixDynamic[i],blockMatrixDynamic[movingBlockIdx].x+10,blockMatrixDynamic[movingBlockIdx].y-30)&&(!getBlockHat(blockMatrixDynamic[movingBlockIdx].id))&&(!getBlockEnd(blockMatrixDynamic[i].id))&&(!getReporter(blockMatrixDynamic[i].id))&&(!getReporter(blockMatrixDynamic[movingBlockIdx].id))){
					renderBlockShadow(C2D_Color32(128,128,128,128),blockMatrixDynamic[i].x,blockMatrixDynamic[i].y+40,0,false,getBlockEnd(blockMatrixDynamic[movingBlockIdx].id),false);
				}
			}
		};
		for(int i=0;i<blockMatrixSize;i++){
			if(i!=movingBlockIdx){
				if(blockCollision(blockMatrixDynamic[i],blockMatrixDynamic[movingBlockIdx].x+10,blockMatrixDynamic[movingBlockIdx].y+55)&&(!getBlockHat(blockMatrixDynamic[i].id))&&(!getBlockEnd(blockMatrixDynamic[movingBlockIdx].id))&&(!getReporter(blockMatrixDynamic[i].id))&&(!getReporter(blockMatrixDynamic[movingBlockIdx].id))){
					renderBlockShadow(C2D_Color32(128,128,128,128),blockMatrixDynamic[i].x,blockMatrixDynamic[i].y-40,0,getBlockHat(blockMatrixDynamic[movingBlockIdx].id),false,false);
				}
			}
		};
	}
	for(int i=0;i<blockMatrixSize;i++){
		renderBlock(blockMatrixDynamic[i]);
	}
}

static void editorBackend(bool scr, float touchX, float touchY, s16 cStickX, s16 cStickY){
	if(!editorInitiated){
		blockMatrixDynamic = (int*)calloc(blockMatrixSize,sizeof(struct Block));
		memcpy(blockMatrixDynamic,blockMatrix,sizeof(blockMatrix));
		editorInitiated=true;
	}
	editorX-=((float)cStickX)/24;
	editorY+=((float)cStickY)/24;
	if(!(touchX==0.0f&&touchY==0.0f)){
		touchX-=editorX;
		touchY-=editorY;
	}
	bool touching=((touchX+touchY)!=0);
	if(currentlyMoving){
		if(movingBlock){
			if(touching){
				blockMatrixDynamic[movingBlockIdx].x=touchX+stylusDiffX;
				blockMatrixDynamic[movingBlockIdx].y=touchY+stylusDiffY;
				int loopCount=0;
				//while((*moveBlock).hasAfter){
				// jankfix because hasAfter wasnt being set, original bit of code above
				struct Block *moveBlock=&blockMatrixDynamic[movingBlockIdx];
				while(loopCount < blockMatrixSize){
					loopCount++;
					if((*moveBlock).hasAfter){
						moveBlock=(*moveBlock).after;
						moveBlock->x=touchX+stylusDiffX;
						moveBlock->y=touchY+stylusDiffY+40*loopCount;
					}
					// this makes block after the one being dragged get also dragged, but this does nothing?
				}
			} else {
				currentlyMoving=false;
				for(int i=0;i<blockMatrixSize;i++){
					if(i!=movingBlockIdx){
						if(blockCollision(blockMatrixDynamic[i],blockMatrixDynamic[movingBlockIdx].x+10,blockMatrixDynamic[movingBlockIdx].y-30)&&(!getBlockHat(blockMatrixDynamic[movingBlockIdx].id))&&(!getBlockEnd(blockMatrixDynamic[i].id))&&(!getReporter(blockMatrixDynamic[i].id))&&(!getReporter(blockMatrixDynamic[movingBlockIdx].id))){
							blockMatrixDynamic[movingBlockIdx].x=blockMatrixDynamic[i].x;
							blockMatrixDynamic[movingBlockIdx].y=blockMatrixDynamic[i].y+40;
							struct Block *moveBlock=&blockMatrixDynamic[movingBlockIdx];
							int loopCount=0;
							while(loopCount < blockMatrixSize){
								loopCount++;
								if((*moveBlock).hasAfter){
									moveBlock=(*moveBlock).after;
									moveBlock->x=blockMatrixDynamic[i].x;
									moveBlock->y=blockMatrixDynamic[i].y+40+40*loopCount;
								}
								// this makes block after the one being dragged get also dragged, but this does nothing?
							}
							blockMatrixDynamic[i].after=&blockMatrixDynamic[movingBlockIdx];
							blockMatrixDynamic[i].hasAfter=true;
						}
					}
				}
				for(int i=0;i<blockMatrixSize;i++){
					if(i!=movingBlockIdx){
						if(blockCollision(blockMatrixDynamic[i],blockMatrixDynamic[movingBlockIdx].x+10,blockMatrixDynamic[movingBlockIdx].y+55)&&(!getBlockHat(blockMatrixDynamic[i].id))&&(!getBlockEnd(blockMatrixDynamic[movingBlockIdx].id))&&(!getReporter(blockMatrixDynamic[i].id))&&(!getReporter(blockMatrixDynamic[movingBlockIdx].id))){
							blockMatrixDynamic[movingBlockIdx].x=blockMatrixDynamic[i].x;
							blockMatrixDynamic[movingBlockIdx].y=blockMatrixDynamic[i].y-40;
							blockMatrixDynamic[movingBlockIdx].after=&blockMatrixDynamic[i];
							blockMatrixDynamic[movingBlockIdx].hasAfter=true;
						}
					}
				};
			}
		} else if(touching) {
			editorX+=touchX-stylusDiffX;
			editorY+=touchY-stylusDiffY;
		} else {
			currentlyMoving=false;
		}
	} else if(touching) {
		movingBlock=false;
		stylusDiffX=touchX;
		stylusDiffY=touchY;
		currentlyMoving=true;
		for(int i=0;i<blockMatrixSize;i++){
			if(blockCollision(blockMatrixDynamic[i],touchX,touchY)){
			//if(touchX<blockMatrix[i].x+30 && touchX>blockMatrix[i].x && touchY<blockMatrix[i].y+30 && touchY>blockMatrix[i].y/* && blockMatrix[i][3]==0*/){
				movingBlock=true;
				movingBlockIdx=i;
				stylusDiffX=blockMatrixDynamic[i].x-touchX;
				stylusDiffY=blockMatrixDynamic[i].y-touchY;
				//blockMatrixDynamic[i].hasAfter=false;
				for(int j=0;j<blockMatrixSize;j++){
					if(blockMatrixDynamic[j].after==(&blockMatrixDynamic[i])){
						blockMatrixDynamic[j].hasAfter=false;
					}
				}
				i=blockMatrixSize; // the value here does not matter, what's important is that we get out of the loop
			}
		}
	}
	editorRender(scr);
}

static void insertBlockFromSelector(int id){
	struct Block* temp=blockMatrixDynamic;
	blockMatrixDynamic = realloc(blockMatrixDynamic,blockMatrixSize*sizeof(struct Block));
	if(!blockMatrixDynamic){
		blockMatrixDynamic=temp;
	} else {
		struct Block newBlock;
		newBlock.id=id;newBlock.x=50;newBlock.y=50;newBlock.hasAfter=false;
		blockMatrixDynamic[blockMatrixSize]=newBlock;
		blockMatrixSize++;
	}
}

static void blockSelector(bool scr, u32 kDown, float touchX, float touchY){
	setBlockRenderingOffset(0.0f,0.0f);
	if(blockSelectorTouchHold&&(touchX+touchY==0)){blockSelectorTouchHold=false;}
	u32 colorArray[10] = {motion_tab_color,looks_tab_color,sound_tab_color,events_tab_color,control_tab_color,sensing_tab_color,operators_tab_color,variables_tab_color,my_blocks_tab_color,extension_tab_color};
	bool touchedBlock=false;
	int scrollI=blockSelectorScroll/50;
	for(int i=0-scrollI;i<6-scrollI;i++){
		if(i<=104){
			struct Block blockToRender;
			blockToRender.id=i;
			blockToRender.x=10;
			blockToRender.y=blockSelectorScroll+i*50;
			renderBlock(blockToRender);
			if((touchX+touchY!=0)&&(!blockSelectorTouchHold)&&blockCollision(blockToRender,touchX,touchY)&&(blockSelectorScrollSpeed==0)){
				touchedBlock=true;
				insertBlockFromSelector(i);
			}
		}
	}
	if((touchX+touchY!=0)&&(!touchedBlock)){
		blockSelectorScroll-=((touchY-120)/30)*(blockSelectorScrollSpeed/60+1);
		if(blockSelectorScroll>10){blockSelectorScroll=10;};
		if(blockSelectorScroll<(-50*(104-3.5))){blockSelectorScroll=(-50*(104-3.5));};
		blockSelectorScrollSpeed+=1;
		if(blockSelectorScrollSpeed>(60*5)){blockSelectorScrollSpeed=(60*5);}
	} else {
		blockSelectorScrollSpeed=0;
	}
	if((!blockSelectorTouchHold)&&(touchX+touchY!=0)){blockSelectorTouchHold=true;}
}