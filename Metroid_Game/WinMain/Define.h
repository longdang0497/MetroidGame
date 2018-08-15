#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class World;
class Samus;
class Metroid;
class Game;
class Bullet;
class Grid;
class GameObject;
class CSound;
class GameSound;
class Map;
class Gate;
class KraidBomerang;
class KraidBullet;
class RidleyBullet;
class Kraid;
class Ridley;

#define KEYBOARD_BUFFER_SIZE	1024
#define KEY_DOWN(code) ( IsKeyDown(code) )
#define KEY_DOWN(vk_code) ( (GetAsyncKeyState(vk_code)&0x8000)?1:0 )

#define TIME_FREEZING 5000
#define TIME_IN_GAME 7000

#define JUMP_VELOCITY 150.0f
#define JUMP_VELOCITY_BOOST 0.5f
#define JUMP_VELOCITY_BOOST_FIRST 28.0f
#define FALLDOWN_VELOCITY_DECREASE 295.0f
#define MAX_FALLING 600.0f
#define GRAVITY_VELOCITY 180.0f
#define ANIMATE_RATE 30
#define LIVE_TIME 3000
#define SAMUS_MAX_JUMP 182
#define SAMUS_MIN_JUMP 64

#define SAMUS_SPEED 200.0f
#define FRICTION 1.0f
#define TEXTURE_GAME_CHARACTERS L"sprites\\Player_32x16.png"

#define MAP_FULL_ROOM "map\\fieldFullRoom.txt"
#define WIDTH_ROOM1 2272
#define WIDTH_ROOM2 2048
#define WIDTH_ROOM_BOSS 640
#define HEIGHT_ROOM	480

enum ROOM_NUMBER {
	ROOM1,
	ROOM2,
	BOSS1,
	BOSS2
};
//================ SCREEN RESOLUTION ================
#define GAME_SCREEN_RESOLUTION_640_480_24   0
#define GAME_SCREEN_RESOLUTION_800_600_24   1
#define GAME_SCREEN_RESOLUTION_1024_768_24  2

#define GAME_SCREEN_RESOLUTION_640_480_32   10
#define GAME_SCREEN_RESOLUTION_800_600_32   11
#define GAME_SCREEN_RESOLUTION_1024_768_32  12

#define CAMERA_FOLLOW_POINT_LEFT_RATIO   2.0/4
#define CAMERA_FOLLOW_POINT_RIGHT_RATIO  2.0/4
#define CAMERA_FOLLOW_POINT_BOTTOM_RATIO 1.0/4
#define CAMERA_FOLLOW_POINT_TOP_RATIO    3.0/4
//================ END RESOLUTION ====================

//================ SAMUS ====================
enum SAMUS_STATE {
	STAND_LEFT,
	STAND_RIGHT,
	RUNNING_LEFT,
	RUNNING_RIGHT,
	STAND_SHOOT_UP_LEFT,
	STAND_SHOOT_UP_RIGHT,
	MORPH_LEFT,
	MORPH_RIGHT,
	RUN_SHOOTING_LEFT,
	RUN_SHOOTING_RIGHT,
	RUN_SHOOT_UP_LEFT,
	RUN_SHOOT_UP_RIGHT,
	JUMP_LEFT,
	JUMP_RIGHT,
	TRANSFORM_BALL_LEFT,
	TRANSFORM_BALL_RIGHT,
	JUMP_SHOOT_UP_LEFT,
	JUMP_SHOOT_UP_RIGHT,
};

//================END SAMUS ====================

//================= OBJECT TYPE ================
enum OBJECT_TYPE
{
	SAMUS,
	BRICK,
	BULLET,
	ITEM,
	GATE,
	EFFECT,
	ZOOMER_YELLOW,
	ZOOMER_PINK,
	SKREE,
	GATE_BLOCK,
	RIDLEY,
	KRAID,
	EXPLOSION_BOMB,
	MARU_MARI,
	ENERGY_ITEM,
	MISSILE_ITEM,
	BOMB_ITEM,
	BOMB_WEAPON,
	RIDLEY_BULLET,
	KRAID_BOMERANG,
	KRAID_BULLET
};
//================= END OBJECT TYPE ============

//================= GAME SCENE ================
#define STARTSCREEN_FILE L"scene\\start_background.png"
#define INTROSCREEN_FILE L"scene\\intro_background.png"
#define GAMEOVERSCREEN_FILE L"scene\\gameover_background.png"

