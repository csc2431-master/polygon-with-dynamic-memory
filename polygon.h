#ifndef POLYGON_H
#define POLYGON_H

#include <string>
#include "point.h"
using std::string;
enum class PointLocation
{
    Invalid = -1,
    Inside,
    Outside,
    OnEdge
};

/**
 * @class Polygon
 * @brief Represents a simple polygon in 2D as an ordered sequence of points.
 *
 * The polygon owns its points and stores them as pointers in a dynamic array.
 * The first @c _numPoints entries in the internal array are assumed to be valid.
 */
class Polygon
{
private:
    Point** _points;   ///< Array of pointers to points (owned by the polygon).
    int _numPoints;    ///< Current number of points stored in the polygon.
    int _capacity;     ///< Maximum number of points the polygon can hold.

public:
    /**
     * @brief Constructs a polygon with a given capacity.
     *
     * Initially the polygon contains zero points. The capacity determines
     * the maximum number of points that can be stored.
     *
     * @param capacity The maximum number of points the polygon can hold.
     */
    Polygon(int capacity);

    /**
     * @brief Destructor that frees all dynamically allocated points and the array.
     */
    ~Polygon();

    /**
     * @brief Copy constructor. Performs a deep copy of the other polygon.
     * @param other The polygon to copy from.
     */
    Polygon(const Polygon& other);

    /**
     * @brief Copy-assignment operator. Performs a deep copy of the other polygon.
     * @param other The polygon to assign from.
     * @return A reference to this polygon after assignment.
     */
    Polygon& operator=(const Polygon& other);

    /**
     * @brief Checks whether the polygon is convex.
     *
     * The polygon is assumed to be simple and its vertices are assumed to be in
     * order (clockwise or counterclockwise). The method examines the signed
     * cross products of consecutive edges and returns true if all turns are in
     * the same direction (or collinear).
     *
     * @return true if the polygon is convex, false otherwise.
     */
    bool IsConvex() const;

    /**
     * @brief Gets the current number of points in the polygon.
     * @return The number of points.
     */
    int GetNumPoints() const;

    /**
     * @brief Returns a pointer to the point at the given index.
     *
     * @param index The index of the point in the range [0, GetNumPoints()).
     * @return A const pointer to the point if the index is valid, nullptr otherwise.
     */
    const Point* GetPoint(int index) const;

    /**
     * @brief Sets (replaces) the point at the given index.
     *
     * The existing point at @p index is deleted and replaced with a copy of @p point.
     *
     * @param index The index at which to set the point (must be in [0, GetNumPoints())).
     * @param point The point to store at the given index.
     * @return true if the index was valid and the point was set, false otherwise.
     */
    bool SetPoint(int index, const Point& point);

    /**
     * @brief Adds a new point at the end of the polygon.
     *
     * If the polygon is already at capacity, the method returns false.
     *
     * @param point The point to add.
     * @return true if the point was added successfully, false if the polygon is full.
     */
    bool AddPoint(const Point& point);

    /**
     * @brief Computes the perimeter of the polygon.
     *
     * The perimeter is defined as the sum of the distances between consecutive
     * points, including the closing edge between the last and the first point.
     *
     * @return The perimeter length. Returns 0.0 if there are fewer than 2 points.
     */
    double Perimeter() const;

    /**
     * @brief Returns a string representation of the polygon.
     *
     * The representation includes the number of points and the coordinates of
     * each point.
     *
     * @return A string describing the polygon.
     */
    std::string ToString() const;

    /**
     * @brief Determines the location of a point relative to the polygon.
     *
     * In here you will describe the algorithm you used to implement this method.
     *
     * @param point The point to test.
     * @return PointLocation::Inside if the point is inside the polygon,
     *         PointLocation::Outside if outside, and
     *         PointLocation::OnEdge if on the edge.
     */
    PointLocation LocatePoint(const Point& point) const;
    /**
     * @brief Exports the polygon to an SVG file.
     *
     * The SVG file will contain a visual representation of the polygon
     * within a canvas of the specified width and height.
     *
     * @param filename The name of the SVG file to create.
     * @param width The width of the SVG canvas.
     * @param height The height of the SVG canvas.
     * @return true if the export was successful, false otherwise.
     */
    bool ExportToSVG(const string& filename, int width, int height) const;
};

#endif // POLYGON_H
