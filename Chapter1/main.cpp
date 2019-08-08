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
#include <cstdio>
#include <vector>

const int WIDTH = 640;
const int HEIGHT = 480;

using byte = unsigned char;

void paint(byte *d, int x, int y, byte r, byte g, byte b, byte a) {
    d += 4 * (y * WIDTH + x);
    d[0] = r;
    d[1] = g;
    d[2] = b;
    d[3] = a;
}

int main() {
    FILE *f = fopen("ch1.png", "wb");
    std::vector<byte> rgba(4 * WIDTH * HEIGHT);
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++)
            paint(rgba.data(), x, y, x * 256 / WIDTH, y * 256 / HEIGHT, 128,
                  (x * 256 / WIDTH + y * 256 / HEIGHT) / 2);
    svpng(f, WIDTH, HEIGHT, rgba.data(), 1);
}