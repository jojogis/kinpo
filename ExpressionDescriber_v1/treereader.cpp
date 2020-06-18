/*!
  \file
    \brief Класс инкапсулирующий чтение дерева разбора выражения
*/
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
 * \throw 2 ошибка открытия файла
 * \throw 1 неподдерживаемый формат
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
    file.close();
    //проверяем формат
    QFileInfo info(filename);
    if(info.suffix() == "json"){
        return readJSON(data,error);
    }else if(info.suffix() == "xml"){
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
 * \throw 3 ошибка разбора xml
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
 * \throw 3 ошибка разбора json
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
    return treeWalkerJSON(jsonDocument.object());
}


/*!
 * Обходит DOM дерево и возвращает дерево разбора в универсальном формате
 * \param [in] node - DOM дерево
 * \return дерево разбора
 * \throw 5 одна из вершм не содержит аттрибут name
*/
ExpressionNode TreeReader::treeWalkerXml(QDomNode node){
    ExpressionNode nodeRes;

    if(node.hasChildNodes()){
        QDomNodeList childs = node.childNodes();
        for(int i = 0; i< childs.count();i++){
            if(childs.at(i).toElement().tagName() == "node")
            nodeRes.child.append(treeWalkerXml(childs.at(i)));
        }
    }
    if(node.toElement().hasAttribute("name"))
        nodeRes.name = node.toElement().attribute("name");
    else
        throw 5;
    return nodeRes;
}
/*!
 * Обходит JSON представление и возвращает дерево разбора в универсальном формате
 * \param [in] obj - JSON объект
 * \return дерево разбора
 * \throw 5 одна из вершм не содержит аттрибут name
*/
ExpressionNode TreeReader::treeWalkerJSON(QJsonObject obj){
    ExpressionNode node;
    if(!obj.contains("name"))throw 5;
    node.name = obj.value("name").toString();
    if(obj.value("child") != QJsonValue::Undefined){
        for(int i = 0;i < obj.value("child").toArray().count();i++){
            node.child.append(treeWalkerJSON(obj.value("child").toArray().takeAt(i).toObject()));
        }
    }
    return node;
}
