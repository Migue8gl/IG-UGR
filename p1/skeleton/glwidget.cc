/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#include "glwidget.h"
#include "window.h"

using namespace std;
using namespace _gl_widget_ne;
using namespace _colors_ne;


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_gl_widget::_gl_widget(_window *Window1):Window(Window1)
{
    setMinimumSize(300, 300);
    setFocusPolicy(Qt::StrongFocus);
}


/*****************************************************************************//**
 * Evento tecla pulsada
 *
 *
 *
 *****************************************************************************/

void _gl_widget::keyPressEvent(QKeyEvent *Keyevent)
{
    switch(Keyevent->key()){
    case Qt::Key_1:Object=OBJECT_TETRAHEDRON;
        Window->set_load_item(0);
        break;
    case Qt::Key_2:Object=OBJECT_CUBE;
        Window->set_load_item(1);
        break;
    case Qt::Key_3:Object=OBJECT_PYRAMID;
        Window->set_load_item(2);
        break;

    case Qt::Key_P:Draw_point=!Draw_point;
        Window->set_mode_point(Draw_point);
        break;
    case Qt::Key_L:Draw_line=!Draw_line;
        Window->set_mode_line(Draw_line);
        break;
    case Qt::Key_F:Draw_fill=!Draw_fill;
        if(Draw_chess)
        {
            Draw_chess=!Draw_chess;
            Window->set_mode_chess(Draw_chess);
        }
        Window->set_mode_fill(Draw_fill);
        break;
    case Qt::Key_C:Draw_chess=!Draw_chess;
        if(Draw_fill)
        {
            Draw_fill=!Draw_fill;
            Window->set_mode_fill(Draw_fill);
        }
        Window->set_mode_chess(Draw_chess);
        break;

    case Qt::Key_Left:Observer_angle_y-=ANGLE_STEP;break;
    case Qt::Key_Right:Observer_angle_y+=ANGLE_STEP;break;
    case Qt::Key_Up:Observer_angle_x-=ANGLE_STEP;break;
    case Qt::Key_Down:Observer_angle_x+=ANGLE_STEP;break;
    case Qt::Key_PageUp:Observer_distance*=1.2;break;
    case Qt::Key_PageDown:Observer_distance/=1.2;break;
    }

    update();
}

void _gl_widget::set_mode_point(int State)
{
    Q_UNUSED(State);
    Draw_point=!Draw_point;
    update();
}

void _gl_widget::set_mode_line(int State)
{
    Q_UNUSED(State);
    Draw_line=!Draw_line;
    update();
}

void _gl_widget::set_mode_fill(int State)
{
    Q_UNUSED(State);
    Draw_fill=!Draw_fill;
    if(Draw_chess){Draw_chess=!Draw_chess;Window->set_mode_chess(Draw_chess);}
    update();
}

void _gl_widget::set_mode_chess(int State)
{
    Q_UNUSED(State);
    Draw_chess=!Draw_chess;
    if(Draw_fill){Draw_fill=!Draw_fill;Window->set_mode_fill(Draw_fill);}
    update();
}

void _gl_widget::set_load_item(int Item)
{
    Q_UNUSED(Item);
    switch(Item){
    case 0:Object=OBJECT_TETRAHEDRON;break;
    case 1:Object=OBJECT_CUBE;break;
    case 2:Object=OBJECT_PYRAMID;break;
    }
    update();
}


/*****************************************************************************//**
 * Limpiar ventana
 *
 *
 *
 *****************************************************************************/

void _gl_widget::clear_window()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}



/*****************************************************************************//**
 * Funcion para definir la transformación de proyeccion
 *
 *
 *
 *****************************************************************************/

void _gl_widget::change_projection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
    // Front_plane>0  Back_plane>PlanoDelantero)
    glFrustum(X_MIN,X_MAX,Y_MIN,Y_MAX,FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE);
}



/*****************************************************************************//**
 * Funcion para definir la transformación de vista (posicionar la camara)
 *
 *
 *
 *****************************************************************************/

void _gl_widget::change_observer()
{
    // posicion del observador
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0,0,-Observer_distance);
    glRotatef(Observer_angle_x,1,0,0);
    glRotatef(Observer_angle_y,0,1,0);
}


/*****************************************************************************//**
 * Funcion que dibuja los objetos
 *
 *
 *
 *****************************************************************************/

void _gl_widget::draw_objects()
{
    Axis.draw_line();

    if (Draw_point){
        glPointSize(5);
        glColor3fv((GLfloat *) &BLACK);
        switch (Object){
        case OBJECT_TETRAHEDRON:Tetrahedron.draw_point();break;
        case OBJECT_CUBE:Cube.draw_point();break;
        case OBJECT_PYRAMID:Pyramid.draw_point();break;
        default:break;
        }
    }

    if (Draw_line){
        glLineWidth(3);
        glColor3fv((GLfloat *) &MAGENTA);
        switch (Object){
        case OBJECT_TETRAHEDRON:Tetrahedron.draw_line();break;
        case OBJECT_CUBE:Cube.draw_line();break;
        case OBJECT_PYRAMID:Pyramid.draw_line();break;
        default:break;
        }
    }

    if (Draw_fill){
        glColor3fv((GLfloat *) &BLUE);
        switch (Object){
        case OBJECT_TETRAHEDRON:Tetrahedron.draw_fill();break;
        case OBJECT_CUBE:Cube.draw_fill();break;
        case OBJECT_PYRAMID:Pyramid.draw_fill();break;
        default:break;
        }
    }

    if (Draw_chess){
        switch (Object){
        case OBJECT_TETRAHEDRON:Tetrahedron.draw_chess();break;
        case OBJECT_CUBE:Cube.draw_chess();break;
        case OBJECT_PYRAMID:Pyramid.draw_chess();break;
        default:break;
        }
    }
}



/*****************************************************************************//**
 * Evento de dibujado
 *
 *
 *
 *****************************************************************************/

void _gl_widget::paintGL()
{
    clear_window();
    change_projection();
    change_observer();
    draw_objects();
}


/*****************************************************************************//**
 * Evento de cambio de tamaño de la ventana
 *
 *
 *
 *****************************************************************************/

void _gl_widget::resizeGL(int Width1, int Height1)
{
    glViewport(0,0,Width1,Height1);
}


/*****************************************************************************//**
 * Inicialización de OpenGL
 *
 *
 *
 *****************************************************************************/

void _gl_widget::initializeGL()
{
    const GLubyte* strm;

    strm = glGetString(GL_VENDOR);
    std::cerr << "Vendor: " << strm << "\n";
    strm = glGetString(GL_RENDERER);
    std::cerr << "Renderer: " << strm << "\n";
    strm = glGetString(GL_VERSION);
    std::cerr << "OpenGL Version: " << strm << "\n";

    if (strm[0] == '1'){
        std::cerr << "Only OpenGL 1.X supported!\n";
        exit(-1);
    }

    strm = glGetString(GL_SHADING_LANGUAGE_VERSION);
    std::cerr << "GLSL Version: " << strm << "\n";

    int Max_texture_size=0;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &Max_texture_size);
    std::cerr << "Max texture size: " << Max_texture_size << "\n";

    glClearColor(1.0,1.0,1.0,1.0);
    glEnable(GL_DEPTH_TEST);;

    Observer_angle_x=0;
    Observer_angle_y=0;
    Observer_distance=DEFAULT_DISTANCE;

    Object=OBJECT_TETRAHEDRON;
    Draw_point=false;
    Draw_line=false;
    Draw_fill=false;
    Draw_chess=false;
}
