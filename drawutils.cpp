#include "drawutils.h"

namespace DrawUtils {

    void drawPoligon(std::vector<Point> &points) {
        glBegin(GL_POLYGON);
        for (Point p : points)
            glVertex2d(p.getX(), p.getY());
        glEnd();
    }

    void drawCube(float size, const Point &point) {
        glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
            // Top face (y = 1.0f)
            // Define vertices in counter-clockwise (CCW) order with normal pointing out

            glVertex3d(point.getX() + size , point.getY() + size, point.getZ());
            glVertex3d(point.getX()        , point.getY() + size, point.getZ());
            glVertex3d(point.getX()        , point.getY() + size, point.getZ() + size);
            glVertex3d(point.getX() + size , point.getY() + size, point.getZ() + size);

            // Bottom face (y = -1.0f)

            glVertex3d(point.getX() + size , point.getY() , point.getZ() + size);
            glVertex3d(point.getX()        , point.getY() , point.getZ() + size);
            glVertex3d(point.getX()        , point.getY() , point.getZ() );
            glVertex3d(point.getX() + size , point.getY() , point.getZ());

            // Front face  (z = 1.0f)

            glVertex3d(point.getX() + size , point.getY() + size, point.getZ() + size);
            glVertex3d(point.getX()        , point.getY() + size, point.getZ() + size);
            glVertex3d(point.getX()        , point.getY()       , point.getZ() + size);
            glVertex3d(point.getX() + size , point.getY()       , point.getZ() + size);

            // Back face (z = -1.0f)

            glVertex3d(point.getX() + size , point.getY()        , point.getZ());
            glVertex3d(point.getX()        , point.getY()        , point.getZ());
            glVertex3d(point.getX()        , point.getY() + size , point.getZ());
            glVertex3d(point.getX() + size , point.getY() + size , point.getZ());

            // Left face (x = -1.0f)
            glVertex3d(point.getX(), point.getY() + size, point.getZ() + size);
            glVertex3d(point.getX(), point.getY() + size, point.getZ());
            glVertex3d(point.getX(), point.getY()       , point.getZ());
            glVertex3d(point.getX(), point.getY()       , point.getZ() + size);

            // Right face (x = 1.0f)
            glVertex3d(point.getX() + size, point.getY() + size, point.getZ());
            glVertex3d(point.getX() + size, point.getY() + size, point.getZ() + size);
            glVertex3d(point.getX() + size, point.getY()       , point.getZ() + size);
            glVertex3d(point.getX() + size, point.getY()       , point.getZ());
        glEnd();  // End of drawing color-cube
    }
}
