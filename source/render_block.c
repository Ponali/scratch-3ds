#include <citro2d.h>
#include "block_data.c"

typedef struct Block{
	int id;
	float x;
	float y;
	struct Block *after;
	bool hasAfter;
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

static float renderOffsetX=0;
static float renderOffsetY=0;

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

static void setBlockRenderingOffset(float x, float y){
	renderOffsetX=x;
	renderOffsetY=y;
}

static void startRenderBlockText(char text[], float* outWidth, float* outHeight){
	C2D_TextBufClear(renderBlockBuf);
	C2D_TextFontParse(&renderBlockTextValue, renderBlockFont, renderBlockBuf, text);
	C2D_TextOptimize(&renderBlockTextValue);
	C2D_TextGetDimensions(&renderBlockTextValue,0.5f,0.5f,outWidth,outHeight);
}

static void renderBlockText(float x, float y){
	C2D_DrawText(&renderBlockTextValue, C2D_WithColor, x, y, 0.0f, 0.5f, 0.5f, C2D_Color32(0xFF,0xFF,0xFF,0xFF));
}

static void renderBlockShadow(u32 c, float x, float y, int width, bool hat, bool end, bool rep){
	x+=renderOffsetX;
	y+=renderOffsetY;
	u32 ltn = C2D_Color32(0xFF, 0xFF, 0xFF, 128);
	
	if(!rep){
		C2D_DrawRectangle(0+x, 0+y+hat*10, 0, 20, 40-hat*10,c,c,c,c);        		// left-most part
		if(!hat){C2D_DrawTriangle(20+x,0+y,c,35+x,10+y,c,20+x,10+y,c,0);};          // left triangle for top
		if(!hat){C2D_DrawTriangle(60+x,0+y,c,45+x,10+y,c,60+x,10+y,c,0);};          // right triangle for top
		C2D_DrawRectangle(20+x, 10+y, 0, 40, 30,c,c,c,c);              		        // fill inside
		if(!end){
			C2D_DrawTriangle(20+x,40+y,c,35+x,50+y,c,35+x,40+y,c,0);       		    // left triangle for bottom
			C2D_DrawTriangle(60+x,40+y,c,45+x,50+y,c,45+x,40+y,c,0);       		    // right triangle for bottom
			C2D_DrawRectangle(35+x, 40+y, 0, 10, 10,c,c,c,c);              		    // fill bottom lump
		}
		C2D_DrawRectangle(60+x, 0+y+hat*10, 0, fmaxf(width-50,20),40-hat*10,c,c,c,c); // right-most part
		
		if(hat){ // top hat circle
			C2D_DrawEllipse(0+x,y-5,0,80,20,c,c,c,c);
			C2D_DrawRectangle(0+x,6+y,0,fmaxf(width,20+50)+10,4,c,c,c,c);
		}

		C2D_DrawTriangle(2+x, 2+y, ltn, 15+x, 2+y, ltn, 2+x, 15+y, ltn, 0);	        // drag indicator
	} else {
		width-=10;
		C2D_DrawCircle(x+10,y+20,0,15,c,c,c,c);
		C2D_DrawRectangle(x+10,y+5,0,width,30,c,c,c,c);
		C2D_DrawCircle(x+10+width,y+20,0,15,c,c,c,c);
	}
}

static void renderBlockFromProperties(u32 c, float x, float y, char text[], bool hat, bool end, bool reporter){
	float textWidth=0;
	float textHeight=0;
	startRenderBlockText(text,&textWidth,&textHeight);
	renderBlockShadow(c,x,y,textWidth,hat,end,reporter);
	renderBlockText(x+6+renderOffsetX,y+13+renderOffsetY);
}

static void renderBlock(struct Block a){
	u32 colorArray[10] = {motion_tab_color,looks_tab_color,sound_tab_color,events_tab_color,control_tab_color,sensing_tab_color,operators_tab_color,variables_tab_color,my_blocks_tab_color,extension_tab_color};
	int id=a.id;
	int bselColorIndex;
	for (int ii=0;ii<9;ii++) {
		if (id>=getBlockColor(ii,0) && id<=getBlockColor(ii,1)){
			bselColorIndex=ii;
			ii=9;
		}
	};
	renderBlockFromProperties(colorArray[bselColorIndex],a.x,a.y,getBlockText(id),getBlockHat(id),getBlockEnd(id),getReporter(id));
}

static bool blockCollision(struct Block a, float x, float y){
	return (x<a.x+30 && x>a.x && y<a.y+30 && y>a.y);
}