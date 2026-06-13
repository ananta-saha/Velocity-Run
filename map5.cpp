#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAP5_PI 3.14159f

float map5_px = 0.0f;
float map5_pz = -5.0f;
float map5_playerSpeedX = 0.0f;
float map5_playerSpeed  = 0.25f;

float map5_eX = 0.0f,  map5_eZ = -40.0f;
float map5_coinX = 0.0f, map5_coinZ = -30.0f;
bool  map5_showCoin = true;
int   map5_score = 0;
bool  map5_gameOver = false;

float map5_coinAngle = 0.0f;
float map5_lanes[3] = {-1.3f, 0.0f, 1.3f};

void map5_drawCircle(float cx, float cy, float r,
                   float red, float green, float blue)
{
    glColor3f(red, green, blue);
    int n = 40;
    float tp = 2.0f * MAP5_PI;
    glBegin(GL_POLYGON);
    for (int i = 0; i <= n; i++)
        glVertex3f(cx + r*cos(i*tp/n), cy + r*sin(i*tp/n), 0);
    glEnd();
}

void map5_light()
{
    GLfloat pos[] = {0, 8, 5, 1};
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
}
void map5_drawSun()
{
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(-15.0f, 25.0f, -100.0f);
    map5_drawCircle(0, 0, 4.0f, 0.95f, 0.95f, 0.0f);
    glColor3f(1.0f, 0.9f, 0.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 8; i++) {
        float a = i * MAP5_PI / 4;
        glVertex3f(0, 0, 0);
        glVertex3f(cos(a)*6.0f, sin(a)*6.0f, 0);
    }
    glEnd();
    glPopMatrix();
    glEnable(GL_LIGHTING);
}
void map5_drawCloud(float x, float y, float z)
{
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(x, y, z);
    map5_drawCircle(0,    0,    1.2f, 1, 1, 1);
    map5_drawCircle(1.4f, 0.8f, 1.4f, 1, 1, 1);
    map5_drawCircle(2.8f, 0,    1.2f, 1, 1, 1);
    map5_drawCircle(1.4f,-0.4f, 1.3f, 1, 1, 1);
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void map5_drawSky()
{
    glDisable(GL_DEPTH_TEST);
    glBegin(GL_QUADS);
        glColor3f(0.4f, 0.7f, 1.0f);
        glVertex3f(-200, 100, -200);
        glVertex3f( 200, 100, -200);
        glColor3f(0.7f, 0.9f, 1.0f);
        glVertex3f( 200,  -5, -200);
        glVertex3f(-200,  -5, -200);
    glEnd();
    map5_drawSun();
    map5_drawCloud(-20, 20, -80);
    map5_drawCloud( 15, 24, -60);
    glEnable(GL_DEPTH_TEST);
}
void map5_drawRoad()
{
    glPushMatrix();
    float roadOffset = floor(map5_pz / 20.0f) * 20.0f;
    glTranslatef(0, 0, roadOffset);

    glColor3f(0.38f, 0.38f, 0.38f);
    glBegin(GL_QUADS);
        glVertex3f(-2, -1,  100);
        glVertex3f( 2, -1,  100);
        glVertex3f( 2, -1, -100);
        glVertex3f(-2, -1, -100);
    glEnd();
    glColor3f(0.2f, 0.78f, 0.2f);
    glBegin(GL_QUADS);
        glVertex3f(-20,-1.1f, 100); glVertex3f(-2,-1.1f, 100);
        glVertex3f( -2,-1.1f,-100); glVertex3f(-20,-1.1f,-100);
        glVertex3f(  2,-1.1f, 100); glVertex3f(20,-1.1f, 100);
        glVertex3f( 20,-1.1f,-100); glVertex3f(  2,-1.1f,-100);
    glEnd();
    glColor3f(1, 1, 0);
    for (float z = 100; z > -100; z -= 10) {
        glBegin(GL_QUADS);
            glVertex3f(-0.15f, -0.99f, z);
            glVertex3f( 0.15f, -0.99f, z);
            glVertex3f( 0.15f, -0.99f, z - 5);
            glVertex3f(-0.15f, -0.99f, z - 5);
        glEnd();
    }
    glPopMatrix();
}
void map5_drawTree(float x, float z)
{
    glPushMatrix();
    glTranslatef(x, -1.0f, z);
    glDisable(GL_LIGHTING);

    glColor3f(0.27f, 0.08f, 0.04f);
    glBegin(GL_POLYGON);
        glVertex3f(0.0f, 0.0f, 0); glVertex3f(0.3f, 0.0f, 0);
        glVertex3f(0.3f, 1.5f, 0); glVertex3f(0.0f, 1.5f, 0);
    glEnd();

    glColor3f(0.0f, 0.22f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex3f(-1.0f,1.5f,0); glVertex3f(1.3f,1.5f,0); glVertex3f(0.15f,3.2f,0);
    glEnd();
    glColor3f(0.0f, 0.33f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex3f(-0.8f,2.4f,0); glVertex3f(1.1f,2.4f,0); glVertex3f(0.15f,4.3f,0);
    glEnd();
    glColor3f(0.0f, 0.47f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex3f(-0.6f,3.2f,0); glVertex3f(0.9f,3.2f,0); glVertex3f(0.15f,5.5f,0);
    glEnd();

    glEnable(GL_LIGHTING);
    glPopMatrix();
}
void map5_drawCar(float x, float y, float z, float r, float g, float b)
{
    glPushMatrix();
    glTranslatef(x, y, z);

    glColor3f(r, g, b);
    glPushMatrix(); glTranslatef(0,0.35f,0); glScalef(1.6f,0.5f,0.8f); glutSolidCube(1); glPopMatrix();

    glColor3f(r*0.85f, g*0.85f, b);
    glPushMatrix(); glTranslatef(0,0.75f,0); glScalef(0.9f,0.4f,0.7f); glutSolidCube(1); glPopMatrix();

    glColor3f(0.7f, 0.9f, 1.0f);
    glPushMatrix(); glTranslatef( 0.36f,0.75f,0); glScalef(0.05f,0.32f,0.6f); glutSolidCube(1); glPopMatrix();
    glPushMatrix(); glTranslatef(-0.36f,0.75f,0); glScalef(0.05f,0.32f,0.6f); glutSolidCube(1); glPopMatrix();
    glColor3f(1.0f, 1.0f, 0.6f);
    glPushMatrix(); glTranslatef(0.82f,0.35f, 0.25f); glutSolidSphere(0.1f,10,10); glPopMatrix();
    glPushMatrix(); glTranslatef(0.82f,0.35f,-0.25f); glutSolidSphere(0.1f,10,10); glPopMatrix();

    glColor3f(1.0f, 0.1f, 0.1f);
    glPushMatrix(); glTranslatef(-0.82f,0.35f, 0.25f); glutSolidSphere(0.09f,10,10); glPopMatrix();
    glPushMatrix(); glTranslatef(-0.82f,0.35f,-0.25f); glutSolidSphere(0.09f,10,10); glPopMatrix();
    glColor3f(0.1f, 0.1f, 0.1f);
    GLUquadric* q = gluNewQuadric();
    glPushMatrix(); glTranslatef( 0.55f,0.0f, 0.45f); glRotatef(90, 1,0,0);  gluCylinder(q,0.2f,0.2f,0.15f,16,4); gluDisk(q,0,0.2f,16,1); glPopMatrix();
    glPushMatrix(); glTranslatef( 0.55f,0.0f,-0.45f); glRotatef(-90,1,0,0); gluCylinder(q,0.2f,0.2f,0.15f,16,4); gluDisk(q,0,0.2f,16,1); glPopMatrix();
    glPushMatrix(); glTranslatef(-0.55f,0.0f, 0.45f); glRotatef(90, 1,0,0);  gluCylinder(q,0.2f,0.2f,0.15f,16,4); gluDisk(q,0,0.2f,16,1); glPopMatrix();
    glPushMatrix(); glTranslatef(-0.55f,0.0f,-0.45f); glRotatef(-90,1,0,0); gluCylinder(q,0.2f,0.2f,0.15f,16,4); gluDisk(q,0,0.2f,16,1); glPopMatrix();
    gluDeleteQuadric(q);

    glPopMatrix();
}
void map5_drawCoin()
{
    if (!map5_showCoin) return;
    glPushMatrix();
    glTranslatef(map5_coinX, 0.5f, map5_coinZ);
    glRotatef(map5_coinAngle, 0, 1, 0);
    glColor3f(1.0f, 0.84f, 0.0f);
    glutSolidSphere(0.3f, 16, 16);
    glPopMatrix();
}
void map5_drawText(float x, float y, const char* str)
{
    glRasterPos2f(x, y);
    for (int i = 0; str[i]; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
}
void map5_drawHUD()
{
    char buf[50];
    glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
    gluOrtho2D(0, 700, 0, 700);
    glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity();
    glDisable(GL_LIGHTING); glDisable(GL_DEPTH_TEST);
    sprintf(buf, "Score: %d", map5_score);
    glColor3f(0, 0, 0);
    map5_drawText(20, 670, buf);
    if (map5_gameOver) {
        glColor3f(1, 0, 0);
        map5_drawText(250, 380, "GAME OVER!");
        glColor3f(1, 1, 1);
        map5_drawText(230, 350, "Press R to Restart");
        sprintf(buf, "Final Score: %d", map5_score);
        map5_drawText(250, 320, buf);
    }
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION); glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
void map5_setup3DCamera()
{
    float camX = map5_px;
    float camY = 8.0f;
    float camZ = map5_pz + 18.0f;
    float lookX = map5_px;
    float lookY = 2.0f;
    float lookZ = map5_pz - 15.0f;
    gluLookAt(camX, camY, camZ, lookX, lookY, lookZ, 0, 1, 0);
}
void map5_resetGame()
{
    map5_px = 0; map5_pz = -5.0f;
    map5_playerSpeedX = 0;
    map5_eX  = 0;    map5_eZ  = -40.0f;
    map5_coinX = 0;  map5_coinZ = -30.0f;
    map5_showCoin = true;
    map5_score = 0;  map5_gameOver = false;
    map5_coinAngle = 0;
}
void map5_display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    map5_setup3DCamera();
    map5_light();
    glPushMatrix();
    glTranslatef(0, 0, map5_pz);
    map5_drawSky();
    glPopMatrix();

    map5_drawRoad();
    for (float z = -5.0f; z > -200.0f; z -= 12.0f)
        map5_drawTree(-4.5f, z);
    for (float z = -8.0f; z > -200.0f; z -= 10.0f)
        map5_drawTree( 4.5f, z);
    map5_drawCar(map5_px, 0.0f, map5_pz, 0.1f, 0.4f, 0.9f);
    map5_drawCar(map5_eX, 0.0f, map5_eZ, 1.0f, 0.1f, 0.1f);
    map5_drawCoin();
    map5_drawHUD();
    glDisable(GL_LIGHTING);
    glutSwapBuffers();
}
void map5_update(int value)
{
    if (!map5_gameOver) {
        map5_score++;
        map5_coinAngle += 4.0f;
        if (map5_coinAngle > 360) map5_coinAngle = 0;

        float enemySpeed = 1.2f;
        map5_eZ += enemySpeed;
        if (map5_eZ > map5_pz + 8) {
            map5_eZ = map5_pz - 60 - (rand() % 30);
            map5_eX = map5_lanes[rand() % 3];
        }
        map5_coinZ += enemySpeed * 0.9f;
        if (map5_coinZ > map5_pz + 8) {
            map5_coinZ = map5_pz - 40;
            map5_coinX = map5_lanes[rand() % 3];
            map5_showCoin = true;
        }
        if (map5_showCoin &&
            fabsf(map5_coinZ - map5_pz) < 1.5f &&
            fabsf(map5_coinX - map5_px) < 1.2f) {
            map5_score += 10;
            map5_showCoin = false;
        }
        map5_px += map5_playerSpeedX * map5_playerSpeed;
        map5_pz -= map5_playerSpeed;
        if (map5_px < -1.5f) map5_px = -1.5f;
        if (map5_px >  1.5f) map5_px =  1.5f;
        if (fabsf(map5_eZ - map5_pz) < 2.2f &&
            fabsf(map5_eX - map5_px) < 1.0f)
            map5_gameOver = true;
    }

    glutPostRedisplay();
}

void map5_keyboard(unsigned char key, int x, int y)
{
    if (map5_gameOver && (key == 'r' || key == 'R')) map5_resetGame();
    if (key == 27) exit(0);
}

void map5_specialKeys(int key, int x, int y)
{
    if (!map5_gameOver) {
        if (key == GLUT_KEY_LEFT)  map5_playerSpeedX = -1.0f;
        if (key == GLUT_KEY_RIGHT) map5_playerSpeedX =  1.0f;
    }
}
void map5_specialKeysUp(int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT || key == GLUT_KEY_RIGHT)
        map5_playerSpeedX = 0;
}
void map5_init()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.33, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    map5_resetGame();
}
