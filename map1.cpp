#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float carX=0.0f;
float targetCarX=0.0f;
float laneMoveSpeed= 0.18f;
float speed=0.6f;
int score= 0;
bool gameOver=false;
float enemyCarX[3];
float enemyCarZ[3];
float enemyCarSpeed[3];
float coinX=0.0f;
float coinZ= -30.0f;
bool coinActive =true;
float roadOffset= 0.0f;
float buildingZ[20];
float buildingHeight[20];
int buildingType[20];

void init1() {
    glClearColor(0.5f, 0.7f, 1.0f, 1.0f);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    GLfloat lightPos[] = {0.0f,20.0f,20.0f,0.0f};
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    GLfloat ambient[] = {0.6f,0.6f,0.6f,1.0f};
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
    GLfloat diffuse[]={0.9f,0.9f,0.9f,1.0f};
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
    carX=0.0f;
    targetCarX =0.0f;
    score=0;
    gameOver=false;
    speed=0.6f;
    for (int i=0;i<3;i++){
        enemyCarZ[i] =-40.0f-(i * 30.0f);
        int lane=rand()%3;
        if(lane==0){
            enemyCarX[i]=-2.5f;
        }
        if(lane==1){
           enemyCarX[i]=0.0f;
        }
        if(lane==2) {
            enemyCarX[i]=2.5f;
        }

        enemyCarSpeed[i]=0.2f +((rand()%10)/100.0f);
    }
    for (int i=0;i<20;i++) {
        buildingZ[i]= -100.0f+(i*6.0f);
        buildingHeight[i]=3.0f+(rand()%6);
        buildingType[i]=rand()%3;
    }
    coinZ=-25.0f;
    coinX=0.0f;
    coinActive=true;
}
void drawText(float x, float y, const char* text) {
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0,800,0,600);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2f(x, y);
    for(int i=0;text[i]!='\0';i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LIGHTING);
}
void drawCar(float r, float g, float b){
    glColor3f(r, g, b);
    glPushMatrix();
    glTranslatef(0.0f, 0.50f, 0.0f);
    glScalef(1.35f, 0.45f, 2.8f);
    glutSolidCube(1.0);
    glPopMatrix();


    glColor3f(r*0.9f,g*0.9f,b*0.9f);
    glPushMatrix();
    glTranslatef(0.0f,0.88f,0.15f);
    glScalef(1.05f,0.30f,1.5f);
    glutSolidCube(1.0);
    glPopMatrix();


    glColor3f(0.03f,0.03f,0.03f);
    glPushMatrix();
    glTranslatef(0.0f,1.08f,0.15f);
    glScalef(0.95f,0.06f,1.2f);
    glutSolidCube(1.0);
    glPopMatrix();


    glColor3f(0.12f,0.12f,0.15f);
    glPushMatrix();
    glTranslatef(0.0f,0.86f,-0.48f);
    glScalef(0.9f, 0.18f, 0.08f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f,0.86f,0.85f);
    glScalef(0.85f,0.16f,0.08f);
    glutSolidCube(1.0);
    glPopMatrix();


    glColor3f(0.15f,0.15f,0.18f);
    glPushMatrix();
    glTranslatef(-0.53f, 0.86f, 0.15f);
    glScalef(0.04f, 0.16f, 1.0f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.53f, 0.86f, 0.15f);
    glScalef(0.04f, 0.16f, 1.0f);
    glutSolidCube(1.0);
    glPopMatrix();


    glColor3f(0.08f, 0.08f, 0.08f);
    glPushMatrix();
    glTranslatef(0.0f, 0.42f, -1.42f);
    glScalef(1.15f, 0.12f, 0.08f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f,0.42f,1.42f);
    glScalef(1.15f, 0.12f, 0.08f);
    glutSolidCube(1.0);
    glPopMatrix();


    glColor3f(0.0f,0.0f,0.0f);
    glPushMatrix();
    glTranslatef(0.0f, 0.60f, -1.39f);
    glScalef(0.55f, 0.12f, 0.05f);
    glutSolidCube(1.0);
    glPopMatrix();


    glColor3f(1.0f, 1.0f, 0.75f);
    glPushMatrix();
    glTranslatef(-0.42f, 0.60f, -1.38f);
    glScalef(0.22f, 0.12f, 0.08f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.42f, 0.60f, -1.38f);
    glScalef(0.22f, 0.12f, 0.08f);
    glutSolidCube(1.0);
    glPopMatrix();



    glColor3f(1.0f, 0.0f,0.0f);
    glPushMatrix();
    glTranslatef(-0.42f,0.58f, 1.38f);
    glScalef(0.20f, 0.10f, 0.08f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.42f,0.58f,1.38f);
    glScalef(0.20f, 0.10f,0.08f);
    glutSolidCube(1.0);
    glPopMatrix();



    glColor3f(0.08f, 0.08f, 0.08f);
    glPushMatrix();
    glTranslatef(-0.68f,0.32f,-0.95f);
    glRotatef(90.0f,0.0f,1.0f,0.0f);
    glutSolidTorus(0.10, 0.22, 12, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.68f, 0.32f, -0.95f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glutSolidTorus(0.10, 0.22, 12, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.68f, 0.32f, 0.95f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glutSolidTorus(0.10, 0.22, 12, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.68f, 0.32f, 0.95f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glutSolidTorus(0.10, 0.22, 12, 20);
    glPopMatrix();
}
void drawRoad() {
    glColor3f(0.2f, 0.55f, 0.2f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);

    glVertex3f(-20.0f, 0.0f, -100.0f);
    glVertex3f(-6.0f, 0.0f, -100.0f);
    glVertex3f(-6.0f, 0.0f, 20.0f);
    glVertex3f(-20.0f, 0.0f, 20.0f);

    glVertex3f(6.0f, 0.0f, -100.0f);
    glVertex3f(20.0f, 0.0f, -100.0f);
    glVertex3f(20.0f, 0.0f, 20.0f);
    glVertex3f(6.0f, 0.0f, 20.0f);
    glEnd();


    glColor3f(0.55f, 0.55f, 0.55f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-6.0f, 0.01f, -100.0f);
    glVertex3f(-4.5f, 0.01f, -100.0f);
    glVertex3f(-4.5f, 0.01f, 20.0f);
    glVertex3f(-6.0f, 0.01f, 20.0f);

    glVertex3f(4.5f, 0.01f, -100.0f);
    glVertex3f(6.0f, 0.01f, -100.0f);
    glVertex3f(6.0f, 0.01f, 20.0f);
    glVertex3f(4.5f, 0.01f, 20.0f);
    glEnd();


    glColor3f(0.28f, 0.28f, 0.28f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-4.5f, 0.02f, -100.0f);
    glVertex3f(4.5f, 0.02f, -100.0f);
    glVertex3f(4.5f, 0.02f, 20.0f);
    glVertex3f(-4.5f, 0.02f, 20.0f);
    glEnd();



    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-4.5f, 0.03f, -100.0f);
    glVertex3f(-4.3f, 0.03f, -100.0f);
    glVertex3f(-4.3f, 0.03f, 20.0f);
    glVertex3f(-4.5f, 0.03f, 20.0f);

    glVertex3f(4.3f, 0.03f, -100.0f);
    glVertex3f(4.5f, 0.03f, -100.0f);
    glVertex3f(4.5f, 0.03f, 20.0f);
    glVertex3f(4.3f, 0.03f, 20.0f);
    glEnd();

    glColor3f(1.0f, 1.0f,1.0f);
    for(float z=-100.0f;z< 20.0f;z+=6.0f) {
        glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-0.08f, 0.04f, z);
        glVertex3f(0.08f, 0.04f, z);
        glVertex3f(0.08f, 0.04f, z + 3.0f);
        glVertex3f(-0.08f, 0.04f, z + 3.0f);
        glEnd();

        glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-1.5f, 0.04f, z);
        glVertex3f(-1.35f, 0.04f, z);
        glVertex3f(-1.35f, 0.04f, z + 3.0f);
        glVertex3f(-1.5f, 0.04f, z + 3.0f);
        glEnd();

        glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(1.35f, 0.04f, z);
        glVertex3f(1.5f, 0.04f, z);
        glVertex3f(1.5f, 0.04f, z + 3.0f);
        glVertex3f(1.35f, 0.04f, z + 3.0f);
        glEnd();
    }
}
void drawSun(){
    glPushMatrix();
    glTranslatef(-5.0f, 50.0f, -150.0f);
    glColor3f(1.0f, 0.9f, 0.0f);
    glutSolidSphere(6.0f, 40, 40);
    glPopMatrix();
}
void drawClouds(){
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();

    glTranslatef(-12.0f, 14.0f, -40.0f);
    glutSolidSphere(1.8f, 20, 20);
    glTranslatef(2.0f, 0.3f, 0.0f);
    glutSolidSphere(2.0f,20,20);
    glTranslatef(2.0f,-0.2f,0.0f);
    glutSolidSphere(1.6f, 20, 20);
    glTranslatef(1.5f,-0.1f,0.0f);
    glutSolidSphere(1.3f,20,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10.0f, 16.0f, -55.0f);
    glutSolidSphere(1.5f, 20,20);
    glTranslatef(1.8f, 0.2f,0.0f);
    glutSolidSphere(1.9f,20,20);
    glTranslatef(1.8f,-0.1f,0.0f);
    glutSolidSphere(1.4f,20,20);
    glPopMatrix();
}
void drawBuildings(){
    for (int i=0;i<20;i++){

        if(buildingType[i]== 0){
        glColor3f(0.45f, 0.45f, 0.75f);
}
        else if(buildingType[i]==1){
        glColor3f(0.75f, 0.45f, 0.45f);
    }
        else{
    glColor3f(0.35f, 0.35f, 0.35f);
    }
        glPushMatrix();
        glTranslatef(-7.5f,buildingHeight[i]/2.0f,buildingZ[i]);
        glScalef(3.0f, buildingHeight[i],3.0f);
        glutSolidCube(1.0);
        glPopMatrix();

        glColor3f(1.0f, 0.9f, 0.2f);
        for (float wy =1.0f;wy<buildingHeight[i]-1.0f;wy += 1.5f) {
            for (float wx= -0.5f;wx<=0.5f;wx+=0.5f){
                glPushMatrix();
                glTranslatef(-6.0f, wy, buildingZ[i] + wx);
                glScalef(0.1f, 0.5f, 0.3f);
                glutSolidCube(1.0);
                glPopMatrix();
            }
        }
        if (buildingType[i] ==0) {
            glColor3f(0.6f, 0.6f, 0.7f);
        } else if (buildingType[i]== 1) {
            glColor3f(0.7f, 0.5f, 0.5f);
        } else {
            glColor3f(0.5f, 0.5f, 0.5f);
        }
        glPushMatrix();
        glTranslatef(7.5f, buildingHeight[i] / 2.0f, buildingZ[i]);
        glScalef(3.0f, buildingHeight[i], 3.0f);
        glutSolidCube(1.0);
        glPopMatrix();

        glColor3f(1.0f,0.9f,0.2f);
        for (float wy=1.0f;wy< buildingHeight[i] - 1.0f;wy += 1.5f) {
            for (float wx = -0.5f; wx <= 0.5f; wx += 0.5f) {
                glPushMatrix();
                glTranslatef(6.0f,wy,buildingZ[i]+wx);
                glScalef(0.1f,0.5f,0.3f);
                glutSolidCube(1.0);
                glPopMatrix();
            }
        }
    }
}
void drawEnemies(){
    for (int i=0;i<3;i++){
        glPushMatrix();
        glTranslatef(enemyCarX[i], 0.0f, enemyCarZ[i]);
        glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
        glScalef(0.8f, 0.8f, 0.8f);
        drawCar(0.6f, 0.2f, 0.8f);
        glPopMatrix();
    }
}
void drawCoin(){
    if (coinActive){
        glPushMatrix();
        glTranslatef(coinX, 0.8f, coinZ);
        glColor3f(1.0f, 0.8f, 0.0f);
        glutSolidSphere(0.4, 15, 15);
        glPopMatrix();
    }
}
void display1(){
    glClearColor(0.45f, 0.65f, 0.95f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    drawSun();
    drawClouds();
    gluLookAt(0.0, 4.5, 7.5,0.0, 0.0, -10.0,0.0, 1.0, 0.0);
    drawRoad();
    drawBuildings();
    drawEnemies();
    drawCoin();
    glPushMatrix();
    glTranslatef(carX, 0.0f, 0.0f);
    glScalef(0.8f, 0.8f, 0.8f);
    drawCar(0.1f, 0.3f, 0.9f);
    glPopMatrix();
    char buffer[50];
    if (gameOver) {
        glColor3f(1.0f, 0.0f, 0.0f);
        drawText(350,350,"GAME OVER");
        sprintf(buffer, "Final Score: %d", score);
        drawText(340,310,buffer);
        drawText(320,270,"Press 'R' to Restart");
    }
    else {
        glColor3f(1.0f,1.0f, 1.0f);
        sprintf(buffer, "Score: %d", score);
        drawText(20, 560, buffer);
        char speedText[50];
int displaySpeed = (int)(speed * 120);
sprintf(speedText, "Speed: %d km/h", displaySpeed);
drawText(620, 560, speedText);
}

    glutSwapBuffers();
}
void update1(int value) {
    if (!gameOver) {

    if (carX < targetCarX) {
    carX += laneMoveSpeed;
    if (carX > targetCarX)
    {
        carX =targetCarX;
    }
}

if(carX>targetCarX)
{
    carX -=laneMoveSpeed;
    if(carX<targetCarX)
    {
        carX=targetCarX;
    }
}
        roadOffset +=speed;
        if(roadOffset>4.0f)
        {
            roadOffset-=4.0f;
        }
        for(int i=0;i<20;i++){
            buildingZ[i] += speed;

            if(buildingZ[i]>10.0f) {
                buildingZ[i]-= 120.0f;
                buildingHeight[i]= 3.0f + (rand() % 6);
                buildingType[i]=rand() % 3;
            }
        }
        for(int i=0;i<3;i++) {
            enemyCarZ[i] += speed + enemyCarSpeed[i];

            if(enemyCarZ[i]>10.0f){
                enemyCarZ[i]=-80.0f - (rand() % 40);

                int lane = rand() % 3;
                if (lane==0)
                {
                     enemyCarX[i]=-2.5f;
                }
                if (lane==1){
                   enemyCarX[i]=0.0f;
                }
                if (lane==2) {
                   enemyCarX[i]=2.5f;
                }

                score += 1;
            }
            if (fabs(enemyCarZ[i]-0.0f)<1.5f && fabs(enemyCarX[i]-carX)<1.2f) {
                gameOver = true;
            }
        }
        coinZ += speed;
        if (coinZ > 10.0f) {
            coinZ = -50.0f - (rand() % 50);

            int lane = rand() % 3;
            if (lane == 0){
               coinX = -2.5f;
            }
            if (lane == 1){
              coinX = 0.0f;
            }
            if (lane == 2){
                coinX = 2.5f;
            }

            coinActive = true;
        }

        if (coinActive && fabs(coinZ - 0.0f) < 2.0f && fabs(coinX - carX) < 1.5f) {
            score += 10;
            coinActive = false;
            speed += 0.02f;
        }
    }

    glutPostRedisplay();
}
void keyboard1(unsigned char key, int x, int y) {
    if (!gameOver)
        {
       if (key == 'a' || key == 'A') {
        if (targetCarX > -2.5f)
        targetCarX -= 2.5f;
}

if (key == 'd' || key == 'D') {

    if (targetCarX < 2.5f)
        targetCarX += 2.5f;
}
       }

    if (key == 'r' || key == 'R') {
        init1();
    }

    if (key == 27) {
        exit(0);
    }
}
