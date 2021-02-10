%{
#include "def.h"
#include <string.h>

#define YYSTYPE Pnode

extern struct SCode *tot_prog;
struct SCode *current_prog;

FILE *yyin;

struct SCode *sub_prog10 ;

extern char *yytext;
extern Value lexval;
extern int line;
extern FILE *yyin;
extern int oid_g;

char *lista_id[SYMTAB_SIZE];
char *lista_id_locale[50];
int indice_locale = 0;

extern struct bucket *symbol_table;

int indice = 0;
Pnode root = NULL;

struct bucket *temp_env;
struct bucket **temp_descr;
struct bucket *current_env;

char *id_func;
struct symb_type current_type; /** Serve per memorizzare il tipo di una funzione*/
int numero_param_formali = 0;
int oid_locale = 0;
int *current_oid;
int isRead = 0;

%}

//TODO: Test with vector code!

%token FUNC BODY END IF THEN ELSE WHILE DO FOR TO BREAK RETURN WRITE WRITELN READ AND OR NOT EQ NE GE GT LT LE MUL PLUS DIV MINUS DECL VECTOR OF IN VOID INTEGER STRING BOOLEAN REAL
%token REALCONST INTCONST STRCONST ID BOOLCONST ASSIGN ERROR

%%

program : var_decl_list func_decl_list body '.' {root = $$ = nontermnode(N_PROGRAM); $$->child = nontermnode(N_VAR_DECL_LIST); $$->child->child = $1; 
                                                 $$->child->brother = nontermnode(N_FUNC_DECL_LIST); $$->child->brother->child = $2;
                                                 $$->child->brother->brother = $3; insert_func("smain",(struct symb_type){S_VOID_,1,NULL},init_pf(0),NULL,symbol_table);};

var_decl_list : var_decl var_decl_list {$$ = $1; $1->brother = $2;}
              | {$$ = NULL;};

var_decl :id_list DECL type ';' {$$ = nontermnode(N_VAR_DECL); $$->child = nontermnode(N_ID_LIST); $$->child->child = $1; $$->child->brother = $3;
                                                        for (int i = 0; i < indice; i++)
                                                        {
                                                          insert(lista_id[i],VAR, $3->sem_type, current_env, current_oid);
                                                        }
                                                        indice=0;
                                                       };

id_list : ID {$$ = idnode();} ',' id_list {$$ = $2; $2->brother = $4;
          if (!isRead) {
            lista_id[indice++] = $2->value.sval;    
          }
          }
        | ID {$$ = idnode(); 
        if (!isRead) {
            lista_id[indice++] = $$->value.sval;    
          }};

type : atomic_type {$$ = $1;}
      | vector_type { $$ = $1;};

vector_type : VECTOR '[' INTCONST {$$=intconstnode();} ']' OF type {$$ = nontermnode(N_TVECTOR); $$->child = $4; 
                                          $$->child->brother = $7;
                                          //Devo continuare a concatenare tipi
                                          $$->sem_type = (struct symb_type){S_VECTOR, $4->value.ival, &($7->sem_type)};};

atomic_type : INTEGER {$$ = keynode(T_INTEGER);$$->sem_type = (struct symb_type){S_INTEGER,1,NULL};}
            | REAL {$$ = keynode(T_REAL); $$->sem_type = (struct symb_type){S_REAL,1,NULL};} 
            | STRING {$$ = keynode(T_STRING); $$->sem_type = (struct symb_type){S_STRING,1,NULL};}
            | BOOLEAN {$$ = keynode(T_BOOLEAN); $$->sem_type = (struct symb_type){S_BOOLEAN_,1,NULL};}
            | VOID {$$ = keynode(T_VOID); $$->sem_type = (struct symb_type){S_VOID_,1,NULL};};
 
func_decl_list : func_decl func_decl_list {$$ = $1; $1->brother = $2;}
               | {$$ = NULL;};

