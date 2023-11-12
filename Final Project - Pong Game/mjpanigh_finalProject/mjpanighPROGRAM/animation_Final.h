/*******************************************
* Michael Panighetti
* 
* Animation Header
********************************************/

#ifndef ANIMATION_FINAL_H
#define ANIMATION_FINAL_H

#include "helper_Final.h"

class ANIMATION_FINAL {

public:
	static void drawBall(int shadow, bool selecting, bool dragging);
	static bool calc_animation_ballThrow(double ball_throw_rotation);
	static int calc_animation_countDown();

private:

};

#endif