#define GAMEMODE_INTRO 0
#define GAMEMODE_START 1
#define GAMEMODE_GAMERUN 2
#define GAMEMODE_GAMEOVER 3

#define TIME_FREEZING 5000
#define TIME_IN_GAME 7000
//================= END GAME SCENE ============

//================ SPRITE SAMUS ================
#define WIDTH_SAMUS_STAND 42
#define HEIGHT_SAMUS_STAND 66
#define COUNT_SAMUS_STAND 1
#define STAND_RIGHT_PATH L"sprites\\STAND_RIGHT.txt"
#define STAND_LEFT_PATH L"sprites\\STAND_LEFT.txt"

#define WIDTH_SAMUS_RUNRIGHT 42
#define HEIGHT_SAMUS_RUNRIGHT 76
#define COUNT_SAMUS_RUNRIGHT 3
#define RUNRIGHT_PATH L"sprites\\RIGHTING.txt"

#define WIDTH_SAMUS_RUNLEFT 42
#define HEIGHT_SAMUS_RUNLEFT 72
#define COUNT_SAMUS_RUNLEFT 3
#define RUNLEFT_PATH L"sprites\\LEFTING.txt"

#define WIDTH_SAMUS_MORPHLEFT 40
#define HEIGHT_SAMUS_MORPHLEFT 48
#define COUNT_SAMUS_MORPHLEFT 4
#define MORPHLEFT_PATH L"sprites\\MORPH_LEFT.txt"

#define WIDTH_SAMUS_MORPHRIGHT 40
#define HEIGHT_SAMUS_MORPHRIGHT 48
#define COUNT_SAMUS_MORPHRIGHT 4
#define MORPHRIGHT_PATH L"sprites\\MORPH_RIGHT.txt"

#define WIDTH_SAMUS_JUMP 48
#define HEIGHT_SAMUS_JUMP 52
#define COUNT_SAMUS_JUMP 1
#define JUMPLEFT_PATH L"sprites\\JUMP_LEFT.txt"
#define JUMPRIGHT_PATH L"sprites\\JUMP_RIGHT.txt"

#define WIDTH_SAMUS_BALLLEFT 26
#define HEIGHT_SAMUS_BALLLEFT 28
#define COUNT_SAMUS_BALLLEFT 4
#define BALLLEFT_PATH L"sprites\\TRANSFORM_BALL_LEFT.txt"

#define WIDTH_SAMUS_BALLRIGHT 26
#define HEIGHT_SAMUS_BALLRIGHT 28
#define COUNT_SAMUS_BALLRIGHT 4
#define BALLRIGHT_PATH L"sprites\\TRANSFORM_BALL_RIGHT.txt"

#define WIDTH_SAMUS_STANDSHOOTUP 30
#define HEIGHT_SAMUS_STANDSHOOTUP 74
#define COUNT_SAMUS_STANDSHOOTUP 1
#define STANDSHOOTUP_LEFT_PATH L"sprites\\STANDSHOOT_LEFT.txt"
#define STANDSHOOTUP_RIGHT_PATH L"sprites\\STANDSHOOT_RIGHT.txt"

#define WIDTH_SAMUS_RUNSHOOTright 51
#define HEIGHT_SAMUS_RUNSHOOTright 64
#define COUNT_SAMUS_RUNSHOOTright 3
#define RUNSHOOTright_PATH L"sprites\\RUNSHOOT_RIGHT.txt"

#define WIDTH_SAMUS_RUNSHOOTleft 51
#define HEIGHT_SAMUS_RUNSHOOTleft 64
#define COUNT_SAMUS_RUNSHOOTleft 3
#define RUNSHOOTleft_PATH L"sprites\\RUNSHOOT_LEFT.txt"

#define WIDTH_SAMUS_JUMPSHOOT 38
#define HEIGHT_SAMUS_JUMPSHOOT 66
#define COUNT_SAMUS_JUMPSHOOT 1
#define JUMPSHOOTright_PATH L"sprites\\JUMPSHOOT_LEFT.txt"
#define JUMPSHOOTleft_PATH L"sprites\\JUMPSHOOT_RIGHT.txt"

