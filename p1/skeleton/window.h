/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardPaths>
#include <QFileDialog>
#include <QDialog>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QGuiApplication>
#include "QCheckBox"
#include "QLabel"
#include "QComboBox"
#include "glwidget.h"


class _gl_widget;


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _window : public QMainWindow
{
    Q_OBJECT

public:
    _window();

    void set_mode_point(bool State);
    void set_mode_line(bool State);
    void set_mode_fill(bool State);
    void set_mode_chess(bool State);
    void set_load_item(int index);

public slots:
    void mode_point_slot(int State);
    void mode_line_slot(int State);
    void mode_fill_slot(int State);
    void mode_chess_slot(int State);
    void load_item_slot(int Item);

private:
    _gl_widget *GL_widget;
    QCheckBox *CB1=nullptr;
    QCheckBox *CB2=nullptr;
    QCheckBox *CB3=nullptr;
    QCheckBox *CB4=nullptr;
    QComboBox *CBB1=nullptr;
};

#endif
