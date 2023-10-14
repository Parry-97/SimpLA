#ifndef DEF_H
#define DEF_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SHIFT 4
#define MAXARGS 3
#define SYMTAB_SIZE 2999

#define YYSTYPE Pnode

extern int yyparse(void);
extern struct bucket *symbol_table;
extern struct SCode *tot_prog;
extern struct SCode *current_prog;

extern struct bucket *temp_env;
extern struct bucket **temp_descr;
extern struct bucket *current_env;
extern char *id_func;
extern int *current_oid;
extern int oid_g;
extern struct SCode *sub_prog10 ;
extern char *lista_id[SYMTAB_SIZE];
extern FILE *yyin;

typedef enum
{
    VAR,
    PAR,
    FUN,
    C_NULL
} symb_class;

typedef enum
{
    S_INTEGER,
    S_REAL,
    S_STRING,
    S_BOOLEAN_,
    S_VOID_,
    T_NULL
} symb_type;

struct param_formali
{
    int num;
    struct bucket **descr;
};

union symb_env {
    struct bucket *local_env; 
    bool need_env; 
};


struct bucket
{
    char *nome;
    symb_class classe;
    int oid;
    symb_type tipo;
    union symb_env env;
    struct param_formali formali;
    struct bucket *next;
};

typedef enum 
{
    N_PROGRAM,
    N_VAR_DECL_LIST,
    N_VAR_DECL,
    N_ID_LIST,
    N_TYPE,
    N_FUNC_DECL_LIST,
    N_FUNC_DECL,
    N_OPT_PARAM_LIST,
    N_PARAM_LIST,
    N_PARAM_DECL,
    N_BODY,
    N_STAT_LIST,
    N_STAT,
    N_ASSIGN_STAT,
    N_IF_STAT,
    N_OPT_ELSE_STAT,
    N_WHILE_STAT,
    N_FOR_STAT,
    N_RETURN_STAT,
    N_OPT_EXPR,
    N_READ_STAT,
    N_WRITE_STAT,
    N_WRITE_OP,
    N_EXPR_LIST,
    N_EXPR,
    N_LOGIC_OP,
    N_BOOL_TERM,
    N_REL_OP,
    N_REL_TERM,
    N_LOW_PREC_OP,
    N_LOW_TERM,
    N_HIGH_PREC_OP,
    N_FACTOR,
    N_UNARY_OP,
    N_CONST,
    N_FUNC_CALL,
    N_OPT_EXPR_LIST,
    N_COND_EXPR,
    N_CAST,
    N_DECL,
    N_ASSIGN,
    N_ERROR,
    N_LOGIC_EXPR,
    N_REL_EXPR,
    N_MATH_EXPR,
    N_NEG_EXPR,
    N_CASTING
} Nonterminal;

typedef enum
{
    T_VOID,
    T_REAL,
    T_INTEGER,
    T_STRING,
    T_BOOLEAN,
    T_INTCONST,
    T_BOOLCONST,
    T_STRCONST,
    T_REALCONST,
    T_ID,
    T_WRITE,
    T_WRITELN,
    T_BREAK,
    T_KEYWORD,
    T_NONTERMINAL,
    T_RETURN,
    T_ELSE,
    T_READ,
    T_AND,
    T_OR,
    T_NOT,
    T_LT,
    T_LE,
    T_EQ,
    T_NE,
    T_GT,
    T_GE,
    T_PLUS,
    T_MINUS,
    T_MUL,
    T_DIV 
} Typenode;

typedef enum
{
    VARI,
    LCI,
    LCR,
    LCS,
    LOD,
    STO,
    JMF,
    JMP,
    EQU,
    NEQ,
    GTI,
    GEI,
    LTI,
    LEI,
    GTR,
    GER,
    LTR,
    LER,
    GTS,
    GES,
    LTS,
    LES,
    ADI,
    SBI,
    MUI,
    DVI,
    ADR,
    SBR,
    MUR,
    DVR,
    UMI,
    UMR,
    NEG,
    PSH,
    GOT,
    POP,
    TOI,
    TOR,
    INP,
    OUT,
    ENT,
    INC,
    RET,
    SIZ,
    STP,
    BRK,
    NIK
} Operator;


typedef union
{
    int ival;
    char *sval;
    enum {FALSE, TRUE} bval;
    float fval;
} Value;

struct data_mem
{
    char *id;
    Value val;
    int size;
};

struct Stat
{
    int address;
    Operator op;
    Value args[3];
    struct Stat *next;
};



struct SCode{
    struct Stat *first;
    int num;
    struct Stat *last;
};

typedef struct snode
{
    Typenode type;
    Value value;
    symb_type sem_type;
    int is_gen;
    int op_code;
    struct snode *child, *brother;
} Node;

