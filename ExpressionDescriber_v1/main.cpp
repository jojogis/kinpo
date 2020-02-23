#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include "declension.h"
#include "operators.h"
#include "treereader.h"
QTextStream cin(stdin);

QHash<QString,QString> readDescribe(QString fileName,QString &error);
QJsonObject readTree(QString filename);
QString treeWalker(ExpressionNode obj,Declension::Declensions currentDecl);

bool useDecl = false;
Declension decl;
QHash<QString,QString> desc;
Operators operators;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    setlocale(LC_ALL,"Russian");
    //ввод данных
    QString fileTree;
    if(argc < 2){
        qDebug() << "введите файл с деревом";
        cin >> fileTree;
    }else{
        fileTree = QString(argv[1]);
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
    ExpressionNode tree;
    QString error;
    try {
        tree = TreeReader::readTree(a.applicationDirPath()+"/tree.json",error);
    } catch (int exep) {
        if(exep == 1)qDebug() << "Недопустимый формат файла с деревом";
        if(exep == 2)qDebug() << "Ошибка открытия файла с деревом: " + error;
        if(exep == 3)qDebug() << "Ошибка разбора файла с деревом: " + error;
        return exep;
    }
    //читаем описание
    try {
        desc = readDescribe(a.applicationDirPath()+"/desc.txt",error);
    } catch (int exep) {
        if(exep == 10)qDebug() << "Ошибка открытия файла с описанием: "+error;
        return exep;
    }

    qDebug() << treeWalker(tree,Declension::I);


    return a.exec();
}

QString treeWalker(ExpressionNode obj,Declension::Declensions currentDecl){
    qDebug() << obj.name;
    //если текущий объект - листок
    if(obj.child.count() == 0){
        //если есть описание для данного элемента
        if(desc.contains(obj.name)){
            QString descEl = desc.value(obj.name);
            if(useDecl){
                return decl.getDeclension(descEl, currentDecl);
            }else{
                return descEl;
            }
        }else{
            //иначе возвращаем имя элемента
            return obj.name;
        }
    //иначе, если не листок
    }else{
        //если оператор - стандартный
        if(operators.operatorsPrepositions.contains(obj.name)){
            QString prep = operators.operatorsPrepositions.value(obj.name);
            Preposition prepDecls = operators.prepositions.value(prep);

            //TODO переписать:
            if(obj.child.count() == 2){
                return operators.getOperatorByDecl(obj.name,currentDecl) + " "+
                        treeWalker(obj.child[0],prepDecls.declPrev)+
                        " "+ prepDecls.text +" "+
                        treeWalker(obj.child[1],prepDecls.declNext);
            }else if(obj.child.count() == 1){
                return operators.getOperatorByDecl(obj.name,currentDecl) + " "+
                        treeWalker(obj.child[0],prepDecls.declPrev);
            }
        }
    }1

}


QHash<QString,QString> readDescribe(QString fileName,QString &error){
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        error = file.errorString();
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

