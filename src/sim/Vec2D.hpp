#include <cmath>
#include <SFML/Graphics.hpp>

// const float pi  = 3.14159265358979323846f;
// const float deg = 180.0f / pi;
// const float rad = pi / 180.0f;

// A simple 2D vector class.
// This class is meant to be used as a replacement for sf::Vector2f.
// Includes the following operators and functions for working with vectors:
// - << (for printing vector information)
// - vector addition (+)
// - vector subtraction (-)
// - vector division (/)
// - scalar division (/)
// - scalar multiplication (*)
// - dot product (Vec2D.dot(Vec2D))
// - magnitude (Vec2D.magnitude())
// - angle (Vec2D.angle())
// - normal (Vec2D.normal())
// - normalize (Vec2D.normalize())
// - rotate (Vec2D.rotate())
// - distance (Vec2D.distance())
// - distanceSquared (Vec2D.distanceSquared())
// - distanceTo (Vec2D.distanceTo(Vec2D))
// - lerp (Vec2D.lerp(Vec2D, float))
// - rotateAround (Vec2D.rotateAround(Vec2D, float))
// - angleBetween (Vec2D.angleBetween(Vec2D))
class Vec2D : public sf::Vector2f {
public:
    // Default constructor (0, 0).
    Vec2D() : sf::Vector2f(0, 0) {}
    // Constructor with defined x and y floats.
    Vec2D(float x, float y) : sf::Vector2f(x, y) {}
    // Copy constructor (copy a sf::Vector2f object).
    Vec2D(const sf::Vector2f& vec) : sf::Vector2f(vec) {}
    // Copy constructor (copy a Vec2D object).
    Vec2D(const Vec2D& vec) : sf::Vector2f(vec) {}

    // Assignment operator (set one Vec2D equal to another).
    Vec2D& operator=(const Vec2D& vec) { x = vec.x; y = vec.y; return *this; }
    // Addition operator (new Vec2D = Vec2D + Vec2D).
    Vec2D operator+(const Vec2D& vec) const { return Vec2D(x + vec.x, y + vec.y); }
    // Subtraction operator (new Vec2D = Vec2D - Vec2D).
    Vec2D operator-(const Vec2D& vec) const { return Vec2D(x - vec.x, y - vec.y); }
    // Division operator (new Vec2D = Vec2D / Vec2D).
    Vec2D operator/(const Vec2D& vec) const { return Vec2D(x / vec.x, y / vec.y); }
    // Scalar multiplication operator (new Vec2D = Vec2D * float).
    Vec2D operator*(float scalar) const { return Vec2D(x * scalar, y * scalar); }
    // Vector multiplication operator (new Vec2D = Vec2D * Vec2D).
    Vec2D operator*(const Vec2D& vec) const { return Vec2D(x * vec.x, y * vec.y); }
    // Scalar division operator (new Vec2D = Vec2D / float).
    Vec2D operator/(float scalar) const { return Vec2D(x / scalar, y / scalar); }

    // Returns the dot product of two Vec2D objects.
    // @param vec: The other Vec2D object.
    float dot(const Vec2D& vec) const { return x * vec.x + y * vec.y; }              // dot product (float = Vec2D.dot(Vec2D))

    // Returns the magnitude of a Vec2D object.
    float magnitude() const { return sqrt(x * x + y * y); }                         // this magnitude (float = Vec2D.magnitude())

    // Returns the angle a Vec2D object makes with the +x-axis, in radians.
    float angle() const { return atan2(y, x); }                                     // this angle (float = Vec2D.angle())

    // Returns the normalized (unit) vector of a Vec2D object.
    Vec2D normalize() const { return *this / magnitude(); }                          // this normalized (Vec2D = Vec2D.normalize())

    // Returns a normal vector of a Vec2D object.
    // i.e. the vector 90deg CCW from it.
    Vec2D normal() const { return Vec2D(-y, x); }                                     // this normal (Vec2D = Vec2D.normal())

    // Returns tangent of a Vec2D object.
    Vec2D tangent() const { return Vec2D(y, -x); }                                    // this tangent (Vec2D = Vec2D.tangent())

    // Returns a new Vec2D object rotated by a given angle, in radians.
    // @param angle: The angle to rotate by, in radians.
    Vec2D rotate(float angle) const { return Vec2D(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle)); }   // rotate (Vec2D = Vec2D.rotate(float))

    // Returns the distance between two Vec2D objects.
    // @param vec: The other Vec2D object, with which to get distance to.
    float distanceTo(const Vec2D& vec) const { return sqrt(pow(x - vec.x, 2) + pow(y - vec.y, 2)); }                     // distance (float = Vec2D.distanceTo(Vec2D))
    
    // Returns the squared distance between two Vec2D objects.
    // @param vec: The other Vec2D object, with which to get distance to.
    float distanceSquared(const Vec2D& vec) const { return pow(x - vec.x, 2) + pow(y - vec.y, 2); }                      // distance squared (float = Vec2D.distanceSquared(Vec2D))
    
    // Returns a new Vec2D object that is lerped between this vector and another at t, where 0 <= t <= 1
    // @param vec: The other Vec2D object, with which to lerp to.
    // @param t: The amount to lerp by, between 0 and 1.
    Vec2D lerp(const Vec2D& vec, float t) const { return *this * (1 - t) + vec * t; }                                     // lerp (Vec2D = Vec2D.lerp(Vec2D, float))

    // Returns a new Vec2D object that is the result of rotating this vector around anoter vector by angle
    // @param vec: The other Vec2D object, with which to rotate around.
    // @param angle: The angle to rotate by, in radians.
    Vec2D rotateAround(const Vec2D& vec, float angle) const { return rotate(angle) + vec - *this; }                       // rotate around (Vec2D = Vec2D.rotateAround(Vec2D, float))
    
    // Returns the angle between two Vec2D objects.
    // @param vec: The other Vec2D object, with which to get the angle to.
    float angleBetween(const Vec2D& vec) const { return acos(dot(vec) / (magnitude() * vec.magnitude())); }              // angle between (float = Vec2D.angleBetween(Vec2D))

private:
    // Overloaded << operator, to print vector information
    friend std::ostream& operator<<(std::ostream& os, const Vec2D& vec) {
        os << "(" << vec.x << ", " << vec.y << ")";
        // os << "(" << vec.x << ", " << vec.y << "),  mag: " << vec.magnitude() << ", theta: " << vec.angle() << " (" << 57.29578*(vec.angle()) << " deg)";
        return os;
    }
};