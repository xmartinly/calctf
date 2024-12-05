
#ifndef CALCTF_H
#define CALCTF_H

#include <QMainWindow>
#include <QMessageBox>


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

    // void on_btn_calc_rev_clicked();

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
    //ic6 cygnus2 frequency range
    double cyg_range_ = 1500000;
    bool calc_freq_ = false;
    double deriCalcThickness(double f_c, double d_m, double matl_z, double f_q)const;
    double calcThickness(double f_c, double d_m, double matl_z, double f_q, double thck = 0)const;
    double newtonRaphson(double initial_guess, double d_m,  double matl_z, double f_q, double thck, double epsilon = 1e-6) const;

    void calcFunction() const;



};

#endif // CALCTF_H
