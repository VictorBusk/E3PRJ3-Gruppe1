#include <qdebug.h>
#include "e3pjr.h"
#include "ui_e3pjr.h"

E3PJR::E3PJR(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::E3PJR)
{
    ui->setupUi(this);

    setFixedSize(480, 272);
    setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint);

    spiCount_ = 0;

}

E3PJR::~E3PJR()
{
    delete ui;
}

void E3PJR::on_pushCalibrateXYZ_clicked()
{
    int err;

    SPIapi spi;

    unsigned char cmdX = 0x18;
    unsigned char cmdY = 0x19;
    unsigned char cmdZ = 0x24;
    unsigned char val = 0xAA;

    qDebug() << "***** SPI tx: " << spiCount_ << " *****";
    err = spi.setPacket(&cmdX, &val);
    qDebug() << "cmd: 0x" << QString::number(cmdX, 16) << " val: 0x" << QString::number(val, 16) << " (" << val << ") status: " << err;
    err = spi.setPacket(&cmdY, &val);
    qDebug() << "cmd: 0x" << QString::number(cmdY, 16) << " val: 0x" << QString::number(val, 16) << " (" << val << ") status: " << err;
    err = spi.setPacket(&cmdZ, &val);
    qDebug() << "cmd: 0x" << QString::number(cmdZ, 16) << " val: 0x" << QString::number(val, 16) << " (" << val << ") status: " << err;
}

void E3PJR::on_pushSetXYZ_clicked()
{
    int err;

    SPIapi spi;

    unsigned char cmdX = 0x10;
    unsigned char cmdY = 0x11;
    unsigned char cmdZ = 0x20;

    unsigned char valX = ui->spinSetX->value();
    unsigned char valY = ui->spinSetY->value();
    unsigned char valZ = ui->spinSetZ->value();

    qDebug() << "***** SPI tx: " << spiCount_ << " *****";
    err = spi.setPacket(&cmdX, &valX);
    qDebug() << "cmd: 0x" << QString::number(cmdX, 16) << " val: 0x" << QString::number(valX, 16) << " (" << valX << ") status: " << err;
    err = spi.setPacket(&cmdY, &valY);
    qDebug() << "cmd: 0x" << QString::number(cmdY, 16) << " val: 0x" << QString::number(valY, 16) << " (" << valY << ") status: " << err;
    err = spi.setPacket(&cmdZ, &valZ);
    qDebug() << "cmd: 0x" << QString::number(cmdZ, 16) << " val: 0x" << QString::number(valZ, 16) << " (" << valZ << ") status: " << err;

    spiCount_++;
}

void E3PJR::on_pushGetXYZPos_clicked()
{
    int err;

    SPIapi spi;

    unsigned char GetPos = 0x01;
    unsigned char cmdXPos = 0x12;
    unsigned char cmdYPos = 0x13;
    unsigned char cmdZPos = 0x21;

    unsigned char val = 0;
    unsigned int valXPos = 0;
    unsigned int valYPos = 0;
    unsigned int valZPos = 0;

    qDebug() << "***** SPI tx: " << spiCount_ << " *****";
    err = spi.setPacket(&GetPos, &val);
    qDebug() << "cmd: 0x" << QString::number(GetPos, 16) << " val: 0x" << QString::number(val, 16) << " (" << val << ") status: " << err;

    sleep(5);

    err = spi.getPacket(&cmdXPos, &valXPos);
    qDebug() << "cmd: 0x" << QString::number(cmdXPos, 16) << " val: 0x" << QString::number(valXPos, 16) << " (" << valXPos << ") status: " << err;
    ui->lineGetXPos->setText(QString::number(valXPos, 16));

    sleep(1);

    err = spi.getPacket(&cmdYPos, &valYPos);
    qDebug() << "cmd: 0x" << QString::number(cmdYPos, 16) << " val: 0x" << QString::number(valYPos, 16) << " (" << valYPos << ") status: " << err;
    ui->lineGetYPos->setText(QString::number(valYPos, 16));

    sleep(1);

    err = spi.getPacket(&cmdZPos, &valZPos);
    qDebug() << "cmd: 0x" << QString::number(cmdZPos, 16) << " val: 0x" << QString::number(valZPos, 16) << " (" << valZPos << ") status: " << err;
    ui->lineGetZPos->setText(QString::number(valZPos, 16));

    spiCount_++;
}

void E3PJR::on_pushGetXYZMax_clicked()
{
    int err;

    SPIapi spi;

    unsigned char GetMax = 0x02;
    unsigned char cmdXMax = 0x14;
    unsigned char cmdYMax = 0x15;
    unsigned char cmdZMax = 0x22;

    unsigned char val = 0xAA;
    unsigned int valXMax = 0;
    unsigned int valYMax = 0;
    unsigned int valZMax = 0;

    qDebug() << "***** SPI tx: " << spiCount_ << " *****";
    err = spi.setPacket(&GetMax, &val);
    qDebug() << "cmd: 0x" << QString::number(GetMax, 16) << " val: 0x" << QString::number(val, 16) << " (" << val << ") status: " << err;

    usleep(1000);

    err = spi.getPacket(&cmdXMax, &valXMax);
    qDebug() << "cmd: 0x" << QString::number(cmdXMax, 16) << " val: 0x" << QString::number(valXMax, 16) << " (" << valXMax << ") status: " << err;
    ui->lineGetXMax->setText(QString::number(valXMax, 16));
    err = spi.getPacket(&cmdYMax, &valYMax);
    qDebug() << "cmd: 0x" << QString::number(cmdYMax, 16) << " val: 0x" << QString::number(valYMax, 16) << " (" << valYMax << ") status: " << err;
    ui->lineGetYMax->setText(QString::number(valYMax, 16));
    err = spi.getPacket(&cmdZMax, &valZMax);
    qDebug() << "cmd: 0x" << QString::number(cmdZMax, 16) << " val: 0x" << QString::number(valZMax, 16) << " (" << valZMax << ") status: " << err;
    ui->lineGetZMax->setText(QString::number(valZMax, 16));

    spiCount_++;
}
