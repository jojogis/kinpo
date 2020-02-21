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
    QString fileJson;
    if(argc < 2){
        qDebug() << "введите файл с деревом";
        cin >> fileJson;
    }else{
        fileJson = QString(argv[1]);
    }
    QString fileDescribe;
    if(argc < 3){
    qDebug() << "введите файл с описанием";
    cin >> fileDescribe;
    }else{
        fileDescribe = QString(argv[2]);
    }
    QString useDeclStr;
    if(argc < 4){
        qDebug() << "использовать склонение? y/n";
        cin >> useDeclStr;
    }else{
        useDeclStr = QString(argv[3]);
    }

    if(useDeclStr == "y" || useDeclStr == ""){
        useDecl = true;
    }else{
        useDecl = false;
    }
    //------------

    //читаем дерево
    QJsonObject tree;
    try {
        tree = readTree(a.applicationDirPath()+"/tree.json");
    } catch (int exep) {
        if(exep == 1)qDebug() << "Ошибка открытия файла с деревом";
        if(exep == 2)qDebug() << "Ошибка разбора файла с деревом";
        return exep;
    }

    //читаем описание
    try {
        desc = readDescribe(a.applicationDirPath()+"/desc.txt");
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
        QString el = obj.value("content").toString();
        //если есть описание для данного элемента
        if(desc.contains(el)){
            QString descEl = desc.value(el);
            if(useDecl){
                return decl.getDeclension(descEl, currentDecl);
            }else{
                return descEl;
            }
        }else{
            //иначе возвращаем имя элемента
            return el;
        }
    //иначе, если не листок
    }else{
        QString operat = obj.value("content").toString();
        //если оператор - стандартный
        if(operators.operatorsPrepositions.contains(operat)){
            QString prep = operators.operatorsPrepositions.value(operat);
            Preposition prepDecls = operators.prepositions.value(prep);

            //TODO переписать:
            if(obj.value("child").toArray().count() == 2){
                return operators.getOperatorByDecl(operat,currentDecl) + " "+
                        treeWalker(obj.value("child").toArray().takeAt(0).toObject(),prepDecls.declPrev)+
                        " "+ prepDecls.text +" "+
                        treeWalker(obj.value("child").toArray().takeAt(1).toObject(),prepDecls.declNext);
            }else if(obj.value("child").toArray().count() == 1){
                return operators.getOperatorByDecl(operat,currentDecl) + " "+
                        treeWalker(obj.value("child").toArray().takeAt(0).toObject(),prepDecls.declPrev);
            }
        }
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
    if(jsonDocument.isNull()){
        throw 2;
    }
    // Из которого выделяем объект в текущий рабочий QJsonObject
    return jsonDocument.object();
}
