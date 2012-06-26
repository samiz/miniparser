#include "grammarparser.h"


/*

  `Grammar` toplevel = `Grammar g;`
            (
                rule:r `g.addRule(r);`
            )*
            `ret= g;`
    ;

  `Rule` rule = codeBlock:retType
        identifier:id
        "="
        pegExpr:e
        `ret = Rule(id, retType, e)
    ;

   `string` codeBlock = `string s;`
        '`'
        (! '`' $anyChar:c `s +=c;`)*
        '`'
    ;

    `string` identifier = `string s;`
        $letter:c1 `s +=c1;`
        (
        $letter:c2 `s+=c2;`
        /
        $digit:c2 `s+=c3;`
        )*
    ;

    `ParseExpression *` pegExpr =

    ;

*/
Grammar metaGrammar()
{
    Grammar ret;
    // todo: Write meta grammar!
}
