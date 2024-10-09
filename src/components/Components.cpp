#include "Components.h"
#include <ncurses.h>

#include "../core/logger.h"

Components::Components() {
    //GDEBUG("Components base class constructor called");
}
Components::~Components() {
    //GDEBUG("Components base class destructor called");
}

CTransform::CTransform(int X, int Y): y(Y), x(X) {
    GDEBUG("CTransform constructor called");
}
CTransform::~CTransform() {
    GDEBUG("CTransform destructor called");
}

CInput::CInput() {
    GDEBUG("CInput constructor called");
}

CInput::~CInput() {
    GDEBUG("CInput destructor called");
}

/*
CWindow::CWindow(int line_X, int line_Y, int X, int Y, WINDOW* parent_win) : y(Y), x(X), line_y(line_Y), line_x(line_X) {
    //NOTE: add error if parent_win is null ptr
    *//*
    if (parent_win == stdscr) {
        m_win = newwin(line_X, line_Y, X, Y);  
    } else {
        m_win = subwin(parent_win, line_X, line_Y, X, Y);
    }
    *//*
}

CWindow::~CWindow() {
    //TODO: add log error if problem 
    
    //delete window 
    //delwin(m_win);
}

const WINDOW* CWindow::getWin() const {
    return m_win;
}
*/
/*
CSpriteNc::CSpriteNc(char* sprite, int x, int y) : m_y(y), m_x(x), m_sprite(sprite) {

}

CSpriteNc::~CSpriteNc() {
    
}

const char* CSpriteNc::getSprite() const {
    return m_sprite;
}

int CSpriteNc::getX() const {
    return m_x;
}

int CSpriteNc::getY() const {
    return m_y;
}

CCollisionShapeNc::CCollisionShapeNc(char* sprite, int x, int y) : m_y(y), m_x(x), m_sprite(sprite) {
    
}

CCollisionShapeNc::~CCollisionShapeNc() {

}

const char* CCollisionShapeNc::getSprite() const {
    return m_sprite;
}

int CCollisionShapeNc::getX() const {
    return m_x;
}

int CCollisionShapeNc::getY() const {
    return m_y;
}
*/



