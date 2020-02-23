#include "treereader.h"

#include <QFile>
#include <qjsondocument.h>
#include <QJsonArray>
#include <QFileInfo>
TreeReader::TreeReader()
{

}
/*!
 * Читает дерево разбора выражения из файла xml/json
 * \param [in] filename - имя файла
 * \param [out] error - строка с ошибкой
 * \return дерево разбора
*/
ExpressionNode TreeReader::readTree(QString filename,QString &error){
    //читаем файл
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        error = file.errorString();
        throw 2;
    }
    QString data = file.readAll();

    //проверяем формат
    QFileInfo info(filename);
    if(info.completeSuffix() == "json"){
        return readJSON(data,error);
    }else if(info.completeSuffix() == "xml"){
        return readXml(data,error);
    }else{
        throw 1;
    }

}
/*!
 * Читает дерево разбора выражения из файла xml
 * \param [in] filename - имя файла
 * \param [out] error - строка с ошибкой
 * \return дерево разбора
*/
ExpressionNode TreeReader::readXml(QString data,QString &error){
    QDomDocument doc("doc");
    int errorLine;int errorColumn;
    if (!doc.setContent(data,&error,&errorLine,&errorColumn)) {
        error += " on "+QString::number(errorLine)+":"+QString::number(errorColumn);
        throw 3;
    }
    QDomNode n = doc.documentElement();
    return treeWalkerXml(n);
}
/*!
 * Читает дерево разбора выражения из файла json
 * \param [in] filename - имя файла
 * \param [out] error - строка с ошибкой
 * \return дерево разбора
*/
ExpressionNode TreeReader::readJSON(QString data,QString &error){
    // Создаём QJsonDocument
    QJsonParseError parseError;
    QJsonDocument jsonDocument(QJsonDocument::fromJson(data.toUtf8(),&parseError));
    if(jsonDocument.isNull()){
        error = parseError.errorString()+" on "+QString::number(parseError.offset);
        throw 3;
    }
    // Из которого выделяем объект в текущий рабочий QJsonObject
    ExpressionNode root;
    return treeWalker(jsonDocument.object());
}

ExpressionNode TreeReader::treeWalkerXml(QDomNode node){
    ExpressionNode nodeRes;

    if(node.hasChildNodes()){
        QDomNodeList childs = node.childNodes();
        for(int i = 0; i< childs.count();i++){
            nodeRes.child.append(treeWalkerXml(childs.at(i)));
        }

    }
    nodeRes.name = node.toElement().attribute("name");
    return nodeRes;
}

ExpressionNode TreeReader::treeWalker(QJsonObject obj){
    ExpressionNode node;
    node.name = obj.value("content").toString();
    if(obj.value("child") != QJsonValue::Undefined){
        for(int i = 0;i < obj.value("child").toArray().count();i++){
            node.child.append(treeWalker(obj.value("child").toArray().takeAt(i).toObject()));
        }
    }
    return node;
}
