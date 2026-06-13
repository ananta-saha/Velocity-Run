#include <GL/glut.h>
#include <cstdio>
#include <cstdlib>
int gameMode = 0;

void display1();
void update1(int);
void keyboard1(unsigned char, int, int);
void init1();

void RenderScene();
void UpdateGameLogic(int);
void HandleStandardKeys(unsigned char, int, int);
void HandleSpecialKeysDown(int, int, int);
void HandleSpecialKeysUp(int, int, int);
void InitializeGame();

void map3_display();
void map3_update(int);
void map3_keyboard(unsigned char, int, int);
void map3_keyboardUp(unsigned char, int, int);
void map3_init();

void map4_display();
void map4_update(int);
void map4_keyboard(unsigned char, int, int);
void map4_specialKeys(int, int, int);
void map4_specialKeysUp(int, int, int);
void map4_init();

void map5_display();
void map5_update(int);
void map5_keyboard(unsigned char key, int x, int y);
void map5_specialKeys(int, int, int);
void map5_specialKeysUp(int, int, int);
void map5_init();

void renderText(float x, float y, const char* str, void* font = GLUT_BITMAP_HELVETICA_18) {
    glRasterPos2f(x, y);
    while (*str) glutBitmapCharacter(font, *str++);
}

void reset3D() {
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_FOG);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 800.0/600.0, 1.0, 500.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawMenu() {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_FOG);
    glDisable(GL_COLOR_MATERIAL);

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);

    renderText(300, 450, "VELOCITY RUN", GLUT_BITMAP_TIMES_ROMAN_24);
    renderText(300, 390, "Press 1 - Map 1", GLUT_BITMAP_HELVETICA_18);
    renderText(300, 360, "Press 2 - Map 2", GLUT_BITMAP_HELVETICA_18);
    renderText(300, 330, "Press 3 - Map 3", GLUT_BITMAP_HELVETICA_18);
    renderText(300, 300, "Press 4 - Map 4", GLUT_BITMAP_HELVETICA_18);
    renderText(300, 270, "Press 5 - Map 5", GLUT_BITMAP_HELVETICA_18);
    renderText(300, 240, "Press ESC - Exit", GLUT_BITMAP_HELVETICA_18);

    glutSwapBuffers();
}

void display() {

    if (gameMode == 0) {
        drawMenu();
        return;
    }
    reset3D();

    if (gameMode == 1) display1();
    else if (gameMode == 2) RenderScene();
    else if (gameMode == 3) map3_display();
    else if (gameMode == 4) map4_display();
    else if (gameMode == 5) map5_display();
}

void update(int v) {

    if (gameMode == 1) update1(v);
    else if (gameMode == 2) UpdateGameLogic(v);
    else if (gameMode == 3) map3_update(v);
    else if (gameMode == 4) map4_update(v);
    else if (gameMode == 5) map5_update(v);

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}
void keyboard(unsigned char key, int x, int y) {

    if (gameMode == 0) {
        if (key == '1') { gameMode = 1; init1(); }
        else if (key == '2') { gameMode = 2; InitializeGame(); }
        else if (key == '3') { gameMode = 3; map3_init(); }
        else if (key == '4') { gameMode = 4; map4_init(); }
        else if (key == '5') { gameMode = 5; map5_init(); }
        else if (key == 27) exit(0);
    }
    else {
        if (key == 27) {
            gameMode = 0;
            glutPostRedisplay();
            return;
        }

        if (gameMode == 1) keyboard1(key, x, y);
        else if (gameMode == 2) HandleStandardKeys(key, x, y);
        else if (gameMode == 3) map3_keyboard(key, x, y);
        else if (gameMode == 4) map4_keyboard(key, x, y);
        else if (gameMode == 5) map5_keyboard(key, x, y);
    }
}

void keyboardUp(unsigned char key, int x, int y) {
    if (gameMode == 3) map3_keyboardUp(key, x, y);
}

void specialKeys(int key, int x, int y) {

    if (gameMode == 2) HandleSpecialKeysDown(key, x, y);
    else if (gameMode == 4) map4_specialKeys(key, x, y);
    else if(gameMode==5){
        map5_specialKeys(key, x, y);
    }
}

void specialKeysUp(int key, int x, int y) {

    if (gameMode == 2) HandleSpecialKeysUp(key, x, y);
    else if (gameMode == 4) map4_specialKeysUp(key, x, y);
    else if(gameMode==5){
        map5_specialKeysUp(key, x, y);
    }
}
int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Velocity Run");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(specialKeys);
    glutSpecialUpFunc(specialKeysUp);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
