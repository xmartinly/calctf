
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

//    void on_le_freq_start_textChanged(const QString& arg1);

//    void on_le_freq_stop_textChanged(const QString& arg1);


  private:
    Ui::CalcTF* ui;

    void set_res_text();
    // pi value
    const double pi = 3.1415926;
    // xtal density
    const double d_q = 2.648;
    // xtal constant
    const double n_q = 1.668e13;

//    QString s_Freq_c = "";
//    QString s_Freq_q = "";
};

#endif // CALCTF_H
