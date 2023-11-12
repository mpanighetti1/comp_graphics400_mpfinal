/******************************************************
* Michael Panighetti
*
* Cup Globals Header - Contains All Arrays
* For Cup Collision Spheres + Position.
*******************************************************/

#ifndef CUP_GLOBALS_H
#define CUP_GLOBALS_H

#include "helper_Final.h"

// Player 1 Cup Positions
double cup1_p1_x = 0 * FT, cup1_p1_y = 2.55 * FT, cup1_p1_z = -3 * FT;
bool cup1_p1_score = false;
bool cup1_p1_gone = false;
double cup1_p1_frontCollision[63][3] = {

    // 9
    {cup1_p1_x + 3.9, cup1_p1_y + 9.88, cup1_p1_z + 2.5},
    {cup1_p1_x - 3.9, cup1_p1_y + 9.88, cup1_p1_z + 2.5},
    {cup1_p1_x + 3.2, cup1_p1_y + 9.78, cup1_p1_z + 4.0},
    {cup1_p1_x - 3.2, cup1_p1_y + 9.78, cup1_p1_z + 4.0},
    {cup1_p1_x + 2.03, cup1_p1_y + 9.78, cup1_p1_z + 5.2},
    {cup1_p1_x - 2.03, cup1_p1_y + 9.78, cup1_p1_z + 5.2},
    {cup1_p1_x - 0, cup1_p1_y + 9.78, cup1_p1_z + 5.8},

    // 8
    {cup1_p1_x + 3.9, cup1_p1_y + 8.7, cup1_p1_z + 2.5},
    {cup1_p1_x - 3.9, cup1_p1_y + 8.7, cup1_p1_z + 2.5},
    {cup1_p1_x + 3.2, cup1_p1_y + 8.6, cup1_p1_z + 4.0},
    {cup1_p1_x - 3.2, cup1_p1_y + 8.6, cup1_p1_z + 4.0},
    {cup1_p1_x + 2.03, cup1_p1_y + 8.6, cup1_p1_z + 5.2},
    {cup1_p1_x - 2.03, cup1_p1_y + 8.6, cup1_p1_z + 5.2},
    {cup1_p1_x - 0, cup1_p1_y + 8.6, cup1_p1_z + 5.8},

    // 7 +
    {cup1_p1_x + 3.9, cup1_p1_y + 8.7, cup1_p1_z - 1.0},
    {cup1_p1_x - 3.9, cup1_p1_y + 8.7, cup1_p1_z - 1.0},
    {cup1_p1_x + 3.2, cup1_p1_y + 8.6, cup1_p1_z - 2.5},
    {cup1_p1_x - 3.2, cup1_p1_y + 8.6, cup1_p1_z - 2.5},
    {cup1_p1_x + 2.03, cup1_p1_y + 8.6, cup1_p1_z - 3.7},
    {cup1_p1_x - 2.03, cup1_p1_y + 8.6, cup1_p1_z - 3.7},
    {cup1_p1_x - 0, cup1_p1_y + 8.6, cup1_p1_z - 4.3},

    // 6
    {cup1_p1_x + 3.9, cup1_p1_y + 7.52, cup1_p1_z + 2.5},
    {cup1_p1_x - 3.9, cup1_p1_y + 7.52, cup1_p1_z + 2.5},
    {cup1_p1_x + 3.2, cup1_p1_y + 7.42, cup1_p1_z + 4.0},
    {cup1_p1_x - 3.2, cup1_p1_y + 7.42, cup1_p1_z + 4.0},
    {cup1_p1_x + 2.03, cup1_p1_y + 7.42, cup1_p1_z + 5.2},
    {cup1_p1_x - 2.03, cup1_p1_y + 7.42, cup1_p1_z + 5.2},
    {cup1_p1_x - 0, cup1_p1_y + 7.42, cup1_p1_z + 5.8},

    // 4
    {cup1_p1_x + 3.9, cup1_p1_y + 6.34, cup1_p1_z + 2.5},
    {cup1_p1_x - 3.9, cup1_p1_y + 6.34, cup1_p1_z + 2.5},
    {cup1_p1_x + 3.2, cup1_p1_y + 6.24, cup1_p1_z + 4.0},
    {cup1_p1_x - 3.2, cup1_p1_y + 6.24, cup1_p1_z + 4.0},
    {cup1_p1_x + 2.03, cup1_p1_y + 6.24, cup1_p1_z + 5.2},
    {cup1_p1_x - 2.03, cup1_p1_y + 6.24, cup1_p1_z + 5.2},
    {cup1_p1_x - 0, cup1_p1_y + 6.24, cup1_p1_z + 5.8},

    // 3
    {cup1_p1_x + 3.9, cup1_p1_y + 5.16, cup1_p1_z + 2.5},
    {cup1_p1_x - 3.9, cup1_p1_y + 5.16, cup1_p1_z + 2.5},
    {cup1_p1_x + 3.2, cup1_p1_y + 5.06, cup1_p1_z + 4.0},
    {cup1_p1_x - 3.2, cup1_p1_y + 5.06, cup1_p1_z + 4.0},
    {cup1_p1_x + 2.03, cup1_p1_y + 5.06, cup1_p1_z + 5.2},
    {cup1_p1_x - 2.03, cup1_p1_y + 5.06, cup1_p1_z + 5.2},
    {cup1_p1_x - 0, cup1_p1_y + 5.06, cup1_p1_z + 5.8},

    // 2
    {cup1_p1_x + 3.9, cup1_p1_y + 3.98, cup1_p1_z + 2.5},
    {cup1_p1_x - 3.9, cup1_p1_y + 3.98, cup1_p1_z + 2.5},
    {cup1_p1_x + 3.2, cup1_p1_y + 3.88, cup1_p1_z + 4.0},
    {cup1_p1_x - 3.2, cup1_p1_y + 3.88, cup1_p1_z + 4.0},
    {cup1_p1_x + 2.03, cup1_p1_y + 3.88, cup1_p1_z + 5.2},
    {cup1_p1_x - 2.03, cup1_p1_y + 3.88, cup1_p1_z + 5.2},
    {cup1_p1_x - 0, cup1_p1_y + 3.88, cup1_p1_z + 5.8},

    // 1
    {cup1_p1_x + 3.9, cup1_p1_y + 2.8, cup1_p1_z + 2.5},
    {cup1_p1_x - 3.9, cup1_p1_y + 2.8, cup1_p1_z + 2.5},
    {cup1_p1_x + 3.2, cup1_p1_y + 2.7, cup1_p1_z + 4.0},
    {cup1_p1_x - 3.2, cup1_p1_y + 2.7, cup1_p1_z + 4.0},
    {cup1_p1_x + 2.03, cup1_p1_y + 2.7, cup1_p1_z + 5.2},
    {cup1_p1_x - 2.03, cup1_p1_y + 2.7, cup1_p1_z + 5.2},
    {cup1_p1_x - 0, cup1_p1_y + 2.7, cup1_p1_z + 5.8},

    // 0
    {cup1_p1_x + 3.9, cup1_p1_y + 1.62, cup1_p1_z + 2.5},
    {cup1_p1_x - 3.9, cup1_p1_y + 1.62, cup1_p1_z + 2.5},
    {cup1_p1_x + 3.2, cup1_p1_y + 1.52, cup1_p1_z + 4.0},
    {cup1_p1_x - 3.2, cup1_p1_y + 1.52, cup1_p1_z + 4.0},
    {cup1_p1_x + 2.03, cup1_p1_y + 1.52, cup1_p1_z + 5.2},
    {cup1_p1_x - 2.03, cup1_p1_y + 1.52, cup1_p1_z + 5.2},
    {cup1_p1_x - 0, cup1_p1_y + 1.52, cup1_p1_z + 5.8},
};

