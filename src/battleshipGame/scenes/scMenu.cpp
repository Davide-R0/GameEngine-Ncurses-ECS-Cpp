#include "scMenu.h"
#include "../../core/logger.h"
#include "../../core/asserts.h"
#include "../../core/gameEngine.h"
#include "../../entities/entity.h"
#include "../../entities/entityMang.h"
#include "../../components/Components.h"
#include "../../actions/action.h"
#include "../../actions/actionConstants.h"
#include "../../assets/assets.h"
#include "../../scenes/sceneConstants.h"
#include "sMenu.h"

#include "scPlay.h"

//wide character ncurses varaint
//#define NCURSES_WIDECHAR 1    //???
//#define _XOPEN_SOURCE 700 
#include <ncursesw/ncurses.h>

scMenu::scMenu() {
 GTRACE("Scene play class constructor called");
    init();

}

scMenu::~scMenu() {
    GTRACE("Scene play class destructor called");

    //TODO: free memory
    delete m_entityMang;
    //delete m_player;

    //do not delete m_game
}


//before a scene change call a prerendering function to render the static object on the screen (like the board, the windows, ecc..)

void scMenu::update() {
    m_entityMang->update();

    wmove(m_focusWindow->getComponent<CWindow>()->win, m_focusWindow->getComponent<CCursorPosition>()->y, m_focusWindow->getComponent<CCursorPosition>()->x); //move cursor

    if (!isPaused()) {
        //call systems ...
    }

    m_currentFrame++;
}

