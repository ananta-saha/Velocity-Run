#include <GL/glut.h>
#include <stdio.h>
#include <stdbool.h>

float map3_px = 0, map3_py = 0, map3_pz = -5;
float map3_playerSpeed = 0;
struct EnemyCar {
    float x, z;
    int colorIndex;
};
EnemyCar map3_enemyCars[5];
float map3_carColors[8][3] = {
    {0.85f, 0.1f, 0.1f},  {0.1f, 0.1f, 0.85f},
    {0.1f, 0.85f, 0.1f},  {0.85f, 0.85f, 0.1f},
    {0.85f, 0.1f, 0.85f}, {0.1f, 0.85f, 0.85f},
    {0.7f, 0.3f, 0.1f},   {0.6f, 0.2f, 0.6f}
};
float map3_coinX = 0, map3_coinZ = -30;
bool map3_showCoin = true;
int map3_avoided = 0, map3_score = 0;
bool map3_gameOver = false;
float map3_roadOffset = 0.0f;
float map3_gameSpeed = 0.8f;

void map3_drawWheel() {
    glPushMatrix();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glColor3f(0.1f, 0.1f, 0.1f);
    glutSolidTorus(0.08f, 0.22f, 15, 20);
    glPopMatrix();
}

void map3_EnemyCars(int colorIndex) {
    float* carColor = map3_carColors[colorIndex];
    glPushMatrix();
    glScalef(0.7f, 0.7f, 0.7f);

    glBegin(GL_QUADS);
    glColor3fv(carColor);
    glVertex3f(-0.45f, 0.0f, 1.0f);
    glVertex3f( 0.45f, 0.0f, 1.0f);
    glVertex3f( 0.45f, 0.4f, 1.0f);
    glVertex3f(-0.45f, 0.4f, 1.0f);

    glVertex3f(-0.45f, 0.0f, -1.0f);
    glVertex3f( 0.45f, 0.0f, -1.0f);
    glVertex3f( 0.45f, 0.4f, -1.0f);
    glVertex3f(-0.45f, 0.4f, -1.0f);

    glVertex3f(-0.45f, 0.0f, -1.0f);
    glVertex3f(-0.45f, 0.0f,  1.0f);
    glVertex3f(-0.45f, 0.4f,  1.0f);
    glVertex3f(-0.45f, 0.4f, -1.0f);

    glVertex3f(0.45f, 0.0f, -1.0f);
    glVertex3f(0.45f, 0.0f,  1.0f);
    glVertex3f(0.45f, 0.4f,  1.0f);
    glVertex3f(0.45f, 0.4f, -1.0f);

    glVertex3f(-0.45f, 0.4f, -1.0f);
    glVertex3f( 0.45f, 0.4f, -1.0f);
    glVertex3f( 0.45f, 0.4f,  1.0f);
    glVertex3f(-0.45f, 0.4f,  1.0f);

    glColor3f(0.6f, 0.8f, 1.0f);

    glVertex3f(-0.3f, 0.4f, 0.5f);
    glVertex3f( 0.3f, 0.4f, 0.5f);
    glVertex3f( 0.3f, 0.8f, 0.5f);
    glVertex3f(-0.3f, 0.8f, 0.5f);

    glVertex3f(-0.3f, 0.4f, -0.5f);
    glVertex3f(-0.3f, 0.4f,  0.5f);
    glVertex3f(-0.3f, 0.8f,  0.5f);
    glVertex3f(-0.3f, 0.8f, -0.5f);

    glVertex3f(-0.3f, 0.8f, -0.5f);
    glVertex3f( 0.3f, 0.8f, -0.5f);
    glVertex3f( 0.3f, 0.8f,  0.5f);
    glVertex3f(-0.3f, 0.8f,  0.5f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(0.3f, 0.2f, 1.0f);
    glutSolidSphere(0.08f, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.3f, 0.2f, 1.0f);
    glutSolidSphere(0.08f, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5f, 0.0f, 0.7f);
    map3_drawWheel();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5f, 0.0f, 0.7f);
    map3_drawWheel();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5f, 0.0f, -0.7f);
    map3_drawWheel();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5f, 0.0f, -0.7f);
    map3_drawWheel();
    glPopMatrix();
    glPopMatrix();
}
void map3_PlayerBus() {
    glPushMatrix();
    glScalef(1.2f, 1.0f, 2.5f);
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 1.0f);

    glVertex3f(-0.45f, 0.0f, 1.0f);
    glVertex3f( 0.45f, 0.0f, 1.0f);
    glVertex3f( 0.45f, 0.6f, 1.0f);
    glVertex3f(-0.45f, 0.6f, 1.0f);

    glVertex3f(-0.45f, 0.0f, -1.0f);
    glVertex3f( 0.45f, 0.0f, -1.0f);
    glVertex3f( 0.45f, 0.6f, -1.0f);
    glVertex3f(-0.45f, 0.6f, -1.0f);

    glVertex3f(-0.45f, 0.0f, -1.0f);
    glVertex3f(-0.45f, 0.0f,  1.0f);
    glVertex3f(-0.45f, 0.6f,  1.0f);
    glVertex3f(-0.45f, 0.6f, -1.0f);

    glVertex3f(0.45f, 0.0f, -1.0f);
    glVertex3f(0.45f, 0.0f,  1.0f);
    glVertex3f(0.45f, 0.6f,  1.0f);
    glVertex3f(0.45f, 0.6f, -1.0f);

    glVertex3f(-0.45f, 0.6f, -1.0f);
    glVertex3f( 0.45f, 0.6f, -1.0f);
    glVertex3f( 0.45f, 0.6f,  1.0f);
    glVertex3f(-0.45f, 0.6f,  1.0f);

    glVertex3f(-0.45f, 0.0f, -1.0f);
    glVertex3f( 0.45f, 0.0f, -1.0f);
    glVertex3f( 0.45f, 0.0f,  1.0f);
    glVertex3f(-0.45f, 0.0f,  1.0f);

    glColor3f(0.7f, 0.9f, 1.0f);
    glVertex3f(-0.30f, 0.25f, 1.01f);
    glVertex3f( 0.30f, 0.25f, 1.01f);
    glVertex3f( 0.22f, 0.55f, 1.01f);
    glVertex3f(-0.22f, 0.55f, 1.01f);

    for(float z = -0.6f; z <= 0.6f; z += 0.3f) {
        glVertex3f(-0.451f, 0.25f, z);
        glVertex3f(-0.451f, 0.25f, z + 0.18f);
        glVertex3f(-0.451f, 0.50f, z + 0.18f);
        glVertex3f(-0.451f, 0.50f, z);

        glVertex3f(0.451f, 0.25f, z);
        glVertex3f(0.451f, 0.25f, z + 0.18f);
        glVertex3f(0.451f, 0.50f, z + 0.18f);
        glVertex3f(0.451f, 0.50f, z);
    }
    glEnd();
    glColor3f(1.0f, 1.0f, 0.8f);
    glPushMatrix();
    glTranslatef(0.25f, 0.15f, 1.05f);
    glutSolidSphere(0.06f, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.25f, 0.15f, 1.05f);
    glutSolidSphere(0.06f, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.55f, 0.0f, 0.75f);
    map3_drawWheel();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.55f, 0.0f, 0.75f);
    map3_drawWheel();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.55f, 0.0f, -0.75f);
    map3_drawWheel();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.55f, 0.0f, -0.75f);
    map3_drawWheel();
    glPopMatrix();
    glPopMatrix();
}

