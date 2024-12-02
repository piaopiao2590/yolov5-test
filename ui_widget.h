/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *stoppB;
    QPushButton *runpB;
    QGroupBox *imageorginGB;
    QGroupBox *imageyoloGB;
    QPushButton *connectIP;
    QLineEdit *ipaddress;
    QLabel *label;
    QPushButton *disconnect;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 636);
        stoppB = new QPushButton(Widget);
        stoppB->setObjectName("stoppB");
        stoppB->setGeometry(QRect(500, 70, 93, 28));
        runpB = new QPushButton(Widget);
        runpB->setObjectName("runpB");
        runpB->setGeometry(QRect(140, 70, 93, 28));
        imageorginGB = new QGroupBox(Widget);
        imageorginGB->setObjectName("imageorginGB");
        imageorginGB->setGeometry(QRect(40, 120, 321, 351));
        imageyoloGB = new QGroupBox(Widget);
        imageyoloGB->setObjectName("imageyoloGB");
        imageyoloGB->setGeometry(QRect(410, 120, 351, 351));
        connectIP = new QPushButton(Widget);
        connectIP->setObjectName("connectIP");
        connectIP->setGeometry(QRect(400, 490, 93, 28));
        ipaddress = new QLineEdit(Widget);
        ipaddress->setObjectName("ipaddress");
        ipaddress->setGeometry(QRect(160, 490, 211, 25));
        label = new QLabel(Widget);
        label->setObjectName("label");
        label->setGeometry(QRect(70, 490, 69, 19));
        disconnect = new QPushButton(Widget);
        disconnect->setObjectName("disconnect");
        disconnect->setGeometry(QRect(550, 490, 93, 28));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        stoppB->setText(QCoreApplication::translate("Widget", "\345\201\234\346\255\242", nullptr));
        runpB->setText(QCoreApplication::translate("Widget", "\350\277\220\350\241\214", nullptr));
        imageorginGB->setTitle(QCoreApplication::translate("Widget", "\345\216\237\345\233\276\345\203\217", nullptr));
        imageyoloGB->setTitle(QCoreApplication::translate("Widget", "\350\257\206\345\210\253\345\233\276\345\203\217", nullptr));
        connectIP->setText(QCoreApplication::translate("Widget", "\350\277\236\346\216\245", nullptr));
        label->setText(QCoreApplication::translate("Widget", "ip\345\234\260\345\235\200", nullptr));
        disconnect->setText(QCoreApplication::translate("Widget", "\346\226\255\345\274\200\350\277\236\346\216\245", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
