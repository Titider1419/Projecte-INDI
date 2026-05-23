TEMPLATE    = app
QT         += opengl 

INCLUDEPATH +=  /home/est/e9978472/home-ubiwan-e9978472/glm-master

FORMS += MyForm.ui

HEADERS += MyForm.h BL2GLWidget.h MyGLWidget.h

SOURCES += main.cpp MyForm.cpp \
        BL2GLWidget.cpp MyGLWidget.cpp

RESOURCES += \
    resources.qrc
