#include "operators.h"

Operators::Operators()
{
    prepositions.insert("и",{Declension::R,Declension::R});
    prepositions.insert("на",{Declension::R,Declension::V});

    operatorsPrepositions.insert("+","и");
    operatorsPrepositions.insert("-","и");
    operatorsPrepositions.insert("/","и");
    operatorsPrepositions.insert("*","на");
    operatorsPrepositions.insert("%","на");
    operatorsPrepositions.insert("<<","на");
    operatorsPrepositions.insert(">>","на");
    operatorsPrepositions.insert("&","и");
    operatorsPrepositions.insert("|","и");

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

    operatorsVDecl.insert("+","сумму");
    operatorsVDecl.insert("-","разность");
    operatorsVDecl.insert("/","частное");
    operatorsVDecl.insert("*","произведение");
    operatorsVDecl.insert("%","остаток от деления");
    operatorsVDecl.insert("<<","результат побитового сдвига влево");
    operatorsVDecl.insert(">>","результат побитового сдвига вправо");
    operatorsVDecl.insert("&","результат побитового И");
    operatorsVDecl.insert("|","результат побитового ИЛИ");
}

QString Operators::getOperatorByDecl(QString name,Declension::Declensions decl){
    switch(decl){
        case Declension::I:
            return operatorsIDecl.value(name);
        case Declension::R:
            return operatorsRDecl.value(name);
        case Declension::V:
            return operatorsVDecl.value(name);
    }

}