void scMenu::init() {
    //Initialization assets
    //Upload assets for the title 
    
    getAssets()->addNcTexture(TITLE, "assets/textures/title.txt");

    //getAssets()->addNcTexture(BASE, "assets/textures/texture.txt"); //give an error log is try to rewrite the same texture (but it will rewrite anyway)

    //Initialization action map
    //dichiarare questa variabile oppure ricordarsi l'indice dell'enum...
    //i KEY_.. sono i valori di default di ncurses per i tasti 
    //command 58 (=`:`) for command window focus
    registerAction((int)'w', UP); //119 for the 'w? character
    registerAction((int)'s', DOWN);
    registerAction((int)'a', LEFT);
    registerAction((int)'d', RIGHT);
    registerAction(10, ENTER);   //10 Enter code for Ncurses

    //general initialization
    m_entityMang = new entityMang();

    //setup window parameters
    //...

    //spawn initial scene
    //-board
    //m_entityMang->addEntity(BOARD);
    //-points window

    //-remaining ship window

    //-info bar on the bottom
    
    m_entityMang->addEntity(USER);    //player entity 

    m_entityMang->addEntity(IMAGE); //logo name window 
    
    m_entityMang->addEntity(WINDOW_REND);   //selection window 

    m_entityMang->addEntity(WINDOW_REND);   //command window 
    
    m_entityMang->update();
    
    m_entityMang->getEntities(USER)[0]->addComponent<CInput>(new CInput());
    //aggiungere un componente che abbia le informazioni del player 
    
    //nc_texture_type texture = getAssets()->getTexture(TITLE);
    //add the texture title to the entity image 
    m_entityMang->getEntities(IMAGE)[0]->addComponent<CTexture>(new CTexture(TITLE));
    //add a transform to the entity
    //m_entityMang->getEntities(IMAGE)[0]->addComponent(new CTransform());
    //CTransform* image_transform = m_entityMang->getEntities(IMAGE)[0]->getComponent<CTransform>();
    

    m_entityMang->getEntities(IMAGE)[0]->addComponent(new CWindow());   //wil be then setted
    //setting a cursor position??
    //m_entityMang->getEntities(IMAGE)[0]->addComponent<CCursorPosition>(new CCursorPosition()); 
    CWindow* image_window = m_entityMang->getEntities(IMAGE)[0]->getComponent<CWindow>();
    const std::vector<std::string>* image_asset = getAssets()->getTexture(m_entityMang->getEntities(IMAGE)[0]->getComponent<CTexture>()->name);
    GDEBUG("Image %d, %d", image_asset->at(0).size(), image_asset->size());
    image_window->dimX = 130;//image_asset->at(0).size()/2; //130;
    image_window->dimY = image_asset->size();
    //centered
    image_window->x = (int)xScr/2-(int)image_window->dimX/2;
    //slitly up
    image_window->y = (int)yScr/2-(int)image_window->dimY/2-(int)yScr/6 -3;
    //per aggiungere il bordo bisogna aggiungere 4 e 2 alle dimensioni della finestra
    image_window->border = false;
    //GDEBUG("x %d, y %d, dimx %d, dimY %d",image_window->x, image_window->y, image_window->dimX, image_window->dimY);
    

    m_entityMang->update();

    

    //menu window
    m_entityMang->getEntities(WINDOW_REND)[0]->addComponent<CWindow>(new CWindow());
    m_entityMang->getEntities(WINDOW_REND)[0]->addComponent<CCursorPosition>(new CCursorPosition());
    CWindow* window = m_entityMang->getEntities(WINDOW_REND)[0]->getComponent<CWindow>();
    window->dimX = 20;
    window->dimY = 18;  //space for command line
    window->x = (int)((xScr - window->dimX)/2);
    window->y = image_window->y + image_window->dimY + 3;
    window->border = false;
    //menu initialization
    m_menu = new menu();    
    //TODO: passare l'asset manager con il contenuto voluto
    m_menu->attachWindow(m_entityMang->getEntities(WINDOW_REND)[0]);
    std::vector<std::string> ent = {
        "┏┓      ",
        "┗┓╋┏┓┏┓╋",
        "┗┛┗┗┻┛ ┗"
    };
    m_menu->addEntry(ent);

    ent = {
        "┳┳┓  ┓ •  ┓        ",
        "┃┃┃┓┏┃╋┓┏┓┃┏┓┓┏┏┓┏┓",
        "┛ ┗┗┻┗┗┗┣┛┗┗┻┗┫┗ ┛ ",
        "        ┛     ┛    "
    };
    m_menu->addEntry(ent);
    ent = {  
        "┳  ┏  ",
        "┃┏┓╋┏┓",
        "┻┛┗┛┗┛"
    };
    m_menu->addEntry(ent);
    
    ent = {  
        "┏┓    •     ",
        "┗┓┏┓╋╋┓┏┓┏┓┏",
        "┗┛┗ ┗┗┗┛┗┗┫┛",
        "          ┛ "
    };
    m_menu->addEntry(ent);

    ent = {
        "┏┓  • ",
        "┣ ┓┏┓╋",
        "┗┛┛┗┗┗"
    };
    m_menu->addEntry(ent);

    //command window
    m_entityMang->getEntities(WINDOW_REND)[1]->addComponent<CWindow>(new CWindow());
    m_entityMang->getEntities(WINDOW_REND)[1]->addComponent<CCursorPosition>(new CCursorPosition());
    window = m_entityMang->getEntities(WINDOW_REND)[1]->getComponent<CWindow>();
    window->dimX = xScr-2;
    window->dimY = 3;  //space for command line
    window->x = 1;
    window->y = yScr-3-1;
    window->border = true;

    //Ncurses rendering 
    sStaticNcRender();

    m_focusWindow = m_entityMang->getEntities(WINDOW_REND)[0];
    m_focusWindow->getComponent<CCursorPosition>()->x = 1;
    m_focusWindow->getComponent<CCursorPosition>()->y = 1;
    wmove(m_focusWindow->getComponent<CWindow>()->win, m_focusWindow->getComponent<CCursorPosition>()->y, m_focusWindow->getComponent<CCursorPosition>()->x); //move cursor
    wrefresh(m_focusWindow->getComponent<CWindow>()->win);
    
    m_entityMang->update();
    
    //rendering command window
    entity* cmd_window = m_entityMang->getEntities(WINDOW_REND)[1];
    std::string cmd_message = "Exit: ^C     Up: 'w'    Down: 's'     Select: Enter or 'd'   Back: Esc or 'a'";
    std::vector<std::string> cmdMessages = {
        " Exit: ^C ",
        " Up: 'w' ",
        " Down: 's' ",
        " Select: Enter or 'd' ",
        " Back: Esc or 'a' "
    };
    int spacing = 5;
    int initialOffset = 2;
    wattron(cmd_window->getComponent<CWindow>()->win, A_STANDOUT);
    for(std::size_t i = 0; i < cmdMessages.size(); i++) {
        mvwprintw(cmd_window->getComponent<CWindow>()->win, 1, initialOffset, "%s", cmdMessages.at(i).c_str());
        initialOffset += spacing + cmdMessages.at(i).size();
    }
    wattroff(cmd_window->getComponent<CWindow>()->win, A_STANDOUT);
    /*wattron(cmd_window->getComponent<CWindow>()->win, A_STANDOUT);
    mvwprintw(cmd_window->getComponent<CWindow>()->win, 1, 1, "%s", cmd_message.c_str());
    wattroff(cmd_window->getComponent<CWindow>()->win, A_STANDOUT);*/
    wrefresh(cmd_window->getComponent<CWindow>()->win);
    
    //cursor visibility
    curs_set(0);    //0 = invisible
                    //1 = terminal specific
                    //2 = always
 
}
/*
void scPlay::sPrintwNc(int x, int y, string...){
    //stanpa la stringa sulla finestra attualmente con focus (m_windowOnFOcus) e fa una serie di verifiche per i bordi e fine della finestra
    //puo anche non prendere argomenti x, y e stampa dove è il cursore
}*/