void map3_Sky() {
    glDisable(GL_DEPTH_TEST);
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.2f, 0.25f);
    glVertex3f(-200.0f, 100.0f, -200.0f);
    glVertex3f(200.0f, 100.0f, -200.0f);
    glColor3f(0.4f, 0.4f, 0.5f);
    glVertex3f(200.0f, -5.0f, -200.0f);
    glVertex3f(-200.0f, -5.0f, -200.0f);
    glEnd();
    glEnable(GL_DEPTH_TEST);
}

void map3_Road() {
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex3f(-4.0f, -1.0f, 5.0f);
    glVertex3f(4.0f, -1.0f, 5.0f);
    glVertex3f(4.0f, -1.0f, -200.0f);
    glVertex3f(-4.0f, -1.0f, -200.0f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    for(float z = 5 + map3_roadOffset; z > -200; z -= 10) {
        glBegin(GL_QUADS);
            glVertex3f(-0.15f, -0.99f, z);
            glVertex3f(0.15f, -0.99f, z);
            glVertex3f(0.15f, -0.99f, z-5);
            glVertex3f(-0.15f, -0.99f, z-5);
        glEnd();
    }
}

void map3_Grass() {
    glColor3f(0.1f, 0.5f, 0.1f);
    glBegin(GL_QUADS);
    glVertex3f(-20.0f, -1.1f, 5.0f);
    glVertex3f(-4.0f, -1.1f, 5.0f);
    glVertex3f(-4.0f, -1.1f, -200.0f);
    glVertex3f(-20.0f, -1.1f, -200.0f);

    glVertex3f(4.0f, -1.1f, 5.0f);
    glVertex3f(20.0f, -1.1f, 5.0f);
    glVertex3f(20.0f, -1.1f, -200.0f);
    glVertex3f(4.0f, -1.1f, -200.0f);
    glEnd();
}

void map3_Water() {
    glColor3f(0.2f, 0.6f, 1.0f);
    glBegin(GL_QUADS);
        glVertex3f(-8.0f, -0.9f, 5.0f);
        glVertex3f(-6.0f, -0.9f, 5.0f);
        glVertex3f(-6.0f, -0.9f, -200.0f);
        glVertex3f(-8.0f, -0.9f, -200.0f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3f(6.0f, -0.9f, 5.0f);
        glVertex3f(8.0f, -0.9f, 5.0f);
        glVertex3f(8.0f, -0.9f, -200.0f);
        glVertex3f(6.0f, -0.9f, -200.0f);
    glEnd();
}

void map3_Tree(){
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -20.0f);

    glColor3f(0.45f, 0.25f, 0.15f);
    glPushMatrix();
    glTranslatef(0.0f, 1.2f, 0.0f);
    glScalef(0.25f, 2.4f, 0.25f);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.15f, 0.55f, 0.2f);
    glPushMatrix();
    glTranslatef(0.0f, 3.5f, 0.0f);
    glutSolidSphere(1.5f, 16, 16);
    glPopMatrix();

    glPopMatrix();
}

