#include "cppgenerator.h"

string int_to_str(int i)
{
    stringstream ss;
    ss << i;
    return ss.str();
}

CPPGenerator::CPPGenerator(Grammar grammar)
    :grammar(grammar)
{
    dummyCount = 0;
    posCount = 0;
}

template<class T> bool testType(ParseExpression *ptr)
{
    T *val = dynamic_cast<T *>(ptr);
    return val != NULL;
}

void CPPGenerator::generate()
{
    gen << "#include <string>\n";
    gen << "using namespace std;\n";
    for(vector<Rule>::iterator i= grammar.rules.begin();
        i != grammar.rules.end(); ++i)
    {
        Rule r = *i;
        gen << "bool " << r.name
            << "(string input, int &position, " << r.returnType <<" &ret)\n";
        gen << "{\n";
        gen << "bool _success = false;\n";
        generateExpression(r.expr);

        gen << "}\n";
    }
}

void CPPGenerator::generateExpression(ParseExpression *expr)
{
    if(testType<Literal>(expr))
        generateLiteral((Literal *) expr);
    else if(testType<RuleInvokation>(expr))
        generateRuleInvokation((RuleInvokation *) expr);
    else if(testType<InlineCode>(expr))
        generateInlineCode((InlineCode *) expr);
    else if(testType<Sequence>(expr))
        generateSequence((Sequence *) expr);
    else if(testType<Choice>(expr))
        generateChoice((Choice *) expr);
    else if(testType<Loop>(expr))
        generateLoop((Loop *) expr);
    else if(testType<Not>(expr))
        generateNot((Not *) expr);
}

void CPPGenerator::generateLiteral(Literal *expr)
{
    int n = expr->toMatch.length();

    if(expr->associatedVar !="")
    {
        gen << "string " << expr->associatedVar << ";\n";
    }
    gen << "if(position + " << n << ">=input.length())\n";
    gen << "return false;\n";
    gen << "if(input.substr(position, " << n <<") == \"" << expr->toMatch
        << "\")\n";
    gen << "{\n";
    if(expr->associatedVar !="")
        gen << expr->associatedVar << "= \""<< expr->toMatch <<"\";\n";
    gen << "_success = true;\n";
    gen << "position += " << expr->toMatch.length() << ";\n";
    gen << "}\n";
    gen << "else\n{\n";
    gen << "_success =  false;\n";
    gen << "}\n";
}

void CPPGenerator::generateRuleInvokation(RuleInvokation *expr)
{
    Rule r = grammar.ruleTable[expr->ruleName];
    string varName;
    if(expr->associatedVar !="")
    {
        varName = expr->associatedVar;
    }
    else
    {
        varName = "_dummy" + int_to_str(dummyCount++);
    }

    gen << r.returnType << " " << varName <<";\n";
    gen << "_success = " << expr->ruleName << "(input, position, "
        << varName << ");\n";
}

void CPPGenerator::generateInlineCode(InlineCode *expr)
{
    gen << expr->code;
}

void CPPGenerator::generateSequence(Sequence *expr)
{
    generateExpression(expr->p1);
    gen << "if(!_success)\n";
    gen << "{\n";
    gen << "return false;\n";
    gen << "}\n";
    generateExpression(expr->p2);
}

void CPPGenerator::generateChoice(Choice *expr)
{
    string oldPosName = "_pos";
    oldPosName += int_to_str(posCount++);

    gen << "int " << oldPosName << " = position;\n";
    generateExpression(expr->p1);

    gen << "if(_success)\n";
    gen << "{\n";
    gen << "return true;\n";
    gen << "}\n";
    gen << "position = " << oldPosName <<";\n";
    generateExpression(expr->p2);

}

void CPPGenerator::generateLoop(Loop *expr)
{
    string oldPosName = "_pos";
    oldPosName += int_to_str(posCount++);
    gen << "int " << oldPosName <<";\n";
    gen << "while(true) {\n";
    gen << oldPosName << " = position;\n";
    generateExpression(expr->p1);
    gen << "if(!_success) { \n";
    gen << "position = " << oldPosName << ";\n";
    gen << "break;\n";
    gen << "}\n"; // end if
    gen << "}\n"; // end while
}

void CPPGenerator::generateNot(Not *expr)
{
    string oldPosName = "_pos";
    oldPosName += int_to_str(posCount++);
    gen << "int " << oldPosName <<";\n";
    generateExpression(expr->p1);
    gen << "_success = ! _success;";
    gen << "position = " << oldPosName << ";\n";
}

string CPPGenerator::generateCondition(string strToTest, string charClass)
{
    if(charClass == "letter")
    {
        return "(" + strToTest + ">='A' &&"
                + strToTest + "<='Z') || ("
                + strToTest + ">='a' && "
                + strToTest + "<='z')";
    }
    else if(charClass == "digit")
    {
        return strToTest + ">='0' &&"
                + strToTest + "<='9'";
    }
    else if(charClass == "anyChar" )
    {
        return "true";
    }
    else if(charClass == "alphaNumeric")
    {
        return "(" + strToTest + ">='A' &&"
                + strToTest + "<='Z') || ("
                + strToTest + ">='a' && "
                + strToTest + "<='z') || ("
                + strToTest + ">='0' &&"
                + strToTest + "<='9' )";
    }
    else
    {
        return "errrorr!!!!! undefine char class: <"+charClass+ ">";
    }
}

void CPPGenerator::generateCharClass(CharClass *expr)
{
    int n = 1;

    if(expr->associatedVar !="")
    {
        gen << "string " << expr->associatedVar << ";\n";
    }
    gen << "if(position + " << n << ">=input.length())\n";
    gen << "return false;\n";
    string cond = generateCondition("(input.substr(position,1)[0])",
                                    expr->className);
    gen << "if(" << cond <<")\n";
    gen << "{\n";
    if(expr->associatedVar !="")
        gen << expr->associatedVar << "= \""<< "(input.substr(position,1))"<<"\";\n";
    gen << "_success = true;\n";
    gen << "position += " << n << ";\n";
    gen << "}\n";
    gen << "else\n{\n";
    gen << "_success =  false;\n";
    gen << "}\n";
}
