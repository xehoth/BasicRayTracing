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
#ifndef _BASIC_RAY_TRACING_COLLISIBLE_LIST_H_
#define _BASIC_RAY_TRACING_COLLISIBLE_LIST_H_
#include "Collide.h"
#include <vector>

struct CollisibleList : Collisible {
    std::vector<Collisible *> d;

    void add(Collisible *x) { d.push_back(x); }

    bool collide(const Ray &r, float tMin, float tMax, CollideRecord &rec) const override {
        bool flag = false;
        float closest = tMax;
        CollideRecord tmpRec;

        for (const auto &i : d) {
            if (i->collide(r, tMin, closest, tmpRec)) {
                flag = true;
                closest = tmpRec.t;
                rec = tmpRec;
            }
        }

        return flag;
    }
};
#endif