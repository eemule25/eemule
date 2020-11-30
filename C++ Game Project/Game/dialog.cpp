#include "dialog.hh"
#include "ui_dialog.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)


{
   ui->setupUi(this);

}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_copterPbtn_clicked()
{
    iconNum_ = 1;
    emit (playerIconValue(iconNum_));
}

void Dialog::on_planePbtn_clicked()
{
    iconNum_ = 2;
    emit (playerIconValue(iconNum_));
}

void Dialog::on_airplanePbtn_clicked()
{
    iconNum_ = 3;
    emit (playerIconValue(iconNum_));
}


void Dialog::on_setNamePbtn_clicked()
{
    name_ = ui->lineEdit->text();
    ui->lineEdit->setDisabled(true);
    emit(setNamePbtnClicked(name_));
}


