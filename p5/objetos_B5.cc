//**************************************************************************
// Práctica 5
//**************************************************************************

#include "objetos_B5.h"
#include "file_ply_stl.hpp"
#include "CImg.h"
using namespace cimg_library;
using namespace _colors_ne;

//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
  glPointSize(grosor);
  glColor3f(r, g, b);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
  glDrawArrays(GL_POINTS, 0, vertices.size());

  /*glPointSize(grosor);
  glColor3f(r, g, b);
  glBegin(GL_POINTS);
  for (unsigned int i = 0; i < vertices.size(); i++)
  {
    glVertex3fv((GLfloat *)&vertices[i]);
  }
  glEnd();*/
}

//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
  ambiente = {0.5f, 0.5f, 0.0f, 1.0f};
  difuso = {0.5f, 0.5f, 0.4f, 1.0f};
  especular = {0.7f, 0.7f, 0.04f, 1.0f};
  brillo = 10.0f;
}

//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glLineWidth(grosor);
  glColor3f(r, g, b);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
  glDrawElements(GL_TRIANGLES, caras.size() * 3, GL_UNSIGNED_INT, &caras[0]);

  /*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glLineWidth(grosor);
  glColor3f(r, g, b);
  glBegin(GL_TRIANGLES);
  for (unsigned int i = 0; i < caras.size(); i++)
  {
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();*/
}

//*************************************************************************
// dibujar en modo sólido con un único color
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(r, g, b);
  glBegin(GL_TRIANGLES);
  for (unsigned int i = 0; i < caras.size(); i++)
  {
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();
}

//*************************************************************************
// dibujar en modo sólido con colores diferentes para cada cara
//*************************************************************************

void _triangulos3D::draw_solido_colores()
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);
  for (unsigned int i = 0; i < caras.size(); i++)
  {
    glColor3fv((GLfloat *)&colores[i % 8]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();
}

//*************************************************************************
// dibujar modo ilumninación plana
//*************************************************************************

void _triangulos3D::draw_solido_plano()
{

  glEnable(GL_LIGHTING);
  glShadeModel(GL_FLAT);
  glEnable(GL_NORMALIZE);

  if (!objeto)
  {
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *)&difuso);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *)&ambiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *)&especular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);
  }

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);
  for (unsigned int i = 0; i < caras.size(); i++)
  {
    glNormal3f(normales_caras[i].r, normales_caras[i].g, normales_caras[i].b);
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();
  glDisable(GL_LIGHTING);
}

//*************************************************************************
// dibujar modo ilumninación smooth
//*************************************************************************

