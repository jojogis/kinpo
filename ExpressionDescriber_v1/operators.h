#ifndef OPERATORS_H
#define OPERATORS_H

#include <qhash.h>



class Operators
{
public:
    Operators();
    QHash<QString,QString> operatorsIDecl;
    QHash<QString,QString> operatorsRDecl;
};

#endif // OPERATORS_H
