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
#ifndef _BASIC_RAY_TRACING_CAMERA_H_
#define _BASIC_RAY_TRACING_CAMERA_H_
#include "../Chapter3/Ray.h"

struct Camera {
    Point3f origin, lowerLeftCorner;
    Vector3f horizontal, vertical;

    Camera(const Point3f &origin, const Point3f &lowerLeftCorner, const Vector3f &horizontal,
           const Vector3f &vertical)
        : origin(origin),
          lowerLeftCorner(lowerLeftCorner),
          horizontal(horizontal),
          vertical(vertical) {}

    Ray getRay(float u, float v) {
        return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
    }
};
#endif