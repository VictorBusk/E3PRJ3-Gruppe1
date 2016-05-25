/*!
 * @file        planner.c
 * @brief       General planing management
 * @author      Victor Busk (201409557@post.au.dk)
 */

#include "plannerdialog.h"
#include "ui_display.h"
#include "maindisplay.h"
#include <QtGui>

/***************************************
 *       Public constants
 ****************************************/

int i, column, row = 0;

/***************************************
 *       Public arrays
 ****************************************/

QPushButton *button[4];

unsigned char xPlan[4];
unsigned char yPlan[4];
unsigned char zPlan[4];

unsigned char redPlan[4];
unsigned char greenPlan[4];
unsigned char bluePlan[4];

/*!
 *  @brief      Adds plan on Add-Button-pressed event
 *  @author     Victor Busk (201409557@post.au.dk)
 */

void MainDisplay::on_addButton_pressed()
{
    PlannerDialog dialog(this);
    dialog.setFixedSize(480, 272);
    dialog.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    int flag = 0;

    if((dialog.exec() == QDialog::Accepted))
    {
        flag = 1;
    }
    else
        flag = 0;

    if(i<4 && (dialog.getLineEditText()!="") && flag==1)
    {
                QString text = dialog.getLineEditText();
                QPushButton *item = new QPushButton("New Button");
                button[i] = item;
                button[i]->setText(text);

                xPlan[i] = ui->xSlider->value();
                yPlan[i] = ui->ySlider->value();
                zPlan[i] = ui->zSlider->value();

                redPlan[i] = ui->redSlider->value();
                greenPlan[i] = ui->greenSlider->value();
                bluePlan[i] = ui->blueSlider->value();

                ui->gridLayout->addWidget(button[i],row,column);
                row++;

                connect(button[i], SIGNAL(pressed()), this, SLOT(on_button_pressed()));

                qDebug() << "Setting plan position: x,y,z = " << xPlan[i] << ", " << yPlan[i] << ", " << zPlan[i];
                qDebug() << "Setting plan light: = " << redPlan[i] << ", " << greenPlan[i] << ", " << bluePlan[i];

                i++;
    }

    else if(i>=4)
    {
        qDebug() << "Err: Maximum plan count reached";
    }

    return;
}

/*!
 *  @brief      Checks which button is pressed and sets data accordingly
 *  @author     Victor Busk (201409557@post.au.dk)
 */

void MainDisplay::on_button_pressed()
{

    QObject* obj = sender();
    for(i=0; i<sizeof(button); i++)
    {
        if(obj == button[i])
            break;
    }
        ui->xSlider->setValue(xPlan[i]);
        ui->ySlider->setValue(yPlan[i]);
        ui->zSlider->setValue(zPlan[i]);

        ui->redSlider->setValue(redPlan[i]);
        ui->greenSlider->setValue(greenPlan[i]);
        ui->blueSlider->setValue(bluePlan[i]);

        button[i]->setFocus();

    qDebug() << "Setting according to plan";

}

/*!
 *  @brief      Deletes marked button
 *  @public
 *  @author     Victor Busk (201409557@post.au.dk)
 */

void MainDisplay::on_delButton_pressed()
{
    delete button[i];
}

/* [] END OF FILE */
