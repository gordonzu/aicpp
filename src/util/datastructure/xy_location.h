// gordon zuehlke on 8/26/18

#ifndef XYLOCATION_H 
#define XYLOCATION_H

#include <iostream>
#include <memory>

class XYLocation {
public:
    XYLocation();
    XYLocation(int x, int y);
    ~XYLocation();
    XYLocation(const XYLocation& other);
    XYLocation(XYLocation& other);

    XYLocation& operator=(const XYLocation& rhs);
    bool operator==(const XYLocation& rhs) const; 
    bool operator<(const XYLocation& rhs) const;
    bool operator!=(const XYLocation& rhs) const;
    friend std::ostream& operator<<(std::ostream& out, const XYLocation& xy);

    void print();
    enum class Direction: unsigned short{ NORTH, SOUTH, EAST, WEST };

    int getx() const;
    int gety() const;

    XYLocation west();
    XYLocation east();
    XYLocation north();
    XYLocation south();
    XYLocation left();
    XYLocation right();
    XYLocation up();
    XYLocation down();
    XYLocation location_at(const Direction& direction);

private:
    int x_;
    int y_;
};
#endif

