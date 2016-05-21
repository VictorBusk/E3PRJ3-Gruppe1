#ifndef LIGHT_H
#define LIGHT_H

#include <QWidget>


class Light : public QWidget
{
    Q_OBJECT

public:
    explicit Light(QWidget *parent = 0);
    QColor color;


private slots:

private:
    QColor rgbColor;
};

#endif // LIGHT_H
