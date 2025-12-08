#include <iostream>
#include "point.h"
#include "polygon.h"

int main(int argc, char* argv[])
{
    std::cout << sizeof(Point) << "\n";
    std::cout << "=== Testing Point ===\n";
    Point p1(0.0, 0.0);
    Point p2(3.0, 4.0);

    std::cout << "p1: " << p1.ToString() << "\n";
    std::cout << "p2: " << p2.ToString() << "\n";
    std::cout << "Distance p1->p2: " << p1.Distance(p2) << " (expected 5)\n";
    std::cout << "p1.Equals(p2): " << (p1.Equals(p2) ? "true" : "false") << "\n\n";

    std::cout << "=== Testing Polygon (square) ===\n";
    Polygon square(4);
    square.AddPoint(Point(0.0, 0.0));
    square.AddPoint(Point(1.0, 0.0));
    square.AddPoint(Point(1.0, 1.0));
    square.AddPoint(Point(0.0, 1.0));

    std::cout << square.ToString() << "\n";
    std::cout << "Num points: " << square.GetNumPoints() << "\n";
    std::cout << "Perimeter: " << square.Perimeter() << " (expected 4)\n";
    std::cout << "IsConvex: " << (square.IsConvex() ? "true" : "false") << " (expected true)\n\n";

    std::cout << "Testing GetPoint and SetPoint:\n";
    const Point* sp = square.GetPoint(2);
    if (sp) {
        std::cout << "Point at index 2: " << sp->ToString() << "\n";
    }
    square.SetPoint(2, Point(2.0, 1.0)); // stretch the square a bit
    std::cout << "After SetPoint(2, (2,1)): " << square.ToString() << "\n";
    std::cout << "New perimeter: " << square.Perimeter() << "\n\n";

    std::cout << "=== Testing Polygon (concave) ===\n";
    Polygon concave(5);
    concave.AddPoint(Point(0.0, 0.0));
    concave.AddPoint(Point(2.0, 0.0));
    concave.AddPoint(Point(2.0, 2.0));
    concave.AddPoint(Point(1.0, 1.0)); // "dent" inward → concave
    concave.AddPoint(Point(0.0, 2.0));

    std::cout << concave.ToString() << "\n";
    std::cout << "IsConvex: " << (concave.IsConvex() ? "true" : "false")
              << " (expected false)\n\n";

    std::cout << "=== Testing copy constructor ===\n";
    Polygon copySquare(square);
    std::cout << "Copy of square: " << copySquare.ToString() << "\n";
    std::cout << "IsConvex (copy): " << (copySquare.IsConvex() ? "true" : "false") << "\n\n";

    std::cout << "=== Testing assignment operator ===\n";
    Polygon assigned(3);
    assigned.AddPoint(Point(-1.0, -1.0));
    assigned.AddPoint(Point(-2.0, -2.0));
    std::cout << "Before assignment: " << assigned.ToString() << "\n";
    assigned = concave;
    std::cout << "After assignment from concave: " << assigned.ToString() << "\n";
    std::cout << "IsConvex (assigned): " << (assigned.IsConvex() ? "true" : "false") << "\n\n";

    std::cout << "All tests finished.\n";
    return 0;
}
