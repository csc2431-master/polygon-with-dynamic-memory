#include "point.h"
#include <cmath>

Point::Point(double x, double y) : _x(x), _y(y) {}

void Point::SetX(double x) {
    this->_x = x;
}

void Point::SetY(double y) {
    this->_y = y;
}

double Point::GetX() const {
    return _x;
}

double Point::GetY() const {
    return _y;
}

double Point::Distance(const Point& other) const {
    double dx = _x - other._x;
    double dy = _y - other._y;
    return std::sqrt(dx * dx + dy * dy);
}

std::string Point::ToString() const {
    return "(" + std::to_string(_x) + ", " + std::to_string(_y) + ")";
}

bool Point::Equals(const Point& other) const {
    return _x == other._x && _y == other._y;
}