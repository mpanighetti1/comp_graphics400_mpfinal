/***********************************************************************
* Helper file for Final  - Includes:
*   - drawScaledCube with any side texture.
*   - drawCylinder with Quadric
*   - getBMPData
*   - loadExternalTextures
*   - renderScaledText
*   - checkSpheresIntersection
*   - getID for Color Picking
*   
************************************************************************/

#include "helper_Final.h"

GLuint tableTexture;
GLuint carpetTexture;
GLuint ballTexture;
GLuint xNeg_spaceTexture;
GLuint xPos_spaceTexture;
GLuint zNeg_spaceTexture;
GLuint zPos_spaceTexture;

///////////// CHANGING EXTERNAL VARIABLES ///////////////

double ball_throw_rotation = 0;
void Helper_Final::change_ball_throw_rotation(double new_value) {
    ball_throw_rotation = new_value;
}

///////////// DRAWING FUCNTIONS ///////////////

// Function to calculate normal of a triangle
void calcNormal(float v1[3], float v2[3], float v3[3], float out[3]) {
    float vec1[3], vec2[3];
    for (int i = 0; i < 3; i++) {
        vec1[i] = v1[i] - v2[i];
        vec2[i] = v1[i] - v3[i];
    }

    out[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
    out[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
    out[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];

    float norm = sqrt(out[0] * out[0] + out[1] * out[1] + out[2] * out[2]);
    for (int i = 0; i < 3; i++) {
        out[i] /= norm;
    }
}

// Function to draw a triangle mesh for the cube
void drawCube_topText(float size, bool applyTexture) {
    
    size /= 2.0f; // Half of the cube size
    int divs = 5; // Number of divisions per side
    float step = size * 2 / divs;

    float vertices[8][3] = {
        {-size, -size, -size}, {size, -size, -size}, {size, size, -size}, {-size, size, -size},
        {-size, -size, size}, {size, -size, size}, {size, size, size}, {-size, size, size}
    };

    int faces[6][4] = {
        {0, 1, 2, 3}, // face 0 -z
        {1, 5, 6, 2}, // face 1 +x
        {5, 4, 7, 6}, // face 2 +z
        {4, 0, 3, 7}, // face 3 -x
        {3, 2, 6, 7}, // face 4 +y
        {4, 5, 1, 0}  // face 5 -y
    };

    for (int f = 0; f < 6; f++) {
        for (int i = 0; i < divs; i++) {
            for (int j = 0; j < divs; j++) {
                float v1[3], v2[3], v3[3], v4[3], normal[3];

                for (int k = 0; k < 3; k++) {
                    v1[k] = vertices[faces[f][0]][k] + (vertices[faces[f][1]][k] - vertices[faces[f][0]][k]) * (i * step) / (size * 2)
                        + (vertices[faces[f][3]][k] - vertices[faces[f][0]][k]) * (j * step) / (size * 2);
                    v2[k] = vertices[faces[f][0]][k] + (vertices[faces[f][1]][k] - vertices[faces[f][0]][k]) * ((i + 1) * step) / (size * 2)
                        + (vertices[faces[f][3]][k] - vertices[faces[f][0]][k]) * (j * step) / (size * 2);
                    v3[k] = vertices[faces[f][0]][k] + (vertices[faces[f][1]][k] - vertices[faces[f][0]][k]) * ((i + 1) * step) / (size * 2)
                        + (vertices[faces[f][3]][k] - vertices[faces[f][0]][k]) * ((j + 1) * step) / (size * 2);
                    v4[k] = vertices[faces[f][0]][k] + (vertices[faces[f][1]][k] - vertices[faces[f][0]][k]) * (i * step) / (size * 2)
                        + (vertices[faces[f][3]][k] - vertices[faces[f][0]][k]) * ((j + 1) * step) / (size * 2);
                }

                if (applyTexture && f == 4) { // Positive Y face
                    glEnable(GL_TEXTURE_2D);
                }

                glBegin(GL_TRIANGLES);

                calcNormal(v1, v3, v2, normal);
                glNormal3fv(normal);
                if (f == 4) { // Positive Y face
                    glTexCoord2f((float)i / divs, (float)j / divs);
                }
                glVertex3fv(v1);
                if (f == 4) { // Positive Y face
                    glTexCoord2f((float)(i + 1) / divs, (float)(j + 1) / divs);
                }
                glVertex3fv(v3);
                if (f == 4) { // Positive Y face
                    glTexCoord2f((float)(i + 1) / divs, (float)j / divs);
                }
                glVertex3fv(v2);

                calcNormal(v3, v1, v4, normal);
                glNormal3fv(normal);
                if (f == 4) { // Positive Y face
                    glTexCoord2f((float)(i + 1) / divs, (float)(j + 1) / divs);
                }
                glVertex3fv(v3);
                if (f == 4) { // Positive Y face
                    glTexCoord2f((float)i / divs, (float)j / divs);
                }
                glVertex3fv(v1);
                if (f == 4) { // Positive Y face
                    glTexCoord2f((float)i / divs, (float)(j + 1) / divs);
                }
                glVertex3fv(v4);

                glEnd();

                if (applyTexture && f == 4) { // Positive Y face
                    glDisable(GL_TEXTURE_2D);
                }
            }
        }
    }
}

// Draw a scaled cube with custom normals and adjustable lighting
void Helper_Final::drawScaledCube_topText(float width, float height, float depth,
    bool applyTexture) {
    
    // Scale the cube and call drawCube function
    glPushMatrix();
    glScalef(width, height, depth);
    drawCube_topText(1.0, applyTexture);
    glPopMatrix();
}

// X+ Texture
void drawCube_xPosText(float size, bool applyTexture) {

    size /= 2.0f; // Half of the cube size
    int divs = 5; // Number of divisions per side
    float step = size * 2 / divs;

    float vertices[8][3] = {
        {-size, -size, -size}, {size, -size, -size}, {size, size, -size}, {-size, size, -size},
        {-size, -size, size}, {size, -size, size}, {size, size, size}, {-size, size, size}
    };

    int faces[6][4] = {
        {0, 1, 2, 3}, // face 0 -z
        {1, 5, 6, 2}, // face 1 +x
        {5, 4, 7, 6}, // face 2 +z
        {4, 0, 3, 7}, // face 3 -x
        {3, 2, 6, 7}, // face 4 +y
        {4, 5, 1, 0}  // face 5 -y
    };

    for (int f = 0; f < 6; f++) {
        for (int i = 0; i < divs; i++) {
            for (int j = 0; j < divs; j++) {
                float v1[3], v2[3], v3[3], v4[3], normal[3];

                for (int k = 0; k < 3; k++) {
                    v1[k] = vertices[faces[f][0]][k] + (vertices[faces[f][1]][k] - vertices[faces[f][0]][k]) * (i * step) / (size * 2)
                        + (vertices[faces[f][3]][k] - vertices[faces[f][0]][k]) * (j * step) / (size * 2);
                    v2[k] = vertices[faces[f][0]][k] + (vertices[faces[f][1]][k] - vertices[faces[f][0]][k]) * ((i + 1) * step) / (size * 2)
                        + (vertices[faces[f][3]][k] - vertices[faces[f][0]][k]) * (j * step) / (size * 2);
                    v3[k] = vertices[faces[f][0]][k] + (vertices[faces[f][1]][k] - vertices[faces[f][0]][k]) * ((i + 1) * step) / (size * 2)
                        + (vertices[faces[f][3]][k] - vertices[faces[f][0]][k]) * ((j + 1) * step) / (size * 2);
                    v4[k] = vertices[faces[f][0]][k] + (vertices[faces[f][1]][k] - vertices[faces[f][0]][k]) * (i * step) / (size * 2)
                        + (vertices[faces[f][3]][k] - vertices[faces[f][0]][k]) * ((j + 1) * step) / (size * 2);
                }

                if (applyTexture && f == 1) { // Positive X face
                    glEnable(GL_TEXTURE_2D);
                }

                glBegin(GL_TRIANGLES);

                calcNormal(v1, v3, v2, normal);
                glNormal3fv(normal);
                if (f == 1) { // Positive X face
                    glTexCoord2f((float)i / divs, (float)j / divs);
                }
                glVertex3fv(v1);
                if (f == 1) { // Positive X face
                    glTexCoord2f((float)(i + 1) / divs, (float)(j + 1) / divs);
                }
                glVertex3fv(v3);
                if (f == 1) { // Positive X face
                    glTexCoord2f((float)(i + 1) / divs, (float)j / divs);
                }
                glVertex3fv(v2);

                calcNormal(v3, v1, v4, normal);
                glNormal3fv(normal);
                if (f == 1) { // Positive X face
                    glTexCoord2f((float)(i + 1) / divs, (float)(j + 1) / divs);
                }
                glVertex3fv(v3);
                if (f == 1) { // Positive X face
                    glTexCoord2f((float)i / divs, (float)j / divs);
                }
                glVertex3fv(v1);
                if (f == 1) { // Positive X face
                    glTexCoord2f((float)i / divs, (float)(j + 1) / divs);
                }
                glVertex3fv(v4);

                glEnd();

                if (applyTexture && f == 1) { // Positive X face
                    glDisable(GL_TEXTURE_2D);
                }
            }
        }
    }
}

// X+ Texture
void Helper_Final::drawScaledCube_xPosText(float width, float height, float depth,
    bool applyTexture) {

    // Scale the cube and call drawCube function
    glPushMatrix();
    glScalef(width, height, depth);
    drawCube_xPosText(1.0, applyTexture);
    glPopMatrix();
}

// X- Texture
void drawCube_xNegText(float size, bool applyTexture) {

    size /= 2.0f; // Half of the cube size
    int divs = 5; // Number of divisions per side
    float step = size * 2 / divs;

    float vertices[8][3] = {
        {-size, -size, -size}, {size, -size, -size}, {size, size, -size}, {-size, size, -size},
        {-size, -size, size}, {size, -size, size}, {size, size, size}, {-size, size, size}
    };

    int faces[6][4] = {
        {0, 1, 2, 3}, // face 0 -z
        {1, 5, 6, 2}, // face 1 +x
        {5, 4, 7, 6}, // face 2 +z
        {4, 0, 3, 7}, // face 3 -x
        {3, 2, 6, 7}, // face 4 +y
        {4, 5, 1, 0}  // face 5 -y
    };

    for (int f = 0; f < 6; f++) {
        for (int i = 0; i < divs; i++) {
            for (int j = 0; j < divs; j++) {
                float v1[3], v2[3], v3[3], v4[3], normal[3];

                for (int k = 0; k < 3; k++) {
                    v1[k] = vertices[faces[f][0]][k] + (vertices[faces[f][1]][k] - vertices[faces[f][0]][k]) * (i * step) / (size * 2)
                        + (vertices[faces[f][3]][k] - vertices[faces[f][0]][k]) * (j * step) / (size * 2);
                    v2[k] = vertices[faces[f][0]][k] + (vertices[faces[f][1]][k] - vertices[faces[f][0]][k]) * ((i + 1) * step) / (size * 2)
                        + (vertices[faces[f][3]][k] - vertices[faces[f][0]][k]) * (j * step) / (size * 2);
                    v3[k] = vertices[faces[f][0]][k] + (vertices[faces[f][1]][k] - vertices[faces[f][0]][k]) * ((i + 1) * step) / (size * 2)
                        + (vertices[faces[f][3]][k] - vertices[faces[f][0]][k]) * ((j + 1) * step) / (size * 2);
                    v4[k] = vertices[faces[f][0]][k] + (vertices[faces[f][1]][k] - vertices[faces[f][0]][k]) * (i * step) / (size * 2)
                        + (vertices[faces[f][3]][k] - vertices[faces[f][0]][k]) * ((j + 1) * step) / (size * 2);
                }

                if (applyTexture && f == 3) { // Positive X face
                    glEnable(GL_TEXTURE_2D);
                }

                glBegin(GL_TRIANGLES);

                calcNormal(v1, v3, v2, normal);
                glNormal3fv(normal);
                if (f == 3) { // Positive X face
                    glTexCoord2f((float)i / divs, (float)j / divs);
                }
                glVertex3fv(v1);
                if (f == 3) { // Positive X face
                    glTexCoord2f((float)(i + 1) / divs, (float)(j + 1) / divs);
                }
                glVertex3fv(v3);
                if (f == 3) { // Positive X face
                    glTexCoord2f((float)(i + 1) / divs, (float)j / divs);
                }
                glVertex3fv(v2);

                calcNormal(v3, v1, v4, normal);
                glNormal3fv(normal);
                if (f == 3) { // Positive X face
                    glTexCoord2f((float)(i + 1) / divs, (float)(j + 1) / divs);
                }
                glVertex3fv(v3);
                if (f == 3) { // Positive X face
                    glTexCoord2f((float)i / divs, (float)j / divs);
                }
                glVertex3fv(v1);
                if (f == 3) { // Positive X face
                    glTexCoord2f((float)i / divs, (float)(j + 1) / divs);
                }
                glVertex3fv(v4);

                glEnd();

                if (applyTexture && f == 3) { // Positive X face
                    glDisable(GL_TEXTURE_2D);
                }
            }
        }
    }
}

// X- Texture
void Helper_Final::drawScaledCube_xNegText(float width, float height, float depth,
    bool applyTexture) {

    // Scale the cube and call drawCube function
    glPushMatrix();
    glScalef(width, height, depth);
    drawCube_xNegText(1.0, applyTexture);
    glPopMatrix();
}

// Z- Texture
void drawCube_zNegText(float size, bool applyTexture) {

    size /= 2.0f; // Half of the cube size
    int divs = 5; // Number of divisions per side
    float step = size * 2 / divs;

    float vertices[8][3] = {
        {-size, -size, -size}, {size, -size, -size}, {size, size, -size}, {-size, size, -size},
        {-size, -size, size}, {size, -size, size}, {size, size, size}, {-size, size, size}
    };

    int faces[6][4] = {
        {0, 1, 2, 3}, // face 0 -z
        {1, 5, 6, 2}, // face 1 +x
        {5, 4, 7, 6}, // face 2 +z
        {4, 0, 3, 7}, // face 3 -x
        {3, 2, 6, 7}, // face 4 +y
        {4, 5, 1, 0}  // face 5 -y
    };

    for (int f = 0; f < 6; f++) {
        for (int i = 0; i < divs; i++) {
            for (int j = 0; j < divs; j++) {
                float v1[3], v2[3], v3[3], v4[3], normal[3];

                for (int k = 0; k < 3; k++) {
                    v1[k] = vertices[faces[f][0]][k] + (vertices[faces[f][1]][k] - vertices[faces[f][0]][k]) * (i * step) / (size * 2)
                        + (vertices[faces[f][3]][k] - vertices[faces[f][0]][k]) * (j * step) / (size * 2);
                    v2[k] = vertices[faces[f][0]][k] + (vertices[faces[f][1]][k] - vertices[faces[f][0]][k]) * ((i + 1) * step) / (size * 2)
                        + (vertices[faces[f][3]][k] - vertices[faces[f][0]][k]) * (j * step) / (size * 2);
                    v3[k] = vertices[faces[f][0]][k] + (vertices[faces[f][1]][k] - vertices[faces[f][0]][k]) * ((i + 1) * step) / (size * 2)
                        + (vertices[faces[f][3]][k] - vertices[faces[f][0]][k]) * ((j + 1) * step) / (size * 2);
                    v4[k] = vertices[faces[f][0]][k] + (vertices[faces[f][1]][k] - vertices[faces[f][0]][k]) * (i * step) / (size * 2)
                        + (vertices[faces[f][3]][k] - vertices[faces[f][0]][k]) * ((j + 1) * step) / (size * 2);
                }

                if (applyTexture && f == 0) { // Positive X face
                    glEnable(GL_TEXTURE_2D);
                }

                glBegin(GL_TRIANGLES);

                calcNormal(v1, v3, v2, normal);
                glNormal3fv(normal);
                if (f == 0) { // Positive X face
                    glTexCoord2f((float)i / divs, (float)j / divs);
                }
                glVertex3fv(v1);
                if (f == 0) { // Positive X face
                    glTexCoord2f((float)(i + 1) / divs, (float)(j + 1) / divs);
                }
                glVertex3fv(v3);
                if (f == 0) { // Positive X face
                    glTexCoord2f((float)(i + 1) / divs, (float)j / divs);
                }
                glVertex3fv(v2);

                calcNormal(v3, v1, v4, normal);
                glNormal3fv(normal);
                if (f == 0) { // Positive X face
                    glTexCoord2f((float)(i + 1) / divs, (float)(j + 1) / divs);
                }
                glVertex3fv(v3);
                if (f == 0) { // Positive X face
                    glTexCoord2f((float)i / divs, (float)j / divs);
                }
                glVertex3fv(v1);
                if (f == 0) { // Positive X face
                    glTexCoord2f((float)i / divs, (float)(j + 1) / divs);
                }
                glVertex3fv(v4);

                glEnd();

                if (applyTexture && f == 0) { // Positive X face
                    glDisable(GL_TEXTURE_2D);
                }
            }
        }
    }
}

// Z- Texture
void Helper_Final::drawScaledCube_zNegText(float width, float height, float depth,
    bool applyTexture) {

    // Scale the cube and call drawCube function
    glPushMatrix();
    glScalef(width, height, depth);
    drawCube_zNegText(1.0, applyTexture);
    glPopMatrix();
}

// Z+ Texture
void drawCube_zPosText(float size, bool applyTexture) {

    size /= 2.0f; // Half of the cube size
    int divs = 5; // Number of divisions per side
    float step = size * 2 / divs;

    float vertices[8][3] = {
        {-size, -size, -size}, {size, -size, -size}, {size, size, -size}, {-size, size, -size},
        {-size, -size, size}, {size, -size, size}, {size, size, size}, {-size, size, size}
    };

    int faces[6][4] = {
        {0, 1, 2, 3}, // face 0 -z
        {1, 5, 6, 2}, // face 1 +x
        {5, 4, 7, 6}, // face 2 +z
        {4, 0, 3, 7}, // face 3 -x
        {3, 2, 6, 7}, // face 4 +y
        {4, 5, 1, 0}  // face 5 -y
    };

    for (int f = 0; f < 6; f++) {
        for (int i = 0; i < divs; i++) {
            for (int j = 0; j < divs; j++) {
                float v1[3], v2[3], v3[3], v4[3], normal[3];

                for (int k = 0; k < 3; k++) {
                    v1[k] = vertices[faces[f][0]][k] + (vertices[faces[f][1]][k] - vertices[faces[f][0]][k]) * (i * step) / (size * 2)
                        + (vertices[faces[f][3]][k] - vertices[faces[f][0]][k]) * (j * step) / (size * 2);
                    v2[k] = vertices[faces[f][0]][k] + (vertices[faces[f][1]][k] - vertices[faces[f][0]][k]) * ((i + 1) * step) / (size * 2)
                        + (vertices[faces[f][3]][k] - vertices[faces[f][0]][k]) * (j * step) / (size * 2);
                    v3[k] = vertices[faces[f][0]][k] + (vertices[faces[f][1]][k] - vertices[faces[f][0]][k]) * ((i + 1) * step) / (size * 2)
                        + (vertices[faces[f][3]][k] - vertices[faces[f][0]][k]) * ((j + 1) * step) / (size * 2);
                    v4[k] = vertices[faces[f][0]][k] + (vertices[faces[f][1]][k] - vertices[faces[f][0]][k]) * (i * step) / (size * 2)
                        + (vertices[faces[f][3]][k] - vertices[faces[f][0]][k]) * ((j + 1) * step) / (size * 2);
                }

                if (applyTexture && f == 2) { // Positive X face
                    glEnable(GL_TEXTURE_2D);
                }

                glBegin(GL_TRIANGLES);

                calcNormal(v1, v3, v2, normal);
                glNormal3fv(normal);
                if (f == 2) { // Positive X face
                    glTexCoord2f((float)i / divs, (float)j / divs);
                }
                glVertex3fv(v1);
                if (f == 2) { // Positive X face
                    glTexCoord2f((float)(i + 1) / divs, (float)(j + 1) / divs);
                }
                glVertex3fv(v3);
                if (f == 2) { // Positive X face
                    glTexCoord2f((float)(i + 1) / divs, (float)j / divs);
                }
                glVertex3fv(v2);

                calcNormal(v3, v1, v4, normal);
                glNormal3fv(normal);
                if (f == 2) { // Positive X face
                    glTexCoord2f((float)(i + 1) / divs, (float)(j + 1) / divs);
                }
                glVertex3fv(v3);
                if (f == 2) { // Positive X face
                    glTexCoord2f((float)i / divs, (float)j / divs);
                }
                glVertex3fv(v1);
                if (f == 2) { // Positive X face
                    glTexCoord2f((float)i / divs, (float)(j + 1) / divs);
                }
                glVertex3fv(v4);

                glEnd();

                if (applyTexture && f == 2) { // Positive X face
                    glDisable(GL_TEXTURE_2D);
                }
            }
        }
    }
}

// Z+ Texture
void Helper_Final::drawScaledCube_zPosText(float width, float height, float depth,
    bool applyTexture) {

    // Scale the cube and call drawCube function
    glPushMatrix();
    glScalef(width, height, depth);
    drawCube_zPosText(1.0, applyTexture);
    glPopMatrix();
}

// Draw Cylinder
void Helper_Final::drawCylinder(float baseRadius, float topRadius, float height,
    int slices, int stacks) {
    
    GLUquadricObj* quadric = gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluQuadricTexture(quadric, GL_TRUE);

    // Draw the lateral surface of the cylinder
    gluCylinder(quadric, baseRadius, topRadius, height, slices, stacks);

    // Draw the bottom disk
    glPushMatrix();
    glRotatef(180, 1, 0, 0);
    gluDisk(quadric, 0, baseRadius, slices, 1);
    glPopMatrix();

    // Draw the top disk
    glPushMatrix();
    glTranslatef(0, 0, height);
    gluDisk(quadric, 0, topRadius, slices, 1);
    glPopMatrix();

    gluDeleteQuadric(quadric);
}

// Draw A Sphere But With Texture Coords
void Helper_Final::drawTexturedSphere(GLfloat radius, GLint slices, GLint stacks, 
    GLuint textureID) {

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    GLUquadric* quadric = gluNewQuadric();

    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluQuadricTexture(quadric, GL_TRUE);
    gluSphere(quadric, radius, slices, stacks);

    gluDeleteQuadric(quadric);
    glDisable(GL_TEXTURE_2D);
}

///////////// UTILITY FUCNTIONS ///////////////

// Routine to read a bitmap file.
BitMapFile* Helper_Final::getBMPData(std::string filename)
{
    BitMapFile* bmp = new BitMapFile;
    unsigned int size, offset, headerSize;

    // Read input file name.
    std::ifstream infile(filename.c_str(), std::ios::binary);

    // Get the starting point of the image data.
    infile.seekg(10);
    infile.read((char*)&offset, 4);

    // Get the header size of the bitmap.
    infile.read((char*)&headerSize, 4);

    // Get width and height values in the bitmap header.
    infile.seekg(18);
    infile.read((char*)&bmp->sizeX, 4);
    infile.read((char*)&bmp->sizeY, 4);

    // Allocate buffer for the image.
    size = bmp->sizeX * bmp->sizeY * 24;
    bmp->data = new unsigned char[size];

    // Read bitmap data.
    infile.seekg(offset);
    infile.read((char*)bmp->data, size);

    /*
    // Reverse color from bgr to rgb.
    int temp;
    for (int i = 0; i < size; i += 3)
    {
        temp = bmp->data[i];
        bmp->data[i] = bmp->data[i + 2];
        bmp->data[i + 2] = temp;
    }
    */

    return bmp;

}

// Load external textures.
void Helper_Final::loadExternalTextures()
{
    // Local storage for bmp image data.
    BitMapFile* image[7];

    // Load the texture.
    image[0] = Helper_Final::getBMPData("mjpanighTEXTURES/table.bmp");
    image[1] = Helper_Final::getBMPData("mjpanighTEXTURES/carpet.bmp");
    image[2] = Helper_Final::getBMPData("mjpanighTEXTURES/SU.bmp");

    image[3] = Helper_Final::getBMPData("mjpanighTEXTURES/xNegWall1.bmp");
    image[4] = Helper_Final::getBMPData("mjpanighTEXTURES/xPosWall1.bmp");
    image[5] = Helper_Final::getBMPData("mjpanighTEXTURES/zNegWall1.bmp");
    image[6] = Helper_Final::getBMPData("mjpanighTEXTURES/zPosWall1.bmp");

    // Activate Table Texture
    glGenTextures(1, &tableTexture);
    glBindTexture(GL_TEXTURE_2D, tableTexture);

    // Set texture parameters for wrapping.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture parameters for filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Specify an image as the texture to be bound with the currently active texture index.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[0]->sizeX, image[0]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[0]->data);

    // Activate Carpet Texture
    glGenTextures(1, &carpetTexture);
    glBindTexture(GL_TEXTURE_2D, carpetTexture);

    // Set texture parameters for wrapping.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture parameters for filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Specify an image as the texture to be bound with the currently active texture index.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[1]->sizeX, image[1]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[1]->data);

    // Activate Ball Texture
    glGenTextures(1, &ballTexture);
    glBindTexture(GL_TEXTURE_2D, ballTexture);

    // Set texture parameters for wrapping.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture parameters for filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Specify an image as the texture to be bound with the currently active texture index.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[2]->sizeX, image[2]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[2]->data);

    // Activate X- Wall Texture
    glGenTextures(1, &xNeg_spaceTexture);
    glBindTexture(GL_TEXTURE_2D, xNeg_spaceTexture);

    // Set texture parameters for wrapping.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture parameters for filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Specify an image as the texture to be bound with the currently active texture index.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[3]->sizeX, image[3]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[3]->data);

    // Activate X+ Wall Texture
    glGenTextures(1, &xPos_spaceTexture);
    glBindTexture(GL_TEXTURE_2D, xPos_spaceTexture);

    // Set texture parameters for wrapping.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture parameters for filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Specify an image as the texture to be bound with the currently active texture index.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[4]->sizeX, image[4]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[4]->data);

    // Activate Z+ Wall Texture
    glGenTextures(1, &zNeg_spaceTexture);
    glBindTexture(GL_TEXTURE_2D, zNeg_spaceTexture);

    // Set texture parameters for wrapping.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture parameters for filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Specify an image as the texture to be bound with the currently active texture index.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[5]->sizeX, image[5]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[5]->data);

    // Activate Z- Wall Texture
    glGenTextures(1, &zPos_spaceTexture);
    glBindTexture(GL_TEXTURE_2D, zPos_spaceTexture);

    // Set texture parameters for wrapping.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture parameters for filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Specify an image as the texture to be bound with the currently active texture index.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[6]->sizeX, image[6]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[6]->data);
}

// Render Bitmap Text
void Helper_Final::renderScaledText(float winSize_X, float winSize_Y,
    float x, float y, float scale, void* font, const char* text) {

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, winSize_X, 0, winSize_Y);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f); // White

    glScaled(scale, scale, 1.0);
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
    
    
    glEnable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glPopMatrix();

    glDisable(GL_COLOR_MATERIAL);
}

// For Collision, Check If There Is An Intersection Of Spheres
int Helper_Final::checkSpheresIntersection(double x1, double y1, double z1, double r1,
    double x2, double y2, double z2, double r2)
{
    /*
    std::cout << " Ball Collision Position: ( " << x1
        << ", " << y1
        << ", " << z1 << ")" << std::endl;
        */

    return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2) <= (r1 + r2) * (r1 + r2));
}

// Get ID for Color Picking
int Helper_Final::getID(int x, int y)
{
    unsigned char pixel[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

    if ((int)pixel[0] == 0 && (int)pixel[1] == 255 && (int)pixel[2] == 0)
    {
        return 2;  // 2 - Green
    }
    else if ((int)pixel[0] == 0 && (int)pixel[1] == 0 && (int)pixel[2] == 255)
    {
        return 3;  // 3 - Blue
    }
    else if ((int)pixel[0] == 255 && (int)pixel[1] == 0 && (int)pixel[2] == 0)
    {
        return 1;  // 1 - Red
    }
    else return 0; // Default - Nothing     
}
