#include "lex_file_template.h"
#include "replace.h"

lex_file_template::lex_file_template()
{
}

std::string lex_file_template::get_first_part(std::string inamespace, std::string scanner_base_name_prefix)
{
    std::string kk;

    kk=R"(

%{ /*** C/C++ Declarations ***/

#include <string>

#include "token_defs.h"
#define YYSTYPE token_defs

#include "scanner.h"

/* import the parser's token type into a local typedef */
typedef NS_AMS8051HEX::Parser::token token;
typedef NS_AMS8051HEX::Parser::token_type token_type;

/* By default yylex returns int, we use token_type. Unfortunately yyterminate
* by default returns 0, which is not of token_type. */
#define yyterminate() return token::END

/* This disables inclusion of unistd.h, which is not available under Visual C++
* on Win32. The C++ scanner uses STL streams instead. */
#define YY_NO_UNISTD_H


%}

/*** Flex Declarations and Options ***/

/* enable c++ scanner class generation */
%option c++

/* change the name of the scanner class. results in "ExampleFlexLexer" --Example */
%option prefix="scanner_base_name_prefix"

/* the manual says "somewhat more optimized" */
%option batch

/* enable scanner to generate debug output. disable this for release
* versions. */
%option debug

/* no support for include files is planned */
%option yywrap nounput

/* enables the use of start condition stacks */
%option stack

/* The following paragraph suffices to track locations accurately. Each time
* yylex is invoked, the begin position is moved onto the end position. */
%{
#define YY_USER_ACTION  {yylloc->step();yylloc->columns(yyleng);}
%}

/* code to place at the beginning of yylex() */
%{
// reset location
//yylloc->step();
%}

/*** BEGIN EXAMPLE - Change the example lexer rules below ***/

%% /*** Regular Expressions Part ***/

            )";



    replace(kk, "NS_AMS8051HEX",inamespace);
    replace(kk, "scanner_base_name_prefix",scanner_base_name_prefix);
    return kk;



}

std::string lex_file_template::get_second_part(std::string inamespace, std::string scanner_base_name_prefix)
{
    std::string kk;


    kk="%%\n";
    kk=kk+"namespace "+inamespace;

    kk=kk+R"(
             {


            Scanner::Scanner(class Driver &drv, std::istream* in,
                     std::ostream* out)
                : ASMFlexLexer(in, out)
            , driver(drv)
            {
            }

            Scanner::~Scanner()
            {
            }


            void Scanner::set_debug(bool b)
            {
                yy_flex_debug = b;
            }


            void Scanner::skip_comment(Parser::location_type* yylloc)
            {
                int c;

                while ((c = yyinput()) != 0)
                {
                    if (c == '\n')
                    {

                            return;
                    }
                }
                std::cout<<"ERROR:"<<"unterminated comment"<<"line:"<<lineno();
            }


            }

            /* This implementation of scanner_base_name_prefixFlexLexer::yylex() is required to fill the
             * vtable of the class scanner_base_name_prefixFlexLexer. We define the scanner's main yylex
             * function via YY_DECL to reside in the Scanner class instead. */

            #ifdef yylex
            #undef yylex
            #endif

            int scanner_base_name_prefixFlexLexer::yylex()
            {
                std::cerr << "in ASMFlexLexer::yylex() !" << std::endl;
                return 0;
            }

            /* When the scanner receives an end-of-file indication from YY_INPUT, it then
             * checks the yywrap() function. If yywrap() returns false (zero), then it is
             * assumed that the function has gone ahead and set up `yyin' to point to
             * another input file, and scanning continues. If it returns true (non-zero),
             * then the scanner terminates, returning 0 to its caller. */

            int scanner_base_name_prefixFlexLexer::yywrap()
            {
                return 1;
            }
            )";


        replace(kk, "NS_AMS8051HEX",inamespace);
        replace(kk, "scanner_base_name_prefix",scanner_base_name_prefix);
        return kk;
}
