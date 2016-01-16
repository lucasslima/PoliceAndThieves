#ifndef DRAWUTILS_H
#define DRAWUTILS_H
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

class Point {
public:
  Point(GLdouble *point = nullptr) {
    if (point == nullptr) {
      coordinates = nullptr;
    } else
      coordinates = new GLdouble[2];
  }

  Point(double x, double y) {
    coordinates = new GLdouble[2];
    coordinates[0] = x;
    coordinates[1] = y;
  }
  Point(const Point& p) {
    coordinates = new GLdouble[2];
    coordinates[0] = p.coordinates[0];
    coordinates[1] = p.coordinates[1];
  }

  GLdouble getX() const{
    if (coordinates == nullptr)
      throw new UninitializedPointException;
    return coordinates[0];
  }

  GLdouble getY() const {
    if (coordinates == nullptr)
      throw new UninitializedPointException;
    return coordinates[1];
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
  GLdouble *getCoordinates() {
    if (coordinates == nullptr)
      throw new UninitializedPointException;
    return coordinates;
  }
   Point& operator=(const Point &rhs){
       if ( this == &rhs)
           return *this;
       if (this->coordinates == nullptr)
           coordinates = new GLdouble[2];
       coordinates[0] = rhs.coordinates[0];
       coordinates[1] = rhs.coordinates[1];
       return *this;
  }

   ~Point(){
       delete coordinates;
   }

private:
  GLdouble *coordinates;
};

void drawPoligon(std::vector<Point> &points);
}
#endif // DRAWUTILS_H
