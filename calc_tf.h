
#ifndef CALCTF_H
#define CALCTF_H

#include <QMainWindow>
#include <QDebug>
#include <cmath>



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

//    double calc_co_part(double f_co = 0, double f_q = 0, double matl_z = 0);
//    double calc_c_part(double f_c = 0, double f_q = 0, double matl_z = 0);

    // pi value
    const double pi = 3.1415926;
    // crystal density
    const double d_q = 2.648;
    // crystal constant
    const double n_q = 1.668e13;
};

#endif // CALCTF_H
