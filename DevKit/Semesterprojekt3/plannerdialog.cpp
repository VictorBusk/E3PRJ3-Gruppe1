/*!
 * @file        light.cpp
 * @brief       Displaying and managing dialog-UI input
 * @author      Victor Busk (201409557@post.au.dk)
 */

#include "plannerdialog.h"
#include "ui_plannerdialog.h"
#include <QWidget>

/*!
 *  @brief      Sets up dialog startup
 *  @param[in]  parent   QWidget UI setup.
 *  @author     Victor Busk (201409557@post.au.dk)
 */

PlannerDialog::PlannerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlannerDialog)
{
    ui->setupUi(this);

    connect(ui->planLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(lineEdit_textChanged()));

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->planLineEdit->setFocus();

}

/*!
 *  @brief      Set restrictions of textinput and ok-button visibility
 *  @author     Victor Busk (201409557@post.au.dk)
 */

void PlannerDialog::lineEdit_textChanged()
{
    ui->planLineEdit->setMaxLength(8);
    QString planString = ui->planLineEdit->text();

    if (planString.isEmpty()) // If the user has typed enable OK
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    else
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

/*!
 *  @brief      Return textinput for futher usage
 *  @author     Victor Busk (201409557@post.au.dk)
 */

QString PlannerDialog::getLineEditText() const
{
    QString plan = ui->planLineEdit->text();
    return plan;
}

/*!
 *  @brief      Destroys dialog-UI when called
 *  @author     Victor Busk (201409557@post.au.dk)
 */

PlannerDialog::~PlannerDialog()
{
    delete ui;
}

/* [] END OF FILE */

