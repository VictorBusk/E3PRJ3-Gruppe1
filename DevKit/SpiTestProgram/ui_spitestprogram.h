/********************************************************************************
** Form generated from reading UI file 'spitestprogram.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPITESTPROGRAM_H
#define UI_SPITESTPROGRAM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SpiTestProgram
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *setTest;
    QVBoxLayout *RedRGB;
    QLabel *tRedRGB;
    QPushButton *pbRedOn;
    QPushButton *pbRedOff;
    QVBoxLayout *GreenRGB;
    QLabel *tGreenRGB;
    QPushButton *pbGreenOn;
    QPushButton *pbGreenOff;
    QVBoxLayout *BlueRGB;
    QLabel *tBlueRGB;
    QPushButton *pbBlueOn;
    QPushButton *pbBlueOff;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *getTest;
    QHBoxLayout *Input;
    QSpinBox *valX;
    QLabel *label;
    QSpinBox *valY;
    QPushButton *pbReslutat;
    QHBoxLayout *Output;
    QLineEdit *inReslutat;
    QPushButton *pbClear;

    void setupUi(QWidget *SpiTestProgram)
    {
        if (SpiTestProgram->objectName().isEmpty())
            SpiTestProgram->setObjectName(QString::fromUtf8("SpiTestProgram"));
        SpiTestProgram->resize(480, 272);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SpiTestProgram->sizePolicy().hasHeightForWidth());
        SpiTestProgram->setSizePolicy(sizePolicy);
        SpiTestProgram->setMinimumSize(QSize(480, 272));
        SpiTestProgram->setMaximumSize(QSize(480, 272));
        horizontalLayoutWidget = new QWidget(SpiTestProgram);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(9, 9, 461, 131));
        setTest = new QHBoxLayout(horizontalLayoutWidget);
        setTest->setSpacing(6);
        setTest->setContentsMargins(11, 11, 11, 11);
        setTest->setObjectName(QString::fromUtf8("setTest"));
        setTest->setContentsMargins(0, 0, 0, 0);
        RedRGB = new QVBoxLayout();
        RedRGB->setSpacing(6);
        RedRGB->setObjectName(QString::fromUtf8("RedRGB"));
        tRedRGB = new QLabel(horizontalLayoutWidget);
        tRedRGB->setObjectName(QString::fromUtf8("tRedRGB"));
        tRedRGB->setMaximumSize(QSize(272, 30));
        tRedRGB->setAlignment(Qt::AlignCenter);

        RedRGB->addWidget(tRedRGB);

        pbRedOn = new QPushButton(horizontalLayoutWidget);
        pbRedOn->setObjectName(QString::fromUtf8("pbRedOn"));
        pbRedOn->setMaximumSize(QSize(160, 30));

        RedRGB->addWidget(pbRedOn);

        pbRedOff = new QPushButton(horizontalLayoutWidget);
        pbRedOff->setObjectName(QString::fromUtf8("pbRedOff"));
        pbRedOff->setMaximumSize(QSize(160, 30));

        RedRGB->addWidget(pbRedOff);


        setTest->addLayout(RedRGB);

        GreenRGB = new QVBoxLayout();
        GreenRGB->setSpacing(6);
        GreenRGB->setObjectName(QString::fromUtf8("GreenRGB"));
        tGreenRGB = new QLabel(horizontalLayoutWidget);
        tGreenRGB->setObjectName(QString::fromUtf8("tGreenRGB"));
        tGreenRGB->setMaximumSize(QSize(160, 30));
        tGreenRGB->setAlignment(Qt::AlignCenter);

        GreenRGB->addWidget(tGreenRGB);

        pbGreenOn = new QPushButton(horizontalLayoutWidget);
        pbGreenOn->setObjectName(QString::fromUtf8("pbGreenOn"));
        pbGreenOn->setMaximumSize(QSize(160, 30));

        GreenRGB->addWidget(pbGreenOn);

        pbGreenOff = new QPushButton(horizontalLayoutWidget);
        pbGreenOff->setObjectName(QString::fromUtf8("pbGreenOff"));
        pbGreenOff->setMaximumSize(QSize(160, 30));

        GreenRGB->addWidget(pbGreenOff);


        setTest->addLayout(GreenRGB);

        BlueRGB = new QVBoxLayout();
        BlueRGB->setSpacing(6);
        BlueRGB->setObjectName(QString::fromUtf8("BlueRGB"));
        tBlueRGB = new QLabel(horizontalLayoutWidget);
        tBlueRGB->setObjectName(QString::fromUtf8("tBlueRGB"));
        tBlueRGB->setMaximumSize(QSize(160, 30));
        tBlueRGB->setAlignment(Qt::AlignCenter);

        BlueRGB->addWidget(tBlueRGB);

        pbBlueOn = new QPushButton(horizontalLayoutWidget);
        pbBlueOn->setObjectName(QString::fromUtf8("pbBlueOn"));
        pbBlueOn->setMaximumSize(QSize(160, 30));

        BlueRGB->addWidget(pbBlueOn);

        pbBlueOff = new QPushButton(horizontalLayoutWidget);
        pbBlueOff->setObjectName(QString::fromUtf8("pbBlueOff"));
        pbBlueOff->setMaximumSize(QSize(160, 30));

        BlueRGB->addWidget(pbBlueOff);


        setTest->addLayout(BlueRGB);

        verticalLayoutWidget = new QWidget(SpiTestProgram);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 150, 461, 111));
        getTest = new QVBoxLayout(verticalLayoutWidget);
        getTest->setSpacing(6);
        getTest->setContentsMargins(11, 11, 11, 11);
        getTest->setObjectName(QString::fromUtf8("getTest"));
        getTest->setContentsMargins(0, 0, 0, 0);
        Input = new QHBoxLayout();
        Input->setSpacing(6);
        Input->setObjectName(QString::fromUtf8("Input"));
        valX = new QSpinBox(verticalLayoutWidget);
        valX->setObjectName(QString::fromUtf8("valX"));
        valX->setMaximumSize(QSize(160, 30));

        Input->addWidget(valX);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(20, 30));
        label->setAlignment(Qt::AlignCenter);

        Input->addWidget(label);

        valY = new QSpinBox(verticalLayoutWidget);
        valY->setObjectName(QString::fromUtf8("valY"));
        valY->setMaximumSize(QSize(160, 30));

        Input->addWidget(valY);

        pbReslutat = new QPushButton(verticalLayoutWidget);
        pbReslutat->setObjectName(QString::fromUtf8("pbReslutat"));
        pbReslutat->setMaximumSize(QSize(160, 30));

        Input->addWidget(pbReslutat);


        getTest->addLayout(Input);

        Output = new QHBoxLayout();
        Output->setSpacing(6);
        Output->setObjectName(QString::fromUtf8("Output"));
        inReslutat = new QLineEdit(verticalLayoutWidget);
        inReslutat->setObjectName(QString::fromUtf8("inReslutat"));
        inReslutat->setMaximumSize(QSize(340, 30));
        inReslutat->setAlignment(Qt::AlignCenter);

        Output->addWidget(inReslutat);

        pbClear = new QPushButton(verticalLayoutWidget);
        pbClear->setObjectName(QString::fromUtf8("pbClear"));
        pbClear->setMaximumSize(QSize(160, 30));

        Output->addWidget(pbClear);


        getTest->addLayout(Output);


        retranslateUi(SpiTestProgram);

        QMetaObject::connectSlotsByName(SpiTestProgram);
    } // setupUi

    void retranslateUi(QWidget *SpiTestProgram)
    {
        tRedRGB->setText(QApplication::translate("SpiTestProgram", "Red RGB", 0, QApplication::UnicodeUTF8));
        pbRedOn->setText(QApplication::translate("SpiTestProgram", "On", 0, QApplication::UnicodeUTF8));
        pbRedOff->setText(QApplication::translate("SpiTestProgram", "Off", 0, QApplication::UnicodeUTF8));
        tGreenRGB->setText(QApplication::translate("SpiTestProgram", "Green RGB", 0, QApplication::UnicodeUTF8));
        pbGreenOn->setText(QApplication::translate("SpiTestProgram", "On", 0, QApplication::UnicodeUTF8));
        pbGreenOff->setText(QApplication::translate("SpiTestProgram", "Off", 0, QApplication::UnicodeUTF8));
        tBlueRGB->setText(QApplication::translate("SpiTestProgram", "Blue RGB", 0, QApplication::UnicodeUTF8));
        pbBlueOn->setText(QApplication::translate("SpiTestProgram", "On", 0, QApplication::UnicodeUTF8));
        pbBlueOff->setText(QApplication::translate("SpiTestProgram", "Off", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SpiTestProgram", "x", 0, QApplication::UnicodeUTF8));
        pbReslutat->setText(QApplication::translate("SpiTestProgram", "Resultat", 0, QApplication::UnicodeUTF8));
        pbClear->setText(QApplication::translate("SpiTestProgram", "Clear", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(SpiTestProgram);
    } // retranslateUi

};

namespace Ui {
    class SpiTestProgram: public Ui_SpiTestProgram {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPITESTPROGRAM_H