void _triangulos3D::draw_solido_suave()
{
  glEnable(GL_LIGHTING);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_NORMALIZE);

  if (!objeto)
  {
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *)&difuso);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *)&ambiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *)&especular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);
  }

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);
  for (unsigned int i = 0; i < caras.size(); i++)
  {
    glNormal3fv((GLfloat *)&normales_vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glNormal3fv((GLfloat *)&normales_vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glNormal3fv((GLfloat *)&normales_vertices[caras[i]._2]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();
  glDisable(GL_LIGHTING);
}

//*************************************************************************
// calcular normales
//*************************************************************************

void _triangulos3D::calcular_normales_caras()
{
  unsigned int n_c;
  n_c = caras.size();
  _vertex3f va, vb;
  float modulo;
  normales_caras.resize(n_c);

  for (unsigned int i = 0; i < n_c; i++)
  {
    va = vertices[caras[i]._1] - vertices[caras[i]._0];
    vb = vertices[caras[i]._2] - vertices[caras[i]._0];
    normales_caras[i].x = va.y * vb.z - va.z * vb.y;
    normales_caras[i].y = va.z * vb.x - va.x * vb.z;
    normales_caras[i].z = va.x * vb.y - va.y * vb.x;
    modulo = sqrt(normales_caras[i].x * normales_caras[i].x +
                  normales_caras[i].y * normales_caras[i].y +
                  normales_caras[i].z * normales_caras[i].z);
    normales_caras[i].x /= modulo;
    normales_caras[i].y /= modulo;
    normales_caras[i].z /= modulo;
  }
}

void _triangulos3D::calcular_normales_vertices()
{
  normales_vertices.resize(vertices.size());

  for (unsigned int i = 0; i < caras.size(); i++)
  {
    normales_vertices[caras[i]._0] += normales_caras[i];
    normales_vertices[caras[i]._1] += normales_caras[i];
    normales_vertices[caras[i]._2] += normales_caras[i];
  }

  for (unsigned int i = 0; i < normales_vertices.size(); i++)
    normales_vertices[i].normalize();
}

void _triangulos3D::colors_flat(float r, float g, float b, float p_lx, float p_ly, float p_lz)
{
  unsigned int n_c;
  _vertex3f l;
  float modulo, escalar;
  n_c = caras.size();
  colores_caras.resize(n_c);

  for (unsigned int i = 0; i < n_c; i++)
  {
    colores_caras[i].r = 0.1 * r;
    colores_caras[i].g = 0.1 * g;
    colores_caras[i].b = 0.101 * b;
    l.x = p_lx - vertices[caras[i]._0].x;
    l.y = p_ly - vertices[caras[i]._0].y;
    l.z = p_lz - vertices[caras[i]._0].z;
    modulo = sqrt(l.x * l.x + l.y * l.y + l.z * l.z);
    l.x /= modulo;
    l.y /= modulo;
    l.z /= modulo;
    escalar = normales_caras[i].x * l.x + normales_caras[i].y * l.y + normales_caras[i].z * l.z;
    if (escalar > 0.0)
    {
      colores_caras[i].r += r * escalar;
      colores_caras[i].g += g * escalar;
      colores_caras[i].b += b * escalar;
    }
  }
}

void _triangulos3D::colors_smooth(float r, float g, float b, float p_lx, float p_ly, float p_lz)
{
  int num_caras;
  _vertex3f l;
  float modulo, escalar;
  num_caras = caras.size();
  colores_caras.resize(num_caras);

  for (int i = 0; i < num_caras; i++)
  {
    colores_caras[i].r = 0.1 * r;
    colores_caras[i].g = 0.1 * g;
    colores_caras[i].b = 0.101 * b;
    l.x = p_lx - vertices[caras[i]._0].x;
    l.y = p_ly - vertices[caras[i]._0].y;
    l.z = p_lz - vertices[caras[i]._0].z;
    modulo = sqrt(l.x * l.x + l.y * l.y + l.z * l.z);
    l.x /= modulo;
    l.y /= modulo;
    l.z /= modulo;
    escalar = normales_vertices[caras[i]._0].x * l.x + normales_vertices[caras[i]._0].y * l.y + normales_vertices[caras[i]._0].z * l.z;

    if (escalar > 0.0)
    {
      colores_caras[i].r += r * escalar;
      colores_caras[i].g += g * escalar;
      colores_caras[i].b += b * escalar;
    }
  }
}

//*************************************************************************
// dibujar en modo seleccion
//*************************************************************************

void _triangulos3D::draw_seleccion(int r, int g, int b)
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3ub(r, g, b);
  glBegin(GL_TRIANGLES);
  for (unsigned i = 0; i < caras.size(); i++)
  {
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r, float g, float b, float grosor)
{
  switch (modo)
  {
  case POINTS:
    draw_puntos(r, g, b, grosor);
    break;
  case EDGES:
    draw_aristas(r, g, b, grosor);
    break;
  case SOLID:
    draw_solido(r, g, b);
    break;
  case SOLID_COLORS:
    draw_solido_colores();
    break;
  case SOLID_FLAT:
    draw_solido_plano();
    break;
  case SOLID_SMOOTH:
    draw_solido_suave();
    break;
  case SELECT:
    draw_seleccion(r, g, b);
    break;
  }
}

void _triangulos3D::colors_chess(float r1, float g1, float b1, float r2, float g2, float b2)
{
  int i, n_c;
  n_c = caras.size();
  colores_caras.resize(n_c);
  for (i = 0; i < n_c; i++)
  {
    if (i % 2 == 0)
    {
      colores_caras[i].r = r1;
      colores_caras[i].g = g1;
      colores_caras[i].b = b1;
    }
    else
    {
      colores_caras[i].r = r2;
      colores_caras[i].g = g2;
      colores_caras[i].b = b2;
    }
  }
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam) // da igual que no este centrado, o que una esquina comience en el eje de coordenadas
{
  // vertices
  vertices.resize(8);
  vertices[0].x = -tam;
  vertices[0].y = -tam;
  vertices[0].z = tam;
  vertices[1].x = tam;
  vertices[1].y = -tam;
  vertices[1].z = tam;
  vertices[2].x = tam;
  vertices[2].y = tam;
  vertices[2].z = tam;
  vertices[3].x = -tam;
  vertices[3].y = tam;
  vertices[3].z = tam;
  vertices[4].x = -tam;
  vertices[4].y = -tam;
  vertices[4].z = -tam;
  vertices[5].x = tam;
  vertices[5].y = -tam;
  vertices[5].z = -tam;
  vertices[6].x = tam;
  vertices[6].y = tam;
  vertices[6].z = -tam;
  vertices[7].x = -tam;
  vertices[7].y = tam;
  vertices[7].z = -tam;

  // triangulos
  caras.resize(12);
  caras[0]._0 = 0;
  caras[0]._1 = 1;
  caras[0]._2 = 3;
  caras[1]._0 = 3;
  caras[1]._1 = 1;
  caras[1]._2 = 2;
  caras[2]._0 = 1;
  caras[2]._1 = 5;
  caras[2]._2 = 2;
  caras[3]._0 = 5;
  caras[3]._1 = 6;
  caras[3]._2 = 2;
  caras[4]._0 = 5;
  caras[4]._1 = 4;
  caras[4]._2 = 6;
  caras[5]._0 = 4;
  caras[5]._1 = 7;
  caras[5]._2 = 6;
  caras[6]._0 = 0;
  caras[6]._1 = 7;
  caras[6]._2 = 4;
  caras[7]._0 = 0;
  caras[7]._1 = 3;
  caras[7]._2 = 7;
  caras[8]._0 = 3;
  caras[8]._1 = 2;
  caras[8]._2 = 7;
  caras[9]._0 = 2;
  caras[9]._1 = 6;
  caras[9]._2 = 7;
  caras[10]._0 = 0;
  caras[10]._1 = 1;
  caras[10]._2 = 4;
  caras[11]._0 = 1;
  caras[11]._1 = 5;
  caras[11]._2 = 4;

  calcular_normales_caras();
  calcular_normales_vertices();
}

//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{
  // vertices
  vertices.resize(5);
  vertices[0].x = -tam;
  vertices[0].y = 0;
  vertices[0].z = tam;
  vertices[1].x = tam;
  vertices[1].y = 0;
  vertices[1].z = tam;
  vertices[2].x = tam;
  vertices[2].y = 0;
  vertices[2].z = -tam;
  vertices[3].x = -tam;
  vertices[3].y = 0;
  vertices[3].z = -tam;
  vertices[4].x = 0;
  vertices[4].y = al;
  vertices[4].z = 0;

  caras.resize(6);
  caras[0]._0 = 0;
  caras[0]._1 = 1;
  caras[0]._2 = 4;
  caras[1]._0 = 1;
  caras[1]._1 = 2;
  caras[1]._2 = 4;
  caras[2]._0 = 2;
  caras[2]._1 = 3;
  caras[2]._2 = 4;
  caras[3]._0 = 3;
  caras[3]._1 = 0;
  caras[3]._2 = 4;
  caras[4]._0 = 3;
  caras[4]._1 = 1;
  caras[4]._2 = 0;
  caras[5]._0 = 3;
  caras[5]._1 = 2;
  caras[5]._2 = 1;

  calcular_normales_caras();
  calcular_normales_vertices();
}

//*************************************************************************
// clase objeto ply
//*************************************************************************

_objeto_ply::_objeto_ply()
{
  // leer lista de coordenadas de vértices y lista de indices de vértices
}

void _objeto_ply::create(const string ply)
{
  _file_ply File;
  vector<float> aux_vert;          // Contenedor auxiliar de vertices
  vector<unsigned int> aux_triang; // Contenedor auxiliar de triangulos

  if (File.open(ply))
  {
    File.read(aux_vert, aux_triang);

    unsigned int j = 0;

    /*Cada 3 elementos encontramos un vertice, igual ocurre
    con triangulos, por ello el tamaño necesitado es el de
    los contenedores auxiliares entre 3*/
    vertices.resize(aux_vert.size() / 3);
    caras.resize(aux_triang.size() / 3);

    // Traspasamos los vertices al contenedor original
    for (unsigned int i = 0; i < aux_vert.size(); i += 3)
    {
      vertices[j] = _vertex3f(aux_vert[i], aux_vert[i + 1], aux_vert[i + 2]);
      j++;
    }

    j = 0;

    // Traspasamos los triangulos al contenedor original
    for (unsigned int i = 0; i < aux_triang.size(); i += 3)
    {
      caras[j] = _vertex3i(aux_triang[i], aux_triang[i + 1], aux_triang[i + 2]);
      j++;
    }
  }

  calcular_normales_caras();
  calcular_normales_vertices();

  File.close();
}

//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{
}

void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tipo, int tapa_in, int tapa_su)
{
  int i, j;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int num_aux;
  float radio;

  // tratamiento de los vértice
  radio = sqrt(perfil[0].x * perfil[0].x + perfil[0].y * perfil[0].y);

  num_aux = perfil.size();
  if (tipo == 1)
    num_aux = num_aux - 1;
  vertices.resize(num_aux * num + 2);
  for (j = 0; j < num; j++)
  {
    for (i = 0; i < num_aux; i++)
    {
      vertice_aux.x = perfil[i].x * cos(2.0 * M_PI * j / (1.0 * num)) +
                      perfil[i].z * sin(2.0 * M_PI * j / (1.0 * num));
      vertice_aux.z = -perfil[i].x * sin(2.0 * M_PI * j / (1.0 * num)) +
                      perfil[i].z * cos(2.0 * M_PI * j / (1.0 * num));
      vertice_aux.y = perfil[i].y;
      vertices[i + j * num_aux] = vertice_aux;
    }
  }

  caras.resize(2 * (num_aux - 1) * num + 2 * num);
  int c = 0;
  for (j = 0; j < num; j++)
  {
    for (i = 0; i < num_aux - 1; i++)
    {
      caras[c]._0 = i + j * num_aux;
      caras[c]._1 = ((j + 1) % num) * num_aux + i;
      caras[c]._2 = 1 + i + j * num_aux;
      c += 1;
      caras[c]._0 = ((j + 1) % num) * num_aux + i;
      caras[c]._1 = ((j + 1) % num) * num_aux + 1 + i;
      caras[c]._2 = 1 + i + j * num_aux;
      c += 1;
    }
  }

  // tapa inferior
  int total = num_aux * num;
  vertices[total].x = 0.0;
  if (tipo == 2)
    vertices[total].y = -radio;
  else
    vertices[total].y = perfil[0].y;
  vertices[total].z = 0.0;

  for (j = 0; j < num; j++)
  {
    caras[c]._0 = j * num_aux;
    caras[c]._1 = ((j + 1) % num) * num_aux;
    caras[c]._2 = total;
    c += 1;
  }

  // tapa superior
  vertices[total + 1].x = 0.0;
  if (tipo == 1)
    vertices[total + 1].y = perfil[1].y;
  if (tipo == 0)
    vertices[total + 1].y = perfil[num_aux - 1].y;
  if (tipo == 2)
    vertices[total + 1].y = radio;
  vertices[total + 1].z = 0.0;

  for (j = 0; j < num; j++)
  {
    caras[c]._0 = total + 1;
    caras[c]._1 = ((j + 1) % num) * num_aux + num_aux - 1;
    caras[c]._2 = num_aux - 1 + j * num_aux;
    c += 1;
  }

  calcular_normales_caras();
  calcular_normales_vertices();
}

