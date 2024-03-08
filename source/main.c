#include <citro2d.h>
#include <3ds.h>
#include "render_block.c"

void render(bool scr){
	renderBlock(C2D_Color32(153, 102, 255, 0xFF),scr?100:0,scr?100:0,scr?"this is the top block":"and this block is the bottom block");
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

		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

		C2D_TargetClear(bot, clear_color);
		C2D_SceneBegin(bot);

		render(false);
		
		C2D_Flush();
		
		C2D_TargetClear(top, clear_color);
		C2D_SceneBegin(top);
		
		render(true);

		C2D_Flush();
		C3D_FrameEnd(0);
	}
	C2D_Fini();
	C3D_Fini();

	gfxExit();
	return 0;
}