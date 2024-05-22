
#include "CommonFunc.h"

namespace SDLCommonFunc {

    int ShowMenu(SDL_Renderer* screen, TTF_Font* font, const std::string& item1, const std::string& item2, const std::string& item3, const std::string& img_path) {
        // Load background image for the menu
       // SDL_Surface* LoadMenuImage(const std::string & file_path) 
      //      SDL_Surface* imageSurface = IMG_Load(file_path.c_str());
        SDL_Surface* menuSurface = IMG_Load(img_path.c_str());

        if (!menuSurface) {
            return 1;
        }
        SDL_Texture* menuTexture = SDL_CreateTextureFromSurface(screen, menuSurface);
        SDL_FreeSurface(menuSurface);

        if (!menuTexture) {
            return 1;
        }

        SDL_Rect menuRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

        // Create menu items
        SDL_Color color = { 255, 255, 255, 255 };
        SDL_Surface* playSurface = TTF_RenderText_Solid(font, item1.c_str(), color);
        SDL_Surface* exitSurface = TTF_RenderText_Solid(font, item2.c_str(), color);
        SDL_Surface* guideSurface = TTF_RenderText_Solid(font, item3.c_str(), color);

        SDL_Texture* playTexture = SDL_CreateTextureFromSurface(screen, playSurface);
        SDL_Texture* exitTexture = SDL_CreateTextureFromSurface(screen, exitSurface);
        SDL_Texture* guideTexture = SDL_CreateTextureFromSurface(screen, guideSurface);

        SDL_Rect playRect = { SCREEN_WIDTH / 2 - playSurface->w / 2, SCREEN_HEIGHT / 2 - 100, playSurface->w, playSurface->h };
        SDL_Rect exitRect = { SCREEN_WIDTH / 2 - exitSurface->w / 2, SCREEN_HEIGHT / 2 + 100, exitSurface->w, exitSurface->h };
        SDL_Rect guideRect = { SCREEN_WIDTH / 2 - guideSurface->w / 2, SCREEN_HEIGHT / 2, guideSurface->w, guideSurface->h };

        SDL_FreeSurface(playSurface);
        SDL_FreeSurface(exitSurface);
        SDL_FreeSurface(guideSurface);

        bool selected = false;
        int x = 0, y = 0;
        while (!selected) {
            while (SDL_PollEvent(&g_event)) {
                switch (g_event.type) {
                case SDL_QUIT:
                    SDL_DestroyTexture(menuTexture);
                    SDL_DestroyTexture(playTexture);
                    SDL_DestroyTexture(exitTexture);
                    SDL_DestroyTexture(guideTexture);
                    return 1;
                case SDL_MOUSEMOTION:
                    x = g_event.motion.x;
                    y = g_event.motion.y;
                    if (x >= playRect.x && x <= playRect.x + playRect.w && y >= playRect.y && y <= playRect.y + playRect.h) {
                        SDL_SetTextureColorMod(playTexture, 255, 0, 0);
                    }
                    else {
                        SDL_SetTextureColorMod(playTexture, 255, 255, 255);
                    }
                    if (x >= exitRect.x && x <= exitRect.x + exitRect.w && y >= exitRect.y && y <= exitRect.y + exitRect.h) {
                        SDL_SetTextureColorMod(exitTexture, 255, 0, 0);
                    }
                    else {
                        SDL_SetTextureColorMod(exitTexture, 255, 255, 255);
                    }
                    if (x >= guideRect.x && x <= guideRect.x + guideRect.w && y >= guideRect.y && y <= guideRect.y + guideRect.h) {
                        SDL_SetTextureColorMod(guideTexture, 255, 0, 0);
                    }
                    else {
                        SDL_SetTextureColorMod(guideTexture, 255, 255, 255);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = g_event.button.x;
                    y = g_event.button.y;
                    if (x >= playRect.x && x <= playRect.x + playRect.w && y >= playRect.y && y <= playRect.y + playRect.h) {
                        SDL_DestroyTexture(menuTexture);
                        SDL_DestroyTexture(playTexture);
                        SDL_DestroyTexture(exitTexture);
                        SDL_DestroyTexture(guideTexture);
                        return 0;
                    }
                    if (x >= exitRect.x && x <= exitRect.x + exitRect.w && y >= exitRect.y && y <= exitRect.y + exitRect.h) {
                        SDL_DestroyTexture(menuTexture);
                        SDL_DestroyTexture(playTexture);
                        SDL_DestroyTexture(exitTexture);
                        SDL_DestroyTexture(guideTexture);
                        return 1;
                    }
                    if (x >= guideRect.x && x <= guideRect.x + guideRect.w && y >= guideRect.y && y <= guideRect.y + guideRect.h) {
                        SDL_DestroyTexture(menuTexture);
                        SDL_DestroyTexture(playTexture);
                        SDL_DestroyTexture(exitTexture);
                        SDL_DestroyTexture(guideTexture);
                        return 2;
                    }
                    break;
                case SDL_KEYDOWN:
                    if (g_event.key.keysym.sym == SDLK_ESCAPE) {
                        SDL_DestroyTexture(menuTexture);
                        SDL_DestroyTexture(playTexture);
                        SDL_DestroyTexture(exitTexture);
                        SDL_DestroyTexture(guideTexture);
                        return 1;
                    }
                }
            }

            SDL_RenderClear(screen);
            SDL_RenderCopy(screen, menuTexture, nullptr, &menuRect);
            SDL_RenderCopy(screen, playTexture, nullptr, &playRect);
            SDL_RenderCopy(screen, exitTexture, nullptr, &exitRect);
            SDL_RenderCopy(screen, guideTexture, nullptr, &guideRect);
            SDL_RenderPresent(screen);
        }
        return 1;
    }

    void ShowGuide(SDL_Renderer* screen, TTF_Font* font, const std::string& guideText)
    {
        // Load background image for the guide screen
        SDL_Surface* guideBgSurface = IMG_Load("img//Main.png");  // Replace with the actual background image path
        if (!guideBgSurface) {
            std::cerr << "Failed to load guide background image! SDL_image Error: " << IMG_GetError() << std::endl;
            return;
        }
        SDL_Texture* guideBgTexture = SDL_CreateTextureFromSurface(screen, guideBgSurface);
        SDL_FreeSurface(guideBgSurface);

        if (!guideBgTexture) {
            std::cerr << "Failed to create texture from surface! SDL Error: " << SDL_GetError() << std::endl;
            return;
        }

        SDL_Rect guideBgRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

        // Create guide text texture
        SDL_Color color = { 255, 255, 255, 255 };
        SDL_Surface* guideSurface = TTF_RenderText_Solid(font, guideText.c_str(), color);
        SDL_Texture* guideTexture = SDL_CreateTextureFromSurface(screen, guideSurface);
        SDL_FreeSurface(guideSurface);

        SDL_Rect guideRect = { SCREEN_WIDTH / 2 - guideSurface->w / 2, SCREEN_HEIGHT / 2 - guideSurface->h / 2, guideSurface->w, guideSurface->h };

        // Create back button texture
        SDL_Surface* backSurface = TTF_RenderText_Solid(font, "Back", color);
        SDL_Texture* backTexture = SDL_CreateTextureFromSurface(screen, backSurface);
        SDL_FreeSurface(backSurface);

        SDL_Rect backRect = { 50, 50, backSurface->w, backSurface->h };

        bool backSelected = false;
        int x = 0, y = 0;
        while (!backSelected) {
            while (SDL_PollEvent(&g_event)) {
                switch (g_event.type) {
                case SDL_QUIT:
                    SDL_DestroyTexture(guideBgTexture);
                    SDL_DestroyTexture(guideTexture);
                    SDL_DestroyTexture(backTexture);
                    return;
                case SDL_MOUSEMOTION:
                    x = g_event.motion.x;
                    y = g_event.motion.y;
                    if (x >= backRect.x && x <= backRect.x + backRect.w && y >= backRect.y && y <= backRect.y + backRect.h) {
                        SDL_SetTextureColorMod(backTexture, 255, 0, 0);
                    }
                    else {
                        SDL_SetTextureColorMod(backTexture, 255, 255, 255);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = g_event.button.x;
                    y = g_event.button.y;
                    if (x >= backRect.x && x <= backRect.x + backRect.w && y >= backRect.y && y <= backRect.y + backRect.h) {
                        backSelected = true;
                    }
                    break;
                case SDL_KEYDOWN:
                    if (g_event.key.keysym.sym == SDLK_ESCAPE) {
                        backSelected = true;
                    }
                }
            }

            SDL_RenderClear(screen);
            SDL_RenderCopy(screen, guideBgTexture, nullptr, &guideBgRect);  // Render background
            SDL_RenderCopy(screen, guideTexture, nullptr, &guideRect);  // Render guide text
            SDL_RenderCopy(screen, backTexture, nullptr, &backRect);  // Render back button
            SDL_RenderPresent(screen);
        }

        SDL_DestroyTexture(guideBgTexture);
        SDL_DestroyTexture(guideTexture);
        SDL_DestroyTexture(backTexture);
    }

} // namespace SDLCommonFunc






int SDLCommonFunc::MyRandom(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

void LogError(std::string msg, int error_code)
{
    if (error_code == SDL_ERROR)
    {
        std::cout << msg << SDL_GetError() << std::endl;
    }
    if (error_code == IMG_ERROR)
    {
        std::cout << msg << IMG_GetError() << std::endl;
    }
    if (error_code == MIX_ERROR)
    {
        std::cout << msg << Mix_GetError() << std::endl;
    }
    if (error_code == TTF_ERROR)
    {
        std::cout << msg << TTF_GetError() << std::endl;
    }
}

bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    int left_a = object1.x;
    int right_a = object1.x + object1.w;
    int top_a = object1.y;
    int bottom_a = object1.y + object1.h;

    int left_b = object2.x;
    int right_b = object2.x + object2.w;
    int top_b = object2.y;
    int bottom_b = object2.y + object2.h;

    // Case 1: size object 1 < size object 2
    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    // Case 2: size object 1 < size object 2
    if (left_b > left_a && left_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (left_b > left_a && left_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    // Case 3: size object 1 = size object 2
    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
    {
        return true;
    }

    return false;
}

