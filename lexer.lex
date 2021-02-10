%{
    #include <stdlib.h>
    #include "parser.h"
    #include "def.h"
    Value lexval;
    int line = 1;
    //TODO: add lex rule for comments
    
%}
%option noyywrap

spacing     ([ \t])+
letter      [A-Za-z]
digit       [0-9]
intconst    {digit}+
realconst   {intconst}"."{intconst}
strconst    \"([^\"])*\"
boolconst   false|true
id          {letter}({letter}|{digit})*
sugar       [()\{\};,\[\]]

%%

{spacing}   ;
\n          {line++;}
func        {return(FUNC);}
body        {return(BODY);}
end         {return(END);}
if          {return(IF);}
then        {return(THEN);}
else        {return(ELSE);}
while       {return(WHILE);}
do          {return(DO);}
for         {return(FOR);}
to          {return(TO);}
break       {return(BREAK);}
return      {return(RETURN);}
write       {return(WRITE);}
writeln     {return(WRITELN);}
read        {return(READ);}
and         {return(AND);}
or          {return(OR);}
not         {return(NOT);}
"<"         {return(LT);}
"<="        {return(LE);}
">"         {return(GT);}
">="        {return(GE);}
"=="        {return(EQ);}
"!="        {return(NE);}
"+"         {return(PLUS);}
"-"         {return(MINUS);}
"*"         {return(MUL);}
"/"         {return(DIV);}
":"         {return(DECL);}
vector      {return(VECTOR);}
"of"        {return(OF);}
"in"        {return(IN);}
void        {return(VOID);}
integer     {return(INTEGER);}
string      {return(STRING);}
boolean     {return(BOOLEAN);}
real        {return(REAL);}
{realconst} {lexval.fval = atof(yytext); return(REALCONST);}
{intconst}  {lexval.ival = atoi(yytext); return(INTCONST);}
{strconst}  {lexval.sval = remove_quotes(newstring(yytext)); return(STRCONST);}
{boolconst} {
               lexval.bval = (yytext[0] == 'f' ? FALSE : TRUE);
               return(BOOLCONST);
            }
{id}        {lexval.sval = newstring(yytext); return(ID);}
{sugar}     {return(yytext[0]);}
"."         {return(yytext[0]);}    
"="         {return(ASSIGN);}
'\nnn'      {return(ERROR);} 

%%
char *newstring(char *s)
{
  char *p;
  
  p = malloc(strlen(s)+1);
  strcpy(p, s);
  return(p);
}

char *remove_quotes(char *s) {
    char *clean;
    clean = (char *)malloc(sizeof(char) * strlen(s));
    int j = 1;
    int i;
    for(i = 0; s[j] != '\"'; i++) {
        clean[i] = s[j];
        j++;
    }
    clean[i] = '\0';
    return clean;
}