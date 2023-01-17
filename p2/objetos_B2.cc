//**************************************************************************
// Práctica 2
//**************************************************************************

#include "objetos_B2.h"
#include "file_ply_stl.hpp"
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
  int i;
  glPointSize(grosor);
  glColor3f(r, g, b);
  glBegin(GL_POINTS);
  for (i = 0; i < vertices.size(); i++)
  {
    glVertex3fv((GLfloat *)&vertices[i]);
  }
  glEnd();
}

//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
}

//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
  int i;
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glLineWidth(grosor);
  glColor3f(r, g, b);
  glBegin(GL_TRIANGLES);
  for (i = 0; i < caras.size(); i++)
  {
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();
}

//*************************************************************************
// dibujar en modo sólido con un único color
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
  int i;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(r, g, b);
  glBegin(GL_TRIANGLES);
  for (i = 0; i < caras.size(); i++)
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
  int i;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);
  for (i = 0; i < caras.size(); i++)
  {
    glColor3fv((GLfloat *) &colores[i % 8]);
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
  }
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam) // da igual que no este centrado, o que una esquina comience en el eje de coordenadas
{
  // vertices
  vertices.resize(8);
  vertices[0].x = 0;
  vertices[0].y = 0;
  vertices[0].z = tam;
  vertices[1].x = tam;
  vertices[1].y = 0;
  vertices[1].z = tam;
  vertices[2].x = tam;
  vertices[2].y = 0;
  vertices[2].z = 0;
  vertices[3].x = 0;
  vertices[3].y = 0;
  vertices[3].z = 0;
  vertices[4].x = 0;
  vertices[4].y = tam;
  vertices[4].z = tam;
  vertices[5].x = tam;
  vertices[5].y = tam;
  vertices[5].z = tam;
  vertices[6].x = tam;
  vertices[6].y = tam;
  vertices[6].z = 0;
  vertices[7].x = 0;
  vertices[7].y = tam;
  vertices[7].z = 0;

  // triangulos
  caras.resize(12);
  caras[0]._0 = 0;
  caras[0]._1 = 1;
  caras[0]._2 = 4;
  caras[1]._0 = 1;
  caras[1]._1 = 5;
  caras[1]._2 = 4;
  caras[2]._0 = 1;
  caras[2]._1 = 2;
  caras[2]._2 = 5;
  caras[3]._0 = 2;
  caras[3]._1 = 6;
  caras[3]._2 = 5;
  caras[4]._0 = 2;
  caras[4]._1 = 3;
  caras[4]._2 = 6;
  caras[5]._0 = 3;
  caras[5]._1 = 7;
  caras[5]._2 = 6;
  caras[6]._0 = 3;
  caras[6]._1 = 0;
  caras[6]._2 = 7;
  caras[7]._0 = 0;
  caras[7]._1 = 4;
  caras[7]._2 = 7;
  caras[8]._0 = 4;
  caras[8]._1 = 5;
  caras[8]._2 = 6;
  caras[9]._0 = 4;
  caras[9]._1 = 6;
  caras[9]._2 = 7;
  caras[10]._0 = 3;
  caras[10]._1 = 1;
  caras[10]._2 = 0;
  caras[11]._0 = 3;
  caras[11]._1 = 2;
  caras[11]._2 = 1;
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
}

//*************************************************************************
// clase objeto ply
//*************************************************************************

_objeto_ply::_objeto_ply()
{
  // leer lista de coordenadas de vértices y lista de indices de vértices
}

void _objeto_ply::create(const char *ply)
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

  File.close();
}

//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{
}

void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tipo)
{
  int i, j;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int num_aux;

  // tratamiento de los vértices

  num_aux = perfil.size();
  // if(tipo==1) num_aux=num_aux-1;
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

  // tratamiento de las caras
  int c = 0;
  caras.resize(2 * (num_aux - 1) * num);
  for (j = 0; j < num; j++)
  {
    for (i = 0; i < num_aux - 1; i++)
    {
      caras[c]._0 = j * num_aux + i;
      caras[c]._1 = ((j + 1) % num) * num_aux + i + 1;
      caras[c]._2 = j * num_aux + i + 1;
      c++;
      caras[c]._0 = ((j + 1) % num) * num_aux + i + 1;
      caras[c]._1 = j * num_aux + i;
      caras[c]._2 = ((j + 1) % num) * num_aux + i;
      c++;
    }
  }

  // tapas
  float radio = sqrt(perfil[0].x * perfil[0].x + perfil[0].y * perfil[0].y);

  // tapa inferior
  vertice_aux.x = 0.0;
  if (tipo == 2)
    vertice_aux.y = -radio;
  else
    vertice_aux.y = perfil[0].y;
  vertice_aux.z = 0.0;
  vertices.push_back(vertice_aux);
  for (int j = 0; j < num; j++)
  {
    cara_aux._0 = vertices.size() - 1;
    cara_aux._1 = j * num_aux;
    cara_aux._2 = ((j + 1) % num) * num_aux;
    caras.push_back(cara_aux);
  }

  // tapa superior
  vertice_aux.x = 0.0;
  if (tipo == 0)
    vertice_aux.y = perfil[num_aux - 1].y;
  if (tipo == 1)
    vertice_aux.y = perfil[1].y;
  if (tipo == 2)
    vertice_aux.y = radio;
  vertice_aux.z = 0.0;
  vertices.push_back(vertice_aux);
  for (int j = 0; j < num; j++)
  {
    cara_aux._0 = vertices.size() - 1;
    cara_aux._1 = ((j + 1) % num) * num_aux + num_aux - 1;
    cara_aux._2 = j * num_aux + num_aux - 1;
    caras.push_back(cara_aux);
  }
}

//************************************************************************
// cilindro
//************************************************************************

//!!!
_cilindro::_cilindro(float r, float h, int n)
{
  num = n;
  _vertex3f aux;
  aux.x = r;
  aux.y = h;
  aux.z = 0.0;
  perfil.push_back(aux);
  aux.x = r;
  aux.y = -h;
  aux.z = 0.0;
  perfil.push_back(aux);

  parametros(perfil, n, 0); // el añade dos parametros más 0/1 para cada tapa no se ve/ se ve
}
//¡¡¡

//************************************************************************
// cono
//************************************************************************

//!!!
_cono::_cono(float r, float h, int n)
{
  num = n;
  _vertex3f aux;
  aux.x = 0.0;
  aux.y = h;
  aux.z = 0.0;
  perfil.push_back(aux);
  aux.x = r;
  aux.y = 0.0;
  aux.z = 0.0;
  perfil.push_back(aux);

  parametros(perfil, n, 1);
}
//¡¡¡

//************************************************************************
// esfera
//************************************************************************

//!!!
_esfera::_esfera(float r, int n)
{
  num = n;
  _vertex3f aux;
  for (int i = 1; i < n; i++)
  {
    aux.x = r * cos(M_PI * i / n - M_PI / 2.0);
    aux.y = r * sin(M_PI * i / n - M_PI / 2.0);
    aux.z = 0.0;
    perfil.push_back(aux);

    parametros(perfil, n, 2);
  }
}
//¡¡¡

//************************************************************************
// objeto por extrusión
//************************************************************************

_extrusion::_extrusion(vector<_vertex3f> poligono, float x, float y, float z)
{
  int i;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int num_aux;

  // tratamiento de los vértice

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
}

_rotacion_ply::_rotacion_ply(char *filename, int n)
{
  ply.create(filename);
  parametros(ply.vertices, n, 0);
}
