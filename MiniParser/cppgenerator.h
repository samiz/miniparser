#ifndef CPPGENERATOR_H
#define CPPGENERATOR_H

#include "grammar.h"
#include <sstream>
using namespace std;
class CPPGenerator
{
    Grammar grammar;
    int dummyCount;
    int posCount;
public:
    stringstream gen;
public:
    CPPGenerator(Grammar grammar);
    void generate();
    void generateExpression(ParseExpression *expr);

    void generateLiteral(Literal *expr);
    void generateRuleInvokation(RuleInvokation *expr);
    void generateInlineCode(InlineCode *expr);
    void generateSequence(Sequence *expr);
    void generateChoice(Choice *expr);
    void generateLoop(Loop *expr);
    void generateNot(Not *expr);
    void generateCharClass(CharClass *expr);

    string generateCondition(string strToTest, string charClass);
};

#endif // CPPGENERATOR_H
