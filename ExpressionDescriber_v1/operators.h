#ifndef OPERATORS_H
#define OPERATORS_H

#include <qhash.h>
#include "declension.h"
/// Структура, описывающая предлог
struct Preposition{
    Declension::Declensions declPrev;///< падеж предыдущего элемента
    Declension::Declensions declNext;///< падеж следующего элемента
    QString text;///< имя предлога
};
/*!
    \brief Класс, содержащий описания предлогов
*/
class Operators
{
public:
    Operators();
    QHash<QString,QString> operatorsPrepositions;///< соответствующие предлоги для операторов
    QHash<QString,Preposition> prepositions;///< описания предлогов(падежи соседних элемнтов)
    QHash<QString,QString> operatorsIDecl;///< операторы в именительном падеже
    QHash<QString,QString> operatorsRDecl;///< операторы в родительном падеже
    QHash<QString,QString> operatorsVDecl;///< операторы в винительном падеже
    QHash<QString,QString> operatorsTDecl;///< операторы в творительном падеже
    QString getOperatorByDecl(QString name,Declension::Declensions decl);
};

#endif // OPERATORS_H
