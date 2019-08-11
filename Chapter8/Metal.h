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
#ifndef _BASIC_RAY_TRACING_METAL_H_
#define _BASIC_RAY_TRACING_METAL_H_
#include "Material.h"
#include "Random.h"

Vector3f reflect(const Vector3f &v, const Vector3f &n) { return v - 2 * dot(v, n) * n; }

struct Metal : Material {
    Vector3f albedo;
    float fuzz;

    Metal(const Vector3f &albedo, float fuzz = 0) : albedo(albedo), fuzz(fuzz) {}

    bool scatter(const Ray &rayIn, const CollideRecord &rec, Vector3f &attenuation,
                 Ray &scattered) const override {
        Vector3f reflected = reflect(rayIn.getDir(), rec.normal);
        scattered = {rec.p, reflected + fuzz * getRandomUnitVector3f()};
        attenuation = albedo;
        return dot(scattered.getDir(), rec.normal) > 0;
    }
};
#endif