/**
 * File: main.cpp
 * Project: tsc - TinyStarChart
 * Creator: jbangelo
 *
 * Description: The entry point to the program
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

#include <iostream>
#include <iomanip>
#include <stdlib.h>

#include "sqlite3.h"
#include "Math/Degree.h"
#include "Time/Stardate.h"
#include "SkyObject/Planet.h"

using tsc::Math::Degree;
using tsc::Time::Stardate;
using tsc::Time::ChristianDate;
using tsc::SkyObject::Planet;
using namespace std;

int main(int argc, char** argv)
{
    char *cvalue = NULL;
    int c;
    Stardate *date = NULL;
    opterr = 0;

    while ((c = getopt(argc, argv, "j:")) != -1)
    {
        switch (c)
        {
            case 'j':
                cvalue = optarg;
                date = new Stardate(::atof(cvalue));
                break;
            case '?':
                if (isprint(optopt))
                {
                    cerr << "Unkown option '-" << optopt << "'\n";
                }
                else
                {
                    cerr << "Unkown option character '0x" << optopt << "'\n";
                }
                return 1;
            default:
                return 1;
        }
    }

    if (date != NULL)
    {
        cout << "Using date " << *date << endl;
    }

    return 0;
}
