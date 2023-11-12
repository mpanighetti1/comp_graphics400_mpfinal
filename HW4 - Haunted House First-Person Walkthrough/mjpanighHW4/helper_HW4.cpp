/***********************************************************************
*
* Helper file for HW4 - Includes:
*   - Scaled Cube With Custom Normals To Turn Sunlight Off
*     Indicated Sides.
*   - drawCube Will Render Sides with Triangle Meshes
*   - drawCylinder
*   
************************************************************************/

#include "helper_HW4.h"

// Helper function to store and restore light states
void setLightState(GLenum light, bool enable) {
    if (enable) {
        glEnable(light);
    }
    else {
        glDisable(light);
    }
}

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
void drawCube(float size, const bool lightSides[6]) {
    
    size /= 2.0f; // Half of the cube size
    int divs = 10; // Number of divisions per side
    float step = size * 2 / divs;

    float vertices[8][3] = {
        {-size, -size, -size}, {size, -size, -size}, {size, size, -size}, {-size, size, -size},
        {-size, -size, size}, {size, -size, size}, {size, size, size}, {-size, size, size}
    };

    int faces[6][4] = {
        {0, 1, 2, 3}, {1, 5, 6, 2}, {5, 4, 7, 6}, {4, 0, 3, 7}, {3, 2, 6, 7}, {4, 5, 1, 0}
    };

    for (int f = 0; f < 6; f++) {
        // Save the initial light states
        GLboolean light0_enabled, light2_enabled;
        glGetBooleanv(GL_LIGHT0, &light0_enabled);

        if (!lightSides[f]) {
            // Disable the lights for this face
            setLightState(GL_LIGHT0, false);
        }

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

                glBegin(GL_TRIANGLES);

                calcNormal(v1, v3, v2, normal);
                glNormal3fv(normal);
                glVertex3fv(v1);
                glVertex3fv(v3);
                glVertex3fv(v2);

                calcNormal(v3, v1, v4, normal);
                glNormal3fv(normal);
                glVertex3fv(v3);
                glVertex3fv(v1);
                glVertex3fv(v4);

                glEnd();
            }
        }

        // Restore the initial light states after drawing the face
        setLightState(GL_LIGHT0, light0_enabled);
    }
}

// Function to draw a triangle mesh for the cube
void drawCube_NoRed(float size, const bool lightSides[6]) {

    size /= 2.0f; // Half of the cube size
    int divs = 10; // Number of divisions per side
    float step = size * 2 / divs;

    float vertices[8][3] = {
        {-size, -size, -size}, {size, -size, -size}, {size, size, -size}, {-size, size, -size},
        {-size, -size, size}, {size, -size, size}, {size, size, size}, {-size, size, size}
    };

    int faces[6][4] = {
        {0, 1, 2, 3}, {1, 5, 6, 2}, {5, 4, 7, 6}, {4, 0, 3, 7}, {3, 2, 6, 7}, {4, 5, 1, 0}
    };

    for (int f = 0; f < 6; f++) {
        // Save the initial light states
        GLboolean light0_enabled, light2_enabled;
        glGetBooleanv(GL_LIGHT0, &light0_enabled);
        glGetBooleanv(GL_LIGHT2, &light2_enabled);

        if (!lightSides[f]) {
            // Disable the lights for this face
            setLightState(GL_LIGHT0, false);
            setLightState(GL_LIGHT2, false);
        }

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

                glBegin(GL_TRIANGLES);

                calcNormal(v1, v3, v2, normal);
                glNormal3fv(normal);
                glVertex3fv(v1);
                glVertex3fv(v3);
                glVertex3fv(v2);

                calcNormal(v3, v1, v4, normal);
                glNormal3fv(normal);
                glVertex3fv(v3);
                glVertex3fv(v1);
                glVertex3fv(v4);

                glEnd();
            }
        }

        // Restore the initial light states after drawing the face
        setLightState(GL_LIGHT0, light0_enabled);
        setLightState(GL_LIGHT2, light2_enabled);
    }
}

// Draw a scaled cube with custom normals and adjustable lighting
void Helper_HW4::drawScaledCube(float width, float height, float depth, 
    const bool lightSides[6]) {
    
    // Save the initial light states
    GLboolean light0_enabled, light2_enabled;
    glGetBooleanv(GL_LIGHT0, &light0_enabled);

    // Scale the cube and call drawCube function
    glPushMatrix();
    glScalef(width, height, depth);
    drawCube(1.0, lightSides);
    glPopMatrix();

    // Restore the initial light states
    setLightState(GL_LIGHT0, light0_enabled);
}

// Draw a scaled cube with custom normals and adjustable lighting
void Helper_HW4::drawScaledCube_NoRed(float width, float height, float depth,
    const bool lightSides[6]) {

    // Save the initial light states
    GLboolean light0_enabled, light2_enabled;
    glGetBooleanv(GL_LIGHT0, &light0_enabled);
    glGetBooleanv(GL_LIGHT2, &light2_enabled);

    // Scale the cube and call drawCube function
    glPushMatrix();
    glScalef(width, height, depth);
    drawCube_NoRed(1.0, lightSides);
    glPopMatrix();

    // Restore the initial light states
    setLightState(GL_LIGHT0, light0_enabled);
    glGetBooleanv(GL_LIGHT2, &light2_enabled);
}

// Draw Cylinder
void Helper_HW4::drawCylinder(float baseRadius, float topRadius, float height,
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