#define WIDTH_SAMUS_RUN_SHOOTUP_right 40
#define HEIGHT_SAMUS_RUN_SHOOTUP_right 78
#define COUNT_SAMUS_RUN_SHOOTUP_right 3
#define RUN_SHOOTUP_right_PATH L"sprites\\RUN_SHOOTUP_RIGHT.txt"

#define WIDTH_SAMUS_RUN_SHOOTUP_left 40
#define HEIGHT_SAMUS_RUN_SHOOTUP_left 78
#define COUNT_SAMUS_RUN_SHOOTUP_left 3
#define RUN_SHOOTUP_left_PATH L"sprites\\RUN_SHOOTUP_LEFT.txt"
//================= END SPRITE SAMUS ============

//================ SPRITE BRICK ================
#define WIDTH_SPRITE_BRICK 32
#define HEIGHT_SPRITE_BRICK 32
//================= END SPRITE BRICK ============

//================ ROOM LIMITATION (TILES COUNT)============================
#define X_LIMITATION 20
#define Y_LIMITATION 15
//================ END ROOM LIMITATION ==================================

//================ BRICK SIZE =============================================
#define BRICK_SIZE 32.0f
#define BRICK_TEXTURE L"map\\brick_32x32.png"
//================ END BRICK SIZE =========================================

//================ GAME SOUND =============================================
#define GAME_INTRO_SOUND L"sound\\background\\Intro.wav"
#define APPEARING_SOUND L"sound\\background\\Appearance.wav"
#define POWER_UP_SOUND L"Audio\\Power_Up.wav"
#define ROOM1_SOUND L"sound\\background\\Map.wav"
//================ END GAME SOUND =========================================

//================ GAME ITEM ===========================

#define ITEM_TIME_SURVIVE 5000
#define ITEM_SPRITE_PATH L"sprites\\item\\items_sprite_sheet.png"

//========= ITEM MARU MARI
#define MARU_MARI_WIDTH 24
#define MARU_MARI_HEIGHT 26
#define MARU_MARI_PATH L"sprites\\item\\MARU_MARI.txt"
#define MARU_MARI_COUNT 1

//========= ITEM ENERGY
#define ITEM_ENERGY_WIDTH 16
#define ITEM_ENERGY_HEIGHT 16
#define ITEM_ENERGY L"sprites\\item\\ITEM_ENERGY.txt"
#define ITEM_ENERGY_COUNT 2

#define ITEM_ENERGY_HEALTH_GAIN 5

//========= ITEM MISSILE
#define ITEM_MISSILE_WIDTH 16
#define ITEM_MISSILE_HEIGHT 24
#define ITEM_MISSILE L"sprites\\item\\ITEM_MISSILE.txt"
#define ITEM_MISSILE_COUNT 1

#define ITEM_MISSILE_GAIN 3
//================ END GAME ITEM ===================================

//================== ENEMY =====================

//================== ZOOMER =====================
enum ZOOMER_STATE
{
	ON_ZOOMER_UP,
	ON_ZOOMER_BOTTOM,
	ON_ZOOMER_LEFT,
	ON_ZOOMER_RIGHT,
};

enum ZOOMER_DIRECTION {
	ZOOMER_UP,
	ZOOMER_LEFT,
	ZOOMER_RIGHT,
	ZOOMER_DOWN
};
#define ENEMY_SPRITE_PATH L"enemy\\metroid_enemies_sheet.png"
#define ZOOMER_WIDTH 36
#define ZOOMER_HEIGHT 32
#define ZOOMER_SPRITE_COUNT 2
#define ZOOMER_SPEED 60.0f

///////ENERGY
#define ENERGY_SPRITE_PATH L"sprites\\energy\\energy.png"
#define ENERGY_WIDTH 60
#define ENERGY_HEIGHT 50
#define ENERGY_PATH L"sprites\\energy\\energy.txt"
#define ENERGY_SPRITE_COUNT 1
///////NUMBER
#define NUMBER_SPRITE_PATH L"sprites\\font\\font.png"
#define NUMBER_WIDTH 14
#define NUMBER_HEIGHT 14
#define NUMBER_PATH L"sprites\\font\\font.txt"
//////MISSILEINFO
#define MISSILE_INFO_SPRITE_PATH L"sprites\\missile\\missile.png"
#define MISSILE_INFO_WIDTH 20
#define MISSILE_INFO_HEIGHT 30
#define MISSILE_PATH L"sprites\\missile\\missile.txt"
#define MISSILE_SPRITE_COUNT 1

