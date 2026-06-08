#include "ui_MyForm.h"

class MyForm : public QWidget
{
  Q_OBJECT

  public:
    MyForm (QWidget *parent=0);

  public slots:
    void actualitzarMonedes(int actuals, int totals);
    void jocGuanyat();
    void jocPerdut();
    void obrirDialegColor();

private:
    Ui::MyForm ui;
};
