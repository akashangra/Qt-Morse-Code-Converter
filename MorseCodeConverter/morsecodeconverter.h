#ifndef MORSECODECONVERTER_H
#define MORSECODECONVERTER_H
#include <QDialog>

//forward declaration
template <typename Left,
          typename Right >
class QBimap;

namespace Ui {
class MorseCodeConverter;
}

class MorseCodeConverter : public QDialog
{
    Q_OBJECT

public:
    //constructor
    MorseCodeConverter(QWidget *parent = nullptr);

    //destructor
    ~MorseCodeConverter();

private slots:
    void on_lineEditAlphabet_textChanged(const QString &arg1);

    void on_lineEditMorseCode_textChanged(const QString &arg1);

private:
    Ui::MorseCodeConverter *_ui; //following the convention of _ with private variables

    //taking pointer because don't want to include the header file here
    /**
     * @brief _mapAlphaVsMorseText : used to store mapping of english letters vs morse text
     * keyfromLeft : Alphabet, keyFromRight : Morse Text
     */
    QBimap<QString,QString> *_mapAlphaVsMorseText;//

    //called from constructor.initializing class variables in this initialize
    void initialize();

};

#endif // MORSECODECONVERTER_H
