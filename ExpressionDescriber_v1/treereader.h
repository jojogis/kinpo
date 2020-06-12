#ifndef TREEREADER_H
#define TREEREADER_H

#include <QDomDocument>
#include <QJsonObject>
#include <QList>
#include <qstring.h>

/// Структура, описывающая вершину
struct ExpressionNode{
    QString name;///< имя элемента или функции
    QList<ExpressionNode> child;///< дочерние вершины
};
/*!
    \brief Класс инкапсулирующий чтение дерева разбора выражения
*/
class TreeReader
{
public:
    TreeReader();
    static ExpressionNode readXml(QString filename,QString &error);
    static ExpressionNode readJSON(QString filename,QString &error);
    static ExpressionNode readTree(QString filename,QString &error);
    static ExpressionNode treeWalkerJSON(QJsonObject obj);
    static ExpressionNode treeWalkerXml(QDomNode node);
};

#endif // TREEREADER_H
