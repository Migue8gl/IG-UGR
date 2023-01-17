//**************************************************************************
// Práctica 3
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
	void colors_chess(float r1, float g1, float b1, float r2, float g2, float b2);

	vector<_vertex3i> caras;
	vector<_vertex3f> colores_caras;
};

//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo : public _triangulos3D
{
public:
	_cubo(float tam = 0.5);
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
	void create(const string ply);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion : public _triangulos3D
{
public:
	_rotacion();

	void parametros(vector<_vertex3f> perfil, int num, int tipo, int tapa_in, int tapa_su);

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
	_cilindro(float r = 1.0, float h = 2.0, int n = 40);
};
//¡¡¡

//*************************************************************************
// clase cono
//*************************************************************************
//!!!
class _cono : public _rotacion
{
public:
	_cono(float r = 1.0, float h = 2.0, int n = 40);
};
//¡¡¡

//*************************************************************************
// clase esfera
//*************************************************************************
//!!!
class _esfera : public _rotacion
{
public:
	_esfera(float radio, int num1, int num2);
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
	_rotacion_ply(const string filename, int n);
};

//************************************************************************
// pala
//************************************************************************

class _pala : public _triangulos3D
{
public:
	_pala(float radio = 1.0, float ancho = 2.0, int num = 8);
};

//************************************************************************
// brazo
//************************************************************************

class _brazo : public _triangulos3D
{
public:
	_brazo();
	void draw(_modo modo, float r, float g, float b, float grosor);

	float ancho;
	float alto;
	float fondo;

protected:
	_cubo cubo;
};

//************************************************************************
// cabina
//************************************************************************

class _cabina : public _triangulos3D
{
public:
	_cabina();
	void draw(_modo modo, float r, float g, float b, float grosor);

	float ancho;
	float alto;
	float fondo;

protected:
	_cubo cubo;
};

//************************************************************************
// sustentación
//************************************************************************

class _sustentacion : public _triangulos3D
{
public:
	_sustentacion();
	void draw(_modo modo, float r, float g, float b, float grosor);

	float ancho;
	float alto;
	float fondo;

	float radio;

protected:
	_cilindro rueda;
	_cubo base;
};

//************************************************************************
// excavadora (montaje del objeto final)
//************************************************************************

class _excavadora : public _triangulos3D
{
public:
	_excavadora();

	void draw(_modo modo, float r, float g, float b, float grosor);

	float giro_cabina;
	float giro_primer_brazo;
	float giro_segundo_brazo;
	float giro_pala;

	float giro_primer_brazo_max;
	float giro_primer_brazo_min;
	float giro_segundo_brazo_max;
	float giro_segundo_brazo_min;
	float giro_pala_max;
	float giro_pala_min;

	float tamanio_pala;

protected:
	_pala pala;
	_brazo brazo;
	_cabina cabina;
	_sustentacion sustentacion;
};

//////////////////////////////////////////////////////////////
///////////////////////// HELICOPTERO ////////////////////////

// RUEDA
class _wheel
{
public:
	_wheel();
	void draw(_modo modo, float r, float g, float b, float grosor);

protected:
	_cilindro cylinder;
};

// METRALLETA
class _machinegun
{
public:
	_machinegun();
	void draw(_modo modo, float r, float g, float b, float grosor);

protected:
	_cilindro cylinder;
};

// BALAS
class _bullet
{
public:
	_bullet();
	void draw(_modo modo, float r, float g, float b, float grosor);

protected:
	_cilindro cylinder;
};

// HOJA
class _blade
{
public:
	_blade();
	void draw(_modo modo, float r, float g, float b, float grosor);

protected:
	_cubo cube;
};

// PUERTA
class _door
{
public:
	_door();
	void draw(_modo modo, float r, float g, float b, float grosor);

protected:
	_cubo cube;
	_wheel wheel;
};

// HELICE
class _propeller
{
public:
	_propeller();
	void draw(_modo modo, float r, float g, float b, float grosor);

protected:
	_blade blade;
	_wheel wheel;
	_cilindro cylinder;
};

// PATINES
class _skids
{
public:
	_skids();
	void draw(_modo modo, float r, float g, float b, float grosor);

protected:
	_wheel wheel;
	_cilindro cylinder;
};

// COLA
class _tail
{
public:
	float little_helice_rotation = 0;

	_tail();
	void draw(_modo modo, float r, float g, float b, float grosor);

protected:
	_cubo cube;
	_cilindro cylinder;
	_propeller propeller;
	_cono cone;
};

// HELICOPTERO
class _helicopter
{
public:
	float helice_rotation = 0;
	;
	float little_helice_rotation = 0;
	float door_rotation = -30;
	float door_translation = 0;
	float machinegun_translation_z = 0.2;
	float machinegun_translation_y = -0.25;
	float machinegun_rotation = 0;
	float bullet_translation = 0;
	float factor = 30;
	bool machinegun_inside = false;
	bool door_inside = false;

	_helicopter();
	void draw(_modo modo, float r, float g, float b, float grosor);

protected:
	_cubo cube;
	_esfera sphere;
	_tail tail;
	_skids skids;
	_door door;
	_cilindro cylinder;
	_propeller propeller;
	_cono cone;
	_machinegun gun;
	_bullet bullet;
};