//************************************************************************
// cilindro
//************************************************************************

_cilindro::_cilindro(float r, float h, int n)
{
  _vertex3f aux;
  aux.x = r;
  aux.y = -h / 2.0;
  aux.z = 0.0;
  perfil.push_back(aux);
  aux.x = r;
  aux.y = h / 2.0;
  aux.z = 0.0;
  perfil.push_back(aux);

  parametros(perfil, n, 0, 1, 1);
}

//************************************************************************
// cono
//************************************************************************

_cono::_cono(float r, float h, int n)
{
  _vertex3f aux;
  aux.x = r;
  aux.y = 0.0;
  aux.z = 0.0;
  perfil.push_back(aux);
  aux.x = 0.0;
  aux.y = h;
  aux.z = 0.0;
  perfil.push_back(aux);

  parametros(perfil, n, 1, 1, 1);
}

//************************************************************************
// esfera
//************************************************************************

_esfera::_esfera(float r = 1, int n = 40, int n2 = 40)
{
  _vertex3f aux;
  for (int i = 1; i < n; i++)
  {
    aux.x = r * cos(M_PI * i / n - M_PI / 2.0);
    aux.y = r * sin(M_PI * i / n - M_PI / 2.0);
    aux.z = 0.0;
    perfil.push_back(aux);

    parametros(perfil, n2, 2, 1, 1);
  }

  normales_vertices.resize(vertices.size());

  for (unsigned int i = 0; i < caras.size(); i++)
  {
    normales_vertices[caras[i]._0] = vertices[caras[i]._0];
    normales_vertices[caras[i]._1] = vertices[caras[i]._1];
    normales_vertices[caras[i]._2] = vertices[caras[i]._2];
  }
}

