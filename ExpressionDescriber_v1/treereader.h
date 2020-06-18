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
    /*!
     * Читает дерево разбора выражения из файла xml
     * \param [in] filename - имя файла
     * \param [out] error - строка с ошибкой
     * \return дерево разбора
     * \throw 3 ошибка разбора xml
    */
    static ExpressionNode readXml(QString filename,QString &error);
    /*!
     * Читает дерево разбора выражения из файла json
     * \param [in] filename - имя файла
     * \param [out] error - строка с ошибкой
     * \return дерево разбора
     * \throw 3 ошибка разбора json
    */
    static ExpressionNode readJSON(QString filename,QString &error);
    /*!
     * Читает дерево разбора выражения из файла xml/json
     * \param [in] filename - имя файла
     * \param [out] error - строка с ошибкой
     * \return дерево разбора
     * \throw 2 ошибка открытия файла
     * \throw 1 неподдерживаемый формат
    */
    static ExpressionNode readTree(QString filename,QString &error);
    /*!
     * Обходит JSON представление и возвращает дерево разбора в универсальном формате
     * \param [in] obj - JSON объект
     * \return дерево разбора
     * \throw 5 одна из вершм не содержит аттрибут name
    */
    static ExpressionNode treeWalkerJSON(QJsonObject obj);
    /*!
     * Обходит DOM дерево и возвращает дерево разбора в универсальном формате
     * \param [in] node - DOM дерево
     * \return дерево разбора
     * \throw 5 одна из вершм не содержит аттрибут name
    */
    static ExpressionNode treeWalkerXml(QDomNode node);
};

#endif // TREEREADER_H