func_decl : FUNC ID {$$ = idnode(); id_func = $$->value.sval; current_env = temp_env; current_oid = &oid_locale;}'(' opt_param_list ')' DECL type var_decl_list body ';'
            {current_env = symbol_table; current_oid = &oid_g; $$ = nontermnode(N_FUNC_DECL); 
            $$->child = $3;

            if ($5 == NULL)
            {
              $3->brother = $8;
            }
            else
            {
              $3->brother = $5;
              $5->brother = $8;
            }
            
            $8->brother = nontermnode(N_VAR_DECL_LIST); $8->brother->child = $9; $8->brother->brother = $10;
            

            struct param_formali pf = init_pf(numero_param_formali);
            pf.descr = temp_descr;
            insert_func(id_func,$8->sem_type,pf,temp_env,symbol_table);
            
            numero_param_formali = 0;
            oid_locale = 0;
            temp_env = init_symbol_table(SYMTAB_SIZE);
            temp_descr = (struct bucket **)malloc(25 * sizeof(struct bucket *));};

            

opt_param_list : param_list {$$ = nontermnode(N_OPT_PARAM_LIST); $$->child = $1;}
               | {$$ = NULL;};

param_list : param_decl ',' param_list {$$ = $1; $1->brother = $3;}
           | param_decl {$$ = $1;};

param_decl : {numero_param_formali++;}ID {$$ = idnode();} DECL type { $$ = nontermnode(N_PARAM_DECL); $$->child = $3; $3->brother = $5;
                                                                      insert($3->value.sval, PAR, $5->sem_type, current_env, current_oid);
                                                                    };

body : BODY stat_list END {$$ = nontermnode(N_STAT_LIST); $$->child = $2;};

stat_list : stat ';' stat_list {$$ = $1; $1->brother = $3;}
          | stat ';' {$$ = $1;};

stat : assign_stat {$$ = $1;}
     | if_stat {$$ = $1;}
     | while_stat {$$ = $1;}
     | for_stat {$$ = $1;} 
     | return_stat {$$ = $1;}
     | read_stat {$$ = $1;}
     | write_stat {$$ = $1;}
     | func_call {$$ = $1;}
     | BREAK {$$ = keynode(T_BREAK);};

//TODO: Sostituire con varname magari e verificare roba di idnode
assign_stat : lhs ASSIGN expr {$$ = nontermnode(N_ASSIGN_STAT); $$->child = $1; $$->child->brother = $3;};

lhs : ID {$$ = idnode();} | indexing {$$ = $1;};


vector_construction : VECTOR '('expr_list')' {$$ = nontermnode(N_VEC_CONSTR); $$->child = nontermnode(N_EXPR_LIST);
                                              $$->child->child = $3;};

indexing : lhs'['expr']' {$$ = nontermnode(N_LHS); $$->child = $1; $$->child->brother = $3;};

if_stat : IF expr THEN stat_list opt_else_stat END {$$ = nontermnode(N_IF_STAT); $$->child = $2;
          $2->brother = nontermnode(N_STAT_LIST); $2->brother->child = $4; $2->brother->brother = $5;};

opt_else_stat : ELSE stat_list {$$ = nontermnode(N_STAT_LIST); $$->child = $2;}
              | {$$ = NULL;};

while_stat : WHILE expr DO stat_list END {$$ = nontermnode(N_WHILE_STAT); $$->child = $2;
             $2->brother = nontermnode(N_STAT_LIST); $2->brother->child = $4;};

for_stat : FOR ID {$$ = idnode();} ASSIGN expr TO expr DO stat_list END {$$ = nontermnode(N_FOR_STAT); $$->child = $3; 
            $3->brother = $5; $5->brother = $7; $7->brother = nontermnode(N_STAT_LIST); $7->brother->child = $9;};

return_stat : RETURN opt_expr {$$ = nontermnode(N_RETURN_STAT); $$->child = $2;};

opt_expr : expr {$$ = $1;}
         | {$$ = NULL;};

