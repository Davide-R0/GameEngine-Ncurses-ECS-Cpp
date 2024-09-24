#ifndef APP_H
#define APP_H

#include <iostream>
#include <ncurses.h>

class app {
    public:
        /**********************************/
        app(const app &other) = delete;
        void operator=(const app&) = delete;
        static app *getInstance();
        /**********************************/
       
        void start();

        bool initApp();
        
        void loopApp();

        void end();

        bool endApp();
    private:
        /**********************************/
        app() {}; //constructor
        static app* s_app;
        /**********************************/


};


#endif 
