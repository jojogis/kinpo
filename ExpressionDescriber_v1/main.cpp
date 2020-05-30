#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include "declension.h"
#include "operators.h"
#include "treereader.h"
QTextStream cin(stdin);

QHash<QString,QString> readDescribe(QString fileName,QString &error);
QHash<QString,QStringList> readFuncDescribe(QString fileName,QString &error);
QJsonObject readTree(QString filename);
QString treeWalker(ExpressionNode obj,Declension::Declensions currentDecl);

bool useDecl = false;
Declension decl;
QHash<QString,QString> desc;
QHash<QString,QStringList> funcDesc;
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
    qDebug() << "введите файл с описанием элементов";
    cin >> fileDescribe;
    }else{
        fileDescribe = QString(argv[2]);
    }
    QString fileFuncDescribe;
    if(argc <4){
    qDebug() << "введите файл с описанием функций";
    cin >> fileFuncDescribe;
    }else{
        fileFuncDescribe = QString(argv[3]);
    }
    QString useDeclStr;
    if(argc < 5){
        qDebug() << "использовать склонение? y/n";
        cin >> useDeclStr;
    }else{
        useDeclStr = QString(argv[4]);
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
        if(exep == 5)qDebug() << "Ошибка разбора файла с деревом: Отсутствует аттрибут name";
        return exep;
    }
    //читаем описание
    try {
        desc = readDescribe(a.applicationDirPath()+"/desc.txt",error);
        funcDesc = readFuncDescribe(a.applicationDirPath()+"/descFunc.txt",error);
    } catch (int exep) {
        if(exep == 4)qDebug() << "Ошибка открытия файла с описанием: "+error;
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
            return decl.getDeclension(descEl, currentDecl,useDecl);
        }else{
            //иначе возвращаем имя элемента
            return "'"+obj.name+"'";
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
        }else if(funcDesc.contains(obj.name)){//если для функции задано описание
            QString descFunc = funcDesc.value(obj.name)[0];
            descFunc = decl.getDeclension(descFunc,currentDecl,useDecl);
            QString childs = "";
            for(int i=0;i<obj.child.count();i++){
                childs += " и " + treeWalker(obj.child[i],Declension::R);
                if(funcDesc.value(obj.name)[i+1] != "-"){
                    childs += ", в качестве " + decl.getDeclension(funcDesc.value(obj.name)[i+1],Declension::R,useDecl);
                }
            }
            childs.remove(0,3);
            return descFunc + " от " + childs;
        }else{//если для оператора нет описания
            QString childs = "";
            for(int i=0;i<obj.child.count();i++){
                childs += " и " + treeWalker(obj.child[i],Declension::R);
            }
            childs.remove(0,3);
            return obj.name + " от " + childs;
        }
    }

}

QHash<QString,QStringList> readFuncDescribe(QString fileName,QString &error){
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        error = file.errorString();
        throw 4;
    }
    QHash<QString,QStringList> res;
    while(!file.atEnd()){
        QString funcName = file.readLine();
        int argCount = funcName.split(" ")[1].toInt();
        funcName = funcName.split(" ")[0].remove("\n");
        QStringList func;
        for(int i = 0;i<argCount+1;i++){
            QString el = file.readLine();
            func.append(el.remove("\n"));
        }
        res.insert(funcName,func);
    }
    return res;
}
QHash<QString,QString> readDescribe(QString fileName,QString &error){
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        error = file.errorString();
        throw 4;
    }
    QHash<QString,QString> res;
    while(!file.atEnd())
    {
        QString el = file.readLine();
        QString desc = file.readLine();
        if(el.length() > 0 && desc.length() > 0)
            res.insert(el.remove("\n"),desc.remove("\n"));
    }
    return res;
}

