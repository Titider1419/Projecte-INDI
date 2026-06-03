TEMPLATE    = app
QT         += opengl

INCLUDEPATH +=  /usr/include/glm
INCLUDEPATH += /home/andres/glm-master
INCLUDEPATH += /home/andres/UNI/Q4/INDI/labs/projecte/Model
INCLUDEPATH += ../ModelS

FORMS += MyForm.ui

HEADERS += MyForm.h BL2GLWidget.h MyGLWidget.h

SOURCES += main.cpp  MyForm.cpp \
        BL2GLWidget.cpp MyGLWidget.cpp ../Model/model.cpp

RESOURCES += \
    resource.qrc
