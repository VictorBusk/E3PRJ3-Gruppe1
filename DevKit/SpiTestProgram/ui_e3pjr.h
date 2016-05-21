/********************************************************************************
** Form generated from reading UI file 'e3pjr.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_E3PJR_H
#define UI_E3PJR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_E3PJR
{
public:
    QWidget *XYZ;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_3;
    QSlider *sliderSetX;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_6;
    QSpinBox *spinSetX;
    QLineEdit *lineGetXPos;
    QLineEdit *lineGetXMax;
    QPlainTextEdit *plainTextX;
    QSlider *sliderSetY;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_7;
    QSpinBox *spinSetY;
    QLineEdit *lineGetYPos;
    QLineEdit *lineGetYMax;
    QPlainTextEdit *plainTextY;
    QSlider *sliderSetZ;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_8;
    QSpinBox *spinSetZ;
    QLineEdit *lineGetZPos;
    QLineEdit *lineGetZMax;
    QPlainTextEdit *plainTextZ;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushSetXYZ;
    QPushButton *pushGetXYZPos;
    QPushButton *pushGetXYZMax;
    QPushButton *pushCalibrateXYZ;

    void setupUi(QTabWidget *E3PJR)
    {
        if (E3PJR->objectName().isEmpty())
            E3PJR->setObjectName(QString::fromUtf8("E3PJR"));
        E3PJR->resize(480, 278);
        XYZ = new QWidget();
        XYZ->setObjectName(QString::fromUtf8("XYZ"));
        verticalLayout_9 = new QVBoxLayout(XYZ);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        sliderSetX = new QSlider(XYZ);
        sliderSetX->setObjectName(QString::fromUtf8("sliderSetX"));
        sliderSetX->setMaximum(255);
        sliderSetX->setSingleStep(5);
        sliderSetX->setPageStep(15);
        sliderSetX->setOrientation(Qt::Vertical);

        horizontalLayout_3->addWidget(sliderSetX);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        spinSetX = new QSpinBox(XYZ);
        spinSetX->setObjectName(QString::fromUtf8("spinSetX"));
        spinSetX->setAlignment(Qt::AlignCenter);
        spinSetX->setMaximum(255);
        spinSetX->setSingleStep(5);

        verticalLayout_6->addWidget(spinSetX);

        lineGetXPos = new QLineEdit(XYZ);
        lineGetXPos->setObjectName(QString::fromUtf8("lineGetXPos"));
        lineGetXPos->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(lineGetXPos);

        lineGetXMax = new QLineEdit(XYZ);
        lineGetXMax->setObjectName(QString::fromUtf8("lineGetXMax"));
        lineGetXMax->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(lineGetXMax);


        horizontalLayout_4->addLayout(verticalLayout_6);


        verticalLayout->addLayout(horizontalLayout_4);

        plainTextX = new QPlainTextEdit(XYZ);
        plainTextX->setObjectName(QString::fromUtf8("plainTextX"));
        plainTextX->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        plainTextX->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        plainTextX->setUndoRedoEnabled(false);
        plainTextX->setReadOnly(true);
        plainTextX->setOverwriteMode(false);

        verticalLayout->addWidget(plainTextX);


        horizontalLayout_3->addLayout(verticalLayout);

        sliderSetY = new QSlider(XYZ);
        sliderSetY->setObjectName(QString::fromUtf8("sliderSetY"));
        sliderSetY->setMaximum(255);
        sliderSetY->setSingleStep(5);
        sliderSetY->setPageStep(15);
        sliderSetY->setOrientation(Qt::Vertical);

        horizontalLayout_3->addWidget(sliderSetY);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        spinSetY = new QSpinBox(XYZ);
        spinSetY->setObjectName(QString::fromUtf8("spinSetY"));
        spinSetY->setAlignment(Qt::AlignCenter);
        spinSetY->setMaximum(255);
        spinSetY->setSingleStep(5);

        verticalLayout_7->addWidget(spinSetY);

        lineGetYPos = new QLineEdit(XYZ);
        lineGetYPos->setObjectName(QString::fromUtf8("lineGetYPos"));
        lineGetYPos->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(lineGetYPos);

        lineGetYMax = new QLineEdit(XYZ);
        lineGetYMax->setObjectName(QString::fromUtf8("lineGetYMax"));
        lineGetYMax->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(lineGetYMax);


        horizontalLayout_5->addLayout(verticalLayout_7);


        verticalLayout_2->addLayout(horizontalLayout_5);

        plainTextY = new QPlainTextEdit(XYZ);
        plainTextY->setObjectName(QString::fromUtf8("plainTextY"));
        plainTextY->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        plainTextY->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        plainTextY->setUndoRedoEnabled(false);
        plainTextY->setReadOnly(true);

        verticalLayout_2->addWidget(plainTextY);


        horizontalLayout_3->addLayout(verticalLayout_2);

        sliderSetZ = new QSlider(XYZ);
        sliderSetZ->setObjectName(QString::fromUtf8("sliderSetZ"));
        sliderSetZ->setMaximum(255);
        sliderSetZ->setSingleStep(5);
        sliderSetZ->setPageStep(15);
        sliderSetZ->setOrientation(Qt::Vertical);

        horizontalLayout_3->addWidget(sliderSetZ);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        spinSetZ = new QSpinBox(XYZ);
        spinSetZ->setObjectName(QString::fromUtf8("spinSetZ"));
        spinSetZ->setAlignment(Qt::AlignCenter);
        spinSetZ->setMaximum(255);
        spinSetZ->setSingleStep(5);

        verticalLayout_8->addWidget(spinSetZ);

        lineGetZPos = new QLineEdit(XYZ);
        lineGetZPos->setObjectName(QString::fromUtf8("lineGetZPos"));
        lineGetZPos->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(lineGetZPos);

        lineGetZMax = new QLineEdit(XYZ);
        lineGetZMax->setObjectName(QString::fromUtf8("lineGetZMax"));
        lineGetZMax->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(lineGetZMax);


        horizontalLayout_6->addLayout(verticalLayout_8);


        verticalLayout_5->addLayout(horizontalLayout_6);

        plainTextZ = new QPlainTextEdit(XYZ);
        plainTextZ->setObjectName(QString::fromUtf8("plainTextZ"));
        plainTextZ->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        plainTextZ->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        plainTextZ->setUndoRedoEnabled(false);
        plainTextZ->setReadOnly(true);

        verticalLayout_5->addWidget(plainTextZ);


        horizontalLayout_3->addLayout(verticalLayout_5);


        verticalLayout_9->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushSetXYZ = new QPushButton(XYZ);
        pushSetXYZ->setObjectName(QString::fromUtf8("pushSetXYZ"));

        horizontalLayout_2->addWidget(pushSetXYZ);

        pushGetXYZPos = new QPushButton(XYZ);
        pushGetXYZPos->setObjectName(QString::fromUtf8("pushGetXYZPos"));

        horizontalLayout_2->addWidget(pushGetXYZPos);

        pushGetXYZMax = new QPushButton(XYZ);
        pushGetXYZMax->setObjectName(QString::fromUtf8("pushGetXYZMax"));

        horizontalLayout_2->addWidget(pushGetXYZMax);

        pushCalibrateXYZ = new QPushButton(XYZ);
        pushCalibrateXYZ->setObjectName(QString::fromUtf8("pushCalibrateXYZ"));

        horizontalLayout_2->addWidget(pushCalibrateXYZ);


        verticalLayout_9->addLayout(horizontalLayout_2);

        E3PJR->addTab(XYZ, QString());
        QWidget::setTabOrder(spinSetY, spinSetZ);

        retranslateUi(E3PJR);
        QObject::connect(sliderSetY, SIGNAL(valueChanged(int)), spinSetY, SLOT(setValue(int)));
        QObject::connect(spinSetY, SIGNAL(valueChanged(int)), sliderSetY, SLOT(setValue(int)));
        QObject::connect(sliderSetZ, SIGNAL(valueChanged(int)), spinSetZ, SLOT(setValue(int)));
        QObject::connect(spinSetZ, SIGNAL(valueChanged(int)), sliderSetZ, SLOT(setValue(int)));
        QObject::connect(sliderSetX, SIGNAL(valueChanged(int)), spinSetX, SLOT(setValue(int)));
        QObject::connect(spinSetX, SIGNAL(valueChanged(int)), sliderSetX, SLOT(setValue(int)));

        E3PJR->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(E3PJR);
    } // setupUi

    void retranslateUi(QTabWidget *E3PJR)
    {
        E3PJR->setWindowTitle(QApplication::translate("E3PJR", "TabWidget", 0, QApplication::UnicodeUTF8));
        lineGetXPos->setPlaceholderText(QApplication::translate("E3PJR", "xPos", 0, QApplication::UnicodeUTF8));
        lineGetXMax->setPlaceholderText(QApplication::translate("E3PJR", "xMax", 0, QApplication::UnicodeUTF8));
        lineGetYPos->setPlaceholderText(QApplication::translate("E3PJR", "yPos", 0, QApplication::UnicodeUTF8));
        lineGetYMax->setPlaceholderText(QApplication::translate("E3PJR", "yMax", 0, QApplication::UnicodeUTF8));
        lineGetZPos->setPlaceholderText(QApplication::translate("E3PJR", "zPos", 0, QApplication::UnicodeUTF8));
        lineGetZMax->setPlaceholderText(QApplication::translate("E3PJR", "zMax", 0, QApplication::UnicodeUTF8));
        pushSetXYZ->setText(QApplication::translate("E3PJR", "SetXYZPos", 0, QApplication::UnicodeUTF8));
        pushGetXYZPos->setText(QApplication::translate("E3PJR", "GetXYZPos", 0, QApplication::UnicodeUTF8));
        pushGetXYZMax->setText(QApplication::translate("E3PJR", "GetXYZMax", 0, QApplication::UnicodeUTF8));
        pushCalibrateXYZ->setText(QApplication::translate("E3PJR", "CalibrateXYZ", 0, QApplication::UnicodeUTF8));
        E3PJR->setTabText(E3PJR->indexOf(XYZ), QApplication::translate("E3PJR", "XYZ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class E3PJR: public Ui_E3PJR {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_E3PJR_H
