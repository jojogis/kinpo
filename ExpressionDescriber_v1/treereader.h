#ifndef TREEREADER_H
#define TREEREADER_H

#include <QDomDocument>
#include <QJsonObject>
#include <QList>
#include <qstring.h>


struct ExpressionNode{
    QString name;
    QList<ExpressionNode> child;
};
class TreeReader
{
public:

    TreeReader();
    static ExpressionNode readXml(QString filename,QString &error);
    static ExpressionNode readJSON(QString filename,QString &error);
    static ExpressionNode readTree(QString filename,QString &error);
    static ExpressionNode treeWalker(QJsonObject obj);
    static ExpressionNode treeWalkerXml(QDomNode node);
};

#endif // TREEREADER_H
