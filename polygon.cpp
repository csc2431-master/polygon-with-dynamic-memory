#include "polygon.h"
#include "point.h"

#include <iostream>
#include <sstream>
#include <cmath>
#include <string>

Polygon::Polygon(int capacity)
    : _points(nullptr), _numPoints(0), _capacity(capacity)
{
    _points = new Point*[_capacity];
    for (int i = 0; i < _capacity; ++i) {
        _points[i] = nullptr;
    }
}

Polygon::~Polygon()
{
    // Delete individual points
    for (int i = 0; i < _numPoints; ++i) {
        delete _points[i];
    }
    // Delete the array of pointers
    delete[] _points;
}

Polygon::Polygon(const Polygon& other)
    : _points(nullptr), _numPoints(other._numPoints), _capacity(other._capacity)
{
    _points = new Point*[_capacity];
    for (int i = 0; i < _capacity; ++i) {
        _points[i] = nullptr;
    }
    for (int i = 0; i < _numPoints; ++i) {
        _points[i] = new Point(*other._points[i]);
    }
}

Polygon& Polygon::operator=(const Polygon& other)
{
    if (this == &other) {
        return *this;
    }

    // Free existing resources
    for (int i = 0; i < _numPoints; ++i) {
        delete _points[i];
    }
    delete[] _points;

    // Copy size/capacity
    _capacity = other._capacity;
    _numPoints = other._numPoints;

    // Allocate new array
    _points = new Point*[_capacity];
    for (int i = 0; i < _capacity; ++i) {
        _points[i] = nullptr;
    }

    // Deep copy points
    for (int i = 0; i < _numPoints; ++i) {
        _points[i] = new Point(*other._points[i]);
    }

    return *this;
}

bool Polygon::IsConvex() const
{
    if (_numPoints < 3) return false;

    bool positive = false;
    bool negative = false;
    const double EPS = 1e-9;

    for (int i = 0; i < _numPoints; ++i) {
        const Point& p1 = *_points[i];
        const Point& p2 = *_points[(i + 1) % _numPoints];
        const Point& p3 = *_points[(i + 2) % _numPoints];

        double cross =
            (p2.GetX() - p1.GetX()) * (p3.GetY() - p2.GetY()) -
            (p2.GetY() - p1.GetY()) * (p3.GetX() - p2.GetX());

        if (cross > EPS) positive = true;
        if (cross < -EPS) negative = true;

        if (positive && negative) {
            return false; // Found both left and right turns
        }
    }

    // If all turns are collinear, you can decide if that counts as convex.
    return positive || negative; // false if all points are collinear
}

int Polygon::GetNumPoints() const
{
    return _numPoints;
}

const Point* Polygon::GetPoint(int index) const
{
    if (index < 0 || index >= _numPoints) {
        return nullptr;
    }
    return _points[index];
}

bool Polygon::SetPoint(int index, const Point& point)
{
    if (index < 0 || index >= _numPoints) {
        return false;
    }
    delete _points[index];
    _points[index] = new Point(point);
    return true;
}

bool Polygon::AddPoint(const Point& point)
{
    if (_numPoints >= _capacity) {
        return false;
    }
    _points[_numPoints] = new Point(point);
    ++_numPoints;
    return true;
}

double Polygon::Perimeter() const
{
    if (_numPoints < 2) {
        return 0.0;
    }

    double perimeter = 0.0;
    for (int i = 0; i < _numPoints; ++i) {
        const Point& current = *_points[i];
        const Point& next = *_points[(i + 1) % _numPoints]; // wrap to first
        perimeter += current.Distance(next);
    }
    return perimeter;
}

std::string Polygon::ToString() const
{
    std::ostringstream oss;
    oss << "Polygon with " << _numPoints << " points: ";
    for (int i = 0; i < _numPoints; ++i) {
        oss << _points[i]->ToString();
        if (i < _numPoints - 1) {
            oss << ", ";
        }
    }
    return oss.str();
}

PointLocation Polygon::LocatePoint(const Point& point) const{
    return PointLocation::Invalid;
}
bool Polygon::ExportToSVG(const string& filename, int width, int height) const{
    return false;
}