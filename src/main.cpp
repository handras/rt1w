#include "stdio.h"
#include "math.h"
#define SDL_MAIN_HANDLED
#include "SDL.h"

#include "sphere.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

void showImage(SDL_Renderer *renderer, SDL_Texture *texture, uint8_t *pixels);
void renderRaytracedImage(uint8_t *pixels);
void cleanUp();
vec3 ray_color(ray);

int main(int argc, char **argv) {
    printf("Hello Andras!\n");
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("RTRenderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture *texture = SDL_CreateTexture(renderer,
                                             SDL_PIXELFORMAT_RGBA32,
                                             SDL_TEXTUREACCESS_STREAMING,
                                             WIN_WIDTH,
                                             WIN_HEIGHT);

    uint8_t pixels[WIN_WIDTH * WIN_HEIGHT * 4] = {0};
    for (size_t i = 0; i < WIN_WIDTH; i++) {
        for (size_t j = 0; j < WIN_HEIGHT; j++) {
            pixels[(j * WIN_WIDTH + i) * 4 + 0] = (3 * i < WIN_WIDTH) ? 20 : ((float)3 / 2 * i < WIN_WIDTH) ? 128
                                                                                                            : 220;
            pixels[(j * WIN_WIDTH + i) * 4 + 1] = (3 * j < WIN_HEIGHT) ? 20 : ((float)3 / 2 * j < WIN_HEIGHT) ? 128
                                                                                                              : 220;
            pixels[(j * WIN_WIDTH + i) * 4 + 2] = (j + i) > (WIN_WIDTH * j + i) % 9 ? 180 : 0;
            pixels[(j * WIN_WIDTH + i) * 4 + 3] = 255;
        }
    }

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
    float aspect_ratio = (float)WIN_WIDTH / WIN_HEIGHT;
    // Camera
    float viewport_height = 2.0;
    float viewport_width = aspect_ratio * viewport_height;
    float focal_length = 1.0;
    vec3 origin = {0, 0, 0};
    vec3 horizontal = {viewport_width, 0, 0};
    vec3 vertical = {0, viewport_height, 0};
    vec3 lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3({0, 0, focal_length});

    printf("Starting render... \n");
    for (int j = WIN_HEIGHT - 1; j >= 0; --j) {
        printf("Scanlines remaining: %d\t\t\r", j);
        for (int i = 0; i < WIN_WIDTH; ++i) {
            double u = (double)(i) / (WIN_WIDTH - 1);
            double v = (double)(j) / (WIN_HEIGHT - 1);
            vec3 dir = lower_left_corner + horizontal * u + vertical * v - origin;
            ray r{origin, dir};
            vec3 pixel_color = ray_color(r);
            pixels[(j * WIN_WIDTH + i) * 4 + 0] = pixel_color.r * 255.99f;
            pixels[(j * WIN_WIDTH + i) * 4 + 1] = pixel_color.g * 255.99f;
            pixels[(j * WIN_WIDTH + i) * 4 + 2] = pixel_color.b * 255.99f;
            pixels[(j * WIN_WIDTH + i) * 4 + 3] = 255;
        }
    }
    printf("\nFinished!\n");
}

double hit_sphere(const vec3 &center, double radius, ray &r) {
    vec3 oc = r.orig - center;
    auto a = r.dir.length_squared();
    auto half_b = dot(oc, r.dir);
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-half_b - sqrt(discriminant)) / a;
    }
}

vec3 ray_color(ray r) {
    sphere s1(vec3({0, 0, -1}), 0.5);
    hit_record rec;
    if(s1.hit(r, 0, 100, rec)){
        auto t = rec.t;
        vec3 normal = r.ray_at(t) - s1.center;
        normal = normal.normalize();
        return vec3({normal.x + 1, normal.y + 1, normal.z + 1}) / 2;
    }
    vec3 unit_dir = r.dir.normalize();
    // vec3 c1 = {0.1f, 0.5f, 1.0f};
    // vec3 c2 = {0.3f, 0.2f, 0.8f};
    vec3 c2 = {0.1f, 0.05f, 1.0f};
    vec3 c1 = {0.1f, 1.0f, 0.08f};
    auto t = 0.5 * (unit_dir.y + 1);
    vec3 color = c1 * t + c2 * (1 - t);
    return color;
}

void cleanUp() {
}
