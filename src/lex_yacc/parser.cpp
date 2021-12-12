/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002-2010 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

// Take the name prefix into account.
#define yylex   asm_lex_stufflex

/* First part of user declarations.  */

/* Line 310 of lalr1.cc  */
#line 4 "ly/parser.yy"
 /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include "../asm_token.h"
#include "../asm8051_lex.h"
#define YYSTYPE asm_token


#include "driver.h"


/* Line 310 of lalr1.cc  */
#line 74 "ly/parser.yy"


#include "scanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex pdriver->m_lexer->lex



/* Line 310 of lalr1.cc  */
#line 70 "parser.cpp"


#include "parser.h"

/* User implementation prologue.  */


/* Line 316 of lalr1.cc  */
#line 79 "parser.cpp"

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* Enable debugging if requested.  */
#if YYDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_REDUCE_PRINT(Rule)
# define YY_STACK_PRINT()

#endif /* !YYDEBUG */

#define yyerrok		(yyerrstatus_ = 0)
#define yyclearin	(yychar = yyempty_)

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace asm_lex_stuff {

/* Line 379 of lalr1.cc  */
#line 145 "parser.cpp"
#if YYERROR_VERBOSE

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              /* Fall through.  */
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

#endif

  /// Build a parser object.
  Parser::Parser (class driver* pdriver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      pdriver (pdriver_yyarg)
  {
  }

  Parser::~Parser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  Parser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    switch (yytype)
      {
         default:
	  break;
      }
  }


  void
  Parser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif

  void
  Parser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
  
	default:
	  break;
      }
  }

  void
  Parser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif

  int
  Parser::parse ()
  {
    /// Lookahead and lookahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    /* State.  */
    int yyn;
    int yylen = 0;
    int yystate = 0;

    /* Error handling.  */
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    semantic_type yylval;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[2];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    YYCDEBUG << "Starting parse" << std::endl;


    /* User initialization code.  */
    
/* Line 552 of lalr1.cc  */
#line 46 "ly/parser.yy"
{
    // initialize the initial location object
    yylloc.begin.filename = yylloc.end.filename = &pdriver->m_stream_name;
}

/* Line 552 of lalr1.cc  */
#line 329 "parser.cpp"

    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;

    /* Accept?  */
    if (yystate == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without lookahead.  */
    yyn = yypact_[yystate];
    if (yyn == yypact_ninf_)
      goto yydefault;

    /* Read a lookahead token.  */
    if (yychar == yyempty_)
      {
	YYCDEBUG << "Reading a token: ";
	yychar = yylex (&yylval, &yylloc);
      }


    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yyn == 0 || yyn == yytable_ninf_)
	goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted.  */
    yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
	  case 3:

/* Line 677 of lalr1.cc  */
#line 91 "ly/parser.yy"
    {(yyval)=(yysemantic_stack_[(1) - (1)]); pdriver->m_token_result=(yyval); pdriver->m_parse_success=1;}
    break;

  case 4:

/* Line 677 of lalr1.cc  */
#line 95 "ly/parser.yy"
    {(yyval)=(yysemantic_stack_[(1) - (1)]);}
    break;

  case 5:

/* Line 677 of lalr1.cc  */
#line 96 "ly/parser.yy"
    {(yyval)=(yysemantic_stack_[(1) - (1)]);}
    break;

  case 6:

/* Line 677 of lalr1.cc  */
#line 97 "ly/parser.yy"
    {(yyval)=(yysemantic_stack_[(1) - (1)]);}
    break;

  case 7:

/* Line 677 of lalr1.cc  */
#line 98 "ly/parser.yy"
    {(yyval).type=TOKEN_PARENT; (yyval).child_type=TOKEN_PARENT; (yyval).m_childs.push_back((yysemantic_stack_[(2) - (1)]));(yyval).m_childs.push_back((yysemantic_stack_[(2) - (2)])); }
    break;

  case 8:

/* Line 677 of lalr1.cc  */
#line 99 "ly/parser.yy"
    {(yyval).type=TOKEN_PARENT; (yyval).child_type=TOKEN_PARENT; (yyval).m_childs.push_back((yysemantic_stack_[(2) - (1)]));(yyval).m_childs.push_back((yysemantic_stack_[(2) - (2)])); }
    break;

  case 9:

/* Line 677 of lalr1.cc  */
#line 100 "ly/parser.yy"
    {(yyval).type=TOKEN_PARENT; (yyval).child_type=TOKEN_PARENT; (yyval).m_childs.push_back((yysemantic_stack_[(2) - (1)]));(yyval).m_childs.push_back((yysemantic_stack_[(2) - (2)])); }
    break;

  case 10:

/* Line 677 of lalr1.cc  */
#line 103 "ly/parser.yy"
    { (yyval)=(yysemantic_stack_[(2) - (1)]);(yyval).type=TOKEN_CMD;   }
    break;

  case 11:

/* Line 677 of lalr1.cc  */
#line 104 "ly/parser.yy"
    { (yyval)=(yysemantic_stack_[(3) - (1)]);(yyval).type=TOKEN_PARENT; (yyval).child_type=TOKEN_CMD; (yysemantic_stack_[(3) - (1)]).type=TOKEN_CMD; (yyval).m_childs.push_back((yysemantic_stack_[(3) - (1)])); (yyval).m_childs.push_back((yysemantic_stack_[(3) - (2)]));   }
    break;

  case 12:

/* Line 677 of lalr1.cc  */
#line 105 "ly/parser.yy"
    {(yyval)=(yysemantic_stack_[(5) - (1)]);(yyval).type=TOKEN_PARENT; (yyval).child_type=TOKEN_CMD;(yysemantic_stack_[(5) - (1)]).type=TOKEN_CMD; (yyval).m_childs.push_back((yysemantic_stack_[(5) - (1)])); (yyval).m_childs.push_back((yysemantic_stack_[(5) - (2)])); (yyval).m_childs.push_back((yysemantic_stack_[(5) - (4)]));   }
    break;

  case 13:

/* Line 677 of lalr1.cc  */
#line 106 "ly/parser.yy"
    {(yyval)=(yysemantic_stack_[(7) - (1)]);
                                                        (yyval).type=TOKEN_PARENT;
                                                        (yyval).child_type=TOKEN_CMD;
                                                        (yysemantic_stack_[(7) - (1)]).type=TOKEN_CMD;
                                                        (yyval).m_childs.push_back((yysemantic_stack_[(7) - (1)]));
                                                        (yyval).m_childs.push_back((yysemantic_stack_[(7) - (2)]));
                                                        (yyval).m_childs.push_back((yysemantic_stack_[(7) - (4)]));
                                                        (yyval).m_childs.push_back((yysemantic_stack_[(7) - (6)]));
                                                        }
    break;

  case 14:

/* Line 677 of lalr1.cc  */
#line 115 "ly/parser.yy"
    {(yyval)=(yysemantic_stack_[(9) - (1)]);
                                                            (yyval).type=TOKEN_PARENT;
                                                            (yyval).child_type=TOKEN_CMD;
                                                            (yysemantic_stack_[(9) - (1)]).type=TOKEN_CMD;
                                                            (yyval).m_childs.push_back((yysemantic_stack_[(9) - (1)]));
                                                            (yyval).m_childs.push_back((yysemantic_stack_[(9) - (2)]));
                                                            (yyval).m_childs.push_back((yysemantic_stack_[(9) - (4)]));
                                                            (yyval).m_childs.push_back((yysemantic_stack_[(9) - (6)]));
                                                            (yyval).m_childs.push_back((yysemantic_stack_[(9) - (8)]));
                                                            }
    break;

  case 16:

/* Line 677 of lalr1.cc  */
#line 129 "ly/parser.yy"
    {
                        (yyval).type=TOKEN_J_DATA;
                        (yyval).val_str="#"+(yysemantic_stack_[(2) - (2)]).val_str;
                        (yyval).m_childs.push_back((yysemantic_stack_[(2) - (2)]));
                        (yyval).m_resolved=0;
                    }
    break;

  case 17:

/* Line 677 of lalr1.cc  */
#line 135 "ly/parser.yy"
    {
                        (yyval).type=TOKEN_DIV_NUM;
                        (yyval).val_str="/"+(yysemantic_stack_[(2) - (2)]).val_str;
                        (yyval).m_childs.clear();
                        (yyval).m_childs.push_back((yysemantic_stack_[(2) - (2)]));
                        (yyval).m_resolved=0;
                    }
    break;

  case 18:

/* Line 677 of lalr1.cc  */
#line 146 "ly/parser.yy"
    {(yyval).type=TOKEN_KEYWORD;(yyval).val_str=(yysemantic_stack_[(1) - (1)]).val_str; (yyval).m_resolved=0;}
    break;

  case 19:

/* Line 677 of lalr1.cc  */
#line 147 "ly/parser.yy"
    {(yyval).type=TOKEN_NUM;(yyval).val_str=(yysemantic_stack_[(1) - (1)]).val_str; (yyval).num = StrToNumber((yysemantic_stack_[(1) - (1)]).val_str); (yyval).m_resolved=1;}
    break;

  case 20:

/* Line 677 of lalr1.cc  */
#line 148 "ly/parser.yy"
    {(yyval).type=TOKEN_NUM;(yyval).val_str=(yysemantic_stack_[(1) - (1)]).val_str;  (yyval).m_resolved=1;}
    break;

  case 21:

/* Line 677 of lalr1.cc  */
#line 149 "ly/parser.yy"
    {(yyval).type=TOKEN_ACC;(yyval).val_str=(yysemantic_stack_[(1) - (1)]).val_str; (yyval).m_resolved=1;}
    break;

  case 22:

/* Line 677 of lalr1.cc  */
#line 150 "ly/parser.yy"
    {(yyval).type=TOKEN_C;(yyval).val_str=(yysemantic_stack_[(1) - (1)]).val_str; (yyval).m_resolved=1;}
    break;

  case 23:

/* Line 677 of lalr1.cc  */
#line 151 "ly/parser.yy"
    {(yyval).type=TOKEN_AB;(yyval).val_str=(yysemantic_stack_[(1) - (1)]).val_str; (yyval).m_resolved=1;}
    break;

  case 24:

/* Line 677 of lalr1.cc  */
#line 152 "ly/parser.yy"
    {(yyval).type=TOKEN_AT_DPTR;(yyval).val_str=(yysemantic_stack_[(1) - (1)]).val_str; (yyval).m_resolved=1;}
    break;

  case 25:

/* Line 677 of lalr1.cc  */
#line 153 "ly/parser.yy"
    {(yyval).type=TOKEN_DPTR;(yyval).val_str=(yysemantic_stack_[(1) - (1)]).val_str; (yyval).m_resolved=1;}
    break;

  case 26:

/* Line 677 of lalr1.cc  */
#line 154 "ly/parser.yy"
    {(yyval).type=TOKEN_AT_A_PLUS_PC;(yyval).val_str=(yysemantic_stack_[(1) - (1)]).val_str; (yyval).m_resolved=1;}
    break;

  case 27:

/* Line 677 of lalr1.cc  */
#line 155 "ly/parser.yy"
    {(yyval).type=TOKEN_AT_A_PLUS_DPTR;(yyval).val_str=(yysemantic_stack_[(1) - (1)]).val_str; (yyval).m_resolved=1;}
    break;

  case 28:

/* Line 677 of lalr1.cc  */
#line 156 "ly/parser.yy"
    {(yyval)=(yysemantic_stack_[(1) - (1)]); (yyval).type=TOKEN_AT_RI;(yyval).val_str=(yysemantic_stack_[(1) - (1)]).val_str; (yyval).m_resolved=1;}
    break;

  case 29:

/* Line 677 of lalr1.cc  */
#line 157 "ly/parser.yy"
    {(yyval)=(yysemantic_stack_[(1) - (1)]); (yyval).type=TOKEN_RN;(yyval).val_str=(yysemantic_stack_[(1) - (1)]).val_str; (yyval).m_resolved=1;}
    break;

  case 30:

/* Line 677 of lalr1.cc  */
#line 158 "ly/parser.yy"
    {(yyval).type=TOKEN_KEYWORD;(yyval).val_str="$"; (yyval).m_resolved=0;}
    break;

  case 31:

/* Line 677 of lalr1.cc  */
#line 159 "ly/parser.yy"
    {
                            (yyval).type=TOKEN_PARENT;
                            (yyval).child_type=TOKEN_OPR;
                            (yyval).val_str="(" + (yysemantic_stack_[(3) - (2)]).val_str +")";
                            (yyval).m_childs.clear();
                            (yyval).m_childs.push_back((yysemantic_stack_[(3) - (1)]));
                            (yyval).m_childs.push_back((yysemantic_stack_[(3) - (2)]));
                            (yyval).m_resolved=0;
                            }
    break;

  case 32:

/* Line 677 of lalr1.cc  */
#line 170 "ly/parser.yy"
    {(yyval)=(yysemantic_stack_[(1) - (1)]);}
    break;

  case 33:

/* Line 677 of lalr1.cc  */
#line 171 "ly/parser.yy"
    {
                             (yyval).type=TOKEN_PARENT;
                             (yyval).child_type=TOKEN_OPR;
                             (yyval).val_str=+"NOT " + (yysemantic_stack_[(2) - (2)]).val_str;
                             (yysemantic_stack_[(2) - (1)]).type=TOKEN_OPR;
                             (yyval).m_childs.push_back((yysemantic_stack_[(2) - (1)]));
                             (yyval).m_childs.push_back((yysemantic_stack_[(2) - (2)]));
                             (yyval).m_resolved=0;
                             }
    break;

  case 34:

/* Line 677 of lalr1.cc  */
#line 180 "ly/parser.yy"
    {
                            (yyval).type=TOKEN_PARENT;
                            (yyval).child_type=TOKEN_OPR;
                            (yyval).val_str=+"HIGH " + (yysemantic_stack_[(2) - (2)]).val_str;
                            (yysemantic_stack_[(2) - (1)]).type=TOKEN_OPR;
                            (yyval).m_childs.push_back((yysemantic_stack_[(2) - (1)]));
                            (yyval).m_childs.push_back((yysemantic_stack_[(2) - (2)]));
                            (yyval).m_resolved=0;
                            }
    break;

  case 35:

/* Line 677 of lalr1.cc  */
#line 189 "ly/parser.yy"
    {
                            (yyval).type=TOKEN_PARENT;
                            (yyval).child_type=TOKEN_OPR;
                            (yyval).val_str=+"LOW " + (yysemantic_stack_[(2) - (2)]).val_str;
                            (yysemantic_stack_[(2) - (1)]).type=TOKEN_OPR;
                            (yyval).m_childs.push_back((yysemantic_stack_[(2) - (1)]));
                            (yyval).m_childs.push_back((yysemantic_stack_[(2) - (2)]));
                            (yyval).m_resolved=0;
                            }
    break;

  case 36:

/* Line 677 of lalr1.cc  */
#line 198 "ly/parser.yy"
    {

                            (yyval).type=TOKEN_PARENT;
                            (yyval).child_type=TOKEN_OPR;
                            (yyval).val_str=(yysemantic_stack_[(3) - (1)]).val_str + " SHL " + (yysemantic_stack_[(3) - (3)]).val_str;
                            (yysemantic_stack_[(3) - (2)]).type=TOKEN_OPR;
                            (yyval).m_childs.push_back((yysemantic_stack_[(3) - (2)]));
                            (yyval).m_childs.push_back((yysemantic_stack_[(3) - (1)]));
                            (yyval).m_childs.push_back((yysemantic_stack_[(3) - (3)]));
                            (yyval).m_resolved=0;
                            }
    break;

  case 37:

/* Line 677 of lalr1.cc  */
#line 209 "ly/parser.yy"
    {
                                (yyval).type=TOKEN_PARENT;
                                (yyval).child_type=TOKEN_OPR;
                                (yyval).val_str= (yysemantic_stack_[(3) - (1)]).val_str +" MOD " + (yysemantic_stack_[(3) - (3)]).val_str;
                                (yysemantic_stack_[(3) - (2)]).type=TOKEN_OPR;
                                (yyval).m_childs.push_back((yysemantic_stack_[(3) - (2)]));
                                (yyval).m_childs.push_back((yysemantic_stack_[(3) - (1)]));
                                (yyval).m_childs.push_back((yysemantic_stack_[(3) - (3)]));
                                (yyval).m_resolved=0;
                            }
    break;

  case 38:

/* Line 677 of lalr1.cc  */
#line 219 "ly/parser.yy"
    {
                                    (yyval).type=TOKEN_PARENT;
                                    (yyval).child_type=TOKEN_OPR;
                                    (yyval).m_childs.push_back((yysemantic_stack_[(3) - (2)]));
                                    (yyval).m_childs.push_back((yysemantic_stack_[(3) - (1)]));
                                    (yyval).m_childs.push_back((yysemantic_stack_[(3) - (3)]));
                                    (yyval).m_resolved=0;
                                    (yyval).val_str=(yysemantic_stack_[(3) - (1)]).val_str+"."+(yysemantic_stack_[(3) - (3)]).val_str;
                                    }
    break;

  case 39:

/* Line 677 of lalr1.cc  */
#line 228 "ly/parser.yy"
    {
                                    (yyval).type=TOKEN_PARENT;
                                    (yyval).child_type=TOKEN_OPR;
                                    (yyval).m_childs.clear();
                                    (yyval).m_childs.push_back((yysemantic_stack_[(3) - (2)]));
                                    (yyval).m_childs.push_back((yysemantic_stack_[(3) - (1)]));
                                    (yyval).m_childs.push_back((yysemantic_stack_[(3) - (3)]));
                                    (yyval).m_resolved=0;
                                    (yyval).val_str=(yysemantic_stack_[(3) - (1)]).val_str+" & "+(yysemantic_stack_[(3) - (3)]).val_str;
                                    }
    break;

  case 40:

/* Line 677 of lalr1.cc  */
#line 239 "ly/parser.yy"
    {
                                    (yyval).type=TOKEN_PARENT;
                                    (yyval).child_type=TOKEN_OPR;
                                    (yyval).m_childs.clear();
                                    (yyval).m_childs.push_back((yysemantic_stack_[(3) - (2)]));
                                    (yyval).m_childs.push_back((yysemantic_stack_[(3) - (1)]));
                                    (yyval).m_childs.push_back((yysemantic_stack_[(3) - (3)]));
                                    (yyval).m_resolved=0;
                                    (yyval).val_str=(yysemantic_stack_[(3) - (1)]).val_str+" >> "+(yysemantic_stack_[(3) - (3)]).val_str;
                                    }
    break;

  case 41:

/* Line 677 of lalr1.cc  */
#line 249 "ly/parser.yy"
    {
                                    (yyval).type=TOKEN_PARENT;
                                    (yyval).child_type=TOKEN_OPR;
                                    (yyval).m_childs.clear();
                                    (yyval).m_childs.push_back((yysemantic_stack_[(3) - (2)]));
                                    (yyval).m_childs.push_back((yysemantic_stack_[(3) - (1)]));
                                    (yyval).m_childs.push_back((yysemantic_stack_[(3) - (3)]));
                                    (yyval).m_resolved=0;
                                    (yyval).val_str=(yysemantic_stack_[(3) - (1)]).val_str+" << "+(yysemantic_stack_[(3) - (3)]).val_str;
                                    }
    break;

  case 42:

/* Line 677 of lalr1.cc  */
#line 262 "ly/parser.yy"
    {(yyval)=(yysemantic_stack_[(1) - (1)]);}
    break;

  case 43:

/* Line 677 of lalr1.cc  */
#line 263 "ly/parser.yy"
    {
                                        (yyval).type=TOKEN_PARENT;
                                        (yyval).child_type=TOKEN_OPR;
                                        (yyval).val_str=(yysemantic_stack_[(3) - (1)]).val_str+"*" + (yysemantic_stack_[(3) - (3)]).val_str;
                                        (yysemantic_stack_[(3) - (2)]).type=TOKEN_OPR;
                                        (yyval).m_childs.push_back((yysemantic_stack_[(3) - (2)]));
                                        (yyval).m_childs.push_back((yysemantic_stack_[(3) - (1)]));
                                        (yyval).m_childs.push_back((yysemantic_stack_[(3) - (3)]));
                                        (yyval).m_resolved=0;

                                        }
    break;

  case 44:

/* Line 677 of lalr1.cc  */
#line 274 "ly/parser.yy"
    {
                                        (yyval).type=TOKEN_PARENT;
                                        (yyval).child_type=TOKEN_OPR;
                                        (yyval).val_str=(yysemantic_stack_[(3) - (1)]).val_str+"/" + (yysemantic_stack_[(3) - (3)]).val_str;
                                        (yysemantic_stack_[(3) - (2)]).type=TOKEN_OPR;
                                        (yyval).m_childs.push_back((yysemantic_stack_[(3) - (2)]));
                                        (yyval).m_childs.push_back((yysemantic_stack_[(3) - (1)]));
                                        (yyval).m_childs.push_back((yysemantic_stack_[(3) - (3)]));
                                        (yyval).m_resolved=0;

                                        }
    break;

  case 45:

/* Line 677 of lalr1.cc  */
#line 285 "ly/parser.yy"
    {
                                    (yyval).type=TOKEN_PARENT;
                                    (yyval).child_type=TOKEN_OPR;
                                    (yyval).val_str=(yysemantic_stack_[(3) - (1)]).val_str+"%" + (yysemantic_stack_[(3) - (3)]).val_str;
                                    (yysemantic_stack_[(3) - (2)]).type=TOKEN_OPR;
                                    (yyval).m_childs.push_back((yysemantic_stack_[(3) - (2)]));
                                    (yyval).m_childs.push_back((yysemantic_stack_[(3) - (1)]));
                                    (yyval).m_childs.push_back((yysemantic_stack_[(3) - (3)]));
                                    (yyval).m_resolved=0;

                                    }
    break;

  case 46:

/* Line 677 of lalr1.cc  */
#line 299 "ly/parser.yy"
    {(yyval)=(yysemantic_stack_[(1) - (1)]);}
    break;

  case 47:

/* Line 677 of lalr1.cc  */
#line 300 "ly/parser.yy"
    {
                                        (yyval).type=TOKEN_PARENT;
                                        (yyval).child_type=TOKEN_OPR;
                                        (yyval).val_str=(yysemantic_stack_[(3) - (1)]).val_str+"+" + (yysemantic_stack_[(3) - (3)]).val_str;
                                        (yysemantic_stack_[(3) - (2)]).type=TOKEN_OPR;
                                        (yyval).m_childs.push_back((yysemantic_stack_[(3) - (2)]));
                                        (yyval).m_childs.push_back((yysemantic_stack_[(3) - (1)]));
                                        (yyval).m_childs.push_back((yysemantic_stack_[(3) - (3)]));
                                        (yyval).m_resolved=0;
                                        }
    break;

  case 48:

/* Line 677 of lalr1.cc  */
#line 310 "ly/parser.yy"
    {
                                (yyval).type=TOKEN_PARENT;
                                (yyval).child_type=TOKEN_OPR;
                                (yyval).val_str=(yysemantic_stack_[(3) - (1)]).val_str+"-" + (yysemantic_stack_[(3) - (3)]).val_str;
                                (yysemantic_stack_[(3) - (2)]).type=TOKEN_OPR;
                                (yyval).m_childs.push_back((yysemantic_stack_[(3) - (2)]));
                                (yyval).m_childs.push_back((yysemantic_stack_[(3) - (1)]));
                                (yyval).m_childs.push_back((yysemantic_stack_[(3) - (3)]));
                                (yyval).m_resolved=0;

                                }
    break;

  case 49:

/* Line 677 of lalr1.cc  */
#line 324 "ly/parser.yy"
    {(yyval)=(yysemantic_stack_[(1) - (1)]);}
    break;

  case 50:

/* Line 677 of lalr1.cc  */
#line 329 "ly/parser.yy"
    { (yyval).type=TOKEN_MACRO; (yyval).val_str = (yysemantic_stack_[(2) - (1)]).val_str;  }
    break;

  case 51:

/* Line 677 of lalr1.cc  */
#line 330 "ly/parser.yy"
    {
                                            (yyval).type=TOKEN_PARENT;
                                            (yyval).child_type = TOKEN_MACRO;
                                            (yysemantic_stack_[(3) - (1)]).type=TOKEN_MACRO;
                                            (yyval).m_childs.push_back((yysemantic_stack_[(3) - (1)]));
                                            (yyval).m_childs.push_back((yysemantic_stack_[(3) - (2)]));
                                            }
    break;

  case 52:

/* Line 677 of lalr1.cc  */
#line 337 "ly/parser.yy"
    {
                                            (yyval).type=TOKEN_PARENT;
                                            (yyval).child_type = TOKEN_MACRO;
                                            (yysemantic_stack_[(4) - (1)]).type=TOKEN_MACRO;
                                            (yyval).m_childs.push_back((yysemantic_stack_[(4) - (1)]));
                                            (yyval).m_childs.push_back((yysemantic_stack_[(4) - (2)]));
                                            (yyval).m_childs.push_back((yysemantic_stack_[(4) - (3)]));
                                            }
    break;

  case 53:

/* Line 677 of lalr1.cc  */
#line 345 "ly/parser.yy"
    {
                                            (yyval).type=TOKEN_PARENT;
                                            (yyval).child_type = TOKEN_MACRO;
                                            (yysemantic_stack_[(4) - (1)]).type=TOKEN_KEYWORD;
                                            (yysemantic_stack_[(4) - (2)]).type=TOKEN_MACRO;
                                            (yyval).m_childs.push_back((yysemantic_stack_[(4) - (1)]));
                                            (yyval).m_childs.push_back((yysemantic_stack_[(4) - (2)]));
                                            (yyval).m_childs.push_back((yysemantic_stack_[(4) - (3)]));
                                            }
    break;

  case 54:

/* Line 677 of lalr1.cc  */
#line 354 "ly/parser.yy"
    {
                                                (yyval)=(yysemantic_stack_[(2) - (1)]);
                                            }
    break;

  case 55:

/* Line 677 of lalr1.cc  */
#line 360 "ly/parser.yy"
    { (yyval).type=TOKEN_DB; (yyval).m_childs.push_back((yysemantic_stack_[(2) - (2)])); }
    break;

  case 56:

/* Line 677 of lalr1.cc  */
#line 361 "ly/parser.yy"
    { (yyval)=(yysemantic_stack_[(3) - (1)]); (yyval).m_childs.push_back((yysemantic_stack_[(3) - (3)])); }
    break;

  case 57:

/* Line 677 of lalr1.cc  */
#line 362 "ly/parser.yy"
    { (yyval)=(yysemantic_stack_[(2) - (1)]); (yyval).m_childs.push_back((yysemantic_stack_[(2) - (2)])); }
    break;

  case 58:

/* Line 677 of lalr1.cc  */
#line 366 "ly/parser.yy"
    {(yyval).type = TOKEN_LABEL; (yyval).val_str = (yysemantic_stack_[(2) - (1)]).val_str; (yyval).m_resolved=1; }
    break;

  case 59:

/* Line 677 of lalr1.cc  */
#line 367 "ly/parser.yy"
    {(yyval)=(yysemantic_stack_[(2) - (1)]);}
    break;



/* Line 677 of lalr1.cc  */
#line 1026 "parser.cpp"
	default:
          break;
      }
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[0] = yylloc;
    if (yyerrstatus_ == 3)
      {
	/* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

	if (yychar <= yyeof_)
	  {
	  /* Return failure if at end of input.  */
	  if (yychar == yyeof_)
	    YYABORT;
	  }
	else
	  {
	    yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
	    yychar = yyempty_;
	  }
      }

    /* Else will try to reuse lookahead token after shifting the error
       token.  */
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;

    yyerror_range[0] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (yyn != yypact_ninf_)
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	YYABORT;

	yyerror_range[0] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[1] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyempty_)
      yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval, &yylloc);

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (yystate_stack_.height () != 1)
      {
	yydestruct_ ("Cleanup: popping",
		   yystos_[yystate_stack_[0]],
		   &yysemantic_stack_[0],
		   &yylocation_stack_[0]);
	yypop_ ();
      }

    return yyresult;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (int yystate, int tok)
  {
    std::string res;
    YYUSE (yystate);
#if YYERROR_VERBOSE
    int yyn = yypact_[yystate];
    if (yypact_ninf_ < yyn && yyn <= yylast_)
      {
	/* Start YYX at -YYN if negative to avoid negative indexes in
	   YYCHECK.  */
	int yyxbegin = yyn < 0 ? -yyn : 0;

	/* Stay within bounds of both yycheck and yytname.  */
	int yychecklim = yylast_ - yyn + 1;
	int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
	int count = 0;
	for (int x = yyxbegin; x < yyxend; ++x)
	  if (yycheck_[x + yyn] == x && x != yyterror_)
	    ++count;

	// FIXME: This method of building the message is not compatible
	// with internationalization.  It should work like yacc.c does it.
	// That is, first build a string that looks like this:
	// "syntax error, unexpected %s or %s or %s"
	// Then, invoke YY_ on this string.
	// Finally, use the string as a format to output
	// yytname_[tok], etc.
	// Until this gets fixed, this message appears in English only.
	res = "syntax error, unexpected ";
	res += yytnamerr_ (yytname_[tok]);
	if (count < 5)
	  {
	    count = 0;
	    for (int x = yyxbegin; x < yyxend; ++x)
	      if (yycheck_[x + yyn] == x && x != yyterror_)
		{
		  res += (!count++) ? ", expecting " : " or ";
		  res += yytnamerr_ (yytname_[x]);
		}
	  }
      }
    else
#endif
      res = YY_("syntax error");
    return res;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const signed char Parser::yypact_ninf_ = -30;
  const short int
  Parser::yypact_[] =
  {
        30,    90,     4,    10,   136,     2,    30,   -30,   -30,    60,
      15,   -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,
     -30,   -30,   -30,   -30,   -30,   194,   194,   194,   165,   165,
     165,     0,    17,   -30,    -3,   -18,   -30,   -30,   120,   136,
     -30,   -30,   -30,   -30,   -30,    15,   -30,   136,   -30,   -30,
     -30,   -30,   -30,   -30,   -30,    -2,   -30,   136,   194,   194,
     194,   194,   194,   194,   165,   165,   165,   165,   165,   -30,
      39,    46,   -30,   -30,     1,   -30,   -30,   -30,   -30,   -30,
     -30,   -30,   -30,   -30,    -3,    -3,   -30,   -30,   -30,   136,
       3,   -30,   136,    51,   -30
  };

  /* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
     doesn't specify something else to do.  Zero means the default is an
     error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         2,     0,     0,     0,     0,     0,     3,     4,     5,     0,
       6,    10,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    19,    20,    18,    30,     0,     0,     0,     0,     0,
       0,     0,    32,    42,    46,    49,    15,    50,     0,     0,
      58,    55,     1,     7,     8,     9,    54,     0,    57,    59,
      33,    34,    35,    16,    17,     0,    11,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    51,
       0,     0,    56,    31,     0,    36,    37,    41,    40,    38,
      39,    44,    43,    45,    47,    48,    52,    53,    12,     0,
       0,    13,     0,     0,    14
  };

  /* YYPGOTO[NTERM-NUM].  */
  const signed char
  Parser::yypgoto_[] =
  {
       -30,   -30,   -30,    68,    -4,    -1,    49,   -29,   -30,    88,
      70,   -30,    71
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  Parser::yydefgoto_[] =
  {
        -1,     5,     6,     7,    31,    32,    33,    34,    35,    36,
       8,     9,    10
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If zero, do what YYDEFACT says.  */
  const signed char Parser::yytable_ninf_ = -1;
  const unsigned char
  Parser::yytable_[] =
  {
        41,    38,    42,    56,    88,    48,    91,    37,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    49,    22,
      67,    68,    23,    24,    50,    51,    52,    39,    64,    57,
      89,    73,    92,    65,    66,    71,    30,    70,    84,    85,
      58,    59,    86,    72,    60,    61,     1,     2,     3,    87,
      40,    62,    63,    74,    94,     0,     4,    75,    76,    77,
      78,    79,    80,    46,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    43,    22,    44,    45,    23,    24,
      25,    26,    27,     0,     0,    90,     0,     0,    93,    47,
      28,    29,    30,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,     0,    22,     0,     0,    23,    24,
      25,    26,    27,    81,    82,    83,    53,    54,    55,     0,
      28,    29,    30,    69,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,     0,    22,     0,     0,    23,    24,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
       0,    22,    30,     0,    23,    24,    25,    26,    27,     0,
       0,     0,     0,     0,     0,     0,    28,    29,    30,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,     0,
      22,     0,     0,    23,    24,    25,    26,    27,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    30,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,     0,    22,
       0,     0,    23,    24,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    30
  };

  /* YYCHECK.  */
  const signed char
  Parser::yycheck_[] =
  {
         4,     2,     0,     3,     3,     9,     3,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,     3,    15,
      38,    39,    18,    19,    25,    26,    27,    17,    31,    29,
      29,    33,    29,    36,    37,    39,    32,    38,    67,    68,
      23,    24,     3,    47,    27,    28,    16,    17,    18,     3,
      40,    34,    35,    57,     3,    -1,    26,    58,    59,    60,
      61,    62,    63,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     6,    15,     6,     6,    18,    19,
      20,    21,    22,    -1,    -1,    89,    -1,    -1,    92,    29,
      30,    31,    32,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    15,    -1,    -1,    18,    19,
      20,    21,    22,    64,    65,    66,    28,    29,    30,    -1,
      30,    31,    32,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    15,    -1,    -1,    18,    19,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    32,    -1,    18,    19,    20,    21,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    -1,    -1,    18,    19,    20,    21,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    15,
      -1,    -1,    18,    19,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    32
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,    16,    17,    18,    26,    42,    43,    44,    51,    52,
      53,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    15,    18,    19,    20,    21,    22,    30,    31,
      32,    45,    46,    47,    48,    49,    50,     3,    46,    17,
      40,    45,     0,    44,    51,    53,     3,    29,    45,     3,
      46,    46,    46,    50,    50,    50,     3,    29,    23,    24,
      27,    28,    34,    35,    31,    36,    37,    38,    39,     3,
      46,    45,    45,    33,    45,    46,    46,    46,    46,    46,
      46,    47,    47,    47,    48,    48,     3,     3,     3,    29,
      45,     3,    29,    45,     3
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  Parser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,    44,
      35,    47,    40,    41,    46,    38,    42,    37,    43,    45,
      58
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    41,    42,    42,    43,    43,    43,    43,    43,    43,
      44,    44,    44,    44,    44,    45,    45,    45,    46,    46,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    46,
      46,    46,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    48,    48,    48,    48,    49,    49,    49,    50,
      51,    51,    51,    51,    51,    52,    52,    52,    53,    53
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     0,     1,     1,     1,     1,     2,     2,     2,
       2,     3,     5,     7,     9,     1,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     1,     3,     3,     3,     1,     3,     3,     1,
       2,     3,     4,     4,     2,     2,     3,     2,     2,     2
  };

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const Parser::yytname_[] =
  {
    "\"end of file\"", "error", "$undefined", "EOL", "TK_ACC", "TK_C",
  "TK_AB", "TK_AT_DPTR", "TK_DPTR", "TK_AT_A_PLUS_PC", "TK_AT_A_PLUS_DPTR",
  "TK_AT_RI", "TK_RN", "I_CONSTANT", "F_CONSTANT", "STRING_LITERAL",
  "TK_CMD", "TK_MACRO", "TK_KEYWORD", "TK_DOLLAR", "TK_NOT", "TK_HIGH",
  "TK_LOW", "TK_SHL", "TK_MOD", "TK_BIT_PT", "TK_DB", "TK_SHIFT_LEFT",
  "TK_SHIFT_RIGHT", "','", "'#'", "'/'", "'('", "')'", "'.'", "'&'", "'*'",
  "'%'", "'+'", "'-'", "':'", "$accept", "startA", "prog_block",
  "cmd_text_line", "opand", "expr_elem", "not_expr", "multi_expr",
  "additive_expr", "expr", "macro_text_line", "db_list", "label_text_line", 0
  };
#endif

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        42,     0,    -1,    -1,    43,    -1,    44,    -1,    51,    -1,
      53,    -1,    43,    44,    -1,    43,    51,    -1,    43,    53,
      -1,    16,     3,    -1,    16,    45,     3,    -1,    16,    45,
      29,    45,     3,    -1,    16,    45,    29,    45,    29,    45,
       3,    -1,    16,    45,    29,    45,    29,    45,    29,    45,
       3,    -1,    50,    -1,    30,    50,    -1,    31,    50,    -1,
      18,    -1,    13,    -1,    15,    -1,     4,    -1,     5,    -1,
       6,    -1,     7,    -1,     8,    -1,     9,    -1,    10,    -1,
      11,    -1,    12,    -1,    19,    -1,    32,    50,    33,    -1,
      46,    -1,    20,    46,    -1,    21,    46,    -1,    22,    46,
      -1,    46,    23,    46,    -1,    46,    24,    46,    -1,    46,
      34,    46,    -1,    46,    35,    46,    -1,    46,    28,    46,
      -1,    46,    27,    46,    -1,    47,    -1,    48,    36,    47,
      -1,    48,    31,    47,    -1,    48,    37,    47,    -1,    48,
      -1,    49,    38,    48,    -1,    49,    39,    48,    -1,    49,
      -1,    17,     3,    -1,    17,    46,     3,    -1,    17,    46,
      46,     3,    -1,    18,    17,    45,     3,    -1,    52,     3,
      -1,    26,    45,    -1,    52,    29,    45,    -1,    52,    45,
      -1,    18,    40,    -1,    53,     3,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned char
  Parser::yyprhs_[] =
  {
         0,     0,     3,     4,     6,     8,    10,    12,    15,    18,
      21,    24,    28,    34,    42,    52,    54,    57,    60,    62,
      64,    66,    68,    70,    72,    74,    76,    78,    80,    82,
      84,    86,    90,    92,    95,    98,   101,   105,   109,   113,
     117,   121,   125,   127,   131,   135,   139,   141,   145,   149,
     151,   154,   158,   163,   168,   171,   174,   178,   181,   184
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  Parser::yyrline_[] =
  {
         0,    90,    90,    91,    95,    96,    97,    98,    99,   100,
     103,   104,   105,   106,   115,   128,   129,   135,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   170,   171,   180,   189,   198,   209,   219,   228,
     239,   249,   262,   263,   274,   285,   299,   300,   310,   324,
     329,   330,   337,   345,   354,   360,   361,   362,   366,   367
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "):" << std::endl;
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    30,     2,    37,    35,     2,
      32,    33,    36,    38,    29,    39,    34,    31,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    40,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 226;
  const int Parser::yynnts_ = 13;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 42;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 41;

  const unsigned int Parser::yyuser_token_number_max_ = 283;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


} // asm_lex_stuff

/* Line 1053 of lalr1.cc  */
#line 1555 "parser.cpp"


/* Line 1055 of lalr1.cc  */
#line 372 "ly/parser.yy"
 /*** Additional Code ***/

void asm_lex_stuff::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    std::cout<<"ERROR:"<<l<<m<<std::endl;
}

