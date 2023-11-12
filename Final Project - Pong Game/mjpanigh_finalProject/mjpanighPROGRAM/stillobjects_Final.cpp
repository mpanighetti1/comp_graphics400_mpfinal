/*****************************************************************
* Still Objects File - Includes:
*   - draw_solo_cup - swept surface!
*   - drawStructure - walls, ceiling, floor.
*   - drawTable - table + shadow rendering.
*   - drawHangingLight
*  
*****************************************************************/

#include "helper_Final.h"
#include "stillobjects_Final.h"

// Globals For draw_solo_cup Parametization
static int mesh_solo_cup_p = 9 * 5; // Number of grid columns.
static int mesh_solo_cup_q = 24 * 2; // Number of grid rows
static float* solo_cup_vertices = NULL; // Vertex array of the mapped sample 
static int inner_mesh_solo_cup_p = 9 * 5; // Number of grid columns.
static int inner_mesh_solo_cup_q = 24 * 2; // Number of grid rows
static float* inner_solo_cup_vertices = NULL; // Vertex array of the mapped sample 

///////////////// START: DRAW SOLO CUP ////////////////////

// Helper function to calculate cross product of two vectors
void crossProduct(float* a, float* b, float* result)
{
    result[0] = a[1] * b[2] - a[2] * b[1];
    result[1] = a[2] * b[0] - a[0] * b[2];
    result[2] = a[0] * b[1] - a[1] * b[0];
}

// Function to calculate the normal at a given vertex index
void calculateNormal(int index1, int index2, int index3, float* vertices, float* normal)
{
    float vec1[] = { vertices[index2 * 3 + 0] - vertices[index1 * 3 + 0],
                     vertices[index2 * 3 + 1] - vertices[index1 * 3 + 1],
                     vertices[index2 * 3 + 2] - vertices[index1 * 3 + 2] };

    float vec2[] = { vertices[index3 * 3 + 0] - vertices[index1 * 3 + 0],
                     vertices[index3 * 3 + 1] - vertices[index1 * 3 + 1],
                     vertices[index3 * 3 + 2] - vertices[index1 * 3 + 2] };

    crossProduct(vec1, vec2, normal);

    // Normalize the normal vector
    float normalLength = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
    normal[0] /= normalLength;
    normal[1] /= normalLength;
    normal[2] /= normalLength;
}

float draw_solo_cup_xc(float t)
{
    if      (t <= 0.2) return 4.0 * t;
    else if (t <= 0.4) return 4.0 + 0.5 * (t - 0.2) / 0.2;
    else if (t <= 0.6) return 4.5 + 0.5 * (t - 0.4) / 0.2;
    else if (t <= 0.8) return 5.0 + 1.0 * (t - 0.6) / 0.2;
    else if (t <= 1.0) return 6.0 - 0.1 * (t - 0.8) / 0.2;
    else if (t <= 1.2) return 5.9 - 1.0 * (t - 1.0) / 0.2;
    else if (t <= 1.4) return 4.9 - 0.5 * (t - 1.2) / 0.2;
    else if (t <= 1.6) return 4.4 - 0.5 * (t - 1.4) / 0.2;
    else if (t <= 1.8) return 3.9 - 3.9 * (t - 1.6) / 0.2;
    else               return 0.0;
}

float inner_draw_solo_cup_xc(float t)
{
    if (t <= 3.89) return 0 + t * (3.89 - 0) / 3.89;
    else if (t <= 7.78) return 3.89 + (t - 3.89) * (4.39 - 3.89) / (7.78 - 3.89);
    else if (t <= 11.67) return 4.39 + (t - 7.78) * (4.89 - 4.39) / (11.67 - 7.78);
    else if (t <= 17.67) return 4.89 + (t - 11.67) * (5.9 - 4.89) / (17.67 - 11.67);
    else if (t <= 18.56) return 5.9 + (t - 17.67) * (5.89 - 5.9) / (18.56 - 17.67);
    else if (t <= 19.45) return 5.89 + (t - 18.56) * (6.1 - 5.89) / (19.45 - 18.56);
    else if (t <= 20.34) return 6.1 + (t - 19.45) * (6.1 - 6.1) / (20.34 - 19.45);
    else if (t <= 21.23) return 6.1 + (t - 20.34) * (5.84 - 6.1) / (21.23 - 20.34);
    else if (t <= 27.23) return 5.84 + (t - 21.23) * (4.84 - 5.84) / (27.23 - 21.23);
    else if (t <= 31.12) return 4.84 + (t - 27.23) * (4.34 - 4.84) / (31.12 - 27.23);
    else if (t <= 35.01) return 4.34 + (t - 31.12) * (3.84 - 4.34) / (35.01 - 31.12);
    else return 3.84 + (t - 35.01) * (0 - 3.84) / (39.0 - 35.01);
}