read_stat : READ {isRead = 1;} '(' id_list{isRead = 0;} ')' {$$ = nontermnode(N_READ_STAT);$$->child = nontermnode(N_ID_LIST); $$->child->child = $4;};

write_stat : write_op '(' expr_list ')' {$$ = nontermnode(N_WRITE_STAT); $$->op_code = $1->type; $$->child = $1; $1->brother = nontermnode(N_EXPR_LIST); 
                                        $1->brother->child = $3;};

write_op : WRITE {$$ = keynode(T_WRITE);}
         | WRITELN {$$ = keynode(T_WRITELN);};

expr_list : expr ',' expr_list {$$ = $1; $1->brother = $3;}
          | expr {$$ = $1;};

expr : expr logic_op bool_term {$$ = nontermnode(N_LOGIC_EXPR);$$->child = $1; $1->brother = $3;
                                $$->op_code = $2->type;
                                }
      | bool_term {$$ = $1;};

logic_op : AND {$$ = keynode(T_AND);}
         | OR {$$ = keynode(T_OR);};

bool_term : rel_term rel_op rel_term  {$$ = nontermnode(N_REL_EXPR); $$->child = $1; $1->brother = $3;
                                        $$->op_code = $2->type;
                                      }
          | rel_term {$$ = $1;};

rel_op : EQ{$$ = keynode(T_EQ);}
       | NE{$$ = keynode(T_NE);}
       | GT {$$ = keynode(T_GT);}
       | GE {$$ = keynode(T_GE);}
       | LT {$$ = keynode(T_LT);}
       | LE {$$ = keynode(T_LE);}
       | IN {$$ = keynode(T_IN);};

rel_term : rel_term low_prec_op low_term {$$ = nontermnode(N_MATH_EXPR); $$->child = $1; $1->brother = $3;
                                          $$->op_code = $2->type;
                                         }
         | low_term {$$ = $1;};

low_prec_op : PLUS {$$ = keynode(T_PLUS);}
            | MINUS {$$ = keynode(T_MINUS);};

low_term : low_term high_prec_op factor {$$ = nontermnode(N_MATH_EXPR); $$->child = $1; $1->brother = $3;
                                          $$->op_code = $2->type;
                                        }
         | factor {$$ = $1;};

high_prec_op : MUL {$$ = keynode(T_MUL);}
             | DIV {$$ = keynode(T_DIV);};


factor : unary_op factor {$$ = nontermnode(N_NEG_EXPR); $$->child = $2;
                          $$->op_code = $1->type;
                          }

       | '(' expr ')' {$$ = $2;}
       | lhs {$$ = $1;}
       | vector_construction {$$=$1;}
       | const {$$ = $1;}
       | func_call {$$ = $1;}
       | cond_expr {$$ = $1;}
       | cast '(' expr ')' {$$ = nontermnode(N_CASTING); $$->child = $3;
                            $$->op_code = $1->type;
                           };

unary_op : MINUS {$$ = keynode(T_MINUS);}
         | NOT {$$ = keynode(T_NOT);};


const : INTCONST {$$ = intconstnode();}
      | REALCONST {$$ = realconstnode();}
      | STRCONST {$$ = strconstnode();}
      | BOOLCONST {$$ = boolconstnode();};

func_call : ID {$$ = idnode();} '(' opt_expr_list ')' {$$ = nontermnode(N_FUNC_CALL); $$->child = $2; $2->brother = $4;};

opt_expr_list : expr_list {$$ = nontermnode(N_EXPR_LIST); $$->child = $1;}
              | {$$ = NULL;};

cond_expr : IF expr THEN expr ELSE expr END {$$ = nontermnode(N_COND_EXPR); $$->child = $2; $2->brother = $4; $4->brother = $6;};

cast : INTEGER {$$ = keynode(T_INTEGER);}
     | REAL {$$ = keynode(T_REAL);};


%%

Pnode nontermnode(Nonterminal nonterm)
{
    Pnode p = newnode(T_NONTERMINAL);
    p->value.ival = nonterm;
    return(p);
}

