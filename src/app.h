#ifndef APP_H
#define APP_H

class game;

class app {
    public:
        /**********************************/
        app(const app &other) = delete;
        void operator=(const app&) = delete;
        static app *getInstance();
        /**********************************/
        
        ~app();

        void start();

        void end();

    private:
        /**********************************/
        app() {}; //constructor
        static app* s_app;
        /**********************************/
        
        game* m_game;

        bool initApp();
        bool initGame();
        bool endApp();
        bool endGame();
    
        int m_xScr, m_yScr;
};


#endif 
