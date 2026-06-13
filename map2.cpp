#include <windows.h>
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>

bool IsGameOver = false;
int PlayerScore = 0;
float DistanceTravel = 0.0f;
int CurrentEnvironment = 0;
float GameForwardSpeed = 1.0f;

bool IsLeftArrowPressed = false;
bool IsRightArrowPressed = false;
bool IsUpArrowPressed = false;
bool IsDownArrowPressed = false;

void DrawTextOnScreen(float PositionX, float PositionY,char* TextString) {
    glRasterPos2f(PositionX, PositionY);
    for (int i = 0; TextString[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, TextString[i]);
    }
}

void DrawTruck(float PositionX, float PositionY, float PositionZ,
               float R, float G, float B) {
    glPushMatrix();
    glTranslatef(PositionX, PositionY, PositionZ);

    glColor3f(R, G, B);
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
    glScalef(1.8f, 0.6f, 4.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glColor3f(R * 0.8f, G * 0.8f, B * 0.8f);
    glBegin(GL_TRIANGLES);

    glVertex3f(-0.9f, 1.1f, -0.5f);
    glVertex3f(-0.9f, 0.8f, -2.0f);
    glVertex3f(-0.9f, 0.8f,  2.0f);

    glVertex3f(0.9f, 1.1f, -0.5f);
    glVertex3f(0.9f, 0.8f, -2.0f);
    glVertex3f(0.9f, 0.8f,  2.0f);
    glEnd();

    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex3f(-0.9f, 0.8f, -2.0f);
    glVertex3f( 0.9f, 0.8f, -2.0f);
    glVertex3f( 0.9f, 1.1f, -0.5f);
    glVertex3f(-0.9f, 1.1f, -0.5f);
   glColor3f(0.1f, 0.1f, 0.1f);
    glVertex3f(-0.9f, 1.1f, -0.5f);
    glVertex3f( 0.9f, 1.1f, -0.5f);
    glVertex3f( 0.9f, 0.8f,  2.0f);
    glVertex3f(-0.9f, 0.8f,  2.0f);
    glEnd();

    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix();
     glTranslatef(-1.0f, 0.2f, -1.2f);
     glScalef(0.4f, 0.6f, 0.6f);
     glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
     glTranslatef( 1.0f, 0.2f, -1.2f);
     glScalef(0.4f, 0.6f, 0.6f);
     glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
     glTranslatef(-1.0f, 0.2f,  1.2f);
     glScalef(0.4f, 0.6f, 0.6f);
     glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
     glTranslatef( 1.0f, 0.2f,  1.2f);
     glScalef(0.4f, 0.6f, 0.6f);
     glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix();
}

void DrawSun() {
    glPushMatrix();
    glTranslatef(15.0f, 35.0f, -150.0f);
    glColor3f(1.0f, 0.9f, 0.2f);
    glutSolidSphere(8.0f, 20, 20);
    glPopMatrix();
}

void DrawCloud(float PositionX, float PositionY, float PositionZ)
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(PositionX, PositionY, PositionZ);

    glutSolidSphere(3.0f, 15, 15);

    glPushMatrix();
    glTranslatef(-2.0f, -0.5f, 0.0f);
    glutSolidSphere(2.0f, 15, 15);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.0f, -0.5f, 0.0f);
    glutSolidSphere(2.0f, 15, 15);
    glPopMatrix();

    glPopMatrix();
}

