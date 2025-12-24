#include <iostream>
#include <cmath>
#include <string>

#include "point.h"
#include "polygon.h"

struct TestStats {
    int passed = 0;
    int failed = 0;
};

static const double EPS = 1e-9;

void Report(const std::string& name, bool condition, TestStats& stats) {
    if (condition) {
        ++stats.passed;
    } else {
        ++stats.failed;
        std::cerr << "[FAIL] " << name << std::endl;
    }
}

bool AlmostEqual(double a, double b, double eps = EPS) {
    return std::fabs(a - b) <= eps;
}

// Macros (optional, just sugar)
#define ASSERT_TRUE(name, cond, stats) \
    Report(name, (cond), stats)

#define ASSERT_CLOSE(name, a, b, stats) \
    Report(name, AlmostEqual((a), (b)), stats)


// ----------------- Tests -----------------

void TestPointBasics(TestStats& stats) {
    std::cout << "Running TestPointBasics...\n";

    Point p1(0.0, 0.0);
    Point p2(3.0, 4.0);

    ASSERT_TRUE("Point::GetX p1", p1.GetX() == 0.0, stats);
    ASSERT_TRUE("Point::GetY p1", p1.GetY() == 0.0, stats);

    ASSERT_TRUE("Point::GetX p2", p2.GetX() == 3.0, stats);
    ASSERT_TRUE("Point::GetY p2", p2.GetY() == 4.0, stats);

    double dist = p1.Distance(p2);
    ASSERT_CLOSE("Point::Distance p1->p2 == 5", dist, 5.0, stats);

    ASSERT_TRUE("Point::Equals false", !p1.Equals(p2), stats);

    Point p3(0.0, 0.0);
    ASSERT_TRUE("Point::Equals true", p1.Equals(p3), stats);
}

void TestPolygonSquareConvex(TestStats& stats) {
    std::cout << "Running TestPolygonSquareConvex...\n";

    Polygon square(4);
    bool addOk = true;
    addOk = addOk && square.AddPoint(Point(0.0, 0.0));
    addOk = addOk && square.AddPoint(Point(1.0, 0.0));
    addOk = addOk && square.AddPoint(Point(1.0, 1.0));
    addOk = addOk && square.AddPoint(Point(0.0, 1.0));

    ASSERT_TRUE("Polygon::AddPoint square all ok", addOk, stats);
    ASSERT_TRUE("Polygon::GetNumPoints == 4", square.GetNumPoints() == 4, stats);

    double per = square.Perimeter();
    ASSERT_CLOSE("Polygon::Perimeter square == 4", per, 4.0, stats);

    ASSERT_TRUE("Polygon::IsConvex square", square.IsConvex(), stats);

    const Point* p = square.GetPoint(2);
    ASSERT_TRUE("Polygon::GetPoint valid index", p != nullptr, stats);
    if (p) {
        ASSERT_TRUE("Polygon::GetPoint(2) == (1,1)",
                    AlmostEqual(p->GetX(), 1.0) && AlmostEqual(p->GetY(), 1.0),
                    stats);
    }

    ASSERT_TRUE("Polygon::GetPoint invalid index returns nullptr",
                square.GetPoint(10) == nullptr, stats);

    // Test SetPoint
    bool setOk = square.SetPoint(2, Point(2.0, 1.0));
    ASSERT_TRUE("Polygon::SetPoint valid index", setOk, stats);
    const Point* pNew = square.GetPoint(2);
    ASSERT_TRUE("Polygon::GetPoint after SetPoint != nullptr", pNew != nullptr, stats);
    if (pNew) {
        ASSERT_TRUE("Polygon::SetPoint updated coordinates",
                    AlmostEqual(pNew->GetX(), 2.0) && AlmostEqual(pNew->GetY(), 1.0),
                    stats);
    }
}

void TestPolygonConcave(TestStats& stats) {
    std::cout << "Running TestPolygonConcave...\n";

    Polygon concave(5);
    bool addOk = true;
    addOk = addOk && concave.AddPoint(Point(0.0, 0.0));
    addOk = addOk && concave.AddPoint(Point(2.0, 0.0));
    addOk = addOk && concave.AddPoint(Point(2.0, 2.0));
    addOk = addOk && concave.AddPoint(Point(1.0, 1.0)); // inward dent
    addOk = addOk && concave.AddPoint(Point(0.0, 2.0));

    ASSERT_TRUE("Polygon::AddPoint concave all ok", addOk, stats);
    ASSERT_TRUE("Polygon::GetNumPoints concave == 5", concave.GetNumPoints() == 5, stats);

    ASSERT_TRUE("Polygon::IsConvex concave == false", !concave.IsConvex(), stats);
}

