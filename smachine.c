#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include <stdbool.h>
#include "def.h"

struct Astack *aroot;
struct Ostack *oroot;

FILE *code_file;

struct data_mem *global_mem;

char **string_table;

void executeSCode(char *filename)
{
    //todo: aggiungere bucket horizontali per evitare collisioni
    string_table = (char **)calloc((SYMTAB_SIZE), sizeof(char *));

    char *format = (char *)malloc(sizeof(char) * 100);

    char *s1 = (char *)malloc(sizeof(char) * 280);
    char *s2 = (char *)malloc(sizeof(char) * 280);

    char *read_format = (char *)malloc(sizeof(char) * 140);

    struct Stat *code_mem = get_scode_from_txt(filename);

    struct data_mem lod_data;

    int call_oid;
    int stat_counter = 0;


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
    int local_obj_id = 0;
    bool end_of_program = false;

    global_mem = (struct data_mem *)malloc(sizeof(struct data_mem) * SYMTAB_SIZE);

    struct data_mem *current_mem;

    aroot = createAStack(256);
    oroot = createOStack(256);

    struct Ostack *next_stack;
    struct Ostack *current_stack;

    current_mem = global_mem;
    current_stack = oroot;
    

    for (int i = 0;!end_of_program; i++)
    {
        switch (code_mem[i].op)
        {

        case VARI:
            if (!env)
            {
                global_mem[global_obj_id++].size = code_mem[i].args[0].ival;
            }
            else
            {

                current_mem[local_obj_id++].size = code_mem[i].args[0].ival;
            }
            break;

        case LCI:
            opush(current_stack, code_mem[i].args[0], get_type_size(T_INTEGER));
            break;

        case LCR:
            opush(current_stack, code_mem[i].args[0], get_type_size(T_REAL));
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
            opush(current_stack, code_mem[i].args[0], get_type_size(T_STRING));
            break;

        case LOD:
            if (code_mem[i].args[0].ival)
            {
                lod_data = current_mem[code_mem[i].args[1].ival];
            }
            else
            {
                lod_data = global_mem[code_mem[i].args[1].ival];
            }
            Value lod_value = lod_data.val;
            opush(current_stack, lod_value, lod_data.size);
            break;

        case STO:

            sto_val = opop(current_stack).val;
            if (code_mem[i].args[0].ival)
            {

                current_mem[code_mem[i].args[1].ival].val = sto_val;
            }
            else
            {
                global_mem[code_mem[i].args[1].ival].val = sto_val;
            }
            break;

        case JMF:
            jmf_decision = opop(current_stack).val;

            if (!jmf_decision.bval)
            {
                i += code_mem[i].args[0].ival - 1;
            }
            break;

        case JMP:
            i += code_mem[i].args[0].ival - 1;
            break;

        case EQU:
            node1 = opop(current_stack);
            node2 = opop(current_stack);

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

            opush(current_stack, ris, get_type_size(T_INTEGER));
            break;

        case NEQ:
            node1 = opop(current_stack);
            node2 = opop(current_stack);

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

            opush(current_stack, ris, get_type_size(T_INTEGER));
            break;

        case GTI:
            num1 = opop(current_stack).val.ival;
            num2 = opop(current_stack).val.ival;

            ris.bval = num2 > num1 ? 1 : 0;

            opush(current_stack, ris, get_type_size(T_INTEGER));
            break;

        case GEI:
            num1 = opop(current_stack).val.ival;
            num2 = opop(current_stack).val.ival;

            ris.bval = num2 >= num1 ? 1 : 0;

            opush(current_stack, ris, get_type_size(T_INTEGER));
            break;

        case LTI:
            num1 = opop(current_stack).val.ival;
            num2 = opop(current_stack).val.ival;

            ris.bval = num2 < num1 ? 1 : 0;

            opush(current_stack, ris, get_type_size(T_INTEGER));
            break;

        case LEI:
            num1 = opop(current_stack).val.ival;
            num2 = opop(current_stack).val.ival;

            ris.bval = num2 <= num1 ? 1 : 0;

            opush(current_stack, ris, get_type_size(T_INTEGER));

            break;

        case GTR:
            num_f1 = opop(current_stack).val.fval;
            num_f2 = opop(current_stack).val.fval;

            ris.bval = num_f2 > num_f1 ? 1 : 0;

            opush(current_stack, ris, get_type_size(T_REAL));

            break;

        case GER:
            num_f1 = opop(current_stack).val.fval;
            num_f2 = opop(current_stack).val.fval;

            ris.bval = num_f2 >= num_f1 ? 1 : 0;

            opush(current_stack, ris, get_type_size(T_REAL));
            break;

        case LTR:
            num_f1 = opop(current_stack).val.fval;
            num_f2 = opop(current_stack).val.fval;

            ris.bval = num_f2 < num_f1 ? 1 : 0;

            opush(current_stack, ris, get_type_size(T_REAL));
            break;

        case LER:
            num_f1 = opop(current_stack).val.fval;
            num_f2 = opop(current_stack).val.fval;

            ris.bval = num_f2 <= num_f1 ? 1 : 0;

            opush(current_stack, ris, get_type_size(T_REAL));
            break;
        case GTS:
            s1 = opop(current_stack).val.sval;
            s2 = opop(current_stack).val.sval;

            ris.bval = strcmp(s2,s1) > 0 ? 1 : 0;
            //printf("GTS: %s < %s : %d\n", s1,s2,strcmp(s1,s2));
            opush(current_stack, ris, get_type_size(T_INTEGER));
            break;

        case GES:
            s1 = opop(current_stack).val.sval;
            s2 = opop(current_stack).val.sval;

            ris.bval = strcmp(s2, s1) >= 0 ? 1 : 0;

            //printf("GES: %s >= %s : %d\n", s1,s2,strcmp(s1,s2));
            opush(current_stack, ris, get_type_size(T_INTEGER));
            break;

        case LTS:
            s1 = opop(current_stack).val.sval;
            s2 = opop(current_stack).val.sval;

            ris.bval = strcmp(s2,s1) < 0 ? 1 : 0;
            //printf("GES: %s < %s : %d\n", s1,s2,strcmp(s1,s2));
            opush(current_stack, ris, get_type_size(T_INTEGER));
            break;

        case LES:
            s1 = opop(current_stack).val.sval;
            s2 = opop(current_stack).val.sval;

            ris.bval = strcmp(s2,s1) <= 0 ? 1 : 0;

            //printf("GES: %s <= %s : %d\n", s1,s2,strcmp(s1,s2));

            opush(current_stack, ris, get_type_size(T_INTEGER));
            break;

        case ADI:
            num1 = opop(current_stack).val.ival;
            num2 = opop(current_stack).val.ival;

            ris.ival = num2 + num1;

            opush(current_stack, ris, get_type_size(T_INTEGER));
            break;

        case SBI:
            num1 = opop(current_stack).val.ival;
            num2 = opop(current_stack).val.ival;

            ris.ival = num2 - num1;

            opush(current_stack, ris, get_type_size(T_INTEGER));
            break;

        case MUI:
            num1 = opop(current_stack).val.ival;
            num2 = opop(current_stack).val.ival;

            ris.ival = num2 * num1;

            opush(current_stack, ris, get_type_size(T_INTEGER));
            break;

        case DVI:
            num1 = opop(current_stack).val.ival;
            num2 = opop(current_stack).val.ival;

            ris.ival = (int)(num2 / num1);

            opush(current_stack, ris, get_type_size(T_INTEGER));
            break;

        case ADR:
            num_f1 = opop(current_stack).val.fval;
            num_f2 = opop(current_stack).val.fval;

            ris.fval = num_f2 + num_f1;

            opush(current_stack, ris, get_type_size(T_REAL));
            break;

        case SBR:
            num_f1 = opop(current_stack).val.fval;
            num_f2 = opop(current_stack).val.fval;

            ris.fval = num_f2 - num_f1;

            opush(current_stack, ris, get_type_size(T_REAL));
            break;

        case MUR:
            num_f1 = opop(current_stack).val.fval;
            num_f2 = opop(current_stack).val.fval;

            ris.fval = num_f2 * num_f1;

            opush(current_stack, ris, get_type_size(T_REAL));
            break;

        case DVR:
            num_f1 = opop(current_stack).val.fval;
            num_f2 = opop(current_stack).val.fval;

            ris.fval = num_f2 / num_f1;

            opush(current_stack, ris, get_type_size(T_REAL));
            break;

        case UMI:
            num1 = opop(current_stack).val.ival;

            ris.ival = -num1;

            opush(current_stack, ris, get_type_size(T_INTEGER));
            break;

        case UMR:
            num_f1 = opop(current_stack).val.fval;

            ris.fval = -num_f1;

            opush(current_stack, ris, get_type_size(T_REAL));
            break;

        case NEG:
            num2 = opop(current_stack).val.bval;

            ris.bval = num2 ? 0 : 1;

            opush(current_stack, ris, get_type_size(T_INTEGER));
            break;

        case PSH:
            call_oid = global_obj_id;
            v1 = code_mem[i].args[0];
            v2 = code_mem[i].args[1];

            struct Ostack *param_stack = createOStack(100);
            struct Ostack_node param;


            for (int j = 0; j < v1.ival; j++)
            {
                param = opop(current_stack);
                opush(param_stack, param.val, param.size);
            }

            apush(aroot, param_stack, call_oid, (struct data_mem *)malloc(sizeof(struct data_mem) * 200), v2.ival, i + 1);
            break;

        case GOT:
            i = code_mem[i].args->ival - 1;
            break;

        case POP:

            break;

        case TOI:
            ovalue = opop(current_stack).val;
            Value toi;
            toi.ival = (int)ovalue.fval;
            opush(current_stack, toi, get_type_size(T_INTEGER));

            break;

        case TOR:
            ovalue = opop(current_stack).val;
            Value tor;
            tor.fval = (float)ovalue.ival;
            opush(current_stack, tor, get_type_size(T_REAL));
            break;

        case INP:
            fflush(stdin);
            char *read_string = (char *)malloc(sizeof(char) * 256);
            if (strcmp(code_mem[i].args[0].sval, "i") == 0)
            {

                int ivalue;
                fflush(stdin);
                fgets(read_string,256,stdin);
                //getchar();
                fflush(stdin);
                read_value.ival = atoi(read_string);
            }
            else if (strcmp(code_mem[i].args[0].sval, "r") == 0)
            {
                float fvalue;
                fflush(stdin);
                fgets(read_string,256,stdin);
                fflush(stdin);
                read_value.fval = atof(read_string);
            }
            else if (strcmp(code_mem[i].args[0].sval, "s") == 0)
            {
                char *str = (char *)malloc(sizeof(char) * 200);
                fflush(stdin);
                fgets(str,200,stdin);
                fflush(stdin);
                char *str2 = malloc(sizeof(char) * (strlen(str)));
                //TODO: Rivedere
                int j;
                for (j = 0; str[j] != '\n'; j++) {
                    str2[j] = str[j];
                }

                str2[j] = '\0';
                if (string_table[hash(str2)] != NULL)
                {
                    /* code */
                    str2 = string_table[hash(str2)];
                }
                else
                {
                    string_table[hash(str2)] = str2;
                }
                //printf("READ STRING: %s\n", str2);
                read_value.sval = str2;
            }
            else if (strcmp(code_mem[i].args[0].sval, "b") == 0)
            {
                //todo:fixme->numero deve essere compreso 0 o 1..o stringa;
                int bvalue;
                fflush(stdin);
                fgets(read_string,256,stdin);
                //getchar();
                fflush(stdin);
                bvalue = atoi(read_string);

                read_value.bval = bvalue > 0 ? TRUE:FALSE;
            }
            else
            {
                fflush(stdin);
            }

            if (code_mem[i].args[1].ival)
            {

                current_mem[code_mem[i].args[2].ival].val = read_value;
            }
            else
            {
                global_mem[code_mem[i].args[2].ival].val = read_value;
            }

            break;

        case OUT:
            format = code_mem[i].args[1].sval;

            int len = code_mem[i].args[0].ival;

            struct Ostack *temp_stack = createOStack(len);
            struct Ostack_node temp;

            for (int j = 0; j < len; j++)
            {
                temp = opop(current_stack);
                opush(temp_stack, temp.val, temp.size);
            }

            Value v;
            for (int j = 0; j < len; j++)
            {
                v = opop(temp_stack).val;
                if (format[j] == 'i')
                {

                    printf("%d", v.ival);
                }
                else if (format[j] == 'b')
                {
                    //todo: fix->print stringa
                    printf("%s", v.bval == TRUE?"true":"false");
                }
                else if (format[j] == 'r')
                {
                    printf("%f", v.fval);
                }
                else if (format[j] == 's')
                {
                    printf("%s", v.sval);
                }
            }
            if (strlen(format) > len)
            {
                printf("\n");
            }

            break;

        case ENT:
            global_obj_id++;
            local_obj_id = 0;
            struct Astack_node record = apeek(aroot);
            struct data_mem *func_mem = apeek(aroot).local_mem;
            
            int j = 0;
            while(!isOEmpty(record.objects))
            {
                sto_val = opop(record.objects).val;
                func_mem[j + 1].val = sto_val;
                local_obj_id++;
                j++;
            }

            current_mem = func_mem;
            current_stack = record.objects;

            env = 1;
            break;

        case INC:
            if (code_mem[i].args[0].ival)
            {
                current_mem[code_mem[i].args[1].ival].val.ival++;
            }
            else
            {
                global_mem[code_mem[i].args[1].ival].val.ival++;
            }
            break;

        case RET:
            if (!code_mem[i].args[0].ival)
            {
                if (!isOEmpty(current_stack))
                {
                    fprintf(stderr, "ERRORE: RETURN INVALIDO!\n");
                    exit(-1);
                }
            }
            
            struct Astack_node activation = apop(aroot);
            global_obj_id = activation.call_oid;
            int ret_i = activation.ret_addr;

            if (ret_i == 2)
            {
                current_mem = global_mem;
                current_stack = oroot;
            }
            else
            {

                current_mem = apeek(aroot).local_mem;
                next_stack = apeek(aroot).objects;
                if (code_mem[i].args[0].ival)
                {
                    struct Ostack_node ret = opop(current_stack);
                    opush(next_stack, ret.val,ret.size);
                }
                current_stack = next_stack;
                
            }
            i = ret_i;
            break;

        case STP:
            end_of_program = true;
            break;
        }
    }
}



int main(int argc, char **argv)
{
    struct SCode *scode = (struct SCode *)malloc(sizeof(struct SCode));
    char *filename;
    if (argc >= 2)
    {
        filename = (char *)malloc(sizeof(char) * (strlen(argv[1]) + 1));
        strcpy(filename, argv[1]);
        executeSCode(filename);
    }
    else
    {
        fprintf(stderr,"ERRORE SIMPLAVM: INDICARE FILE.SIM DA ESEGUIRE");
        exit(-1);
    }
    return 0;
}