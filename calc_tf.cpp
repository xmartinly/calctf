
#include "calc_tf.h"
#include "ui_calc_tf.h"


CalcTF::CalcTF(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::CalcTF) {
    ui->setupUi(this);
}

CalcTF::~CalcTF() {
    delete ui;
}



void CalcTF::on_btn_calc_clicked() {
    // xtal stop frequency
    double f_c = ui->le_freq_stop->text().toDouble();
    // xtal start frequency
    double f_q = ui->le_freq_start->text().toDouble();
    // material z
    double matl_z = ui->le_matl_z->text().toDouble();
    // material density
    double matl_d = ui->le_matl_d->text().toDouble();
    // time span
    double acq_intvl = ui->le_meas_itl->text().toDouble();
    if(!f_c || !f_q || !matl_d || !matl_z || !acq_intvl) {
        return;
    }
    ui->lbl_result->clear();
//    s_Freq_q = "";
//    s_Freq_c = "";
    // part1 for normal calculate
    double val_frnt = (n_q * d_q) / (pi * matl_d * f_c * matl_z);
    // part2 for atan calculate
    double val_back = atan(matl_z * tan(pi * ((f_q - f_c) / f_q)));
    // thickness value
    double thickness = val_frnt * val_back;
    // thickness text, include unit
    QString text_thickness = "Thickness: \t" +  QString::number(thickness, 'f', 3) + u8"\tÅ";
    // rate text, include unit
    QString text_rate = "Rate: \t\t" + QString::number(thickness * 1000 / acq_intvl, 'f', 3) + u8"\tÅ/s";
    ui->lbl_result->setText(text_thickness + "\n" + text_rate);
}


//void CalcTF::on_le_freq_start_textChanged(const QString& arg1) {
//    double f_q = arg1.toDouble();
//    s_Freq_q = ui->lb_f_q->text() + ":\t" + QString::number(f_q / 1000000, 'f', 3) + " MHz";
//    set_res_text();
//}


//void CalcTF::on_le_freq_stop_textChanged(const QString& arg1) {
//    double f_c = arg1.toDouble();
//    s_Freq_c = ui->lb_f_c->text()  + ":\t" + QString::number(f_c / 1000000, 'f', 3) + " MHz";
//    set_res_text();
//}

//void CalcTF::set_res_text() {
//    ui->lbl_result->clear();
//    ui->lbl_result->setText(s_Freq_q + "\n" + s_Freq_c);
//}

