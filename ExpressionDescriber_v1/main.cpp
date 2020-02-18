#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QJsonArray>
#include "declension.h"
#include "operators.h"
QTextStream cin(stdin);

QHash<QString,QString> readDescribe(QString fileName);
QJsonObject readTree(QString jsonFileName);
QString treeWalker(QJsonObject obj,Declension::Declensions decl);
bool useDecl = false;
Declension decl;
QHash<QString,QString> desc;
Operators operators;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    setlocale(LC_ALL,"Russian");
    //ввод данных
    qDebug() << "введите файл с деревом";
    QString fileJson;
    cin >> fileJson;
    QString fileDescribe;
    qDebug() << "введите файл с описанием";
    cin >> fileDescribe;
    qDebug() << "использовать склонение? y/n";
    QString useDeclStr;
    cin >> useDeclStr;
    if(useDeclStr == "y" || useDeclStr == ""){
        useDecl = true;
    }else{
        useDecl = false;
    }
    //------------

    //читаем дерево
    QJsonObject tree;
    try {
        tree = readTree("C:\\Users\\alexe\\Desktop\\kinpo\\build-ExpressionDescriber_v1-Desktop_Qt_5_12_2_MSVC2017_64bit-Debug\\debug\\tree.json");
    } catch (int exep) {
        if(exep == 1)qDebug() << "Ошибка открытия файла с деревом";
        return exep;
    }

    //читаем описание
    try {
        desc = readDescribe("C:\\Users\\alexe\\Desktop\\kinpo\\build-ExpressionDescriber_v1-Desktop_Qt_5_12_2_MSVC2017_64bit-Debug\\debug\\desc.txt");
    } catch (int exep) {
        if(exep == 10)qDebug() << "Ошибка открытия файла с описанием";
        return exep;
    }

    qDebug() << treeWalker(tree,Declension::I);


    return a.exec();
}

QString treeWalker(QJsonObject obj,Declension::Declensions currentDecl){
    qDebug() << obj.value("content").toString();
    //если текущий объект - листок
    if(obj.value("child") == QJsonValue::Undefined){
        if(useDecl){
            QString descEl = desc.value(obj.value("content").toString());

            return decl.getDeclension(descEl, currentDecl);
        }else{
            QString descEl = desc.value(obj.value("content").toString());
            return descEl;
        }
    //иначе, если не листок
    }else{
        QString operat = obj.value("content").toString();
        QString prep = operators.operatorsPrepositions.value(operat);
        Preposition prepDecls = operators.prepositions.value(prep);
        return operators.getOperatorByDecl(operat,currentDecl) + " "+
            treeWalker(obj.value("child").toArray().takeAt(0).toObject(),prepDecls.declPrev)+
                    " "+ prep +" "+
            treeWalker(obj.value("child").toArray().takeAt(1).toObject(),prepDecls.declNext);
    }

}


QHash<QString,QString> readDescribe(QString fileName){
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly |QIODevice::Text)){
        throw 10;
    }
    QHash<QString,QString> res;
    while(!file.atEnd())
    {
        QString el = file.readLine();
        QString desc = file.readLine();
        res.insert(el.remove("\n"),desc.remove("\n"));
    }
    return res;
}

/*!
 * Читает дерево разбора выражения из файла
 * \param [in] jsonFileName - имя файла
 * \return дерево разбора
*/
QJsonObject readTree(QString jsonFileName){
    //парсим дерево
    QFileInfo fileInfo(jsonFileName);   // С помощью QFileInfo
    QDir::setCurrent(fileInfo.path());  // установим текущую рабочую директорию, где будет файл
    // Создаём объект файла и открываем его на чтение
    QFile jsonFile(jsonFileName);
    if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        throw 1;
    }
    // Считываем весь файл
    QString saveData = jsonFile.readAll();
    // Создаём QJsonDocument
    QJsonDocument jsonDocument(QJsonDocument::fromJson(saveData.toUtf8()));
    // Из которого выделяем объект в текущий рабочий QJsonObject
    return jsonDocument.object();
}
