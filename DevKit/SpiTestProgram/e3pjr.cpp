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

void E3PJR::on_pushCalibrateXYZ_pressed()
{
    ui->plainTextX->appendPlainText("Sender xCal..");
    ui->plainTextY->appendPlainText("Sender yCal..");
    ui->plainTextZ->appendPlainText("Sender zCal..");
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
    if(err != 0)
    {
        ui->plainTextX->appendPlainText("..calX err!");
    }
    else
    {
        ui->plainTextX->appendPlainText("..calX sent");
    }

    err = spi.setPacket(&cmdY, &val);
    qDebug() << "cmd: 0x" << QString::number(cmdY, 16) << " val: 0x" << QString::number(val, 16) << " (" << val << ") status: " << err;
    if(err != 0)
    {
        ui->plainTextY->appendPlainText("..calY err!");
    }
    else
    {
        ui->plainTextY->appendPlainText("..calY sent");
    }

    err = spi.setPacket(&cmdZ, &val);
    qDebug() << "cmd: 0x" << QString::number(cmdZ, 16) << " val: 0x" << QString::number(val, 16) << " (" << val << ") status: " << err;
    if(err != 0)
    {
        ui->plainTextZ->appendPlainText("..calZ err!");
    }
    else
    {
        ui->plainTextZ->appendPlainText("..calZ sent");
    }
}
void E3PJR::on_pushSetXYZ_pressed()
{
    ui->plainTextX->appendPlainText("Sender xPos..");
    ui->plainTextY->appendPlainText("Sender yPos..");
    ui->plainTextZ->appendPlainText("Sender zPos..");
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
    if(err != 0)
    {
        ui->plainTextX->appendPlainText("..setX err!");
    }
    else
    {
        ui->plainTextX->appendPlainText("..setX sent");
    }
    err = spi.setPacket(&cmdY, &valY);
    qDebug() << "cmd: 0x" << QString::number(cmdY, 16) << " val: 0x" << QString::number(valY, 16) << " (" << valY << ") status: " << err;
    if(err != 0)
    {
        ui->plainTextY->appendPlainText("..setY err!");
    }
    else
    {
        ui->plainTextY->appendPlainText("..setY sent");
    }
    err = spi.setPacket(&cmdZ, &valZ);
    qDebug() << "cmd: 0x" << QString::number(cmdZ, 16) << " val: 0x" << QString::number(valZ, 16) << " (" << valZ << ") status: " << err;
    if(err != 0)
    {
        ui->plainTextZ->appendPlainText("..setZ err!");
    }
    else
    {
        ui->plainTextZ->appendPlainText("..setZ sent");
    }

    spiCount_++;
}

void E3PJR::on_pushGetXYZPos_pressed()
{
    ui->lineGetXPos->clear();
    ui->lineGetYPos->clear();
    ui->lineGetZPos->clear();
    ui->plainTextX->appendPlainText("Henter xPos...");
    ui->plainTextY->appendPlainText("Henter yPos...");
    ui->plainTextZ->appendPlainText("Henter zPos...");
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

    sleep(1);

    err = spi.getPacket(&cmdXPos, &valXPos);
    qDebug() << "cmd: 0x" << QString::number(cmdXPos, 16) << " val: 0x" << QString::number(valXPos, 16) << " (" << valXPos << ") status: " << err;
    if(err != 0)
    {
        ui->plainTextX->appendPlainText("..getXPos err!");
        ui->lineGetXPos->clear();
    }
    else
    {
        ui->plainTextX->appendPlainText("..getXPos done");
        ui->lineGetXPos->setText(QString::number(valXPos, 10));
    }

    err = spi.getPacket(&cmdYPos, &valYPos);
    qDebug() << "cmd: 0x" << QString::number(cmdYPos, 16) << " val: 0x" << QString::number(valYPos, 16) << " (" << valYPos << ") status: " << err;
    if(err != 0)
    {
        ui->plainTextY->appendPlainText("..getYPos err!");
        ui->lineGetXPos->clear();
    }
    else
    {
        ui->plainTextY->appendPlainText("..getYPos done");
        ui->lineGetYPos->setText(QString::number(valYPos, 10));
    }

    err = spi.getPacket(&cmdZPos, &valZPos);
    qDebug() << "cmd: 0x" << QString::number(cmdZPos, 16) << " val: 0x" << QString::number(valZPos, 16) << " (" << valZPos << ") status: " << err;
    if(err != 0)
    {
        ui->plainTextZ->appendPlainText("..getZPos err!");
        ui->lineGetZPos->clear();
    }
    else
    {
        ui->plainTextZ->appendPlainText("..getZPos done");
        ui->lineGetZPos->setText(QString::number(valZPos, 10));
    }

    spiCount_++;
}

void E3PJR::on_pushGetXYZMax_pressed()
{
    ui->lineGetXMax->clear();
    ui->lineGetYMax->clear();
    ui->lineGetZMax->clear();
    ui->plainTextX->appendPlainText("Henter xMax...");
    ui->plainTextY->appendPlainText("Henter yMax...");
    ui->plainTextZ->appendPlainText("Henter zMax...");
}

void E3PJR::on_pushGetXYZMax_clicked()
{
    int err;

    SPIapi spi;

    unsigned char GetMax = 0x02;
    unsigned char cmdXMax = 0x14;
    unsigned char cmdYMax = 0x15;
    unsigned char cmdZMax = 0x22;

    unsigned char val = 0;
    unsigned int valXMax = 0;
    unsigned int valYMax = 0;
    unsigned int valZMax = 0;

    qDebug() << "***** SPI tx: " << spiCount_ << " *****";
    err = spi.setPacket(&GetMax, &val);
    qDebug() << "cmd: 0x" << QString::number(GetMax, 16) << " val: 0x" << QString::number(val, 16) << " (" << val << ") status: " << err;

    sleep(1);

    err = spi.getPacket(&cmdXMax, &valXMax);
    qDebug() << "cmd: 0x" << QString::number(cmdXMax, 16) << " val: 0x" << QString::number(valXMax, 16) << " (" << valXMax << ") status: " << err;
    if(err != 0)
    {
        ui->plainTextX->appendPlainText("..getXMax err!");
        ui->lineGetXMax->clear();
    }
    else
    {
        ui->plainTextX->appendPlainText("..getXMax done");
        ui->lineGetXMax->setText(QString::number(valXMax, 10));
    }

    err = spi.getPacket(&cmdYMax, &valYMax);
    qDebug() << "cmd: 0x" << QString::number(cmdYMax, 16) << " val: 0x" << QString::number(valYMax, 16) << " (" << valYMax << ") status: " << err;
    if(err != 0)
    {
        ui->plainTextY->appendPlainText("..getYMax err!");
        ui->lineGetXMax->clear();
    }
    else
    {
        ui->plainTextY->appendPlainText("..getYMax done");
        ui->lineGetYMax->setText(QString::number(valYMax, 10));
    }

    err = spi.getPacket(&cmdZMax, &valZMax);
    qDebug() << "cmd: 0x" << QString::number(cmdZMax, 16) << " val: 0x" << QString::number(valZMax, 16) << " (" << valZMax << ") status: " << err;
    if(err != 0)
    {
        ui->plainTextZ->appendPlainText("..getZMax err!");
        ui->lineGetZMax->clear();
    }
    else
    {
        ui->plainTextZ->appendPlainText("..getZMax done");
        ui->lineGetZMax->setText(QString::number(valZMax, 10));
    }

    spiCount_++;
}
