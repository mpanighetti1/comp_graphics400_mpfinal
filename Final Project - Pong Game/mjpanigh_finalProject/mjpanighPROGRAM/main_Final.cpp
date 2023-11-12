/*********************************************************
*
* Main file for Final Project
*
* Official Name:  Michael Panighetti
*
* E-mail:  mjpanigh@syr.edu
*
* Assignment:  Final - Water Pong
*
* Environment/Compiler:  Visual Studio Community 2022
*
* Date submitted:  April 30th, 2023
*
* References: 
*   - Adapting class example programs – i.e. External Texture Loading, 
*     Parameterized swept surfaces, Color Picking, etc. Some used again from last project.
*   - Difference between Sleep() and sleep() from Windows to 
*     Apple found at: https://www.geeksforgeeks.org/sleep-function-in-c/ (Line 805)
*
* 
* Texture Credits:
*   - 2014 Rich Barnes/Getty Images - Jim Boeheim Image
*   - Denis Tangney Jr/Getty Images - Photo of Crouse College Building
*   - Blakeway Worldwide Panoramas, Inc. - Photo of Duke vs. SU Basketball
*   - Well Woven 2023 - wellwoven.com - Rug Print
*   - Adobe Stock Images - Ursula Page - stock.adobe.com - Wall Chair Rail
*   - Adobe Stock Images - Viktoriia - stock.adobe.com - Bamboo Wood Tabletop
*   - Syracuse University Logos - syracuse.edu
*   - Sports Illustrate - Carmelo Anthony Cover 2003 - Getty Images
* 
* Interactions:
*   - The goal of the game is to throw the ball into all of your 
*       cups before your opponent does.
*   - Press 'R' to Start The Game.
*   - Hold Left-Click over ball to drag into desired position.
*   - Higher position = longer Shot.
*   - Lower position = shorter Shot.
*   - Press 'Space Bar' to throw the ball. 
*   - Scoreboard is at the top of the screen.
*   - There will be a mark next to the player whose turn it is at top of screen.
*   - Also, cup color will signify whose turn it is.
*   - Red = Player 1
*   - Blue = Player 2
* 
**********************************************************/

#include "helper_Final.h"
#include "stillobjects_Final.h"
#include "animation_Final.h"
#include "cup_Globals.h"

// Window Settings Globals
float winSize_X = 800;
float winSize_Y = 600;
static long font = (long)GLUT_BITMAP_TIMES_ROMAN_24; // Font selection.

// Game Globals
//Default Viewer, But This Changes To Player1 and Player2
int turn = 3;
int player1_score = 0;
int player2_score = 0;
bool player_set = false;
bool ball_missed = false;
bool first_game = true;
bool score = false;
bool switching = false;
bool game_started = false;
int countDown = 0;
int last_turn = 0;
int last_chance = 1;


// Color Picking
int itemID = 0;
bool selecting = false;
bool dragging = false;
float click_x, click_y;
float prevMouseX, prevMouseY;

// Ball Movement Globals
double ball_x, ball_y, ball_z;
bool throw_ball = false;
bool ball_thrown = false;
double ball_throw_rotation_divider = 35;
double ball_world_x = 0.0;
double ball_world_y = 0.0;
double ball_world_z = 0.0;

// Camera Globals
static float camera_angle_h = 270.0; // Horizontal angle
static float camera_angle_v = -15.0; // Vertical angle
// Used in calculating eye_x & eye_z
static float camera_x = -81.0, camera_z = 0;
static float camera_height = 6;

//Player 1 Camera Globals
static float player1_camera_angle_h = 360.0; // Horizontal angle
static float player1_camera_angle_v = -15.0; // Vertical angle
// Used in calculating eye_x & eye_z
static float player1_camera_x = 0, player1_camera_z = 99;
static float player1_camera_height = 6;

//Player 2 Camera Globals
static float player2_camera_angle_h = 180.0; // Horizontal angle
static float player2_camera_angle_v = -15.0; // Vertical angle
// Used in calculating eye_x & eye_z
static float player2_camera_x = 0, player2_camera_z = -99;
static float player2_camera_height = 6;

//Viewer Camera Globals
static float viewer_camera_angle_h = 270.0; // Horizontal angle
static float viewer_camera_angle_v = -20.0; // Vertical angle
// Used in calculating eye_x & eye_z
static float viewer_camera_x = -81.0, viewer_camera_z = 0;
static float viewer_camera_height = 6;

// Light Positions
float spot_lightPos[] = { 0 * FT, 8.0 * FT, 0 * FT, 1.0 };
float ambient_lightPos[] = { 0 * FT, 8.0 * FT, 0 * FT, 1.0 };
float green_lightPos[] = { 0 * FT, 0 * FT, 0 * FT, 1.0 };
float red_lightPos[] = { 0 * FT, 0 * FT, 0 * FT, 1.0 };

