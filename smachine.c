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

void executeSCode(struct SCode prog)
{
    string_table = (char **)calloc(sizeof(char *), SYMTAB_SIZE);

    char *format = (char *)malloc(sizeof(char) * 100);

    char *s1 = (char *)malloc(sizeof(char) * 280);
    char *s2 = (char *)malloc(sizeof(char) * 280);

    char *read_format = (char *)malloc(sizeof(char) * 140);

    struct Stat *code_mem = (struct Stat *)calloc(sizeof(struct Stat), prog.num);
    struct Stat *code_stat = prog.first;

    struct data_mem lod_data;

    int call_oid;
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
    int local_obj_id = 0;
    bool end_of_program = false;

    global_mem = (struct data_mem *)malloc(sizeof(struct data_mem) * SYMTAB_SIZE);

    struct data_mem *current_mem;

    aroot = createAStack(256);
    oroot = createOStack(256);

    struct Ostack *next_stack;
    struct Ostack *current_stack;

    //struct Stat *scode = prog.first;

    current_mem = global_mem;
    current_stack = oroot;
    

    for (int i = 0; i < prog.num && !end_of_program; i++)
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
                //lod_data = global_mem[global_obj_id + code_mem[i].args[1].ival];
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

            ris.bval = strcmp(s1, s2) > 0 ? 1 : 0;

            opush(current_stack, ris, get_type_size(T_INTEGER));
            break;

        case GES:
            s1 = opop(current_stack).val.sval;
            s2 = opop(current_stack).val.sval;

            ris.bval = strcmp(s1, s2) >= 0 ? 1 : 0;
            opush(current_stack, ris, get_type_size(T_INTEGER));
            break;

        case LTS:
            s1 = opop(current_stack).val.sval;
            s2 = opop(current_stack).val.sval;

            ris.bval = strcmp(s1, s2) < 0 ? 1 : 0;

            opush(current_stack, ris, get_type_size(T_INTEGER));
            break;

        case LES:
            s1 = opop(current_stack).val.sval;
            s2 = opop(current_stack).val.sval;

            ris.bval = strcmp(s1, s2) <= 0 ? 1 : 0;

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
            ;

            for (int j = 0; j < v1.ival; j++)
            {
                param = opop(current_stack);
                //printf("Prob in PSH\n");
                opush(param_stack, param.val, param.size);
                //printf("Dopo il PSH\n");
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
            /*char **printformat = (char **)malloc(sizeof(char *) * strlen(format));
            
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
            }*/

            int len = code_mem[i].args[0].ival;

            struct Ostack *temp_stack = createOStack(len);
            struct Ostack_node temp;

            for (int j = 0; j < len; j++)
            {
                temp = opop(current_stack); //non capisco perche triggeri se uso opeek
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

                    printf("%d", v.bval);
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
            //record.objects = createOStack(100);
            //printf("objects new capacity: %d\n", record.objects->capacity);
            current_stack = record.objects;
            //printf("current stack new capacity: %d\n", current_stack->capacity);

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
                    fprintf(stderr, "Return Error!\n");
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
                    //printf("Prob nel caso di RET %d\n",code_mem[i].args[0].ival);
                    struct Ostack_node ret = opop(current_stack);
                    opush(next_stack, ret.val,ret.size);
                    //printf("Fine Prob in RET\n");
                }
                current_stack = next_stack;
                
            }
            //maybe looking too much in the astack...the last apeek/opeek don't work
            i = ret_i;
            break;

        case STP:
            end_of_program = true;
            break;
        }
    }
}

void get_scode_from_file(char *filename)
{
    FILE *fptr;
    struct SCode int_scode = endcode();

    if ((fptr = fopen(filename, "rb")) == NULL)
    {
        fprintf(stderr,"ERRORE SIMPLAVM: FILE NON ESISTE!");
        // Program exits if the file pointer returns NULL.
        exit(-1);
    }
    int prog_len;
    fread(&prog_len, sizeof(int), 1, fptr);


    struct Stat *code_mem = (struct Stat *)calloc(sizeof(struct Stat), prog_len);

    for (int i = 0; i < prog_len; i++) {
        fread(&code_mem[i],sizeof(struct Stat), 1, fptr);
    }

    fclose(fptr);

    for (int i = 0; i < prog_len; i++) {
        printf("OP: %s \n",print_args(code_mem[i]));
    }

    /*fseek(fptr, 0, SEEK_END);
    unsigned long len = (unsigned long)ftell(fptr);

    if (len > 0)
    { //check if the file is empty or not.
        rewind(fptr);
        struct Stat *file_stat;
        while (!feof(fptr))
        {
            file_stat = (struct Stat *)malloc(sizeof(struct Stat));
            fread(file_stat, sizeof(struct Stat), 1, fptr);
            printf("Op letta: %d\n", file_stat->op);
            int_scode = appcode(int_scode, makecode_from_stat(*file_stat));
        }
    }*/
}

/*int main(int argc, char **argv)
{
    struct SCode *scode = (struct SCode *)malloc(sizeof(struct SCode));

    if (argc >= 2)
    {
        *scode = get_scode_from_file(argv[1]);
    }
    else
    {
        fprintf(stderr,"ERRORE SIMPLAVM: INDICARE FILE.SIM DA ESEGUIRE");
        // Program exits if the file pointer returns NULL.
        exit(-1);
    }
    printf("Starting  Code execution\n");
    codeprint(scode);
    executeSCode(*scode);
}*/