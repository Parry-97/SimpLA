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
        "N_FUNC_DECL_LIST",
        "N_FUNC_DECL",
        "N_OPT_PARAM_LIST",
        "N_PARAM_DECL",
        "N_STAT_LIST",
        "N_ASSIGN_STAT",
        "N_IF_STAT",
        "N_WHILE_STAT",
        "N_FOR_STAT",
        "N_RETURN_STAT",
        "N_READ_STAT",
        "N_WRITE_STAT",
        "N_EXPR_LIST",
        "N_FUNC_CALL",
        "N_COND_EXPR",
        "N_LOGIC_EXPR",
        "N_REL_EXPR",
        "N_MATH_EXPR",
        "N_NEG_EXPR",
        "N_CASTING",
        "N_TVECTOR",
        "N_VEC_CONSTR",
        "N_LHS"};

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
