#ifndef PLAYER_OBJECT_H_
#define PLAYER_OBJECT_H_

#include "BaseObject.h"
#include "CommonFunc.h"

class PlayerObject : public BaseObject
{
public:
    PlayerObject();
    ~PlayerObject();

    void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void DoFalling(SDL_Renderer* des);
    void DoGround(SDL_Renderer* screen);
    bool OnGround() const;
    void Render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, BaseObject& Ob);

    bool IsJumping() const { return is_jumping_; }
    void SetRect(int x, int y);

    // Thêm các phương thức mới
    bool GetIsDie() const { return is_die_; }
    void SetFalling(bool falling) { is_falling_ = falling; }
    bool GetFalling() const { return is_falling_; }

private:
    bool is_falling_;
    bool is_die_;
    bool is_jumping_;
    int y_val_;
};

#endif  // PLAYER_OBJECT_H_
