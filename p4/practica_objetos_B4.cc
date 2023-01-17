//**************************************************************************
// Práctica 4
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B4.h"

using namespace std;

// The time in milliseconds between timer ticks
#define TIMERMSECS 50

// tipos
typedef enum
{
	CUBO,
	PIRAMIDE,
	OBJETO_PLY,
	ROTACION,
	EXTRUSION,
	CILINDRO,
	CONO,
	ESFERA,
	ROTACION_PLY,
	HELICOPTERO,
	EXCAVADORA,
	TEXTURA
} _tipo_objeto;

_tipo_objeto t_objeto = CUBO;
_modo modo = POINTS;
bool mov = false;
bool turno = true, turno2 = true;
bool luz1 = false;
float alpha = 0.0;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x, Size_y, Front_plane, Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x = 50, Window_y = 50, Window_width = 800, Window_high = 800;

// objetos
_cubo cubo;
_piramide piramide(0.85, 1.3);
_objeto_ply ply;
_rotacion rotacion;
_extrusion *extrusion;
_cilindro cilindro(1, 2, 40);
_cono cono(1, 2, 40);
_esfera esfera(1, 40, 40);
_rotacion_ply ply_rotacion("copa.ply", 40);
_excavadora excavadora;
_helicopter helicoptero;
_textura textura;
GLuint text_id;

//**************************************************************************
//
//***************************************************************************

void clean_window()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
	//  plano_delantero>0  plano_trasero>PlanoDelantero)
	glFrustum(-Size_x, Size_x, -Size_y, Size_y, Front_plane, Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

	// posicion del observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -Observer_distance);
	glRotatef(Observer_angle_x, 1, 0, 0);
	glRotatef(Observer_angle_y, 0, 1, 0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{

	glDisable(GL_LIGHTING);
	glLineWidth(2);
	glBegin(GL_LINES);
	// eje X, color rojo
	glColor3f(1, 0, 0);
	glVertex3f(-AXIS_SIZE, 0, 0);
	glVertex3f(AXIS_SIZE, 0, 0);
	// eje Y, color verde
	glColor3f(0, 1, 0);
	glVertex3f(0, -AXIS_SIZE, 0);
	glVertex3f(0, AXIS_SIZE, 0);
	// eje Z, color azul
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, -AXIS_SIZE);
	glVertex3f(0, 0, AXIS_SIZE);
	glEnd();
	glColor3f(1,1,1);
}

//**************************************************************************
// Funcion que dibuja los objetos
//**************************************************************************

void draw_objects()
{

	switch (t_objeto)
	{
	case CUBO:
		cubo.draw(modo, 1.0, 0.0, 0.0, 3);
		break;
	case PIRAMIDE:
		piramide.draw(modo, 1.0, 0.0, 0.0, 3);
		break;
	case OBJETO_PLY:
		ply.draw(modo, 1.0, 0.6, 0.0, 3);
		break;
	case ROTACION:
		rotacion.draw(modo, 1.0, 0.0, 0.0, 3);
		break;
	case EXTRUSION:
		extrusion->draw(modo, 1.0, 0.0, 0.0, 3);
		break;
	case CILINDRO:
		cilindro.draw(modo, 1.0, 0.0, 0.0, 3);
		break;
	case CONO:
		cono.draw(modo, 1.0, 0.0, 0.0, 3);
		break;
	case ESFERA:
		esfera.draw(modo, 1.0, 0.0, 0.0, 3);
		break;
	case ROTACION_PLY:
		ply_rotacion.draw(modo, 1.0, 0.6, 0.0, 3);
		break;
	case EXCAVADORA:
		excavadora.draw(modo, 1.0, 0.0, 0.0, 3);
		break;
	case HELICOPTERO:
		helicoptero.draw(modo, 1.0, 0.0, 0.0, 3);
		break;
	case TEXTURA:
		textura.dibuja();
		break;
	}
}

void luces()
{
	GLfloat luz_ambiente[] = {1, 1, 1, 1.0},
			luz_difusa[] = {1, 1, 1, 1.0},
			luz_especular[] = {1.0, 1.0, 1.0, 1.0},
			luz_posicion[] = {2.0, 2.0, 0.0, 1.0};

	glLightfv(GL_LIGHT1, GL_AMBIENT, luz_ambiente);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luz_difusa);
	glLightfv(GL_LIGHT1, GL_SPECULAR, luz_especular);
	glLightfv(GL_LIGHT1, GL_POSITION, luz_posicion);

	glDisable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	if (luz1)
	{
		GLfloat luz_ambiente2[] = {0.1, 0.0, 0.0, 1.0},
				luz_difusa2[] = {0.1, 0.0, 0.0, 1.0},
				luz_especular2[] = {1.0, 0.0, 1.0, 1.0},
				luz_posicion2[] = {0.0, -10.0, 10.0, 1.0};

		glLightfv(GL_LIGHT2, GL_AMBIENT, luz_ambiente2);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, luz_difusa2);
		glLightfv(GL_LIGHT2, GL_SPECULAR, luz_especular2);
		glPushMatrix();
		glRotatef(alpha, 0, 1, 0);
		glLightfv(GL_LIGHT2, GL_POSITION, luz_posicion2);
		glPopMatrix();
		glEnable(GL_LIGHT2);
	}
	else
		glDisable(GL_LIGHT2);
}

