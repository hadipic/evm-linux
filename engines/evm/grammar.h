DEF_RULE(program, rule(sourceElements), rule_end)
DEF_RULE(sourceElements, tk_more, rule(sourceElement), tk_more, tk_end)
DEF_RULE(sourceElement, tk_or, rule(functionDeclaration), tk_or, rule(statement), tk_or_end, tk_end)
DEF_RULE(functionDeclaration, c(atom_function), c(atom_id), rule(formalParameterList), rule(statementBlock), tk_end)
DEF_RULE(formalParameterList, c(atom_bracket), tk_maybe, c(atom_id), tk_more, c(atom_comma), c(atom_id), tk_more_end, tk_maybe_end, c(atom_bracket_close), tk_end)
DEF_RULE(functionBody, c(atom_brace), rule(sourceElements), c(atom_brace_close), tk_end)
DEF_RULE(statement, 
         tk_or, rule(statementBlock), 
         tk_or, rule(variableStatement),
         tk_or, rule(ifStatement), 
         tk_or, rule(forStatement), 
         tk_or, rule(whileStatement),
         tk_or, rule(continueStatement),
         tk_or, rule(breakStatement),
         tk_or, rule(returnStatement),
         tk_or, rule(throwStatement),
         tk_or, rule(switchStatement),
         tk_or, rule(tryStatement),
         tk_or, rule(expressionStatement), tk_end)
DEF_RULE(statementBlock, c(atom_brace), tk_maybe, rule(statementList), tk_maybe_end, c(atom_brace_close), tk_end)
DEF_RULE(statementList, rule(statement), tk_more, rule(statement), tk_more_end, tk_end)
DEF_RULE(variableStatement, rule(variableDeclarationList), c(atom_newline_or_semicolon), tk_end)
DEF_RULE(variableDeclarationList, c(atom_var), rule(variableDeclaration), tk_more, c(atom_comma), rule(variableDeclaration), tk_more_end, tk_end)
DEF_RULE(variableDeclaration, c(atom_id), tk_maybe, rule(initialiser), tk_maybe_end, tk_end)


