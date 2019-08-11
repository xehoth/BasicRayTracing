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
#ifndef _BASIC_RAY_TRACING_SPHERE_H_
#define _BASIC_RAY_TRACING_SPHERE_H_
#include "Collide.h"
#include "Material.h"

struct Sphere : Collisible {
    Point3f center;
    float radius;
    Material *material;

    Sphere() : center(), radius() {}
    Sphere(const Point3f &center, float radius, Material *material)
        : center(center), radius(radius), material(material) {}

    bool collide(const Ray &r, float tMin, float tMax, CollideRecord &rec) const override {
        Vector3f p = r.getOrigin() - center;
        float b = 2.0f * dot(r.getDir(), p);
        float c = p.length2() - radius * radius;
        float delta = b * b - 4 * c;
        if (delta > 0) {
            float t = (-b - sqrtf(delta)) / 2.0f;
            if (tMin < t && t < tMax) {
                rec.t = t;
                rec.p = r.get(t);
                rec.normal = (rec.p - center).normalize();
                rec.material = material;
                return true;
            }
            t = (-b + sqrtf(delta)) / 2.0f;
            if (tMin < t && t < tMax) {
                rec.t = t;
                rec.p = r.get(t);
                rec.normal = (rec.p - center).normalize();
                rec.material = material;
                return true;
            }
        }
        return false;
    }
};
#endif