
#include "calc_tf.h"
#include "ui_calc_tf.h"


CalcTF::CalcTF(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::CalcTF) {
    ui->setupUi(this);
//    ui->label_5->setHidden(true);
//    ui->le_meas_itl->setHidden(true);
}

CalcTF::~CalcTF() {
    delete ui;
}



void CalcTF::on_btn_calc_clicked() {
    double f_c = ui->le_freq_stop->text().toDouble();
    double f_q = ui->le_freq_start->text().toDouble();
    double matl_z = ui->le_matl_z->text().toDouble();
    double matl_d = ui->le_matl_d->text().toDouble();
    double acq_intvl = ui->le_meas_itl->text().toDouble();
    if(!f_c || !f_q || !matl_d || !matl_z || !acq_intvl) {
        return;
    }
    ui->lbl_result->clear();
    double val_frnt = (n_q * d_q) / (pi * matl_d * f_c * matl_z);
    double val_back = atan(matl_z * tan(pi * ((f_q - f_c) / f_q)));
    double thickness = val_frnt * val_back;
    QString text_thickness = "Thickness: \t" +  QString::number(thickness, 'f', 3) + u8"\tÅ";
    QString text_rate = "Rate: \t\t" + QString::number(thickness * 1000 / acq_intvl, 'f', 3) + u8"\tÅ/s";
    ui->lbl_result->setText(text_thickness + "\n" + text_rate);
}

//double CalcTF::calc_co_part(double f_co, double f_q, double matl_z) {
//    if(!f_co || !f_q || !matl_z) {
//        return 0;
//    }
//    return (1 / f_co) * atan(matl_z * tan(pi * f_co * f_q));
//}

//double CalcTF::calc_c_part(double f_c, double f_q, double matl_z) {
//    if(!f_c || !f_q || !matl_z) {
//        return 0;
//    }
//    return 0;
//}

