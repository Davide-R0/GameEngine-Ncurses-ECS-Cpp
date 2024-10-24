#include "textlist.h"

#include "../../components/Components.h"
#include <ncursesw/ncurses.h>


textlist::textlist(text_list_info info) : m_info(info) {
    //TODO: do checks on entries
}

void textlist::addAssetEntries(std::vector<std::string> assetEntries) {
    //TODO: add checks 
    //we are coping a vector of vector... it's not ideal, to adjust we should pass only the asset manager and let the asset manager manage the data
    m_assetEntries.push_back(assetEntries);
    nArgs++;
}

void textlist::moveNext() {
    if (m_activeIndex < nArgs-1) { 
        m_activeIndex++;
        sRenderMenu();
    }
}

void textlist::movePrev() {
    if (m_activeIndex > 0) { 
        m_activeIndex--;
        sRenderMenu();
    }
}

int textlist::getSelect() const {
    return m_activeIndex;
}

void textlist::sRenderMenu() {
    m_info.window->getComponent<CCursorPosition>()->x = 1;
    m_info.window->getComponent<CCursorPosition>()->y = 1;

    if (m_info.simpleText) {
        //TODO:
    } else {
        int x_indent = 0, len = 0;
        for (int i = 0; i<(int)m_assetEntries.size(); i++) {
            //hilighting
            if (i == m_activeIndex) wattron(m_info.window->getComponent<CWindow>()->win, A_STANDOUT);
            
            //centering 
            //transform string in wstring and calculate the lenght
            //NOTE: take the first element [i][0] because we assume that the array at [i] have lenght equal for each line 
            len = m_assetEntries.at(i).at(1).length()/4;
            
            //GDEBUG("Whide character lenght: %d", len);

            x_indent = (int)((m_info.window->getComponent<CWindow>()->dimX - len))/2 -1;
            
            //NOTE: momentaneo per problemi di wide character
            if (i==1) x_indent -=2;

            for (std::size_t j = 0; j< m_assetEntries.at(i).size(); j++) {
                mvwprintw(  m_info.window->getComponent<CWindow>()->win, 
                            m_info.window->getComponent<CCursorPosition>()->y, 
                            x_indent + m_info.window->getComponent<CCursorPosition>()->x , 
                            "%s", m_assetEntries.at(i).at(j).c_str());

                m_info.window->getComponent<CCursorPosition>()->y += 1;
                
            }

            if (m_info.vertical) {
                    m_info.window->getComponent<CCursorPosition>()->y += m_info.padding -1;
                } else {
                    m_info.window->getComponent<CCursorPosition>()->x += len + m_info.padding;
                }
            
            //hilighting
            if (i == m_activeIndex) wattroff(m_info.window->getComponent<CWindow>()->win, A_STANDOUT);

        }
    }
}
