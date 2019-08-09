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
#include "Ray.h"
#include <cstdio>

const int WIDTH = 640;
const int HEIGHT = 480;

using byte = unsigned char;

void paint(byte *d, int x, int y, Color3f color, float alpha) {
    d += 4 * (y * WIDTH + x);
    d[0] = (int)255 * color.r;
    d[1] = (int)255 * color.g;
    d[2] = (int)255 * color.b;
    d[3] = (int)255 * alpha;
}

Color3f mix(const Color3f &a, const Color3f &b, float t) { return a * (1.0f - t) + b * t; }

Color3f paint(const Ray &r) {
    Vector3f dir = r.getDir();
    float t = 0.5f * (dir.y + 1.0f);
    return mix({1.0f, 1.0f, 1.0f}, {0.5f, 0.7f, 1.0f}, t);
}

int main() {
    FILE *f = fopen("ch3.png", "wb");
    byte d[4 * WIDTH * HEIGHT];
    Point3f lowerLeftCorner(-2.0f, -1.0f, -1.0f);
    Vector3f horizonal(4.0f, 0.0f, 0.0f);
    Vector3f vertical(0.0f, 2.0f, 0.0f);
    Point3f origin(0.0f, 0.0f, 0.0f);

    for (int y = HEIGHT - 1; y >= 0; y--) {
        for (int x = 0; x < WIDTH; x++) {
            float u = (float)x / WIDTH;
            float v = (float)y / HEIGHT;
            Ray r(origin, lowerLeftCorner + u * horizonal + v * vertical);
            paint(d, x, y, paint(r), 1.0f);
        }
    }
    svpng(f, WIDTH, HEIGHT, d, 1);
    fclose(f);
}