//************************************************************************
// objeto por extrusión
//************************************************************************

_extrusion::_extrusion(vector<_vertex3f> poligono, float x, float y, float z)
{
  int i;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int num_aux;

  // tratamiento de los vértices

  num_aux = poligono.size();
  vertices.resize(num_aux * 2);
  for (i = 0; i < num_aux; i++)
  {
    vertices[2 * i] = poligono[i];
    vertices[2 * i + 1].x = poligono[i].x + x;
    vertices[2 * i + 1].y = poligono[i].y + y;
    vertices[2 * i + 1].z = poligono[i].z + z;
  }

  // tratamiento de las caras

  caras.resize(num_aux * 2);
  int c = 0;
  for (i = 0; i < num_aux; i++)
  {
    caras[c]._0 = i * 2;
    caras[c]._1 = (i * 2 + 2) % (num_aux * 2);
    caras[c]._2 = i * 2 + 1;
    c = c + 1;
    caras[c]._0 = (i * 2 + 2) % (num_aux * 2);
    caras[c]._1 = (i * 2 + 2) % (num_aux * 2) + 1;
    caras[c]._2 = i * 2 + 1;
    c = c + 1;
  }
  calcular_normales_caras();
  calcular_normales_vertices();
}

_rotacion_ply::_rotacion_ply(const string filename, int n)
{
  ply.create(filename);
  parametros(ply.vertices, n, 0, 1, 1);
}

_pala::_pala(float radio, float ancho, int num)
{
  vector<_vertex3f> perfil;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int i, j;

  vertice_aux.x = radio;
  vertice_aux.y = 0;
  vertice_aux.z = -ancho / 2.0;
  perfil.push_back(vertice_aux);
  vertice_aux.z = ancho / 2.0;
  perfil.push_back(vertice_aux);

  // tratamiento de los vértices

  for (j = 0; j <= num; j++)
  {
    for (i = 0; i < 2; i++)
    {
      vertice_aux.x = perfil[i].x * cos(M_PI * j / (1.0 * num)) -
                      perfil[i].y * sin(M_PI * j / (1.0 * num));
      vertice_aux.y = perfil[i].x * sin(M_PI * j / (1.0 * num)) +
                      perfil[i].y * cos(M_PI * j / (1.0 * num));
      vertice_aux.z = perfil[i].z;
      vertices.push_back(vertice_aux);
    }
  }

  // tratamiento de las caras

  for (j = 0; j < num; j++)
  {
    cara_aux._0 = j * 2;
    cara_aux._1 = (j + 1) * 2;
    cara_aux._2 = (j + 1) * 2 + 1;
    caras.push_back(cara_aux);

    cara_aux._0 = j * 2;
    cara_aux._1 = (j + 1) * 2 + 1;
    cara_aux._2 = j * 2 + 1;
    caras.push_back(cara_aux);
  }

  // tapa inferior
  vertice_aux.x = 0;
  vertice_aux.y = 0;
  vertice_aux.z = -ancho / 2.0;
  vertices.push_back(vertice_aux);

  for (j = 0; j < num; j++)
  {
    cara_aux._0 = j * 2;
    cara_aux._1 = (j + 1) * 2;
    cara_aux._2 = vertices.size() - 1;
    caras.push_back(cara_aux);
  }

  // tapa superior
  vertice_aux.x = 0;
  vertice_aux.y = 0;
  vertice_aux.z = ancho / 2.0;
  vertices.push_back(vertice_aux);

  for (j = 0; j < num; j++)
  {
    cara_aux._0 = j * 2 + 1;
    cara_aux._1 = (j + 1) * 2 + 1;
    cara_aux._2 = vertices.size() - 1;
    caras.push_back(cara_aux);
  }

  colors_chess(1.0, 1.0, 0.0, 0.0, 0.0, 1.0);
}