double cup2_p1_x = 0.4 * FT, cup2_p1_y = 2.55 * FT, cup2_p1_z = -3.6 * FT;
bool cup2_p1_score = false;
bool cup2_p1_gone = false;
double cup2_p1_frontCollision[63][3] = {

    // 9
    {cup2_p1_x + 3.9, cup2_p1_y + 9.88, cup2_p1_z + 2.5},
    {cup2_p1_x - 3.9, cup2_p1_y + 9.88, cup2_p1_z + 2.5},
    {cup2_p1_x + 3.2, cup2_p1_y + 9.78, cup2_p1_z + 4.0},
    {cup2_p1_x - 3.2, cup2_p1_y + 9.78, cup2_p1_z + 4.0},
    {cup2_p1_x + 2.03, cup2_p1_y + 9.78, cup2_p1_z + 5.2},
    {cup2_p1_x - 2.03, cup2_p1_y + 9.78, cup2_p1_z + 5.2},
    {cup2_p1_x - 0, cup2_p1_y + 9.78, cup2_p1_z + 5.8},

    // 8
    {cup2_p1_x + 3.9, cup2_p1_y + 8.7, cup2_p1_z + 2.5},
    {cup2_p1_x - 3.9, cup2_p1_y + 8.7, cup2_p1_z + 2.5},
    {cup2_p1_x + 3.2, cup2_p1_y + 8.6, cup2_p1_z + 4.0},
    {cup2_p1_x - 3.2, cup2_p1_y + 8.6, cup2_p1_z + 4.0},
    {cup2_p1_x + 2.03, cup2_p1_y + 8.6, cup2_p1_z + 5.2},
    {cup2_p1_x - 2.03, cup2_p1_y + 8.6, cup2_p1_z + 5.2},
    {cup2_p1_x - 0, cup2_p1_y + 8.6, cup2_p1_z + 5.8},

    // 7 +
    {cup2_p1_x + 3.9, cup2_p1_y + 8.7, cup2_p1_z - 1.0},
    {cup2_p1_x - 3.9, cup2_p1_y + 8.7, cup2_p1_z - 1.0},
    {cup2_p1_x + 3.2, cup2_p1_y + 8.6, cup2_p1_z - 2.5},
    {cup2_p1_x - 3.2, cup2_p1_y + 8.6, cup2_p1_z - 2.5},
    {cup2_p1_x + 2.03, cup2_p1_y + 8.6, cup2_p1_z - 3.7},
    {cup2_p1_x - 2.03, cup2_p1_y + 8.6, cup2_p1_z - 3.7},
    {cup2_p1_x - 0, cup2_p1_y + 8.6, cup2_p1_z - 4.3},

    // 6
    {cup2_p1_x + 3.9, cup2_p1_y + 7.52, cup2_p1_z + 2.5},
    {cup2_p1_x - 3.9, cup2_p1_y + 7.52, cup2_p1_z + 2.5},
    {cup2_p1_x + 3.2, cup2_p1_y + 7.42, cup2_p1_z + 4.0},
    {cup2_p1_x - 3.2, cup2_p1_y + 7.42, cup2_p1_z + 4.0},
    {cup2_p1_x + 2.03, cup2_p1_y + 7.42, cup2_p1_z + 5.2},
    {cup2_p1_x - 2.03, cup2_p1_y + 7.42, cup2_p1_z + 5.2},
    {cup2_p1_x - 0, cup2_p1_y + 7.42, cup2_p1_z + 5.8},

    // 4
    {cup2_p1_x + 3.9, cup2_p1_y + 6.34, cup2_p1_z + 2.5},
    {cup2_p1_x - 3.9, cup2_p1_y + 6.34, cup2_p1_z + 2.5},
    {cup2_p1_x + 3.2, cup2_p1_y + 6.24, cup2_p1_z + 4.0},
    {cup2_p1_x - 3.2, cup2_p1_y + 6.24, cup2_p1_z + 4.0},
    {cup2_p1_x + 2.03, cup2_p1_y + 6.24, cup2_p1_z + 5.2},
    {cup2_p1_x - 2.03, cup2_p1_y + 6.24, cup2_p1_z + 5.2},
    {cup2_p1_x - 0, cup2_p1_y + 6.24, cup2_p1_z + 5.8},

    // 3
    {cup2_p1_x + 3.9, cup2_p1_y + 5.16, cup2_p1_z + 2.5},
    {cup2_p1_x - 3.9, cup2_p1_y + 5.16, cup2_p1_z + 2.5},
    {cup2_p1_x + 3.2, cup2_p1_y + 5.06, cup2_p1_z + 4.0},
    {cup2_p1_x - 3.2, cup2_p1_y + 5.06, cup2_p1_z + 4.0},
    {cup2_p1_x + 2.03, cup2_p1_y + 5.06, cup2_p1_z + 5.2},
    {cup2_p1_x - 2.03, cup2_p1_y + 5.06, cup2_p1_z + 5.2},
    {cup2_p1_x - 0, cup2_p1_y + 5.06, cup2_p1_z + 5.8},

    // 2
    {cup2_p1_x + 3.9, cup2_p1_y + 3.98, cup2_p1_z + 2.5},
    {cup2_p1_x - 3.9, cup2_p1_y + 3.98, cup2_p1_z + 2.5},
    {cup2_p1_x + 3.2, cup2_p1_y + 3.88, cup2_p1_z + 4.0},
    {cup2_p1_x - 3.2, cup2_p1_y + 3.88, cup2_p1_z + 4.0},
    {cup2_p1_x + 2.03, cup2_p1_y + 3.88, cup2_p1_z + 5.2},
    {cup2_p1_x - 2.03, cup2_p1_y + 3.88, cup2_p1_z + 5.2},
    {cup2_p1_x - 0, cup2_p1_y + 3.88, cup2_p1_z + 5.8},

    // 1
    {cup2_p1_x + 3.9, cup2_p1_y + 2.8, cup2_p1_z + 2.5},
    {cup2_p1_x - 3.9, cup2_p1_y + 2.8, cup2_p1_z + 2.5},
    {cup2_p1_x + 3.2, cup2_p1_y + 2.7, cup2_p1_z + 4.0},
    {cup2_p1_x - 3.2, cup2_p1_y + 2.7, cup2_p1_z + 4.0},
    {cup2_p1_x + 2.03, cup2_p1_y + 2.7, cup2_p1_z + 5.2},
    {cup2_p1_x - 2.03, cup2_p1_y + 2.7, cup2_p1_z + 5.2},
    {cup2_p1_x - 0, cup2_p1_y + 2.7, cup2_p1_z + 5.8},

    // 0
    {cup2_p1_x + 3.9, cup2_p1_y + 1.62, cup2_p1_z + 2.5},
    {cup2_p1_x - 3.9, cup2_p1_y + 1.62, cup2_p1_z + 2.5},
    {cup2_p1_x + 3.2, cup2_p1_y + 1.52, cup2_p1_z + 4.0},
    {cup2_p1_x - 3.2, cup2_p1_y + 1.52, cup2_p1_z + 4.0},
    {cup2_p1_x + 2.03, cup2_p1_y + 1.52, cup2_p1_z + 5.2},
    {cup2_p1_x - 2.03, cup2_p1_y + 1.52, cup2_p1_z + 5.2},
    {cup2_p1_x - 0, cup2_p1_y + 1.52, cup2_p1_z + 5.8},
};

