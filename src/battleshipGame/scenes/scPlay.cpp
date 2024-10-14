#include "scPlay.h"
#include "../../core/logger.h"
#include "../../entities/entity.h"
#include "../../entities/entityMang.h"
#include "../../components/Components.h"
#include "../../actions/action.h"
#include "../../actions/actionConstants.h"
#include "../../assets/assets.h"

//wide character ncurses varaint
//#define NCURSES_WIDECHAR 1    //???
//#define _XOPEN_SOURCE 700 
#include <ncursesw/ncurses.h>
//#include <ncursesw/curses.h>

//#include "gameEngine.h"

scPlay::scPlay() {
    GTRACE("Scene play class constructor called");
    init();
}

scPlay::~scPlay() {
    GTRACE("Scene play class destructor called");

    //TODO: free memory
    delete m_entityMang;
    delete m_player;

    //do not delete m_game
}

//before a scene change call a prerendering function to render the static object on the screen (like the board, the windows, ecc..)

void scPlay::update() {
     GDEBUG("scplay update");
    m_entityMang->update();

    //wmove(m_focusWindow->getComponent<CWindow>()->win, m_focusWindow->getComponent<CCursorPosition>()->y, m_focusWindow->getComponent<CCursorPosition>()->x); //move cursor

    if (!isPaused()) {
        //call systems ...
    }

    m_currentFrame++;
}

void scPlay::init() {
     GDEBUG("Init scene PLAY");
    //Initialization assets
    //getAssets()->addNcTexture(BASE, "assets/textures/texture.txt");

    //getAssets()->addNcTexture(BASE, "assets/textures/texture.txt"); //give an error log is try to rewrite the same texture (but it will rewrite anyway)

    //Initialization action map
    //dichiarare questa variabile oppure ricordarsi l'indice dell'enum...
    //i KEY_.. sono i valori di default di ncurses per i tasti 
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
    m_entityMang->addEntity(BOARD);
    //-points window

    //-remaining ship window

    //-info bar on the bottom

    m_entityMang->addEntity(PLAYER);

    m_entityMang->addEntity(BOARD);

        
    //m_entityMang->update();

    //m_entityMang->removeEntity(PLAYER, m_entityMang->getEntities(PLAYER)[0]->getId());
    m_entityMang->addEntity(WINDOW_REND);   //board window 
    m_entityMang->addEntity(WINDOW_REND);   //command window 
    m_entityMang->addEntity(WINDOW_REND);   //points window 
    m_entityMang->addEntity(WINDOW_REND); //remaining ships window
    m_entityMang->update();
    
    

    //setting ocmponents
    
    //board window
    m_entityMang->getEntities(WINDOW_REND)[0]->addComponent<CWindow>(new CWindow());
    m_entityMang->getEntities(WINDOW_REND)[0]->addComponent<CCursorPosition>(new CCursorPosition());
    CWindow* window = m_entityMang->getEntities(WINDOW_REND)[0]->getComponent<CWindow>();
    window->x = 1;
    window->y = 1;
    window->dimX = (int)xScr*0.8 - 1;
    window->dimY = yScr-4;  //space for command line
    window->border = true;
    
    //command window 
    m_entityMang->getEntities(WINDOW_REND)[1]->addComponent<CWindow>(new CWindow());
    m_entityMang->getEntities(WINDOW_REND)[1]->addComponent<CCursorPosition>(new CCursorPosition());
    window = m_entityMang->getEntities(WINDOW_REND)[1]->getComponent<CWindow>();
    window->x = 1;
    window->y = yScr-3;
    window->dimX = xScr-1;
    window->dimY = 3;  
    window->border = true;

    //points window 
    m_entityMang->getEntities(WINDOW_REND)[2]->addComponent<CWindow>(new CWindow());
    m_entityMang->getEntities(WINDOW_REND)[2]->addComponent<CCursorPosition>(new CCursorPosition());
    window = m_entityMang->getEntities(WINDOW_REND)[2]->getComponent<CWindow>();
    window->x = (int)xScr*0.8;
    window->y = 1;
    window->dimX = (int)xScr*0.2-1;
    window->dimY = (int)yScr*0.2-2;
    window->border = true;

    //remaining ships window 
    m_entityMang->getEntities(WINDOW_REND)[3]->addComponent<CWindow>(new CWindow());
    m_entityMang->getEntities(WINDOW_REND)[3]->addComponent<CCursorPosition>(new CCursorPosition());
    window = m_entityMang->getEntities(WINDOW_REND)[3]->getComponent<CWindow>();
    window->x = (int)xScr*0.8;
    window->y = (int)yScr*0.2-1;
    window->dimX = (int)xScr*0.2-1;
    window->dimY = (int)yScr*0.8-1;  
    window->border = true;
    
    sStaticNcRender();
    //choose the window on focus
    m_focusWindow = m_entityMang->getEntities(WINDOW_REND)[0];
    m_focusWindow->getComponent<CCursorPosition>()->x = 1;
    m_focusWindow->getComponent<CCursorPosition>()->y = 1;
    wmove(m_focusWindow->getComponent<CWindow>()->win, m_focusWindow->getComponent<CCursorPosition>()->y, m_focusWindow->getComponent<CCursorPosition>()->x); //move cursor
    wrefresh(m_focusWindow->getComponent<CWindow>()->win);
    
    //cursor visibility
    curs_set(0);    //0 = invisible
                    //1 = terminal specific
                    //2 = always

/*
    setcchar(&window->borderCh[0], L"║", 0, 0, nullptr);
    setcchar(&window->borderCh[1], L"║", 0, 0, nullptr);
    setcchar(&window->borderCh[2], L"═", 0, 0, nullptr);
    setcchar(&window->borderCh[3], L"═", 0, 0, nullptr);
    setcchar(&window->borderCh[4], L"╔", 0, 0, nullptr);
*/

    //BUT if the component have a constructor with logic is necessary to call the constructor each time the new component is added, like this: (there is no other way to do this)
    m_entityMang->getEntities(BOARD)[0]->addComponent<CInput>(new CInput());
    m_entityMang->getEntities(BOARD)[0]->addComponent<CTransform>(new CTransform(10,10));
    //m_entityMang->getEntities(BOARD)[0]->addComponent<CTransform>(new CTransform(10,10));   //note if tryng to add two same componets on the same entity the second will be destructed by default
    
    //and to access che component:    
    GDEBUG("Component name %s", m_entityMang->getEntities(BOARD)[0]->getComponent<CTransform>()->name);

    //so if all the constructor of all components are empty (this mean that there must not be any private variable(?) or const value) you can let entity class create and destroy all components 

    //m_entityMang->getEntities(BOARD)[0]->~entity();

    m_player = new entity(PLAYER, -1);
    m_player->addComponent<CInput>(new CInput());
    
     GDEBUG("End init Sene PLAY");

    

    /*
    move(x, y); //on the same screen??
    move(win, x, y); 
    //call refresh() after
    */

}
/*
void scPlay::sPrintwNc(int x, int y, string...){
    //stanpa la stringa sulla finestra attualmente con focus (m_windowOnFOcus) e fa una serie di verifiche per i bordi e fine della finestra
    //puo anche non prendere argomenti x, y e stampa dove è il cursore
}*/