Pnode idnode()
{
    Pnode p = newnode(T_ID);
    p->value.sval = lexval.sval;
    return(p);
}

Pnode keynode(Typenode keyword)
{
    return(newnode(keyword));
}

Pnode intconstnode()
{
    Pnode p = newnode(T_INTCONST);
    p->value.ival = lexval.ival;
    p->sem_type = (struct symb_type){S_INTEGER,1,NULL};
    return(p);
}

Pnode realconstnode()
{
    Pnode p = newnode(T_REALCONST);
    p->value.fval = lexval.fval;
    p->sem_type = (struct symb_type){S_REAL, 1, NULL};
    return(p);
}

Pnode strconstnode()
{
    Pnode p = newnode(T_STRCONST);
    p->value.sval = lexval.sval;
    p->sem_type = (struct symb_type){S_STRING, 1, NULL};
    return(p);
}

Pnode boolconstnode()
{
  Pnode p = newnode(T_BOOLCONST);
  p->value.bval = lexval.bval;
  p->sem_type = (struct symb_type){S_BOOLEAN_, 1, NULL};
  return(p);
}

Pnode newnode(Typenode tnode)
{
  Pnode p = malloc(sizeof(Node));
  p->type = tnode;
  p->is_gen = 0;
  p->child = p->brother = NULL;
  return(p);
}

int main(int argc, char **argv)
{
  symbol_table = init_symbol_table(SYMTAB_SIZE);
  temp_env = init_symbol_table(SYMTAB_SIZE);
  temp_descr = (struct bucket **)malloc(25 * sizeof(struct bucket *));
  current_env = symbol_table; 
  id_func = (char *)malloc(140);
  current_oid = &oid_g;
  //sub_prog10 = (struct SCode *)malloc(sizeof(struct SCode));
  //tot_prog = (struct SCode *)malloc(sizeof(struct SCode));
  //current_prog = (struct SCode *)malloc(sizeof(struct SCode));
  int result;

  for (int i = 0; i < SYMTAB_SIZE; i++)
  {
    lista_id[i] = (char * )malloc(140);
  }

  if (argc >= 2) {
    if ((yyin = fopen(argv[1], "r")) == NULL){
       fprintf(stderr,"ERRORE SIMPLAC: FILE NON ESISTE!");
       // Program exits if the file pointer returns NULL.
       exit(-1);
   }
  }
  else {
      fprintf(stderr,"ERRORE SIMPLAC: INDICARE FILE DA COMPILARE");
       // Program exits if the file pointer returns NULL.
       exit(-1);
  }
    

  if ((result = yyparse()) == 0) {
    //Togliere commento sulla funzione treeprint per visualizzare l'albero sintattico astratto a video
    treeprint(root, 0);

    //print_symbol_table(symbol_table);
    
    /*analizza(root, symbol_table);
    
    *sub_prog10 = endcode();
    generateCode(root, symbol_table, sub_prog10);
    int size;
    size = sub_prog10->num;

    *tot_prog = appcode(makecode1(SIZ,size), make_psh_pop(0, count_var(symbol_table), get_func_entry_point(sub_prog10,"smain")));
    *tot_prog = appcode(*tot_prog, makecode(STP));
    *tot_prog = appcode(*tot_prog,*sub_prog10);

    printf("---- Compilazione di Codice SimpLA avvenuta con successo -----\n");
    //Togliere commento sulla funzione codeprint per visualizzare il codice intermedio SCode a video
    codeprint(tot_prog);

    char *s_filename = strcat(argv[1],".sim");
    save_to_txt(tot_prog, s_filename);

    //printf("---- Test Code: -----\n");
    //get_scode_from_file(s_filename);

    //executeSCode(s_filename);*/
  }
  
  return(result);
}

void yyerror(int argc)
{
  fprintf(stderr, "Line %d: syntax error on symbol \"%s\"\n",
          line, yytext);
  exit(-1);
}
