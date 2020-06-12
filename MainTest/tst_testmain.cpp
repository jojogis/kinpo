#include <QtTest>

#include "../ExpressionDescriber_v1/declension.h"
#include "../ExpressionDescriber_v1/operators.h"
#include "../ExpressionDescriber_v1/treereader.h"
#include "../ExpressionDescriber_v1/treewalker.h"
#include "../ExpressionDescriber_v1/declension.cpp"
#include "../ExpressionDescriber_v1/operators.cpp"
#include "../ExpressionDescriber_v1/treereader.cpp"
#include "../ExpressionDescriber_v1/treewalker.cpp"
// add necessary includes here

class TestMain : public QObject
{

    Q_OBJECT

public:
    TestMain();
    ~TestMain();

private slots:
    void one_elem();
    void multiple();
    void one_func();
    void no_desc();
    void full();
    void main_1();
    void main_2();
    void main_3();
    void main_4();
    void main_5();
    void main_6();
    void main_7();
    void main_8();
};

TestMain::TestMain()
{

}

TestMain::~TestMain()
{

}

void TestMain::full(){
    ExpressionNode node;
    node.name = "%";
    ExpressionNode childNode;
    childNode.name = "--";
    childNode.child.append(ExpressionNode{"x"});
    node.child.append(childNode);
    ExpressionNode childNode1;
    childNode1.name = "[]";
    childNode1.child.append(ExpressionNode{"Y"});
    childNode1.child.append(ExpressionNode{"i"});
    node.child.append(childNode1);
    TreeWalker walker;
    walker.useDecl = true;
    walker.desc.insert("x","абсцисса");
    walker.desc.insert("Y","массив ординат");
    QCOMPARE( walker.treeWalker(node,Declension::I), "остаток от деления декремента абсциссы на элемент массива ординат с индексом 'i'");
}

void TestMain::no_desc(){
    ExpressionNode node;
    node.name = "*";
    node.child.append(ExpressionNode{"x"});
    node.child.append(ExpressionNode{"y"});
    TreeWalker walker;
    walker.useDecl = true;
    QCOMPARE( QString(walker.treeWalker(node,Declension::I)), "произведение 'x' на 'y'");
}

void TestMain::one_func(){
    ExpressionNode node;
    node.name = "sqrt";
    node.child.append(ExpressionNode{"x"});
    TreeWalker walker;
    walker.useDecl = true;
    walker.funcDesc.insert("sqrt",{"корень","-"});
    walker.desc.insert("x","абсцисса");
    QCOMPARE( walker.treeWalker(node,Declension::R), "корня от абсциссы");
}

void TestMain::multiple(){
    ExpressionNode node;
    node.name = "*";
    node.child.append(ExpressionNode{"x"});
    node.child.append(ExpressionNode{"y"});

    TreeWalker walker;
    walker.useDecl = true;
    walker.desc.insert("x","абсцисса");
    walker.desc.insert("y","ордината");
    QCOMPARE( walker.treeWalker(node,Declension::I), "произведение абсциссы на ординату");
}

void TestMain::one_elem()
{
    ExpressionNode node;
    node.name = "x";
    TreeWalker walker;
    walker.desc.insert("x","абсцисса");
    QCOMPARE( walker.treeWalker(node,Declension::I), "абсцисса");
}
void TestMain::main_1(){
    QProcess *process = new QProcess();
    process->start("../ExpressionDescriber_v1/debug/ExpressionDescriber_v1.exe tests/1.3.xml tests/1.1.txt tests/1.2.txt n");
    process->waitForFinished();
    QByteArray res = process->readAll();
    QString resStr = QString::fromLocal8Bit(res);
    QCOMPARE(resStr,"абсцисса ");
}

void TestMain::main_2(){
    QProcess *process = new QProcess();
    process->start("../ExpressionDescriber_v1/debug/ExpressionDescriber_v1.exe tests/2.3.xml tests/2.1.txt tests/2.2.txt n");
    process->waitForFinished();
    QByteArray res = process->readAll();
    QString resStr = QString::fromLocal8Bit(res);
    QCOMPARE(resStr,"присвоить абсцисса значение произведения абсцисса на ордината");
}

void TestMain::main_3(){
    QProcess *process = new QProcess();
    process->start("../ExpressionDescriber_v1/debug/ExpressionDescriber_v1.exe tests/3.3.xml tests/3.1.txt tests/3.2.txt n");
    process->waitForFinished();
    QByteArray res = process->readAll();
    QString resStr = QString::fromLocal8Bit(res);
    QCOMPARE(resStr,"присвоить абсцисса значение 'y'");
}

void TestMain::main_4(){
    QProcess *process = new QProcess();
    process->start("../ExpressionDescriber_v1/debug/ExpressionDescriber_v1.exe tests/4.3.xml tests/4.1.txt tests/4.2.txt n");
    process->waitForFinished();
    QByteArray res = process->readAll();
    QString resStr = QString::fromLocal8Bit(res);
    QCOMPARE(resStr,"присвоить 'x' значение log от 'x' и 'y'");
}

void TestMain::main_5(){
    QProcess *process = new QProcess();
    process->start("../ExpressionDescriber_v1/debug/ExpressionDescriber_v1.exe tests/5.3.xml tests/5.1.txt tests/5.2.txt n");
    process->waitForFinished();
    QByteArray res = process->readAll();
    QString resStr = QString::fromLocal8Bit(res);
    QCOMPARE(resStr,"присвоить 'x' значение логарифм от 'x', в качестве число и 'y', в качестве основание");
}

void TestMain::main_6(){
    QProcess *process = new QProcess();
    process->start("../ExpressionDescriber_v1/debug/ExpressionDescriber_v1.exe tests/6.3.xml tests/6.1.txt tests/6.2.txt n");
    process->waitForFinished();
    QByteArray res = process->readAll();
    QString resStr = QString::fromLocal8Bit(res);
    QCOMPARE(resStr,"присвоить 'x' значение логарифм от 'x' и 'y', в качестве основание");
}

void TestMain::main_7(){
    QProcess *process = new QProcess();
    process->start("../ExpressionDescriber_v1/debug/ExpressionDescriber_v1.exe tests/7.3.xml tests/7.1.txt tests/7.2.txt n");
    process->waitForFinished();
    QByteArray res = process->readAll();
    QString resStr = QString::fromLocal8Bit(res);
    QCOMPARE(resStr,"присвоить 'x' значение элемента 'y' с индексом 'i'");
}

void TestMain::main_8(){
    QProcess *process = new QProcess();
    process->start("../ExpressionDescriber_v1/debug/ExpressionDescriber_v1.exe tests/8.3.xml tests/8.1.txt tests/8.2.txt n");
    process->waitForFinished();
    QByteArray res = process->readAll();
    QString resStr = QString::fromLocal8Bit(res);
    QCOMPARE(resStr,"остаток от деления результата побитового ИЛИ над абсцисса и логарифм от абсцисса и ордината, в качестве основание на декремент абсцисса");
}

QTEST_MAIN(TestMain);
#include "debug/tst_testmain.moc"


