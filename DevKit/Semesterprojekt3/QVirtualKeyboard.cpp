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


#include "QVirtualKeyboard.h"

#define defaultWidth    480
#define defaultHeight   110





QVirtualKeyboard::QVirtualKeyboard(QWidget*parent) : QWidget(parent)
{
    parentWidget = parent;      // Stock le pointeur du Widget parent dans parentWidget

    createButtons();            // Méthode qui génère et organise l'affiche des boutons


// Initialise le signalMapper pour les boutons B0 à B25 : Signal clicked()
     signalMapper = new QSignalMapper(this);

     for (int i=0; i<26; i++)
     {
         signalMapper->setMapping(button[i], i);
         connect(button[i], SIGNAL(clicked()), signalMapper, SLOT(map()));
     }

     connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(sendChar(int))); // Envoi le numéro du bouton au slot sendChar



// Initialise le signalMapper pour les boutons B0 à B25 : Signal pressed()
     signalMapper2 = new QSignalMapper(this);

     for (int i=0; i<26; i++)
     {
         signalMapper2->setMapping(button[i], i);
         connect(button[i], SIGNAL(pressed()), signalMapper2, SLOT(map()));
     }

     connect(signalMapper2, SIGNAL(mapped(int)), this, SLOT(buttonPressed(int))); // Envoi le numéro du bouton au slot buttonPressed



// Initialise le signalMapper pour les boutons des caractères accentués : Signal clicked()
    AccentedCharSignalMapper = new QSignalMapper(this);

     for (int i=0; i<10; i++)
     {
         AccentedCharSignalMapper->setMapping(AccentedCharButton[i], i);
         connect(AccentedCharButton[i], SIGNAL(clicked()), AccentedCharSignalMapper, SLOT(map()));
     }

     connect(AccentedCharSignalMapper, SIGNAL(mapped(int)), this, SLOT(sendAccentedChar(int))); // Envoi le numéro du bouton au slot sendAccentedChar




// Connexion des boutons de contrôle C1 à C6
    connect(buttonC1, SIGNAL(clicked()), this, SLOT(buttonC1Function()));
    connect(buttonC2, SIGNAL(clicked()), this, SLOT(buttonC2Function()));
    connect(buttonC3, SIGNAL(clicked()), this, SLOT(buttonC3Function()));
    connect(buttonC4, SIGNAL(clicked()), this, SLOT(buttonC4Function()));
    connect(buttonC5, SIGNAL(clicked()), this, SLOT(buttonC5Function()));
    connect(buttonC6, SIGNAL(clicked()), this, SLOT(buttonC6Function()));



// Connexion du Timer pour l'affichage des caractères accentués
    connect(pressTimer, SIGNAL(timeout()), this, SLOT(displayAccentedChar()));
}




