#ifndef PLANNERDIALOG_H
#define PLANNERDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QRegExp>
#include "plannerdialog.h"

namespace Ui {
class PlannerDialog;
}

class PlannerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlannerDialog(QWidget *parent = 0);
    //bool eventFilter(QObject* object, QEvent* event);
    void on_buttonBox_accepted();
    void setLineEdits(QString plan);
    QString getLineEditText() const;
    ~PlannerDialog();

signals:
    void planAdded( const QString & plan);

private slots:
    void lineEdit_textChanged();

    //void on_buttonBox_pressed(QAbstractButton *button);

private:
     Ui::PlannerDialog *ui;
};

#endif // PLANNERDIALOG_H