// LookAt Variables
static float eye_x;
static float eye_y;
static float eye_z;
static float lookAt_x;
static float lookAt_y;
static float lookAt_z;
static float up_x;
static float up_y;
static float up_z;

// Rotation Function For Coordinates Instead Of Matrix
void applyRotation(double angle, double x, double y, double z, 
    double& px, double& py, double& pz) {

    // Define the origin of rotation
    double originX = 0;
    double originY = -28.8;
    double originZ = turn == 2 ? -36 : 36;

    // Translate the object to the origin
    px -= originX;
    py -= originY;
    pz -= originZ;

    // Normalize the rotation axis
    double length = sqrt(x * x + y * y + z * z);
    x /= length;
    y /= length;
    z /= length;

    // Convert the angle to radians
    angle = angle * PI / 180.0;

    // Compute the sine and cosine of the angle
    double c = cos(angle);
    double s = sin(angle);

    // Compute the rotation matrix elements
    double r00 = x * x * (1 - c) + c;
    double r01 = x * y * (1 - c) - z * s;
    double r02 = x * z * (1 - c) + y * s;
    double r10 = y * x * (1 - c) + z * s;
    double r11 = y * y * (1 - c) + c;
    double r12 = y * z * (1 - c) - x * s;
    double r20 = z * x * (1 - c) - y * s;
    double r21 = z * y * (1 - c) + x * s;
    double r22 = z * z * (1 - c) + c;

    // Apply the rotation to the point (px, py, pz)
    double new_x = r00 * px + r01 * py + r02 * pz;
    double new_y = r10 * px + r11 * py + r12 * pz;
    double new_z = r20 * px + r21 * py + r22 * pz;

    // Translate the object back to its original position
    px = new_x + originX;
    py = new_y + originY;
    pz = new_z + originZ;
}

// Checking Cup Collision Points For Ball Score
void ballScore_Collision(double x, double y, double z)
{    
    if (turn == 2) {

        if (!cup1_p2_gone && Helper_Final::checkSpheresIntersection(x, y, z, 2.0,
            cup1_p2_x, cup1_p2_y + 8, cup1_p2_z + 0.5, 1.0)) {
            cup1_p2_score = true;
        }
        else if (!cup2_p2_gone && Helper_Final::checkSpheresIntersection(x, y, z, 2.0,
            cup2_p2_x, cup2_p2_y + 8, cup2_p2_z + 0.5, 1.0)) {
            cup2_p2_score = true;
        }
        else if (!cup3_p2_gone && Helper_Final::checkSpheresIntersection(x, y, z, 2.0,
            cup3_p2_x, cup3_p2_y + 8, cup3_p2_z + 0.5, 1.0)) {
            cup3_p2_score = true;
        }
        
        if (!score) {
            if (cup3_p2_score || cup2_p2_score || cup1_p2_score) {
                player2_score += 1;
                score = true;
            }
        }
    }
    else if (turn == 1) {

        if (!cup1_p1_gone && Helper_Final::checkSpheresIntersection(x, y, z, 2.0,
            cup1_p1_x, cup1_p1_y + 8, cup1_p1_z - 0.5, 1.0)) {
            cup1_p1_score = true;
        }
        else if (!cup2_p1_gone && Helper_Final::checkSpheresIntersection(x, y, z, 2.0,
            cup2_p1_x, cup2_p1_y + 8, cup2_p1_z - 0.5, 1.0)) {
            cup2_p1_score = true;
        }
        else if (!cup3_p1_gone && Helper_Final::checkSpheresIntersection(x, y, z, 2.0,
            cup3_p1_x, cup3_p1_y + 8, cup3_p1_z - 0.5, 1.0)) {
            cup3_p1_score = true;
        }

        if (!score) {
            if (cup3_p1_score || cup2_p1_score || cup1_p1_score) {
                player1_score += 1;
                score = true;
            }
        }
    }
}

