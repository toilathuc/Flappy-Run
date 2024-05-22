//#include <iostream>
//#include <SDL.h>
//#include <SDL_image.h>
//using namespace std;
//
//const int SCREEN_WIDTH = 800;
//const int SCREEN_HEIGHT = 600;
//const char* WINDOW_TITLE = "SDL test";
//
//void logSDLError(std::ostream& os, const std::string& msg, bool fatal = false);
//void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);
//void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
//void waitUntilKeyPressed();
//
//SDL_Texture* loadTexture(const std::string& file, SDL_Renderer* renderer);
//
//int main(int argc, char* argv[])
//{
//    SDL_Window* window;
//    SDL_Renderer* renderer;
//    initSDL(window, renderer);
//
//    SDL_Texture* background = loadTexture("bikiniBottom.jpg", renderer);
//    SDL_RenderCopy(renderer, background, NULL, NULL);
//    SDL_RenderPresent(renderer);
//
//    // draw
//    waitUntilKeyPressed();
//    quitSDL(window, renderer);
//    return 0;
//}
//
//SDL_Texture* loadTexture(const std::string& file, SDL_Renderer* renderer)
//{
//    SDL_Texture* texture = IMG_LoadTexture(renderer, file.c_str());
//    // SDL_Texture* texture = IMG_LoadTexture(renderer, file.c_str());
//    if (texture == nullptr)
//    {
//        logSDLError(std::cout, "LoadTexture", true);
//    }
//    return texture;
//}
//
//
//void logSDLError(std::ostream& os, const std::string& msg, bool fatal)
//{
//    os << msg << " Error: " << SDL_GetError() << std::endl;
//    if (fatal) {
//        SDL_Quit();
//        exit(1);
//    }
//}
//
//void initSDL(SDL_Window*& window, SDL_Renderer*& renderer)
//{
//    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
//        logSDLError(std::cout, "SDL_Init", true);
//
//    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
//        SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);
//
//    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);
//
//    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
//    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
//}
//
//void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
//{
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//}
//
//void waitUntilKeyPressed()
//{
//    SDL_Event e;
//    while (true) {
//        if (SDL_WaitEvent(&e) != 0 &&
//            (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
//            return;
//        SDL_Delay(100);
//    }
//}
//#include<Windows.h>
//#include<SDL.h>
//#include<string>
//#include<SDL_image.h>
//using namespace std;
// Xay dung ham displayformat
// +(ham nay tra ve la kieu SDL surface la mot kieu du lieu ma co co the
// tao ra mo surface image bao phu len man hunh window)
// +Doi so dau vao la ten cua anh backgroud
// +IMG_load se thuc hien doc file anhva tra ve ket qua la du lieu SDL_Suface
// +Sau do key qua tra ve duoc dua vao ham dinh dang hien thi SDL_DisplayFormat toi uu hoa surface cho phu hop
// dau tien can load file anh tu file sau do can phan 

//SDL_Surface* LoadImage(string file_path) {
//	SDL_Surface* load_image = NULL;
//	SDL_Surface* optimize_image = NULL;
//	load_image = IMG_Load(file_path.c_str());
//	if (load_image != NULL) {
//		
//		optimize_image = SDL_DisplayFormat(load_image);
//		SDL_FreeSurface(load_image);
//	}
//	return optimize_image;
//
//
//}
//SDL_Surface* LoadImage(string file_path) {
//	SDL_Surface* load_image = IMG_Load(file_path.c_str());
//	if (load_image != NULL) {
//		SDL_Surface* optimize_image = SDL_ConvertSurface(load_image, load_image->format, 0);
//		SDL_FreeSurface(load_image);
//		return optimize_image;
//	}
//	return NULL;
//}


/* +Khoi tao che do thu vien SDL voi kieu la, SDL_INIT EVERTHING.
*  +Thiet lap che do dinh dang video SDL trong moi truong windows.
* => Kich thuoc window swe la 1200 600. toi co the cho ngau nhien va sua lai size cua tam anh. Hoac 
	toi cos the chon anh theo size
* +32 la so chi bit per pixel. nghia la 1 pixel duoc ma hoa boi 32 bit
=> va co flag chon la SDL_SWSurface
+ Thuc hien load anh banh cach hoi ham Loadimage ow treb va chung ta chuyen ten va anh. Nho doi ten 
kho down cho dung ten
+	Sau do goi ham BlitSurface dev thuc hien qua trinh map anh vao man hinh trong che do SDL
+	Neu khong co ham tre 500 thi chuong trinh chay len roi tat ngay
+	Cuoi cung la giai phong bien luu trux imag va thoat chuong trinh

*/
//int main() {
//	SDL_Surface* screen;
//	SDL_Surface* image;
//	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) return 1;
//
//	SDL_Window* window = SDL_CreateWindow("SDL test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 600, SDL_WINDOW_SHOWN);
//	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//
//	image = LoadImage("bikiniBottom");
//	SDL_Rect destRect = { 0, 0, 1200, 600 };
//	//screen = SDL_SetVideoMode(1200, 600, 32, SDL_SWSURFACE);
//	SDL_BlitSurface(image, NULL, SDL_GetWindowSurface(window), &destRect);
//
//	//SDL_BlitSurface(image, NULL, screen, NULL);
//	SDL_RenderPresent(renderer);
//	///--->//SDL_Flip(screen);
//	SDL_Delay(5000);
//	SDL_DestroyRenderer(renderer);
//	SDL_DestroyWindow(window);
//	SDL_Quit();
//	
//}
//

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE = "SDL test";

void logSDLError(std::ostream& os, const std::string& msg, bool fatal = false);
void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();

SDL_Texture* loadTexture(const std::string& file, SDL_Renderer* renderer);

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);

    SDL_Texture* background = loadTexture("bikiniBottom.jpg", renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);
    SDL_RenderPresent(renderer);

    // draw
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}

SDL_Texture* loadTexture(const std::string& file, SDL_Renderer* renderer)
{
    SDL_Texture* texture = IMG_LoadTexture(renderer, file.c_str());
    // SDL_Texture* texture = IMG_LoadTexture(renderer, file.c_str());
    if (texture == nullptr)
    {
        logSDLError(std::cout, "LoadTexture", true);
    }
    return texture;
}


void logSDLError(std::ostream& os, const std::string& msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window*& window, SDL_Renderer*& renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if (SDL_WaitEvent(&e) != 0 &&
            (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}