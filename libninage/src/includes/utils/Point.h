#ifndef POINT_H
#define POINT_H

/**
 * @deprecated
 */
class Point {
    public:
        Point(float x, float y);

        float x;
        float y;

        void setPosition(float x, float y);
};

#endif