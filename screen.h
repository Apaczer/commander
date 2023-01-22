#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <SDL.h>

#if defined(TRIMUISMART) && defined(VSYNCWAIT)
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#endif

#include "config.h"

struct Screen
{
    // Logical width and height.
    decltype(SDL_Rect().w) w;
    decltype(SDL_Rect().h) h;

    // Scaling factors.
    float ppu_x;
    float ppu_y;

    // Actual width and height.
    decltype(SDL_Rect().w) actual_w;
    decltype(SDL_Rect().h) actual_h;

    // We target 25 FPS because currently the key repeat timer is tied into the
    // frame limit. :(
    int refreshRate = 25;

    SDL_Surface *surface;

#ifdef USE_SDL2
    SDL_Window *window;
#endif

    void flip() {
#ifdef USE_SDL2
		if (SDL_UpdateWindowSurface(window) <= -1) {
			SDL_Log("%s", SDL_GetError());
		}
		surface = SDL_GetWindowSurface(window);
#elif TRIMUISMART
	SDL_Surface *video = SDL_GetVideoSurface();
	// 320x240 rotate 90 CCW
	uint32_t	*s, *d, pix1, pix2;
	int		x, y;
	s = (uint32_t*)surface->pixels + 159;
	d = (uint32_t*)video->pixels;
	for (x=160; x>0; x--, s -= 160*240+1, d += 120) {
		for (y=120; y>0; y--, s += 320, d++) {
			pix1 = s[0];					// read AB
			pix2 = s[160];					// read CD
			d[0] = (pix1>>16) | (pix2 & 0xFFFF0000);	// write BD
			d[120] = (pix1 & 0xFFFF) | (pix2<<16);		// write AC
		}
	}
#ifdef VSYNCWAIT
	static int framebuffer_fd = 0;
	int dmy;
	if (!framebuffer_fd) framebuffer_fd = open("/dev/fb0", O_RDWR);
	if (framebuffer_fd) ioctl(framebuffer_fd, FBIO_WAITFORVSYNC, &dmy);
#endif
	SDL_Flip(video);
#else
      SDL_Flip(surface);
      surface = SDL_GetVideoSurface();
#endif
    }

    // Called once at startup.
    int init();

    // Called on every SDL_RESIZE event.
    int onResize(int w, int h);

    void setPhysicalResolution(int actual_w, int actual_h);

    void zoom(float factor);
};

extern Screen screen;

#endif // _SCREEN_H_