typedef Node *Pnode;


extern Pnode root;

struct Ostack_node
{
    int size;
    Value val;
};

struct Ostack 
{
    int top;
    unsigned capacity;
    struct Ostack_node *stack;
};

struct Astack
{
    int top;
    unsigned capacity;
    struct Astack_node *stack;
};

struct Astack_node
{
    int num_objs;
    struct Ostack *objects;
    int ret_addr;
    int call_oid;
    struct data_mem *local_mem;
    struct Astack_node *next;
};

char *newstring(char *),
     *remove_quotes(char *),
     *print_args(struct Stat stat);

int yylex(),
    count_var(struct bucket *table),
    hash(const char *id);

Pnode nontermnode(Nonterminal), 
      idnode(), 
      keynode(Typenode), 
      intconstnode(),
      strconstnode(),
      boolconstnode(),
      newnode(Typenode),
      realconstnode();

struct param_formali init_pf(int numero_param);

struct bucket *find_in_chain_senza_errore(char *id, struct bucket *bc), 
              *init_bucket(),
              *find_in_chain(char *id, struct bucket *bc),
              *init_symbol_table();

int conta_fratelli(Pnode fratello, int contatore),
    get_func_num_variables(char *id),
    count_var_in_chain(struct bucket *bc),
    count_var(struct bucket *env_),
    get_type_size(Typenode type),
    get_func_entry_point(struct SCode *prog, char *id),
    create_int_temp(struct bucket *env, int *oid_l),
    get_next_stats_num(Pnode nextstat),
    add_temp_in_chain(struct bucket *bc, int *oid_l),
    isAEmpty(struct Astack *root),
    isOEmpty(struct Ostack *root);

char *get_format(symb_type txpe),
     *print_args(struct Stat stat);

void treeprint(Pnode, int),
    analizza(Pnode root, struct bucket symbtab[]),
    print_symbol_table(struct bucket symbtab[]),
    yyerror(),
    add_in_chain(char *id, struct bucket *bc),
    add_in_chain_args(char *id, symb_class classe, symb_type tipo, struct bucket *bc, int *oid_gg),
    add_func_in_chain_args(char *id, symb_type tipo, struct param_formali formali, struct bucket local_env[], struct bucket *bc, int *oid_gg),
    print_bucket(struct bucket *bucket),
    insert_by_ID(char *id, struct bucket symbtab[]),
    insert(char *id, symb_class classe, symb_type tipo, struct bucket symbtab[], int *oid_gg),
    insert_func(char *id, symb_type tipo, struct param_formali formali, struct bucket local_env[], struct bucket symbtab[]),
    codeprint(struct SCode *prog),
    save_to_file(struct SCode *prog, char *filename),
    generateCode(Pnode p, struct bucket *symbtab, struct SCode *prog),
    relocateAddress(struct SCode code, int offset),
    generateID_Code(Pnode p, struct bucket *symbtab, struct SCode *prog),
    apush(struct Astack *stack, struct Ostack *objects, int call_oid, struct data_mem *local_mem ,int num_objs, int ret_addr),
    opush(struct Ostack *stack, Value val, int size),
    executeSCode(char *filename),
    correct_breaks(struct SCode *prog),
    correct_returns(struct SCode *prog);

struct SCode appcode(struct SCode code1, struct SCode code2),
    endcode(),
    makecode_from_stat(struct Stat stat),
    concode(struct SCode code1, struct SCode code2, ...),
    makecode(Operator op),
    makecode1(Operator op, int arg),
    makecode2(Operator op, int arg1, int arg2),
    makecode3(Operator op, int arg1, int arg2, int arg3),
    make_psh_pop(int num_formals, int num_variables, int entry),
    make_lci(int i),
    makeout(Operator op, int n, char *format),
    makeread(Operator op, char *format, int n, int n2),
    make_lcr(float r),
    make_lcs(char *s);

struct Stat *newstat(Operator op);

struct Stat *get_scode_from_file(char *filename);

struct Ostack_node newONode();

struct Ostack_node opop(struct Ostack *ostack);

struct Astack *createAStack(unsigned capacity);
struct Ostack *createOStack(unsigned capacity);

struct Astack_node newANode();
struct Astack_node apop(struct Astack *root);

struct Ostack *createOStack(unsigned capacity);
int isFull(struct Ostack *stack);
struct Ostack_node newONode();
struct Ostack_node opeek(struct Ostack *ostack);
struct Astack_node apeek(struct Astack *astack);


char *save_args(struct Stat stat);

struct Stat *get_scode_from_txt(char *filename);

void save_to_txt(struct SCode *prog, char *filename),
     get_args_from_str(struct Stat *pStat, char *str_args);

#endif