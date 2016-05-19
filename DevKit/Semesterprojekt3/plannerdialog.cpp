#include "plannerdialog.h"
#include "ui_plannerdialog.h"
#include <QCommandLinkButton>
#include <QHBoxLayout>
#include <QWidget>
#include <QEvent>


PlannerDialog::PlannerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlannerDialog)
{
    ui->setupUi(this);
    connect(ui->planLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(lineEdit_textChanged()));
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(pressed()), SLOT(on_buttonBox_pressed()));
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    ui->planLineEdit->installEventFilter(this);
}

//bool PlannerDialog::eventFilter(QObject* object, QEvent* event)
//{
//    if(object == ui->planLineEdit && event->type() == QEvent::MouseButtonPress) {
//        // bring up your custom edit
//        return false; // lets the event continue to the edit
//    }
//    return false;
//}

void PlannerDialog::lineEdit_textChanged()
{
    ui->planLineEdit->setMaxLength(12);

    QString planString = ui->planLineEdit->text();

    if (planString.isEmpty()) // If the user has typed enable OK
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    else
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

QString PlannerDialog::getLineEditText() const
{
    QString plan = ui->planLineEdit->text();
    return plan;
}

void PlannerDialog::on_buttonBox_accepted()
{
    emit planAdded(ui->planLineEdit->text());
}

void PlannerDialog::setLineEdits(QString plan)
{
    ui->planLineEdit->setText(plan);
}


PlannerDialog::~PlannerDialog()
{
    delete ui;
}

