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
#include "../Chapter5/Sphere.h"
#include "../Chapter5/CollisibleList.h"
#include "../Chapter6/Camera.h"
#include <cstdio>
#include <limits>
#include <random>
#include <functional>

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

std::uniform_real_distribution<float> dis;
std::mt19937 engine;
auto gen = std::bind(dis, engine);

Vector3f getRandomUnit() {
    Vector3f p;
    do {
        p = 2.0f * Vector3f(gen(), gen(), gen()) - Vector3f(1, 1, 1);
    } while (p.length2() >= 1.0);
    return p;
}

Color3f paint(const Ray &r, const Collisible &obj) {
    CollideRecord rec;
    if (obj.collide(r, 0.001f, std::numeric_limits<float>::max(), rec))
        return 0.5f * paint({rec.p, rec.normal + getRandomUnit()}, obj);

    Vector3f dir = r.getDir();
    float t = 0.5f * (dir.y + 1.0f);
    return mix({1.0f, 1.0f, 1.0f}, {0.5f, 0.7f, 1.0f}, t);
}

int main() {
    byte d[4 * WIDTH * HEIGHT];
    FILE *f = fopen("ch7.png", "wb");

    Camera camera({0.0f, 0.0f, 0.0f}, {-2.0f, -1.5f, -1.0f}, {4.0f, 0.0f, 0.0f},
                  {0.0f, 3.0f, 0.0f});

    CollisibleList list;
    Collisible *obj[2];
    obj[0] = new Sphere({0, 0, -1}, 0.5);
    obj[1] = new Sphere({0, -100.5, -1}, 100);

    list.add(obj[0]);
    list.add(obj[1]);

    const int SAMPLE_TIMES = 100;
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            Color3f col;
            for (int i = 0; i < SAMPLE_TIMES; i++) {
                float u = (float)(x + gen()) / WIDTH;
                float v = (float)(y + gen()) / HEIGHT;
                col += paint(camera.getRay(u, v), list);
            }
            col /= SAMPLE_TIMES;
            col = {sqrtf(col[0]), sqrtf(col[1]), sqrtf(col[2])};
            paint(d, x, y, col, 1.0f);
        }
    }

    delete obj[0];
    delete obj[1];
    svpng(f, WIDTH, HEIGHT, d, 1);
    fclose(f);
}