void QVirtualKeyboard::createButtons(void)
{
// Layout par défaut : AZERTY
    AlphabetLayout = 0;

// Taille par défaut
    kw = defaultWidth;
    kh = defaultHeight;
    this->setGeometry(QRect(0, 0, kw, kh/2));
    this->setMinimumSize(50,50);


// Arrière plan du clavier
    backgroundLabel = new QLabel("",this);
    backgroundLabel->setStyleSheet(QString::fromUtf8("background-color:rgb(105, 105, 105);"));
    backgroundLabel->setGeometry(QRect(0, 0, kw, kh/2));
    backgroundLabel->show();


// Déclaration des 26 boutons centraux qui contiennent des caractères. Les QPushButton sont stockés dans un QVector
    for(int i=0; i < 26; i++)
    {
        button.append(new QPushButton(".", this));
        button[i]->setFocusPolicy(Qt::NoFocus);     // Pas de focus sur ces boutons
    }


// Widget qui contient le layout principal vertical
    verticalLayoutWidget = new QWidget(this);
    verticalLayoutWidget->setGeometry(QRect(0, 0, kw, kh/2));


// Laypout principal vertical
    mainVerticalLayout = new QVBoxLayout(verticalLayoutWidget);
    mainVerticalLayout->setSpacing(0);
    mainVerticalLayout->setContentsMargins(0, 0, 0, 0);


// Layout Horizontal 1 -----------------------------------------------
    horizontalLayout_1 = new QHBoxLayout();

    for(int i=0; i < 10; i++)
    {
        horizontalLayout_1->addWidget(button[i]); // Ajoute les boutons B0 à B9 au layout horizontal 1
    }

    mainVerticalLayout->addLayout(horizontalLayout_1); // Ajoute le layout horizontal 1 au layout vertical


// Layout Horizontal 2 -----------------------------------------------
    horizontalLayout_2 = new QHBoxLayout();

    for(int i=10; i < 20; i++)
    {
        horizontalLayout_2->addWidget(button[i]); // Ajoute les boutons B10 à B19 au layout horizontal 2
    }

    mainVerticalLayout->addLayout(horizontalLayout_2); // Ajoute le layout horizontal 2 au layout vertical


// Layout Horizontal 3 -----------------------------------------------
    horizontalLayout_3 = new QHBoxLayout();

    buttonC1 = new QPushButton(this);
    buttonC1->setFocusPolicy(Qt::NoFocus);          // Pas de focus
    horizontalLayout_3->addWidget(buttonC1);        // Ajoute le bouton C1 au layout horizontal 3

    horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    horizontalLayout_3->addItem(horizontalSpacer);

    for(int i=20; i < 26; i++)
    {
        horizontalLayout_3->addWidget(button[i]);   // Ajoute les boutons B20 à B25 au layout horizontal 3
    }


    horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);
    horizontalLayout_3->addItem(horizontalSpacer_2);

    buttonC2 = new QPushButton(QIcon(":/icon/delArrow.png"), " ", this);
    buttonC2->setFocusPolicy(Qt::NoFocus);          // Pas de focus
    horizontalLayout_3->addWidget(buttonC2);        // Ajoute le bouton C2 au layout horizontal 3


    mainVerticalLayout->addLayout(horizontalLayout_3); // Ajoute le layout horizontal 3 au layout vertical


// Layout Horizontal 4 -----------------------------------------------
    horizontalLayout_4 = new QHBoxLayout();

    buttonC3 = new QPushButton(this);
    buttonC3->setFocusPolicy(Qt::NoFocus);              // Pas de focus
    buttonC3->setMaximumSize(QSize(kw*19/100, 16777215));
    horizontalLayout_4->addWidget(buttonC3);

    buttonC4 = new QPushButton("Space", this);
    buttonC4->setFocusPolicy(Qt::NoFocus);              // Pas de focus
    horizontalLayout_4->addWidget(buttonC4);

    buttonC5 = new QPushButton("Hide", this);
    buttonC5->setFocusPolicy(Qt::NoFocus);              // Pas de focus
    buttonC5->setMaximumSize(QSize(kw*19/100, 16777215));
    horizontalLayout_4->addWidget(buttonC5);

    buttonC6 = new QPushButton("Enter", this);
    buttonC6->setFocusPolicy(Qt::NoFocus);              // Pas de focus
    buttonC6->setMaximumSize(QSize(kw*19/100, 16777215));
    horizontalLayout_4->addWidget(buttonC6);

    mainVerticalLayout->addLayout(horizontalLayout_4);


// Etiquette qui affiche la lettre appyuée
    labelDisplayChar = new QPushButton("", parentWidget);
    labelDisplayChar->hide();


// initialise les boutons de contrôle
    buttonC3->setText(QString(".?123"));
    buttonC1->setText(QString(" "));
    buttonC1->setIcon(QIcon(":/icon/arrow.png"));
    buttonC1->setCheckable(true);


// Affiche l'alphabet
    displayAlphabet();


// Initialisation des boutons pour les caractères accentués
    for(int i = 0; i < 10; i++)
    {
        AccentedCharButton.append(new QPushButton("", this));
        AccentedCharButton[i]->setFocusPolicy(Qt::NoFocus);     // Pas de focus sur ces boutons
        AccentedCharButton[i]->hide();
    }


