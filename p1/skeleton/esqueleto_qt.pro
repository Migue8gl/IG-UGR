HEADERS += \
  colors.h \
  basic_object3d.h \
  object3d.h \
  axis.h \
  pyramid.h \
  tetrahedron.h \
  cube.h \
  glwidget.h \
  window.h

SOURCES += \
  basic_object3d.cc \
  object3d.cc \
  axis.cc \
  pyramid.cc \
  tetrahedron.cc \
  cube.cc \
  main.cc \
  glwidget.cc \
  window.cc


LIBS += -L/usr/X11R6/lib64 -lGL


CONFIG += c++11
QT += widgets