float draw_solo_cup_yc(float t)
{
    if      (t <= 0.2) return 0.0;
    else if (t <= 0.4) return 8.0 * (t - 0.2) / 0.2;
    else if (t <= 0.6) return 8.0 + 0.5 * (t - 0.4) / 0.2;
    else if (t <= 0.8) return 8.5 + 6.5 * (t - 0.6) / 0.2;
    else if (t <= 1.0) return 15.0;
    else if (t <= 1.2) return 15.0 - 6.5 * (t - 1.0) / 0.2;
    else if (t <= 1.4) return 8.5 - 0.5 * (t - 1.2) / 0.2;
    else if (t <= 1.6) return 8.0 - 7.9 * (t - 1.4) / 0.2;
    else if (t <= 1.8) return 0.1 - 0.1 * (t - 1.6) / 0.2;
    else               return 0.0;
}

float inner_draw_solo_cup_yc(float t)
{
    if (t <= 3.89) return 0.11 + (t - 0) * (0.11 - 0.11) / (3.89 - 0);
    else if (t <= 7.78) return 0.11 + (t - 3.89) * (8.0 - 0.11) / (7.78 - 3.89);
    else if (t <= 11.67) return 8.0 + (t - 7.78) * (8.5 - 8.0) / (11.67 - 7.78);
    else if (t <= 17.67) return 8.5 + (t - 11.67) * (15.0 - 8.5) / (17.67 - 11.67);
    else if (t <= 18.56) return 15.0 + (t - 17.67) * (15.0 - 15.0) / (18.56 - 17.67);
    else if (t <= 19.45) return 15.0 + (t - 18.56) * (15.0 - 15.0) / (19.45 - 18.56);
    else if (t <= 20.34) return 15.0 + (t - 19.45) * (15.1 - 15.0) / (20.34 - 19.45);
    else if (t <= 21.23) return 15.1 + (t - 20.34) * (15.1 - 15.1) / (21.23 - 20.34);
    else if (t <= 27.23) return 15.1 + (t - 21.23) * (8.5 - 15.1) / (27.23 - 21.23);
    else if (t <= 31.12) return 8.5 + (t - 27.23) * (8.0 - 8.5) / (31.12 - 27.23);
    else if (t <= 35.01) return 8.0 + (t - 31.12) * (0.16 - 8.0) / (35.01 - 31.12);
    else return 0.16 + (t - 35.01) * (0.16 - 0.16) / (39.0 - 35.01);
}

float f(int i, int j)
{
    return (draw_solo_cup_xc((float)i / mesh_solo_cup_p * 1.8) * cos((-1 + 2 * (float)j / mesh_solo_cup_q) * PI));
}
float g(int i, int j)
{
    return (draw_solo_cup_yc((float)i / mesh_solo_cup_p * 1.8));
}
float h(int i, int j)
{
    return (draw_solo_cup_xc((float)i / mesh_solo_cup_p * 1.8) * sin((-1 + 2 * (float)j / mesh_solo_cup_q) * PI));
}

float inner_f(int i, int j)
{
    return (inner_draw_solo_cup_xc((float)i / inner_mesh_solo_cup_p * 35.01) * cos((-1 + 2 * (float)j / inner_mesh_solo_cup_q) * PI));
}
float inner_g(int i, int j)
{
    return (inner_draw_solo_cup_yc((float)i / inner_mesh_solo_cup_p * 35.01));
}
float inner_h(int i, int j)
{
    return (inner_draw_solo_cup_xc((float)i / inner_mesh_solo_cup_p * 35.01) * sin((-1 + 2 * (float)j / inner_mesh_solo_cup_q) * PI));
}

void outer_fillVertexArray(void)
{
    int i, j, k;

    k = 0;
    for (j = 0; j <= mesh_solo_cup_q; j++)
        for (i = 0; i <= mesh_solo_cup_p; i++)
        {
            solo_cup_vertices[k++] = f(i, j);
            solo_cup_vertices[k++] = g(i, j);
            solo_cup_vertices[k++] = h(i, j);
        }
}

