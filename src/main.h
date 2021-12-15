#ifndef MAIN_H
#define MAIN_H

void showImage(SDL_Renderer *renderer, SDL_Texture *texture, uint8_t *pixels);
void renderRaytracedImage(uint8_t *pixels);
int render_wrapper(void *);
void cleanUp();
scene create_scene();
vec3 ray_color(ray, scene &, int);

typedef struct {
    SDL_Event *event;
    uint8_t *pixels;
} render_fn_data;

#endif // MAIN_H
