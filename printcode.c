#include <stdlib.h>
#include "string.h"
#include "def.h"


char *codeops[] =
    {
        "VARI",
        "LCI",
        "LCR",
        "LCS",
        "LOD",
        "STO",
        "JMF",
        "JMP",
        "EQU",
        "NEQ",
        "GTI",
        "GEI",
        "LTI",
        "LEI",
        "GTR",
        "GER",
        "LTR",
        "LER",
        "GTS",
        "GES",
        "LTS",
        "LES",
        "ADI",
        "SBI",
        "MUI",
        "DVI",
        "ADR",
        "SBR",
        "MUR",
        "DVR",
        "UMI",
        "UMR",
        "NEG",
        "PSH",
        "GOT",
        "POP",
        "TOI",
        "TOR",
        "INP",
        "OUT",
        "ENT",
        "INC",
        "RET",
        "SIZ",
        "STP"};

void codeprint(struct SCode *prog) {
    struct Stat *iter_stat = (struct Stat *)malloc(sizeof(struct Stat));
    
    iter_stat = prog->first;

    while(iter_stat != NULL)
    {
        printf("%s %s\n", codeops[iter_stat->op] , print_args(*iter_stat));
        iter_stat = iter_stat->next;
    }
    
}

char * print_args(struct Stat stat) {

    char * str_args = (char*)malloc(10*sizeof(char));
    


    switch (stat.op)
    {
    case VARI: 
        sprintf(str_args, "%d",stat.args[0].ival);
        break;

    case LCI:
        sprintf(str_args, "%d", stat.args[0].ival);
        break;

    case LCR:
        sprintf(str_args, "%f", stat.args[0].fval);
        break;

    case LCS:
        sprintf(str_args, "%s", stat.args[0].sval);
        break;

    case LOD:
        sprintf(str_args, "%d %d", stat.args[0].ival, stat.args[1].ival);
        break;

    case STO:
        sprintf(str_args, "%d %d", stat.args[0].ival, stat.args[1].ival);
        break;

    case JMF:
        sprintf(str_args, "%d", stat.args[0].ival);
        break;

    case JMP:
        sprintf(str_args, "%d", stat.args[0].ival);
        break;

    case PSH:
        sprintf(str_args, "%d %d", stat.args[0].ival, stat.args[1].ival);
        break;

    case GOT:
        sprintf(str_args, "%d", stat.args[0].ival);
        break;

    case INP:
        sprintf(str_args, "%s %d %d", stat.args[0].sval, stat.args[1].ival, stat.args[2].ival);
        break;

    case OUT:
        sprintf(str_args, "%d %s", stat.args[0].ival, stat.args[1].sval);
        break;

    case ENT:
        sprintf(str_args, "%d", stat.args[0].ival);
        break;

    case INC:
        sprintf(str_args, "%d %d", stat.args[0].ival, stat.args[1].ival);
        break;

    case RET:
        sprintf(str_args, "%d", stat.args[0].ival);
        break;

    case SIZ:
        sprintf(str_args, "%d", stat.args[0].ival);
        break;

    default: return "";
        break;
    }

    return str_args;
}