//--YElLOW
#define ZOOMER_YELLOW_TOP L"enemy\\ZOOMER_YELLOW_TOP.txt"
#define ZOOMER_YELLOW_BOTTOM L"enemy\\ZOOMER_YELLOW_BOTTOM.txt"
#define ZOOMER_YELLOW_LEFT L"enemy\\ZOOMER_YELLOW_LEFT.txt"
#define ZOOMER_YELLOW_RIGHT L"enemy\\ZOOMER_YELLOW_RIGHT.txt"

//PINK
#define ZOOMER_PINK_UP L"enemy\\ZOOMER_PINK_TOP.txt"
#define ZOOMER_PINK_BOTTOM L"enemy\\ZOOMER_PINK_BOTTOM.txt"
#define ZOOMER_PINK_LEFT L"enemy\\ZOOMER_PINK_LEFT.txt"
#define ZOOMER_PINK_RIGHT L"enemy\\ZOOMER_PINK_RIGHT.txt"
//================== END ZOOMER =================


//================== SKREE  =====================
enum SKREE_STATE
{
	ON_HANGING,
	ON_FALLING,
	LANDED,
	SHOT,
	EXPLOSION_STATE,
	KILLED
};


#define SKREE_WIDTH 36
#define SKREE_HEIGHT 52

#define SKREE_COUNT 3

#define SKREE_PATH L"enemy\\SKREE.txt"

#define SKREE_STANDARD_ANIMATE_RATE 7
#define SKREE_BOOST_ANIMATE_RATE 30

#define ZOOMER_CASE 0
#define SKREE_CASE 2
#define BOSS1_CASE 3
#define BOSS2_CASE 4

#define SKREE_DISTANCE_TO_SAMUS  300.0f
#define SKREE_SPEED 150.0f

#define SKREE_BULLET_SPEED 125.0f
#define SKREE_BULLET_DISTANCE 75.0f

#define SKREE_LIVE_TIME 50.0f

//================== END SKREE =================

//================ GATE ===============
#define GATE_SPRITES_PATH L"sprites\\gate\\GATE_32.png"
#define GATE_LEFT_EXISTS L"sprites\\gate\\GATE_LEFT_EXISTS.txt"
#define GATE_RIGHT_EXISTS L"sprites\\gate\\GATE_RIGHT_EXISTS.txt"
#define GATE_EXISTS_COUNT 1

#define GATE_LEFT_DESTROYING L"sprites\\gate\\GATE_LEFT_DESTROYING.txt"
#define GATE_RIGHT_DESTROYING L"sprites\\gate\\GATE_RIGHT_DESTROYING.txt"
#define GATE_DESTROYING_COUNT 3

#define GATE_WIDTH 16
#define GATE_HEIGHT 96

#define GATE_BLOCK_PATH L"sprites\\gate\\GATE_BLOCK.txt"
#define GATE_BLOCK_WIDTH 64
#define GATE_BLOCK_HEIGHT 96

#define GATE_TIME_SURVIVE 3
//================= END GATE ===========

//================== EXPLOSION =================
#define EXPLOSION L"enemy\\ENEMY_DETROYED.txt"
#define EXPLOSION_PATH L"enemy\\explosion.png"
#define EXPLOSION_COUNT 1
#define EXPLOSION_WIDTH 48
#define EXPLOSION_HEIGHT 48

//================== END EXPLOSION =================


//================== BIRD  =====================

#define BIRD_WIDTH 36
#define BIRD_HEIGHT 52

#define BIRD_FLY_SPRITE_COUNT 3

#define BIRD_FLY "sprites\\enemy\\BIRD_FLY.txt"

#define BIRD_STANDARD_ANIMATE_RATE 7
#define BIRD_BOOST_ANIMATE_RATE 30
//================== END BIRD =================

//================== BLOCK =====================

#define BLOCK_WIDTH 36
#define BLOCK_HEIGHT 20
#define BLOCK_SPRITE_COUNT 1
#define BLOCK_SPEED 0.1f

//--YElLOW
#define BLOCK_LEFT "sprites\\enemy\\BLOCK_LEFT.txt"
#define BLOCK_RIGHT "sprites\\enemy\\BLOCK_RIGHT.txt"
//================== END BLOCK =================

