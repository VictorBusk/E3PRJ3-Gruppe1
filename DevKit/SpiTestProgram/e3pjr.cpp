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

    int errX, errY, errZ;

    SPIapi spi;

    unsigned char cmdX = 0x18;
    unsigned char cmdY = 0x19;
    unsigned char cmdZ = 0x24;
    unsigned char val = 0xAA;

    qDebug() << "***** SPI tx: " << spiCount_ << " *****";
    errX = spi.setPacket(&cmdX, &val);
    qDebug() << "cmd: 0x" << QString::number(cmdX, 16) << " val: 0x" << QString::number(val, 16) << " (" << val << ") status: " << errX;
    if(errX != 0)
    {
        ui->plainTextX->appendPlainText("..calX err!");
    }
    else
    {
        ui->plainTextX->appendPlainText("..calX sent");
    }

    errY = spi.setPacket(&cmdY, &val);
    qDebug() << "cmd: 0x" << QString::number(cmdY, 16) << " val: 0x" << QString::number(val, 16) << " (" << val << ") status: " << errY;
    if(errY != 0)
    {
        ui->plainTextY->appendPlainText("..calY err!");
    }
    else
    {
        ui->plainTextY->appendPlainText("..calY sent");
    }

    errZ = spi.setPacket(&cmdZ, &val);
    qDebug() << "cmd: 0x" << QString::number(cmdZ, 16) << " val: 0x" << QString::number(val, 16) << " (" << val << ") status: " << errZ;
    if(errZ != 0)
    {
        ui->plainTextZ->appendPlainText("..calZ err!");
    }
    else
    {
        ui->plainTextZ->appendPlainText("..calZ sent");
    }
}

//void E3PJR::on_sliderSetX_valueChanged()
//{
//    ui->plainTextX->appendPlainText("Opdater xPos..");

//    int errX;

//    SPIapi spi;

//    unsigned char cmdX = 0x10;

//    unsigned char valX = ui->sliderSetX->value();

//    qDebug() << "***** SPI tx: " << spiCount_ << " *****";
//    errX = spi.setPacket(&cmdX, &valX);
//    qDebug() << "cmd: 0x" << QString::number(cmdX, 16) << " val: 0x" << QString::number(valX, 16) << " (" << valX << ") status: " << errX;
//    if(errX != 0)
//    {
//        ui->plainTextX->appendPlainText("..setX err!");
//    }
//    else
//    {
//        ui->plainTextX->appendPlainText("..setX sent");
//    }
//}

//void E3PJR::on_sliderSetY_valueChanged()
//{
//    ui->plainTextY->appendPlainText("Opdater yPos..");

//    int errY;

//    SPIapi spi;

//    unsigned char cmdY = 0x11;

//    unsigned char valY = ui->sliderSetY->value();

//    qDebug() << "***** SPI tx: " << spiCount_ << " *****";
//    errY = spi.setPacket(&cmdY, &valY);
//    qDebug() << "cmd: 0x" << QString::number(cmdY, 16) << " val: 0x" << QString::number(valY, 16) << " (" << valY << ") status: " << errY;
//    if(errY != 0)
//    {
//        ui->plainTextY->appendPlainText("..setY err!");
//    }
//    else
//    {
//        ui->plainTextY->appendPlainText("..setY sent");
//    }
//}

//void E3PJR::on_sliderSetZ_valueChanged()
//{
//    ui->plainTextZ->appendPlainText("Opdater zPos..");

//    int errZ;

//    SPIapi spi;

//    unsigned char cmdZ = 0x11;

//    unsigned char valZ = ui->sliderSetY->value();

//    qDebug() << "***** SPI tx: " << spiCount_ << " *****";
//    errZ = spi.setPacket(&cmdZ, &valZ);
//    qDebug() << "cmd: 0x" << QString::number(cmdZ, 16) << " val: 0x" << QString::number(valZ, 16) << " (" << valZ << ") status: " << errZ;
//    if(errZ != 0)
//    {
//        ui->plainTextY->appendPlainText("..setZ err!");
//    }
//    else
//    {
//        ui->plainTextZ->appendPlainText("..setZ sent");
//    }
//}