double cup3_p1_x = -0.4 * FT, cup3_p1_y = 2.55 * FT, cup3_p1_z = -3.6 * FT;
bool cup3_p1_score = false;
bool cup3_p1_gone = false;
double cup3_p1_frontCollision[63][3] = {

    // 9
    {cup3_p1_x + 3.9, cup3_p1_y + 9.88, cup3_p1_z + 2.5},
    {cup3_p1_x - 3.9, cup3_p1_y + 9.88, cup3_p1_z + 2.5},
    {cup3_p1_x + 3.2, cup3_p1_y + 9.78, cup3_p1_z + 4.0},
    {cup3_p1_x - 3.2, cup3_p1_y + 9.78, cup3_p1_z + 4.0},
    {cup3_p1_x + 2.03, cup3_p1_y + 9.78, cup3_p1_z + 5.2},
    {cup3_p1_x - 2.03, cup3_p1_y + 9.78, cup3_p1_z + 5.2},
    {cup3_p1_x - 0, cup3_p1_y + 9.78, cup3_p1_z + 5.8},

    // 8
    {cup3_p1_x + 3.9, cup3_p1_y + 8.7, cup3_p1_z + 2.5},
    {cup3_p1_x - 3.9, cup3_p1_y + 8.7, cup3_p1_z + 2.5},
    {cup3_p1_x + 3.2, cup3_p1_y + 8.6, cup3_p1_z + 4.0},
    {cup3_p1_x - 3.2, cup3_p1_y + 8.6, cup3_p1_z + 4.0},
    {cup3_p1_x + 2.03, cup3_p1_y + 8.6, cup3_p1_z + 5.2},
    {cup3_p1_x - 2.03, cup3_p1_y + 8.6, cup3_p1_z + 5.2},
    {cup3_p1_x - 0, cup3_p1_y + 8.6, cup3_p1_z + 5.8},

    // 7 +
    {cup3_p1_x + 3.9, cup3_p1_y + 8.7, cup3_p1_z - 1.0},
    {cup3_p1_x - 3.9, cup3_p1_y + 8.7, cup3_p1_z - 1.0},
    {cup3_p1_x + 3.2, cup3_p1_y + 8.6, cup3_p1_z - 2.5},
    {cup3_p1_x - 3.2, cup3_p1_y + 8.6, cup3_p1_z - 2.5},
    {cup3_p1_x + 2.03, cup3_p1_y + 8.6, cup3_p1_z - 3.7},
    {cup3_p1_x - 2.03, cup3_p1_y + 8.6, cup3_p1_z - 3.7},
    {cup3_p1_x - 0, cup3_p1_y + 8.6, cup3_p1_z - 4.3},

    // 6
    {cup3_p1_x + 3.9, cup3_p1_y + 7.52, cup3_p1_z + 2.5},
    {cup3_p1_x - 3.9, cup3_p1_y + 7.52, cup3_p1_z + 2.5},
    {cup3_p1_x + 3.2, cup3_p1_y + 7.42, cup3_p1_z + 4.0},
    {cup3_p1_x - 3.2, cup3_p1_y + 7.42, cup3_p1_z + 4.0},
    {cup3_p1_x + 2.03, cup3_p1_y + 7.42, cup3_p1_z + 5.2},
    {cup3_p1_x - 2.03, cup3_p1_y + 7.42, cup3_p1_z + 5.2},
    {cup3_p1_x - 0, cup3_p1_y + 7.42, cup3_p1_z + 5.8},

    // 4
    {cup3_p1_x + 3.9, cup3_p1_y + 6.34, cup3_p1_z + 2.5},
    {cup3_p1_x - 3.9, cup3_p1_y + 6.34, cup3_p1_z + 2.5},
    {cup3_p1_x + 3.2, cup3_p1_y + 6.24, cup3_p1_z + 4.0},
    {cup3_p1_x - 3.2, cup3_p1_y + 6.24, cup3_p1_z + 4.0},
    {cup3_p1_x + 2.03, cup3_p1_y + 6.24, cup3_p1_z + 5.2},
    {cup3_p1_x - 2.03, cup3_p1_y + 6.24, cup3_p1_z + 5.2},
    {cup3_p1_x - 0, cup3_p1_y + 6.24, cup3_p1_z + 5.8},

    // 3
    {cup3_p1_x + 3.9, cup3_p1_y + 5.16, cup3_p1_z + 2.5},
    {cup3_p1_x - 3.9, cup3_p1_y + 5.16, cup3_p1_z + 2.5},
    {cup3_p1_x + 3.2, cup3_p1_y + 5.06, cup3_p1_z + 4.0},
    {cup3_p1_x - 3.2, cup3_p1_y + 5.06, cup3_p1_z + 4.0},
    {cup3_p1_x + 2.03, cup3_p1_y + 5.06, cup3_p1_z + 5.2},
    {cup3_p1_x - 2.03, cup3_p1_y + 5.06, cup3_p1_z + 5.2},
    {cup3_p1_x - 0, cup3_p1_y + 5.06, cup3_p1_z + 5.8},

    // 2
    {cup3_p1_x + 3.9, cup3_p1_y + 3.98, cup3_p1_z + 2.5},
    {cup3_p1_x - 3.9, cup3_p1_y + 3.98, cup3_p1_z + 2.5},
    {cup3_p1_x + 3.2, cup3_p1_y + 3.88, cup3_p1_z + 4.0},
    {cup3_p1_x - 3.2, cup3_p1_y + 3.88, cup3_p1_z + 4.0},
    {cup3_p1_x + 2.03, cup3_p1_y + 3.88, cup3_p1_z + 5.2},
    {cup3_p1_x - 2.03, cup3_p1_y + 3.88, cup3_p1_z + 5.2},
    {cup3_p1_x - 0, cup3_p1_y + 3.88, cup3_p1_z + 5.8},

    // 1
    {cup3_p1_x + 3.9, cup3_p1_y + 2.8, cup3_p1_z + 2.5},
    {cup3_p1_x - 3.9, cup3_p1_y + 2.8, cup3_p1_z + 2.5},
    {cup3_p1_x + 3.2, cup3_p1_y + 2.7, cup3_p1_z + 4.0},
    {cup3_p1_x - 3.2, cup3_p1_y + 2.7, cup3_p1_z + 4.0},
    {cup3_p1_x + 2.03, cup3_p1_y + 2.7, cup3_p1_z + 5.2},
    {cup3_p1_x - 2.03, cup3_p1_y + 2.7, cup3_p1_z + 5.2},
    {cup3_p1_x - 0, cup3_p1_y + 2.7, cup3_p1_z + 5.8},

    // 0
    {cup3_p1_x + 3.9, cup3_p1_y + 1.62, cup3_p1_z + 2.5},
    {cup3_p1_x - 3.9, cup3_p1_y + 1.62, cup3_p1_z + 2.5},
    {cup3_p1_x + 3.2, cup3_p1_y + 1.52, cup3_p1_z + 4.0},
    {cup3_p1_x - 3.2, cup3_p1_y + 1.52, cup3_p1_z + 4.0},
    {cup3_p1_x + 2.03, cup3_p1_y + 1.52, cup3_p1_z + 5.2},
    {cup3_p1_x - 2.03, cup3_p1_y + 1.52, cup3_p1_z + 5.2},
    {cup3_p1_x - 0, cup3_p1_y + 1.52, cup3_p1_z + 5.8},
};