void TestPolygonCopyAndAssign(TestStats& stats) {
    std::cout << "Running TestPolygonCopyAndAssign...\n";

    // Base polygon (a triangle)
    Polygon base(3);
    base.AddPoint(Point(0.0, 0.0));
    base.AddPoint(Point(1.0, 0.0));
    base.AddPoint(Point(0.0, 1.0));

    double basePer = base.Perimeter();

    // Copy constructor
    Polygon copy(base);
    ASSERT_TRUE("Copy ctor: same number of points",
                copy.GetNumPoints() == base.GetNumPoints(), stats);
    ASSERT_CLOSE("Copy ctor: same perimeter", copy.Perimeter(), basePer, stats);
    ASSERT_TRUE("Copy ctor: IsConvex matches",
                copy.IsConvex() == base.IsConvex(), stats);

    // Assignment operator
    Polygon assigned(5);
    assigned.AddPoint(Point(10.0, 10.0)); // some dummy content
    assigned = base;

    ASSERT_TRUE("Assign: same number of points",
                assigned.GetNumPoints() == base.GetNumPoints(), stats);
    ASSERT_CLOSE("Assign: same perimeter", assigned.Perimeter(), basePer, stats);
    ASSERT_TRUE("Assign: IsConvex matches",
                assigned.IsConvex() == base.IsConvex(), stats);
}
void TestPolygonLocatePoint(TestStats& stats) {
    std::cout << "Running TestPolygonLocatePoint...\n";

    // ---------------------------
    // Polygon #1: Unit square
    // (0,0) -> (2,0) -> (2,2) -> (0,2)
    // ---------------------------
    Polygon square(4);
    bool addOk1 = true;
    addOk1 = addOk1 && square.AddPoint(Point(0.0, 0.0));
    addOk1 = addOk1 && square.AddPoint(Point(2.0, 0.0));
    addOk1 = addOk1 && square.AddPoint(Point(2.0, 2.0));
    addOk1 = addOk1 && square.AddPoint(Point(0.0, 2.0));
    // ASSERT_TRUE("LocatePoint setup: square AddPoint ok", addOk1, stats);

    // Inside (2 tests)
    ASSERT_TRUE("LocatePoint square inside #1",
                square.LocatePoint(Point(1.0, 1.0)) == PointLocation::Inside, stats);
    ASSERT_TRUE("LocatePoint square inside #2",
                square.LocatePoint(Point(0.25, 1.75)) == PointLocation::Inside, stats);

    // Outside (2 tests)
    ASSERT_TRUE("LocatePoint square outside #1",
                square.LocatePoint(Point(3.0, 1.0)) == PointLocation::Outside, stats);
    ASSERT_TRUE("LocatePoint square outside #2",
                square.LocatePoint(Point(-0.5, -0.5)) == PointLocation::Outside, stats);

    // On edge (2 tests)
    ASSERT_TRUE("LocatePoint square on-edge #1 (bottom edge)",
                square.LocatePoint(Point(1.0, 0.0)) == PointLocation::OnEdge, stats);
    ASSERT_TRUE("LocatePoint square on-edge #2 (left edge)",
                square.LocatePoint(Point(0.0, 1.0)) == PointLocation::OnEdge, stats);


    // ---------------------------
    // Polygon #2: Convex pentagon (non-regular)
    // (0,0) -> (3,0) -> (4,2) -> (2,4) -> (-1,2)
    // ---------------------------
    Polygon pentagon(5);
    bool addOk2 = true;
    addOk2 = addOk2 && pentagon.AddPoint(Point(0.0, 0.0));
    addOk2 = addOk2 && pentagon.AddPoint(Point(3.0, 0.0));
    addOk2 = addOk2 && pentagon.AddPoint(Point(4.0, 2.0));
    addOk2 = addOk2 && pentagon.AddPoint(Point(2.0, 4.0));
    addOk2 = addOk2 && pentagon.AddPoint(Point(-1.0, 2.0));
    // ASSERT_TRUE("LocatePoint setup: pentagon AddPoint ok", addOk2, stats);

    // (Optional sanity) ensure convex as intended
    // ASSERT_TRUE("LocatePoint setup: pentagon IsConvex == true", pent.IsConvex(), stats);

    // Inside (2 tests)
    ASSERT_TRUE("LocatePoint pentagon inside #1",
                pentagon.LocatePoint(Point(2.0, 2.0)) == PointLocation::Inside, stats);
    ASSERT_TRUE("LocatePoint pentagon inside #2",
                pentagon.LocatePoint(Point(1.0, 1.0)) == PointLocation::Inside, stats);

    // Outside (2 tests)
    ASSERT_TRUE("LocatePoint pentagon outside #1",
                pentagon.LocatePoint(Point(5.0, 2.0)) == PointLocation::Outside, stats);
    ASSERT_TRUE("LocatePoint pentagon outside #2",
                pentagon.LocatePoint(Point(-2.0, 3.0)) == PointLocation::Outside, stats);

    // On edge (2 tests)
    // On edge between (0,0) and (3,0)
    ASSERT_TRUE("LocatePoint pentagon on-edge #1 (bottom edge)",
                pentagon.LocatePoint(Point(2.0, 0.0)) == PointLocation::OnEdge, stats);
    // On edge between (4,2) and (2,4): midpoint (3,3)
    ASSERT_TRUE("LocatePoint pentagon on-edge #2 (diagonal edge midpoint)",
                pentagon.LocatePoint(Point(3.0, 3.0)) == PointLocation::OnEdge, stats);
}


// ----------------- main -----------------

int main() {
    TestStats stats;

    TestPointBasics(stats);
    TestPolygonSquareConvex(stats);
    TestPolygonConcave(stats);
    TestPolygonCopyAndAssign(stats);
    TestPolygonLocatePoint(stats);    

    std::cout << "\n=== TEST SUMMARY ===\n";
    std::cout << "Passed: " << stats.passed << "\n";
    std::cout << "Failed: " << stats.failed << "\n";

    if (stats.failed > 0) {
        std::cout << "Some tests FAILED.\n";
        return 1;
    } else {
        std::cout << "All tests PASSED.\n";
        return 0;
    }
}