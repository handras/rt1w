#include "stdio.h"
#include "math.h"
#define SDL_MAIN_HANDLED
#include "SDL.h"

#include "sphere.h"
#include "scene.h"
#include "camera.h"
#include "rand_utils.h"
extern "C" {
#include "bmp.h"
}

#define WIN_WIDTH 1080
#define WIN_HEIGHT 720
#define SUBSAMPLING 2
#define MAXDETH 5

#define fSUBSAMPLING (float)(SUBSAMPLING)
#define EPSILON 0.00002

void showImage(SDL_Renderer *renderer, SDL_Texture *texture, uint8_t *pixels);
void renderRaytracedImage(uint8_t *pixels);
void cleanUp();
scene create_scene();
vec3 ray_color(ray, scene &, int);

int main(int argc, char **argv) {
    printf("Hello Andras!\n");
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("RTRenderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, 0);
    if (window == NULL) {
        printf("Can't create window. Error is:\n%s", SDL_GetError());
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL) {
        printf("Can't create renderer. Error is:\n%s", SDL_GetError());
    }
    SDL_Texture *texture = SDL_CreateTexture(renderer,
                                             SDL_PIXELFORMAT_RGBA32,
                                             SDL_TEXTUREACCESS_STREAMING,
                                             WIN_WIDTH,
                                             WIN_HEIGHT);
    if (texture == NULL) {
        printf("Can't create texture. Error is:\n%s", SDL_GetError());
    }

    uint8_t *pixels = new uint8_t[WIN_WIDTH * WIN_HEIGHT * 4];

    renderRaytracedImage(pixels);

    showImage(renderer, texture, pixels);
    SDL_Event event;
    while (1) {
        if (SDL_WaitEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void showImage(SDL_Renderer *renderer, SDL_Texture *texture, uint8_t *pixels) {
    int texture_pitch = 0;
    void *texture_pixels = NULL;
    if (SDL_LockTexture(texture, NULL, &texture_pixels, &texture_pitch) != 0) {
        SDL_Log("Unable to lock texture: %s", SDL_GetError());
    } else {
        memcpy(texture_pixels, pixels, texture_pitch * WIN_HEIGHT);
    }
    SDL_UnlockTexture(texture);
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void renderRaytracedImage(uint8_t *pixels) {
    // Camera
    auto cam = camera((float)WIN_WIDTH / WIN_HEIGHT);
    scene s = create_scene();

    printf("Starting render... \n");
    for (int j = WIN_HEIGHT - 1; j >= 0; --j) {
        printf("Scanlines remaining: %d\t\t\r", j);
        for (int i = 0; i < WIN_WIDTH; ++i) {
            vec3 pixel_color = vec3({0, 0, 0});
            for (int k = 0; k < SUBSAMPLING; k++) {
                for (int l = 0; l < SUBSAMPLING; l++) {
                    double u = (double)(i + (k / fSUBSAMPLING)) / (WIN_WIDTH - 1);
                    double v = (double)(j + (l / fSUBSAMPLING)) / (WIN_HEIGHT - 1);
                    ray r = cam.get_ray(u, v);
                    pixel_color += ray_color(r, s, MAXDETH);
                }
            }
            pixel_color = pixel_color / (fSUBSAMPLING * fSUBSAMPLING);
            int pixel_index = ((WIN_HEIGHT - 1 - j) * WIN_WIDTH + i) * 4;
            pixels[pixel_index + 0] = sqrt(pixel_color.r) * 255.999f;
            pixels[pixel_index + 1] = sqrt(pixel_color.g) * 255.999f;
            pixels[pixel_index + 2] = sqrt(pixel_color.b) * 255.999f;
            pixels[pixel_index + 3] = 255;
        }
    }
    printf("\nFinished!\n");
    printf("Saving image...\n");
    generateBitmapImage(pixels, WIN_HEIGHT, WIN_WIDTH, "generated_image.bmp");
    printf("Saved!\n");
}

vec3 ray_color(ray r, scene &s, int depth) {
    hit_record rec;
    if (depth <= 0)
        return vec3({0, 0, 0});
    if (s.hit(r, EPSILON, 10e8, rec)) { // scene
        ray scattered;
        vec3 attenuation;
        if (rec.mat->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, s, depth - 1);
        return vec3({0, 0, 0});
        // normal = normal.normalize();
        // return (normal + vec3({1, 1, 1})) / 2;
    } else { // background
        vec3 unit_dir = r.dir.normalize();
        // pastell
        // vec3 c1 = {0.9f, 0.75f, 1.0f};
        // vec3 c2 = {0.7f, 0.9f, 0.9f};
        // white
        vec3 c1 = {0.99f, 0.99f, 0.99f};
        vec3 c2 = {0.99f, 0.99f, 0.99f};
        // blue green
        // vec3 c1 = {0.1f, 0.05f, 1.0f};
        // vec3 c2 = {0.1f, 1.0f, 0.08f};
        auto t = 0.5 * (unit_dir.x + 1);
        vec3 color = c1 * t + c2 * (1 - t);
        return color;
    }
}

scene create_scene() {
    auto mat1 = new lambertian(vec3({0.3f, 0.2f, 0.8f}));
    auto mat_silver = new metal(vec3({0.8f, 0.8f, 0.9f}));
    auto mat_gold = new metal(vec3({0.828125f, 0.683593f, 0.2148439f}));
    auto s1 = new sphere(vec3({0, 0, -1.0}), 0.5, mat1);
    auto s2 = new sphere(vec3({-1.5, 0, -1.2}), 0.49, mat_silver);
    auto s3 = new sphere(vec3({1.5, 0, -1.2}), 0.49, mat_gold);
    auto s4 = new sphere(vec3({0, -100.5, -1.0}), 100, mat1);
    scene s;
    s.add(*s1);
    s.add(*s2);
    s.add(*s3);
    s.add(*s4);
    return s;
}

void cleanUp() {
}