// Checking Cup Collision Points Array For Ball Miss
void cupBounce_Collision(double x, double y, double z)
{
    if (turn == 2) {
        for (int i = 0; i < 63; ++i) {
            if (!cup1_p2_gone && Helper_Final::checkSpheresIntersection(x, y, z, 2.0,
                cup1_p2_frontCollision[i][0],
                cup1_p2_frontCollision[i][1],
                cup1_p2_frontCollision[i][2],
                0.5)) {
                throw_ball = false;
                ball_missed = true;
            }
            else if (!cup2_p2_gone && Helper_Final::checkSpheresIntersection(x, y, z, 2.0,
                cup2_p2_frontCollision[i][0],
                cup2_p2_frontCollision[i][1],
                cup2_p2_frontCollision[i][2],
                0.5)) {
                throw_ball = false;
                ball_missed = true;
            }
            else if (!cup3_p2_gone && Helper_Final::checkSpheresIntersection(x, y, z, 2.0,
                cup3_p2_frontCollision[i][0],
                cup3_p2_frontCollision[i][1],
                cup3_p2_frontCollision[i][2],
                0.5)) {
                throw_ball = false;
                ball_missed = true;
            }
            if (ball_missed) break;
        }
    }
    else if (turn == 1) {
        for (int i = 0; i < 63; ++i) {
            if (!cup1_p1_gone && Helper_Final::checkSpheresIntersection(x, y, z, 2.0,
                cup1_p1_frontCollision[i][0],
                cup1_p1_frontCollision[i][1],
                cup1_p1_frontCollision[i][2],
                0.5)) {
                throw_ball = false;
                ball_missed = true;
            }
            else if (!cup2_p1_gone && Helper_Final::checkSpheresIntersection(x, y, z, 2.0,
                cup2_p1_frontCollision[i][0],
                cup2_p1_frontCollision[i][1],
                cup2_p1_frontCollision[i][2],
                0.5)) {
                throw_ball = false;
                ball_missed = true;
            }
            else if (!cup3_p1_gone && Helper_Final::checkSpheresIntersection(x, y, z, 2.0,
                cup3_p1_frontCollision[i][0],
                cup3_p1_frontCollision[i][1],
                cup3_p1_frontCollision[i][2],
                0.5)) {
                throw_ball = false;
                ball_missed = true;
            }
            if (ball_missed) break;
        }
    }
}

// On-Screen Text For Player Scores
void scoreBoard() {

    std::string str_score_p1 = "Player 1:  " + std::to_string(player1_score) + " / 3                  "
        + "Player 2:  " + std::to_string(player2_score) + " / 3";
    const char* charStr_score_p1 = str_score_p1.c_str();    

    Helper_Final::renderScaledText(winSize_X, winSize_Y,
        (winSize_X / 2) - 210, winSize_Y - (winSize_Y / 20), 1, (void*)font,
        charStr_score_p1);
}

// Main setup
void main_setup(void)
{
    //For Swept draw_solo_cup Texture
    glEnableClientState(GL_VERTEX_ARRAY);
    glClearColor(0.0, 0.0, 0.0, 0.0); // Black

    // Load external texture and generate and load procedural texture.
    Helper_Final::loadExternalTextures();
    // Specify how texture values combine with current surface color values.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // Enable Depth Testing By Default.
    glEnable(GL_DEPTH_TEST);
    // Enable Lighting By Default
    glEnable(GL_LIGHTING);
    // Enable Normalizing By Default
    glEnable(GL_NORMALIZE);  
    // Enable Smooth Shading By Default
    glShadeModel(GL_SMOOTH);

    // Middle Spot Light = LIGHT0
    glEnable(GL_LIGHT0);
    float spot_lightDiff[] = { 1.0 * 0.7, 0.835 * 0.7, 0.667 * 0.7, 1.0 };
    float spot_lightSpec[] = { 1.0 * 0.7, 0.835 * 0.7, 0.667 * 0.7, 1.0 };
    float spot_lightAmb[] = { 0.1, 0.1, 0.1, 1.0 };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, spot_lightDiff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spot_lightSpec);
    glLightfv(GL_LIGHT0, GL_AMBIENT, spot_lightAmb);

    // Middle Ambient Light = LIGHT1
    glEnable(GL_LIGHT1);
    float ambient_lightDiff[] = { 1.0 * 2, 0.835 * 2, 0.667 * 2, 1.0 };
    float ambient_lightSpec[] = { 1.0 * 2, 0.835 * 2, 0.667 * 2, 1.0 };
    float ambient_lightAmb[] = { 0.1, 0.1, 0.1, 1.0 };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, ambient_lightDiff);
    glLightfv(GL_LIGHT1, GL_SPECULAR, ambient_lightSpec);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_lightAmb);

    // Green Score Light = LIGHT2
    float green_lightDiff[] = { 0.0, 1.0 * 5, 0.0, 1.0 };
    float green_lightSpec[] = { 1.0 * 5, 1.0 * 5, 1.0 * 5, 1.0 };
    float green_lightAmb[] = { 0.0, 1.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT2, GL_DIFFUSE, green_lightDiff);
    glLightfv(GL_LIGHT2, GL_SPECULAR, green_lightSpec);
    glLightfv(GL_LIGHT2, GL_AMBIENT, green_lightAmb);
    
    // Red Miss Light = LIGHT3
    float red_lightDiff[] = { 1.0 * 5, 0.0, 0.0, 1.0 };
    float red_lightSpec[] = { 1.0 * 5, 1.0 * 5, 1.0 * 5, 1.0 };
    float red_lightAmb[] = { 1.0, 0.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT3, GL_DIFFUSE, red_lightDiff);
    glLightfv(GL_LIGHT3, GL_SPECULAR, red_lightSpec);
    glLightfv(GL_LIGHT3, GL_AMBIENT, red_lightAmb);

    // Enable local viewpoint
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1); 

    // Cull back faces.
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

}