_brazo::_brazo()
{
  ancho = 0.6;
  alto = 0.1;
  fondo = 0.1;
  colors_chess(1.0, 1.0, 0.0, 0.0, 0.0, 1.0);
};

void _brazo::draw(_modo modo, float r, float g, float b, float grosor)
{
  glPushMatrix();
  glScalef(ancho, alto, fondo);
  glTranslatef(0.5, 0, 0);
  cubo.draw(modo, r, g, b, grosor);
  glPopMatrix();
};

//************************************************************************
// cabina
//************************************************************************

_cabina::_cabina()
{
  ancho = 0.4;
  alto = 0.6;
  fondo = 0.4;
  cubo.colors_chess(1.0, 1.0, 0.0, 0.0, 0.0, 1.0);
};

void _cabina::draw(_modo modo, float r, float g, float b, float grosor)
{
  glPushMatrix();
  glScalef(ancho, alto, fondo);
  cubo.draw(modo, r, g, b, grosor);
  glPopMatrix();
}

//************************************************************************
// sustentación
//************************************************************************

_sustentacion::_sustentacion()
{
  ancho = 1.2;
  alto = 0.3;
  fondo = 0.8;
  radio = 0.15;
  base.colors_chess(1.0, 1.0, 0.0, 0.0, 0.0, 1.0);
}

void _sustentacion::draw(_modo modo, float r, float g, float b, float grosor)
{
  glPushMatrix();
  glTranslatef(2 * ancho / 6, -alto / 2.0, 0);
  glRotatef(90, 1, 0, 0);
  glScalef(radio, fondo / 2.2, radio);
  rueda.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-2 * ancho / 6, -alto / 2.0, 0);
  glRotatef(90, 1, 0, 0);
  glScalef(radio, fondo / 2.2, radio);
  rueda.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(ancho, alto, fondo);
  base.draw(modo, r, g, b, grosor);
  glPopMatrix();
}

//************************************************************************
// excavadora (montaje del objeto final)
//************************************************************************

_excavadora::_excavadora()
{
  giro_cabina = 0.0;
  giro_primer_brazo = 0.0;
  giro_primer_brazo_max = 0;
  giro_primer_brazo_min = -90;
  giro_segundo_brazo = 0.0;
  giro_segundo_brazo_max = 30;
  giro_segundo_brazo_min = 0;
  giro_pala = 0.0;
  giro_pala_max = 50.0;
  giro_pala_min = -90.0;

  tamanio_pala = 0.15;
}

void _excavadora::draw(_modo modo, float r, float g, float b, float grosor)
{
  glPushMatrix();

  sustentacion.draw(modo, r, g, b, grosor);

  glTranslatef(0, (cabina.alto + sustentacion.alto) / 2.0, 0);
  glRotatef(giro_cabina, 0, 1, 0);
  cabina.draw(modo, r, g, b, grosor);

  glTranslatef(cabina.ancho / 2.0, 0, 0);
  glRotatef(giro_segundo_brazo, 0, 0, 1);
  brazo.draw(modo, r, g, b, grosor);

  glTranslatef(brazo.ancho, 0, 0);
  glRotatef(giro_primer_brazo, 0, 0, 1);
  brazo.draw(modo, r, g, b, grosor);

  glTranslatef(brazo.ancho, 0, 0);
  glRotatef(giro_pala, 0, 0, 1);
  glTranslatef(tamanio_pala, 0, 0);
  glScalef(tamanio_pala, tamanio_pala, tamanio_pala);
  pala.draw(modo, r, g, b, grosor);
  glPopMatrix();
}

////////////////////////////////////////////////////////

void materiales(int material)
{
  switch (material)
  {
  case 0:
  { // Perla
    GLfloat Material_diffuse[] = {0.427451f, 0.470588f, 0.541176f, 1.0f};
    GLfloat Material_ambient[] = {0.105882f, 0.058824f, 0.113725f, 1.0f};
    GLfloat Material_specular[] = {0.333333f, 0.333333f, 0.521569f, 1.0f};

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *)&Material_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *)&Material_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *)&Material_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 9.84615f);
  }
  break;
  case 1:
  { // Jade
    GLfloat Material_diffuse[] = {0.54f, 0.89f, 0.63f, 0.95f};
    GLfloat Material_ambient[] = {0.135f, 0.2225f, 0.1575f, 0.95f};
    GLfloat Material_specular[] = {0.316228f, 0.316228f, 0.316228f, 0.95f};

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *)&Material_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *)&Material_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *)&Material_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 12.8f);
  }
  break;
  case 2:
  { // Oro
    GLfloat Material_diffuse[] = {0.780392f, 0.568627f, 0.113725f, 1.0f};
    GLfloat Material_ambient[] = {0.329412f, 0.223529f, 0.027451f, 1.0f};
    GLfloat Material_specular[] = {0.992157f, 0.941176f, 0.807843f, 1.0f};

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *)&Material_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *)&Material_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *)&Material_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 27.8974f);
  }
  break;
  case 3:
  { // Ruby
    GLfloat Material_diffuse[] = {0.61424f, 0.04136f, 0.04136f, 0.55f};
    GLfloat Material_ambient[] = {0.1745f, 0.01175f, 0.01175f, 0.55f};
    GLfloat Material_specular[] = {0.727811f, 0.626959f, 0.626959f, 0.55f};

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (GLfloat *)&Material_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (GLfloat *)&Material_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *)&Material_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 76.8f);
  }
  break;
  }
}

