#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float map4_absVal(float x)
{
    if (x < 0)
    {
        x = -x;
    }
    return x;
}

float map4_px = 0;
float map4_pz = -5;
float map4_playerSpeedX = 0;

float map4_basePlayerSpeed = 0.15f;
float map4_currentPlayerSpeed = 0.15f;
float map4_gameTime = 0;

#define MAX_ENEMY_CARS 3
struct EnemyCar {
    float x, z;
    int lane;
};
EnemyCar map4_enemyCars[MAX_ENEMY_CARS];

float map4_roadLanes[3] = {-1.5f, 0.0f, 1.5f};
float map4_coinX = 0;
float map4_coinZ = -30;
bool map4_showCoin = true;
int map4_score = 0;
bool map4_gameOver = false;

struct Bird
{
    float x;
    float y;
    float z;
    float speed;
};
Bird map4_birds[4];

void map4_drawTree(float x, float z);
void map4_setup3DCamera();

void map4_drawBox(float x, float y, float z, float width, float height, float length) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(width, height, length);
    glutSolidCube(1.0);
    glPopMatrix();
}
void map4_drawWheel(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix();
    glScalef(0.15f, 0.44f, 0.44f);
    glutSolidCube(1.0);
    glPopMatrix();
    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix();
    glScalef(0.16f, 0.25f, 0.25f);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();
}
void simple_drawBox(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glutSolidCube(1.0f);
    glPopMatrix();
}
void map4_drawEnemyCar() {
    glPushMatrix();
    glScalef(0.7f, 0.7f, 0.7f);
    glColor3f(0.1f, 0.1f, 0.1f);
    simple_drawBox(0.0f, 0.2f, 0.0f);
    glColor3f(0.95f, 0.95f, 0.95f);
    simple_drawBox(0.0f, 0.45f, -0.05f);
    glColor3f(0.0f, 0.0f, 1.0f);
    simple_drawBox(0.15f, 0.68f, -0.05f);
    glColor3f(1.0f, 0.0f, 0.0f);
    simple_drawBox(-0.15f, 0.68f, -0.05f);
    glPopMatrix();
}
void map4_drawPlayerCar() {
    float truckBlue[3] = {0.1f, 0.4f, 0.8f};
    float cargoGrey[3] = {0.7f, 0.7f, 0.7f};
    glPushMatrix();
    glScalef(1.1f, 1.1f, 1.1f);
    glColor3fv(truckBlue);
    simple_drawBox(0.0f, 0.2f, 0.0f);
    glColor3fv(truckBlue);
    simple_drawBox(0.0f, 0.6f, -0.7f);
    glColor4f(0.7f, 0.9f, 1.0f, 0.6f);
    simple_drawBox(0.0f, 0.65f, -1.11f);
    glColor3fv(cargoGrey);
    simple_drawBox(0.0f, 0.75f, 0.35f);
    glColor3f(1.0f, 1.0f, 0.8f);
    glPushMatrix(); glTranslatef(0.38f, 0.35f, -1.15f); glutSolidSphere(0.08f, 16, 16); glPopMatrix();
    glPushMatrix(); glTranslatef(-0.38f, 0.35f, -1.15f); glutSolidSphere(0.08f, 16, 16); glPopMatrix();
    float wheelZ_front = -0.75f;
    float wheelZ_rear = 0.6f;
    float wheelX = 0.53f;
    float wheelY = 0.22f;

    map4_drawWheel(wheelX, wheelY, wheelZ_front);
    map4_drawWheel(-wheelX, wheelY, wheelZ_front);
    map4_drawWheel(wheelX, wheelY, wheelZ_rear);
    map4_drawWheel(-wheelX, wheelY, wheelZ_rear);

    glPopMatrix();
}
void map4_drawText(float x, float y, const char* str)
{
    glRasterPos2f(x, y);
    for (int i = 0; str[i]; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
    }
}
void map4_drawHUD()
{
    char buffer[100];
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 1024, 0, 768);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    glColor3f(0,0,0);
    sprintf(buffer, "Score: %d", map4_score);
    map4_drawText(20, 730, buffer);
    if (map4_gameOver)
    {
        glColor3f(1,0,0);
        map4_drawText(450, 400, "GAME OVER");
        map4_drawText(420, 360, "Press R to Restart");
        sprintf(buffer, "Final Score: %d", map4_score);
        map4_drawText(440, 330, buffer);
    }
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
void map4_drawSun()
{
    glPushMatrix();
    glTranslatef(-15.0f, 25.0f, -100.0f);
    glColor3f(1.0f, 0.6f, 0.3f);
    glLineWidth(1.2f);
    glBegin(GL_LINES);
    for (int i = 0; i < 16; i++) {
        float angle = i * (2.0f * 3.14159f / 16.0f);
        glVertex3f(0, 0, 0);
        glVertex3f(cos(angle) * 5.5f, sin(angle) * 5.5f, 0);
    }
    glEnd();
   glColor3f(1.0f, 0.7f, 0.4f);
    glutSolidSphere(4.0f, 16, 16);
    glPopMatrix();
}
void map4_drawBird(float x, float y, float z)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    float flap = sin(glutGet(GLUT_ELAPSED_TIME) * 0.01f) * 0.4f;
    glColor3f(0.1f, 0.1f, 0.1f);
    glLineWidth(2.5f);
    glBegin(GL_LINE_STRIP);
        glVertex3f(-0.7f, 0.0f + flap, 0);
        glVertex3f(-0.3f, 0.3f, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0.3f, 0.3f, 0);
        glVertex3f(0.7f, 0.0f + flap, 0);
    glEnd();
    glPopMatrix();
}
void map4_drawSky()
{
    glDisable(GL_DEPTH_TEST);
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.7f, 0.8f);
        glVertex3f(-200, 100, -200);
        glVertex3f( 200, 100, -200);
        glColor3f(1.0f, 0.85f, 0.6f);
        glVertex3f( 200, -5, -200);
        glVertex3f(-200, -5, -200);
    glEnd();
    map4_drawSun();
    for (int i = 0; i < 4; i++)
    {
        map4_drawBird(map4_birds[i].x, map4_birds[i].y, map4_birds[i].z);
    }
    glEnable(GL_DEPTH_TEST);
}
void map4_drawRoad() {
    glPushMatrix();
    float roadOffset = floor(map4_pz / 20.0f) * 20.0f;
    glTranslatef(0, 0, roadOffset);
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_QUADS);
        glVertex3f(-4, -1, 100);
        glVertex3f( 4, -1, 100);
        glVertex3f( 4, -1, -100);
        glVertex3f(-4, -1, -100);
    glEnd();
    glColor3f(1, 1, 1);
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
void map4_drawGrass() {
    glPushMatrix();
    float roadOffset = floor(map4_pz / 20.0f) * 20.0f;
    glTranslatef(0, 0, roadOffset);
    glColor3f(0.2f, 0.8f, 0.2f);
    glBegin(GL_QUADS);
        glVertex3f(-20, -1.1, 100);
        glVertex3f(-4, -1.1, 100);
        glVertex3f(-4, -1.1, -100);
        glVertex3f(-20, -1.1, -100);
        glVertex3f(4, -1.1, 100);
        glVertex3f(20, -1.1, 100);
        glVertex3f(20, -1.1, -100);
        glVertex3f(4, -1.1, -100);
    glEnd();
    glPopMatrix();
}
void map4_drawThinGrassPath()
{
    glColor3f(0.25f, 0.85f, 0.25f);
    glBegin(GL_QUADS);
        glVertex3f(-4.5f, -0.95f,    5.0f);
        glVertex3f(-4.0f, -0.95f,    5.0f);
        glVertex3f(-4.0f, -0.95f, -200.0f);
        glVertex3f(-4.5f, -0.95f, -200.0f);
        glVertex3f( 4.0f, -0.95f,    5.0f);
        glVertex3f( 6.0f, -0.95f,    5.0f);
        glVertex3f( 6.0f, -0.95f, -200.0f);
        glVertex3f( 4.0f, -0.95f, -200.0f);
    glEnd();
    for (float z = -5.0f; z > -200.0f; z -= 12.0f)
    {
        map4_drawTree(-4.25f, z);
    }
    for (float z = -8.0f; z > -200.0f; z -= 10.0f)
    {
        map4_drawTree(5.0f, z);
    }
}
void map4_drawTree(float x, float z)
{
    glColor3f(0.55f, 0.27f, 0.07f);
    map4_drawBox(x, 1.0f, z, 0.3f, 2.0f, 0.3f);
    glColor3f(0.1f, 0.7f, 0.2f);
    map4_drawBox(x, 3.0f, z, 2.4f, 2.0f, 2.0f);
    map4_drawBox(x + 0.8f, 3.2f, z, 2.0f, 1.6f, 1.6f);
    map4_drawBox(x - 0.8f, 3.2f, z, 2.0f, 1.6f, 1.6f);
    map4_drawBox(x, 3.5f, z + 0.5f, 2.2f, 1.8f, 1.8f);
}
void map4_drawBuildings()
{
    float x = -10.0f;
    float buildingColors[5][3] = {
        {0.8f, 0.6f, 0.6f},
        {0.6f, 0.8f, 0.8f},
        {0.6f, 0.8f, 0.6f},
        {0.8f, 0.8f, 0.6f},
        {0.7f, 0.6f, 0.8f}
    };
    int colorIndex = 0;
    for (float z = 0.0f; z > -200.0f; z -= 10.0f)
    {
        glColor3fv(buildingColors[colorIndex % 5]);
        map4_drawBox(x, 3.0f, z, 3.0f, 6.0f, 6.0f);
        glColor3f(1.0f, 1.0f, 0.7f);
        for (float y = 1.0f; y <= 5.0f; y += 1.0f)
        {
            for (float xi = -1.0f; xi <= 1.0f; xi += 1.0f)
            {
                map4_drawBox(x + xi, y, z + 3.0f, 0.4f, 0.5f, 0.1f);
            }
        }
        colorIndex++;
    }
}
void map4_drawCoin()
{
    if (!map4_showCoin) return;
    glPushMatrix();
    glTranslatef(map4_coinX, 1.2f, map4_coinZ);
    glColor3f(1.0f, 0.84f, 0.0f);
    glutSolidSphere(0.4f, 20, 20);
    glPopMatrix();
}
void map4_drawPlayer()
{
    glPushMatrix();
    glTranslatef(map4_px, 0.0f, map4_pz);
    map4_drawPlayerCar();
    glPopMatrix();
}
void map4_setup3DCamera()
{
    float camX = map4_px;
    float camY = 8.0f;
    float camZ = map4_pz + 18.0f;
    float lookX = map4_px;
    float lookY = 2.0f;
    float lookZ = map4_pz - 15.0f;
    gluLookAt(camX, camY, camZ, lookX, lookY, lookZ, 0, 1, 0);
}
void map4_resetGame()
{
    map4_score = 0;
    map4_gameTime = 0.0f;
    map4_gameOver = false;
    map4_px = 0.0f;
    map4_pz = 0.0f;
    map4_currentPlayerSpeed = map4_basePlayerSpeed;
    for (int i = 0; i < MAX_ENEMY_CARS; i++) {
        map4_enemyCars[i].z = map4_pz - 40 - (rand() % 30);
        map4_enemyCars[i].lane = rand() % 3;
        map4_enemyCars[i].x = map4_roadLanes[map4_enemyCars[i].lane];
    }
    map4_coinZ = map4_pz - 30;
    map4_showCoin = true;
}
void map4_update(int value)
{
    if (!map4_gameOver)
    {
        map4_score += 1;
        map4_currentPlayerSpeed = 0.25f;
        float enemySpeed = 1.2f;

        for (int i = 0; i < MAX_ENEMY_CARS; i++) {
            map4_enemyCars[i].z += enemySpeed;
            if (map4_enemyCars[i].z > 8) {
                map4_enemyCars[i].z = map4_pz - 60 - (rand() % 30);
                map4_enemyCars[i].lane = rand() % 3;
                map4_enemyCars[i].x = map4_roadLanes[map4_enemyCars[i].lane];
            }
           if (fabsf(map4_enemyCars[i].z - map4_pz) < 2.2f && fabsf(map4_enemyCars[i].x - map4_px) < 1.0f) {
                map4_gameOver = true;
            }
        }
        map4_coinZ += enemySpeed * 0.9f;
        if (map4_coinZ > 8) {
            map4_coinZ = map4_pz - 40;
            map4_coinX = map4_roadLanes[rand() % 3];
            map4_showCoin = true;
        }
        if (map4_showCoin && map4_absVal(map4_coinZ - map4_pz) < 1.5f && map4_absVal(map4_coinX - map4_px) < 1.2f) {
            map4_score += 10;
            map4_showCoin = false;
        }
        map4_px += map4_playerSpeedX * map4_currentPlayerSpeed;
        map4_pz -= map4_currentPlayerSpeed;
        if (map4_px < -3.5f) map4_px = -3.5f;
        if (map4_px > 3.5f)  map4_px = 3.5f;
        for (int i = 0; i < 4; i++) {
            map4_birds[i].x += map4_birds[i].speed * (1.0f + map4_gameTime * 0.0001f);
            if (map4_birds[i].x > 40) {
                map4_birds[i].x = -40;
                map4_birds[i].y = rand() % 5 + 15;
            }
        }
    }
    glutPostRedisplay();
}
void map4_keyboard(unsigned char key, int x, int y) {
    if (map4_gameOver && (key == 'r' || key == 'R')) map4_resetGame();
}
void map4_display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    map4_setup3DCamera();
    glPushMatrix();
    glTranslatef(0, 0, map4_pz);
    map4_drawSky();
    glPopMatrix();
    map4_drawRoad();
    map4_drawGrass();
    map4_drawThinGrassPath();
    map4_drawBuildings();
    map4_drawPlayer();
    for (int i = 0; i < MAX_ENEMY_CARS; i++) {
        glPushMatrix();
        glTranslatef(map4_enemyCars[i].x, 0, map4_enemyCars[i].z);
        map4_drawEnemyCar();
        glPopMatrix();
    }
    map4_drawCoin();
    map4_drawHUD();
    glutSwapBuffers();
}
void map4_specialKeys(int key, int x, int y) {
    if (!map4_gameOver) {
        if (key == GLUT_KEY_LEFT)  map4_playerSpeedX = -1.0f;
        if (key == GLUT_KEY_RIGHT) map4_playerSpeedX = 1.0f;
    }
}
void map4_specialKeysUp(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT || key == GLUT_KEY_RIGHT) map4_playerSpeedX = 0;
}
void map4_init()
{
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.33, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    for (int i = 0; i < 4; i++) {
        map4_birds[i].x = (rand() % 60) - 30;
        map4_birds[i].y = 15 + (rand() % 5);
        map4_birds[i].z = (rand() % 40) - 70;
        map4_birds[i].speed = 0.1f;
    }
    for (int i = 0; i < MAX_ENEMY_CARS; i++) {
        map4_enemyCars[i].lane = i % 3;
        map4_enemyCars[i].x = map4_roadLanes[map4_enemyCars[i].lane];
        map4_enemyCars[i].z = -50.0f - (i * 20.0f);
    }
    map4_gameTime = 0.0f;
    map4_currentPlayerSpeed = map4_basePlayerSpeed;
}
