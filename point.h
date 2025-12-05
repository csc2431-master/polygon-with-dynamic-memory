#ifndef POINT_H
#define POINT_H

#include <string>

/**
 * @class Point
 * @brief Represents a point in 2D Cartesian space.
 */
class Point
{
private:
    double _x; ///< X-coordinate of the point.
    double _y; ///< Y-coordinate of the point.

public:
    /**
     * @brief Constructs a point with the given coordinates.
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     */
    Point(double x, double y);

    /**
     * @brief Gets the x-coordinate of the point.
     * @return The x-coordinate.
     */
    double GetX() const;

    /**
     * @brief Gets the y-coordinate of the point.
     * @return The y-coordinate.
     */
    double GetY() const;

    /**
     * @brief Sets the x-coordinate of the point.
     * @param x The new x-coordinate.
     */
    void SetX(double x);

    /**
     * @brief Sets the y-coordinate of the point.
     * @param y The new y-coordinate.
     */
    void SetY(double y);

    /**
     * @brief Returns a string representation of the point.
     * @return A string in the form "(x, y)".
     */
    std::string ToString() const;

    /**
     * @brief Computes the Euclidean distance to another point.
     * @param other The other point.
     * @return The distance between this point and @p other.
     */
    double Distance(const Point& other) const;

    /**
     * @brief Compares this point with another for equality.
     *
     * Two points are considered equal if both their coordinates are equal.
     * @param other The point to compare with.
     * @return true if the points have the same coordinates, false otherwise.
     */
    bool Equals(const Point& other) const;
};

#endif