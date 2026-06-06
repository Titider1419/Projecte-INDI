#include "MyForm.h"
#include <QMessageBox>
#include <QPushButton>
#include <QColorDialog>
#include <QColor>

MyForm::MyForm (QWidget* parent) : QWidget(parent)
{
  ui.setupUi(this);

  ui.psiSlider->setMinimum(-1000);
  ui.psiSlider->setMaximum(1000);
  ui.psiSlider->setSingleStep(1);
  ui.psiSlider->setPageStep(10);
  ui.psiSlider->setValue(0);

  ui.thetaSlider->setMinimum(-1000);
  ui.thetaSlider->setMaximum(1000);
  ui.thetaSlider->setSingleStep(1);
  ui.thetaSlider->setPageStep(10);
  ui.thetaSlider->setValue(0);

  ui.zoomSlider->setMinimum(0);
  ui.zoomSlider->setMaximum(1000);
  ui.zoomSlider->setSingleStep(1);
  ui.zoomSlider->setPageStep(10);
  ui.zoomSlider->setValue(500);

  ui.camaraGen->setChecked(true);
  ui.rotMonedes->setChecked(true);

  ui.solSlider->setMinimum(0);
  ui.solSlider->setMaximum(1000);
  ui.solSlider->setSingleStep(1);
  ui.solSlider->setPageStep(10);
  ui.solSlider->setValue(500);

  connect(ui.startGame, &QPushButton::clicked, ui.widget, &MyGLWidget::startGame);
  connect(ui.widget, &MyGLWidget::comptadorMonedes, this, &MyForm::actualitzarMonedes);
  connect(ui.widget, &MyGLWidget::guanyat, this, &MyForm::jocGuanyat);
  connect(ui.widget, &MyGLWidget::perdut, this, &MyForm::jocPerdut);
  connect(ui.psiSlider, &QSlider::valueChanged, ui.widget, &MyGLWidget::psiObtingut);
  connect(ui.widget, &MyGLWidget::psiEnviat, ui.psiSlider, &QSlider::setValue);
  connect(ui.thetaSlider, &QSlider::valueChanged, ui.widget, &MyGLWidget::thetaObtingut);
  connect(ui.widget, &MyGLWidget::thetaEnviat, ui.thetaSlider, &QSlider::setValue);
  connect(ui.zoomSlider, &QSlider::valueChanged, ui.widget, &MyGLWidget::zoomObtingut);
  connect(ui.widget, &MyGLWidget::zoomEnviat, ui.zoomSlider, &QSlider::setValue);
  connect(ui.camaraGen, &QRadioButton::clicked, ui.widget, &MyGLWidget::camaraGen);
  connect(ui.primPersona, &QRadioButton::clicked, ui.widget, &MyGLWidget::primeraPers);
  connect(ui.widget, &MyGLWidget::alternarCamara, this, [this](bool primeraPers){
        if (primeraPers) ui.primPersona->setChecked(true);
        else ui.camaraGen->setChecked(true);
  });
  connect(ui.rotMonedes, &QRadioButton::clicked, ui.widget, &MyGLWidget::rotMonedes);
  connect(ui.estMonedes, &QRadioButton::clicked, ui.widget, &MyGLWidget::estMonedes);

  connect(ui.widget, &MyGLWidget::alternarRotacioMoneda, this, [this](bool timerActiu){
      if (timerActiu) ui.rotMonedes->setChecked(true);
      else ui.estMonedes->setChecked(true);
  });
  connect(ui.colorLlum, &QPushButton::clicked, this, &MyForm::colorLlum);
  connect(ui.solSlider, &QSlider::valueChanged, ui.widget, &MyGLWidget::thetaFocusObtingut);
  connect(ui.widget, &MyGLWidget::thetaFocusEnviat, ui.solSlider, &QSlider::setValue);
}

void MyForm::actualitzarMonedes(int actuals, int totals){
    ui.monedes->setText(QString("%1/%2 coins").arg(actuals).arg(totals));
}

void MyForm::jocGuanyat(){
    QMessageBox msgBox;
    msgBox.setWindowTitle("¡Victoria!");
    msgBox.setText("Felicitats! Has aconseguit escapar.");
    msgBox.setInformativeText("Qué vols fer ara?");
    msgBox.setIcon(QMessageBox::Question);
    QPushButton *btnReiniciar = msgBox.addButton("Start Game", QMessageBox::ActionRole);
    QPushButton *btnSalir = msgBox.addButton("Sortir", QMessageBox::RejectRole);
    msgBox.exec();
    if (msgBox.clickedButton() == btnReiniciar)
    {
        ui.widget->reiniciar();
    }
    else if (msgBox.clickedButton() == btnSalir)
    {
        this->close();
    }
}

void MyForm::jocPerdut(){
    QMessageBox msgBox;
    msgBox.setWindowTitle("¡Has perdut!");
    msgBox.setText("La pròxima vegada ho aconseguiràs.");
    msgBox.setInformativeText("Qué vols fer ara?");
    msgBox.setIcon(QMessageBox::Question);
    QPushButton *btnReiniciar = msgBox.addButton("Start Game", QMessageBox::ActionRole);
    QPushButton *btnSalir = msgBox.addButton("Sortir", QMessageBox::RejectRole);
    msgBox.exec();
    if (msgBox.clickedButton() == btnReiniciar)
    {
        ui.widget->reiniciar();
    }
    else if (msgBox.clickedButton() == btnSalir)
    {
        this->close();
    }
}

void MyForm::colorLlum()
{
    QColor colorTriat = QColorDialog::getColor(Qt::white, this, "Escull el color del focus");


    if (colorTriat.isValid())
    {
        float r = colorTriat.redF();
        float g = colorTriat.greenF();
        float b = colorTriat.blueF();

        glm::vec3 colorFormatOpenGL(r, g, b);
        ui.widget->canviarColorFocus(colorFormatOpenGL);
    }
}
