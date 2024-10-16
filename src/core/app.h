#ifndef APP_H
#define APP_H

class gameEngine;

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

        gameEngine* getEngine() const;

    private:
        /**********************************/
        app() {}; //constructor
        static app* s_app;
        /**********************************/
        
        bool initApp();
        bool initGame();
        bool endGame();
        
        gameEngine* m_game;
        
};


#endif 
