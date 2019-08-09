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
#ifndef _BASIC_RAY_TRACING_VECTOR_H_
#define _BASIC_RAY_TRACING_VECTOR_H_
#include <cmath>
#include <iostream>

struct Vector3f final {
    union {
        float a[3];

        struct {
            float x, y, z;
        };

        struct {
            float r, g, b;
        };
    };

    Vector3f() : a() {}
    Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}
    Vector3f(float *a) {
        this->a[0] = a[0];
        this->a[1] = a[1];
        this->a[2] = a[2];
    }

    const Vector3f &operator+() const { return *this; }
    Vector3f operator-() const { return {-x, -y, -z}; }
    float operator[](int i) const { return a[i]; }
    float &operator[](int i) { return a[i]; }

    Vector3f operator+(const Vector3f &other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vector3f operator-(const Vector3f &other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    Vector3f &operator+=(const Vector3f &other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3f &operator-=(const Vector3f &other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    float length() const { return sqrtf(x * x + y * y + z * z); }
    float length2() const { return x * x + y * y + z * z; }

    Vector3f &normalize() {
        float inv = 1.0f / length();
        x *= inv;
        y *= inv;
        z *= inv;
        return *this;
    }

    Vector3f getNormalizedVector() const { return Vector3f(*this).normalize(); }

    friend std::istream &operator>>(std::istream &is, Vector3f &vec) {
        is >> vec.x >> vec.y >> vec.z;
        return is;
    }

    Vector3f operator*(const Vector3f &other) const {
        return {x * other.x, y * other.y, z * other.z};
    }

    Vector3f &operator*=(const Vector3f &other) {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    friend Vector3f operator*(float t, const Vector3f &vec) {
        return {vec.x * t, vec.y * t, vec.z * t};
    }

    Vector3f operator*(float t) const { return {x * t, y * t, z * t}; }

    Vector3f &operator*=(float t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    Vector3f operator/(const Vector3f &other) const {
        return {x / other.x, y / other.y, z / other.z};
    }

    Vector3f &operator/=(const Vector3f &other) {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    Vector3f operator/(float t) const { return {x / t, y / t, z / t}; }

    Vector3f &operator/=(float t) {
        x /= t;
        y /= t;
        z /= t;
        return *this;
    }
};

float dot(const Vector3f &a, const Vector3f &b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

Vector3f cross(const Vector3f &a, const Vector3f &b) {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

using Color3f = Vector3f;
using Point3f = Vector3f;
#endif
