//#include "editor.c"
#include "interpreter.c"

static bool screenSwap=true;
static float cursorX=50;
static float cursorY=50;

static void updateCursor(s16 circleX, s16 circleY){
	cursorX+=circleX/24;
	cursorY-=circleY/24;
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

static void renderScreen(u32 kHeld, bool scr, float touchX, float touchY, s16 circleX, s16 circleY, bool bsel, u32 kDown, s16 cStickX, s16 cStickY){
	bool pressedA=false;if(kHeld&KEY_A){pressedA=true;}
	float useX=touchX;float useY=touchY;
	if(scr){
		updateCursor(circleX,circleY);
		if(pressedA){
			useX=cursorX;
			useY=cursorY;
		} else {
			useX=0.0f;useY=0.0f;
		}
		buttonPrompt(scr,"\uE000: Click",1);
		buttonPrompt(scr,"\uE050: Move cursor",3);
	} else {
		buttonPrompt(scr,"\uE054: Swap screens",1);
	}
	if(scr^screenSwap){
		editorBackend(scr,useX,useY,cStickX,cStickY);
	} else {
		if (bsel){
			blockSelector(scr,kDown,useX,useY);
		} else {
			// temporary triangle
			projectFrame(scr, kDown, touchX, touchY);
			C2D_DrawTriangle(0,0,C2D_Color32(0xFF,10,10,0xFF),150,0,C2D_Color32(10,0xFF,10,0xFF),0,150,C2D_Color32(10,10,0xFF,0xFF),0);
			buttonPrompt(scr,"\uE002: Block selector",0);
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