#ifndef DRAWUTILS_H
#define DRAWUTILS_H
#include <windows.h>
#include <GL/gl.h>
#include <vector>
#include <exception>

namespace DrawUtils {
    using std::vector;

// Exception Class for acessing unintialized points.
    struct UninitializedPointException : public std::exception {
        const char *what() const noexcept {
            return "Point coordinates not initialized.";
        }
    };



    struct pairhash {
    public:
        template<typename T, typename U>
        std::size_t operator()(const std::pair<T, U> &x) const {
            return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
        }
    };


    class Point {
    public:
        Point(GLdouble *point = nullptr) {
            if (point == nullptr) {
                coordinates = nullptr;
            } else
                coordinates = new GLdouble[2];
        }

        Point(double x, double y, double z) {
            coordinates = new GLdouble[2];
            coordinates[0] = x;
            coordinates[1] = y;
            coordinates[2] = z;
        }

        Point(const Point &p) {
            coordinates = new GLdouble[2];
            coordinates[0] = p.coordinates[0];
            coordinates[1] = p.coordinates[1];
            coordinates[2] = p.coordinates[2];
        }

        GLdouble getX() const {
            if (coordinates == nullptr)
                throw new UninitializedPointException;
            return coordinates[0];
        }

        GLdouble getY() const {
            if (coordinates == nullptr)
                throw new UninitializedPointException;
            return coordinates[1];
        }

        GLdouble getZ() const {
            if (coordinates == nullptr)
                throw new UninitializedPointException;
            return coordinates[2];
        }

        void setX(GLdouble x) {
            if (coordinates == nullptr)
                throw new UninitializedPointException;
            coordinates[0] = x;
        }

        void setY(GLdouble y) {
            if (coordinates == nullptr)
                throw new UninitializedPointException;
            coordinates[1] = y;
        }

        void setZ(GLdouble z) {
            if (coordinates == nullptr)
                throw new UninitializedPointException;
        }

        GLdouble *getCoordinates() {
            if (coordinates == nullptr)
                throw new UninitializedPointException;
            return coordinates;
        }

        Point &operator=(const Point &rhs) {
            if (this == &rhs)
                return *this;
            if (this->coordinates == nullptr)
                coordinates = new GLdouble[2];
            coordinates[0] = rhs.coordinates[0];
            coordinates[1] = rhs.coordinates[1];
            coordinates[2] = rhs.coordinates[2];
            return *this;
        }

        ~Point() {
           // delete coordinates;
        }

    private:
        GLdouble *coordinates;
    };

    void drawPoligon(std::vector<Point> &points);

    void drawCube(float size, const Point &point);
}
#endif // DRAWUTILS_H
