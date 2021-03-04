#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include <stdbool.h>
#include "def.h"

struct Astack *aroot;
struct Ostack *oroot;

//instance stack per memorizzare elementi vettoriali
struct Ostack *iroot; //TODO: credo me ne serva uno anche per le funzioni?

FILE *code_file;

struct data_mem *global_mem;

char **string_table;

void executeSCode(char *filename)
{
    string_table = (char **)calloc((SYMTAB_SIZE), sizeof(char *));

    char *format = (char *)malloc(sizeof(char) * 100);

    char *s1 = (char *)malloc(sizeof(char) * 280);
    char *s2 = (char *)malloc(sizeof(char) * 280);

    char *read_format = (char *)malloc(sizeof(char) * 140);

    struct Stat *code_mem = get_scode_from_txt(filename);

    struct data_mem lod_data;

    int call_oid, cat_index;
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
    Value ixa;
    Value lod_value;

    struct Ostack_node node1 = newONode();
    struct Ostack_node node2 = newONode();

    int env = 0;
    int global_obj_id = 0;
    int local_obj_id = 0;
    bool end_of_program = false;

    global_mem = (struct data_mem *)malloc(sizeof(struct data_mem) * SYMTAB_SIZE);

    struct data_mem *current_mem;

    aroot = createAStack(512);
    oroot = createOStack(512);
    iroot = createOStack(SYMTAB_SIZE);

    struct Ostack *next_stack;
    struct Ostack *current_stack;
    struct Ostack *current_instack;

    current_instack = iroot;
    current_mem = global_mem;
    current_stack = oroot;

    for (int i = 0; !end_of_program; i++)
    {
        //FIXME: Dove metti size di
        switch (code_mem[i].op)
        {

        case VARI:

            if (!env)
            {

                global_mem[global_obj_id++].tipo = code_mem[i].args[0].ival;
                global_mem[global_obj_id].size = 1;
            }
            else
            {

                current_mem[local_obj_id++].tipo = code_mem[i].args[0].ival;
                current_mem[local_obj_id].size = 1;
            }
            break;
        //FIXME: Gestire la cosa degli size degli stacknode in ostack( istack è fatto solo di elementi atomici)
        case VEC:
            //TODO: Rivedere magari la cosa degli elementi invertiti(ovvero considerare top - n.elems come primo elem)
            if (!env)
            {
                global_mem[global_obj_id++].tipo = S_VECTOR;
                global_mem[global_obj_id].size = code_mem[i].args[0].ival;
                global_mem[global_obj_id].val.vec_p = opush_batch(current_instack, code_mem[i].args[0].ival);
            }
            else
            {
                current_mem[local_obj_id++].tipo = S_VECTOR;
                current_mem[local_obj_id].size = code_mem[i].args[0].ival;
                current_mem[local_obj_id].val.vec_p = opush_batch(current_instack, code_mem[i].args[0].ival);
            }
            break;

        case IXA:
            //Just doing this for the sake of avoiding SIGSEVs for now
            ixa.vec_p = opop(current_stack).val.ival * code_mem[i].args[0].ival;
            ixa.vec_p += opop(current_stack).val.vec_p;

            //menate..non necessariamente credo sia vettoriale come elemento
            opush_t(current_stack, ixa, code_mem[i].args[0].ival, S_VECTOR); //TODO: ...CHECK...
            break;

        case LDA:
            //SImile a LOD
            if (code_mem[i].args[0].ival)
            {
                lod_data = current_mem[code_mem[i].args[1].ival];
            }
            else
            {
                lod_data = global_mem[code_mem[i].args[1].ival];
            }
            lod_value = lod_data.val;
            opush_t(current_stack, lod_value, lod_data.size, S_VECTOR);
            break;

        case IST:
            v1 = opop(current_stack).val;
            current_instack->stack[v1.vec_p].val = opop(current_stack).val;
            break;

        case EIL:
            node1 = current_instack->stack[opop(current_stack).val.vec_p];
            opush_t(current_stack, node1.val, 1, node1.tipo);
            break;

        case CAT:

            /*Finche sono elementi atomici è easy perche prendo robe sullo ostack, le metto
            * nello istack e rimetto sull'ostack lo stacknode con puntatore a primo elemento in istack
            */
            cat_index = code_mem[i].args[1].ival / code_mem[i].args[0].ival; //speriamo no errori di arrotondamento

            struct Ostack *reverseStack = createOStack(code_mem[i].args[0].ival);
            struct Ostack_node cat_elem;

            if (cat_index == 1)
            {

                //FIXME: I vettori sono invertiti!

                for (int j = 0; j < code_mem[i].args[0].ival; j++)
                {
                    /* code */
                    cat_elem = opop(current_stack);
                    opush_t(reverseStack, cat_elem.val, 1, cat_elem.tipo);
                }

                for (int j = 0; j < code_mem[i].args[0].ival; j++)
                {
                    cat_elem = opop(reverseStack);
                    opush_t(current_instack, cat_elem.val, 1, cat_elem.tipo);
                }
            }
            else
            {

                for (int j = 0; j < code_mem[i].args[0].ival; j++)
                {
                    cat_elem = opop(current_stack);
                    opush_t(reverseStack, cat_elem.val, cat_elem.size, cat_elem.tipo);
                }

                for (int j = 0; j < code_mem[i].args[0].ival; j++) //per ciascun vettore da concatenare
                {
                    Value vec_ref = opop(reverseStack).val;
                    /**
                     * Per ciascun elemento di un sottovettore(parto dall'elemento in 'cima' e poi scendo) 
                    */
                    for (int k = vec_ref.vec_p; k < vec_ref.vec_p + cat_index; k++) //TODO: CHECK FOR INDEXING
                    {
                        opush_t(current_instack, current_instack->stack[k].val, current_instack->stack[k].size, current_instack->stack[k].tipo);
                    }
                }
            }
            Value cat_value;
            cat_value.vec_p = current_instack->top - code_mem[i].args[1].ival + 1;
            opush_t(current_stack, cat_value, code_mem[i].args[1].ival, S_VECTOR);

            break;

        case LCI:
            opush_t(current_stack, code_mem[i].args[0], 1, S_INTEGER);
            break;

        case LCR:
            opush_t(current_stack, code_mem[i].args[0], 1, S_REAL);
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
            opush_t(current_stack, code_mem[i].args[0], 1, S_STRING);
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
            lod_value = lod_data.val;
            opush_t(current_stack, lod_value, lod_data.size, lod_data.tipo);
            break;

        case STO:

            sto_val = opeek(current_stack).val;
            if (code_mem[i].args[0].ival)
            {

                current_mem[code_mem[i].args[1].ival].val = sto_val;
                current_mem[code_mem[i].args[1].ival].tipo = opeek(current_stack).tipo;
                current_mem[code_mem[i].args[1].ival].size = opop(current_stack).size;
            }
            else
            {
                global_mem[code_mem[i].args[1].ival].val = sto_val;
                global_mem[code_mem[i].args[1].ival].tipo = opeek(current_stack).tipo;
                global_mem[code_mem[i].args[1].ival].size = opop(current_stack).size;
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
            //FIXME
            node1 = opop(current_stack);
            node2 = opop(current_stack);

            if (node1.tipo == S_BOOLEAN_)
            {
                ris.bval = node1.val.bval == node2.val.bval ? 1 : 0;
            }
            else if (node1.tipo == S_INTEGER)
            {
                ris.bval = node1.val.ival == node2.val.ival ? 1 : 0;
            }
            else if (node1.tipo == S_REAL)
            {
                ris.bval = node2.val.fval == node1.val.fval ? 1 : 0;
            }
            else
            {
                ris.bval = node2.val.sval == node1.val.sval ? 1 : 0;
            }

            opush_t(current_stack, ris, 1, S_BOOLEAN_);
            break;

        case VIN:

            //TODO: COntrollare che i size dei vettori siano ben messi...altrimenti menate qua
            node1 = opop(current_stack);
            node2 = opop(current_stack);

            int result = 0;
            struct Ostack_node elem_vin;
            for (int j = node1.val.vec_p; j < node1.val.vec_p + node1.size && !result; j++)
            {
                /* code */
                elem_vin = current_instack->stack[j];
                if (elem_vin.tipo == S_BOOLEAN_)
                {
                    result = node2.val.bval == elem_vin.val.bval ? 1 : 0;
                }
                else if (elem_vin.tipo == S_INTEGER)
                {
                    result = node2.val.ival == elem_vin.val.ival ? 1 : 0;
                }
                else if (elem_vin.tipo == S_REAL)
                {
                    result = node2.val.fval == elem_vin.val.fval ? 1 : 0;
                }
                else if (elem_vin.tipo == S_STRING)
                {
                    result = node2.val.sval == elem_vin.val.sval ? 1 : 0;
                }
            }

            ris.bval = result;
            opush_t(current_stack, ris, 1, S_BOOLEAN_);

            break;

        case NEQ:
            //FIXME
            node1 = opop(current_stack);
            node2 = opop(current_stack);

            if (node1.tipo == S_BOOLEAN_)
            {
                ris.bval = node1.val.bval != node2.val.bval ? 1 : 0;
            }
            else if (node1.tipo == S_INTEGER)
            {
                ris.bval = node1.val.ival != node2.val.ival ? 1 : 0;
            }
            else if (node1.tipo == S_REAL)
            {
                ris.bval = node2.val.fval != node2.val.fval ? 1 : 0;
            }
            else
            {
                ris.bval = node2.val.sval != node1.val.sval ? 1 : 0;
            }

            opush_t(current_stack, ris, 1, S_BOOLEAN_);
            break;

        case GTI:
            num1 = opop(current_stack).val.ival;
            num2 = opop(current_stack).val.ival;

            ris.bval = num2 > num1 ? 1 : 0;

            opush_t(current_stack, ris, 1, S_BOOLEAN_);
            break;

        case GEI:
            num1 = opop(current_stack).val.ival;
            num2 = opop(current_stack).val.ival;

            ris.bval = num2 >= num1 ? 1 : 0;

            opush_t(current_stack, ris, 1, S_BOOLEAN_);
            break;

        case LTI:
            num1 = opop(current_stack).val.ival;
            num2 = opop(current_stack).val.ival;


            ris.bval = num2 < num1 ? 1 : 0;

            opush_t(current_stack, ris, 1, S_BOOLEAN_);
            break;

        case LEI:
            num1 = opop(current_stack).val.ival;
            num2 = opop(current_stack).val.ival;

            ris.bval = num2 <= num1 ? 1 : 0;

            opush_t(current_stack, ris, 1, S_BOOLEAN_);

            break;

        case GTR:
            num_f1 = opop(current_stack).val.fval;
            num_f2 = opop(current_stack).val.fval;

            ris.bval = num_f2 > num_f1 ? 1 : 0;

            opush_t(current_stack, ris, 1, S_BOOLEAN_);

            break;

        case GER:
            num_f1 = opop(current_stack).val.fval;
            num_f2 = opop(current_stack).val.fval;

            ris.bval = num_f2 >= num_f1 ? 1 : 0;

            opush_t(current_stack, ris, 1, S_BOOLEAN_);
            break;

        case LTR:
            num_f1 = opop(current_stack).val.fval;
            num_f2 = opop(current_stack).val.fval;

            ris.bval = num_f2 < num_f1 ? 1 : 0;

            opush_t(current_stack, ris, 1, S_BOOLEAN_);
            break;

        case LER:
            num_f1 = opop(current_stack).val.fval;
            num_f2 = opop(current_stack).val.fval;

            ris.bval = num_f2 <= num_f1 ? 1 : 0;

            opush_t(current_stack, ris, 1, S_BOOLEAN_);
            break;
        case GTS:
            s1 = opop(current_stack).val.sval;
            s2 = opop(current_stack).val.sval;

            ris.bval = strcmp(s2, s1) > 0 ? 1 : 0;
            opush_t(current_stack, ris, 1, S_BOOLEAN_);
            break;

        case GES:
            s1 = opop(current_stack).val.sval;
            s2 = opop(current_stack).val.sval;

            ris.bval = strcmp(s2, s1) >= 0 ? 1 : 0;

            opush_t(current_stack, ris, 1, S_BOOLEAN_);
            break;

        case LTS:
            s1 = opop(current_stack).val.sval;
            s2 = opop(current_stack).val.sval;

            ris.bval = strcmp(s2, s1) < 0 ? 1 : 0;
            opush_t(current_stack, ris, 1, S_BOOLEAN_);
            break;

        case LES:
            s1 = opop(current_stack).val.sval;
            s2 = opop(current_stack).val.sval;

            ris.bval = strcmp(s2, s1) <= 0 ? 1 : 0;

            opush_t(current_stack, ris, 1, S_BOOLEAN_);
            break;

        case ADI:
            num1 = opop(current_stack).val.ival;
            num2 = opop(current_stack).val.ival;

            ris.ival = num2 + num1;

            opush_t(current_stack, ris, 1, S_INTEGER);
            break;

        case SBI:
            num1 = opop(current_stack).val.ival;
            num2 = opop(current_stack).val.ival;

            ris.ival = num2 - num1;

            opush_t(current_stack, ris, 1, S_INTEGER);
            break;

        case MUI:
            num1 = opop(current_stack).val.ival;
            num2 = opop(current_stack).val.ival;

            ris.ival = num2 * num1;

            opush_t(current_stack, ris, 1, S_INTEGER);
            break;

        case DVI:
            num1 = opop(current_stack).val.ival;
            num2 = opop(current_stack).val.ival;

            ris.ival = (int)(num2 / num1);

            opush_t(current_stack, ris, 1, S_INTEGER);
            break;

        case ADR:
            num_f1 = opop(current_stack).val.fval;
            num_f2 = opop(current_stack).val.fval;

            ris.fval = num_f2 + num_f1;

            opush_t(current_stack, ris, 1, S_REAL);
            break;

        case SBR:
            num_f1 = opop(current_stack).val.fval;
            num_f2 = opop(current_stack).val.fval;

            ris.fval = num_f2 - num_f1;

            opush_t(current_stack, ris, 1, S_REAL);
            break;

        case MUR:
            num_f1 = opop(current_stack).val.fval;
            num_f2 = opop(current_stack).val.fval;

            ris.fval = num_f2 * num_f1;

            opush_t(current_stack, ris, 1, S_REAL);
            break;

        case DVR:
            num_f1 = opop(current_stack).val.fval;
            num_f2 = opop(current_stack).val.fval;

            ris.fval = num_f2 / num_f1;

            opush_t(current_stack, ris, 1, S_REAL);
            break;

        case UMI:
            num1 = opop(current_stack).val.ival;

            ris.ival = -num1;

            opush_t(current_stack, ris, 1, S_INTEGER);
            break;

        case UMR:
            num_f1 = opop(current_stack).val.fval;

            ris.fval = -num_f1;

            opush_t(current_stack, ris, 1, S_REAL);
            break;

        case NEG:
            num2 = opop(current_stack).val.bval;

            ris.bval = num2 ? 0 : 1;

            opush_t(current_stack, ris, 1, S_BOOLEAN_);
            break;

        case PSH:
            //FIXME: fix new instack element stacking ..elements are reversed
            call_oid = global_obj_id;
            v1 = code_mem[i].args[0];
            v2 = code_mem[i].args[1];

            struct Ostack *param_stack = createOStack(100);
            struct Ostack *vec_stack = createOStack(2048);

            struct Ostack_node param;

            for (int j = 0; j < v1.ival; j++)
            {
                param = opop(current_stack); //FIXME: SE non atomico devo copiare i dati nel istack per la funzione

                if (param.size > 1)
                {
                    for (int k = param.val.vec_p; k < param.val.vec_p + param.size; k++) //TODO: CHECK indexing
                    {
                        opush_t(vec_stack, current_instack->stack[k].val, 1, current_instack->stack[k].tipo);
                    }
                    param.val.vec_p = vec_stack->top - param.size + 1;
                }
                opush_t(param_stack, param.val, param.size, param.tipo);
            }

            apush(aroot, param_stack, vec_stack, call_oid, (struct data_mem *)malloc(sizeof(struct data_mem) * 200), v2.ival, i + 1);
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
            opush_t(current_stack, toi, 1, S_INTEGER);

            break;

        case TOR:
            ovalue = opop(current_stack).val;
            Value tor;
            tor.fval = (float)ovalue.ival;
            opush_t(current_stack, tor, 1, S_REAL);
            break;

        case INP:
            fflush(stdin);
            char *read_string = (char *)malloc(sizeof(char) * 256);
            if (strcmp(code_mem[i].args[0].sval, "i") == 0)
            {

                int ivalue;
                fflush(stdin);
                fgets(read_string, 256, stdin);
                fflush(stdin);
                read_value.ival = atoi(read_string);
            }
            else if (strcmp(code_mem[i].args[0].sval, "r") == 0)
            {
                float fvalue;
                fflush(stdin);
                fgets(read_string, 256, stdin);
                fflush(stdin);
                read_value.fval = atof(read_string);
            }
            else if (strcmp(code_mem[i].args[0].sval, "s") == 0)
            {
                char *str = (char *)malloc(sizeof(char) * 200);
                fflush(stdin);
                fgets(str, 200, stdin);
                fflush(stdin);
                char *str2 = malloc(sizeof(char) * (strlen(str)));

                int j;
                for (j = 0; str[j] != '\n'; j++)
                {
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
                read_value.sval = str2;
            }
            else if (strcmp(code_mem[i].args[0].sval, "b") == 0)
            {

                int bvalue;
                fflush(stdin);
                fgets(read_string, 256, stdin);
                fflush(stdin);
                bvalue = atoi(read_string);

                read_value.bval = bvalue > 0 ? TRUE : FALSE;
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
                    printf("%s", v.bval == TRUE ? "true" : "false");
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
            while (!isOEmpty(record.objects))
            {
                sto_val = opeek(record.objects).val;
                func_mem[j + 1].val = sto_val;
                func_mem[j + 1].tipo = opeek(record.objects).tipo;
                func_mem[j + 1].size = opop(record.objects).size;
                local_obj_id++;
                j++;
            }

            current_mem = func_mem;
            current_stack = record.objects;
            current_instack = record.vec_elems;

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
                current_instack = iroot;
            }
            else
            {

                current_mem = apeek(aroot).local_mem;
                next_stack = apeek(aroot).objects;
                struct Ostack *next_vecstack = apeek(aroot).vec_elems;

                if (code_mem[i].args[0].ival)
                {
                    struct Ostack_node ret = opop(current_stack);
                    //FIXME : vettore potrebbe essere invertito
                    if (ret.size > 1) //FIXME: apparently = 0
                    {
                        for (int k = ret.val.vec_p; k < ret.val.vec_p + ret.size; k++) //TODO: CHECK indexing
                        {
                            opush_t(next_vecstack, current_instack->stack[k].val, 1, current_instack->stack[k].tipo);
                        }
                        ret.val.vec_p = next_vecstack->top - ret.size + 1;
                    }
                    opush_t(next_stack, ret.val, ret.size, ret.tipo); //FIXME: Se vettore..controllare
                }
                current_stack = next_stack;
                current_instack = next_vecstack;
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

        if (strstr(filename, ".sim") == NULL)
        {
            fprintf(stderr, "ERRORE SIMPLAVM: INDICARE FILE.SIM DA ESEGUIRE\n");
            exit(-1);
        }

        executeSCode(filename);
    }
    else
    {
        fprintf(stderr, "ERRORE SIMPLAVM: INDICARE FILE.SIM DA ESEGUIRE\n");
        exit(-1);
    }
    return 0;
}