void DrawEndlessEnvironment() {
    int Prny = (int)(DistanceTravel / 3000);
    if (Prny % 2 == 0) {
        CurrentEnvironment = 0;
        glClearColor(0.4f, 0.7f, 1.0f, 1.0f);
    } else {
        CurrentEnvironment = 1;
         glClearColor(0.7f, 0.8f, 0.9f, 1.0f);
    }
    DrawSun();
    DrawCloud(-20.0f, 18.0f, -120.0f);
    DrawCloud(25.0f, 22.0f, -140.0f);
    DrawCloud(-35.0f, 15.0f, -100.0f);

    if (CurrentEnvironment == 0) {
        glColor3f(0.8f, 0.7f, 0.4f);
    } else {
        glColor3f(0.9f, 0.95f, 1.0f);
    }
    glBegin(GL_QUADS);
    glVertex3f(-200.0f, 0.0f,  50.0f);
    glVertex3f( 200.0f, 0.0f,  50.0f);
    glVertex3f( 200.0f, 0.0f, -300.0f);
    glVertex3f(-200.0f, 0.0f, -300.0f);
    glEnd();

    float SceneryGap = 50.0f;
    float Shift = fmod(DistanceTravel, SceneryGap);

    for (float z = 50.0f; z > -300.0f; z = z-SceneryGap) {
        float ActualZ = z + Shift;

        if (CurrentEnvironment == 0) {
            glColor3f(0.7f, 0.5f, 0.2f);
            glPushMatrix();
            glTranslatef(-30.0f, 0.0f, ActualZ);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
            glutSolidCone(10.0f, 15.0f, 4, 1);
            glPopMatrix();

            glColor3f(0.75f, 0.55f, 0.25f);
            glPushMatrix();
            glTranslatef(30.0f, 0.0f, ActualZ - 20.0f);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
            glutSolidCone(12.0f, 18.0f, 4, 1);
            glPopMatrix();
        } else {
            glColor3f(0.4f, 0.2f, 0.1f);
            glPushMatrix();
            glTranslatef(-20.0f, 1.0f, ActualZ);
            glScalef(1.0f, 2.0f, 1.0f);
            glutSolidCube(1.0f);
            glPopMatrix();

            glColor3f(1.0f, 1.0f, 1.0f);
            glPushMatrix();
            glTranslatef(-20.0f, 2.0f, ActualZ);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
            glutSolidCone(3.0f, 8.0f, 8, 1);
            glPopMatrix();

            glColor3f(0.4f, 0.2f, 0.1f);
            glPushMatrix();
            glTranslatef(20.0f, 1.0f, ActualZ - 20.0f);
            glScalef(1.0f, 2.0f, 1.0f);
            glutSolidCube(1.0f);
            glPopMatrix();

            glColor3f(1.0f, 1.0f, 1.0f);
            glPushMatrix();
            glTranslatef(20.0f, 2.0f, ActualZ - 20.0f);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
             glutSolidCone(3.0f, 8.0f, 8, 1);
             glPopMatrix();
        }
    }
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex3f(-8.0f, 0.02f,  50.0f);
    glVertex3f( 8.0f, 0.02f,  50.0f);
    glVertex3f( 8.0f, 0.02f, -300.0f);
    glVertex3f(-8.0f, 0.02f, -300.0f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    float LineGap = 15.0f;
    float LShift = fmod(DistanceTravel, LineGap);
    for (float z = 50.0f; z > -300.0f; z = z-LineGap) {
        float ActualZ = z + LShift;
        glBegin(GL_QUADS);
        glVertex3f(-0.2f, 0.05f, ActualZ);
        glVertex3f( 0.2f, 0.05f, ActualZ);
        glVertex3f( 0.2f, 0.05f, ActualZ - 5.0f);
        glVertex3f(-0.2f, 0.05f, ActualZ - 5.0f);
        glEnd();
    }
}

 float EnemyPosX = 0.0f;
 float EnemyPosZ = -150.0f;
 float EnemyColorR = 0.8f;
 float EnemyColorG = 0.2f;
 float EnemyColorB = 0.2f;

 float BarrierPosX = 4.0f;
 float BarrierPosZ = -200.0f;

 float PowerUpPositionX = -4.0f;
 float PowerUpPositionZ = -100.0f;
 int PowerUpType = 0;

void DrawGameObjects() {
    DrawTruck(EnemyPosX, 0.0f, EnemyPosZ,
              EnemyColorR, EnemyColorG, EnemyColorB);

    glPushMatrix();
    glTranslatef(BarrierPosX, 0.5f, BarrierPosZ);
    glColor3f(1.0f, 0.4f, 0.0f);
    glScalef(2.5f, 1.0f, 0.5f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(PowerUpPositionX, 1.0f, PowerUpPositionZ);

    if (PowerUpType == 0) {
        glColor3f(1.0f, 0.8f, 0.0f);
        glutSolidSphere(0.6f, 15, 15);
    }
    else if (PowerUpType == 1) {
        glColor3f(0.0f, 1.0f, 0.0f);
        glutSolidCube(1.0f);
    }
    else if (PowerUpType == 2) {
        glColor3f(0.0f, 0.5f, 1.0f);
        glutSolidSphere(0.7f, 15, 15);
    }

    glPopMatrix();
}

  float PlayerPositionX = 0.0f;
  float PlayerPositionZ = 0.0f;
  float PlayerSideSpeed = 0.2f;

  bool IsShieldActive = false;
  int ShieldHitsRemaining = 0;
  int BoostTimerRemaining = 0;

void RenderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0f, 8.0f, 15.0f,
              0.0f, 0.0f, -20.0f,
              0.0f, 1.0f, 0.0f);

    DrawEndlessEnvironment();
    DrawGameObjects();

    DrawTruck(PlayerPositionX, 0.0f, PlayerPositionZ, 0.6f, 0.6f, 0.6f);

    if (IsShieldActive) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.0f, 0.5f, 1.0f, 0.4f);
        glPushMatrix();
        glTranslatef(PlayerPositionX, 1.5f, PlayerPositionZ);
        glutSolidSphere(2.5f, 20, 20);
        glPopMatrix();
        glDisable(GL_BLEND);
    }

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    char TextBuffer[100];
    if (IsGameOver) {
        glColor3f(1.0f, 0.0f, 0.0f);
        DrawTextOnScreen(350, 300, "GAME OVER");
        glColor3f(1.0f, 1.0f, 1.0f);
        sprintf(TextBuffer, "Final Score: %d", PlayerScore);
        DrawTextOnScreen(350, 260, TextBuffer);
        DrawTextOnScreen(350, 220, "Press R to Restart");
    } else {
        glColor3f(1.0f, 1.0f, 1.0f);
        sprintf(TextBuffer, "Score: %d", PlayerScore);
        DrawTextOnScreen(20, 560, TextBuffer);

        sprintf(TextBuffer, "Speed: %d km/h", (int)(GameForwardSpeed * 50));
        DrawTextOnScreen(350, 560, TextBuffer);

        if (BoostTimerRemaining > 0) {
            glColor3f(0.0f, 1.0f, 0.0f);
            DrawTextOnScreen(550, 560, "BOOST ACTIVE ");
        }
        if (IsShieldActive) {
            glColor3f(0.0f, 0.5f, 1.0f);
            DrawTextOnScreen(550, 500, "SHIELD Active ");
        }
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glutSwapBuffers();
}

