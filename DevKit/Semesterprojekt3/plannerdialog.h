/*!
 * @file        plannerdialog.h
 * @brief       Handles all UI-related in plannerdialog
 * @class       PlannerDialog
 * @author      Victor Busk (201409557@post.au.dk)
 */

#ifndef PLANNERDIALOG_H
#define PLANNERDIALOG_H

#include <QDialog>
#include "plannerdialog.h"

namespace Ui {
class PlannerDialog;
}

class PlannerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlannerDialog(QWidget *parent = 0);
    void setLineEdits(QString plan);
    QString getLineEditText() const;
    ~PlannerDialog();

signals:

private slots:
    void lineEdit_textChanged();

private:
     Ui::PlannerDialog *ui;
};

#endif // PLANNERDIALOG_H

/* [] END OF FILE */
