#include <morsecodeconverter.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MorseCodeConverter morseCodeConverter;
    morseCodeConverter.show();
    return a.exec();
}
