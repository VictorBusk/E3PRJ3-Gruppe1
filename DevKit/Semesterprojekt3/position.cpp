/*!
 * @file        position.cpp
 * @brief       Handles positioning
 * @author      Victor Busk (201409557@post.au.dk)
 */

#include "maindisplay.h"
#include "plannerdialog.h"
#include "spiapi.h"
#include "ui_display.h"
#include <qdebug.h>
#include <QWidget>

/***************************************
 *       Public constants
 ****************************************/

const unsigned char cmdX = 0x10u;
const unsigned char cmdY = 0x11u;
const unsigned char cmdZ = 0x20u;

/*!
 *  @brief      Sets up display startup
 *  @param[in]  parent   QWidget UI setup.
 *  @author     Victor Busk (201409557@post.au.dk)
 */

MainDisplay::MainDisplay(QWidget *parent) : QWidget(parent),
    ui(new Ui::MainDisplay)
{
    ui->setupUi(this);
    connect(ui->xSlider, SIGNAL(valueChanged(int)), SLOT(on_PosChanged()));
    connect(ui->ySlider, SIGNAL(valueChanged(int)), SLOT(on_PosChanged()));
    connect(ui->zSlider, SIGNAL(valueChanged(int)), SLOT(on_PosChanged()));

    connect(ui->redSlider, SIGNAL(valueChanged(int)), SLOT(on_ColorChanged()));
    connect(ui->greenSlider, SIGNAL(valueChanged(int)), SLOT(on_ColorChanged()));
    connect(ui->blueSlider, SIGNAL(valueChanged(int)), SLOT(on_ColorChanged()));

    connect(ui->lumenSlider, SIGNAL(valueChanged(int)), SLOT(on_lumenChanged()));
    connect(ui->distanceSpinBox, SIGNAL(valueChanged(int)), SLOT(on_distanceChanged()));
    connect(ui->movementSlider, SIGNAL(valueChanged(int)), SLOT(on_movementChanged()));

    ui->lumenSlider->setValue(0);

    ui->sliderButton->setVisible(false);
    ui->currentButton->setVisible(false);

    setFixedSize(480, 272);
    setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint);

}

/*!
 *  @brief      Destroys maindisplay-UI when called
 *  @author     Victor Busk (201409557@post.au.dk)
 */

MainDisplay::~MainDisplay()
{
    delete ui;
}

/*!
 *  @brief      Handles movement of position indicators
 *  @author     Victor Busk (201409557@post.au.dk)
 */

void MainDisplay::on_PosChanged()
{

    //Setting pushbutton position according to screen size. Y-axis is inverted.
    ui->sliderButton->move(((ui->xSlider->value())), (-(((ui->ySlider->value())*0.57)-145)));
    ui->sliderButton->setVisible(true);

    qDebug() << "Slider values: " << ui->xSlider->value() << "," << ui->ySlider->value() << "," << ui->zSlider->value();

}

/*!
 *  @brief      Sends position XYZ from sliders on Go-Button-pressed event and updates green indicator
 *  @author     Victor Busk (201409557@post.au.dk)
 */

void MainDisplay::on_goPosButton_pressed()
{

    unsigned char valX = ui->xSlider->value();
    unsigned char valY = ui->ySlider->value();
    unsigned char valZ = ui->zSlider->value();

    setSendPos.setPacket(&cmdX, &valX);
    setSendPos.setPacket(&cmdY, &valY);
    setSendPos.setPacket(&cmdZ, &valZ);

    ui->currentButton->move(((ui->xSlider->value())), (-((ui->ySlider->value()*0.57)-145)));

    qDebug() << "currentpos: " << valX << "," << valY << "," << valZ;

    ui->currentButton->setVisible(true);
}

/* [] END OF FILE */
