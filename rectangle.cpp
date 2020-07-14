#include "rectangle.h"
#include<iostream>
#include<algorithm>
using namespace std;
bool
rectangle::isOverlap(rectangle *Re_1, rectangle *Re_2)
{
    if(max(Re_1->x,Re_2->x) - min(Re_1->x , Re_2->x) < (Re_1->x<Re_2->x?Re_1->w:Re_2->w)){
        if(max(Re_1->y,Re_2->y) - min(Re_1->y , Re_2->y) < (Re_1->y<Re_2->y?Re_1->h:Re_2->h)) return true;
    }

    return false;
}
