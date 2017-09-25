#include <SDL_image.h>
#include "SDL.h"
#include "SDL_ttf.h"

int DrawText(SDL_Surface* screen, TTF_Font* font, const char* text)
{
    SDL_Color color = {0,0,0};//颜色
    SDL_Surface *text_surface;
    text_surface = TTF_RenderUTF8_Solid(font, text, color);
    TTF_RenderUTF8_Blended(font, text, color);
    if (text_surface != NULL)
    {
        SDL_BlitSurface(text_surface, NULL, screen, NULL);//将文字复制到屏幕的surface上面
        SDL_FreeSurface(text_surface);
    } else  {
        // report error
        return 0;
    }
    text_surface= TTF_RenderUTF8_Blended(font, text, color);
    if (text_surface != NULL)
    {
        SDL_Rect des_pos={0,TTF_FontHeight(font),screen->w,screen->h};
        SDL_BlitSurface(text_surface, NULL, screen, &des_pos);//将文字复制到屏幕的surface上面
        SDL_FreeSurface(text_surface);
        return 1;
    } else  {
        // report error
        return 0;
    }
}


 int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    SDL_Log("lxm SDL main enter");



    //配置一个图像缩放的效果,linear效果更平滑,也叫抗锯齿
    //SDL_setenv(SDL_HINT_RENDER_SCALE_QUALITY,"linear",0);
    // 初始化SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return 1;

    // 创建一个窗口
    window = SDL_CreateWindow("SDL_RenderClear", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_SHOWN);
    // 创建一个渲染器
    renderer = SDL_CreateRenderer(window, -1, 0);
     if(TTF_Init()==-1) {
         printf("TTF_Init: %s\n", TTF_GetError()); return 1;
     }
//打开字库
     TTF_Font *font;
     font=TTF_OpenFont("font.ttf", 128);
     if(!font) {
         printf("TTF_OpenFont: %s\n", TTF_GetError());
     }
    // 创建一个Surface
    //SDL_Surface *bmp = SDL_LoadBMP("sdl.bmp");
     //初始化所有格式
     IMG_Init(~0);
    //加载图片
     SDL_Surface *bmp = IMG_Load("test.jpg");
    //设置图片中的白色为透明色
    SDL_SetColorKey(bmp, SDL_TRUE, 0xffffff);

     DrawText(bmp,font,"代码GG");

    // 创建一个Texture
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, bmp);
    //清除所有事件
    SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
    //进入主循环
    while (1) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN || event.type == SDL_FINGERDOWN)
                break;
        }
        //使用红色填充背景
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);
        // 将纹理布置到渲染器
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        // 刷新屏幕
        SDL_RenderPresent(renderer);

    }
     // 释放Surface
    SDL_FreeSurface(bmp);
    //  释放Texture
    SDL_DestroyTexture(texture);
    //释放渲染器
    SDL_DestroyRenderer(renderer);
    //释放窗口
    SDL_DestroyWindow(window);
    //延时
    //SDL_Delay(8000);
    //退出
    SDL_Quit();
    return 0;
}