#include "render_block.c"

static float blockposX = 0;
static float blockposY = 0;
static bool dragstarted = false;
static float stylusblockposdiffX = 0;
static float stylusblockposdiffY = 0;

static void editorRender(bool scr, float touchX, float touchY){
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
	renderBlock(scr?sensing_tab_color:operators_tab_color,scr?100:touchX,scr?100:touchY,scr?"top screen sensing color":"bottom screen operator color");
}

static void editorThink(bool scr, float touchX, float touchY){
	if (touchX<blockposX+30 && touchX>blockposX && touchY<blockposY+30 && touchY>blockposY && dragstarted==false)
	{
		dragstarted = true;
		stylusblockposdiffX = touchX-blockposX;
		stylusblockposdiffY = touchY-blockposY;
	}
	if (dragstarted==true && (touchX!=0 || touchY!=0))
	{
		blockposX = touchX-stylusblockposdiffX;
		blockposY = touchY-stylusblockposdiffY;
	}
	else
	{
		dragstarted = false;
	}
	editorRender(scr,blockposX,blockposY);
}