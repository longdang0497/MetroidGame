#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class World;
class Samus;
class Metroid;
class Game;

#define KEYBOARD_BUFFER_SIZE	1024
#define KEY_DOWN(code) ( IsKeyDown(code) )
#define KEY_DOWN(vk_code) ( (GetAsyncKeyState(vk_code)&0x8000)?1:0 )

#define TIME_FREEZING 5000
#define TIME_IN_GAME 7000

#define JUMP_VELOCITY_BOOST 100.0f
#define JUMP_VELOCITY_BOOST_FIRST 50.0f
#define FALLDOWN_VELOCITY_DECREASE 0.3f
#define GRAVITY_VELOCITY 100.f
#define ANIMATE_RATE 20
#define JUMP_HEIGHT 100.0f

#define SAMUS_SPEED 100.0f
#define SAMUS_MORPHING_SPEED 175.0f
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


//================= OBJECT TYPE ================
enum OBJECT_TYPE
{
	SAMUS = 1,
	ENEMY = 2,
	BRICK = 3,
};
//================= END OBJECT TYPE ============


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
//================ END BRICK SIZE =========================================

//================ GAME SOUND =============================================
#define GAME_INTRO_SOUND L"sound\\background\\Intro.wav"
#define APPEARING_SOUND L"Audio\\Enter_samus.wav"
#define POWER_UP_SOUND L"Audio\\Power_Up.wav"
#define ROOMA_SOUND L"Audio\\Brinstar.wav"
//================ END GAME SOUND =========================================