void scMenu::sStaticNcRender() {
    
    //Image rendring
    for (auto e : m_entityMang->getEntities(IMAGE)) {
        //if (e->isToRender()) { ...
        CWindow* windowToRender = e->getComponent<CWindow>();

        windowToRender->win = newwin(windowToRender->dimY, windowToRender->dimX, windowToRender->y, windowToRender->x);
        refresh();
        int border_offset = 0;
        //border rendering 
        if (windowToRender->box == true && windowToRender->border == true) {
            GERROR("Setted both box and border true to the CWindow() component");
            border_offset ++;
        } else if (windowToRender->border == true) {
            //full 7 character border
            if (windowToRender->win == nullptr) {
                //std window border
                border_set(&windowToRender->borderCh[0], &windowToRender->borderCh[1], &windowToRender->borderCh[2], &windowToRender->borderCh[3], 
                           &windowToRender->borderCh[4], &windowToRender->borderCh[5], &windowToRender->borderCh[6], &windowToRender->borderCh[7]);
            
            } else {        
                wborder_set(windowToRender->win, &windowToRender->borderCh[0], &windowToRender->borderCh[1], &windowToRender->borderCh[2], &windowToRender->borderCh[3], 
                                                 &windowToRender->borderCh[4], &windowToRender->borderCh[5], &windowToRender->borderCh[6], &windowToRender->borderCh[7]);
            } 
            border_offset ++;
        } else if (windowToRender->box == true){
            //2 character border
            //GDEBUG("------Rendering simple box");
            box_set(windowToRender->win, &windowToRender->boxCh[0], &windowToRender->boxCh[1]);
            border_offset ++;
        }

        //set initial cursor positions
        /*
        if (windowToRender->box == true || windowToRender->border == true) {
            e->getComponent<CCursorPosition>()->x =2; //2,2 per il bordo
            e->getComponent<CCursorPosition>()->y =2; 
        } else {
            e->getComponent<CCursorPosition>()->x =0;
            e->getComponent<CCursorPosition>()->y =0;
        }*/
        
        //image rendering:
        //...
        const std::vector<std::string>* image_asset = getAssets()->getTexture(e->getComponent<CTexture>()->name);
        //GINFO("%s", image_asset->texture.c_str());
        //only for window with border
        for(std::size_t i = 0; i<image_asset->size(); i++) {
            //i*lenLine -> i*(lenLine+1)
            //image_asset->texture
            //TODO: importare i dati effettivi
            mvwprintw(windowToRender->win, i+border_offset, border_offset, "%s", image_asset->at(i).c_str());
        }


        wrefresh(windowToRender->win);
        //refresh();
    }


    for (auto e : m_entityMang->getEntities(WINDOW_REND)) {
        //GDEBUG("------Rendering window");
        //if (e->isToRender()) { ...
        CWindow* windowToRender = e->getComponent<CWindow>();

        windowToRender->win = newwin(windowToRender->dimY, windowToRender->dimX, windowToRender->y, windowToRender->x);
        refresh();

        if (windowToRender->border == true) {
            //full 7 character border
            if (windowToRender->win == nullptr) {
                //std window border
                border_set(&windowToRender->borderCh[0], &windowToRender->borderCh[1], &windowToRender->borderCh[2], &windowToRender->borderCh[3], 
                           &windowToRender->borderCh[4], &windowToRender->borderCh[5], &windowToRender->borderCh[6], &windowToRender->borderCh[7]);
            
            } else {        
                wborder_set(windowToRender->win, &windowToRender->borderCh[0], &windowToRender->borderCh[1], &windowToRender->borderCh[2], &windowToRender->borderCh[3], 
                                                 &windowToRender->borderCh[4], &windowToRender->borderCh[5], &windowToRender->borderCh[6], &windowToRender->borderCh[7]);
            } 
        } else if (windowToRender->box == true){
            //2 character border
            //GDEBUG("------Rendering simple box");
            box_set(windowToRender->win, &windowToRender->boxCh[0], &windowToRender->boxCh[1]);
        }
        
        m_menu->renderMenu();

        wrefresh(windowToRender->win);
        //refresh();
    }
}