// Timer pour les carctères accentués
    pressTimer = new QTimer(this);


// Initialise l'arrière-plan et le layout pour boutons des carctères accentués
    backgroundAccentedCharLabel = new QLabel("",parentWidget);
    verticalLayoutWidget2 = new QWidget(parentWidget);
    horizontalLayout = new QHBoxLayout(verticalLayoutWidget2);
    horizontalLayout->setContentsMargins(5, 0, 5, 0);
    horizontalLayout->setSpacing(1);

    return;
}



void QVirtualKeyboard::displayAlphabet(void) // Affiche l'alphabet
{
    if(AlphabetLayout)  // Si AlphabetLayout == 1 : Mode AZERTY
    {
        unsigned char azerty[] = {'A', 'Z', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'Q', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'W', 'X', 'C', 'V', 'B', 'N'};

        for(int i=0; i < 26; i++)
        {
            button[i]->setText(QChar::fromAscii(azerty[i]));
        }
    }
    else  // Sinon AlphabetLayout Mode QWERTY
    {
        unsigned char qwerty[] = {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 'X', 'C', 'V', 'B', 'N', 'M'};

        // Décale le bouton B19
        horizontalLayout_2->removeWidget(button[19]);
        horizontalLayout_3->insertWidget(2, button[19]);


        for(int i=0; i < 26; i++)
        {
            button[i]->setText(QChar::fromAscii(qwerty[i]));
        }
    }

    return;
}



void QVirtualKeyboard::displayNumber(void) // Affiche les nombres
{
    if(!AlphabetLayout) // Si on est en mode QWERTY, on décale le bouton B19
    {
        horizontalLayout_3->removeWidget(button[19]);
        horizontalLayout_2->addWidget(button[19]);
    }

    unsigned short int number[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '/', ':', ';', '(', ')', 0x20ac, '&', '@', '"', '.', ',', '?', '!', 39, 0x00B2};

    for(int i=0; i < 26; i++)
    {
        if(number[i] != '&')
        {
            button[i]->setText(QChar(number[i]));
        }
        else
        {
            button[i]->setText(QString(QChar(number[i]))+QString(QChar(number[i]))); // Pour le symbole "&", il faut en insérer deux pour qu'il apparaisse
        }
    }

    return;
}



void QVirtualKeyboard::displaySpecialChar(void) // Affiche les caractères spéciaux
{
    unsigned char SpecialChar[] = {'[', ']', '{', '}', '#', '%', '^', '*', '+', '=', '_', '\\', '|', '~', '<', '>', '$', '£', '¥', '¤', '.', ',', '?', '!', '\'', '°'};

    for(int i=0; i < 26; i++)
    {
        button[i]->setText(QChar::fromAscii(SpecialChar[i]));
    }

    return;
}



void QVirtualKeyboard::buttonC1Function(void) // Contrôle le bouton C1
{
    if(buttonC3->text() == QString("ABC"))
    {
        if(buttonC1->text() == QString("#+="))
        {
            buttonC1->setText(QString("123"));
            buttonC1->setCheckable(false);
            displaySpecialChar();
        }
        else
        {
            buttonC1->setText(QString("#+="));
            buttonC1->setIcon(QIcon(""));
            buttonC1->setCheckable(false);
            displayNumber();
        }
    }

    return;
}



void QVirtualKeyboard::buttonC2Function(void) // Contrôle le bouton C2 - BackSpace
{
    QApplication::sendEvent(parentWidget->focusWidget(), new QKeyEvent(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier, QString(QChar(0x0008))));
    return;
}



