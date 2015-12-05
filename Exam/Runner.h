#pragma once
#include "ProjectHeader.h"
#define NAME_MAP "_map.bmp"
#define NAME_TILE "_main.bmp"
#define NAME_TYPE "_type.bmp"
#define NAME_LEVEL "_map_level.bmp"
#define NAME_BKG "_bkg_level.bmp"
#define TILESIZE 16
#define ERROR_CODE -1


enum eObjType
{
	eObjSolid = 1,
	eObjNoSolid,
	eObjEnemy,
	eObjCoin,
	eObjBonus
};

const struct ObjectKey
{
	unsigned Solid       = 0xff7a00;
	unsigned NoSolid	 = 0x00a300;
	unsigned Enemy		 = 0xff1e00;
	unsigned Coin		 = 0xf5ef00;
	unsigned Bonus		 = 0xffc000;
};

//struct ClipCoords
//{
//	int startX;
//	int startY;
//	int endX;
//	int endY;
//};

// Объединение кода картинки и его индекса, чтобы каждый раз не искать его в массиве.
struct IndexTile
{
	int picIndex;
	unsigned code;
};

// Статический объект, который не должен менятся на протяжении всего уровня. Тайлы берет с LevelStaticInfo
struct LevelStaticObject
{
	int objectType;
	IndexTile tileInfo;
};

// Динамический объект содержит собственные спрайты, текущие координаты и предыдущие.
struct LevelDynamicObject
{
	new_GFSurface* spriteset;
	int spritesize;
	int index;
	double prevX;
	double prevY;
	double posX;
	double posY;
};

// Массив динамических объектов в сцене.
struct LevelDynamicInfo
{
	int dynObjSize;
	LevelDynamicObject* dynobj;
};

// Массив статических объектов, откуда мы берем информацию от объектов
struct LevelStaticInfo
{
	int objStatSize;
	new_GFSurface* tileset;
	LevelStaticObject* objStatMap;
};

struct LevelScreen
{
	LevelStaticObject** levelmap;
	int mapSizeX;
	int mapSizeY;
	new_GFSurface* screen;
	new_GFSurface* levelSurf;
	new_GFSurface* background;
	int pixelSizeX;
	int pixelSizeY;
};

struct LevelData
{	
	LevelStaticInfo stInfo;
	LevelDynamicInfo dyInfo;
	LevelScreen lvlInfo;
	int score;
	int lives;
	int winX;
	int winY;
};


int getRunnerObjectType(RGBBlock &block);
IndexTile getRunnerTileIndex(BMPPicture &mapset, RGBBlock &block);
LevelStaticObject cleanStaticObject();
LevelStaticObject getStaticObject(LevelData &data, unsigned code);
int initStatic(LevelData &data, char* mainname);
int initLevel(LevelData &data, char* levelname);
bool blitTile(LevelData &data, unsigned code, int tilesize, int posX,int posY);
LevelData* initLevelData(char* levelname, char* mainname, int winX, int winY);
int activeRunner(GameData &data);