
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "CommonFunc.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>


#define SDL_ERROR 1
#define IMG_ERROR 2
#define MIX_ERROR 3
#define TTF_ERROR 4

class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	virtual bool LoadImageFile(std::string path, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void RenderOb(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip = nullptr);


	int GetWidth();
	int GetHeight();



	void Free();
	void SetRect(const int& x, const int& y) { rect_.x = x, rect_.y = y; };
	SDL_Rect GetRect() const { return rect_; }
	SDL_Texture* GetObject() { return p_object_; }

protected:
	SDL_Texture* p_object_;
	SDL_Rect rect_;
};


#endif