// Rueda
_wheel::_wheel()
{
  objeto = true;
  cylinder.objeto = true;
}

void _wheel::draw(_modo modo, float r, float g, float b, float grosor)
{
  glPushMatrix();
  glRotatef(90, 0, 0, 1);
  glScalef(1, 0.2, 1);
  materiales(2);
  cylinder.draw(modo, r, g, b, grosor);
  glPopMatrix();
}

// Hoja
_blade::_blade()
{
  objeto = true;
  cube.objeto = true;
}

void _blade::draw(_modo modo, float r, float g, float b, float grosor)
{
  glPushMatrix();
  glRotatef(0, 0, 0, 1);
  glScalef(0.2, 0.03, 2);
  cube.draw(modo, r, g, b, grosor);
  glPopMatrix();
}

// Puerta
_door::_door()
{
}

void _door::draw(_modo modo, float r, float g, float b, float grosor)
{
  glPushMatrix();
  glRotatef(120, 0, 0, 1);
  glScalef(0.5, 0.05, 0.9);
  cube.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.1, -0.18, 0);
  glRotatef(30, 0, 0, 1);
  glScalef(0.1, 0.2, 0.45);
  wheel.draw(modo, r, g, b, grosor);
  glPopMatrix();
}

// Metralleta
_machinegun::_machinegun()
{
  objeto = true;
  cylinder.objeto = true;
}

void _machinegun::draw(_modo modo, float r, float g, float b, float grosor)
{
  glPushMatrix();
  glRotatef(90, 1, 0, 0);
  glScalef(0.15, 0.3, 0.15);
  cylinder.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 0, 0.3);
  glRotatef(90, 1, 0, 0);
  glScalef(0.03, 0.1, 0.03);
  cylinder.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 0.075, 0.3);
  glRotatef(90, 1, 0, 0);
  glScalef(0.03, 0.1, 0.03);
  cylinder.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, -0.075, 0.3);
  glRotatef(90, 1, 0, 0);
  glScalef(0.03, 0.1, 0.03);
  cylinder.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.075, 0, 0.3);
  glRotatef(90, 1, 0, 0);
  glScalef(0.03, 0.1, 0.03);
  cylinder.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.075, 0, 0.3);
  glRotatef(90, 1, 0, 0);
  glScalef(0.03, 0.1, 0.03);
  cylinder.draw(modo, r, g, b, grosor);
  glPopMatrix();
}

// balas
_bullet::_bullet()
{
  objeto = true;
  cylinder.objeto = true;
}

void _bullet::draw(_modo modo, float r, float g, float b, float grosor)
{
  glPushMatrix();
  glTranslatef(0, 0, 0.3);
  glRotatef(90, 1, 0, 0);
  glScalef(0.01, 0.05, 0.01);
  cylinder.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 0.075, 0.3);
  glRotatef(90, 1, 0, 0);
  glScalef(0.01, 0.05, 0.01);
  cylinder.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, -0.075, 0.3);
  glRotatef(90, 1, 0, 0);
  glScalef(0.01, 0.05, 0.01);
  cylinder.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.075, 0, 0.3);
  glRotatef(90, 1, 0, 0);
  glScalef(0.01, 0.05, 0.01);
  cylinder.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.075, 0, 0.3);
  glRotatef(90, 1, 0, 0);
  glScalef(0.01, 0.05, 0.01);
  cylinder.draw(modo, r, g, b, grosor);
  glPopMatrix();
}

// Helice
_propeller::_propeller()
{
  objeto = true;
  cylinder.objeto = true;
}

void _propeller::draw(_modo modo, float r, float g, float b, float grosor)
{
  // Las helices se crearan a partir de dos hojas.
  glPushMatrix();
  glScalef(1, 1, 1.2);
  blade.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glRotatef(90, 0, 1, 0);
  glScalef(1, 1, 1.2);
  blade.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // Añadimos un objeto rueda que servira de union entre helices.
  glPushMatrix();
  glTranslatef(0.02, 0.05, 0);
  glRotatef(90, 0, 0, 1);
  glScalef(0.2, 0.2, 0.2);
  wheel.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // La estructura que conectara con la cabina sera un cilindro.
  glPushMatrix();
  glRotatef(90, 0, 1, 0);
  glTranslatef(0, -0.4, 0);
  glScalef(0.1, 0.4, 0.1);
  cylinder.draw(modo, r, g, b, grosor);
  glPopMatrix();
}

// Patines
_skids::_skids()
{
  objeto = true;
  cylinder.objeto = true;
}

