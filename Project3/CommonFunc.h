
//Copyright: Phattrienphanmem123az.com
#ifndef COMMON_FUNC_H_
#define COMMON_FUNC_H_

#include <windows.h>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "TextObject.h"
#include "BaseObject.h"


#define SDL_ERROR 1
#define IMG_ERROR 2
#define MIX_ERROR 3
#define TTF_ERROR 4

const int BACKGROUND_LAYER = 8;

const double LAYER_1_SPEED = 0.0;
const double LAYER_2_SPEED = 0.25;
const double LAYER_3_SPEED = 0.5;
const double LAYER_4_SPEED = 0.75;
const double LAYER_5_SPEED = 1.0;
const double LAYER_6_SPEED = 1.25;
const double LAYER_7_SPEED = 1.5;
const double LAYER_8_SPEED = 1.75;
const double LAYER_9_SPEED = 2.0;

static  SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;

static SDL_Event g_event;

#define GROUND_MAP 550

const int COLOR_KEY_R = 180;
const int COLOR_KEY_G = 180;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0XFF;

//Screen
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;

const int BLOCK_WIDTH = 70;
const int BLOCK_HEIGHT = 480;

typedef struct GeometricFormat
{
public:
    GeometricFormat(int left, int top, int width, int height)
    {
        left_ = left;
        top_ = top;
        width_ = width;
        height_ = height;
    }

    int left_;
    int top_;
    int width_;
    int height_;
};

typedef struct ColorData
{
public:
    ColorData(Uint8 r, Uint8 g, Uint8 b)
    {
        red_ = r, green_ = g, blue_ = b;
    }
    Uint8 red_;
    Uint8 green_;
    Uint8 blue_;
};

void LogError(std::string msg, int error_code = SDL_ERROR);

namespace SDLCommonFunc
{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
    int ShowMenu(SDL_Renderer* g_screen, TTF_Font* font,
        const std::string& menu1,
        const std::string& menu2,
        const std::string& menu3,
        const std::string& img_name);
    void ShowGuide(SDL_Renderer* screen, TTF_Font* font, const std::string& guideText);
    int MyRandom(int min, int max);
}





#endif