float CalculateAbsoluteValue(float NumberValue) {
    if (NumberValue < 0) {
        return -NumberValue;
    } else {
        return NumberValue;
    }
}

float GetRandomLanePosition() {
    int RandomLane = rand() % 3;
    if (RandomLane == 0)
    {
        return -4.0f;
    } else if (RandomLane == 1) {
        return 0.0f;
    } else {
        return 4.0f;
    }
}

void UpdateGameLogic(int TimerValue) {
    if (!IsGameOver) {
        if (IsLeftArrowPressed){
            PlayerPositionX =PlayerPositionX - PlayerSideSpeed;
        }
        if (IsRightArrowPressed) {PlayerPositionX += PlayerSideSpeed;}

        if (PlayerPositionX < -6.0f){
            PlayerPositionX = -6.0f;
        }
        if (PlayerPositionX >  6.0f){
              PlayerPositionX =  6.0f;
        }
        if (IsUpArrowPressed){
            GameForwardSpeed = GameForwardSpeed + 0.02f;
        }
        else if(IsDownArrowPressed){
            GameForwardSpeed -= 0.05f;
        }

        if (GameForwardSpeed > 3.0f){
            GameForwardSpeed = 3.0f;
        }
        if (GameForwardSpeed < 0.8f){
             GameForwardSpeed = 0.8f;
        }

        float ActiveSpeed = GameForwardSpeed;
        if (BoostTimerRemaining > 0) {
            ActiveSpeed =ActiveSpeed + 1.5f;
            BoostTimerRemaining--;
        }
             DistanceTravel=DistanceTravel + ActiveSpeed;
             EnemyPosZ =EnemyPosZ + ActiveSpeed;
             BarrierPosZ =BarrierPosZ + ActiveSpeed;
             PowerUpPositionZ=PowerUpPositionZ + ActiveSpeed;

        if (EnemyPosZ > 15.0f) {
            EnemyPosZ = -200.0f - (rand() % 100);
            EnemyPosX = GetRandomLanePosition();
            EnemyColorR = (rand() % 10) / 10.0f;
            EnemyColorG = (rand() % 10) / 10.0f;
            EnemyColorB = (rand() % 10) / 10.0f;
            PlayerScore += 10;
        }

        if (BarrierPosZ > 15.0f) {
            BarrierPosZ = -200.0f - (rand() % 100);
            BarrierPosX = GetRandomLanePosition();
        }

        if (PowerUpPositionZ > 15.0f) {
            PowerUpPositionZ = -150.0f - (rand() % 100);
            PowerUpPositionX = GetRandomLanePosition();
            PowerUpType = rand() % 3;
        }
        float HitMarginX = 2.0f;
        float HitMarginZ = 3.0f;

        bool Zcheck=CalculateAbsoluteValue(EnemyPosZ - PlayerPositionZ) < HitMarginZ;
        bool Xcheck=CalculateAbsoluteValue(EnemyPosX - PlayerPositionX) < HitMarginX;
        if (Zcheck && Xcheck) {
            if (IsShieldActive) {
                IsShieldActive = false;
                EnemyPosZ = 20.0f;
            } else { IsGameOver = true; }
        }

        bool ZBarrierCheck=CalculateAbsoluteValue(BarrierPosZ - PlayerPositionZ) < HitMarginZ;
        bool XBarrierCheck = CalculateAbsoluteValue(BarrierPosX - PlayerPositionX) < HitMarginX;
        if (ZBarrierCheck && XBarrierCheck) {
            if (IsShieldActive) {
                IsShieldActive = false;
                BarrierPosZ = 20.0f;
            } else { IsGameOver = true; }
        }

        if (CalculateAbsoluteValue(PowerUpPositionZ - PlayerPositionZ) < 2.0f &&
            CalculateAbsoluteValue(PowerUpPositionX - PlayerPositionX) < 2.0f) {
            if (PowerUpType == 0){
                PlayerScore = PlayerScore + 50;
            }
            else if (PowerUpType == 1) { BoostTimerRemaining = 100; }
            else if (PowerUpType == 2){
                IsShieldActive = true;
            }

            PowerUpPositionZ = 20.0f;
        }
    }

    glutPostRedisplay();
}

