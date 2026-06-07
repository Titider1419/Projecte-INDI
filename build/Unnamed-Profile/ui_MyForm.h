/********************************************************************************
** Form generated from reading UI file 'MyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYFORM_H
#define UI_MYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "MyGLWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MyForm
{
public:
    QHBoxLayout *horizontalLayout;
    MyGLWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *startGame;
    QLabel *monedes;
    QLabel *label;
    QSlider *psiSlider;
    QLabel *label_2;
    QSlider *thetaSlider;
    QLabel *label_3;
    QSlider *zoomSlider;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *camaraGen;
    QRadioButton *primPersona;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *rotMonedes;
    QRadioButton *estMonedes;
    QPushButton *colorLlum;
    QLabel *label_4;
    QSlider *solSlider;
    QCheckBox *nocturn;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton;

    void setupUi(QWidget *MyForm)
    {
        if (MyForm->objectName().isEmpty())
            MyForm->setObjectName(QString::fromUtf8("MyForm"));
        MyForm->resize(819, 726);
        horizontalLayout = new QHBoxLayout(MyForm);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new MyGLWidget(MyForm);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(50, 50));

        horizontalLayout->addWidget(widget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        startGame = new QPushButton(MyForm);
        startGame->setObjectName(QString::fromUtf8("startGame"));

        verticalLayout->addWidget(startGame);

        monedes = new QLabel(MyForm);
        monedes->setObjectName(QString::fromUtf8("monedes"));

        verticalLayout->addWidget(monedes);

        label = new QLabel(MyForm);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        psiSlider = new QSlider(MyForm);
        psiSlider->setObjectName(QString::fromUtf8("psiSlider"));
        psiSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(psiSlider);

        label_2 = new QLabel(MyForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        thetaSlider = new QSlider(MyForm);
        thetaSlider->setObjectName(QString::fromUtf8("thetaSlider"));
        thetaSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(thetaSlider);

        label_3 = new QLabel(MyForm);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        zoomSlider = new QSlider(MyForm);
        zoomSlider->setObjectName(QString::fromUtf8("zoomSlider"));
        zoomSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(zoomSlider);

        widget_2 = new QWidget(MyForm);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_4 = new QHBoxLayout(widget_2);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        camaraGen = new QRadioButton(widget_2);
        camaraGen->setObjectName(QString::fromUtf8("camaraGen"));

        horizontalLayout_2->addWidget(camaraGen);

        primPersona = new QRadioButton(widget_2);
        primPersona->setObjectName(QString::fromUtf8("primPersona"));

        horizontalLayout_2->addWidget(primPersona);


        horizontalLayout_4->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(MyForm);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_5 = new QHBoxLayout(widget_3);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        rotMonedes = new QRadioButton(widget_3);
        rotMonedes->setObjectName(QString::fromUtf8("rotMonedes"));

        horizontalLayout_3->addWidget(rotMonedes);

        estMonedes = new QRadioButton(widget_3);
        estMonedes->setObjectName(QString::fromUtf8("estMonedes"));

        horizontalLayout_3->addWidget(estMonedes);


        horizontalLayout_5->addLayout(horizontalLayout_3);


        verticalLayout->addWidget(widget_3);

        colorLlum = new QPushButton(MyForm);
        colorLlum->setObjectName(QString::fromUtf8("colorLlum"));

        verticalLayout->addWidget(colorLlum);

        label_4 = new QLabel(MyForm);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        solSlider = new QSlider(MyForm);
        solSlider->setObjectName(QString::fromUtf8("solSlider"));
        solSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(solSlider);

        nocturn = new QCheckBox(MyForm);
        nocturn->setObjectName(QString::fromUtf8("nocturn"));

        verticalLayout->addWidget(nocturn);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushButton = new QPushButton(MyForm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(pushButton);


        horizontalLayout->addLayout(verticalLayout);

        horizontalLayout->setStretch(0, 1);

        retranslateUi(MyForm);
        QObject::connect(pushButton, SIGNAL(clicked()), MyForm, SLOT(close()));

        QMetaObject::connectSlotsByName(MyForm);
    } // setupUi

    void retranslateUi(QWidget *MyForm)
    {
        MyForm->setWindowTitle(QCoreApplication::translate("MyForm", "IDI-Lab", nullptr));
        startGame->setText(QCoreApplication::translate("MyForm", "Start Game", nullptr));
        monedes->setText(QCoreApplication::translate("MyForm", "0/10 Monedes", nullptr));
        label->setText(QCoreApplication::translate("MyForm", "PSI", nullptr));
        label_2->setText(QCoreApplication::translate("MyForm", "Theta", nullptr));
        label_3->setText(QCoreApplication::translate("MyForm", "Zoom", nullptr));
        camaraGen->setText(QCoreApplication::translate("MyForm", "C\303\240mara General", nullptr));
        primPersona->setText(QCoreApplication::translate("MyForm", "Primera Persona", nullptr));
        rotMonedes->setText(QCoreApplication::translate("MyForm", "Monedes rotan", nullptr));
        estMonedes->setText(QCoreApplication::translate("MyForm", "Monedes est\303\240tiques", nullptr));
        colorLlum->setText(QCoreApplication::translate("MyForm", "Color de la Llum Principal", nullptr));
        label_4->setText(QCoreApplication::translate("MyForm", "Sol", nullptr));
        nocturn->setText(QCoreApplication::translate("MyForm", "Mode Nocturn", nullptr));
        pushButton->setText(QCoreApplication::translate("MyForm", "&Sortir", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyForm: public Ui_MyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYFORM_H