// Player 2 Cup Positions
double cup1_p2_x = 0 * FT, cup1_p2_y = 2.55 * FT, cup1_p2_z = 3 * FT;
bool cup1_p2_score = false;
bool cup1_p2_gone = false;
double cup1_p2_frontCollision[63][3] = {

    // 9
    {cup1_p2_x - 3.9, cup1_p2_y + 9.88, cup1_p2_z - 2.5},
    {cup1_p2_x + 3.9, cup1_p2_y + 9.88, cup1_p2_z - 2.5},
    {cup1_p2_x - 3.2, cup1_p2_y + 9.78, cup1_p2_z - 4.0},
    {cup1_p2_x + 3.2, cup1_p2_y + 9.78, cup1_p2_z - 4.0},
    {cup1_p2_x - 2.03, cup1_p2_y + 9.78, cup1_p2_z - 5.2},
    {cup1_p2_x + 2.03, cup1_p2_y + 9.78, cup1_p2_z - 5.2},
    {cup1_p2_x + 0, cup1_p2_y + 9.78, cup1_p2_z - 5.8},

    // 8
    {cup1_p2_x - 3.9, cup1_p2_y + 8.7, cup1_p2_z - 2.5},
    {cup1_p2_x + 3.9, cup1_p2_y + 8.7, cup1_p2_z - 2.5},
    {cup1_p2_x - 3.2, cup1_p2_y + 8.6, cup1_p2_z - 4.0},
    {cup1_p2_x + 3.2, cup1_p2_y + 8.6, cup1_p2_z - 4.0},
    {cup1_p2_x - 2.03, cup1_p2_y + 8.6, cup1_p2_z - 5.2},
    {cup1_p2_x + 2.03, cup1_p2_y + 8.6, cup1_p2_z - 5.2},
    {cup1_p2_x + 0, cup1_p2_y + 8.6, cup1_p2_z - 5.8},

    // 7 +
    {cup1_p2_x - 3.9, cup1_p2_y + 8.7, cup1_p2_z + 1.0},
    {cup1_p2_x + 3.9, cup1_p2_y + 8.7, cup1_p2_z + 1.0},
    {cup1_p2_x - 3.2, cup1_p2_y + 8.6, cup1_p2_z + 2.5},
    {cup1_p2_x + 3.2, cup1_p2_y + 8.6, cup1_p2_z + 2.5},
    {cup1_p2_x - 2.03, cup1_p2_y + 8.6, cup1_p2_z + 3.7},
    {cup1_p2_x + 2.03, cup1_p2_y + 8.6, cup1_p2_z + 3.7},
    {cup1_p2_x + 0, cup1_p2_y + 8.6, cup1_p2_z + 4.3},

    // 6
    {cup1_p2_x - 3.9, cup1_p2_y + 7.52, cup1_p2_z - 2.5},
    {cup1_p2_x + 3.9, cup1_p2_y + 7.52, cup1_p2_z - 2.5},
    {cup1_p2_x - 3.2, cup1_p2_y + 7.42, cup1_p2_z - 4.0},
    {cup1_p2_x + 3.2, cup1_p2_y + 7.42, cup1_p2_z - 4.0},
    {cup1_p2_x - 2.03, cup1_p2_y + 7.42, cup1_p2_z - 5.2},
    {cup1_p2_x + 2.03, cup1_p2_y + 7.42, cup1_p2_z - 5.2},
    {cup1_p2_x + 0, cup1_p2_y + 7.42, cup1_p2_z - 5.8},

    // 4
    {cup1_p2_x - 3.9, cup1_p2_y + 6.34, cup1_p2_z - 2.5},
    {cup1_p2_x + 3.9, cup1_p2_y + 6.34, cup1_p2_z - 2.5},
    {cup1_p2_x - 3.2, cup1_p2_y + 6.24, cup1_p2_z - 4.0},
    {cup1_p2_x + 3.2, cup1_p2_y + 6.24, cup1_p2_z - 4.0},
    {cup1_p2_x - 2.03, cup1_p2_y + 6.24, cup1_p2_z - 5.2},
    {cup1_p2_x + 2.03, cup1_p2_y + 6.24, cup1_p2_z - 5.2},
    {cup1_p2_x + 0, cup1_p2_y + 6.24, cup1_p2_z - 5.8},

    // 3
    {cup1_p2_x - 3.9, cup1_p2_y + 5.16, cup1_p2_z - 2.5},
    {cup1_p2_x + 3.9, cup1_p2_y + 5.16, cup1_p2_z - 2.5},
    {cup1_p2_x - 3.2, cup1_p2_y + 5.06, cup1_p2_z - 4.0},
    {cup1_p2_x + 3.2, cup1_p2_y + 5.06, cup1_p2_z - 4.0},
    {cup1_p2_x - 2.03, cup1_p2_y + 5.06, cup1_p2_z - 5.2},
    {cup1_p2_x + 2.03, cup1_p2_y + 5.06, cup1_p2_z - 5.2},
    {cup1_p2_x + 0, cup1_p2_y + 5.06, cup1_p2_z - 5.8},

    // 2
    {cup1_p2_x - 3.9, cup1_p2_y + 3.98, cup1_p2_z - 2.5},
    {cup1_p2_x + 3.9, cup1_p2_y + 3.98, cup1_p2_z - 2.5},
    {cup1_p2_x - 3.2, cup1_p2_y + 3.88, cup1_p2_z - 4.0},
    {cup1_p2_x + 3.2, cup1_p2_y + 3.88, cup1_p2_z - 4.0},
    {cup1_p2_x - 2.03, cup1_p2_y + 3.88, cup1_p2_z - 5.2},
    {cup1_p2_x + 2.03, cup1_p2_y + 3.88, cup1_p2_z - 5.2},
    {cup1_p2_x + 0, cup1_p2_y + 3.88, cup1_p2_z - 5.8},

    // 1
    {cup1_p2_x - 3.9, cup1_p2_y + 2.8, cup1_p2_z - 2.5},
    {cup1_p2_x + 3.9, cup1_p2_y + 2.8, cup1_p2_z - 2.5},
    {cup1_p2_x - 3.2, cup1_p2_y + 2.7, cup1_p2_z - 4.0},
    {cup1_p2_x + 3.2, cup1_p2_y + 2.7, cup1_p2_z - 4.0},
    {cup1_p2_x - 2.03, cup1_p2_y + 2.7, cup1_p2_z - 5.2},
    {cup1_p2_x + 2.03, cup1_p2_y + 2.7, cup1_p2_z - 5.2},
    {cup1_p2_x + 0, cup1_p2_y + 2.7, cup1_p2_z - 5.8},

    // 0
    {cup1_p2_x - 3.9, cup1_p2_y + 1.62, cup1_p2_z - 2.5},
    {cup1_p2_x + 3.9, cup1_p2_y + 1.62, cup1_p2_z - 2.5},
    {cup1_p2_x - 3.2, cup1_p2_y + 1.52, cup1_p2_z - 4.0},
    {cup1_p2_x + 3.2, cup1_p2_y + 1.52, cup1_p2_z - 4.0},
    {cup1_p2_x - 2.03, cup1_p2_y + 1.52, cup1_p2_z - 5.2},
    {cup1_p2_x + 2.03, cup1_p2_y + 1.52, cup1_p2_z - 5.2},
    {cup1_p2_x + 0, cup1_p2_y + 1.52, cup1_p2_z - 5.8},
};

