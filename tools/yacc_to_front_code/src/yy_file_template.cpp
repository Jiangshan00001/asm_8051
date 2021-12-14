#include "yy_file_template.h"

yy_file_template::yy_file_template()
{
}

std::string yy_file_template::get_fist_part(std::string inamespace, std::string iparser_class_name)
{
    std::string kk;

    kk=R"(

%{ /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include "token_defs.h"

#include "comp_context.h"
#include "comp_context_gen_defs.h"
#define YYSTYPE token_defs

%}

/*** yacc/bison Declarations ***/

/* Require bison 2.3 or later */
%require "2.3"

/* add debug output code to generated parser. disable this for release
* versions. */
%debug

/* write out a header file containing the token defines */
%defines

/* use newer C++ skeleton file */
%skeleton "lalr1.cc"


/* keep track of the current position within the input */
%locations
%initial-action
{
// initialize the initial location object
@$.begin.filename = @$.end.filename = &driver.streamname;
};

/* The driver is passed by reference to the parser and to the scanner. This
* provides a simple but effective pure interface, not relying on global
* variables. */
%parse-param { class Driver& driver }

/* verbose error messages */
%error-verbose

/*** BEGIN EXAMPLE - Change the example grammar's tokens below ***/

            )";

    /* namespace to enclose parser in */
    //%name-prefix="NS_AMS8051HEX"

    /* set the parser's class identifier */
    //%define "parser_class_name" "Parser"

    kk = kk + "\n"+"%name-prefix=\"" + inamespace+"\"\n";
    kk = kk + "\n"+"%define \"parser_class_name\"  \"" + iparser_class_name+"\"\n";


    return kk;
}

std::string yy_file_template::get_second_part()
{
    std::string kk;
    kk=R"(
%{

#include "driver.h"
#include "scanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
* object. it defines the yylex() function call to pull the next token from the
* current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex

%}
%% /*** Grammar Rules ***/

            )";

            return kk;
}

std::string yy_file_template::get_third_part(std::string inamespace, std::string iparser_class_name)
{
    std::string kk;
kk=R"(
%% /*** Additional Code ***/
)";
            kk=kk + "void  "+inamespace+"::"+iparser_class_name+"::error";
kk=kk+R"(
(const Parser::location_type& l,
            const std::string& m)
    {
        std::cout<<"ERROR:"<<l<<m<<std::endl;
    }
)";

    return kk;
}