// Draw Function
void display(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Initial Game Setup
    if (player_set == false) {

        // Seed the random number generator with the current time 
        srand(time(0));

        // Generate a random number between 0 and RAND_MAX
        float rand_ball_x_start = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        float rand_ball_y_start = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

        // Scale and shift the number to the range [-1, 1]
        rand_ball_x_start = 2.0 * rand_ball_x_start - 1.0;

        // Scale and shift the number to the range [5.0, 6.2]
        rand_ball_y_start = 5.0 + rand_ball_y_start * 1.2;

        if (turn == 1) {
            camera_angle_h = player1_camera_angle_h;
            camera_angle_v = player1_camera_angle_v;
            camera_x = player1_camera_x;
            camera_z = player1_camera_z;
            camera_height = player1_camera_height;            

            // Where The Ball Starts
            ball_x = rand_ball_x_start * FT;
            ball_y = rand_ball_y_start * FT;
            ball_z = 5.0 * FT;

            ball_world_x = ball_x;
            ball_world_y = ball_y;
            ball_world_z = ball_z;

            first_game = false;
        }
        else if (turn == 2) {       
            camera_angle_h = player2_camera_angle_h;
            camera_angle_v = player2_camera_angle_v;
            camera_x = player2_camera_x;
            camera_z = player2_camera_z;
            camera_height = player2_camera_height;

            //Where The Ball Starts
            ball_x = rand_ball_x_start * FT;
            ball_y = rand_ball_y_start * FT;
            ball_z = -5.0 * FT;

            ball_world_x = ball_x;
            ball_world_y = ball_y;
            ball_world_z = ball_z;

        }    
        else if (turn == 3) {
            camera_angle_h = viewer_camera_angle_h;
            camera_angle_v = viewer_camera_angle_v;
            camera_x = viewer_camera_x;
            camera_z = viewer_camera_z;
            camera_height = viewer_camera_height;

            // Remove Scored Cup
            if (cup1_p2_score) cup1_p2_gone = true;
            if (cup2_p2_score) cup2_p2_gone = true;
            if (cup3_p2_score) cup3_p2_gone = true;
            if (cup1_p1_score) cup1_p1_gone = true;
            if (cup2_p1_score) cup2_p1_gone = true;
            if (cup3_p1_score) cup3_p1_gone = true;

            cup1_p2_score = false;
            cup2_p2_score = false;
            cup3_p2_score = false;
            cup1_p1_score = false;
            cup2_p1_score = false;
            cup3_p1_score = false;
            throw_ball = false;
            score = false;
            ball_throw_rotation = 0;            

            if (ball_thrown && player1_score == 3 && player2_score == 3) {
                ball_thrown = false;
                ball_missed = false;

                std::string str = "Tie! Press 'R' to Play Again.";
                const char* q = str.c_str();
                Helper_Final::renderScaledText(winSize_X, winSize_Y,
                    (winSize_X / 2) - 130, winSize_Y / 2 + 100, 1, (void*)font,
                    q);

                game_started = false;
            }
            else if (last_turn == 1 && player2_score == 3 && last_chance == 0) {
                ball_thrown = false;
                ball_missed = false;
                
                std::string str = "Player 2 Wins! Press 'R' to Play Again.";
                const char* q = str.c_str();
                Helper_Final::renderScaledText(winSize_X, winSize_Y,
                    (winSize_X / 2) - 130, winSize_Y / 2 + 100, 1, (void*)font,
                    q);

                game_started = false;
            }
            else if (last_turn == 2 && player1_score == 3 && last_chance == 0) {
                ball_thrown = false;
                ball_missed = false;

                std::string str = "Player 1 Wins! Press 'R' to Play Again.";
                const char* q = str.c_str();
                Helper_Final::renderScaledText(winSize_X, winSize_Y,
                    (winSize_X / 2) - 130, winSize_Y / 2 + 100, 1, (void*)font,
                    q);

                game_started = false;
            }
            else if (ball_thrown) {
                ball_thrown = false;
                ball_missed = false;
                switching = true;
                countDown = 5;
            }

            //Where The Ball Starts
            ball_x = 0 * FT;
            ball_y = 20 * FT;
            ball_z = 0 * FT;

            ball_world_x = ball_x;
            ball_world_y = ball_y;
            ball_world_z = ball_z;            
        }
        player_set = true;
    }

    // Camera Declarations
    eye_x = camera_x - 10 * sin((PI / 180.0) * camera_angle_h) * cos((PI / 180.0) * camera_angle_v);
    eye_y = (camera_height * FT) + 10 * sin((PI / 180.0) * camera_angle_v);
    eye_z = camera_z - 10 * cos((PI / 180.0) * camera_angle_h) * cos((PI / 180.0) * camera_angle_v);
    lookAt_x = camera_x - 11 * sin((PI / 180.0) * camera_angle_h) * cos((PI / 180.0) * camera_angle_v);
    lookAt_y = (camera_height * FT) + 11 * sin((PI / 180.0) * camera_angle_v);
    lookAt_z = camera_z - 11 * cos((PI / 180.0) * camera_angle_h) * cos((PI / 180.0) * camera_angle_v);
    up_x = 0.0;
    up_y = 1.0;
    up_z = 0.0;
     
    // Perspective
    gluLookAt(eye_x, eye_y, eye_z,
        lookAt_x, lookAt_y, lookAt_z,
        up_x, up_y, up_z);

    /* Light Positioning */
    glDisable(GL_LIGHTING);

    // Middle Spot Light = Light0
    float spotDirection[] = { 0.0, -1.0, 0.0 };
    float spotAngle = 80.0; // Spotlight cone half-angle.
    float spotExponent = 50; // Spotlight exponent = attenuation.
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
    glLightfv(GL_LIGHT0, GL_POSITION, spot_lightPos);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotAngle);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);

    // Middle Ambient Light = Light1
    float ambientDirection[] = { 0.0, -1.0, 0.0 };
    float ambientAngle = 80.0; // Spotlight cone half-angle.
    float ambientExponent = 3; // Spotlight exponent = attenuation.
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, ambientDirection);
    glLightfv(GL_LIGHT1, GL_POSITION, ambient_lightPos);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, ambientAngle);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, ambientExponent);

    // Green Score Light = Light2
    float greenDirection[] = { 0.0, 1.0, 0.0 };
    float greenAngle = 80.0; // Spotlight cone half-angle.
    float greenExponent = 3; // Spotlight exponent = attenuation.
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, greenDirection);
    glLightfv(GL_LIGHT2, GL_POSITION, green_lightPos);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, greenAngle);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, greenExponent);

    // Red Score Light = Light3
    float redDirection[] = { 0.0, 1.0, 0.0 };
    float redAngle = 80.0; // Spotlight cone half-angle.
    float redExponent = 3; // Spotlight exponent = attenuation.
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, redDirection);
    glLightfv(GL_LIGHT3, GL_POSITION, red_lightPos);
    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, redAngle);
    glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, redExponent);

    glEnable(GL_LIGHTING);
    /* End Light Positioning */

    STILLOBJECTS_FINAL::drawStructure();

    /*Shadows Table*/glDisable(GL_LIGHTING);
    /*Shadows Table*/glDisable(GL_DEPTH_TEST);
    /*A*/glPushMatrix();
    glScalef(1.0, 0.0, 1.0);
    STILLOBJECTS_FINAL::drawTable(1);
    /*A*/glPopMatrix();
    /*Shadows Table*/glEnable(GL_DEPTH_TEST);
    /*Shadows Table*/glEnable(GL_LIGHTING);

    STILLOBJECTS_FINAL::drawTable(0);

    if (turn == 3 && game_started == false && first_game) {
        std::string str = "Press 'R' to Start Game.";
        const char* q = str.c_str();
        Helper_Final::renderScaledText(winSize_X, winSize_Y,
            (winSize_X / 2) - 130, winSize_Y / 2, 1, (void*)font,
            q);
    }
    else if ((turn == 1 || turn == 2) && throw_ball == false) {
        std::string str = "Press 'Space Bar' to Throw Ball.";
        const char* q = str.c_str();
        Helper_Final::renderScaledText(winSize_X, winSize_Y,
            (winSize_X / 2) - 150, winSize_Y - (winSize_Y * 0.90), 1, (void*)font,
            q);
    }

    ///////////////// START: DRAW CUPS ////////////////////

    ballScore_Collision(ball_world_x, ball_world_y, ball_world_z);

    if (!score) {
         cupBounce_Collision(ball_world_x, ball_world_y, ball_world_z);
    }

    if (!score && (ball_throw_rotation == 70 || ball_throw_rotation == -70)) {
        ball_missed = true;
    }

    if (turn == 2) {
        if (!cup1_p2_gone) {
            // Cup 1 - Player 2 - Front Cup
            glPushMatrix();
            glTranslated(cup1_p2_x, cup1_p2_y, cup1_p2_z);
            glScaled(0.6, 0.6, 0.6);
            STILLOBJECTS_FINAL::draw_solo_cup(cup1_p2_score, ball_missed);
            glPopMatrix();
        }
        if (!cup2_p2_gone) {
            // Cup 2 - Player 2 - Front Cup
            glPushMatrix();
            glTranslated(cup2_p2_x, cup2_p2_y, cup2_p2_z);
            glScaled(0.6, 0.6, 0.6);
            STILLOBJECTS_FINAL::draw_solo_cup(cup2_p2_score, ball_missed);
            glPopMatrix();
        }
        if (!cup3_p2_gone) {
            // Cup 3 - Player 2 - Front Cup
            glPushMatrix();
            glTranslated(cup3_p2_x, cup3_p2_y, cup3_p2_z);
            glScaled(0.6, 0.6, 0.6);
            STILLOBJECTS_FINAL::draw_solo_cup(cup3_p2_score, ball_missed);
            glPopMatrix();
        }
    }

    if (turn == 1) {
        if (!cup1_p1_gone) {
            // Cup 1 - Player 1 - Front Cup
            glPushMatrix();
            glTranslated(cup1_p1_x, cup1_p1_y, cup1_p1_z);
            glScaled(0.6, 0.6, 0.6);
            STILLOBJECTS_FINAL::draw_solo_cup(cup1_p1_score, ball_missed);
            glPopMatrix();
        }
        if (!cup2_p1_gone) {
            // Cup 2 - Player 1 - Front Cup
            glPushMatrix();
            glTranslated(cup2_p1_x, cup2_p1_y, cup2_p1_z);
            glScaled(0.6, 0.6, 0.6);
            STILLOBJECTS_FINAL::draw_solo_cup(cup2_p1_score, ball_missed);
            glPopMatrix();
        }
        if (!cup3_p1_gone) {
            // Cup 3 - Player 1 - Front Cup
            glPushMatrix();
            glTranslated(cup3_p1_x, cup3_p1_y, cup3_p1_z);
            glScaled(0.6, 0.6, 0.6);
            STILLOBJECTS_FINAL::draw_solo_cup(cup3_p1_score, ball_missed);
            glPopMatrix();
        }
    }

    if (turn == 3) {

        turn = 1;
        if (!cup1_p1_gone) {
            // Cup 1 - Player 1 - Front Cup
            glPushMatrix();
            glTranslated(cup1_p1_x, cup1_p1_y, cup1_p1_z);
            glScaled(0.6, 0.6, 0.6);
            STILLOBJECTS_FINAL::draw_solo_cup(cup1_p1_score, ball_missed);
            glPopMatrix();
        }
        if (!cup2_p1_gone) {
            // Cup 2 - Player 1 - Front Cup
            glPushMatrix();
            glTranslated(cup2_p1_x, cup2_p1_y, cup2_p1_z);
            glScaled(0.6, 0.6, 0.6);
            STILLOBJECTS_FINAL::draw_solo_cup(cup2_p1_score, ball_missed);
            glPopMatrix();
        }
        if (!cup3_p1_gone) {
            // Cup 3 - Player 1 - Front Cup
            glPushMatrix();
            glTranslated(cup3_p1_x, cup3_p1_y, cup3_p1_z);
            glScaled(0.6, 0.6, 0.6);
            STILLOBJECTS_FINAL::draw_solo_cup(cup3_p1_score, ball_missed);
            glPopMatrix();
        }

        turn = 2;
        if (!cup1_p2_gone) {
            // Cup 1 - Player 2 - Front Cup
            glPushMatrix();
            glTranslated(cup1_p2_x, cup1_p2_y, cup1_p2_z);
            glScaled(0.6, 0.6, 0.6);
            STILLOBJECTS_FINAL::draw_solo_cup(cup1_p2_score, ball_missed);
            glPopMatrix();
        }
        if (!cup2_p2_gone) {
            // Cup 2 - Player 2 - Front Cup
            glPushMatrix();
            glTranslated(cup2_p2_x, cup2_p2_y, cup2_p2_z);
            glScaled(0.6, 0.6, 0.6);
            STILLOBJECTS_FINAL::draw_solo_cup(cup2_p2_score, ball_missed);
            glPopMatrix();
        }
        if (!cup3_p2_gone) {
            // Cup 3 - Player 2 - Front Cup
            glPushMatrix();
            glTranslated(cup3_p2_x, cup3_p2_y, cup3_p2_z);
            glScaled(0.6, 0.6, 0.6);
            STILLOBJECTS_FINAL::draw_solo_cup(cup3_p2_score, ball_missed);
            glPopMatrix();
        }

        turn = 3;
    }

    ///////////////// START: DRAW PONG BALL ////////////////////

    /*A*/glPushMatrix();   

    if (ball_missed) {
        ball_x = ball_world_x;
        ball_y = ball_world_y;
        ball_z = ball_world_z;

        // Ball Starting Position
        glTranslated(ball_x, ball_y, ball_z);
    }
    else {
        // Ball Starting Position
        glTranslated(ball_x, ball_y, ball_z);

        // Apply translation To World Coordinates
        ball_world_x = ball_x;
        ball_world_y = ball_y;
        ball_world_z = ball_z;

        // Create Rotation Pivot
        if (turn == 1) {
            glTranslated(0, -8 * FT, -2 * FT);
        }
        else if (turn == 2) {
            glTranslated(0, -8 * FT, 2 * FT);
        }
        // Apply rotation
        glRotated(ball_throw_rotation, 1, 0, 0);
        applyRotation(ball_throw_rotation, 1, 0, 0,
            ball_world_x, ball_world_y, ball_world_z);

        if (turn == 1) {
            glTranslated(0, 8 * FT, 2 * FT);
        }
        else if (turn == 2) {
            glTranslated(0, 8 * FT, -2 * FT);
        }       
    }

    if (turn == 1) {
        glRotated(270.0, 1.0, 0.0, 0.0);
        glRotated(180.0, 0.0, 1.0, 0.0);
    }
    else if (turn == 2) {
        glRotated(90.0, 1.0, 0.0, 0.0);
        glRotated(180.0, 0.0, 1.0, 0.0);
    }

    if (!score) {
        /*Shadows Table*/glDisable(GL_LIGHTING);
        /*Shadows Table*/glDisable(GL_DEPTH_TEST);
        /*A*/glPushMatrix();

        float ball_shadow = 0;

        if (turn == 1) {
            ball_shadow = -1 * ((2.5 * FT) - ball_world_y);
        }
        else if (turn == 2) {
            ball_shadow = 1 * ((2.5 * FT) - ball_world_y);
        }

        glTranslated(0.0, 0.0, ball_shadow);
        glScalef(1.0, 0.1, 1.0);
        ANIMATION_FINAL::drawBall(1, selecting, dragging);
        /*A*/glPopMatrix();
        /*Shadows Table*/glEnable(GL_DEPTH_TEST);
        /*Shadows Table*/glEnable(GL_LIGHTING);
    }
    
    ANIMATION_FINAL::drawBall(0, selecting, dragging);    

    /*A*/glPopMatrix();  

    ///////////////// START: HANGING LIGHT ////////////////////

    STILLOBJECTS_FINAL::drawHangingLight();

    ///////////////// START: GAME LOGIC FLOW ////////////////////

    scoreBoard();

    if (ball_thrown) {
        last_turn = turn;
        player_set = false;
        turn = 3;
        #ifdef __APPLE__
        sleep(1.5);
        #else
        Sleep(1500);
        #endif
        glutPostRedisplay();
    }

    if (switching == true && countDown != 0) {

        if (player1_score == 3 && last_chance == 1) {
            std::string str = "Player 2's Last Chance Starts In... " +
                std::to_string(countDown);
            const char* q = str.c_str();
            Helper_Final::renderScaledText(winSize_X, winSize_Y,
                (winSize_X / 2) - 150, winSize_Y / 2 + 100, 1, (void*)font,
                q);
        }
        else if (player2_score == 3 && last_chance == 1) {
            std::string str = "Player 1's Last Chance Starts In... " +
                std::to_string(countDown);
            const char* q = str.c_str();
            Helper_Final::renderScaledText(winSize_X, winSize_Y,
                (winSize_X / 2) - 150, winSize_Y / 2 + 100, 1, (void*)font,
                q);
        }
        else if (last_turn == 1) {
            std::string str = "Player 2's Turn Starts In... " +
                std::to_string(countDown);
            const char* q = str.c_str();
            Helper_Final::renderScaledText(winSize_X, winSize_Y,
                (winSize_X / 2) - 140, winSize_Y / 2 + 100, 1, (void*)font,
                q);
        }
        else if (last_turn == 2) {
            std::string str = "Player 1's Turn Starts In... " +
                std::to_string(countDown);
            const char* q = str.c_str();
            Helper_Final::renderScaledText(winSize_X, winSize_Y,
                (winSize_X / 2) - 140, winSize_Y / 2 + 100, 1, (void*)font,
                q);
        }
        
    }
    else if (switching == true) {

        switching = false;
        player_set = false;

        if (last_turn == 1 && player2_score == 3 && last_chance == 1) turn = 1;
        else if (last_turn == 2 && player1_score == 3 && last_chance == 1) turn = 2;
        else if (last_turn == 1) turn = 2;
        else if (last_turn == 2) turn = 1;
        glutPostRedisplay();
    }  

    if (ball_missed) {
        ball_thrown = true;

        if (last_turn == 1 && player2_score == 3 && last_chance == 1)
            last_chance = 0;
        else if (last_turn == 2 && player1_score == 3 && last_chance == 1) {
            last_chance = 0;
        }
        glutPostRedisplay();
    }
}

