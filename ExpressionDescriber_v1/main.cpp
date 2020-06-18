/*!
    \file
    \brief Главная функция
*/
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include "declension.h"
#include "operators.h"
#include "treereader.h"
#include <iostream>
#include "treewalker.h"
QTextStream cin(stdin);
QTextStream cout(stdout);

QHash<QString,QString> readDescribe(QString fileName,QString &error);
QHash<QString,QStringList> readFuncDescribe(QString fileName,QString &error);
QJsonObject readTree(QString filename);



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TreeWalker walker;
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
        walker.useDecl = true;
    }else{
        walker.useDecl = false;
    }
    //------------

    //читаем дерево
    ExpressionNode tree;
    QString error;
    try {
        tree = TreeReader::readTree(fileTree,error);
    } catch (int exep) {
        if(exep == 1)qDebug() << "Недопустимый формат файла с деревом";
        if(exep == 2)qDebug() << "Ошибка открытия файла с деревом: " + error;
        if(exep == 3)qDebug() << "Ошибка разбора файла с деревом: " + error;
        if(exep == 5)qDebug() << "Ошибка разбора файла с деревом: Отсутствует аттрибут name";
        return 0;
    }
    //читаем описание
    try {
        walker.desc = readDescribe(fileDescribe,error);
    } catch (int exep) {
        if(exep == 4)qDebug() << "Ошибка открытия файла с описанием: "+error;
        return 0;
    }
    try {
        walker.funcDesc = readFuncDescribe(fileFuncDescribe,error);
    } catch (int exep) {
        if(exep == 4)qDebug() << "Ошибка открытия файла с описанием функций: "+error;
        return 0;
    }
    QByteArray result = walker.treeWalker(tree,Declension::I).toUtf8();
    if(argc == 6){
        QFile output(argv[5]);
        if(output.open(QFile::WriteOnly)){
            output.write(result);
            output.close();
        }
    }else{
        cout << result;
    }


    return 0;
}

/*!
Функия чтения описания функций
\param[in] fileName путь к файлу с описанием функций
\param[in|out] error текст ошибки
\return описания функций
*/
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
    file.close();
    return res;
}
/*!
Функия чтения описания элементов
\param[in] fileName путь к файлу с описанием элементов
\param[in|out] error текст ошибки
\return описания элементов
*/
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
    file.close();
    return res;
}

