#include "editor.c"

static bool screenSwap=true;
static float cursorX=50;
static float cursorY=50;

static void updateCursor(s16 cStickX, s16 cStickY){
	cursorX+=cStickX/24;
	cursorY-=cStickY/24;
	if(cursorX<0){cursorX=0;}
	if(cursorY<0){cursorY=0;}
	if(cursorX>400){cursorX=400;}
	if(cursorY>240){cursorY=240;}
}

static void renderCursor(float cursorX, float cursorY, bool pressedA){
	u32 c=C2D_Color32(10,10,10,0xFF);
	if(pressedA){c=C2D_Color32(100,100,100,0xFF);}
	C2D_DrawTriangle(cursorX+0,cursorY+0,c,cursorX+15,cursorY+0,c,cursorX+0,cursorY+15,c,0);
}

static void renderScreen(u32 kHeld, bool scr, float touchX, float touchY, s16 cStickX, s16 cStickY, bool bsel, u32 kDown){
	bool pressedA=false;if(kHeld&KEY_A){pressedA=true;}
	float useX=touchX;float useY=touchY;
	if(scr){
		updateCursor(cStickX,cStickY);
		if(pressedA){
			useX=cursorX;
			useY=cursorY;
		} else {
			useX=0.0f;useY=0.0f;
		}
	}
	if(scr^screenSwap){
		editorBackend(scr,useX,useY);
	} else {
		if (bsel){
			blockSelector(scr,kDown,useX,useY);
		} else {
			// temporary triangle
			C2D_DrawTriangle(0,0,C2D_Color32(0xFF,10,10,0xFF),150,0,C2D_Color32(10,0xFF,10,0xFF),0,150,C2D_Color32(10,10,0xFF,0xFF),0);
		}
	}
	if(scr){
		renderCursor(cursorX,cursorY,pressedA);
	}
}

static void screenSwapCheck(u32 kDown){
	if (kDown & KEY_ZL)
		screenSwap=!screenSwap;
}