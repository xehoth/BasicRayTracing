/**
 * Copyright (c) 2019, xehoth
 * All rights reserved.
 *
 * Licensed under the MIT License;
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @author xehoth
 */
#include "../3rdParty/svpng/svpng.inc"
#include "../Chapter6/Camera.h"
#include "Sphere.h"
#include "CollisibleList.h"
#include "Metal.h"
#include "Lambertian.h"
#include <cstdio>
#include <limits>

const int WIDTH = 640;
const int HEIGHT = 480;

using byte = unsigned char;

void paint(byte *d, int x, int y, Color3f color, float alpha) {
    d += 4 * ((HEIGHT - y - 1) * WIDTH + x);
    d[0] = 255 * color.r;
    d[1] = 255 * color.g;
    d[2] = 255 * color.b;
    d[3] = 255 * alpha;
}

Color3f mix(const Color3f &a, const Color3f &b, float t) { return a * (1.0f - t) + b * t; }

Color3f paint(const Ray &r, const Collisible &obj, int depth) {
    CollideRecord rec;
    if (obj.collide(r, 0.001f, std::numeric_limits<float>::max(), rec)) {
        Ray scattered;
        Vector3f attenuation;
        if (depth < 50 && rec.material->scatter(r, rec, attenuation, scattered)) {
            return attenuation * paint(scattered, obj, depth + 1);
        }
        return {0.0f, 0.0f, 0.0f};
    }

    Vector3f dir = r.getDir();
    float t = 0.5f * (dir.y + 1.0f);
    return mix({1.0f, 1.0f, 1.0f}, {0.5f, 0.7f, 1.0f}, t);
}

int main() {
    byte d[4 * WIDTH * HEIGHT];
    FILE *f = fopen("ch8.png", "wb");

    Camera camera({0.0f, 0.0f, 0.0f}, {-2.0f, -1.5f, -1.0f}, {4.0f, 0.0f, 0.0f},
                  {0.0f, 3.0f, 0.0f});

    CollisibleList list;
    Collisible *obj[4];
    Material *mats[4];
    mats[0] = new Lambertian({0.8, 0.3, 0.3});
    mats[1] = new Lambertian({0.8, 0.8, 0.0});
    mats[2] = new Metal({0.8, 0.6, 0.2}, 0.3);
    mats[3] = new Metal({0.8, 0.8, 0.8}, 0.3);

    obj[0] = new Sphere({0, 0, -1}, 0.5, mats[0]);
    obj[1] = new Sphere({0, -100.5, -1}, 100, mats[1]);
    obj[2] = new Sphere({1, 0, -1}, 0.5, mats[2]);
    obj[3] = new Sphere({-1, 0, -1}, 0.5, mats[3]);

    for (int i = 0; i < 4; i++) list.add(obj[i]);

    const int SAMPLE_TIMES = 100;
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            Color3f col;
            for (int i = 0; i < SAMPLE_TIMES; i++) {
                float u = (float)(x + genFloat()) / WIDTH;
                float v = (float)(y + genFloat()) / HEIGHT;
                col += paint(camera.getRay(u, v), list, 0);
            }
            col /= SAMPLE_TIMES;
            col = {sqrtf(col[0]), sqrtf(col[1]), sqrtf(col[2])};
            paint(d, x, y, col, 1.0f);
        }
    }

    for (int i = 0; i < 4; i++) delete mats[i];
    for (int i = 0; i < 4; i++) delete obj[i];
    svpng(f, WIDTH, HEIGHT, d, 1);
    fclose(f);
}