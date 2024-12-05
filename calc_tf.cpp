
#include "calc_tf.h"
#include "ui_calc_tf.h"
#include <cmath>


CalcTF::CalcTF(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::CalcTF) {
    ui->setupUi(this);
    ui->lb_thck->setHidden(!calc_freq_);
    ui->le_thck->setHidden(!calc_freq_);
    ui->lb_freq_range->setHidden(!calc_freq_);
    ui->cb_freq_range->setHidden(!calc_freq_);
}

CalcTF::~CalcTF() {
    delete ui;
}

void CalcTF::on_btn_calc_clicked() {
    calcFunction();
}


double CalcTF::deriCalcThickness(double f_c, double d_m, double matl_z, double f_q) const {
    double term1 = (n_q * d_q / (pi * d_m * f_c * f_c * matl_z)) * atan(matl_z * tan(pi * (f_q - f_c) / f_q));
    double term2 = (n_q * d_q / (pi * d_m * f_c * matl_z)) * matl_z * (1 / cos(pi * (f_q - f_c) / f_q)) * (-pi / f_q);
    return term1 + term2;
}

double CalcTF::calcThickness(double f_c, double d_m, double matl_z, double f_q, double thck) const {
    return (n_q * d_q / (pi * d_m * f_c * matl_z)) * atan(matl_z * tan(pi * (f_q - f_c) / f_q)) - thck;
}

double CalcTF::newtonRaphson(double initial_guess, double d_m,  double matl_z, double f_q, double thck, double epsilon) const {
    double F_c = initial_guess;
    double f_F_c = calcThickness(F_c, d_m, matl_z, f_q, thck);
    double df_F_c = deriCalcThickness(F_c, d_m, matl_z, f_q);
    while (fabs(f_F_c) > epsilon) {
        F_c = F_c - f_F_c / df_F_c;
        f_F_c = calcThickness(F_c, d_m, matl_z, f_q, thck);
        df_F_c = deriCalcThickness(F_c, d_m, matl_z, f_q);
    }
    return F_c;
}

void CalcTF::calcFunction() const {
    bool ok;
    // xtal start frequency
    double f_q = ui->le_freq_start->text().toDouble(&ok);
    if(!ok) {
        errMsg(u8"频率", u8"起始频率输入格式错误。");
        return;
    }
    // material z
    double matl_z = ui->le_matl_z->text().toDouble(&ok);
    if(!ok) {
        errMsg(u8"Z-Ratio", u8"Z-Ratio输入格式错误。");
        return;
    }
    // material density
    double matl_d = ui->le_matl_d->text().toDouble(&ok);
    if(!ok) {
        errMsg(u8"密度", u8"材料密度输入格式错误。");
        return;
    }
    if(calc_freq_) {
        // input thickness
        double thck = ui->le_thck->text().toDouble(&ok);
        if(!ok) {
            errMsg(u8"厚度", u8"厚度输入错误。");
            return;
        }
        if(thck < 10) {
            QMessageBox::information(nullptr, u8"厚度参数", u8"厚度输入格式错误，需要大于10的值");
            return;
        }
        // calc frequency stop
        double f_c_calc = newtonRaphson(5000000, matl_d, matl_z, f_q, thck);
        ui->le_freq_stop->setText(QString::number(f_c_calc, 'f', 3));
        double life = (f_q - f_c_calc ) / cyg_range_ * 100;
        QString freq_text = u8"频率: \t" +  QString::number(f_c_calc, 'f', 3) + u8"\tHz";
        QString life_text = u8"Life: \t" +  QString::number(life, 'f', 3) + u8"\t\t%";
        ui->lbl_result->setText(freq_text + "\n" + life_text);
        return;
    }
    // time span
    double acq_intvl = ui->le_meas_itl->text().toDouble(&ok);
    if(!ok || acq_intvl < 10) {
        errMsg(u8"间隔", u8"间隔输入格式错误。\n间隔时间过短，需要设置为10ms以上。");
        return;
    }
    // xtal stop frequency
    double f_c = ui->le_freq_stop->text().toDouble(&ok);
    if(!ok) {
        errMsg(u8"频率", u8"中止频率输入格式错误。");
        return;
    }
    if(f_c == f_q || f_q < f_c) {
        QMessageBox::information(nullptr, u8"频率", u8"频率输入格式错误。\n频率只不能相同且中止频率需要小于起始频率。");
        return;
    }
    double thck = calcThickness(f_c, matl_d, matl_z, f_q);
    // thickness text, include unit
    QString text_thickness = u8"厚度: \t" +  QString::number(thck, 'f', 3) + u8"\tÅ";
    // rate text, include unit
    QString text_rate = u8"速率: \t" + QString::number(thck * 1000 / acq_intvl, 'f', 3) + u8"\tÅ/s";
    ui->lbl_result->setText(text_thickness + "\n" + text_rate);
}

void CalcTF::errMsg(const QString& title, const QString& msg) const {
    QMessageBox::information(nullptr, title, msg);
}


void CalcTF::on_cb_method_currentIndexChanged(int index) {
    calc_freq_ = index;
    ui->le_freq_stop->setHidden(calc_freq_);
    ui->le_meas_itl->setHidden(calc_freq_);
    ui->lb_f_c->setHidden(calc_freq_);
    ui->lb_meas_itl->setHidden(calc_freq_);
    ui->lb_thck->setHidden(!calc_freq_);
    ui->le_thck->setHidden(!calc_freq_);
    ui->lb_freq_range->setHidden(!calc_freq_);
    ui->cb_freq_range->setHidden(!calc_freq_);
}


void CalcTF::on_cb_freq_range_currentIndexChanged(int index) {
    cyg_range_ = index ? 1000000 : 1500000;
}

