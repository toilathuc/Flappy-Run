#include "CommonFunc.h"
#include "PlayerObject.h"
#include "ImpTimer.h"
#include "BlockObject.h"
#include "Geometric.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 640
#define BACKGROUND_LAYER 8

#define BASE_OFFSET_SPEED 0
#define RUNNING_FRAMES 6
#define ROLLING_FRAMES 6

const std::string LAYER[BACKGROUND_LAYER] = {
    "imgs/background/sky.png",
    "imgs/background/sky02.png",
    "imgs/background/clouds_1.png",
    "imgs/background/clouds_2.png",
    "imgs/background/clouds_3.png",
    "imgs/background/clouds_4.png",
    "imgs/background/rocks_1.png",
    "imgs/background/rocks_2.png",
};

BaseObject gBackgroundTexture[BACKGROUND_LAYER];
BaseObject g_background;
BaseObject g_ground;
BaseObject gGroundTexture;
BaseObject Obrun;
BaseObject Obroll;

SDL_Rect gCharacterClips[RUNNING_FRAMES];
SDL_Rect gRollingClips[ROLLING_FRAMES];  // Thêm mảng khung hình cho animation cuộn

TTF_Font* g_font_text = NULL;
TTF_Font* g_font_MENU = NULL;

void RenderScrollingBackground(std::vector<double>& offsetSpeed,
    BaseObject(&gBackgroundTexture)[BACKGROUND_LAYER],
    SDL_Renderer* gRenderer)
{
    std::vector<double> layer_speed = {
        LAYER_1_SPEED, LAYER_2_SPEED, LAYER_3_SPEED,
        LAYER_4_SPEED, LAYER_5_SPEED, LAYER_6_SPEED,
        LAYER_7_SPEED, LAYER_8_SPEED, LAYER_9_SPEED
    };

    for (int i = 0; i < BACKGROUND_LAYER; ++i)
    {
        offsetSpeed[i] -= layer_speed[i];
        if (offsetSpeed[i] < -gBackgroundTexture[i].GetWidth())
        {
            offsetSpeed[i] = 0;
        }

        gBackgroundTexture[i].RenderOb(offsetSpeed[i], 0, gRenderer);
        gBackgroundTexture[i].RenderOb(offsetSpeed[i] + gBackgroundTexture[i].GetWidth(), 0, gRenderer);
    }
}

void RenderScrollingGround(int& speed, BaseObject& gGroundTexture, SDL_Renderer* gRenderer)
{
    speed -= 2;

    if (speed < -gGroundTexture.GetWidth())
    {
        speed = 0;
    }

    gGroundTexture.RenderOb(speed, SCREEN_HEIGHT - gGroundTexture.GetHeight(), gRenderer);
    gGroundTexture.RenderOb(speed + gGroundTexture.GetWidth(), SCREEN_HEIGHT - gGroundTexture.GetHeight(), gRenderer);
}

bool InitData()
{
    bool bSuccess = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("Flappy",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (g_window != NULL)
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen != NULL)
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR,
                RENDER_DRAW_COLOR,
                RENDER_DRAW_COLOR,
                RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
            {
                std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
                bSuccess = false;
            }
        }
        else
        {
            std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            bSuccess = false;
        }

        if (TTF_Init() == -1)
        {
            std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
            bSuccess = false;
        }

        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        {
            std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
            bSuccess = false;
        }

        g_font_text = TTF_OpenFont("font//ARCADE.ttf", 38);
        if (g_font_text == NULL)
        {
            std::cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
            bSuccess = false;
        }

        g_font_MENU = TTF_OpenFont("font//ARCADE.ttf", 80);
        if (g_font_MENU == NULL)
        {
            std::cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
            bSuccess = false;
        }

        for (int i = 0; i < BACKGROUND_LAYER; ++i)
        {
            if (!gBackgroundTexture[i].LoadImageFile(LAYER[i].c_str(), g_screen))
            {
                std::cerr << "Failed to load background image: " << LAYER[i] << std::endl;
                bSuccess = false;
            }
        }
        if (!gGroundTexture.LoadImageFile("imgs/background/ground.png", g_screen))
        {
            std::cerr << "Failed to load ground image" << std::endl;
            bSuccess = false;
        }
        if (!Obrun.LoadImageFile("imgs/character/0run.png", g_screen))
        {
            std::cerr << "Failed to load character image." << std::endl;
            bSuccess = false;
        }
        if (!Obroll.LoadImageFile("imgs/character/r2.png", g_screen))
        {
            std::cerr << "Failed to load character image." << std::endl;
            bSuccess = false;
        }
        else
        {

            for (int i = 0; i < RUNNING_FRAMES; i++)
            {
                gCharacterClips[i].x = 66 * i;
                gCharacterClips[i].y = 0;
                gCharacterClips[i].w = 66;
                gCharacterClips[i].h = 75;
            }
            for (int i = 0; i < ROLLING_FRAMES; i++) 
            {
                gRollingClips[i].x = 66 * i;
                gRollingClips[i].y = 0;  
                gRollingClips[i].w = 66;
                gRollingClips[i].h = 61;  
            }
        }
    }
    else
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        bSuccess = false;
    }

    return bSuccess;
}

bool LoadBackground()
{
    bool ret = g_background.LoadImageFile("img//bkgn.png", g_screen);
    if (!ret)
    {
        std::cerr << "Failed to load background image!" << std::endl;
    }
    return ret;
}

