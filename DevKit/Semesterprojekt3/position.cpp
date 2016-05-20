#include "position.h"
#include "plannerdialog.h"
#include "spiapi.h"
#include "ui_display.h"
#include <qdebug.h>
#include <QWidget>

unsigned char valX=0;
unsigned char valY=0;
unsigned char valZ=0;

MainDisplay::MainDisplay(QWidget *parent) : QWidget(parent),
    ui(new Ui::MainDisplay)
{
    ui->setupUi(this);
    connect(ui->xSlider, SIGNAL(sliderReleased()), SLOT(on_PosChanged()));
    connect(ui->ySlider, SIGNAL(sliderReleased()), SLOT(on_PosChanged()));
    connect(ui->zSlider, SIGNAL(sliderReleased()), SLOT(on_PosChanged()));

    connect(ui->redSlider, SIGNAL(sliderReleased()), SLOT(on_ColorChanged()));
    connect(ui->greenSlider, SIGNAL(sliderReleased()), SLOT(on_ColorChanged()));
    connect(ui->blueSlider, SIGNAL(sliderReleased()), SLOT(on_ColorChanged()));

    ui->redLine->setReadOnly(true);
    ui->greenLine->setReadOnly(true);
    ui->blueLine->setReadOnly(true);

    ui->sliderButton->setVisible(false);
    ui->currentButton->setVisible(false);

    setFixedSize(480, 272);
    setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint);

}

MainDisplay::~MainDisplay()
{
    delete ui;
}


void MainDisplay::on_PosChanged()
{
    MainDisplay::setXYZ *setXYZPtr = new setXYZ((ui->xSlider->value()), (ui->ySlider->value()), (ui->zSlider->value()));

    qDebug() << "Slider values: " << setXYZPtr->x << "," << setXYZPtr->y << "," << setXYZPtr->z;

    //Setting pushbutton position according to screen size. Y-axis is inverted.
    ui->sliderButton->move(((ui->xSlider->value())), (-(((ui->ySlider->value())*0.57)-145)));
    ui->sliderButton->setVisible(true);

}

void MainDisplay::on_calButton_pressed()
{

    //Set x,y,z to the maximum value
    quint8 xMax = 255;
    quint8 yMax = 255;
    quint8 zMax = 255;

    setSendPos.setPacket(&cmdX, &xMax);
    setSendPos.setPacket(&cmdY, &yMax);
    setSendPos.setPacket(&cmdZ, &zMax);

    //Return to original value
    setSendPos.setPacket(&cmdX, &valX);
    setSendPos.setPacket(&cmdY, &valY);
    setSendPos.setPacket(&cmdZ, &valZ);

    on_PosChanged();
}

void MainDisplay::on_goPosButton_pressed()
{

    valX = ui->xSlider->value();
    valY = ui->ySlider->value();
    valZ = ui->zSlider->value();

    setSendPos.setPacket(&cmdX, &valX);
    setSendPos.setPacket(&cmdY, &valY);
    setSendPos.setPacket(&cmdZ, &valZ);

    ui->currentButton->move(((ui->xSlider->value())), (-((ui->ySlider->value()*0.57)-145)));

    qDebug() << "currentpos: " << valX << "," << valY << "," << valZ;

    ui->currentButton->setVisible(true);

    on_PosChanged();
}

void MainDisplay::on_setTestButton_pressed()
{
    unsigned char val=0xaa;
    unsigned char cmdSet=0x98;

    SPIapi spi;

    spi.setPacket(&cmdSet, &val);

    qDebug() << "Sendt kommando: " << cmdSet << ", og val:" << val;
}

void MainDisplay::on_getTestButton_pressed()
{
    unsigned char cmdGet=0x99;
    unsigned int returnVal;
    SPIapi spi;

    spi.getPacket(&cmdGet, &returnVal);

    ui->getTestLine->setText(QString::number(returnVal));

    qDebug() << "Modtaget kommando: " << cmdGet << ", og val:" << returnVal;
}