void inner_fillVertexArray(void)
{
    int i, j, k;

    k = 0;
    for (j = 0; j <= inner_mesh_solo_cup_q; j++)
        for (i = 0; i <= inner_mesh_solo_cup_p; i++)
        {
            inner_solo_cup_vertices[k++] = inner_f(i, j);
            inner_solo_cup_vertices[k++] = inner_g(i, j);
            inner_solo_cup_vertices[k++] = inner_h(i, j);
        }
}

void inner_draw_solo_cup(bool scored, bool ball_missed) {

    if (scored) {
        glEnable(GL_LIGHT2);
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT0);
    }
    else if (ball_missed) {
        glEnable(GL_LIGHT3);
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT0);
    }

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

    float matInnerCupDiff[] = { 1.0, 1.0, 1.0, 1.0 };
    float matInnerCupAmb[] = { 1.0, 1.0, 1.0, 1.0 };
    float matInnerCupSpec[] = { 1.0, 1.0, 1.0, 1.0 };
    float matInnerCupEmissRed[] = { 1.0, 0.0, 0.0, 1.0 };
    float matInnerCupEmissGreen[] = { 0.0, 1.0, 0.0, 1.0 };
    float matInnerCupShine[] = { 50.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matInnerCupDiff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matInnerCupAmb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matInnerCupSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matInnerCupShine);

    if (scored) {
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matInnerCupEmissGreen);
    }
    else if (ball_missed) {
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matInnerCupEmissRed);
    }
  
    int  i, j;
    // Dynamic array allocation with new value of p and q.
    inner_solo_cup_vertices = new float[3 * (inner_mesh_solo_cup_p + 1) * (inner_mesh_solo_cup_q + 1)];
    glVertexPointer(3, GL_FLOAT, 0, inner_solo_cup_vertices);

    // Fill the vertex array.
    inner_fillVertexArray();

    // Make the approximating triangular mesh.
    // Include normals
    for (j = 0; j < inner_mesh_solo_cup_q; j++)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (i = 0; i <= inner_mesh_solo_cup_p; i++)
        {
            int index1 = (j + 1) * (inner_mesh_solo_cup_p + 1) + i; // Dark
            int index2 = j * (inner_mesh_solo_cup_p + 1) + i; //
            int index3 = j * (inner_mesh_solo_cup_p + 1) + i + 1;

            float normal[3];
            calculateNormal(index1, index2, index3, inner_solo_cup_vertices, normal); 
            glNormal3fv(normal);
            glArrayElement(index1);
            glArrayElement(index2);
        }
        glEnd();
    }

    //Restore Old Material Settings
    glMaterialfv(GL_FRONT, GL_AMBIENT, CurrentAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, CurrentDiff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, CurrentSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, CurrentShine);
    glMaterialfv(GL_FRONT, GL_EMISSION, CurrentEmission);

    
    if (scored) {
        glDisable(GL_LIGHT2);
        glEnable(GL_LIGHT1);
        glEnable(GL_LIGHT0);        
    }
    else if (ball_missed) {
        glDisable(GL_LIGHT3);
        glEnable(GL_LIGHT1);
        glEnable(GL_LIGHT0);
    }
}

