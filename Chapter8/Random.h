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
#ifndef _BASIC_RAY_TRACING_RANDOM_H_
#define _BASIC_RAY_TRACING_RANDOM_H_
#include <random>
#include <functional>
#include "../Chapter2/Vector.h"

auto genFloat = std::bind(std::uniform_real_distribution<float>(), std::mt19937());

Vector3f getRandomUnitVector3f() {
    Vector3f p;
    do {
        p = 2.0f * Vector3f(genFloat(), genFloat(), genFloat()) - Vector3f(1, 1, 1);
    } while (p.length2() >= 1.0);
    return p;
}
#endif
