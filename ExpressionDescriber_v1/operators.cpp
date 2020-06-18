/*!
     \file
    \brief Класс, содержащий описания предлогов
*/
#include "operators.h"

Operators::Operators()
{
    prepositions.insert("и",{Declension::R,Declension::R,"и"});
    prepositions.insert("на",{Declension::R,Declension::V,"на"});
    prepositions.insert("над",{Declension::T,Declension::T,"и"});
    prepositions.insert("унарный",{Declension::R,Declension::R,""});
    prepositions.insert("индекс",{Declension::R,Declension::R,"с индексом"});
    prepositions.insert("присвоить",{Declension::D,Declension::R,"значение"});

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
    operatorsPrepositions.insert("=","присвоить");
    operatorsPrepositions.insert("*=","присвоить");
    operatorsPrepositions.insert("/=","присвоить");
    operatorsPrepositions.insert("+=","присвоить");
    operatorsPrepositions.insert("-=","присвоить");
    operatorsPrepositions.insert("!","унарный");
    operatorsPrepositions.insert("&","унарный");
    operatorsPrepositions.insert("~","унарный");
    operatorsPrepositions.insert("*","унарный");
    operatorsPrepositions.insert("==","и");
    operatorsPrepositions.insert("!=","и");
    operatorsPrepositions.insert(">","и");
    operatorsPrepositions.insert("<","и");
    operatorsPrepositions.insert("&&","и");
    operatorsPrepositions.insert("||","и");



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
    operatorsIDecl.insert("=","присвоить");
    operatorsIDecl.insert("*=","присвоить с умножением");
    operatorsIDecl.insert("/=","присвоить с делением");
    operatorsIDecl.insert("+=","присвоить с суммированием");
    operatorsIDecl.insert("-=","присвоить с разностью");
    operatorsIDecl.insert("!","отрицание");
    operatorsIDecl.insert("&","адрес");
    operatorsIDecl.insert("~","результат побитового отрицания над");
    operatorsIDecl.insert("*","элемент по адресу");
    operatorsIDecl.insert("==","результат сравнения 'равно'");
    operatorsIDecl.insert("!=","результат сравнения 'неравно'");
    operatorsIDecl.insert(">","результат сравнения 'больше'");
    operatorsIDecl.insert("<","результат сравнения 'меньше'");
    operatorsIDecl.insert("&&","результат логического И");
    operatorsIDecl.insert("||","результат логического ИЛИ");

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
    operatorsRDecl.insert("!","отрицания");
    operatorsRDecl.insert("&","адреса");
    operatorsRDecl.insert("~","результата побитового отрицания над");
    operatorsRDecl.insert("*","элемента по адресу");
    operatorsRDecl.insert("==","результата сравнения 'равно'");
    operatorsRDecl.insert("!=","результата сравнения 'неравно'");
    operatorsRDecl.insert(">","результата сравнения 'больше'");
    operatorsRDecl.insert("<","результата сравнения 'меньше'");
    operatorsRDecl.insert("&&","результата логического И");
    operatorsRDecl.insert("||","результата логического ИЛИ");

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
    operatorsVDecl.insert("!","отрицание");
    operatorsVDecl.insert("&","адрес");
    operatorsVDecl.insert("~","результат побитового отрицания над");
    operatorsVDecl.insert("*","элемент по адресу");
    operatorsVDecl.insert("==","результат сравнения 'равно'");
    operatorsVDecl.insert("!=","результат сравнения 'неравно'");
    operatorsVDecl.insert(">","результат сравнения 'больше'");
    operatorsVDecl.insert("<","результат сравнения 'меньше'");
    operatorsVDecl.insert("&&","результат логического И");
    operatorsVDecl.insert("||","результат логического ИЛИ");

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
    operatorsTDecl.insert("!","отрицанием");
    operatorsTDecl.insert("&","адресом");
    operatorsTDecl.insert("~","результатом побитового отрицания над");
    operatorsTDecl.insert("*","элементом по адресу");
    operatorsTDecl.insert("==","результатом сравнения 'равно'");
    operatorsTDecl.insert("!=","результатом сравнения 'неравно'");
    operatorsTDecl.insert(">","результатом сравнения 'больше'");
    operatorsTDecl.insert("<","результатом сравнения 'меньше'");
    operatorsTDecl.insert("&&","результатом логического И");
    operatorsTDecl.insert("||","результатом логического ИЛИ");
}


/*!
 * Возвращает описание оператора в указанном падеже
 * \param [in] name - оператор
 * \param [in] decl - падеж
 * \return описание оператора
*/
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
