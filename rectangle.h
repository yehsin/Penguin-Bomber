#ifndef RECTANGLE_H_INCLUDED
#define RECTANGLE_H_INCLUDED
class rectangle{
public:
    rectangle() {}

    rectangle(float x, float y, float w,float h)
    {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }

    static bool isOverlap(rectangle*, rectangle*);

    int w,h;
    int x,y;
};


#endif // RECTANGLE_H_INCLUDED
