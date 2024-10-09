#ifndef ACTION_H
#define ACTION_H

//actions are also called commands some times 

#include "actionConstants.h"

//specify the input in each frame (more efficent)
//or specify a start in a frame and a end in another

class action {
    public:
        action();
        action(const ACTION_NAME& name, const ACTION_PHASE& phase);
        ~action();
        
        const ACTION_NAME& getName() const;
        const ACTION_PHASE& getPhase() const;

        //void doAction();
    
    private:
        ACTION_NAME m_name;
        ACTION_PHASE m_phase; 
};

#endif 
