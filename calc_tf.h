
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

    void on_cb_method_currentIndexChanged(int index);

    void on_cb_freq_range_currentIndexChanged(int index);

  private:
    Ui::CalcTF* ui;

    // pi value
    const double pi = 3.1415926;
    // xtal density
    const double d_q = 2.648;
    // xtal constant
    const double n_q = 1.668e13;
    // ic6 cygnus2 frequency range
    double cyg_range_ = 1500000;
    // initial guess for frequency stop.
    double initial_guess_ = 0;
    // is calculate frequncy shift
    bool calc_freq_ = false;

  private:
    // derivative function for calculate thickness
    double deriCalcThickness(double f_c, double d_m, double matl_z, double f_q)const;
    // calculate thickness
    double calcThickness(double f_c, double d_m, double matl_z, double f_q, double thck = 0)const;
    // Newton Raphson function for calculate frequency stop
    double newtonRaphson(double d_m,  double matl_z, double f_q, double thck, double epsilon = 1e-6) const;
    // calculate function after button click
    void calcFunction() const;
    // error message when input is wrong
    void errMsg(const QString& title, const QString& msg) const;

};

#endif // CALCTF_H
