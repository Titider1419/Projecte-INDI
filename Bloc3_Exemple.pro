TEMPLATE    = app
QT         += opengl

INCLUDEPATH +=  /usr/include/glm
INCLUDEPATH += /home/andres/glm-master
INCLUDEPATH += /home/andres/Model
INCLUDEPATH += ../ModelS

FORMS += MyForm.ui

HEADERS += MyForm.h BL3GLWidget.h MyGLWidget.h

SOURCES += main.cpp  MyForm.cpp \
        BL3GLWidget.cpp MyGLWidget.cpp ../Model/model.cpp
SOURCES += /home/andres/Model/model.cpp

RESOURCES += \
    resource.qrc
