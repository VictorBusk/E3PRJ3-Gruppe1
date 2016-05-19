/*
 * Copyright 2011 Sigma (http://ultimatewebfree.kinssha.org/)
 *
 * Version : QVirtualKeyboard 0.2
 *
 * This file is part of Virtual Keyboard.
 *
 * Virtual Keyboard is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation
 *
 * Virtual Keyboard is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Virtual Keyboard. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QVIRTUALKEYBOARD_H_INCLUDED
#define QVIRTUALKEYBOARD_H_INCLUDED

#include <QtGui>



class QVirtualKeyboard : public QWidget
{
    Q_OBJECT

    public:
        QVirtualKeyboard(QWidget *parent = 0);

        void mouseReleaseEvent (QMouseEvent * event);
        void resizeEvent(QResizeEvent * event);
        void setKeyboardLayout(int layout);


    private slots:
        void createButtons(void);

        void displayAlphabet(void);
        void displayNumber(void);
        void displaySpecialChar(void);

        void buttonC1Function(void);
        void buttonC2Function(void);
        void buttonC3Function(void);
        void buttonC4Function(void);
        void buttonC5Function(void);
        void buttonC6Function(void);

        void sendChar(int indexOfCharToSend);
        void buttonPressed(int indexOfCharToSend);

        void displayAccentedChar(void);
        void sendAccentedChar(int indexOfCharToSend);




    private:
        QWidget *parentWidget;

// Boutons et signalMapper
        QSignalMapper *signalMapper;
        QSignalMapper *signalMapper2;

        QVector<QPushButton *> button;

        QPushButton *buttonC1;
        QPushButton *buttonC2;
        QPushButton *buttonC3;
        QPushButton *buttonC4;
        QPushButton *buttonC5;
        QPushButton *buttonC6;

        QPushButton *labelDisplayChar;

        QLabel *backgroundLabel;

        QWidget *verticalLayoutWidget;
        QVBoxLayout *mainVerticalLayout;
        QHBoxLayout *horizontalLayout_1;
        QHBoxLayout *horizontalLayout_2;
        QHBoxLayout *horizontalLayout_3;
        QHBoxLayout *horizontalLayout_4;

        QSpacerItem *horizontalSpacer;
        QSpacerItem *horizontalSpacer_2;

        int kw; // Keyboard custom width
        int kh; // Keyboard custom height


        QTimer *pressTimer;
        int lastPressedKey;
        QVector<QPushButton *> AccentedCharButton;
        QSignalMapper *AccentedCharSignalMapper;

        QLabel *backgroundAccentedCharLabel;

        QWidget *verticalLayoutWidget2;
        QHBoxLayout *horizontalLayout;

        int AlphabetLayout; // AZERTY = 1 ou QWERTY = 0

};

#endif // VIRTUALKEYBOARD_H_INCLUDED

