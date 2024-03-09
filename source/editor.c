#include "render_block.c"

static float stylusblockposdiffX = 0;
static float stylusblockposdiffY = 0;
static bool blockbeingmoved = false;
static int blockmatrix[2][4] = {{0,0,0,0},{50,50,0,0}}; //3rd entry would be block index

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
	int i;
	for (i=0;i<2;i++)
	{
		renderBlock(scr?colorarray[i]:colorarray[i+2],blockmatrix[i][0],blockmatrix[i][1],scr?"top screen":"bottom screen");
	}
	
}

static void editorBackend(bool scr, float touchX, float touchY){
	int i;
	for (i=0;i<2;i++)
	{
		if (touchX<blockmatrix[i][0]+30 && touchX>blockmatrix[i][0] && touchY<blockmatrix[i][1]+30 && touchY>blockmatrix[i][1] && blockmatrix[i][3]==0)
		{
			if (blockbeingmoved==false)//this whole blockbeingmoved stuff is unfinished. the blocks used to stick together once the stylus gets close enough, so i put this in so you cant grab the other blocks while one is being grabbed, however this doesnt work and idk why.
			{
				blockmatrix[i][3]=1;
				blockbeingmoved = true;
				stylusblockposdiffX = touchX-blockmatrix[i][0];
				stylusblockposdiffY = touchY-blockmatrix[i][1];
			}
			
		}
		if (blockmatrix[i][3]==1 && (touchX!=0 || touchY!=0))
		{
			blockmatrix[i][0] = touchX-stylusblockposdiffX;
			blockmatrix[i][1] = touchY-stylusblockposdiffY;
		}
		else
		{
			blockmatrix[i][3]=0;
			blockbeingmoved=false;
			for (i=0;i<2;i++)
			{
				if (blockmatrix[i][3]==1)
				{
					blockbeingmoved = true;
				}
			}
		}
	}
	editorRender(scr);
}