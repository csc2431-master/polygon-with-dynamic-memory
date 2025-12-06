#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "point.h"
#include "polygon.h"

struct TestStats {
    int passed = 0;
    int failed = 0;
};

static const double EPS = 1e-2; // tolerant because file perimeters are rounded

void Report(const std::string& name, bool cond, TestStats& stats) {
    if (cond) {
        ++stats.passed;
    } else {
        ++stats.failed;
        std::cerr << "[FAIL] " << name << std::endl;
    }
}

bool AlmostEqual(double a, double b, double eps = EPS) {
    return std::fabs(a - b) <= eps;
}

int main() {
    std::ifstream fin("data/polygons.txt");
    if (!fin.is_open()) {
        std::cerr << "Error: cannot open polygons.txt\n";
        return 1;
    }

    TestStats stats;
    int polygonIndex = 0;

    while (true) {
        int n;
        if (!(fin >> n)) {
            break; // no more polygons
        }
        ++polygonIndex;

        Polygon poly(n);

        // Read n points as "x,y"
        for (int i = 0; i < n; ++i) {
            double x, y;
            char comma;
            if (!(fin >> x >> comma >> y) || comma != ',') {
                std::cerr << "[ERROR] Bad point format in polygon " << polygonIndex << "\n";
                return 1;
            }
            poly.AddPoint(Point(x, y));
        }

        // Read expected convex flag ("Yes" / "No")
        std::string convexStr;
        if (!(fin >> convexStr)) {
            std::cerr << "[ERROR] Missing convex flag in polygon " << polygonIndex << "\n";
            return 1;
        }
        bool expectedConvex =
            (convexStr == "Yes" || convexStr == "yes" ||
             convexStr == "Y"   || convexStr == "y");

        // Read expected number of points
        int expectedNumPoints;
        if (!(fin >> expectedNumPoints)) {
            std::cerr << "[ERROR] Missing expectedNumPoints in polygon " << polygonIndex << "\n";
            return 1;
        }

        // Read expected perimeter
        double expectedPerimeter;
        if (!(fin >> expectedPerimeter)) {
            std::cerr << "[ERROR] Missing expectedPerimeter in polygon " << polygonIndex << "\n";
            return 1;
        }

        std::cout << "=== Polygon " << polygonIndex << " ===\n";
        std::cout << poly.ToString() << "\n";

        // ---- Actual values from code ----
        int actualNumPoints = poly.GetNumPoints();
        bool actualConvex   = poly.IsConvex();
        double actualPerimeterRaw = poly.Perimeter();
        double actualEffectivePerimeter =
            actualConvex ? actualPerimeterRaw : 0.0;

        // ---- Tests ----
        Report("NumPoints matches",
               actualNumPoints == expectedNumPoints, stats);

        Report("Convex flag matches",
               actualConvex == expectedConvex, stats);

        // If the polygon is not convex, we REQUIRE expectedPerimeter == 0
        if (!actualConvex) {
            Report("Non-convex ⇒ expectedPerimeter == 0",
                   AlmostEqual(expectedPerimeter, 0.0), stats);
        }

        Report("Effective perimeter matches expected",
               AlmostEqual(actualEffectivePerimeter, expectedPerimeter), stats);

        std::cout << "Actual convex: "      << (actualConvex ? "Yes" : "No") << "\n";
        std::cout << "Actual perimeter: "   << actualPerimeterRaw << "\n";
        std::cout << "Effective perimeter: "<< actualEffectivePerimeter << "\n";
        std::cout << "Expected convex: "    << convexStr << "\n";
        std::cout << "Expected perimeter: " << expectedPerimeter << "\n\n";
    }

    std::cout << "=== TEST SUMMARY ===\n";
    std::cout << "Passed: " << stats.passed << "\n";
    std::cout << "Failed: " << stats.failed << "\n";

    return (stats.failed == 0) ? 0 : 1;
}