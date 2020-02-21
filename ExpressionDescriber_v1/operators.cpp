#include "operators.h"

Operators::Operators()
{
    prepositions.insert("и",{Declension::R,Declension::R,"и"});
    prepositions.insert("на",{Declension::R,Declension::V,"на"});
    prepositions.insert("над",{Declension::T,Declension::T,"и"});
    prepositions.insert("унарный",{Declension::R,Declension::R,""});
    prepositions.insert("индекс",{Declension::R,Declension::R,"с индексом"});

    operatorsPrepositions.insert("+","и");
    operatorsPrepositions.insert("-","и");
    operatorsPrepositions.insert("/","и");
    operatorsPrepositions.insert("*","на");
    operatorsPrepositions.insert("%","на");
    operatorsPrepositions.insert("<<","на");
    operatorsPrepositions.insert(">>","на");
    operatorsPrepositions.insert("&","над");
    operatorsPrepositions.insert("|","над");
    operatorsPrepositions.insert("^","над");
    operatorsPrepositions.insert("++","унарный");
    operatorsPrepositions.insert("--","унарный");
    operatorsPrepositions.insert("[]","индекс");


    //именительный
    operatorsIDecl.insert("+","сумма");
    operatorsIDecl.insert("-","разность");
    operatorsIDecl.insert("/","частное");
    operatorsIDecl.insert("*","произведение");
    operatorsIDecl.insert("%","остаток от деления");
    operatorsIDecl.insert("<<","результат побитового сдвига влево");
    operatorsIDecl.insert(">>","результат побитового сдвига вправо");
    operatorsIDecl.insert("&","результат побитового И над");
    operatorsIDecl.insert("|","результат побитового ИЛИ над");
    operatorsIDecl.insert("^","результат побитового исключающего ИЛИ над");
    operatorsIDecl.insert("++","инкремент");
    operatorsIDecl.insert("--","декремент");
    operatorsIDecl.insert("[]","элемент");

    //родительный
    operatorsRDecl.insert("+","суммы");
    operatorsRDecl.insert("-","разности");
    operatorsRDecl.insert("/","частного");
    operatorsRDecl.insert("*","произведения");
    operatorsRDecl.insert("%","остатка от деления");
    operatorsRDecl.insert("<<","результата побитового сдвига влево");
    operatorsRDecl.insert(">>","результата побитового сдвига вправо");
    operatorsRDecl.insert("&","результата побитового И над");
    operatorsRDecl.insert("|","результата побитового ИЛИ над");
    operatorsRDecl.insert("^","результата побитового исключающего ИЛИ над");
    operatorsRDecl.insert("++","инкремента");
    operatorsRDecl.insert("--","декремента");
    operatorsRDecl.insert("[]","элемента");

    //винительный
    operatorsVDecl.insert("+","сумму");
    operatorsVDecl.insert("-","разность");
    operatorsVDecl.insert("/","частное");
    operatorsVDecl.insert("*","произведение");
    operatorsVDecl.insert("%","остаток от деления");
    operatorsVDecl.insert("<<","результат побитового сдвига влево");
    operatorsVDecl.insert(">>","результат побитового сдвига вправо");
    operatorsVDecl.insert("&","результат побитового И над");
    operatorsVDecl.insert("|","результат побитового ИЛИ над");
    operatorsVDecl.insert("^","результат побитового исключающего ИЛИ над");
    operatorsVDecl.insert("++","инкремент");
    operatorsVDecl.insert("--","декремент");
    operatorsVDecl.insert("[]","элемент");

    //творительный
    operatorsTDecl.insert("+","суммой");
    operatorsTDecl.insert("-","разностью");
    operatorsTDecl.insert("/","частным");
    operatorsTDecl.insert("*","произведением");
    operatorsTDecl.insert("%","остатоком от деления");
    operatorsTDecl.insert("<<","результатом побитового сдвига влево");
    operatorsTDecl.insert(">>","результатом побитового сдвига вправо");
    operatorsTDecl.insert("&","результатом побитового И над");
    operatorsTDecl.insert("|","результатом побитового ИЛИ над");
    operatorsTDecl.insert("^","результатом побитового исключающего ИЛИ над");
    operatorsTDecl.insert("++","инкрементом");
    operatorsTDecl.insert("--","декрементом");
    operatorsTDecl.insert("[]","элементом");
}

QString Operators::getOperatorByDecl(QString name,Declension::Declensions decl){
    switch(decl){
        case Declension::I:
            return operatorsIDecl.value(name);
        case Declension::R:
            return operatorsRDecl.value(name);
        case Declension::V:
            return operatorsVDecl.value(name);
        case Declension::T:
            return operatorsTDecl.value(name);
    }
    return "";
}