double cup2_p2_x = 0.4 * FT, cup2_p2_y = 2.55 * FT, cup2_p2_z = 3.6 * FT;
bool cup2_p2_score = false;
bool cup2_p2_gone = false;
double cup2_p2_frontCollision[63][3] = {

    // 9
    {cup2_p2_x - 3.9, cup2_p2_y + 9.88, cup2_p2_z - 2.5},
    {cup2_p2_x + 3.9, cup2_p2_y + 9.88, cup2_p2_z - 2.5},
    {cup2_p2_x - 3.2, cup2_p2_y + 9.78, cup2_p2_z - 4.0},
    {cup2_p2_x + 3.2, cup2_p2_y + 9.78, cup2_p2_z - 4.0},
    {cup2_p2_x - 2.03, cup2_p2_y + 9.78, cup2_p2_z - 5.2},
    {cup2_p2_x + 2.03, cup2_p2_y + 9.78, cup2_p2_z - 5.2},
    {cup2_p2_x + 0, cup2_p2_y + 9.78, cup2_p2_z - 5.8},

    // 8
    {cup2_p2_x - 3.9, cup2_p2_y + 8.7, cup2_p2_z - 2.5},
    {cup2_p2_x + 3.9, cup2_p2_y + 8.7, cup2_p2_z - 2.5},
    {cup2_p2_x - 3.2, cup2_p2_y + 8.6, cup2_p2_z - 4.0},
    {cup2_p2_x + 3.2, cup2_p2_y + 8.6, cup2_p2_z - 4.0},
    {cup2_p2_x - 2.03, cup2_p2_y + 8.6, cup2_p2_z - 5.2},
    {cup2_p2_x + 2.03, cup2_p2_y + 8.6, cup2_p2_z - 5.2},
    {cup2_p2_x + 0, cup2_p2_y + 8.6, cup2_p2_z - 5.8},

    // 7 +
    {cup2_p2_x - 3.9, cup2_p2_y + 8.7, cup2_p2_z + 1.0},
    {cup2_p2_x + 3.9, cup2_p2_y + 8.7, cup2_p2_z + 1.0},
    {cup2_p2_x - 3.2, cup2_p2_y + 8.6, cup2_p2_z + 2.5},
    {cup2_p2_x + 3.2, cup2_p2_y + 8.6, cup2_p2_z + 2.5},
    {cup2_p2_x - 2.03, cup2_p2_y + 8.6, cup2_p2_z + 3.7},
    {cup2_p2_x + 2.03, cup2_p2_y + 8.6, cup2_p2_z + 3.7},
    {cup2_p2_x + 0, cup2_p2_y + 8.6, cup2_p2_z + 4.3},

    // 6
    {cup2_p2_x - 3.9, cup2_p2_y + 7.52, cup2_p2_z - 2.5},
    {cup2_p2_x + 3.9, cup2_p2_y + 7.52, cup2_p2_z - 2.5},
    {cup2_p2_x - 3.2, cup2_p2_y + 7.42, cup2_p2_z - 4.0},
    {cup2_p2_x + 3.2, cup2_p2_y + 7.42, cup2_p2_z - 4.0},
    {cup2_p2_x - 2.03, cup2_p2_y + 7.42, cup2_p2_z - 5.2},
    {cup2_p2_x + 2.03, cup2_p2_y + 7.42, cup2_p2_z - 5.2},
    {cup2_p2_x + 0, cup2_p2_y + 7.42, cup2_p2_z - 5.8},

    // 4
    {cup2_p2_x - 3.9, cup2_p2_y + 6.34, cup2_p2_z - 2.5},
    {cup2_p2_x + 3.9, cup2_p2_y + 6.34, cup2_p2_z - 2.5},
    {cup2_p2_x - 3.2, cup2_p2_y + 6.24, cup2_p2_z - 4.0},
    {cup2_p2_x + 3.2, cup2_p2_y + 6.24, cup2_p2_z - 4.0},
    {cup2_p2_x - 2.03, cup2_p2_y + 6.24, cup2_p2_z - 5.2},
    {cup2_p2_x + 2.03, cup2_p2_y + 6.24, cup2_p2_z - 5.2},
    {cup2_p2_x + 0, cup2_p2_y + 6.24, cup2_p2_z - 5.8},

    // 3
    {cup2_p2_x - 3.9, cup2_p2_y + 5.16, cup2_p2_z - 2.5},
    {cup2_p2_x + 3.9, cup2_p2_y + 5.16, cup2_p2_z - 2.5},
    {cup2_p2_x - 3.2, cup2_p2_y + 5.06, cup2_p2_z - 4.0},
    {cup2_p2_x + 3.2, cup2_p2_y + 5.06, cup2_p2_z - 4.0},
    {cup2_p2_x - 2.03, cup2_p2_y + 5.06, cup2_p2_z - 5.2},
    {cup2_p2_x + 2.03, cup2_p2_y + 5.06, cup2_p2_z - 5.2},
    {cup2_p2_x + 0, cup2_p2_y + 5.06, cup2_p2_z - 5.8},

    // 2
    {cup2_p2_x - 3.9, cup2_p2_y + 3.98, cup2_p2_z - 2.5},
    {cup2_p2_x + 3.9, cup2_p2_y + 3.98, cup2_p2_z - 2.5},
    {cup2_p2_x - 3.2, cup2_p2_y + 3.88, cup2_p2_z - 4.0},
    {cup2_p2_x + 3.2, cup2_p2_y + 3.88, cup2_p2_z - 4.0},
    {cup2_p2_x - 2.03, cup2_p2_y + 3.88, cup2_p2_z - 5.2},
    {cup2_p2_x + 2.03, cup2_p2_y + 3.88, cup2_p2_z - 5.2},
    {cup2_p2_x + 0, cup2_p2_y + 3.88, cup2_p2_z - 5.8},

    // 1
    {cup2_p2_x - 3.9, cup2_p2_y + 2.8, cup2_p2_z - 2.5},
    {cup2_p2_x + 3.9, cup2_p2_y + 2.8, cup2_p2_z - 2.5},
    {cup2_p2_x - 3.2, cup2_p2_y + 2.7, cup2_p2_z - 4.0},
    {cup2_p2_x + 3.2, cup2_p2_y + 2.7, cup2_p2_z - 4.0},
    {cup2_p2_x - 2.03, cup2_p2_y + 2.7, cup2_p2_z - 5.2},
    {cup2_p2_x + 2.03, cup2_p2_y + 2.7, cup2_p2_z - 5.2},
    {cup2_p2_x + 0, cup2_p2_y + 2.7, cup2_p2_z - 5.8},

    // 0
    {cup2_p2_x - 3.9, cup2_p2_y + 1.62, cup2_p2_z - 2.5},
    {cup2_p2_x + 3.9, cup2_p2_y + 1.62, cup2_p2_z - 2.5},
    {cup2_p2_x - 3.2, cup2_p2_y + 1.52, cup2_p2_z - 4.0},
    {cup2_p2_x + 3.2, cup2_p2_y + 1.52, cup2_p2_z - 4.0},
    {cup2_p2_x - 2.03, cup2_p2_y + 1.52, cup2_p2_z - 5.2},
    {cup2_p2_x + 2.03, cup2_p2_y + 1.52, cup2_p2_z - 5.2},
    {cup2_p2_x + 0, cup2_p2_y + 1.52, cup2_p2_z - 5.8},
};

