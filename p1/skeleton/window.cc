/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#include <QApplication>
#include <QAction>
#include <QMenuBar>
#include <QFrame>

#include "window.h"
#include "glwidget.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_window::_window()
{

    QSizePolicy Q(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QWidget *Central_widget = new QWidget(this);

    QFrame *Framed_widget= new QFrame(Central_widget);
    Framed_widget->setSizePolicy(Q);
    Framed_widget->setFrameStyle(QFrame::Panel);
    Framed_widget->setLineWidth(3);


    GL_widget = new _gl_widget(this);
    GL_widget->setSizePolicy(Q);

    QHBoxLayout *Horizontal_frame = new QHBoxLayout();
    Horizontal_frame->setContentsMargins(1,1,1,1);

    Horizontal_frame->addWidget(GL_widget);
    Framed_widget->setLayout(Horizontal_frame);

    QHBoxLayout *Horizontal_main = new QHBoxLayout(Central_widget);

    Horizontal_main->addWidget(Framed_widget);

    Central_widget->setLayout(Horizontal_main);
    setCentralWidget(Central_widget);

    QWidget *W1 = new QWidget;
    QVBoxLayout *LVP1 = new QVBoxLayout;
    QLabel *L1 = new QLabel("Point");
    QLabel *L2 = new QLabel("Line");
    QLabel *L3 = new QLabel("Fill");
    QLabel *L4 = new QLabel("Chess");
    QLabel *L5 = new QLabel("Figures:");

    CB1 = new QCheckBox;
    CB2 = new QCheckBox;
    CB3 = new QCheckBox;
    CB4 = new QCheckBox;

    CBB1 = new QComboBox;
    CBB1->addItem("Tetrahedron");
    CBB1->addItem("Cube");
    CBB1->addItem("Pyramid");

    LVP1->addWidget(L1);
    LVP1->addWidget(CB1);
    LVP1->addWidget(L2);
    LVP1->addWidget(CB2);
    LVP1->addWidget(L3);
    LVP1->addWidget(CB3);
    LVP1->addWidget(L4);
    LVP1->addWidget(CB4);
    LVP1->addWidget(L5);
    LVP1->addWidget(CBB1);
    LVP1->addStretch();
    W1->setLayout(LVP1);
    W1->setMinimumWidth(100);


    Horizontal_main->addWidget(W1);
    Central_widget->setLayout(Horizontal_main);
    setCentralWidget(Central_widget);
    connect(CB1,SIGNAL(stateChanged(int)),this,SLOT(mode_point_slot(int)));
    connect(CB2,SIGNAL(stateChanged(int)),this,SLOT(mode_line_slot(int)));
    connect(CB3,SIGNAL(stateChanged(int)),this,SLOT(mode_fill_slot(int)));
    connect(CB4,SIGNAL(stateChanged(int)),this,SLOT(mode_chess_slot(int)));
    connect(CBB1,SIGNAL(currentIndexChanged(int)),this,SLOT(load_item_slot(int)));

    // actions for file menu
    QAction *Exit = new QAction(QIcon("./icons/exit.png"), tr("&Exit..."), this);
    Exit->setShortcut(tr("Ctrl+Q"));
    Exit->setToolTip(tr("Exit the application"));
    connect(Exit, SIGNAL(triggered()), this, SLOT(close()));

    // menus
    QMenu *File_menu=menuBar()->addMenu(tr("&File"));
    File_menu->addAction(Exit);
    File_menu->setAttribute(Qt::WA_AlwaysShowToolTips);

    setWindowTitle(tr("Práctica 1"));

    resize(800,800);
}

void _window::mode_point_slot(int State)
{
    GL_widget->set_mode_point(State);
}

void _window::set_mode_point(bool State)
{
    CB1->blockSignals(true);
    if(State)
        CB1->setCheckState(Qt::Checked);
    else
        CB1->setCheckState(Qt::Unchecked);
    CB1->blockSignals(false);
}

void _window::mode_line_slot(int State)
{
    GL_widget->set_mode_line(State);
}

void _window::set_mode_line(bool State)
{
    CB2->blockSignals(true);
    if(State)
        CB2->setCheckState(Qt::Checked);
    else
        CB2->setCheckState(Qt::Unchecked);
    CB2->blockSignals(false);
}

void _window::mode_fill_slot(int State)
{
    GL_widget->set_mode_fill(State);
}

void _window::set_mode_fill(bool State)
{
    CB3->blockSignals(true);
    if(State)
        CB3->setCheckState(Qt::Checked);
    else
        CB3->setCheckState(Qt::Unchecked);
    CB3->blockSignals(false);
}

void _window::mode_chess_slot(int State)
{
    GL_widget->set_mode_chess(State);
}

void _window::set_mode_chess(bool State)
{
    CB4->blockSignals(true);
    if(State)
        CB4->setCheckState(Qt::Checked);
    else
        CB4->setCheckState(Qt::Unchecked);
    CB4->blockSignals(false);
}

void _window::load_item_slot(int Item)
{
    GL_widget->set_load_item(Item);
}

void _window::set_load_item(int index)
{
    CBB1->setCurrentIndex(index);
}