// Color Picking Step
void drawScene(void)
{
    //draw everything with special coloring for selecting
    //but don't display on computer screen.
    if (selecting)
    {
        display();
        itemID = Helper_Final::getID(click_x, click_y);
        selecting = false;               
    }
    //draw everything 
    else
    {
        display();
        glutSwapBuffers();
    }
}

// Timer function callback for throwing ball
void animation_ballThrow(int someValue){
    if (throw_ball == true && ball_thrown == false && ball_missed == false) {
        ball_thrown = ANIMATION_FINAL::calc_animation_ballThrow(ball_throw_rotation);        
    }
    glutTimerFunc(1, animation_ballThrow, 1);
}

// Timer function callback for countDown
void animation_countDown(int someValue) {

    if (switching == true) {        
        countDown = ANIMATION_FINAL::calc_animation_countDown();        
    }   
    glutTimerFunc(1000, animation_countDown, 1);
}

// OpenGL window reshape routine.
void main_resize(int w, int h)
{     
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)w / (float)h;
    float fov = 60.0;
    gluPerspective(fov, aspect, 0.1, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    winSize_Y = h;
    winSize_X = w;    
}

// Mouse control function
void main_MouseControl(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN && button == GLUT_LEFT)
    {      
        selecting = true;
        click_x = x;
        click_y = winSize_Y - y;
        prevMouseX = x;
        prevMouseY = y;
        dragging = true;
        itemID = Helper_Final::getID(click_x, click_y);
        glutPostRedisplay();
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        selecting = false;
        dragging = false;
        glutPostRedisplay();
    }   
}

