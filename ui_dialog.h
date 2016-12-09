/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGraphicsView *graphicsView_Depth;
    QLabel *label_depth_2;
    QLabel *label_depth_3;
    QLabel *label_depth_4;
    QLabel *label_depth_5;
    QPushButton *pushButton_Measure;
    QPushButton *pushButton_Exit;
    QLineEdit *lineEdit_Frames;
    QLineEdit *lineEdit_X;
    QLineEdit *lineEdit_Y;
    QLineEdit *lineEdit_Z;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton_Install;
    QLabel *label_3;
    QPushButton *pushButton_UpdateBg;
    QPushButton *pushButton_Start;
    QFrame *line_3;
    QLabel *label_4;
    QLineEdit *lineEdit_IP;
    QLineEdit *lineEdit_Port;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_depth_6;
    QLineEdit *lineEdit_Boundingvol;
    QLineEdit *lineEdit_IntegeralVol;
    QLabel *label_7;
    QLabel *label_depth_7;
    QFrame *line_4;
    QFrame *line;
    QLabel *label_depth_8;
    QLineEdit *lineEdit_Timestamp;
    QLineEdit *lineEdit_Type;
    QLabel *label_depth_9;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(892, 685);
        graphicsView_Depth = new QGraphicsView(Dialog);
        graphicsView_Depth->setObjectName(QStringLiteral("graphicsView_Depth"));
        graphicsView_Depth->setGeometry(QRect(220, 70, 646, 486));
        label_depth_2 = new QLabel(Dialog);
        label_depth_2->setObjectName(QStringLiteral("label_depth_2"));
        label_depth_2->setGeometry(QRect(220, 30, 91, 31));
        QFont font;
        font.setPointSize(20);
        label_depth_2->setFont(font);
        label_depth_3 = new QLabel(Dialog);
        label_depth_3->setObjectName(QStringLiteral("label_depth_3"));
        label_depth_3->setGeometry(QRect(30, 290, 21, 21));
        label_depth_3->setFont(font);
        label_depth_4 = new QLabel(Dialog);
        label_depth_4->setObjectName(QStringLiteral("label_depth_4"));
        label_depth_4->setGeometry(QRect(30, 340, 61, 21));
        label_depth_4->setFont(font);
        label_depth_5 = new QLabel(Dialog);
        label_depth_5->setObjectName(QStringLiteral("label_depth_5"));
        label_depth_5->setGeometry(QRect(30, 390, 61, 21));
        label_depth_5->setFont(font);
        pushButton_Measure = new QPushButton(Dialog);
        pushButton_Measure->setObjectName(QStringLiteral("pushButton_Measure"));
        pushButton_Measure->setEnabled(false);
        pushButton_Measure->setGeometry(QRect(710, 500, 151, 51));
        pushButton_Measure->setFont(font);
        pushButton_Measure->setFlat(false);
        pushButton_Exit = new QPushButton(Dialog);
        pushButton_Exit->setObjectName(QStringLiteral("pushButton_Exit"));
        pushButton_Exit->setGeometry(QRect(720, 600, 151, 51));
        pushButton_Exit->setFont(font);
        lineEdit_Frames = new QLineEdit(Dialog);
        lineEdit_Frames->setObjectName(QStringLiteral("lineEdit_Frames"));
        lineEdit_Frames->setEnabled(false);
        lineEdit_Frames->setGeometry(QRect(810, 40, 51, 20));
        lineEdit_Frames->setMouseTracking(false);
        lineEdit_Frames->setFocusPolicy(Qt::NoFocus);
        lineEdit_Frames->setLayoutDirection(Qt::LeftToRight);
        lineEdit_Frames->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_Frames->setReadOnly(true);
        lineEdit_X = new QLineEdit(Dialog);
        lineEdit_X->setObjectName(QStringLiteral("lineEdit_X"));
        lineEdit_X->setEnabled(false);
        lineEdit_X->setGeometry(QRect(70, 290, 111, 27));
        lineEdit_Y = new QLineEdit(Dialog);
        lineEdit_Y->setObjectName(QStringLiteral("lineEdit_Y"));
        lineEdit_Y->setEnabled(false);
        lineEdit_Y->setGeometry(QRect(70, 340, 111, 27));
        lineEdit_Z = new QLineEdit(Dialog);
        lineEdit_Z->setObjectName(QStringLiteral("lineEdit_Z"));
        lineEdit_Z->setEnabled(false);
        lineEdit_Z->setGeometry(QRect(70, 390, 111, 27));
        label = new QLabel(Dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(180, 300, 31, 17));
        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(180, 350, 31, 17));
        pushButton_Install = new QPushButton(Dialog);
        pushButton_Install->setObjectName(QStringLiteral("pushButton_Install"));
        pushButton_Install->setGeometry(QRect(20, 600, 151, 51));
        pushButton_Install->setFont(font);
        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(180, 400, 31, 17));
        pushButton_UpdateBg = new QPushButton(Dialog);
        pushButton_UpdateBg->setObjectName(QStringLiteral("pushButton_UpdateBg"));
        pushButton_UpdateBg->setGeometry(QRect(380, 600, 151, 51));
        pushButton_UpdateBg->setFont(font);
        pushButton_Start = new QPushButton(Dialog);
        pushButton_Start->setObjectName(QStringLiteral("pushButton_Start"));
        pushButton_Start->setGeometry(QRect(210, 600, 151, 51));
        pushButton_Start->setFont(font);
        line_3 = new QFrame(Dialog);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(0, 560, 901, 20));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(Dialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 80, 31, 16));
        QFont font1;
        font1.setPointSize(14);
        label_4->setFont(font1);
        lineEdit_IP = new QLineEdit(Dialog);
        lineEdit_IP->setObjectName(QStringLiteral("lineEdit_IP"));
        lineEdit_IP->setGeometry(QRect(60, 70, 131, 31));
        QFont font2;
        font2.setPointSize(13);
        lineEdit_IP->setFont(font2);
        lineEdit_Port = new QLineEdit(Dialog);
        lineEdit_Port->setObjectName(QStringLiteral("lineEdit_Port"));
        lineEdit_Port->setGeometry(QRect(60, 120, 131, 31));
        lineEdit_Port->setFont(font2);
        label_5 = new QLabel(Dialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 130, 41, 16));
        label_5->setFont(font1);
        label_6 = new QLabel(Dialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(180, 460, 41, 17));
        label_depth_6 = new QLabel(Dialog);
        label_depth_6->setObjectName(QStringLiteral("label_depth_6"));
        label_depth_6->setGeometry(QRect(10, 450, 81, 21));
        QFont font3;
        font3.setPointSize(11);
        label_depth_6->setFont(font3);
        lineEdit_Boundingvol = new QLineEdit(Dialog);
        lineEdit_Boundingvol->setObjectName(QStringLiteral("lineEdit_Boundingvol"));
        lineEdit_Boundingvol->setEnabled(false);
        lineEdit_Boundingvol->setGeometry(QRect(70, 450, 111, 27));
        lineEdit_IntegeralVol = new QLineEdit(Dialog);
        lineEdit_IntegeralVol->setObjectName(QStringLiteral("lineEdit_IntegeralVol"));
        lineEdit_IntegeralVol->setEnabled(false);
        lineEdit_IntegeralVol->setGeometry(QRect(70, 510, 111, 27));
        label_7 = new QLabel(Dialog);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(180, 520, 41, 17));
        label_depth_7 = new QLabel(Dialog);
        label_depth_7->setObjectName(QStringLiteral("label_depth_7"));
        label_depth_7->setGeometry(QRect(10, 510, 81, 21));
        label_depth_7->setFont(font3);
        line_4 = new QFrame(Dialog);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(0, 160, 221, 20));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line = new QFrame(Dialog);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(180, 570, 21, 121));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        label_depth_8 = new QLabel(Dialog);
        label_depth_8->setObjectName(QStringLiteral("label_depth_8"));
        label_depth_8->setGeometry(QRect(20, 190, 51, 21));
        label_depth_8->setFont(font3);
        lineEdit_Timestamp = new QLineEdit(Dialog);
        lineEdit_Timestamp->setObjectName(QStringLiteral("lineEdit_Timestamp"));
        lineEdit_Timestamp->setEnabled(false);
        lineEdit_Timestamp->setGeometry(QRect(70, 190, 111, 27));
        lineEdit_Type = new QLineEdit(Dialog);
        lineEdit_Type->setObjectName(QStringLiteral("lineEdit_Type"));
        lineEdit_Type->setEnabled(false);
        lineEdit_Type->setGeometry(QRect(70, 240, 111, 27));
        label_depth_9 = new QLabel(Dialog);
        label_depth_9->setObjectName(QStringLiteral("label_depth_9"));
        label_depth_9->setGeometry(QRect(20, 240, 51, 21));
        label_depth_9->setFont(font1);
        pushButton_Measure->raise();
        graphicsView_Depth->raise();
        label_depth_2->raise();
        label_depth_3->raise();
        label_depth_4->raise();
        label_depth_5->raise();
        pushButton_Exit->raise();
        lineEdit_Frames->raise();
        lineEdit_X->raise();
        lineEdit_Y->raise();
        lineEdit_Z->raise();
        label->raise();
        label_2->raise();
        pushButton_Install->raise();
        label_3->raise();
        pushButton_UpdateBg->raise();
        pushButton_Start->raise();
        line_3->raise();
        label_4->raise();
        lineEdit_IP->raise();
        lineEdit_Port->raise();
        label_5->raise();
        label_6->raise();
        label_depth_6->raise();
        lineEdit_Boundingvol->raise();
        lineEdit_IntegeralVol->raise();
        label_7->raise();
        label_depth_7->raise();
        line_4->raise();
        line->raise();
        label_depth_8->raise();
        lineEdit_Timestamp->raise();
        lineEdit_Type->raise();
        label_depth_9->raise();

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "\345\233\276\346\274\276\347\247\221\346\212\200 - \346\234\252\350\277\236\346\216\245", 0));
        label_depth_2->setText(QApplication::translate("Dialog", "\346\267\261\345\272\246\345\233\276", 0));
        label_depth_3->setText(QApplication::translate("Dialog", "X", 0));
        label_depth_4->setText(QApplication::translate("Dialog", "Y", 0));
        label_depth_5->setText(QApplication::translate("Dialog", "Z", 0));
        pushButton_Measure->setText(QApplication::translate("Dialog", "\346\243\200\346\265\213", 0));
        pushButton_Exit->setText(QApplication::translate("Dialog", "\351\200\200\345\207\272", 0));
        lineEdit_Frames->setText(QApplication::translate("Dialog", "0", 0));
        label->setText(QApplication::translate("Dialog", "mm", 0));
        label_2->setText(QApplication::translate("Dialog", "mm", 0));
        pushButton_Install->setText(QApplication::translate("Dialog", "\345\274\200\345\247\213\345\256\211\350\243\205", 0));
        label_3->setText(QApplication::translate("Dialog", "mm", 0));
        pushButton_UpdateBg->setText(QApplication::translate("Dialog", "\346\233\264\346\226\260\350\203\214\346\231\257", 0));
        pushButton_Start->setText(QApplication::translate("Dialog", "\345\274\200\345\247\213", 0));
        label_4->setText(QApplication::translate("Dialog", "IP", 0));
        lineEdit_IP->setText(QApplication::translate("Dialog", "192.168.1.80", 0));
        lineEdit_Port->setText(QApplication::translate("Dialog", "7000", 0));
        label_5->setText(QApplication::translate("Dialog", "\347\253\257\345\217\243", 0));
        label_6->setText(QApplication::translate("Dialog", "mm3", 0));
        label_depth_6->setText(QApplication::translate("Dialog", "\345\244\226\346\216\245\344\275\223\347\247\257", 0));
        label_7->setText(QApplication::translate("Dialog", "mm3", 0));
        label_depth_7->setText(QApplication::translate("Dialog", "\347\247\257\345\210\206\344\275\223\347\247\257", 0));
        label_depth_8->setText(QApplication::translate("Dialog", "\346\227\266\351\227\264\346\210\263", 0));
        label_depth_9->setText(QApplication::translate("Dialog", "\347\261\273\345\236\213", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
