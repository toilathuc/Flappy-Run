#pragma once
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "CommonFuntion.h"
#include "BaseObject.h"

#define GRAVITY_SPEED 2
#define MAX_FALL_SPEED 8
#define PLAYER_SPEED 10
#define PLAYER_JUMP_VALUE 15

class MainObject :public BaseObject
{
public:
	MainObject();
	~MainObject();

	enum WalkType
	{
		WALK_NONE = 0,
		//WALK_RIGHT = 0,
		//WALK_LEFT = 1,
		WALK_UP = 1,
        WALK_DOWN =2,
	};
	virtual bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HamdelInputAction(SDL_Event events, SDL_Renderer* screen);
	void set_clips(); // chuyen mon quan ly van de animaition

	void DoFalling(SDL_Renderer* des);
	bool GetFalling() const { return is_falling_; }
	void SetFalling(bool falling) { is_falling_ = falling; }


	void DoPlayer(Map& map_data);
	
	void CheckToMap(Map& map_data);
	void SetMapXY(const int map_x, const int map_y) { map_x_ = map_x; map_y_ = map_y; }
	void CenterEntityOnMap(Map& map_data);
	void handleEvents(SDL_Event events, SDL_Renderer* screen);
	void UpdateImagePlayer(SDL_Renderer* des);
	bool GetIsDie() const { return is_die_; }
	bool CheckInMap(Map& map_data);
private:

	bool is_falling_;
	bool is_die_;
	bool is_jump_;

	float x_val_;
	float y_val_;

	float x_pos_;
	float y_pos_;

	int width_frame_;
	int heith_frame_;

	SDL_Rect frame_clip_[8];
	Input input_type_;
	int frame_;
	int status_;
	bool on_ground;

	int map_x_;
	int map_y_;

	int tamp_x_;
	int tamp_y_;

	bool check = true;


};

#endif