// Moving Ball When Dragging Enabled
void moving_objects(int x, int y) {

    double deltaX = (prevMouseX - x) * 0.0242;
    double deltaY = (prevMouseY - y) * 0.0268;

    if (itemID == 2 && dragging) {
        double adjustedDeltaX = deltaX;
        double adjustedDeltaY = deltaY;

        // Account for coordinate transformation based on the current viewpoint
        if (turn == 1) {
            adjustedDeltaX = -deltaX;
            adjustedDeltaY = deltaY;
        }
        else if (turn == 2) {
            adjustedDeltaX = deltaX;
            adjustedDeltaY = deltaY;
        }

        if (ball_x <= (-1 * FT)) { // Left Side Cut-Off
            // Only Positive Movement
            if (adjustedDeltaX > 0) {
                ball_x += adjustedDeltaX;
            }
        }
        else if (ball_x >= (1 * FT)) { // Right Side Cut-Off
            // Only Negative Movement
            if (adjustedDeltaX < 0) {
                ball_x += adjustedDeltaX;
            }
        }
        else {
            ball_x += adjustedDeltaX;
        }

        if (ball_y <= (5 * FT)) { // Bottom Side Cut-Off
            // Only Positive Movement
            if (adjustedDeltaY > 0) {
                ball_y += adjustedDeltaY;
            }
        }
        else if (ball_y >= (6.2 * FT)) { // Top Side Cut-Off
            // Only Negative Movement
            if (adjustedDeltaY < 0) {
                ball_y += adjustedDeltaY;
            }
        }
        else {
            ball_y += adjustedDeltaY;
        }
    }

    prevMouseX = x;
    prevMouseY = y;
    glutPostRedisplay();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case ' ':  
        throw_ball = true;
        break;
    case 'r': // Start Game
        if (game_started == false) {
            player1_score = 0;
            player2_score = 0;
            cup1_p1_gone = false;
            cup2_p1_gone = false;
            cup3_p1_gone = false;
            cup1_p2_gone = false;
            cup2_p2_gone = false;
            cup3_p2_gone = false;
            throw_ball = false;
            ball_thrown = false;
            ball_missed = false;
            player_set = false;
            cup1_p2_score = false;
            cup2_p2_score = false;
            cup3_p2_score = false;
            cup1_p1_score = false;
            cup2_p1_score = false;
            cup3_p1_score = false;
            score = false;
            ball_throw_rotation = 0;
            game_started = true;
            turn = 1;
        }
        break;
    default:
        break;
    }    
    glutPostRedisplay();
}