//**************************************************************************
//
//***************************************************************************

void draw(void)
{
	clean_window();
	change_observer();
	luces();
	draw_axis();
	draw_objects();
	glutSwapBuffers();
}

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1, int Alto1)
{
	float Aspect_ratio;

	Aspect_ratio = (float)Alto1 / (float)Ancho1;
	Size_y = Size_x * Aspect_ratio;
	change_projection();
	glViewport(0, 0, Ancho1, Alto1);
	glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1, int x, int y)
{
	switch (toupper(Tecla1))
	{
	case 'Q':
		exit(0);
	case '1':
		modo = POINTS;
		break;
	case '2':
		modo = EDGES;
		break;
	case '3':
		modo = SOLID;
		break;
	case '4':
		modo = SOLID_COLORS;
		break;
	case '5':
		modo = SOLID_FLAT;
		break;
	case '6':
		modo = SOLID_SMOOTH;
		break;
	case 'U':
		t_objeto = PIRAMIDE;
		break;
	case 'C':
		t_objeto = CUBO;
		break;
	case 'B':
		t_objeto = OBJETO_PLY;
		break;
	case 'R':
		t_objeto = ROTACION;
		break;
	case 'X':
		t_objeto = EXTRUSION;
		break;
	case 'L':
		t_objeto = CILINDRO;
		break;
	case 'N':
		t_objeto = CONO;
		break;
	case 'E':
		t_objeto = ESFERA;
		break;
	case 'W':
		t_objeto = ROTACION_PLY;
		break;
	case 'Z':
		t_objeto = EXCAVADORA;
		break;
	case 'A':
		t_objeto = HELICOPTERO;
		break;
	case 'S':
		mov = !mov;
		break;
	case 'I':
		luz1 = !luz1;
		break;
	case 'O':
		alpha += 2;
		break;
	case 'P':
		alpha -= 2;
		break;
	case 'T':
		t_objeto = TEXTURA;
		break;
	}
	glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1, int x, int y)
{
	switch (Tecla1)
	{
	case GLUT_KEY_LEFT:
		Observer_angle_y -= 3;
		break;
	case GLUT_KEY_RIGHT:
		Observer_angle_y += 3;
		break;
	case GLUT_KEY_UP:
		Observer_angle_x -= 3;
		break;
	case GLUT_KEY_DOWN:
		Observer_angle_x += 3;
		break;
	case GLUT_KEY_PAGE_UP:
		Observer_distance *= 1.2;
		break;
	case GLUT_KEY_PAGE_DOWN:
		Observer_distance /= 1.2;
		break;
	case GLUT_KEY_F1:
		helicoptero.helice_rotation += 10 * helicoptero.factor;
		break;
	case GLUT_KEY_F2:
		helicoptero.little_helice_rotation += 10 * helicoptero.factor;
		break;
	case GLUT_KEY_F3:
		if (helicoptero.door_rotation < 60)
			helicoptero.door_rotation += 10;
		if (helicoptero.door_translation < 0.2)
			helicoptero.door_translation += 0.04;
		break;
	case GLUT_KEY_F4:
		if (helicoptero.door_rotation > -30)
			helicoptero.door_rotation -= 10;
		if (helicoptero.door_translation > -0.15)
			helicoptero.door_translation -= 0.05;
		break;
	case GLUT_KEY_F5:
		if (helicoptero.machinegun_translation_z < 1)
			helicoptero.machinegun_translation_z += 0.02;
		if (helicoptero.machinegun_translation_y > -0.5)
			helicoptero.machinegun_translation_y -= 0.02;
		helicoptero.machinegun_rotation += 40;
		helicoptero.bullet_translation += 0.5;
		if (helicoptero.bullet_translation > 2)
			helicoptero.bullet_translation = 0;
		break;
	case GLUT_KEY_F6:
		helicoptero.bullet_translation = 0;
		if (helicoptero.machinegun_translation_z > 0.2)
			helicoptero.machinegun_translation_z -= 0.02;
		if (helicoptero.machinegun_translation_y < -0.25)
			helicoptero.machinegun_translation_y += 0.02;
		helicoptero.machinegun_rotation += 40;
		break;
	}
	glutPostRedisplay();
}

//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
	// se inicalizan la ventana y los planos de corte
	Size_x = 0.5;
	Size_y = 0.5;
	Front_plane = 1;
	Back_plane = 1000;

	// se incia la posicion del observador, en el eje z
	Observer_distance = 5 * Front_plane;
	Observer_angle_x = 0;
	Observer_angle_y = 0;

	// se indica el color para limpiar la ventana	(r,v,a,al)
	// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
	// glClearColor(1, 1, 1, 1);
	glClearColor(1, 1, 1, 1);

	// se habilita el z-bufer
	glEnable(GL_DEPTH_TEST);
	change_projection();
	glViewport(0, 0, Window_width, Window_high);
}

