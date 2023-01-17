#include "pyramid.h"

_pyramid::_pyramid(float Size, float Height)
{
    Vertices.resize(5);

    Vertices[0]=_vertex3f(-Size/2,0,Size/2);
    Vertices[1]=_vertex3f(Size/2,0,Size/2);
    Vertices[2]=_vertex3f(Size/2,0,-Size/2);
    Vertices[3]=_vertex3f(-Size/2,0,-Size/2);
    Vertices[4]=_vertex3f(0,Height/2,0);

    Triangles.resize(6);

    Triangles[0]=_vertex3ui(0,1,4);
    Triangles[1]=_vertex3ui(1,2,4);
    Triangles[2]=_vertex3ui(2,3,4);
    Triangles[3]=_vertex3ui(3,0,4);
    Triangles[4]=_vertex3ui(3,1,0);
    Triangles[5]=_vertex3ui(3,2,1);
}
