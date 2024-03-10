float max(a,b){return a>b?a:b;}
float min(a,b){return a<b?a:b;}

#include <citro2d.h>
#include <3ds.h>
#include "screen_manage.c"

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
		u32 kHeld = hidKeysHeld();
		screenSwapCheck(kDown);
		if (kDown & KEY_SELECT)
			break;
		
		touchPosition touch;
		hidTouchRead(&touch);

		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

		C2D_TargetClear(bot, clear_color);
		C2D_SceneBegin(bot);

		renderScreen(kDown,kHeld,false,touch.px,touch.py);
		
		C2D_Flush();
		
		C2D_TargetClear(top, clear_color);
		C2D_SceneBegin(top);
		
		renderScreen(kDown,kHeld,true,touch.px,touch.py);

		C2D_Flush();
		C3D_FrameEnd(0);
	}
	C2D_Fini();
	C3D_Fini();

	gfxExit();
	return 0;
}