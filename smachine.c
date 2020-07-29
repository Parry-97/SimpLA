#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "def.h"
#include <stdbool.h>

struct Astack *aroot;
struct Ostack *oroot;

struct data_mem *global_mem;

char **string_table;

void executeSCode(struct SCode prog)
{
    string_table = (char **)calloc(sizeof(char *), SYMTAB_SIZE);

    char *format = (char *)malloc(sizeof(char) * 100);

    char *s1 = (char *)malloc(sizeof(char) * 100);
    char *s2 = (char *)malloc(sizeof(char) * 100);

    char *read_format = (char *)malloc(sizeof(char) * 25);

    struct Stat *code_mem = (struct Stat *)calloc(sizeof(struct Stat), prog.num);
    struct Stat *code_stat = prog.first;

    struct data_mem lod_data;

    int stat_counter = 0;

    while (code_stat != NULL)
    {
        code_mem[stat_counter] = *code_stat;
        code_stat = code_stat->next;
        stat_counter++;
    }

    int num1;
    int num2;
    float num_f1;
    float num_f2;

    Value ris;
    Value ovalue;
    Value read_value;
    Value sto_val;
    Value jmf_decision;
    Value v1;
    Value v2;

    struct Ostack_node node1 = newONode();
    struct Ostack_node node2 = newONode();

    int env = 0;
    int global_obj_id = 0;
    int current_obj_id = 0;
    bool end_of_program = false;

    global_mem = (struct data_mem *)malloc(sizeof(struct data_mem) * SYMTAB_SIZE);

    struct data_mem *current_mem;

    aroot = createAStack(200);
    oroot = createOStack(200);

    struct Stat *scode = prog.first;

    current_mem = global_mem;
    for (int i = 0; i < prog.num && !end_of_program; i++)
    {
        switch (code_mem[i].op)
        {

        case VARI:
            if (!env)
            {
                global_obj_id++;
            }
            current_mem[current_obj_id++].size = code_mem[i].args[0].ival;
            break;

        case LCI:
            opush(oroot, code_mem[i].args[0], get_type_size(T_INTEGER));
            break;

        case LCR:
            opush(oroot, code_mem[i].args[0], get_type_size(T_REAL));
            break;

        case LCS:

            if (string_table[hash(code_mem[i].args[0].sval)] != NULL)
            {
                /* code */
                code_mem[i].args[0].sval = string_table[hash(code_mem[i].args[0].sval)];
            }
            else
            {
                string_table[hash(code_mem[i].args[0].sval)] = code_mem[i].args[0].sval;
            }
            opush(oroot, code_mem[i].args[0], get_type_size(T_STRING));
            break;

        case LOD:
            if (code_mem[i].args[0].ival)
            {
                lod_data = global_mem[global_obj_id + code_mem[i].args[1].ival];
            }
            else
            {
                lod_data = global_mem[code_mem[i].args[1].ival];
            }
            opush(oroot, lod_data.val, lod_data.size);
            break;

        case STO:

            sto_val = opop(oroot).val;
            if (code_mem[i].args[0].ival)
            {

                global_mem[global_obj_id + code_mem[i].args[1].ival].val = sto_val;
            }
            else
            {
                global_mem[code_mem[i].args[1].ival].val = sto_val;
            }
            break;

        case JMF:
            jmf_decision = opop(oroot).val;

            if (!jmf_decision.bval)
            {
                i += code_mem[i].args[0].ival - 1;
            }
            break;

        case JMP:
            i += code_mem[i].args[0].ival - 1;
            break;

        case EQU:
            node1 = opop(oroot);
            node2 = opop(oroot);

            if (node1.size == 4)
            {
                ris.bval = node1.val.ival == node2.val.ival ? 1 : 0;
            }
            else if (node1.size == 8)
            {
                ris.bval = node1.val.fval == node2.val.fval ? 1 : 0;
            }
            else
            {
                ris.bval = node1.val.sval == node2.val.sval ? 1 : 0;
            }

            opush(oroot, ris, get_type_size(T_INTEGER));
            break;

        case NEQ:
            node1 = opop(oroot);
            node2 = opop(oroot);

            if (node1.size == 4)
            {
                ris.bval = node1.val.ival != node2.val.ival ? 1 : 0;
            }
            else if (node1.size == 8)
            {
                ris.bval = node1.val.fval != node2.val.fval ? 1 : 0;
            }
            else
            {
                ris.bval = node1.val.sval != node2.val.sval ? 1 : 0;
            }

            opush(oroot, ris, get_type_size(T_INTEGER));
            break;

        case GTI:
            num1 = opop(oroot).val.ival;
            num2 = opop(oroot).val.ival;

            ris.bval = num2 > num1 ? 1 : 0;

            opush(oroot, ris, get_type_size(T_INTEGER));
            break;

        case GEI:
            num1 = opop(oroot).val.ival;
            num2 = opop(oroot).val.ival;

            ris.bval = num2 >= num1 ? 1 : 0;

            opush(oroot, ris, get_type_size(T_INTEGER));
            break;

        case LTI:
            num1 = opop(oroot).val.ival;
            num2 = opop(oroot).val.ival;

            ris.bval = num2 < num1 ? 1 : 0;

            opush(oroot, ris, get_type_size(T_INTEGER));
            break;

        case LEI:
            num1 = opop(oroot).val.ival;
            num2 = opop(oroot).val.ival;

            ris.bval = num2 <= num1 ? 1 : 0;

            opush(oroot, ris, get_type_size(T_INTEGER));

            break;

        case GTR:
            num_f1 = opop(oroot).val.fval;
            num_f2 = opop(oroot).val.fval;

            ris.bval = num_f2 > num_f1 ? 1 : 0;

            opush(oroot, ris, get_type_size(T_REAL));

            break;

        case GER:
            num_f1 = opop(oroot).val.fval;
            num_f2 = opop(oroot).val.fval;

            ris.bval = num_f2 >= num_f1 ? 1 : 0;

            opush(oroot, ris, get_type_size(T_REAL));
            break;

        case LTR:
            num_f1 = opop(oroot).val.fval;
            num_f2 = opop(oroot).val.fval;

            ris.bval = num_f2 < num_f1 ? 1 : 0;

            opush(oroot, ris, get_type_size(T_REAL));
            break;

        case LER:
            num_f1 = opop(oroot).val.fval;
            num_f2 = opop(oroot).val.fval;

            ris.bval = num_f2 <= num_f1 ? 1 : 0;

            opush(oroot, ris, get_type_size(T_REAL));
            break;

        case GTS:
            s1 = opop(oroot).val.sval;
            s2 = opop(oroot).val.sval;

            ris.bval = strcmp(s1, s2) > 0 ? 1 : 0;

            opush(oroot, ris, get_type_size(T_INTEGER));
            break;

        case GES:
            s1 = opop(oroot).val.sval;
            s2 = opop(oroot).val.sval;

            ris.bval = strcmp(s1, s2) >= 0 ? 1 : 0;
            opush(oroot, ris, get_type_size(T_INTEGER));
            break;

        case LTS:
            s1 = opop(oroot).val.sval;
            s2 = opop(oroot).val.sval;

            ris.bval = strcmp(s1, s2) < 0 ? 1 : 0;

            opush(oroot, ris, get_type_size(T_INTEGER));
            break;

        case LES:
            s1 = opop(oroot).val.sval;
            s2 = opop(oroot).val.sval;

            ris.bval = strcmp(s1, s2) <= 0 ? 1 : 0;

            opush(oroot, ris, get_type_size(T_INTEGER));
            break;

        case ADI:
            num1 = opop(oroot).val.ival;
            num2 = opop(oroot).val.ival;

            ris.ival = num2 + num1;

            opush(oroot, ris, get_type_size(T_INTEGER));
            break;

        case SBI:
            num1 = opop(oroot).val.ival;
            num2 = opop(oroot).val.ival;

            ris.ival = num2 - num1;

            opush(oroot, ris, get_type_size(T_INTEGER));
            break;

        case MUI:
            num1 = opop(oroot).val.ival;
            num2 = opop(oroot).val.ival;

            ris.ival = num2 * num1;

            opush(oroot, ris, get_type_size(T_INTEGER));
            break;

        case DVI:
            num1 = opop(oroot).val.ival;
            num2 = opop(oroot).val.ival;

            ris.ival = (int)(num2 / num1);

            opush(oroot, ris, get_type_size(T_INTEGER));
            break;

        case ADR:
            num_f1 = opop(oroot).val.fval;
            num_f2 = opop(oroot).val.fval;

            ris.fval = num_f2 + num_f1;

            opush(oroot, ris, get_type_size(T_REAL));
            break;

        case SBR:
            num_f1 = opop(oroot).val.fval;
            num_f2 = opop(oroot).val.fval;

            ris.fval = num_f2 - num_f1;

            opush(oroot, ris, get_type_size(T_REAL));
            break;

        case MUR:
            num_f1 = opop(oroot).val.fval;
            num_f2 = opop(oroot).val.fval;

            ris.fval = num_f2 * num_f1;

            opush(oroot, ris, get_type_size(T_REAL));
            break;

        case DVR:
            num_f1 = opop(oroot).val.fval;
            num_f2 = opop(oroot).val.fval;

            ris.fval = num_f2 / num_f1;

            opush(oroot, ris, get_type_size(T_REAL));
            break;

        case UMI:
            num1 = opop(oroot).val.ival;

            ris.ival = -num1;

            opush(oroot, ris, get_type_size(T_INTEGER));
            break;

        case UMR:
            num_f1 = opop(oroot).val.fval;

            ris.fval = -num_f1;

            opush(oroot, ris, get_type_size(T_REAL));
            break;

        case NEG:
            num2 = opop(oroot).val.bval;

            ris.bval = num2 ? 0 : 1;

            opush(oroot, ris, get_type_size(T_INTEGER));
            break;

        case PSH:

            v1 = code_mem[i].args[0];
            v2 = code_mem[i].args[1];

            struct Ostack *param_stack = createOStack(v1.ival);
            struct Ostack_node *param = (struct Ostack_node *)malloc(sizeof(struct Ostack_node));

            for (int j = 0; j < v1.ival; j++)
            {
                *param = opop(oroot);
                opush(param_stack, param->val, param->size);

            }

            apush(aroot, param_stack, v2.ival, i + 1);
            break;

        case GOT:
            i = code_mem[i].args->ival - 1;
            break;

        case POP:

            break;

        case TOI:
            ovalue = opop(oroot).val;
            Value toi;
            toi.ival = (int)ovalue.fval;
            opush(oroot, toi, get_type_size(T_INTEGER));

            break;

        case TOR:
            ovalue = opop(oroot).val;
            Value tor;
            tor.fval = (float)ovalue.ival;
            opush(oroot, tor, get_type_size(T_REAL));
            break;

        case INP:
            fflush(stdin);
            char *read_string = (char *)malloc(sizeof(char) * 200);
            if (strcmp(code_mem[i].args[0].sval, "i") == 0)
            {
                
                int ivalue;
                fflush(stdin);
                scanf("%d", &ivalue);
                read_value.ival = ivalue;

            }
            else if (strcmp(code_mem[i].args[0].sval, "r") == 0)
            {
                fflush(stdin);
                float fvalue;
                scanf("%f", &fvalue);
                read_value.fval = fvalue;
            }
            else if (strcmp(code_mem[i].args[0].sval, "s") == 0)
            {
                char *str = (char *)malloc(sizeof(char) * 200);
                fflush(stdin);
                scanf("%s", str);

                if (string_table[hash(str)] != NULL)
                {
                    /* code */
                    str = string_table[hash(str)];
                }
                else
                {
                    string_table[hash(str)] = str;
                }
                read_value.sval = str;
            }
            else if (strcmp(code_mem[i].args[0].sval, "b") == 0)
            {
                int bvalue;
                fflush(stdin);
                scanf("%d", &bvalue);
                read_value.ival = bvalue;

            } else
            {
                fflush(stdin);
            }
            
            if (code_mem[i].args[1].ival)
            {

                global_mem[global_obj_id + code_mem[i].args[2].ival].val = read_value;
            }
            else
            {
                global_mem[code_mem[i].args[2].ival].val = read_value;
            }

            break;

        case OUT:
            format = code_mem[i].args[1].sval;

            char **printformat = (char **)malloc(sizeof(char *) * strlen(format));
            int len = code_mem[i].args[0].ival;

            for (int j = 0; j < len; j++)
            {
                if (format[j] == 'i')
                {
                    printformat[j] = " %d ";
                }
                else if (format[j] == 'r')
                {
                    printformat[j] = " %f ";
                }
                else if (format[j] == 's')
                {
                    printformat[j] = " %s ";
                }
                else if (format[j] == 'b')
                {
                    printformat[j] = " %d ";
                }
                else {
                    char f[3] = {' ',format[j], ' '};
                    printformat[j] = strcpy(printformat[j], f);
                }
            }
            

            struct Ostack *temp_stack = createOStack(len);
            struct Ostack_node temp;

            for (int j = 0; j < len; j++)
            {
                temp = opop(oroot);
                opush(temp_stack, temp.val, temp.size);
            }
            

            Value v;
            for (int j = 0; j < len; j++)
            {
                v = opop(temp_stack).val;
                if (strcmp(printformat[j], " %d ") == 0)
                {
                    if (format[j] == 'b')
                    {
                        printf("%d", v.bval);
                    }
                    else
                    {

                        printf("%d", v.ival);
                    }
                }
                else if (strcmp(printformat[j], " %f ") == 0)
                {
                    printf("%f", v.fval);
                }
                else if (strcmp(printformat[j], " %s ") == 0)
                {
                    printf("%s", v.sval);
                }
                else
                {
                    printf("%s",printformat[j]);
                }
            }
            if (strlen(format) > len)
            {
                printf("\n");
            }
            
            break;

        case ENT:
            global_obj_id = (current_obj_id - global_obj_id) + code_mem[i].args[0].ival;
            current_obj_id++;
            struct Astack_node record = apeek(aroot);
            for (int j = 0; j < record.objects->capacity; j++)
            {
                sto_val = opop(record.objects).val;
                global_mem[global_obj_id + j + 1].val = sto_val;
                current_obj_id++;
            }
            

            env = 1;
            break;

        case INC:
            if (code_mem[i].args[0].ival)
            {
                global_mem[global_obj_id + code_mem[i].args[1].ival].val.ival++;
            }
            else
            {
                global_mem[code_mem[i].args[1].ival].val.ival++;
            }
            break;

        case RET:
            if (!code_mem[i].args[0].ival)
            {
                if (!isOEmpty(oroot))
                {
                    fprintf(stderr, "Return Error!\n");
                    exit(-1);
                }
            }

            i = apop(aroot).ret_addr;
            break;

        case STP:
            end_of_program = true;
            break;
        }
    }
}