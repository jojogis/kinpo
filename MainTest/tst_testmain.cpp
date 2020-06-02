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


QTEST_MAIN(TestMain);
#include "debug/tst_testmain.moc"


