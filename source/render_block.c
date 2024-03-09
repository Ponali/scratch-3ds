#include <citro2d.h>

static C2D_Font renderBlockFont;
static C2D_TextBuf renderBlockBuf;
static C2D_Text renderBlockTextValue;

static void initBlockRendering(){
	renderBlockFont=C2D_FontLoad("romfs:/font.bcfnt");
	renderBlockBuf=C2D_TextBufNew(4096);
}

static void startRenderBlockText(char text[], u32 outWidth, u32 outHeight){
	C2D_TextBufClear(renderBlockBuf);
	C2D_TextFontParse(&renderBlockTextValue, renderBlockFont, renderBlockBuf, text);
	C2D_TextOptimize(&renderBlockTextValue);
	C2D_TextGetDimensions(&renderBlockTextValue,0.5f,0.5f,outWidth,outHeight);
}

static void renderBlockText(float x, float y){
	C2D_DrawText(&renderBlockTextValue, C2D_WithColor, x, y, 0.0f, 0.5f, 0.5f, C2D_Color32(0xFF,0xFF,0xFF,0xFF));
}

static void renderBlockShadow(u32 c, float x, float y, int width){
	u32 ltn = C2D_Color32(0xFF, 0xFF, 0xFF, 128);
	C2D_DrawRectangle(0+x, 0+y, 0, 20, 40,c,c,c,c);                		// left-most part
	C2D_DrawTriangle(20+x,0+y,c,35+x,10+y,c,20+x,10+y,c,0);        		// left triangle for top
	C2D_DrawTriangle(60+x,0+y,c,45+x,10+y,c,60+x,10+y,c,0);        		// right triangle for top
	C2D_DrawRectangle(20+x, 10+y, 0, 40, 30,c,c,c,c);              		// fill inside
	C2D_DrawTriangle(20+x,40+y,c,35+x,50+y,c,35+x,40+y,c,0);       		// left triangle for bottom
	C2D_DrawTriangle(60+x,40+y,c,45+x,50+y,c,45+x,40+y,c,0);       		// right triangle for bottom
	C2D_DrawRectangle(35+x, 40+y, 0, 10, 10,c,c,c,c);              		// fill bottom lump
	C2D_DrawRectangle(60+x, 0+y, 0, max(width-50,20), 40,c,c,c,c); 		// right-most part
	C2D_DrawTriangle(2+x, 2+y, ltn, 15+x, 2+y, ltn, 2+x, 15+y, ltn, 0);	// drag indicator
}

static void renderBlock(u32 c, float x, float y, char text[]){
	float textWidth=0;
	float textHeight=0;
	startRenderBlockText(text,&textWidth,&textHeight);
	renderBlockShadow(c,x,y,textWidth);
	renderBlockText(x+6,y+13);
}