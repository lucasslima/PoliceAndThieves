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

  GLdouble getX() {
    if (coordinates == nullptr)
      throw new UninitializedPointException;
    return coordinates[0];
  }

  GLdouble getY() {
    if (coordinates == nullptr)
      throw new UninitializedPointException;
    return coordinates[1];
  }

  GLdouble *getCoordinates() {
    if (coordinates == nullptr)
      throw new UninitializedPointException;
    return coordinates;
  }

private:
  GLdouble *coordinates;
};

void drawPoligon(vector<Point> &points) {
  glBegin(GL_POLYGON);
  for (Point p : points)
    glVertex2dv(p.getCoordinates());
  glEnd();
}
}
#endif // DRAWUTILS_H
