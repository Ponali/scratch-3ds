#include <citro2d.h>

typedef struct Block{
	int id;
	float x;
	float y;
};


static C2D_Font renderBlockFont;
static C2D_TextBuf renderBlockBuf;
static C2D_Text renderBlockTextValue;

// block colors
static u32 motion_tab_color;
static u32 looks_tab_color;
static u32 sound_tab_color;
static u32 events_tab_color;
static u32 control_tab_color;
static u32 sensing_tab_color;
static u32 operators_tab_color;
static u32 variables_tab_color;
static u32 my_blocks_tab_color;
static u32 extension_tab_color;

static void initBlockRendering(){
	renderBlockFont=C2D_FontLoad("romfs:/font.bcfnt");
	renderBlockBuf=C2D_TextBufNew(4096);
	motion_tab_color = C2D_Color32(76, 151, 255, 0xFF);
	looks_tab_color = C2D_Color32(153, 102, 255, 0xFF);
	sound_tab_color = C2D_Color32(207, 99, 207, 0xFF);
	events_tab_color = C2D_Color32(255, 191, 0, 0xFF);
	control_tab_color = C2D_Color32(255, 171, 25, 0xFF);
	sensing_tab_color = C2D_Color32(92, 177, 214, 0xFF);
	operators_tab_color = C2D_Color32(89, 192, 89, 0xFF);
	variables_tab_color = C2D_Color32(255, 140, 26, 0xFF);
	my_blocks_tab_color = C2D_Color32(255, 102, 128, 0xFF);
	extension_tab_color = C2D_Color32(15, 189, 140, 0xFF);
	//memcpy(_blockColor,blockColorImport,sizeof(_blockColor));
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

static void renderBlockFromProperties(u32 c, float x, float y, char text[]){
	float textWidth=0;
	float textHeight=0;
	startRenderBlockText(text,&textWidth,&textHeight);
	renderBlockShadow(c,x,y,textWidth);
	renderBlockText(x+6,y+13);
}

static void renderBlock(struct Block a){
	u32 colorArray[10] = {motion_tab_color,looks_tab_color,sound_tab_color,events_tab_color,control_tab_color,sensing_tab_color,operators_tab_color,variables_tab_color,my_blocks_tab_color,extension_tab_color};
	int id=a.id;
	int bselColorIndex;
	for (int ii=0;ii<9;ii++) {
		if (id>=/*blockColor[ii][0]*/getBlockColor(ii,0) && id<=/*blockColor[ii][1]*/getBlockColor(ii,1)){
			bselColorIndex=ii;
			ii=9;
		}
	}
	renderBlockFromProperties(colorArray[bselColorIndex],a.x,a.y,/*blockText[id]*/getBlockText(id));
}

static bool blockCollision(struct Block a, float x, float y){
	return (x<a.x+30 && x>a.x && y<a.y+30 && y>a.y);
}