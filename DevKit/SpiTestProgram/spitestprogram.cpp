#include "spitestprogram.h"
#include "ui_spitestprogram.h"

SpiTestProgram::SpiTestProgram(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpiTestProgram)
{
    ui->setupUi(this);

    setFixedSize(480, 272);
    setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint); // Uncommect to make fullscreen
}

SpiTestProgram::~SpiTestProgram()
{
    delete ui;
}

void SpiTestProgram::on_pbRedOn_clicked()
{
    SPIapi redOn;

    unsigned char cmd = 0x31;
    unsigned char val = 0xff;

    redOn.setPacket(&cmd, &val);
}

void SpiTestProgram::on_pbRedOff_clicked()
{
    SPIapi redOff;

    unsigned char cmd = 0x31;
    unsigned char val = 0x00;

    redOff.setPacket(&cmd, &val);
}

void SpiTestProgram::on_pbGreenOn_clicked()
{
    SPIapi greenOn;

    unsigned char cmd = 0x32;
    unsigned char val = 0xff;

    greenOn.setPacket(&cmd, &val);
}

void SpiTestProgram::on_pbGreenOff_clicked()
{
    SPIapi greenOff;

    unsigned char cmd = 0x32;
    unsigned char val = 0x00;

    greenOff.setPacket(&cmd, &val);
}

void SpiTestProgram::on_pbBlueOn_clicked()
{
    SPIapi blueOn;

    unsigned char cmd = 0x33;
    unsigned char val = 0xff;

    blueOn.setPacket(&cmd, &val);
}

void SpiTestProgram::on_pbBlueOff_clicked()
{
    SPIapi blueOff;

    unsigned char cmd = 0x33;
    unsigned char val = 0x00;

    blueOff.setPacket(&cmd, &val);
}

void SpiTestProgram::on_pbReslutat_clicked()
{
    SPIapi getVal;

    unsigned char cmdX = 0x91;
    unsigned char cmdY = 0x92;
    unsigned char cmdR = 0x93;

    unsigned char valX = ui->valX->value();
    unsigned char valY = ui->valY->value();
    unsigned int reslutat;

    getVal.setPacket(&cmdX, &valX);

    getVal.setPacket(&cmdY, &valY);

    getVal.getPacket(&cmdR, &reslutat);

    QString rString;
    rString.append(QString::number(valX));
    rString.append(" x ");
    rString.append(QString::number(valY));
    rString.append(" = ");
    rString.append(QString::number(reslutat));
    rString.append(" med venlig hilsen din PSoC :)");
    ui->inReslutat->setText(rString);

}

void SpiTestProgram::on_pbClear_clicked()
{
    ui->inReslutat->clear();
}