void _skids::draw(_modo modo, float r, float g, float b, float grosor)
{
  // Las dos patas horizontales paralelas
  glPushMatrix();
  glTranslatef(0.3, -0.1, 0);
  glRotatef(90, 1, 0, 0);
  glScalef(0.05, 0.8, 0.05);
  materiales(3);
  cylinder.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.3, -0.1, 0);
  glRotatef(90, 1, 0, 0);
  glScalef(0.05, 0.8, 0.05);
  materiales(3);
  cylinder.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // Las dos patas delanteras que unen la cabina con las patas de apoyo.
  glPushMatrix();
  glTranslatef(0.3, 0.1, 0.6);
  glRotatef(-15, 1, 0, 0);
  glScalef(0.05, 0.2, 0.05);
  materiales(3);
  cylinder.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.3, 0.1, 0.6);
  glRotatef(-15, 1, 0, 0);
  glScalef(0.05, 0.2, 0.05);
  materiales(3);
  cylinder.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // Las dos patas traseras que unen la cabina con las patas de apoyo.
  glPushMatrix();
  glTranslatef(0.3, 0.1, -0.2);
  glRotatef(5, 1, 0, 0);
  glScalef(0.05, 0.2, 0.05);
  materiales(3);
  cylinder.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.3, 0.1, -0.2);
  glRotatef(5, 1, 0, 0);
  glScalef(0.05, 0.2, 0.05);
  materiales(3);
  cylinder.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // Parte saliente de las patas de apoyo (Sensacion de curvatura de las patas).
  glPushMatrix();
  glTranslatef(0.3, 0, 0.88);
  glRotatef(45, 1, 0, 0);
  glScalef(0.05, 0.17, 0.05);
  materiales(3);
  cylinder.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.3, 0, 0.88);
  glRotatef(45, 1, 0, 0);
  glScalef(0.05, 0.17, 0.05);
  materiales(3);
  cylinder.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // Las dos ruedas del helicoptero.
  glPushMatrix();
  glTranslatef(0.35, -0.1, -0.3);
  glScalef(0.2, 0.12, 0.12);
  wheel.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.35, -0.1, -0.3);
  glScalef(0.2, 0.12, 0.12);
  wheel.draw(modo, r, g, b, grosor);
  glPopMatrix();
}

// Cola
_tail::_tail()
{
  objeto = true;
  cylinder.objeto = true;
  cone.objeto = true;
  cube.objeto = true;
}

void _tail::draw(_modo modo, float r, float g, float b, float grosor)
{
  // Añadimos una helice a la cola.
  glPushMatrix();
  glScalef(0.4, 0.4, 0.4);
  glRotatef(90, 1, 0, 0);
  glRotatef(little_helice_rotation, 0, 1, 0);
  propeller.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // Estructura de union de la cola con la cabina.
  glPushMatrix();
  glTranslatef(-0.6, 0, -0.2);
  glRotatef(90, 0, 0, 1);
  glScalef(0.05, 0.8, 0.15);
  cylinder.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // Estructura de aleron unida con la cola.
  glPushMatrix();
  glTranslatef(0, 0, -0.2);
  glRotatef(-25, 0, 0, 1);
  glScalef(0.1, 0.5, 0.1);
  cone.draw(modo, r, g, b, grosor);
  glPopMatrix();

  // Trio de cubo que forman los alerones.
  glPushMatrix();
  glTranslatef(0.25, 0.5, -0.2);
  glScalef(0.1, 0.02, 0.4);
  cube.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.25, 0.5, -0.4);
  glScalef(0.1, 0.2, 0.02);
  cube.draw(modo, r, g, b, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.25, 0.5, 0);
  glScalef(0.1, 0.2, 0.02);
  cube.draw(modo, r, g, b, grosor);
  glPopMatrix();
}

// Helicoptero
_helicopter::_helicopter()
{
  objeto = true;
  sphere.objeto = true;
  cone.objeto = true;
  cylinder.objeto = true;

  int color = 80;
  piezas = 8;
  grosor_select = 0.5;
  color_pick = _vertex3f(1.0, 0.0, 0.0);
  color_select.resize(piezas);
  activo.resize(piezas);

  for (int i = 0; i < piezas; i++)
  {
    activo[i] = 0;
    color_select[i].r = color_select[i].g = color_select[i].b = color;
    color += 20;
  }
}