// Instructions
void printInstructions()
{
    std::cout << "Welcome to 1-On-1 Water Pong Game!" << std::endl;
    std::cout << " * -The goal of the game is to throw the ball into all of your" << std::endl;
    std::cout << " *   cups before your opponent does." << std::endl;
    std::cout << " * -Press R to Start The Game." << std::endl;
    std::cout << " * -Hold Left - Click over ball to drag into desired position." << std::endl;
    std::cout << " * -Higher position = longer Shot." << std::endl;
    std::cout << " * -Lower position = shorter Shot." << std::endl;
    std::cout << " * -Press Space Bar to throw the ball." << std::endl;
    std::cout << " * -Scoreboard is at the top of the screen." << std::endl;
    std::cout << " * -There will be a mark next to the player whose turn it is at top of screen." << std::endl;
    std::cout << " * -Also, cup color will signify whose turn it is." << std::endl;
    std::cout << " * -Red = Player 1" << std::endl;
    std::cout << " * -Blue = Player 2" << std::endl;
}

// Main routine.
int main(int argc, char** argv)
{
    printInstructions();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    //Window Size:
    glutInitWindowSize(winSize_X, winSize_Y);
    glutInitWindowPosition(850, 100);

    //Create Window:
    glutCreateWindow("Water Pong 1 on 1");

    //Initialization for Window:
    main_setup();

    //Animation - countDown
    glutTimerFunc(1, animation_countDown, 1);

    //Animation - Ball Throw
    glutTimerFunc(1, animation_ballThrow, 1);

    glutDisplayFunc(drawScene);
    glutReshapeFunc(main_resize);
    glutMouseFunc(main_MouseControl);
    glutMotionFunc(moving_objects);
    glutKeyboardFunc(keyInput); 

    glutMainLoop();
    return 0;
}