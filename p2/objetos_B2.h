//**************************************************************************
// Práctica 2
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>

const float AXIS_SIZE = 5000;
typedef enum
{
	POINTS,
	EDGES,
	SOLID,
	SOLID_COLORS
} _modo;
namespace _colors_ne
{

	const _vertex3f RED(1, 0, 0);
	const _vertex3f GREEN(0, 1, 0);
	const _vertex3f BLUE(0, 0, 1);
	const _vertex3f CYAN(0, 1, 1);
	const _vertex3f MAGENTA(1, 0, 1);
	const _vertex3f YEllOW(1, 1, 0);
	const _vertex3f BLACK(0, 0, 0);
	const _vertex3f WHITE(1, 1, 1);

	const _vertex3f colores[] = {RED, GREEN, BLUE, CYAN, MAGENTA, YEllOW, BLACK, WHITE};
}

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:
	_puntos3D();
	void draw_puntos(float r, float g, float b, int grosor);

	vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D : public _puntos3D
{
public:
	_triangulos3D();
	void draw_aristas(float r, float g, float b, int grosor);
	void draw_solido(float r, float g, float b);
	void draw_solido_colores();
	void draw(_modo modo, float r, float g, float b, float grosor);

	vector<_vertex3i> caras;
};

//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo : public _triangulos3D
{
public:
	_cubo(float tam = 1);
};

//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide : public _triangulos3D
{
public:
	_piramide(float tam = 0.5, float al = 1.0);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply : public _triangulos3D
{
public:
	_objeto_ply();
	void create(const char *ply);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion : public _triangulos3D
{
public:
	_rotacion();

	void parametros(vector<_vertex3f> p, int n, int t);

	vector<_vertex3f> perfil;
	int num;
};

//*************************************************************************
// clase cilindro
//*************************************************************************
//!!!
class _cilindro : public _rotacion
{
public:
	_cilindro(float r, float h, int n);
};
//¡¡¡

//*************************************************************************
// clase cono
//*************************************************************************
//!!!
class _cono : public _rotacion
{
public:
	_cono(float r, float h, int n);
};
//¡¡¡

//*************************************************************************
// clase esfera
//*************************************************************************
//!!!
class _esfera : public _rotacion
{
public:
	_esfera(float r, int n); // altitud y latitud, las dos cosas porque uno representa el numero de perfiles que se van a generar y el otro el numero de puntos desde la tapa de abajo a la de arriba
};
//¡¡¡

//************************************************************************
// objeto por extrusión
//************************************************************************

class _extrusion : public _triangulos3D
{
public:
	_extrusion(vector<_vertex3f> poligono, float x, float y, float z);
};

//************************************************************************
// objeto ply
//************************************************************************

class _rotacion_ply : public _rotacion
{
private:
	_objeto_ply ply;
public:
	_rotacion_ply(char *filename, int n);
};