void scMenu::sImageNcRender(entity* ent) {
    
    //print the same image?

}


void scMenu::sRender() {
    //render only modified objects (no screen clean)
    //sStaticNcRender();
    
    //Image rendering
    /*
    for (auto e : m_entityMang->getEntities(IMAGE)){
        sImageNcRender(e);
    }*/

    //board special rendering 
    //NOTE: usually this call is needed only in the initialization and in the evential change scene, not always
    //ncRenderingBoard(m_entityMang->getEntities(BOARD));

    for (auto e : m_entityMang->getEntities(SHIP)){
        if (e->isToRender() && e->isAlive()){ 
            //distinguish between ship inisde the board and outside for different rendering 
            //ncRenderingShips(e);
        }
    }

    //NOTE: even in this case usaully is rendered only at the begining or change scene
    /*
       for (auto e : m_entityMang->getEntities(WINDOW)) {
       if (e->isToRender() && e->isAlive()){ 
    //distinguish between ship inisde the board and outside for different rendering 
    //ncRenderingWindows(e);
    }
    }*/

}


void scMenu::sDoAction(const action* act) {
    //NOTE: due modi per farlo: 
    //      1. metterci la logica delle azioni all'interno delle scene
    //      2. metterci la logica delle azioni nella classe action con classi derivate e base ecc...

    //if the actions are more then /approx 7 use switch, otherwise if/else if
    //if (act->getPhase() == 0) {    //0 for press in the enum, Ncurses do not distinguish the press/release
   
    if (act->getName() == 1) {   
        //wprintw(m_focusWindow->getComponent<CWindow>()->win, "w pressed");
        //menu up
        m_menu->moveUp();
        //m_game->changeScene(a, new scPlay());

    } else if (act->getName() == 2) {   
        //wprintw(m_focusWindow->getComponent<CWindow>()->win, "s pressed");
        //menu down
        m_menu->moveDown();

     } else if (act->getName() == 3) {   
        //wprintw(m_focusWindow->getComponent<CWindow>()->win, "d pressed");
        //nothing

    } else if (act->getName() == 4) {   
        //wprintw(m_focusWindow->getComponent<CWindow>()->win, "a pressed");
        //nothing

    } else if (act->getName() == 5) {   
        //wprintw(m_focusWindow->getComponent<CWindow>()->win, "Enter pressed");
        //menu select 
        //m_menu->select();

    }
    //m_focusWindow->getComponent<CCursorPosition>()->x = 1;
    //m_focusWindow->getComponent<CCursorPosition>()->y += 1;

    //}
    
    wrefresh(m_focusWindow->getComponent<CWindow>()->win);
    refresh();
}