void close()
{
    g_background.Free();
    g_ground.Free();
    gGroundTexture.Free();
    Obrun.Free();
    Obroll.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    TTF_CloseFont(g_font_text);
    TTF_CloseFont(g_font_MENU);
    g_font_text = NULL;
    g_font_MENU = NULL;

    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    if (InitData() == false)
    {
        return -1;
    }

    ImpTimer fps;
    bool quit = false;

    // Make menu game
    while (!quit) {
        int ret_menu = SDLCommonFunc::ShowMenu(g_screen, g_font_MENU, "Play Game", "Guide", "Exit", "img//start.png");
        if (ret_menu == 1) {
            quit = true;
        }
        else if (ret_menu == 2) {
            // Show guide
            SDLCommonFunc::ShowGuide(g_screen, g_font_MENU, "This is the guide text. Replace with actual instructions.");
            continue;  // Show menu again after displaying guide
        }

        if (!LoadBackground()) {
            return -1;
        }

        bool ret = g_ground.LoadImageFile("img//ground2.png", g_screen);
        if (ret == false) {
            std::cerr << "Failed to load ground2 image" << std::endl;
            return -1;
        }
        g_ground.SetRect(0, SCREEN_HEIGHT - g_ground.GetHeight());

    again_label:
        bool stop_scrolling = false;
        bool end_game = false;

        int acceleration = 0;
        int OffsetSpeed_Ground = BASE_OFFSET_SPEED;
        std::vector<double> OffsetSpeed_Bkgr(BACKGROUND_LAYER, BASE_OFFSET_SPEED);

        TextObject text_count_;
        text_count_.setColor(TextObject::WHITE_TEXT);

        PlayerObject player;
        ret = player.LoadImg("img//fl_bird.png", g_screen);
        player.SetRect(100, 100);
        if (ret == false) {
            std::cerr << "Failed to load fl_bird image" << std::endl;
            return -1;
        }

        BlockManager manage_block;
        ret = manage_block.InitBlockList(g_screen);
        if (ret == false) {
            std::cerr << "Failed to initialize block list" << std::endl;
            return -1;
        }

        int frame_Character = 0;
        int frame_Rolling = 0;
        int rolling_timer = 0;

        while (!quit && !end_game)
        {
            fps.start();
            while (SDL_PollEvent(&g_event) != 0)
            {
                if (g_event.type == SDL_QUIT)
                {
                    quit = true;
                }

                player.HandleInputAction(g_event, g_screen);
            }

            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR,
                RENDER_DRAW_COLOR,
                RENDER_DRAW_COLOR,
                RENDER_DRAW_COLOR);

            SDL_RenderClear(g_screen);

            if (!stop_scrolling) {
                RenderScrollingBackground(OffsetSpeed_Bkgr, gBackgroundTexture, g_screen);
                RenderScrollingGround(OffsetSpeed_Ground, gGroundTexture, g_screen);
            }

            manage_block.SetPlayerRect(player.GetRect());

            bool is_falling = player.GetFalling();
            if (is_falling == true)
            {
                manage_block.SetStopMoving(true);
            }
            player.DoFalling(g_screen);
            manage_block.Render(g_screen);

            bool collision = manage_block.GetColState();
            if (collision == true)
            {
                player.SetFalling(true);
                stop_scrolling = true;
                end_game = true;
            }

            SDL_Rect* currentClip_Character = &gCharacterClips[frame_Character / (RUNNING_FRAMES / 6)];
            if (!player.OnGround()) {
                currentClip_Character = &gRollingClips[frame_Rolling / (ROLLING_FRAMES / 6)];
                player.Render(currentClip_Character, g_screen, Obroll);
                frame_Rolling++;
                if (frame_Rolling / (ROLLING_FRAMES / 6) >= ROLLING_FRAMES) {
                    frame_Rolling = 0;
                }
            }
            else {
                currentClip_Character = &gCharacterClips[frame_Character / (RUNNING_FRAMES / 6)];
                player.Render(currentClip_Character, g_screen, Obrun);
                frame_Character++;
                if (frame_Character / (RUNNING_FRAMES / 6) >= RUNNING_FRAMES) {
                    frame_Character = 0;
                }
            }

            // Draw Geometric
            GeometricFormat rectange_size(0, 0, SCREEN_WIDTH, 30);
            ColorData color_data(36, 36, 36);
            Gemometric::RenderRectange(rectange_size, color_data, g_screen);

            GeometricFormat outlie_size(1, 1, SCREEN_WIDTH - 1, 28);
            ColorData color_data1(255, 255, 255);
            Gemometric::RenderOutline(outlie_size, color_data1, g_screen);

            int count = manage_block.GetCount();
            std::string count_str = std::to_string(count);
            text_count_.SetText(count_str);
            text_count_.loadFromRenderedText(g_font_text, g_screen);
            text_count_.RenderText(g_screen, SCREEN_WIDTH * 0.5, 2);

            SDL_RenderPresent(g_screen);

            // Cap the frame rate
            int val1 = fps.get_ticks();
            if (fps.get_ticks() < 1000 / 10)
            {
                SDL_Delay((1000 / 10) - fps.get_ticks());
            }
        }

        // Make menu game over
        if (end_game) {
            SDL_Delay(500);
            int ret_menu = SDLCommonFunc::ShowMenu(g_screen, g_font_MENU,
                "Player Again", "Guide", "Exit",
                "img//end.png");
            if (ret_menu == 1)
            {
                quit = true;
            }
            else if (ret_menu == 2) {
                SDLCommonFunc::ShowGuide(g_screen, g_font_MENU, "This is the guide text. Replace with actual instructions.");
                continue;  // Show menu again after displaying guide
            }
            else
            {
                quit = false;
                manage_block.FreeBlock();
                stop_scrolling = false;
                end_game = false;
                goto again_label;
            }
        }
    }

    close();
    return 0;
}


