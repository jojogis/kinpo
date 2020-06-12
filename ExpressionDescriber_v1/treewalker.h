#ifndef TREEWALKER_H
#define TREEWALKER_H

#include "declension.h"
#include "operators.h"
#include "treereader.h"

#include <QString>


/*!
    \brief Класс, инкапсулирующий обход дерева и составление описания
*/
class TreeWalker
{
public:
    bool useDecl = false;///< флаг использования склонения
    QHash<QString,QString> desc;///< описание элементов
    Declension decl;
    Operators operators;
    QHash<QString,QStringList> funcDesc;///< описание фукнций
    TreeWalker();
    QString treeWalker(ExpressionNode obj,Declension::Declensions currentDecl);
};

#endif // TREEWALKER_H
