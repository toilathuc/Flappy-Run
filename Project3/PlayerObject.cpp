#include "PlayerObject.h"

PlayerObject::PlayerObject()
{
    is_falling_ = false;
    is_die_ = false;
    is_jumping_ = false;  // Khởi tạo trạng thái nhảy là false
    y_val_ = 1;

    // Thiết lập vị trí ban đầu của nhân vật trên mặt đất
    rect_.x = 100;  // Vị trí x ban đầu
    rect_.y = GROUND_MAP - rect_.h;  // Vị trí y để nhân vật đứng trên mặt đất
}

PlayerObject::~PlayerObject()
{
    Free();
}

void PlayerObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{
    static bool isJumping = false;  
    if (events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_UP:
            if (!isJumping)  
            {
                y_val_ = -15;
                isJumping = true; 
            }
            break;
        }
    }
    else if (events.type == SDL_KEYUP)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_UP:
            y_val_ = 5;
            isJumping = false;  
            break;
        }
    }
}
bool PlayerObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImageFile(path, screen);
    return ret;
}

void PlayerObject::Show(SDL_Renderer* des)
{
    BaseObject::Render(des);
}

void PlayerObject::DoFalling(SDL_Renderer* des)
{
    rect_.y += y_val_;
    if ((rect_.y + rect_.h) >= GROUND_MAP)
    {
        rect_.y = GROUND_MAP - rect_.h;  // Đặt nhân vật đứng vững trên mặt đất
        y_val_ = 0;  // Dừng di chuyển theo trục y
        is_falling_ = false;  // Cập nhật trạng thái không còn rơi
        is_jumping_ = false;  // Cập nhật trạng thái không còn nhảy
        // Khôi phục hoặc thay đổi hình ảnh nhân vật nếu cần
    }
}

void PlayerObject::DoGround(SDL_Renderer* screen)
{
    y_val_ = 0;
    rect_.y = GROUND_MAP - rect_.h;
    is_die_ = true;
}

void PlayerObject::Render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, BaseObject& Ob)
{
    Ob.RenderOb(rect_.x, rect_.y, gRenderer, currentClip);
}

bool PlayerObject::OnGround() const
{
    return (rect_.y + rect_.h >= GROUND_MAP);
}

void PlayerObject::SetRect(int x, int y)
{
    rect_.x = x;
    rect_.y = y;

    // Đảm bảo nhân vật ở trên mặt đất
    if ((rect_.y + rect_.h) > GROUND_MAP)
    {
        rect_.y = GROUND_MAP - rect_.h;
    }
}
