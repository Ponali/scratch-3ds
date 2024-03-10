#include "render_block.c"

static float stylusDiffX = 0;
static float stylusDiffY = 0;
static bool movingBlock = false;
static int movingBlockIdx = 0;
static int blockMatrix[2][4] = {{0,0,0,0},{50,50,0,0}}; //3rd entry would be block index

static void editorRender(bool scr){
	u32 motion_tab_color = C2D_Color32(76, 151, 255, 0xFF);
	u32	looks_tab_color = C2D_Color32(153, 102, 255, 0xFF);
	u32	sound_tab_color = C2D_Color32(207, 99, 207, 0xFF);
	u32	events_tab_color = C2D_Color32(255, 191, 0, 0xFF);
	u32	control_tab_color = C2D_Color32(255, 171, 25, 0xFF);
	u32	sensing_tab_color = C2D_Color32(92, 177, 214, 0xFF);
	u32	operators_tab_color = C2D_Color32(89, 192, 89, 0xFF);
	u32	variables_tab_color = C2D_Color32(255, 140, 26, 0xFF);
	u32	my_blocks_tab_color = C2D_Color32(255, 102, 128, 0xFF);
	u32	extension_tab_color = C2D_Color32(15, 189, 140, 0xFF);
	u32 colorarray[10] = {motion_tab_color,looks_tab_color,sound_tab_color,events_tab_color,control_tab_color,sensing_tab_color,operators_tab_color,variables_tab_color,my_blocks_tab_color,extension_tab_color};
	for(int i=0;i<2;i++){
		renderBlock(colorarray[i],blockMatrix[i][0],blockMatrix[i][1],"sample block text");
	}
	
}

static void editorBackend(bool scr, float touchX, float touchY){
	bool touching=((touchX+touchY)!=0);
	if(movingBlock){
		if(touching){
			blockMatrix[movingBlockIdx][0]=touchX+stylusDiffX;
			blockMatrix[movingBlockIdx][1]=touchY+stylusDiffY;
		} else {
			movingBlock=false;
		}
	} else if(touching) {
		for(int i=0;i<2;i++){
			if(touchX<blockMatrix[i][0]+30 && touchX>blockMatrix[i][0] && touchY<blockMatrix[i][1]+30 && touchY>blockMatrix[i][1] && blockMatrix[i][3]==0){
				movingBlockIdx=i;
				movingBlock=true;
				stylusDiffX=blockMatrix[i][0]-touchX;
				stylusDiffY=blockMatrix[i][1]-touchY;
				i=100; // the value here does not matter, what's important is that we get out of the loop
			}
		}
	}
	editorRender(scr);
}