void map3_Wall(float x) {
    float colors[][3] = {{0.7f, 0.3f, 0.3f},{0.3f, 0.6f, 0.8f},{0.4f, 0.7f, 0.4f},{0.7f, 0.6f, 0.3f},{0.6f, 0.4f, 0.7f}};
    int i = 0;
    glBegin(GL_QUADS);
    for(float z = 0; z > -200; z -= 10) {
        int c = i % 5;
        glColor3f(colors[c][0], colors[c][1], colors[c][2]);

        glVertex3f(x-1.5f, 0, z+3);
        glVertex3f(x+1.5f, 0, z+3);
        glVertex3f(x+1.5f, 8, z+3);
        glVertex3f(x-1.5f, 8, z+3);

        glVertex3f(x-1.5f, 0, z-3);
        glVertex3f(x+1.5f, 0, z-3);
        glVertex3f(x+1.5f, 8, z-3);
        glVertex3f(x-1.5f, 8, z-3);

        glVertex3f(x-1.5f, 0, z-3);
        glVertex3f(x-1.5f, 0, z+3);
        glVertex3f(x-1.5f, 8, z+3);
        glVertex3f(x-1.5f, 8, z-3);

        glVertex3f(x+1.5f, 0, z-3);
        glVertex3f(x+1.5f, 0, z+3);
        glVertex3f(x+1.5f, 8, z+3);
        glVertex3f(x+1.5f, 8, z-3);

        glVertex3f(x-1.5f, 8, z-3);
        glVertex3f(x+1.5f, 8, z-3);
        glVertex3f(x+1.5f, 8, z+3);
        glVertex3f(x-1.5f, 8, z+3);

        glVertex3f(x-1.5f, 0, z-3);
        glVertex3f(x+1.5f, 0, z-3);
        glVertex3f(x+1.5f, 0, z+3);
        glVertex3f(x-1.5f, 0, z+3);

        glColor3f(1.0f, 1.0f, 0.7f);
        for(float y = 2; y < 7; y += 2) {
            glVertex3f(x-0.3f, y-0.4f, z+3.1f);
            glVertex3f(x+0.3f, y-0.4f, z+3.1f);
            glVertex3f(x+0.3f, y+0.4f, z+3.1f);
            glVertex3f(x-0.3f, y+0.4f, z+3.1f);

            glVertex3f(x-1.6f, y-0.4f, z-0.3f);
            glVertex3f(x-1.6f, y-0.4f, z+0.3f);
            glVertex3f(x-1.6f, y+0.4f, z+0.3f);
            glVertex3f(x-1.6f, y+0.4f, z-0.3f);

            glVertex3f(x+1.6f, y-0.4f, z-0.3f);
            glVertex3f(x+1.6f, y-0.4f, z+0.3f);
            glVertex3f(x+1.6f, y+0.4f, z+0.3f);
            glVertex3f(x+1.6f, y+0.4f, z-0.3f);
        }i++;
    }
    glEnd();
}

