float max(a,b){return a>b?a:b;} //test comment
float min(a,b){return a<b?a:b;}

#include <citro2d.h>
#include <3ds.h>
#include "render_block.c"

float blockposX = 0;
float blockposY = 0;
bool dragstarted = false;
float stylusblockposdiffX = 0;
float stylusblockposdiffY = 0;

void render(bool scr, float touchX, float touchY){
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

int main(int argc, char* argv[]) {
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();

	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	C3D_RenderTarget* bot = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

	initBlockRendering();
	
	u32 clear_color = C2D_Color32f(1.0f, 1.0f, 1.0f, 1.0f);

	while (aptMainLoop()) {
		//gspWaitForVBlank();
		hidScanInput();

		u32 kDown = hidKeysDown();
		if (kDown & KEY_SELECT)
			break;
		
		touchPosition touch;
		hidTouchRead(&touch);

		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

		C2D_TargetClear(bot, clear_color);
		C2D_SceneBegin(bot);
		if (touch.px<blockposX+30 && touch.px>blockposX && touch.py<blockposY+30 && touch.py>blockposY && dragstarted==false)
		{
			dragstarted = true;
			stylusblockposdiffX = touch.px-blockposX;
			stylusblockposdiffY = touch.py-blockposY;
		}
		if (dragstarted==true && (touch.px!=0 || touch.py!=0))
		{
			blockposX = touch.px-stylusblockposdiffX;
			blockposY = touch.py-stylusblockposdiffY;
		}
		else
		{
			dragstarted = false;
		}
		render(false,blockposX,blockposY);
		
		C2D_Flush();
		
		C2D_TargetClear(top, clear_color);
		C2D_SceneBegin(top);
		
		render(true,0.0f,0.0f);

		C2D_Flush();
		C3D_FrameEnd(0);
	}
	C2D_Fini();
	C3D_Fini();

	gfxExit();
	return 0;
}