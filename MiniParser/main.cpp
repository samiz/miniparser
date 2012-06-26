#include <QtCore/QCoreApplication>
#include <iostream>
#include <fstream>
using namespace std;

#include "cppgenerator.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    Grammar grammar;

    Rule r = Rule("num", "int",
                  new Choice(new Sequence(new Literal("1"), new RuleInvokation("num")),
                             new Literal(""))
                  );
    grammar.addRule(r);
    CPPGenerator generator(grammar);
    generator.generate();
    ofstream fs("result.txt");
    fs << generator.gen.str();
    fs.flush();
    return a.exec();
}