void map3_Text(float x, float y, const char* str) {
    glRasterPos2f(x, y);
    for(int i = 0; str[i]; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
}

void map3_HUD() {
    char text[50];
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, 1024, 0, 768);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    sprintf(text, "Score: %d", map3_score);
    map3_Text(20, 730, text);
    sprintf(text, "Avoided: %d", map3_avoided);
    map3_Text(20, 700, text);
    if (map3_gameOver) {
        glColor3f(1.0f, 0.0f, 0.0f);
        map3_Text(450, 400,"GAME OVER");
        map3_Text(420, 360,"Press R to Restart");
    }
}
void map3_update(int value) {
    if (map3_gameOver)
        return;
    map3_roadOffset += map3_gameSpeed;

    if (map3_roadOffset > 10)
        map3_roadOffset = 0;
    for (int i = 0; i < 5; i++) {
        map3_enemyCars[i].z += 0.8f;
        if (map3_enemyCars[i].z > 5) {
            map3_enemyCars[i].z = -60;
            map3_enemyCars[i].x = (rand() % 3 - 1) * 2.0f;
            map3_avoided++;
        }
        if (map3_enemyCars[i].z > map3_pz - 1.5f && map3_enemyCars[i].z < map3_pz + 1.5f && map3_enemyCars[i].x > map3_px - 1.2f && map3_enemyCars[i].x < map3_px + 1.2f && map3_py < 0.5f) {
            map3_gameOver = true;
        }
    }
    map3_coinZ += 0.8f;
    if (map3_coinZ > 5) {
        map3_coinZ = -40;
        map3_coinX = (rand() % 3 - 1) * 2.0f;
        map3_showCoin = true;
}
    if (map3_showCoin && map3_coinZ > map3_pz - 1.5f && map3_coinZ < map3_pz + 1.5f && map3_coinX > map3_px - 1.2f && map3_coinX < map3_px + 1.2f) {
        map3_score += 10;
        map3_showCoin = false;
}
    map3_px += map3_playerSpeed;
    if (map3_px < -2.5f)
        map3_px = -2.5f;
    if (map3_px > 2.5f)
        map3_px = 2.5f;
}

void map3_display() {
    glClear(GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 7, 15, 0, 0, -20, 0, 1, 0);

    map3_Sky();
    map3_Grass();
    map3_Water();
    map3_Road();

    glPushMatrix();
    glTranslatef(0, 0, map3_roadOffset);
    for(float z = 10; z > -200; z -= 8) {
        glPushMatrix();
        glTranslatef(-10, 0, z);
        map3_Tree();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(10, 0, z);
        map3_Tree();
        glPopMatrix();
    }
    map3_Wall(-14);
    map3_Wall(14);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(map3_px, map3_py, map3_pz);
    map3_PlayerBus();
    glPopMatrix();

    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        glTranslatef(map3_enemyCars[i].x, 0, map3_enemyCars[i].z);
        map3_EnemyCars(map3_enemyCars[i].colorIndex);
        glPopMatrix();
    }

    if (map3_showCoin) {
        glColor3f(1, 0.8, 0);
        glPushMatrix();
        glTranslatef(map3_coinX, 1.2f, map3_coinZ);
        glutSolidSphere(0.4, 20, 20);
        glPopMatrix();
    }
    map3_HUD();
    glutSwapBuffers();
}

void map3_keyboard(unsigned char key, int x, int y) {
    if (key == 'a') {map3_playerSpeed = -0.15f;}
    if (key == 'd') {map3_playerSpeed = 0.15f;}
    if (key == 'r') {
        map3_gameOver = false;
        map3_score = 0;
        map3_avoided = 0;
        map3_pz = -5;
        map3_px = 0;
        map3_py = 0;
        for (int i = 0; i < 5; i++) {
            map3_enemyCars[i].z = -50 - (i * 20);
            map3_enemyCars[i].x = 0;
        }
    }
}

void map3_keyboardUp(unsigned char key, int x, int y) {
    if (key == 'a' || key == 'd') map3_playerSpeed = 0;
}

void map3_init() {
    glClearColor(0.5f, 0.8f, 1.0f, 1);
    gluPerspective(45, 1.33, 1, 500);

    for (int i = 0; i < 5; i++) {
        map3_enemyCars[i].z = -50 - i * 20;
        map3_enemyCars[i].colorIndex = rand() % 8;
    }
}