void scPlay::sStaticNcRender() {
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
        

        wrefresh(windowToRender->win);
        //refresh();
    }
}

void scPlay::sRender() {
    //render only modified objects (no screen clean)
    //sStaticNcRender();

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

void scPlay::sDoAction(const action* act) {
    //NOTE: due modi per farlo: 
    //      1. metterci la logica delle azioni all'interno delle scene
    //      2. metterci la logica delle azioni nella classe action con classi derivate e base ecc...

    //if the actions are more then /approx 7 use switch, otherwise if/else if
    //if (act->getPhase() == 0) {    //0 for press in the enum, Ncurses do not distinguish the press/release
   
    if (act->getName() == 1) {   
        wprintw(m_focusWindow->getComponent<CWindow>()->win, "w pressed");
        
    } else if (act->getName() == 2) {   
        wprintw(m_focusWindow->getComponent<CWindow>()->win, "s pressed");

    } else if (act->getName() == 3) {   
        wprintw(m_focusWindow->getComponent<CWindow>()->win, "d pressed");

    } else if (act->getName() == 4) {   
        wprintw(m_focusWindow->getComponent<CWindow>()->win, "a pressed");

    } else if (act->getName() == 5) {   
        wprintw(m_focusWindow->getComponent<CWindow>()->win, "Enter pressed");

    }
    m_focusWindow->getComponent<CCursorPosition>()->x = 1;
    m_focusWindow->getComponent<CCursorPosition>()->y += 1;

    //}
    
    wrefresh(m_focusWindow->getComponent<CWindow>()->win);
    refresh();
}

/*
   void gameEngine::sRender() {
//clear window
clear();

for (auto e : m_entityMang->getEntities()){
if (e->isToRender() && e->isAlive()){ 
ncRendering(e);
}
}

//display
}
*//*
     void game::sNcCollide(std::shared_ptr<entity> a, std::shared_ptr<entity> b) {
//a->cCollisionShapeNc->mask_layer ...
//string della dimensione della board
//per ogni elemento (a, b) controllare che le posizioni non escano dalla board
//iterare lungo ogni nave e stamparla nella string controllando che la casella non sia già piena
}
*/
/*
   void gameEngine::sCollision() {
//colliison between ship 
*//*
     for (auto e : m_entityMang->getEntities(SHIP)){
//collion detection only if it have collision shape component
if (e->cCollisionShapeNc != nullptr) {
//e->cCollisionShapeNc->mask_layer ...
//string della dimensione della board
//per ogni elemento (a, b) controllare che le posizioni non escano dalla board
//iterare lungo ogni nave e stamparla nella string controllando che la casella non sia già piena
//fare il tutto per ogni board nel caso 

//alternativa non giusta
for (auto b : m_entityMang->getEntities(SHIP)) {
if (b->cCollisionShapeNc != nullptr) {
//sNcCollide(e, b);
}
}
}
}
//collision with board ????
*/
/*
   }*/

