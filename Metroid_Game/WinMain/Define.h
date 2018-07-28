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

#define KEYBOARD_BUFFER_SIZE	1024
#define KEY_DOWN(code) ( IsKeyDown(code) )
#define KEY_DOWN(vk_code) ( (GetAsyncKeyState(vk_code)&0x8000)?1:0 )

#define TIME_FREEZING 5000
#define TIME_IN_GAME 7000

#define JUMP_VELOCITY_BOOST 0.5f
#define JUMP_VELOCITY_BOOST_FIRST 64.0f
#define FALLDOWN_VELOCITY_DECREASE 0.3f
#define GRAVITY_VELOCITY 0.5f
#define ANIMATE_RATE 30
#define LIVE_TIME 3000

#define SAMUS_SPEED 200.0f
#define FRICTION 1.0f
#define TEXTURE_GAME_CHARACTERS L"sprites\\Player_32x16.png"

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
	SAMUS = 0,
	ENEMY = 1,
	BRICK = 2,
	BULLET = 3,
	ITEM = 4
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
#define JUMPSHOOTright_PATH L"sprites\\JUMPSHOOT_RIGHT.txt"
#define JUMPSHOOTleft_PATH L"sprites\\JUMPSHOOT_LEFT.txt"

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
#define BRICK_SIZE 32
#define BRICK_TEXTURE L"brick_32x32.png"
//================ END BRICK SIZE =========================================

//================ GAME SOUND =============================================
#define GAME_INTRO_SOUND L"sound\\background\\Intro.wav"
#define APPEARING_SOUND L"sound\\background\\Appearance.wav"
#define POWER_UP_SOUND L"Audio\\Power_Up.wav"
#define ROOM1_SOUND L"sound\\background\\Map.wav"
//================ END GAME SOUND =========================================

//================ GAME ITEM ===========================

enum ITEM_TYPE
{
	MARU_MARI,
	ENERGY_ITEM,
	MISSILE_ITEM
};

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

//================= ENEMY TYPE =================
enum ENEMY_TYPE
{
	ZOOMER_YELLOW = 0,
	ZOOMER_PINK = 1,
	BIRD = 2,
	BLOCK = 3,
	BEE = 4,
	RIDLEY = 5,
	MOTHER_BRAIN = 6,
};
//================= END ENEMY TYPE =============

//================== ENEMY =====================
//================== ZOOMER =====================
#define ENEMY_SPRITE_PATH L"enemy\\metroid_enemies_sheet.png"
#define ZOOMER_WIDTH 36
#define ZOOMER_HEIGHT 32
#define ZOOMER_SPRITE_COUNT 2
#define ZOOMER_SPEED 0.07f;

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

//================== BEE  =====================

#define BEE_WIDTH 52
#define BEE_HEIGHT 42

#define BEE_FLY_SPRITE_COUNT 2

#define BEE_FLY "sprites\\enemy\\BEE_FLY.txt"
//================== END BEE =================

//================== END ENEMY =================


//================== Bullet ====================
#define SAMUS_BULLET_PATH L"sprites\\item\\bullet.png"
#define X_VELOCITY_BULLET 12
#define Y_VELOCITY_BULLET 12
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
#define DEFINE_ROW 50
#define DEFINE_COLUMN 100
#define COLLISION_DISTANCE 15
enum COLLISION_DIRECTION {
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,
	NONE
};
//================== END Grid ====================