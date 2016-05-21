#include "planner.h"
#include "plannerdialog.h"
#include "ui_display.h"
#include "position.h"
#include <QtGui>


QPushButton *button[12];
int i = 1;
int column, row = 0;

void MainDisplay::on_addButton_pressed()
{
    PlannerDialog dialog(this);

    connect( &dialog, SIGNAL( planAdded( const QString &) ), this, SLOT( on_planAdddedChanged( const QString &) ) );
    dialog.exec();

    if(i<=12)
    {
            QPushButton *item = new QPushButton("New Button");
            button[i] = item;
            QString text = dialog.getLineEditText();
            button[i]->setText(text);
            button[i]->resize(10, 10);

            if(column == 3)
            {
                ui->gridLayout->addWidget(button[i],row,column,Qt::AlignLeft);
                column=0;
                row++;
            }
            else
            {
                ui->gridLayout->addWidget(button[i],row,column,Qt::AlignLeft);
                column++;
            }
            i++;
    }

    else
    {
        qDebug() << "Err: Maximum planner count reached";
    }

}

