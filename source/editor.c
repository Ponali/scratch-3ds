#include "block_data.c"
#include "render_block.c"

static float stylusDiffX = 0;
static float stylusDiffY = 0;
static bool movingBlock = false;
static int movingBlockIdx = 0;
static struct Block blockMatrix[2]={{0,0,0},{1,50,50}};
// static int blockMatrix[2][4] = {{0,0,0,0},{50,50,0,0}}; 3rd entry would be block index
static float blockSelectorScroll = 10.0f;
static int blockSelectorScrollSpeed= 0;

static void editorRender(bool scr){
	for(int i=0;i<2;i++){
		/*struct Block currentBlock;
		currentBlock.id=i;
		currentBlock.x=i*50;
		currentBlock.y=i*50;*/
		//renderBlock(colorArray[i],blockMatrix[i][0],blockMatrix[i][1],"sample block text");
		renderBlock(blockMatrix[i]);
	}
	
}

static void editorBackend(bool scr, float touchX, float touchY){
	bool touching=((touchX+touchY)!=0);
	if(movingBlock){
		if(touching){
			blockMatrix[movingBlockIdx].x=touchX+stylusDiffX;
			blockMatrix[movingBlockIdx].y=touchY+stylusDiffY;
		} else {
			movingBlock=false;
		}
	} else if(touching) {
		for(int i=0;i<2;i++){
			if(touchX<blockMatrix[i].x+30 && touchX>blockMatrix[i].x && touchY<blockMatrix[i].y+30 && touchY>blockMatrix[i].y/* && blockMatrix[i][3]==0*/){
				movingBlockIdx=i;
				movingBlock=true;
				stylusDiffX=blockMatrix[i].x-touchX;
				stylusDiffY=blockMatrix[i].y-touchY;
				i=100; // the value here does not matter, what's important is that we get out of the loop
			}
		}
	}
	editorRender(scr);
}

static void blockSelector(bool scr, u32 kDown, float touchX, float touchY){
	u32 colorArray[10] = {motion_tab_color,looks_tab_color,sound_tab_color,events_tab_color,control_tab_color,sensing_tab_color,operators_tab_color,variables_tab_color,my_blocks_tab_color,extension_tab_color};
	/*if (kDown & KEY_L) {
		if (bselSelectedBlock==0) {
			bselSelectedBlock=104;
		} else {
			bselSelectedBlock--;
		}
	}
	if (kDown & KEY_R) {
		if (bselSelectedBlock==104) {
			bselSelectedBlock=0;
		} else {
			bselSelectedBlock++;
		}
	}*/
	int scrollI=blockSelectorScroll/50;
	for(int i=0-scrollI;i<6-scrollI;i++){
		if(i<=104){
			/*int bselColorIndex;
			for (int ii=0;ii<9;ii++) {
				if (i>=blockColor[ii][0] && i<=blockColor[ii][1]){
					bselColorIndex=ii;
				}
			}*/
			struct Block blockToRender;
			blockToRender.id=i;
			blockToRender.x=10;
			blockToRender.y=blockSelectorScroll+i*50;
			renderBlock(blockToRender);
			//renderBlockFromProperties(colorArray[bselColorIndex],10,blockSelectorScroll+i*50,blockText[i]);
		}
	}
	if(touchX+touchY!=0){
		blockSelectorScroll-=((touchY-120)/30)*(blockSelectorScrollSpeed/60+1);
		if(blockSelectorScroll>10){blockSelectorScroll=10;};
		if(blockSelectorScroll<(-50*(104-3.5))){blockSelectorScroll=(-50*(104-3.5));};
		blockSelectorScrollSpeed+=1;
		if(blockSelectorScrollSpeed>(60*4)){blockSelectorScrollSpeed=(60*4);}
	} else {
		blockSelectorScrollSpeed=0;
	}
}