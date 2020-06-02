#include "treewalker.h"

TreeWalker::TreeWalker()
{

}

QString TreeWalker::treeWalker(ExpressionNode obj, Declension::Declensions currentDecl)
{
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
