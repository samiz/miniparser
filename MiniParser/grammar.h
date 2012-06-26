#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <string>
#include <vector>
#include <map>

using namespace std;

class ParseExpression
{
    int test;
public:
    ParseExpression();
    virtual string toString() { return "";}
};

class Literal: public ParseExpression
{
public:
    string toMatch;
    string associatedVar;
    Literal(string toMatch) : ParseExpression(), toMatch(toMatch){}
};

class RuleInvokation: public ParseExpression
{
public:
    string ruleName;
    string associatedVar;
    RuleInvokation(string ruleName) :
        ParseExpression(),
        ruleName(ruleName){}
};

class InlineCode : public ParseExpression
{
public:
    string code;
    InlineCode(string code):
        ParseExpression(),
        code(code) {}
};

class Sequence : public ParseExpression
{
public:
    ParseExpression *p1, *p2;
    Sequence(ParseExpression *p1, ParseExpression *p2)
        :
          ParseExpression(),
          p1(p1),
          p2(p2) {}
};

class Choice : public ParseExpression
{
public:
    ParseExpression *p1, *p2;
    Choice(ParseExpression *p1, ParseExpression *p2)
        :ParseExpression(),
          p1(p1),
          p2(p2) {}
};

class Loop : public ParseExpression
{
public:
    ParseExpression *p1;
    Loop(ParseExpression *p1)
        :ParseExpression(),
          p1(p1) {}
};

// 'Not' does not consume input!
class Not : public ParseExpression
{
public:
   ParseExpression *p1;
   Not(ParseExpression *p1)
       :ParseExpression(),
         p1(p1) {}
};

class CharClass: public ParseExpression
{
public:
   string className;
   string associatedVar;

   CharClass(string className, string associatedVar)
       :ParseExpression(),
         className(className), associatedVar(associatedVar) {}
};

class Rule
{
public:
    string name;
    string returnType;
    ParseExpression *expr;
    Rule(string name, string returnType, ParseExpression *expr)
        :
          name(name),
          returnType(returnType),
          expr(expr)
    {

    }
    Rule() {} // for adding to vectors and maps
    Rule &operator = (const Rule &other)
    {
        name = other.name;
        returnType = other.returnType;
        return *this;
    }
};

class Grammar
{
public:
    vector<Rule> rules;
    map<string, Rule> ruleTable;
    void addRule(Rule r)
    {
        rules.push_back(r);
        ruleTable[r.name] = r;
    }
};

#endif // GRAMMAR_H
