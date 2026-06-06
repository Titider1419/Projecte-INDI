TEMPLATE    = app
QT         += opengl

INCLUDEPATH += $$PWD/assimp/include
INCLUDEPATH += $$PWD/assimp
INCLUDEPATH += $$PWD/Models3D

FORMS += MyForm.ui

HEADERS += MyForm.h BL2GLWidget.h MyGLWidget.h
HEADERS += ./assimp/Mesh.h


SOURCES += main.cpp  MyForm.cpp \
        BL2GLWidget.cpp MyGLWidget.cpp ./Models3D/model.cpp

RESOURCES += \
    resource.qrc


SOURCES += ./assimp/Mesh.cpp \
           ./assimp/ogldev_texture.cpp \
           ./assimp/ogldev_util.cpp \
           ./assimp/3rdparty/stb_image.cpp

LIBS += $$PWD/assimp/lib/libassimp.a
LIBS += $$PWD/assimp/lib/libdraco.a
LIBS += $$PWD/assimp/lib/libkubazip.a
LIBS += $$PWD/assimp/lib/libminizip.a
LIBS += $$PWD/assimp/lib/libpoly2tri.a
LIBS += $$PWD/assimp/lib/libpolyclipping.a
LIBS += $$PWD/assimp/lib/libpugixml.a
LIBS += $$PWD/assimp/lib/libz.a

QMAKE_CXXFLAGS += -Wno-ignored-qualifiers -Wno-type-limits -Wno-unused-parameter