//================ BOMB =====================
#define BOMB_PATH L"sprites\\item\\BOMB.txt"
#define BOMB_WIDTH 19
#define BOMB_HEIGHT 18
#define BOMB_SPRITE_COUNT 2
#define BOMB_TEXTURE L"sprites\\item\\bomb.png"

//================ END BOMB =================

//================ EFFECT ===================
#define EFFECT_TIME_SURVIVE 1
#define EFFECT_SPRITE_PATH L"sprites\\explode_effect\\explosion.png"

//========== EFFECT EXPLOSION
#define EFFECT_EXPLOSION L"sprites\\explode_effect\\EFFECT_EXPLOSION.txt"
#define EFFECT_EXPLOSION_WIDTH 64
#define EFFECT_EXPLOSION_HEIGHT 64
#define EFFECT_EXPLOSION_COUNT 3

//================ END EFFECT ===============


//================== BEE  =====================

#define BEE_WIDTH 52
#define BEE_HEIGHT 42

#define BEE_FLY_SPRITE_COUNT 2

#define BEE_FLY "sprites\\enemy\\BEE_FLY.txt"
//================== END BEE =================

//================== END ENEMY =================


//================== Bullet ====================
#define SAMUS_BULLET_PATH L"sprites\\item\\bullet.png"
#define X_VELOCITY_BULLET 600.0f
#define Y_VELOCITY_BULLET 600.0f
#define BULLET_COUNT 8
#define WIDTH_BULLET 12
#define HEIGHT_BULLET 14

enum Bullet_SAMUS_Direction
{
	SHOOT_UP_LEFT,
	SHOOT_UP_RIGHT,
	SHOOT_LEFT,
	SHOOT_RIGHT,
	OFF
};

//================== END Bullet ====================

//================== Grid ====================
#define CELL_SIZE 128
#define DEFINE_ROW 8
#define DEFINE_COLUMN 20
#define COLLISION_DISTANCE 15
enum COLLISION_DIRECTION {
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,
	NONE
};
//================== END Grid ====================

#define ZOOMER_YELLOW_CASE 0
#define ZOOMER_PINK_CASE 1
#define SKREE_CASE 2
#define RIO_CASE 3

//================== BOSS ====================
#define BOSS_TEXTURE L"enemy\\boss_sheet.png"
//---------RIDLEY------------
#define WIDTH_RIDLEY 96
#define HEIGHT_RIDLEY_SIT 120
#define HEIGHT_RIDLEY_FLY 139
#define RIDLEY_COUNT 2
#define RIDLEY_SIT_LEFT_PATH L"enemy\\RIDLEY_SIT_LEFT.txt"
#define RIDLEY_SIT_RIGHT_PATH L"enemy\\RIDLEY_SIT_RIGHT.txt"
#define RIDLEY_FLY_LEFT_PATH L"enemy\\RIDLEY_FLY_RIGHT.txt"
#define RIDLEY_FLY_RIGHT_PATH L"enemy\\RIDLEY_FLY_RIGHT.txt"

#define WIDTH_RIDLEY_BULLET 23
#define HEIGHT_RIDLEY_BULLET 24
#define RIDLEY_BULLET_COUNT 4
#define RIDLEY_BULLET_PATH L"enemy\\RIDLEY_BULLET.txt"

enum RIDLEY_STATE {
	SIT_LEFT,
	FLY_LEFT,
	SIT_RIGHT,
	FLY_RIGHT
};
//---------END RIDLEY--------

//---------KRAID-------------
#define WIDTH_KRAID 70
#define HEIGHT_KRAID 96
#define KRAID_COUNT 2
#define KRAID_RIGHT_PATH L"enemy\\KRAID_RIGHT.txt"
#define KRAID_LEFT_PATH L"enemy\\KRAID_LEFT.txt"

#define SIZE_KRAID_BOMERANG 25
#define COUNT_KRAID_BOMERANG 4
#define KRAID_BOMERANG_PATH L"enemy\\KRAID_BOMERANG.txt"

#define WIDTH_KRAID_BULLET 26
#define HEIGHT_KRAID_BULLET 11
#define COUNT_KRAID_BULLET 1
#define KRAID_BULLET_PATH L"enemy\\KRAID_BULLET.txt"
//---------END KRAID---------
//================== END BOSS ====================