void STILLOBJECTS_FINAL::draw_solo_cup(bool scored, bool ball_missed) {

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

    if (turn == 1) {
        float matCupDiff[] = { 0.8, 0.0, 0.0, 1.0 };
        float matCupAmb[] = { 0.8 * 2, 0.0, 0.0, 1.0 };
        float matCupSpec[] = { 1.0 * 2, 0.835 * 2, 0.667 * 2, 1.0 };
        float matCupShine[] = { 50.0 };
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matCupDiff);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matCupAmb);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matCupSpec);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matCupShine);
    }    
    else if (turn == 2) {
        float matCupDiff[] = { 0.132, 0.1694, 0.88 * 2, 1.0 };
        float matCupAmb[] = { 0.132, 0.1694, 0.88 * 2, 1.0 };
        float matCupSpec[] = { 1.0 * 2, 0.835 * 2, 0.667 * 2, 1.0 };
        float matCupShine[] = { 50.0 };
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matCupDiff);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matCupAmb);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matCupSpec);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matCupShine);
    }

    int  i, j;
    // Dynamic array allocation with new value of p and q.
    solo_cup_vertices = new float[3 * (mesh_solo_cup_p + 1) * (mesh_solo_cup_q + 1)];
    glVertexPointer(3, GL_FLOAT, 0, solo_cup_vertices);

    // Fill the vertex array.
    outer_fillVertexArray();

    // Make the approximating triangular mesh.
    // Include normals
    for (j = 0; j < mesh_solo_cup_q; j++)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (i = 0; i <= mesh_solo_cup_p; i++)
        {
            int index1 = (j + 1) * (mesh_solo_cup_p + 1) + i;
            int index2 = j * (mesh_solo_cup_p + 1) + i;
            int index3 = j * (mesh_solo_cup_p + 1) + i + 1;

            float normal[3];
            calculateNormal(index1, index2, index3, solo_cup_vertices, normal);
            glNormal3fv(normal);
            glArrayElement(index1);
            glArrayElement(index2);
        }
        glEnd();
    }

    inner_draw_solo_cup(scored, ball_missed);

    //Restore Old Material Settings
    glMaterialfv(GL_FRONT, GL_AMBIENT, CurrentAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, CurrentDiff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, CurrentSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, CurrentShine);
    glMaterialfv(GL_FRONT, GL_EMISSION, CurrentEmission);
}

///////////////// START: DRAW STRUCTURE ////////////////////

void STILLOBJECTS_FINAL::drawStructure() {
    
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
    
    float matStuctureDiff[] = { 0.9, 0.9, 0.9, 1.0 };
    float matStuctureAmb[] = { 0.9, 0.9, 0.9, 1.0 };
    float matStuctureSpec[] = { 0.9, 0.9, 0.9, 1.0 };
    float matStuctureShine[] = { 50.0 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matStuctureDiff);
    glMaterialfv(GL_FRONT, GL_AMBIENT, matStuctureAmb);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matStuctureSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matStuctureShine);

    // X- Wall
    glBindTexture(GL_TEXTURE_2D, xNeg_spaceTexture);
    glPushMatrix();
    glTranslated(-5.5 * FT, 4.5 * FT, 0 * FT);
    Helper_Final::drawScaledCube_xPosText(1.0 * FT, 9.0 * FT, 13.0 * FT, true);
    glPopMatrix();
    
    // X+ Wall
    glBindTexture(GL_TEXTURE_2D, xPos_spaceTexture);
    glPushMatrix();
    glTranslated(5.5 * FT, 4.5 * FT, 0 * FT);
    Helper_Final::drawScaledCube_xNegText(1.0 * FT, 9.0 * FT, 13.0 * FT, true);
    glPopMatrix();

    // Z+ Wall
    glBindTexture(GL_TEXTURE_2D, zNeg_spaceTexture);
    glPushMatrix();
    glTranslated(0 * FT, 4.5 * FT, 7.0 * FT);
    Helper_Final::drawScaledCube_zNegText(10.0 * FT, 9.0 * FT, 1.0 * FT, true);
    glPopMatrix();

    // Z- Wall
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, zPos_spaceTexture);
    glTranslated(0 * FT, 4.5 * FT, -7.0 * FT);
    Helper_Final::drawScaledCube_zPosText(10.0 * FT, 9.0 * FT, 1.0 * FT, true);
    glPopMatrix();       

    // Floor
    glBindTexture(GL_TEXTURE_2D, carpetTexture);
    glPushMatrix();
    glTranslated(0 * FT, -0.5 * FT, 0 * FT);
    Helper_Final::drawScaledCube_topText(10 * FT, 1.0 * FT, 13.0 * FT, true);
    glPopMatrix();

    // Ceiling    
    glPushMatrix();
    glTranslated(0 * FT, 9.5 * FT, 0 * FT);
    Helper_Final::drawScaledCube_topText(11 * FT, 1.0 * FT, 14.0 * FT, false);
    glPopMatrix();

    //Restore Old Material Settings
    glMaterialfv(GL_FRONT, GL_AMBIENT, CurrentAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, CurrentDiff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, CurrentSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, CurrentShine);
    glMaterialfv(GL_FRONT, GL_EMISSION, CurrentEmission);
}

///////////////// START: DRAW TABLE ////////////////////

