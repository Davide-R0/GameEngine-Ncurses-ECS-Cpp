#include "sMenu.h"
#include "../../components/Components.h"
#include <ncursesw/ncurses.h>

void menu::addEntry(std::vector<std::string> content) {
    /*std::vector<std::string> ent = {
      "┏┓",
      "┗┓╋┏┓┏┓╋",
      "┗┛┗┗┻┛ ┗"
      };*/
    m_entries.push_back(content);
    //m_entries.push_back(content);
}

void menu::moveUp() {
    if (m_activeIndex-1 >= 0) { 

        m_activeIndex -= 1;
        renderMenu();

    }
}

void menu::moveDown() {
    if (m_activeIndex+1 < m_entries.size()) { 
        m_activeIndex += 1;
        renderMenu();
    }
}

void menu::attachWindow(entity* window) {
    m_window = window;
}

void menu::renderMenu() {
    m_window->getComponent<CCursorPosition>()->x = 1;
    m_window->getComponent<CCursorPosition>()->y = 1;
    int x_indent=0;
    for (int i = 0; i<m_entries.size(); i++) {
        if (i == m_activeIndex) wattron(m_window->getComponent<CWindow>()->win, A_STANDOUT);
        //centering
        x_indent = (int)((m_window->getComponent<CWindow>()->dimX-m_entries.at(i).at(1).size()/4)/2) - 1;
        //NOTE: momentaneo per problemi di wide character
        if (i==1) x_indent -=1;

        //GDEBUG("indentations: %d",  x_indent); 

        for (int j = 0; j< m_entries.at(i).size(); j++) {
            mvwprintw(m_window->getComponent<CWindow>()->win, m_window->getComponent<CCursorPosition>()->y, x_indent, "%s", m_entries.at(i).at(j).c_str());
            m_window->getComponent<CCursorPosition>()->y += 1;
        }

        if (i == m_activeIndex) wattroff(m_window->getComponent<CWindow>()->win, A_STANDOUT);

    }
}
