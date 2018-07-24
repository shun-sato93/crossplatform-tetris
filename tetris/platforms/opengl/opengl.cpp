//
//  opengl.cpp
//  tetris
//
//  Created by Shun Sato on 7/2/18.
//  Copyright © 2018 佐藤駿. All rights reserved.
//

#include "opengl.hpp"

#ifdef _WIN32
	#include <gl/glut.h>
	#include "unistd.h"
#else
	#include <GLUT/glut.h>
	#include <unistd.h>
#endif

#include "Constants.hpp"
#include "Coordinates.hpp"
#include "Drawer.hpp"
#include "GameContext.hpp"
#include "IOInterface.hpp"
#include "TouchEvent.hpp"
#include "Updater.hpp"
#include "UIManager.hpp"

#include <iostream>
using namespace std;


void OpenGL::setup(int argc, char** argv)
{
    glutInit(&argc, argv);
    
    /* set the window size */
    Size windowSize = getWindowSize();
    glutInitWindowSize(windowSize.width, windowSize.height);
    
    /* set the display mode to Red, Green, Blue and Alpha
     allocate a depth buffer
     enable double buffering
     */
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    
    /* create the window (and call it Lab 1) */
    glutCreateWindow("Tetris");
    
    /* set the glut display callback function
     this is the function GLUT will call every time
     the window needs to be drawn
     */
    glutDisplayFunc(display);
    
    /* set the glut reshape callback function
     this is the function GLUT will call whenever
     the window is resized, including when it is
     first created
     */
    glutReshapeFunc(reshape);
    
    glutIdleFunc(update);
    glutKeyboardFunc(keyboardInput);
    glutSpecialFunc(specialKeyboardInput);
    glutMouseFunc(mouseInput);
    
    /* enter the main event loop so that GLUT can process
     all of the window event messages
     */
    glutMainLoop();
}

void OpenGL::mouseInput(int button, int state, int x, int y) {
    std::cout << "OpenGL::mouseInput x=" << x << " y=" << y << endl;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        auto windowSize = getWindowSize();
        TouchEvent touchEvent = TouchEvent(TouchEvent::DOWN, vec2d(x, windowSize.height - y));
        UIManager::get().handleTouchEvent(touchEvent);
    }
}


void OpenGL::keyboardInput(unsigned char key, int x, int y) {
    cout << key << endl;
    switch (key) {
        case ' ': // Space key
            IOInterface::keyboardInput(Keyboard::SPACE);
            break;
        case 27: // ESC key
            IOInterface::keyboardInput(Keyboard::ESC);
            break;
    }
}

void OpenGL::specialKeyboardInput(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            IOInterface::keyboardInput(Keyboard::LEFT);
            break;
        case GLUT_KEY_UP:
            IOInterface::keyboardInput(Keyboard::UP);
            break;
        case GLUT_KEY_DOWN:
            IOInterface::keyboardInput(Keyboard::DOWN);
            break;
        case GLUT_KEY_RIGHT:
            IOInterface::keyboardInput(Keyboard::RIGHT);
            break;
    }
}

void OpenGL::update() {
    Updater::get().update(false);
    glutPostRedisplay();
}

/*! glut display callback function.  Every time the window needs to be drawn,
 glut will call this function.  This includes when the window size
 changes, or when another window covering part of this window is
 moved so this window is uncovered.
 */
void OpenGL::display() {
    /* clear the color buffer (resets everything to black) */
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    Drawer::get().draw();

    /* swap the back and front buffers so we can see what we just drew */
    glutSwapBuffers();
}

void OpenGL::setColor(Color::Types color) {
    static Color::Types currentColor = Color::NONE;
    // avoid unnecessary color setting
    if (currentColor != color) {
        switch (color) {
            case Color::NONE: break;
            case Color::_1:
                glColor3ub(179, 219, 192);
                break;
            case Color::_2:
                glColor3ub(254, 0, 0);
                break;
            case Color::_3:
                glColor3ub(253, 246, 246);
                break;
            case Color::_4:
                glColor3ub(103, 186, 202);
                break;
            case Color::BLACK:
                glColor3ub(0, 0, 0);
                break;
            case Color::WHITE:
                glColor3ub(255, 255, 255);
                break;
            case Color::GREY:
                glColor3ub(128, 128, 128);
                break;
        }
        
        currentColor = color;
    }
}

void OpenGL::drawRectangle(Color::Types color, double x1, double y1, double x2, double y2) {
    if (color == Color::NONE) { return; }
    setColor(color);
    glRectd(x1, y1, x2, y2);
}

void OpenGL::drawText(double x, double y, const string& text, Color::Types color) {
    //(x,y) is from the bottom left of the window
    setColor(color);
    glRasterPos2d(x,y);
    for (int i=0; i<text.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
    }
}

Size OpenGL::getTextSize(const std::string& text, int font) {
    // TODO: font size
    return Size(9*text.length(), 15);
}

void OpenGL::changeWindowSize(int width, int height) {
    glutReshapeWindow(width, height);
}

/*! glut reshape callback function.  GLUT calls this function whenever
 the window is resized, including the first time it is created.
 You can use variables to keep track the current window size.
 */
void OpenGL::reshape(int width, int height) {
    /* tell OpenGL we want to display in a recangle that is the
     same size as the window
     */
    glViewport(0,0,width,height);
    
    /* switch to the projection matrix */
    glMatrixMode(GL_PROJECTION);
    
    /* clear the projection matrix */
    glLoadIdentity();
    
    /* set the camera view, orthographic projection in 2D */
    gluOrtho2D(0,width,0,height);
    
    /* switch back to the model view matrix */
    glMatrixMode(GL_MODELVIEW);
}
