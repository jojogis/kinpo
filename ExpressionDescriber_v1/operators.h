#ifndef OPERATORS_H
#define OPERATORS_H

#include <qhash.h>
#include "declension.h"

struct Preposition{
    Declension::Declensions declPrev;
    Declension::Declensions declNext;
    QString text;
};
class Operators
{
public:
    Operators();
    QHash<QString,QString> operatorsPrepositions;
    QHash<QString,Preposition> prepositions;
    QHash<QString,QString> operatorsIDecl;
    QHash<QString,QString> operatorsRDecl;
    QHash<QString,QString> operatorsVDecl;
    QHash<QString,QString> operatorsTDecl;
    QString getOperatorByDecl(QString name,Declension::Declensions decl);
};

#endif // OPERATORS_H
