#ifndef TREEWALKER_H
#define TREEWALKER_H

#include "declension.h"
#include "operators.h"
#include "treereader.h"

#include <QString>



class TreeWalker
{
public:
    bool useDecl = false;
    QHash<QString,QString> desc;
    Declension decl;
    Operators operators;
    QHash<QString,QStringList> funcDesc;
    TreeWalker();
    QString treeWalker(ExpressionNode obj,Declension::Declensions currentDecl);
};

#endif // TREEWALKER_H
