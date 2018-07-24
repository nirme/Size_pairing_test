/********************************************************************************
** Form generated from reading UI file 'main_class.ui'
**
** Created: Thu 10. Mar 14:24:24 2011
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_CLASS_H
#define UI_MAIN_CLASS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_main_classClass
{
public:

    void setupUi(QWidget *main_classClass)
    {
        if (main_classClass->objectName().isEmpty())
            main_classClass->setObjectName(QString::fromUtf8("main_classClass"));
        main_classClass->resize(600, 400);

        retranslateUi(main_classClass);

        QMetaObject::connectSlotsByName(main_classClass);
    } // setupUi

    void retranslateUi(QWidget *main_classClass)
    {
        main_classClass->setWindowTitle(QApplication::translate("main_classClass", "main_class", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class main_classClass: public Ui_main_classClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_CLASS_H