void QVirtualKeyboard::buttonC3Function(void) // Contrôle le bouton C3
{
    if(buttonC3->text() == QString(".?123"))
    {
        buttonC3->setText(QString("ABC"));
        buttonC1->setText(QString("#+="));
        buttonC1->setIcon(QIcon(""));
        buttonC1->setCheckable(false);
        displayNumber();
    }
    else
    {
        buttonC3->setText(QString(".?123"));
        buttonC1->setText(QString(" "));
        buttonC1->setIcon(QIcon(":/icon/arrow.png"));
        buttonC1->setCheckable(true);
        displayAlphabet();
    }

    return;
}



void QVirtualKeyboard::buttonC4Function(void) // Contrôle le bouton C4 - Espace
{
   QApplication::sendEvent(parentWidget->focusWidget(), new QKeyEvent(QEvent::KeyPress, ' ', Qt::NoModifier, QString(" ")));
    return;
}



void QVirtualKeyboard::buttonC5Function(void) // Contrôle le bouton C5
{
    this->hide();
    return;
}



void QVirtualKeyboard::buttonC6Function(void) // Contrôle le bouton C6 - Entrer
{
    QApplication::sendEvent(parentWidget->focusWidget(), new QKeyEvent(QEvent::KeyPress, Qt::Key_Enter, Qt::NoModifier, QString(QChar(13))+QString(QChar(13))));
    return;
}



void QVirtualKeyboard::sendChar(int indexOfCharToSend) // Envoit le caractère appuyé au widget qui a le focus
{
    pressTimer->stop(); // On arrête le timer pour que le siganl de timeout ne soit pas emis

    if(verticalLayoutWidget2->isVisible())  // Si les caractère accentués sont affiché, on envoie pas le caractère
    {
        return;
    }

    QChar charToSend(button[indexOfCharToSend]->text().at(0));

    if(!buttonC1->isChecked() && buttonC3->text() == QString(".?123"))
    {
        QApplication::sendEvent(parentWidget->focusWidget(), new QKeyEvent(QEvent::KeyPress, charToSend.toLower().unicode(), Qt::NoModifier, QString(charToSend.toLower())));
    }
    else
    {
        QApplication::sendEvent(parentWidget->focusWidget(), new QKeyEvent(QEvent::KeyPress, charToSend.unicode(), Qt::NoModifier, QString(charToSend)));
    }


    labelDisplayChar->hide();   // Enlève l'étiquette du bouton appuyé

    return;
}



void QVirtualKeyboard::buttonPressed(int indexOfCharToSend) // Affiche l'étiquette du bouton appuyé
{
    if(!buttonC1->isChecked())  // Si on est pas en mode majuscule, on démarre le timer
    {
        pressTimer->start(1000);
    }

    backgroundAccentedCharLabel->hide();    // On cache les carctères accentués
    verticalLayoutWidget2->hide();          // On cache les carctères accentués

    lastPressedKey = indexOfCharToSend;     // On stocke le numéro du bouton appuyé dans une variable

    if(!buttonC1->isChecked() && buttonC3->text() == QString(".?123"))
    {
        labelDisplayChar->setText(QString(button[indexOfCharToSend]->text()).toLower());
    }
    else
    {
        labelDisplayChar->setText(QString(button[indexOfCharToSend]->text()));
    }

    labelDisplayChar->setEnabled(false);

    QFont font;
    font.setPointSize(14);
    font.setBold(true);
    font.setWeight(75);
    labelDisplayChar->setFont(font);

    QRect pos(button[indexOfCharToSend]->x()+button[indexOfCharToSend]->width()/2-32/2+this->x(), button[indexOfCharToSend]->y()-3-32+this->y(), 32, 32);
    labelDisplayChar->setGeometry(pos);
    labelDisplayChar->setAutoFillBackground(false);
    labelDisplayChar->show();

    return;
}




void QVirtualKeyboard::resizeEvent ( QResizeEvent * event )
{
    event->accept();

    kw = event->size().width();
    kh = event->size().height();

    backgroundLabel->resize(kw, kh);
    verticalLayoutWidget->resize(kw, kh);
    buttonC3->setMaximumSize(QSize(kw*19/100, 16777215));
    buttonC5->setMaximumSize(QSize(kw*19/100, 16777215));
    buttonC6->setMaximumSize(QSize(kw*19/100, 16777215));

    return;
}