void animacion(int value)
{
	glutTimerFunc(TIMERMSECS, animacion, 0);
	if (mov)
	{
		helicoptero.helice_rotation += 10 * helicoptero.factor;
		helicoptero.little_helice_rotation += 10 * helicoptero.factor;

		if (!helicoptero.machinegun_inside)
		{
			if (helicoptero.machinegun_translation_z < 1)
				helicoptero.machinegun_translation_z += 0.02;
			if (helicoptero.machinegun_translation_y > -0.5)
				helicoptero.machinegun_translation_y -= 0.02;
			helicoptero.machinegun_rotation += 40;
			helicoptero.bullet_translation += 0.5;
			if (helicoptero.bullet_translation > 2)
				helicoptero.bullet_translation = 0;
		}
		else
		{
			helicoptero.bullet_translation = 0;
			if (helicoptero.machinegun_translation_z > 0.2)
				helicoptero.machinegun_translation_z -= 0.02;
			if (helicoptero.machinegun_translation_y < -0.25)
				helicoptero.machinegun_translation_y += 0.02;
			helicoptero.machinegun_rotation += 40;
		}

		if (!helicoptero.door_inside)
		{
			if (helicoptero.door_rotation < 60)
				helicoptero.door_rotation += 10;
			if (helicoptero.door_translation < 0.2)
				helicoptero.door_translation += 0.04;
		}
		else
		{
			if (helicoptero.door_rotation > -30)
				helicoptero.door_rotation -= 10;
			if (helicoptero.door_translation > -0.15)
				helicoptero.door_translation -= 0.05;
		}

		if (turno)
		{
			helicoptero.machinegun_inside = false;
			if (helicoptero.machinegun_translation_z > 1)
				turno = false;
		}
		else
		{
			helicoptero.machinegun_inside = true;
			if (helicoptero.machinegun_translation_z < 0.2)
				turno = true;
		}

		if (turno2)
		{
			helicoptero.door_inside = false;
			if (helicoptero.door_rotation >= 60)
				turno2 = false;
		}
		else
		{
			helicoptero.door_inside = true;
			if (helicoptero.door_rotation <= -30)
				turno2 = true;
		}

		glutPostRedisplay();
	}
}

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char *argv[])
{
	vector<_vertex3f> perfil, poligono;
	_vertex3f aux;

	aux.x = 1.0;
	aux.y = -1.0;
	aux.z = 0.0;
	perfil.push_back(aux);
	aux.x = 1.0;
	aux.y = 1.0;
	aux.z = 0.0;
	perfil.push_back(aux);

	rotacion.parametros(perfil, 6, 0, 1, 1);

	aux.x = 1.0;
	aux.y = 0.0;
	aux.z = 1.0;
	poligono.push_back(aux);
	aux.x = 1.0;
	aux.y = 0.0;
	aux.z = -1.0;
	poligono.push_back(aux);
	aux.x = -1.2;
	aux.y = 0.0;
	aux.z = -1.0;
	poligono.push_back(aux);
	aux.x = -0.8;
	aux.y = 0.0;
	aux.z = 0.0;
	poligono.push_back(aux);
	aux.x = -1.2;
	aux.y = 0.0;
	aux.z = 1.0;
	poligono.push_back(aux);

	extrusion = new _extrusion(poligono, 0.25, 1.0, 0.25);

	// se llama a la inicialización de glut
	glutInit(&argc, argv);

	// se indica las caracteristicas que se desean para la visualización con OpenGL
	// Las posibilidades son:
	// GLUT_SIMPLE -> memoria de imagen simple
	// GLUT_DOUBLE -> memoria de imagen doble
	// GLUT_INDEX -> memoria de imagen con color indizado
	// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
	// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
	// GLUT_DEPTH -> memoria de profundidad o z-bufer
	// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// posicion de la esquina inferior izquierdad de la ventana
	glutInitWindowPosition(Window_x, Window_y);

	// tamaño de la ventana (ancho y alto)
	glutInitWindowSize(Window_width, Window_high);

	// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
	// al bucle de eventos)
	glutCreateWindow("PRACTICA - 4");

	// asignación de la funcion llamada "dibujar" al evento de dibujo
	glutDisplayFunc(draw);
	// asignación de la funcion llamada "change_window_size" al evento correspondiente
	glutReshapeFunc(change_window_size);
	// asignación de la funcion llamada "normal_key" al evento correspondiente
	glutKeyboardFunc(normal_key);
	// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
	glutSpecialFunc(special_key);

	// funcion de inicialización
	initialize();

	// creación del objeto ply
	ply.create(string(argv[1]));

	textura.prepara_textura("./skybox.jpg", &text_id);

	glutTimerFunc(TIMERMSECS, animacion, 0);

	// inicio del bucle de eventos
	glutMainLoop();

	textura.libera_textura(textura.textura_id);
	return 0;
}