void HandleSpecialKeysDown(int KeyboardKey, int MouseX, int MouseY) {
    if (KeyboardKey == GLUT_KEY_LEFT){
        IsLeftArrowPressed = true;
    }
    if (KeyboardKey == GLUT_KEY_RIGHT){
         IsRightArrowPressed = true;
    }
    if (KeyboardKey == GLUT_KEY_UP){
         IsUpArrowPressed = true;
    }
    if (KeyboardKey == GLUT_KEY_DOWN){
        IsDownArrowPressed = true;
    }
}

void HandleSpecialKeysUp(int KeyboardKey, int MouseX, int MouseY) {
    if (KeyboardKey == GLUT_KEY_LEFT)  { IsLeftArrowPressed = false; }
    if (KeyboardKey == GLUT_KEY_RIGHT) { IsRightArrowPressed = false; }
    if (KeyboardKey == GLUT_KEY_UP)    { IsUpArrowPressed = false; }
    if (KeyboardKey == GLUT_KEY_DOWN)  { IsDownArrowPressed = false; }
}

void HandleStandardKeys(unsigned char KeyboardKey, int MouseX, int MouseY) {
    if (KeyboardKey == 'r' || KeyboardKey == 'R') {
        IsGameOver = false;
        PlayerScore = 0;
        DistanceTravel = 0.0f;
        PlayerPositionX = 0.0f;
        GameForwardSpeed = 1.0f;
        EnemyPosZ = -150.0f;
        BarrierPosZ = -300.0f;
        PowerUpPositionZ = -100.0f;
        IsShieldActive = false;
        BoostTimerRemaining = 0;
    }
}

void InitializeGame() {
    srand((unsigned int)time(NULL));
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat LightAmbientColor[]  = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat LightDiffuseColor[]  = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat LightPosition[]      = {0.0f, 50.0f, -50.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbientColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuseColor);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 800.0 / 600.0, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}