void _helicopter::draw(_modo modo, float r, float g, float b, float grosor)
{
  float r_p, g_p, b_p;

  r_p = color_pick.r;
  g_p = color_pick.g;
  b_p = color_pick.b;

  // La esfera y el cono son la estructura de la cabina.
  glPushMatrix();
  glScalef(0.5, 0.5, 0.9);
  materiales(0);
  if (activo[0] == 1)
    sphere.draw(EDGES, r_p, g_p, b_p, grosor_select);
  else
    sphere.draw(modo, 0.3, 0.5, 0.6, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 0, -0.3);
  glRotatef(-90, 1, 0, 0);
  glScalef(0.4, 0.6, 0.45);
  materiales(1);
  if (activo[1] == 1)
    cone.draw(EDGES, r_p, g_p, b_p, grosor_select);
  else
    cone.draw(modo, 0, 0.5, 0.4, grosor);
  glPopMatrix();

  // Añadimos la helice.
  glPushMatrix();
  glTranslatef(0, 0.8, 0);
  glRotatef(helice_rotation, 0, 1, 0);
  materiales(1);
  if (activo[2] == 1)
    propeller.draw(EDGES, r_p, g_p, b_p, grosor_select);
  else
    propeller.draw(modo, 0, 0.5, 0.4, grosor);
  glPopMatrix();

  // Añadimos la cola.
  glPushMatrix();
  glTranslatef(0.2, 0, -2);
  glRotatef(90, 0, 1, 0);
  tail.little_helice_rotation = little_helice_rotation;
  materiales(2);
  if (activo[3] == 1)
    tail.draw(EDGES, r_p, g_p, b_p, grosor_select);
  else
    tail.draw(modo, 0.3, 0.5, 0.6, grosor);
  glPopMatrix();

  // Añadimos las patas.
  glPushMatrix();
  glTranslatef(0, -0.6, -0.2);
  if (activo[4] == 1)
    skids.draw(EDGES, r_p, g_p, b_p, grosor_select);
  else
    skids.draw(modo, 0.6, 0.6, 0.6, grosor);
  glPopMatrix();

  // Añadimos las puertas
  glPushMatrix();
  glTranslatef(door_translation + 0.25, 0, 0);
  glRotatef(door_rotation, 0, 0, 1);
  materiales(2);
  if (activo[5] == 1)
    door.draw(EDGES, r_p, g_p, b_p, grosor_select);
  else
    door.draw(modo, 0.3, 0.5, 0.5, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-door_translation - 0.25, 0, 0);
  glRotatef(-(door_rotation) + 300, 0, 0, 1);
  if (activo[6] == 1)
    door.draw(EDGES, r_p, g_p, b_p, grosor_select);
  else
    door.draw(modo, 0.3, 0.5, 0.5, grosor);
  glPopMatrix();

  // Añadimos la torreta
  glPushMatrix();
  glTranslatef(0, machinegun_translation_y + 0.1, machinegun_translation_z - 0.3);
  glRotatef(130, 1, 0, 0);
  glScalef(0.05, 0.3, 0.05);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, machinegun_translation_y, machinegun_translation_z);
  glRotatef(machinegun_rotation, 0, 0, 1);
  materiales(1);
  if (activo[7] == 1)
    gun.draw(EDGES, r_p, g_p, b_p, grosor_select);
  else
    gun.draw(modo, 0.3, 0.5, 0.5, grosor);
  glPopMatrix();

  // Añadimos balas
  glPushMatrix();
  glTranslatef(0, machinegun_translation_y, machinegun_translation_z + bullet_translation);
  materiales(3);
  bullet.draw(modo, 0.8, 0.2, 0, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, machinegun_translation_y, machinegun_translation_z + bullet_translation - 0.25);
  materiales(3);
  bullet.draw(modo, 0.8, 0.2, 0, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, machinegun_translation_y, machinegun_translation_z + bullet_translation - 0.5);
  materiales(3);
  bullet.draw(modo, 0.8, 0.2, 0, grosor);
  glPopMatrix();
}

void _helicopter::seleccion()
{
  _vertex3i color;

  glPushMatrix();
  glScalef(0.5, 0.5, 0.9);
  color = color_select[0];
  sphere.draw(SELECT, color.r, color.g, color.b, 1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 0, -0.3);
  glRotatef(-90, 1, 0, 0);
  glScalef(0.4, 0.6, 0.45);
  materiales(1);
  color = color_select[1];
  cone.draw(SELECT, color.r, color.g, color.b, 1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 0.8, 0);
  glRotatef(helice_rotation, 0, 1, 0);
  color = color_select[2];
  propeller.draw(SELECT, color.r, color.g, color.b, 1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.2, 0, -2);
  glRotatef(90, 0, 1, 0);
  tail.little_helice_rotation = little_helice_rotation;
  color = color_select[3];
  tail.draw(SELECT, color.r, color.g, color.b, 1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, -0.6, -0.2);
  color = color_select[4];
  skids.draw(SELECT, color.r, color.g, color.b, 1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(door_translation + 0.25, 0, 0);
  glRotatef(door_rotation, 0, 0, 1);
  color = color_select[5];
  door.draw(SELECT, color.r, color.g, color.b, 1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-door_translation - 0.25, 0, 0);
  glRotatef(-(door_rotation) + 300, 0, 0, 1);
  color = color_select[6];
  door.draw(SELECT, color.r, color.g, color.b, 1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, machinegun_translation_y, machinegun_translation_z);
  glRotatef(machinegun_rotation, 0, 0, 1);
  color = color_select[7];
  gun.draw(SELECT, color.r, color.g, color.b, 1);
  glPopMatrix();
}

_textura::_textura()
{
}

void _textura::prepara_textura(string file, GLuint *tex_id)
{
  vector<unsigned char> data;
  CImg<unsigned char> image;
  textura_id = tex_id;

  image.load(file.c_str());

  // empaquetamos bien los datos
  for (long y = 0; y < image.height(); y++)
    for (long x = 0; x < image.width(); x++)
    {
      unsigned char *r = image.data(x, y, 0, 0);
      unsigned char *g = image.data(x, y, 0, 1);
      unsigned char *b = image.data(x, y, 0, 2);
      data.push_back(*r);
      data.push_back(*g);
      data.push_back(*b);
    }

  glGenTextures(1, tex_id);
  glBindTexture(GL_TEXTURE_2D, *textura_id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // TRASFIERE LOS DATOS A GPU
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width(), image.height(),
               0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);
}

void _textura::dibuja()
{
  glEnable(GL_TEXTURE_2D);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY_EXT);

  glBindTexture(GL_TEXTURE_2D, *textura_id);

  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glTexCoordPointer(2, GL_FLOAT, 0, tex_vertices);
  glScalef(0.5, 0.5, 0.5);
  glDrawArrays(GL_QUADS, 0, 24);

  glDisableClientState(GL_VERTEX_ARRAY);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
}

void _textura::libera_textura(GLuint *tex_id)
{
  glDeleteTextures(1, tex_id);
}
