#include "operators.h"

Operators::Operators()
{
    operatorsIDecl.insert("+","сумма");
    operatorsIDecl.insert("-","разность");
    operatorsIDecl.insert("/","частное");
    operatorsIDecl.insert("*","произведение");
    operatorsIDecl.insert("%","остаток от деления");
    operatorsIDecl.insert("<<","результат побитового сдвига влево");
    operatorsIDecl.insert(">>","результат побитового сдвига вправо");
    operatorsIDecl.insert("&","результат побитового И");
    operatorsIDecl.insert("|","результат побитового ИЛИ");


    operatorsRDecl.insert("+","суммы");
    operatorsRDecl.insert("-","разности");
    operatorsRDecl.insert("/","частного");
    operatorsRDecl.insert("*","произведения");
    operatorsRDecl.insert("%","остатка от деления");
    operatorsRDecl.insert("<<","результата побитового сдвига влево");
    operatorsRDecl.insert(">>","результата побитового сдвига вправо");
    operatorsRDecl.insert("&","результата побитового И");
    operatorsRDecl.insert("|","результата побитового ИЛИ");
}
