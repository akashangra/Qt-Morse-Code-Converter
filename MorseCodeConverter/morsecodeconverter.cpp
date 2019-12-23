#include "morsecodeconverter.h"
#include <ui_morsecodeconverter.h>
#include <QBimap.h> //including template created bimap
#include <QRegExpValidator>

MorseCodeConverter::MorseCodeConverter(QWidget *parent)
    :QDialog(parent),
      _ui(new Ui::MorseCodeConverter ),
      _mapAlphaVsMorseText(new QBimap<QString,QString>())
{
    _ui->setupUi(this);
    initialize();
}

MorseCodeConverter::~MorseCodeConverter()
{
    delete _mapAlphaVsMorseText;
    delete _ui;
}

void MorseCodeConverter::initialize()
{
    //initializing two-way hash
    _mapAlphaVsMorseText->insert("A",".-");
    _mapAlphaVsMorseText->insert("B","-...");
    _mapAlphaVsMorseText->insert("C","-.-.");
    _mapAlphaVsMorseText->insert("D","-..");
    _mapAlphaVsMorseText->insert("E",".");
    _mapAlphaVsMorseText->insert("F","..-");
    _mapAlphaVsMorseText->insert("G","--.");
    _mapAlphaVsMorseText->insert("H","....");
    _mapAlphaVsMorseText->insert("I","..");
    _mapAlphaVsMorseText->insert("J",".---");
    _mapAlphaVsMorseText->insert("K","-.-");
    _mapAlphaVsMorseText->insert("L",".-..");
    _mapAlphaVsMorseText->insert("M","--");
    _mapAlphaVsMorseText->insert("N","-.");
    _mapAlphaVsMorseText->insert("O","---");
    _mapAlphaVsMorseText->insert("P",".--.");
    _mapAlphaVsMorseText->insert("Q","--.-");
    _mapAlphaVsMorseText->insert("R",".-.");
    _mapAlphaVsMorseText->insert("S","...");
    _mapAlphaVsMorseText->insert("T","-");
    _mapAlphaVsMorseText->insert("U","..-");
    _mapAlphaVsMorseText->insert("V","...-");
    _mapAlphaVsMorseText->insert("W",".--");
    _mapAlphaVsMorseText->insert("X","-..-");
    _mapAlphaVsMorseText->insert("Y","-.--");
    _mapAlphaVsMorseText->insert("Z","--..");

    //eq. akash (allowed only alphabets)
    _ui->lineEditAlphabet->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]*"), this ) );

    //eg. .- -.- .- ... .... (allowed only morse text space seperated)
    _ui->lineEditMorseCode->setValidator(new QRegExpValidator(QRegExp("([-.]+[ ]?[-.]*)*"), this ) );

}


void MorseCodeConverter::on_lineEditAlphabet_textChanged(const QString &arg1)
{
    QString morseCodeText;
    QString alphaText = arg1.toUpper();//converting input to upper to maintain consistency

    {
        QSignalBlocker signalBlocker( _ui->lineEditMorseCode );
        _ui->lineEditAlphabet->setText( alphaText );//always displaying upper text.but lower allowed to enter
    }

    // don't want to complex the code. More optimization can be done by storing the text once processed
    for(auto ch : alphaText)
    {
        QString morseCurrentText;
        if( _mapAlphaVsMorseText->getRightValue(ch, morseCurrentText ) )
        {
            morseCodeText.append(morseCurrentText + " ");//append with space to maintain consistency
        }
        else
        {
            //if mapping not found exit from loop
            break;
        }
    }

    {
        QSignalBlocker signalBlocker( _ui->lineEditMorseCode ); // to prevent call to on_lineEditMorseCode_textChanged
        _ui->lineEditMorseCode->setText( morseCodeText );
    }
}

void MorseCodeConverter::on_lineEditMorseCode_textChanged(const QString &arg1)
{
    QString alPhaText;
    QStringList morseTextList = arg1.split(" ");//morse text should be entered space seperated to identify the morse code ending

    // don't want to complex the code. More optimization can be done by storing the text once processed
    for(const QString &morseText : morseTextList)
    {
        QString alPhaCurrentText;
        if( _mapAlphaVsMorseText->getLeftValue(morseText, alPhaCurrentText ) )
        {
            alPhaText.append(alPhaCurrentText);
        }
        else
        {
            break;
        }
    }

    {
        QSignalBlocker signalBlocker( _ui->lineEditAlphabet );// blocking signal to avoid call to on_lineEditAlphabet_textChanged
        _ui->lineEditAlphabet->setText( alPhaText );
    }
}
