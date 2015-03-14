/**
 * File: Star.h
 * Project: tsc - TinyStarChart
 * Creator: jbangelo
 *
 * Description: Defines an interface for Star objects to follow
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 jbangelo
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef STAR_H_
#define STAR_H_

#include <string>
#include <vector>
#include "sqlite3.h"
#include "SkyObject/SkyObject.h"
#include "Math/Units.h"

using std::string;
using std::vector;
using tsc::SkyObject::SkyObject;

namespace tsc
{
namespace SkyObject
{
    class Star : public SkyObject
    {
        public:
            Star(integer starID, integer hip, integer hd, integer hr, string gliese, string bayer, string pName, real RA, real Dec, real dist, real absM);
            ~Star();
            integer getStarID();
            integer getHIP();
            integer getHD();
            integer getHR();
            string getGliese();
            string getBayerFlamsteed();
            real getAbsMag();

            static vector<Star> getStarsByMag(sqlite3* db, real mag);
            
        protected:
            // The HYG catalog ID for the star
            integer _starID;
            integer _hip;
            // The Henry Draper catalog ID, or -1 if not know
            integer _hd;
            // The Harvard Revised catalog ID, or -1 if not know
            integer _hr;
            // The Gliese catalog Third Edition's ID
            string _gliese;
            // The Bayer/Flamsteed designation
            string _bayerFlamsteed;
            // The Absolute magnitude
            real _absM;
    };
}
}

#endif
