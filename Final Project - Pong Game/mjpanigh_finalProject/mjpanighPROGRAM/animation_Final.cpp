/************************************************************************
* Animation File - Includes:
*   - drawBall - draw pong ball for game.
*   - calc_animation_ballThrow - Rotation calculation.
*   - calc_animation_countDown - Countdown to next turn.
*
*************************************************************************/

#include "helper_Final.h"
#include "animation_Final.h"

///////////////// START: DRAW PONG BALL ////////////////////

void ANIMATION_FINAL::drawBall(int shadow, bool selecting, bool dragging) {

    if (selecting) {
        glDisable(GL_LIGHTING);
        glColor3f(0.0, 1.0, 0.0); // Green RGB for Selecting
        glutSolidSphere(1.5, 360, 360);
        glEnable(GL_LIGHTING);
    }
    else if (shadow) {
        glScaled(1.05, 1.05, 1.05);
        glColor4f(0.0, 0.0, 0.0, 0.7);
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glutSolidSphere(1.5, 360, 360);

        glDisable(GL_BLEND);
    }
    else {
        // Get Current Material Values To Restore Them Later
        float CurrentAmb[4],
            CurrentDiff[4],
            CurrentSpec[4],
            CurrentShine[1],
            CurrentEmission[4];

        glGetMaterialfv(GL_FRONT, GL_AMBIENT, CurrentAmb);
        glGetMaterialfv(GL_FRONT, GL_DIFFUSE, CurrentDiff);
        glGetMaterialfv(GL_FRONT, GL_SPECULAR, CurrentSpec);
        glGetMaterialfv(GL_FRONT, GL_SHININESS, CurrentShine);
        glGetMaterialfv(GL_FRONT, GL_EMISSION, CurrentEmission);

        float matBallDiff[] = { 1.0, 1.0, 1.0, 1.0 };
        float matBallAmb[] = { 1.0, 1.0, 1.0, 1.0 };
        float matBallSpec[] = { 1.0 * 0.7, 0.835 * 0.7, 0.667 * 0.7, 1.0 };
        float matBallEmiss[] = { 1.0 * 0.2, 0.835 * 0.2, 0.667 * 0.2, 1.0 };
        float matBallEmissDragging[] = { 1.0, 0.835, 0.667, 1.0 };        
        float matBallShine[] = { 100.0 };
        glMaterialfv(GL_FRONT, GL_DIFFUSE, matBallDiff);
        glMaterialfv(GL_FRONT, GL_AMBIENT, matBallAmb);
        glMaterialfv(GL_FRONT, GL_SPECULAR, matBallSpec);
        glMaterialfv(GL_FRONT, GL_SHININESS, matBallShine);

        if (itemID == 2 && dragging) {
            glMaterialfv(GL_FRONT, GL_EMISSION, matBallEmissDragging);
        } 
        else {
            glMaterialfv(GL_FRONT, GL_EMISSION, matBallEmiss);            
        }        

        Helper_Final::drawTexturedSphere(1.5, 360, 360, ballTexture);

        //Restore Old Material Settings
        glMaterialfv(GL_FRONT, GL_AMBIENT, CurrentAmb);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, CurrentDiff);
        glMaterialfv(GL_FRONT, GL_SPECULAR, CurrentSpec);
        glMaterialfv(GL_FRONT, GL_SHININESS, CurrentShine);
        glMaterialfv(GL_FRONT, GL_EMISSION, CurrentEmission);
    }
};

///////////////// START: BALL THROW ////////////////////

bool ANIMATION_FINAL::calc_animation_ballThrow(double ball_throw_rotation) {

    if (ball_throw_rotation != 70 && throw_ball == true && turn == 2) {

        ball_throw_rotation += 70/ball_throw_rotation_divider;

        Helper_Final::change_ball_throw_rotation(ball_throw_rotation);

        glutPostRedisplay();
        return false;
    }
    else if (ball_throw_rotation != -70 && throw_ball == true && turn == 1) {

        ball_throw_rotation -= 70 / ball_throw_rotation_divider;

        Helper_Final::change_ball_throw_rotation(ball_throw_rotation);

        glutPostRedisplay();
        return false;
    }
    else {
        glutPostRedisplay();
        return true;
    }
}

///////////////// START: COUNT DOWN ////////////////////

int ANIMATION_FINAL::calc_animation_countDown() {

    /*
    #ifdef __APPLE__
    sleep(1);
    #else
    Sleep(1000);
    #endif
    */

    --countDown;

    glutPostRedisplay();
    return countDown;    
}