void E3PJR::on_pushSetXYZ_pressed()
{
    ui->plainTextX->appendPlainText("Sender xPos..");
    ui->plainTextY->appendPlainText("Sender yPos..");
    ui->plainTextZ->appendPlainText("Sender zPos..");

    int errX, errY, errZ;

    SPIapi spi;

    unsigned char cmdX = 0x10;
    unsigned char cmdY = 0x11;
    unsigned char cmdZ = 0x20;

    unsigned char valX = ui->spinSetX->value();
    unsigned char valY = ui->spinSetY->value();
    unsigned char valZ = ui->spinSetZ->value();

    qDebug() << "***** SPI tx: " << spiCount_ << " *****";
    errX = spi.setPacket(&cmdX, &valX);
    qDebug() << "cmd: 0x" << QString::number(cmdX, 16) << " val: 0x" << QString::number(valX, 16) << " (" << valX << ") status: " << errX;
    if(errX != 0)
    {
        ui->plainTextX->appendPlainText("..setX err!");
    }
    else
    {
        ui->plainTextX->appendPlainText("..setX sent");
    }
    errY = spi.setPacket(&cmdY, &valY);
    qDebug() << "cmd: 0x" << QString::number(cmdY, 16) << " val: 0x" << QString::number(valY, 16) << " (" << valY << ") status: " << errY;
    if(errY != 0)
    {
        ui->plainTextY->appendPlainText("..setY err!");
    }
    else
    {
        ui->plainTextY->appendPlainText("..setY sent");
    }
    errZ = spi.setPacket(&cmdZ, &valZ);
    qDebug() << "cmd: 0x" << QString::number(cmdZ, 16) << " val: 0x" << QString::number(valZ, 16) << " (" << valZ << ") status: " << errZ;
    if(errZ != 0)
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

    int err, errX, errY, errZ;

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

    errX = spi.getPacket(&cmdXPos, &valXPos);
    qDebug() << "cmd: 0x" << QString::number(cmdXPos, 16) << " val: 0x" << QString::number(valXPos, 16) << " (" << valXPos << ") status: " << errX;
    if(errX != 0)
    {
        ui->plainTextX->appendPlainText("..getXPos err!");
        ui->lineGetXPos->clear();
    }
    else
    {
        ui->plainTextX->appendPlainText("..getXPos done");
        ui->lineGetXPos->setText(QString::number(valXPos, 10));
    }

    errY = spi.getPacket(&cmdYPos, &valYPos);
    qDebug() << "cmd: 0x" << QString::number(cmdYPos, 16) << " val: 0x" << QString::number(valYPos, 16) << " (" << valYPos << ") status: " << errY;
    if(errY != 0)
    {
        ui->plainTextY->appendPlainText("..getYPos err!");
        ui->lineGetXPos->clear();
    }
    else
    {
        ui->plainTextY->appendPlainText("..getYPos done");
        ui->lineGetYPos->setText(QString::number(valYPos, 10));
    }

    errZ = spi.getPacket(&cmdZPos, &valZPos);
    qDebug() << "cmd: 0x" << QString::number(cmdZPos, 16) << " val: 0x" << QString::number(valZPos, 16) << " (" << valZPos << ") status: " << errZ;
    if(errZ != 0)
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

    int err, errX, errY, errZ;

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

    errX = spi.getPacket(&cmdXMax, &valXMax);
    qDebug() << "cmd: 0x" << QString::number(cmdXMax, 16) << " val: 0x" << QString::number(valXMax, 16) << " (" << valXMax << ") status: " << errX;
    if(errX != 0)
    {
        ui->plainTextX->appendPlainText("..getXMax err!");
        ui->lineGetXMax->clear();
    }
    else
    {
        ui->plainTextX->appendPlainText("..getXMax done");
        ui->lineGetXMax->setText(QString::number(valXMax, 10));
    }

    errY = spi.getPacket(&cmdYMax, &valYMax);
    qDebug() << "cmd: 0x" << QString::number(cmdYMax, 16) << " val: 0x" << QString::number(valYMax, 16) << " (" << valYMax << ") status: " << errY;
    if(errY != 0)
    {
        ui->plainTextY->appendPlainText("..getYMax err!");
        ui->lineGetXMax->clear();
    }
    else
    {
        ui->plainTextY->appendPlainText("..getYMax done");
        ui->lineGetYMax->setText(QString::number(valYMax, 10));
    }

    errZ = spi.getPacket(&cmdZMax, &valZMax);
    qDebug() << "cmd: 0x" << QString::number(cmdZMax, 16) << " val: 0x" << QString::number(valZMax, 16) << " (" << valZMax << ") status: " << errZ;
    if(errZ != 0)
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