void STILLOBJECTS_FINAL::drawTable(int shadow) {

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

    if (shadow) {
        glScaled(1.0, 1.0, 1.1);
        glColor4f(0.0, 0.0, 0.0, 0.7);
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    else {
        float matTableDiff[] = { 0.78, 0.5857, 0.273, 1.0 };
        float matTableAmb[] = { 0.78, 0.5857, 0.273, 1.0 };
        float matTableSpec[] = { 1.0 * 0.7, 0.835 * 0.7, 0.667 * 0.7, 1.0 };
        float matTableShine[] = { 50.0 };
        glMaterialfv(GL_FRONT, GL_DIFFUSE, matTableDiff);
        glMaterialfv(GL_FRONT, GL_AMBIENT, matTableAmb);
        glMaterialfv(GL_FRONT, GL_SPECULAR, matTableSpec);
        glMaterialfv(GL_FRONT, GL_SHININESS, matTableShine);
        glBindTexture(GL_TEXTURE_2D, tableTexture);
    }    

    // Table
    glPushMatrix();
    glTranslated(0 * FT, 2.5 * FT, 0 * FT);
    if (shadow) Helper_Final::drawScaledCube_topText(4.0 * FT, 0.1 * FT, 9.0 * FT, false);
    else Helper_Final::drawScaledCube_topText(4.0 * FT, 0.1 * FT, 9.0 * FT, true);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(1 * FT, 0 * FT, 0 * FT);
    float matTableDiff[] = { 0.78 * 0.5, 0.5857 * 0.5, 0.273 * 0.5, 1.0 };
    float matTableAmb[] = { 0.78 * 0.5, 0.5857 * 0.5, 0.273 * 0.5, 1.0 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matTableDiff);
    glMaterialfv(GL_FRONT, GL_AMBIENT, matTableAmb);
    Helper_Final::drawScaledCube_topText(1 * FT, 2 * FT, 4.0 * FT, false);
    glPopMatrix();

    glDisable(GL_BLEND);
    //Restore Old Material Settings
    glMaterialfv(GL_FRONT, GL_AMBIENT, CurrentAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, CurrentDiff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, CurrentSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, CurrentShine);
    glMaterialfv(GL_FRONT, GL_EMISSION, CurrentEmission);
}

///////////////// START: DRAW HANGING LIGHT ////////////////////

void STILLOBJECTS_FINAL::drawHangingLight() {

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

    float matLightDiff[] = { 0.01, 0.01, 0.01, 1.0 };
    float matLightAmb[] = { 0.01, 0.01, 0.01, 1.0 };
    float matLightSpec[] = { 1.0 * 0.7, 0.835 * 0.7, 0.667 * 0.7, 1.0 };
    float matLightShine[] = { 100.0 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matLightDiff);
    glMaterialfv(GL_FRONT, GL_AMBIENT, matLightAmb);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matLightSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matLightShine);

    // Hanging Light
    glPushMatrix();
    glTranslated(0 * FT, 8 * FT, 0 * FT);
    glRotated(90, 1, 0, 0);
    Helper_Final::drawCylinder(0.3 * FT, 1.5 * FT, 1.0 * FT, 360, 360);
    glPopMatrix();

    float matLightInsideDiff[] = { 1.0, 1.0, 1.0, 1.0 };
    float matLightInsideAmb[] = { 1.0, 1.0, 1.0, 1.0 };
    float matLightInsideSpec[] = { 1.0 * 0.7, 0.835 * 0.7, 0.667 * 0.7, 1.0 };
    float matLightInsideEmiss[] = { 1.0 * 0.7, 0.835 * 0.7, 0.667 * 0.7, 1.0 };
    float matLightInsideShine[] = { 100.0 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matLightInsideDiff);
    glMaterialfv(GL_FRONT, GL_AMBIENT, matLightInsideAmb);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matLightInsideSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matLightInsideShine);
    glMaterialfv(GL_FRONT, GL_EMISSION, matLightInsideEmiss);

    // Hanging Light
    glPushMatrix();
    glTranslated(0 * FT, 7.99 * FT, 0 * FT);
    glRotated(90, 1, 0, 0);
    Helper_Final::drawCylinder(0.3 * FT, 1.5 * FT, 1.0 * FT, 360, 360);
    glPopMatrix();

    //Restore Old Material Settings
    glMaterialfv(GL_FRONT, GL_AMBIENT, CurrentAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, CurrentDiff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, CurrentSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, CurrentShine);
    glMaterialfv(GL_FRONT, GL_EMISSION, CurrentEmission);
}