void QVirtualKeyboard::displayAccentedChar(void) // Affiche les caractères accentués
{
    QChar pressedKey(button[lastPressedKey]->text().at(0)); // Récupère le caractère du bouton appuyé

    QString AccentedCharString;

    if(pressedKey == QChar('A'))
    {
        AccentedCharString = "àâäã";
    }
    else if(pressedKey == QChar('C'))
    {
        AccentedCharString = "ç";
    }
    else if(pressedKey == QChar('E'))
    {
        AccentedCharString = "éèêë";
    }
    else if(pressedKey == QChar('I'))
    {
        AccentedCharString = "îï";
    }
    else if(pressedKey == QChar('N'))
    {
        AccentedCharString = "ñ";
    }
    else if(pressedKey == QChar('O'))
    {
        AccentedCharString = "ôö";
    }
    else if(pressedKey == QChar('U'))
    {
        AccentedCharString = "ùûüµ";
    }
    else if(pressedKey == QChar('Y'))
    {
        AccentedCharString = "ÿ";
    }
    else
    {
        return;
    }


    labelDisplayChar->hide();                               // Cache l'étiquette du bouton appuyé
    pressTimer->stop();                                     // Arrête le timer



    int width = this->width()*6/100*AccentedCharString.size();
    if(width < 4+22*AccentedCharString.size())
    {
        width = 4+22*AccentedCharString.size();
    }


// Arrière plan pour les caractères accentués
    backgroundAccentedCharLabel->setStyleSheet(QString::fromUtf8("background-color:rgb(230, 230, 230);border: 2px solid #8f8f91;border-radius: 10px;"));
    backgroundAccentedCharLabel->setGeometry(QRect(button[lastPressedKey]->x()+this->x(), button[lastPressedKey]->y()-15*button[lastPressedKey]->height()/10-3+this->y(), width, 15*button[lastPressedKey]->height()/10));
    backgroundAccentedCharLabel->show();


// Widget qui contient le layout
    verticalLayoutWidget2->setGeometry(QRect(button[lastPressedKey]->x()+this->x(), button[lastPressedKey]->y()-15*button[lastPressedKey]->height()/10-3+this->y(), width, 15*button[lastPressedKey]->height()/10));
    verticalLayoutWidget2->show();



// Supprime tous les boutons du layout
    for(int i = 0; i < AccentedCharButton.size(); i++)
    {
        horizontalLayout->removeWidget(AccentedCharButton[i]);
        AccentedCharButton[i]->hide();
    }



// Ajoute les boutons au layout
    for(int i = 0; i < AccentedCharString.size(); i++)
    {
        AccentedCharButton[i]->setText(AccentedCharString.at(i));
        horizontalLayout->addWidget(AccentedCharButton[i]); // Ajoute les boutons B0 à B9 au layout horizontal 1
        AccentedCharButton[i]->show();
    }


    return;
}



void QVirtualKeyboard::sendAccentedChar(int indexOfCharToSend)
{
    QChar charToSend(AccentedCharButton[indexOfCharToSend]->text().at(0));

    QApplication::sendEvent(parentWidget->focusWidget(), new QKeyEvent(QEvent::KeyPress, charToSend.unicode(), Qt::NoModifier, QString(charToSend)));

    backgroundAccentedCharLabel->hide();
    verticalLayoutWidget2->hide();

    return;
}



void QVirtualKeyboard::mouseReleaseEvent(QMouseEvent * event)
{
    event->accept();
    labelDisplayChar->hide();   // Enlève l'étiquette du bouton appuyé
    return;
}




void QVirtualKeyboard::setKeyboardLayout(int layout)
{
    AlphabetLayout = layout;

    if(buttonC3->text() == QString(".?123"))    // Si l'alphabet est affiché, on met à jour le layout
    {
        displayAlphabet();
    }

    return;
}



