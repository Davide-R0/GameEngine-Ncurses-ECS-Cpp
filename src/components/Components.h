#ifndef COMPONENTS_H
#define COMPONENTS_H


class CTransform {
    public:
        void setXY(int X, int Y);
        int getX() const;
        int getY() const;
    private:
        int x = 0;
        int y = 0;
};

#endif 
