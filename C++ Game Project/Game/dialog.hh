#ifndef DIALOG_HH
#define DIALOG_HH
#include "mainwindow.hh"
#include "engine.hh"

#include <QDialog>
#include <QPushButton>
#include <QIcon>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

signals: 
    void playerIconValue(int iconNum);
    void setNamePbtnClicked (QString name_);


public slots:
    void on_airplanePbtn_clicked();
    void on_planePbtn_clicked();
    void on_copterPbtn_clicked();

private slots:

    void on_setNamePbtn_clicked();



private:
    Ui::Dialog *ui;
    int iconNum_;
    QString name_;

};

#endif // DIALOG_HH