double cup3_p2_x = -0.4 * FT, cup3_p2_y = 2.55 * FT, cup3_p2_z = 3.6 * FT;
bool cup3_p2_score = false;
bool cup3_p2_gone = false;
double cup3_p2_frontCollision[63][3] = {

    // 9
    {cup3_p2_x - 3.9, cup3_p2_y + 9.88, cup3_p2_z - 2.5},
    {cup3_p2_x + 3.9, cup3_p2_y + 9.88, cup3_p2_z - 2.5},
    {cup3_p2_x - 3.2, cup3_p2_y + 9.78, cup3_p2_z - 4.0},
    {cup3_p2_x + 3.2, cup3_p2_y + 9.78, cup3_p2_z - 4.0},
    {cup3_p2_x - 2.03, cup3_p2_y + 9.78, cup3_p2_z - 5.2},
    {cup3_p2_x + 2.03, cup3_p2_y + 9.78, cup3_p2_z - 5.2},
    {cup3_p2_x + 0, cup3_p2_y + 9.78, cup3_p2_z - 5.8},

    // 8
    {cup3_p2_x - 3.9, cup3_p2_y + 8.7, cup3_p2_z - 2.5},
    {cup3_p2_x + 3.9, cup3_p2_y + 8.7, cup3_p2_z - 2.5},
    {cup3_p2_x - 3.2, cup3_p2_y + 8.6, cup3_p2_z - 4.0},
    {cup3_p2_x + 3.2, cup3_p2_y + 8.6, cup3_p2_z - 4.0},
    {cup3_p2_x - 2.03, cup3_p2_y + 8.6, cup3_p2_z - 5.2},
    {cup3_p2_x + 2.03, cup3_p2_y + 8.6, cup3_p2_z - 5.2},
    {cup3_p2_x + 0, cup3_p2_y + 8.6, cup3_p2_z - 5.8},

    // 7 +
    {cup3_p2_x - 3.9, cup3_p2_y + 8.7, cup3_p2_z + 1.0},
    {cup3_p2_x + 3.9, cup3_p2_y + 8.7, cup3_p2_z + 1.0},
    {cup3_p2_x - 3.2, cup3_p2_y + 8.6, cup3_p2_z + 2.5},
    {cup3_p2_x + 3.2, cup3_p2_y + 8.6, cup3_p2_z + 2.5},
    {cup3_p2_x - 2.03, cup3_p2_y + 8.6, cup3_p2_z + 3.7},
    {cup3_p2_x + 2.03, cup3_p2_y + 8.6, cup3_p2_z + 3.7},
    {cup3_p2_x + 0, cup3_p2_y + 8.6, cup3_p2_z + 4.3},

    // 6
    {cup3_p2_x - 3.9, cup3_p2_y + 7.52, cup3_p2_z - 2.5},
    {cup3_p2_x + 3.9, cup3_p2_y + 7.52, cup3_p2_z - 2.5},
    {cup3_p2_x - 3.2, cup3_p2_y + 7.42, cup3_p2_z - 4.0},
    {cup3_p2_x + 3.2, cup3_p2_y + 7.42, cup3_p2_z - 4.0},
    {cup3_p2_x - 2.03, cup3_p2_y + 7.42, cup3_p2_z - 5.2},
    {cup3_p2_x + 2.03, cup3_p2_y + 7.42, cup3_p2_z - 5.2},
    {cup3_p2_x + 0, cup3_p2_y + 7.42, cup3_p2_z - 5.8},

    // 4
    {cup3_p2_x - 3.9, cup3_p2_y + 6.34, cup3_p2_z - 2.5},
    {cup3_p2_x + 3.9, cup3_p2_y + 6.34, cup3_p2_z - 2.5},
    {cup3_p2_x - 3.2, cup3_p2_y + 6.24, cup3_p2_z - 4.0},
    {cup3_p2_x + 3.2, cup3_p2_y + 6.24, cup3_p2_z - 4.0},
    {cup3_p2_x - 2.03, cup3_p2_y + 6.24, cup3_p2_z - 5.2},
    {cup3_p2_x + 2.03, cup3_p2_y + 6.24, cup3_p2_z - 5.2},
    {cup3_p2_x + 0, cup3_p2_y + 6.24, cup3_p2_z - 5.8},

    // 3
    {cup3_p2_x - 3.9, cup3_p2_y + 5.16, cup3_p2_z - 2.5},
    {cup3_p2_x + 3.9, cup3_p2_y + 5.16, cup3_p2_z - 2.5},
    {cup3_p2_x - 3.2, cup3_p2_y + 5.06, cup3_p2_z - 4.0},
    {cup3_p2_x + 3.2, cup3_p2_y + 5.06, cup3_p2_z - 4.0},
    {cup3_p2_x - 2.03, cup3_p2_y + 5.06, cup3_p2_z - 5.2},
    {cup3_p2_x + 2.03, cup3_p2_y + 5.06, cup3_p2_z - 5.2},
    {cup3_p2_x + 0, cup3_p2_y + 5.06, cup3_p2_z - 5.8},

    // 2
    {cup3_p2_x - 3.9, cup3_p2_y + 3.98, cup3_p2_z - 2.5},
    {cup3_p2_x + 3.9, cup3_p2_y + 3.98, cup3_p2_z - 2.5},
    {cup3_p2_x - 3.2, cup3_p2_y + 3.88, cup3_p2_z - 4.0},
    {cup3_p2_x + 3.2, cup3_p2_y + 3.88, cup3_p2_z - 4.0},
    {cup3_p2_x - 2.03, cup3_p2_y + 3.88, cup3_p2_z - 5.2},
    {cup3_p2_x + 2.03, cup3_p2_y + 3.88, cup3_p2_z - 5.2},
    {cup3_p2_x + 0, cup3_p2_y + 3.88, cup3_p2_z - 5.8},

    // 1
    {cup3_p2_x - 3.9, cup3_p2_y + 2.8, cup3_p2_z - 2.5},
    {cup3_p2_x + 3.9, cup3_p2_y + 2.8, cup3_p2_z - 2.5},
    {cup3_p2_x - 3.2, cup3_p2_y + 2.7, cup3_p2_z - 4.0},
    {cup3_p2_x + 3.2, cup3_p2_y + 2.7, cup3_p2_z - 4.0},
    {cup3_p2_x - 2.03, cup3_p2_y + 2.7, cup3_p2_z - 5.2},
    {cup3_p2_x + 2.03, cup3_p2_y + 2.7, cup3_p2_z - 5.2},
    {cup3_p2_x + 0, cup3_p2_y + 2.7, cup3_p2_z - 5.8},

    // 0
    {cup3_p2_x - 3.9, cup3_p2_y + 1.62, cup3_p2_z - 2.5},
    {cup3_p2_x + 3.9, cup3_p2_y + 1.62, cup3_p2_z - 2.5},
    {cup3_p2_x - 3.2, cup3_p2_y + 1.52, cup3_p2_z - 4.0},
    {cup3_p2_x + 3.2, cup3_p2_y + 1.52, cup3_p2_z - 4.0},
    {cup3_p2_x - 2.03, cup3_p2_y + 1.52, cup3_p2_z - 5.2},
    {cup3_p2_x + 2.03, cup3_p2_y + 1.52, cup3_p2_z - 5.2},
    {cup3_p2_x + 0, cup3_p2_y + 1.52, cup3_p2_z - 5.8},
};


#endif