
#ifndef CALCTF_H
#define CALCTF_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui {
    class CalcTF;
}
QT_END_NAMESPACE

class CalcTF : public QMainWindow

{
    Q_OBJECT

  public:
    CalcTF(QWidget* parent = nullptr);
    ~CalcTF();

  private slots:
    void on_btn_calc_clicked();

  private:
    Ui::CalcTF* ui;

    void set_res_text();
    // pi value
    const double pi = 3.1415926;
    // xtal density
    const double d_q = 2.648;
    // xtal constant
    const double n_q = 1.668e13;


};

#endif // CALCTF_H
