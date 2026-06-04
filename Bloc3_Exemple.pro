TEMPLATE    = app
QT         += opengl

INCLUDEPATH += $$PWD/glm-master
INCLUDEPATH += $$PWD/Models3D

FORMS += MyForm.ui

HEADERS += MyForm.h BL2GLWidget.h MyGLWidget.h

SOURCES += main.cpp  MyForm.cpp \
        BL2GLWidget.cpp MyGLWidget.cpp ./Models3D/model.cpp

RESOURCES += \
    resource.qrc
