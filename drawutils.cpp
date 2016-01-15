#include "drawutils.h"

namespace DrawUtils{
void drawPoligon(std::vector<Point> &points) {
  glBegin(GL_POLYGON);
  for (Point p : points)
    glVertex2d(p.getX(), p.getY());
  glEnd();
}
}
