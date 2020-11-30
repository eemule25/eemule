/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QPushButton *start_button;
    QPushButton *pause_button;
    QLabel *label;
    QLCDNumber *lcd_number_sec;
    QLabel *label_2;
    QLabel *label_3;
    QLCDNumber *score_number;
    QLabel *label_4;
    QLCDNumber *level_display;
    QOpenGLWidget *the_end_widget;
    QLabel *the_end_text;
    QLCDNumber *lcd_number_min;
    QLabel *label_5;
    QPushButton *reset_button;
    QLabel *label_6;
    QPushButton *player_name_button;
    QPushButton *leaderboard_push_button;
    QTextBrowser *text_browser;
    QPushButton *close_push_button;
    QLineEdit *player_name_line_edit;
    QLabel *label_7;
    QPushButton *easy_level_button;
    QPushButton *normal_level_button;
    QPushButton *hard_level_button;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(685, 777);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(19, 23, 24, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(29, 35, 37, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(24, 29, 30, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(9, 11, 12, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(13, 15, 16, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush6(QColor(0, 0, 0, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        QBrush brush7(QColor(41, 58, 76, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush7);
        QBrush brush8(QColor(138, 226, 52, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush8);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush4);
        QBrush brush9(QColor(255, 255, 220, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush9);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush9);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush9);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        MainWindow->setPalette(palette);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(130, 411, 171, 71));
        start_button = new QPushButton(centralWidget);
        start_button->setObjectName(QStringLiteral("start_button"));
        start_button->setGeometry(QRect(520, 150, 111, 41));
        QPalette palette1;
        QBrush brush10(QColor(115, 210, 22, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush10);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush10);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        start_button->setPalette(palette1);
        QFont font;
        font.setPointSize(25);
        start_button->setFont(font);
        pause_button = new QPushButton(centralWidget);
        pause_button->setObjectName(QStringLiteral("pause_button"));
        pause_button->setGeometry(QRect(520, 210, 111, 31));
        QFont font1;
        font1.setPointSize(15);
        pause_button->setFont(font1);
        pause_button->setFocusPolicy(Qt::NoFocus);
        pause_button->setAutoDefault(false);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 30, 311, 81));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        label->setPalette(palette2);
        QFont font2;
        font2.setFamily(QStringLiteral("Open Sans"));
        font2.setPointSize(60);
        font2.setBold(true);
        font2.setItalic(false);
        font2.setUnderline(true);
        font2.setWeight(75);
        font2.setStrikeOut(false);
        font2.setKerning(true);
        label->setFont(font2);
        label->setFrameShape(QFrame::WinPanel);
        label->setFrameShadow(QFrame::Sunken);
        label->setLineWidth(5);
        label->setMidLineWidth(0);
        lcd_number_sec = new QLCDNumber(centralWidget);
        lcd_number_sec->setObjectName(QStringLiteral("lcd_number_sec"));
        lcd_number_sec->setGeometry(QRect(580, 350, 50, 41));
        lcd_number_sec->setSmallDecimalPoint(false);
        lcd_number_sec->setDigitCount(2);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(520, 320, 63, 20));
        label_2->setFont(font1);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(520, 400, 63, 20));
        label_3->setFont(font1);
        score_number = new QLCDNumber(centralWidget);
        score_number->setObjectName(QStringLiteral("score_number"));
        score_number->setGeometry(QRect(520, 430, 111, 41));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(520, 480, 63, 20));
        label_4->setFont(font1);
        level_display = new QLCDNumber(centralWidget);
        level_display->setObjectName(QStringLiteral("level_display"));
        level_display->setGeometry(QRect(520, 510, 111, 41));
        the_end_widget = new QOpenGLWidget(centralWidget);
        the_end_widget->setObjectName(QStringLiteral("the_end_widget"));
        the_end_widget->setGeometry(QRect(100, 220, 241, 341));
        the_end_text = new QLabel(centralWidget);
        the_end_text->setObjectName(QStringLiteral("the_end_text"));
        the_end_text->setGeometry(QRect(110, 310, 301, 131));
        QPalette palette3;
        QBrush brush11(QColor(204, 0, 0, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush11);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush11);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        the_end_text->setPalette(palette3);
        QFont font3;
        font3.setPointSize(30);
        the_end_text->setFont(font3);
        lcd_number_min = new QLCDNumber(centralWidget);
        lcd_number_min->setObjectName(QStringLiteral("lcd_number_min"));
        lcd_number_min->setGeometry(QRect(520, 350, 50, 41));
        lcd_number_min->setDigitCount(2);
        lcd_number_min->setMode(QLCDNumber::Dec);
        lcd_number_min->setSegmentStyle(QLCDNumber::Filled);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(570, 350, 16, 41));
        QFont font4;
        font4.setPointSize(22);
        label_5->setFont(font4);
        reset_button = new QPushButton(centralWidget);
        reset_button->setObjectName(QStringLiteral("reset_button"));
        reset_button->setGeometry(QRect(520, 260, 111, 31));
        reset_button->setFont(font1);
        reset_button->setFocusPolicy(Qt::NoFocus);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(520, 30, 81, 20));
        label_6->setFont(font1);
        player_name_button = new QPushButton(centralWidget);
        player_name_button->setObjectName(QStringLiteral("player_name_button"));
        player_name_button->setGeometry(QRect(640, 60, 21, 31));
        player_name_button->setFocusPolicy(Qt::NoFocus);
        leaderboard_push_button = new QPushButton(centralWidget);
        leaderboard_push_button->setObjectName(QStringLiteral("leaderboard_push_button"));
        leaderboard_push_button->setGeometry(QRect(520, 570, 111, 28));
        leaderboard_push_button->setFocusPolicy(Qt::NoFocus);
        text_browser = new QTextBrowser(centralWidget);
        text_browser->setObjectName(QStringLiteral("text_browser"));
        text_browser->setGeometry(QRect(90, 190, 261, 401));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        palette4.setBrush(QPalette::Active, QPalette::Button, brush);
        palette4.setBrush(QPalette::Active, QPalette::Light, brush);
        palette4.setBrush(QPalette::Active, QPalette::Midlight, brush);
        QBrush brush12(QColor(127, 127, 127, 255));
        brush12.setStyle(Qt::SolidPattern);
        palette4.setBrush(QPalette::Active, QPalette::Dark, brush12);
        QBrush brush13(QColor(170, 170, 170, 255));
        brush13.setStyle(Qt::SolidPattern);
        palette4.setBrush(QPalette::Active, QPalette::Mid, brush13);
        palette4.setBrush(QPalette::Active, QPalette::Text, brush6);
        palette4.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette4.setBrush(QPalette::Active, QPalette::ButtonText, brush6);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush);
        palette4.setBrush(QPalette::Active, QPalette::Window, brush);
        palette4.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette4.setBrush(QPalette::Active, QPalette::AlternateBase, brush);
        palette4.setBrush(QPalette::Active, QPalette::ToolTipBase, brush9);
        palette4.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette4.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Dark, brush12);
        palette4.setBrush(QPalette::Inactive, QPalette::Mid, brush13);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush6);
        palette4.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::ButtonText, brush6);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette4.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush9);
        palette4.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush12);
        palette4.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Dark, brush12);
        palette4.setBrush(QPalette::Disabled, QPalette::Mid, brush13);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush12);
        palette4.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::ButtonText, brush12);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette4.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush9);
        palette4.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        text_browser->setPalette(palette4);
        close_push_button = new QPushButton(centralWidget);
        close_push_button->setObjectName(QStringLiteral("close_push_button"));
        close_push_button->setGeometry(QRect(180, 550, 84, 28));
        player_name_line_edit = new QLineEdit(centralWidget);
        player_name_line_edit->setObjectName(QStringLiteral("player_name_line_edit"));
        player_name_line_edit->setGeometry(QRect(520, 60, 113, 31));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        palette5.setBrush(QPalette::Active, QPalette::Button, brush);
        palette5.setBrush(QPalette::Active, QPalette::Light, brush);
        palette5.setBrush(QPalette::Active, QPalette::Midlight, brush);
        palette5.setBrush(QPalette::Active, QPalette::Dark, brush12);
        palette5.setBrush(QPalette::Active, QPalette::Mid, brush13);
        palette5.setBrush(QPalette::Active, QPalette::Text, brush6);
        palette5.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette5.setBrush(QPalette::Active, QPalette::ButtonText, brush6);
        palette5.setBrush(QPalette::Active, QPalette::Base, brush);
        palette5.setBrush(QPalette::Active, QPalette::Window, brush);
        palette5.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette5.setBrush(QPalette::Active, QPalette::AlternateBase, brush);
        palette5.setBrush(QPalette::Active, QPalette::ToolTipBase, brush9);
        palette5.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette5.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Dark, brush12);
        palette5.setBrush(QPalette::Inactive, QPalette::Mid, brush13);
        palette5.setBrush(QPalette::Inactive, QPalette::Text, brush6);
        palette5.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::ButtonText, brush6);
        palette5.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette5.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush9);
        palette5.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush12);
        palette5.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Dark, brush12);
        palette5.setBrush(QPalette::Disabled, QPalette::Mid, brush13);
        palette5.setBrush(QPalette::Disabled, QPalette::Text, brush12);
        palette5.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::ButtonText, brush12);
        palette5.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette5.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush9);
        palette5.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        player_name_line_edit->setPalette(palette5);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(70, 660, 131, 21));
        label_7->setFont(font1);
        easy_level_button = new QPushButton(centralWidget);
        easy_level_button->setObjectName(QStringLiteral("easy_level_button"));
        easy_level_button->setGeometry(QRect(220, 660, 84, 28));
        easy_level_button->setFocusPolicy(Qt::NoFocus);
        normal_level_button = new QPushButton(centralWidget);
        normal_level_button->setObjectName(QStringLiteral("normal_level_button"));
        normal_level_button->setGeometry(QRect(320, 660, 84, 28));
        normal_level_button->setFocusPolicy(Qt::NoFocus);
        hard_level_button = new QPushButton(centralWidget);
        hard_level_button->setObjectName(QStringLiteral("hard_level_button"));
        hard_level_button->setGeometry(QRect(420, 660, 84, 28));
        hard_level_button->setFocusPolicy(Qt::NoFocus);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 685, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        start_button->setText(QApplication::translate("MainWindow", "START", Q_NULLPTR));
        pause_button->setText(QApplication::translate("MainWindow", "PAUSE", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "TETRIS", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "TIME", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "SCORE", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "LEVEL", Q_NULLPTR));
        the_end_text->setText(QApplication::translate("MainWindow", "GAME OVER", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", ":", Q_NULLPTR));
        reset_button->setText(QApplication::translate("MainWindow", "RESET", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "PLAYER", Q_NULLPTR));
        player_name_button->setText(QApplication::translate("MainWindow", ">", Q_NULLPTR));
        leaderboard_push_button->setText(QApplication::translate("MainWindow", "LEADERBOARD", Q_NULLPTR));
        close_push_button->setText(QApplication::translate("MainWindow", "CLOSE", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "SELECT LEVEL", Q_NULLPTR));
        easy_level_button->setText(QApplication::translate("MainWindow", "EASY", Q_NULLPTR));
        normal_level_button->setText(QApplication::translate("MainWindow", "NORMAL", Q_NULLPTR));
        hard_level_button->setText(QApplication::translate("MainWindow", "HARD", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
