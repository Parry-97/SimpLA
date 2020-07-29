#include "def.h"

char *tabtypes[] =
   {
         "VOID",
         "REAL",
         "INTEGER",
         "STRING",
         "BOOLEAN",
         "INTCONST",
         "BOOLCONST",
         "STRCONST",
         "REALCONST",
         "ID",
         "WRITE",
         "WRITELN",
         "BREAK",
         "NONTERMINAL"
     };

char *tabnonterm[] =
    {
        "N_PROGRAM",
        "N_VAR_DECL_LIST",
        "N_VAR_DECL",
        "N_ID_LIST",
        "N_TYPE",
        "N_FUNC_DECL_LIST",
        "N_FUNC_DECL",
        "N_OPT_PARAM_LIST",
        "N_PARAM_LIST",
        "N_PARAM_DECL",
        "N_BODY",
        "N_STAT_LIST",
        "N_STAT",
        "N_ASSIGN_STAT",
        "N_IF_STAT",
        "N_OPT_ELSE_STAT",
        "N_WHILE_STAT",
        "N_FOR_STAT",
        "N_RETURN_STAT",
        "N_OPT_EXPR",
        "N_READ_STAT",
        "N_WRITE_STAT",
        "N_WRITE_OP",
        "N_EXPR_LIST",
        "N_EXPR",
        "N_LOGIC_OP",
        "N_BOOL_TERM",
        "N_REL_OP",
        "N_REL_TERM",
        "N_LOW_PREC_OP",
        "N_LOW_TERM",
        "N_HIGH_PREC_OP",
        "N_FACTOR",
        "N_UNARY_OP",
        "N_CONST",
        "N_FUNC_CALL",
        "N_OPT_EXPR_LIST",
        "N_COND_EXPR",
        "N_CAST",
        "N_DECL",
        "N_ASSIGN",
        "N_ERROR",
        "N_LOGIC_EXPR",
        "N_REL_EXPR",
        "N_MATH_EXPR",
        "N_NEG_EXPR",
        "N_CASTING"};

void treeprint(Pnode root, int indent)
{
  int i;
  Pnode p;

  for (i = 0; i < indent; i++)
    printf("    ");
  printf("%s", (root->type == T_NONTERMINAL ? tabnonterm[root->value.ival] : tabtypes[root->type]));
  if (root->type == T_ID || root->type == T_STRCONST)
    printf(" (%s)", root->value.sval);
  else if (root->type == T_INTCONST)
    printf(" (%d)", root->value.ival);
  else if (root->type == T_REALCONST)
    printf(" (%f)", root->value.fval);
  else if (root->type == T_BOOLCONST)
    printf(" (%s)", (root->value.ival == TRUE ? "true" : "false"));
  printf("\n");
  for (p = root->child; p != NULL; p = p->brother)
    treeprint(p, indent + 1);
}
