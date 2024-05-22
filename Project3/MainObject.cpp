#include "sdlafx.h"
#include "MainObject.h"
#include "BaseObject.h"

MainObject::MainObject()
{
	frame_ = 0;
	x_pos_ = 0;
	y_pos_ = 0;
	x_val_ = 0;
	y_val_ = 0;
	width_frame_ = 0;
	heith_frame_ = 0;
	status_ = WALK_NONE;
	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.jump_ = 0;
	input_type_.down_ = 0;
	input_type_.up_ = 0;
	on_ground = false;
	map_x_ = 0;
	map_y_ = 0;


}

MainObject::~MainObject()
{


}

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);

	if (ret == true)
	{
		width_frame_ = rect_.w / 8;
		heith_frame_ = rect_.h;

	}
	return ret;
}

void MainObject::set_clips()
{
	if (width_frame_ > 0 && heith_frame_ > 0)
	{
		for (int i = 0; i < 8; i++)
		{
			frame_clip_[i].x = i * width_frame_;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame_;
			frame_clip_[i].h = heith_frame_;
		}
	}
}

void MainObject::Show(SDL_Renderer* des)
{
	UpdateImagePlayer(des);
	frame_++;

	if (frame_ >= 8) {
		frame_ = 0;
	}

	rect_.x = x_pos_ - map_x_;
	rect_.y = y_pos_ - map_y_;

	SDL_Rect* current_clip = &frame_clip_[frame_];

	SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, heith_frame_ };

	SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);


}

void MainObject::DoFalling(SDL_Renderer* des)
{
	rect_.y += y_val_;
	if ((rect_.y + rect_.h) >= 600)//1280
	{
		UpdateImagePlayer(des);
		is_falling_ = true;
		//DoGround(des);
	}
}

void MainObject::HamdelInputAction(SDL_Event events, SDL_Renderer* screen)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
				case SDLK_UP:
				{
					status_ = WALK_UP;
					input_type_.down_ = 1;
					input_type_.up_ = 0;
					UpdateImagePlayer(screen);
				}
				break;
			//}
		/*case SDLK_DOWN:
			{
				status_ = WALK_DOWN;
				input_type_.down_ = 0;
				input_type_.up_ = 1;
				UpdateImagePlayer(des);
			}*/
			//break;
		}
	}


	 else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
			case SDLK_UP:
			{
				input_type_.down_ = 0;
				input_type_.jump_ = 1;
			}
			break;
			/*case SDLK_DOWN:
			{
				input_type_.down_ = 0;
			}
			break;*/
		}
	}
}
 

void MainObject:: DoPlayer(Map& map_data)
{


	x_val_ = 0 ;
	y_val_ += 1 ;

	if (y_val_ >= MAX_FALL_SPEED)
	{
		y_val_ = MAX_FALL_SPEED;
	}

	//KIEM TRA MAN MAP BAN DO CO VA CHAM HAY KHONG

	if (input_type_.jump_ == 1)
	{
		if (on_ground == true)
		{
			y_val_ = -PLAYER_JUMP_VALUE;

		}
		//else y_val_ = PLAYER_JUMP_VALUE;
		on_ground = false;
		x_val_ = 0;
		input_type_.jump_ = 0;
	}
	//khi dang nhay giu mai tren khong trung 
	CheckToMap(map_data);
	CenterEntityOnMap(map_data);

}



void MainObject::CenterEntityOnMap(Map& map_data)
{
	map_data.start_x_ = x_pos_ - (SCREEN_WIDTH / 2);
	if (map_data.start_x_ < 0)
	{
		map_data.start_x_ = 0;
	}
	else if (map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_)
	{
		map_data.max_x_ = map_data.max_x_ - SCREEN_WIDTH;
	}
	map_data.start_y_ = y_pos_ - (SCREEN_HEITH / 2);
	if (map_data.start_y_ < 0)
	{
		map_data.start_y_ = 0;
	}
	else if (map_data.start_y_ + SCREEN_HEITH >= map_data.max_y_)
	{
		map_data.start_y_ = map_data.max_y_ - SCREEN_HEITH;
	}
}


void MainObject::CheckToMap(Map& map_data) {

	int x1 = 0, x2 = 0, y1 = 0, y2 = 0;

	// cp the them
	//on_ground = false;


	int min_height = heith_frame_ < TILE_SIZE ? heith_frame_ : TILE_SIZE;


	x1 = (x_pos_ + x_val_) / TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;
	y1 = y_pos_ / TILE_SIZE;
	y2 = (y_pos_ + min_height - 1) / TILE_SIZE;


	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (x_val_ > 0) {
			if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE) {
				
				x_pos_ = x2 * TILE_SIZE - width_frame_ - 1;
				x_val_ = 0;
			}
		}
		else if (x_val_ < 0) {
			if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE) {
				x_pos_ = (x1 + 1) * TILE_SIZE;
				x_val_ = 0;
			}
		}
	}


	int min_width = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;


	x1 = x_pos_ / TILE_SIZE;
	x2 = (x_pos_ + min_width) / TILE_SIZE;
	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + heith_frame_ - 1) / TILE_SIZE;


	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (y_val_ > 0) {
			if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE) {

				y_pos_ = y2 * TILE_SIZE - (heith_frame_ + 1);
				y_val_ = 0;
				on_ground = true;
			//	tamp_x_ = x_pos_;
			}
		}
		else if (y_val_ < 0) {
			if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE) {
				y_pos_ = (y1 + 1) * TILE_SIZE;
				y_val_ = 0;
			//	tamp_y_ = y_pos_;
			}
		}
	}
	//if (x_pos_ == tamp_x_ && y_pos_ == tamp_y_) on_ground = true;

	x_pos_ += x_val_;
	y_pos_ += y_val_;

	


	if (x_pos_ < 0) {
		x_pos_ = 0;
	}
	else if (x_pos_ + width_frame_ > map_data.max_x_) {
		x_pos_ = map_data.max_x_ - width_frame_ - 1;
	}
}


void MainObject::UpdateImagePlayer(SDL_Renderer* des)
{
	if (on_ground == true)
	{
			LoadImg("img//player_right.png",des);
	}
	else
	{
			LoadImg("img//jum_right.png", des);
	}
}
