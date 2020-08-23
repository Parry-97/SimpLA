#include <stdlib.h>
#include "string.h"
#include "def.h"

extern int oid_g;
extern struct bucket *symbol_table;

extern struct SCode *current_prog;
int oidl;

int is_break = 0;
int is_return = 0;
Pnode expr_list;

void generateCode(Pnode p, struct bucket *symbtab, struct SCode *prog)
{

    if (p->is_gen)
    {
        return;
    }

    int type_size, env2, oid2, nume, return_offset, break_jump, return_jump;
    struct SCode math_code, cast_code, *while_expr;
    Pnode count_expr, count_bro, cont_stat, cont_stat2, cont_stat3;

    struct bucket *func_bc;

    if (p->type != T_NONTERMINAL)
    {

        switch (p->type)
        {
        case T_ID:

            generateID_Code(p, symbtab, prog);
            p->is_gen = 1;
            break;

        case T_BREAK:
            cont_stat2 = p->brother;

            is_break = 1;

            struct SCode *sub_prog13 = (struct SCode *)malloc(sizeof(struct SCode));
            *sub_prog13 = endcode();

            while (cont_stat2 != NULL)
            {
                generateCode(cont_stat2, symbtab, sub_prog13);
                cont_stat2 = cont_stat2->brother;
            }

            break_jump = sub_prog13->num + 3;

            *prog = appcode(*prog, makecode1(BRK, break_jump));
            *prog = appcode(*prog, *sub_prog13);

            p->is_gen = 1;
            break;

        case T_INTCONST:
            *prog = appcode(*prog, make_lci(p->value.ival));
            p->is_gen = 1;
            break;

        case T_BOOLCONST:
            *prog = appcode(*prog, make_lci(p->value.bval ? 1 : 0));
            p->is_gen = 1;
            break;

        case T_REALCONST:
            *prog = appcode(*prog, make_lcr(p->value.fval));
            p->is_gen = 1;
            break;

        case T_STRCONST:
            *prog = appcode(*prog, make_lcs(p->value.sval));
            p->is_gen = 1;
            break;

        default:
            break;
        }
    }
    else if (p->type == T_NONTERMINAL)
    {

        switch (p->value.ival)
        {

        case N_PROGRAM:

            generateCode(p->child->brother, symbol_table, prog);
            func_bc = find_in_chain("smain", &symbol_table[hash("smain")]);

            *prog = appcode(*prog, makecode1(ENT, func_bc->oid));
            generateCode(p->child, symbol_table, prog);
            generateCode(p->child->brother->brother, symbol_table, prog);
            *prog = appcode(*prog, makecode1(RET, 0));
            p->is_gen = 1;

            break;

        case N_VAR_DECL:
            
            type_size = get_type_size(p->child->brother->type);

            int num;
            num = conta_fratelli(p->child->child, 0);

            for (int i = 0; i < num; i++)
            {
                *prog = appcode(*prog, makecode1(VARI, type_size));
            }

            p->is_gen = 1;
            break;

        case N_ASSIGN_STAT:
            generateCode(p->child->brother, symbtab, prog);

            char *id = p->child->value.sval;

            int env, oid;
            struct bucket *id_bucket = find_in_chain_senza_errore(id, &symbtab[hash(id)]);

            env = symbtab == symbol_table ? 0 : 1;
            if (id_bucket == NULL)
            {
                id_bucket = find_in_chain(id, &symbol_table[hash(id)]);
                env = 0;
            }

            oid = id_bucket->oid;
            struct SCode sto_code = makecode2(STO, env, oid);

            *prog = appcode(*prog, sto_code);
            p->is_gen = 1;
            break;

        case N_LOGIC_EXPR:

            if (p->op_code == T_AND)
            {
                generateCode(p->child, symbtab, prog);

                struct SCode *sub_prog5 = (struct SCode *)malloc(sizeof(struct SCode));
                *sub_prog5 = endcode();

                generateCode(p->child->brother, symbtab, sub_prog5);

                int offset = sub_prog5->num + 2;

                *prog = appcode(*prog, makecode1(JMF, offset));
                *prog = appcode(*prog, *sub_prog5);
                *prog = appcode(*prog, makecode1(JMP, 2));
                *prog = appcode(*prog, makecode1(LCI, 0));
            }
            else
            {
                generateCode(p->child, symbtab, prog);
                *prog = appcode(*prog, makecode1(JMF, 3));
                *prog = appcode(*prog, makecode1(LCI, 1));

                struct SCode *sub_prog6 = (struct SCode *)malloc(sizeof(struct SCode));
                *sub_prog6 = endcode();
                generateCode(p->child->brother, symbtab, sub_prog6);
                int exit = sub_prog6->num + 1;
                *prog = appcode(*prog, makecode1(JMP, exit));
                *prog = appcode(*prog, *sub_prog6);
            }

            p->is_gen = 1;
            break;

        case N_REL_EXPR:

            generateCode(p->child, symbtab, prog);
            generateCode(p->child->brother, symbtab, prog);

            switch (p->op_code)
            {
            case T_EQ:
                *prog = appcode(*prog, makecode(EQU));
                break;

            case T_NE:
                *prog = appcode(*prog, makecode(NEQ));
                break;

            case T_GT:

                switch (p->child->sem_type)
                {
                case S_REAL:
                    *prog = appcode(*prog, makecode(GTR));
                    break;

                case S_INTEGER:
                    *prog = appcode(*prog, makecode(GTI));
                    break;

                case S_STRING:
                    *prog = appcode(*prog, makecode(GTS));
                    break;
                }
                break;

            case T_LT:

                switch (p->child->sem_type)
                {
                case S_REAL:
                    *prog = appcode(*prog, makecode(LTR));
                    break;

                case S_INTEGER:
                    *prog = appcode(*prog, makecode(LTI));
                    break;

                case S_STRING:
                    *prog = appcode(*prog, makecode(LTS));
                    break;
                }
                break;

            case T_GE:

                switch (p->child->sem_type)
                {
                case S_REAL:
                    *prog = appcode(*prog, makecode(GER));
                    break;

                case S_INTEGER:
                    *prog = appcode(*prog, makecode(GEI));
                    break;

                case S_STRING:
                    *prog = appcode(*prog, makecode(GES));
                    break;
                }
                break;

            case T_LE:

                switch (p->child->sem_type)
                {
                case S_REAL:
                    *prog = appcode(*prog, makecode(LER));
                    break;

                case S_INTEGER:
                    *prog = appcode(*prog, makecode(LEI));
                    break;

                case S_STRING:
                    *prog = appcode(*prog, makecode(LES));
                    break;
                }
                break;
            }

            p->is_gen = 1;
            break;

        case N_MATH_EXPR:

            generateCode(p->child, symbtab, prog);
            generateCode(p->child->brother, symbtab, prog);

            switch (p->op_code)
            {
            case T_PLUS:
                if (p->sem_type == S_REAL)
                {
                    math_code = makecode(ADR);
                }
                else
                {
                    math_code = makecode(ADI);
                }

                *prog = appcode(*prog, math_code);
                break;

            case T_MINUS:
                if (p->sem_type == S_REAL)
                {
                    math_code = makecode(SBR);
                }
                else
                {
                    math_code = makecode(SBI);
                }

                *prog = appcode(*prog, math_code);
                break;

            case T_MUL:
                if (p->sem_type == S_REAL)
                {
                    math_code = makecode(MUR);
                }
                else
                {
                    math_code = makecode(MUI);
                }

                *prog = appcode(*prog, math_code);
                break;

            case T_DIV:
                if (p->sem_type == S_REAL)
                {
                    math_code = makecode(DVR);
                }
                else
                {
                    math_code = makecode(DVI);
                }

                *prog = appcode(*prog, math_code);
                break;
            }

            p->is_gen = 1;
            break;

        case N_NEG_EXPR:

            generateCode(p->child, symbtab, prog);
            if (p->op_code == T_NOT)
            {
                *prog = appcode(*prog, makecode(NEG));
            }
            else
            {
                if (p->child->sem_type == S_REAL)
                {
                    *prog = appcode(*prog, makecode(UMR));
                }
                else
                {
                    *prog = appcode(*prog, makecode(UMI));
                }
            }

            p->is_gen = 1;
            break;

        case N_COND_EXPR:

            generateCode(p->child, symbtab, prog);

            struct SCode *sub_prog1 = (struct SCode *)malloc(sizeof(struct SCode));
            *sub_prog1 = endcode();
            generateCode(p->child->brother, symbtab, sub_prog1);
            int cond_offset;
            cond_offset = sub_prog1->num + 2;

            *prog = appcode(*prog, makecode1(JMF, cond_offset));
            *prog = appcode(*prog, *sub_prog1);

            struct SCode *sub_prog2 = (struct SCode *)malloc(sizeof(struct SCode));
            *sub_prog2 = endcode();
            generateCode(p->child->brother->brother, symbtab, sub_prog2);
            int exit = sub_prog2->num + 1;

            *prog = appcode(*prog, makecode1(JMP, exit));
            *prog = appcode(*prog, *sub_prog2);

            p->is_gen = 1;
            break;

        case N_CASTING:
            generateCode(p->child, symbtab, prog);

            if (p->op_code == T_INTEGER)
            {
                cast_code = makecode(TOI);
            }
            else
            {
                cast_code = makecode(TOR);
            }

            *prog = appcode(*prog, cast_code);

            p->is_gen = 1;
            p->child->is_gen = 1;
            break;

        case N_READ_STAT:

            nume = conta_fratelli(p->child->child, 0);
            Pnode cont;
            cont = p->child->child;

            int env1, oid1;
            for (int i = 0; i < nume; i++)
            {
                struct bucket *cont_bucket = find_in_chain_senza_errore(cont->value.sval, &symbtab[hash(cont->value.sval)]);

                env1 = symbtab == symbol_table ? 0 : 1;

                if (cont_bucket == NULL)
                {
                    cont_bucket = find_in_chain(cont->value.sval, &symbol_table[hash(cont->value.sval)]);
                    env1 = 0;
                }

                oid1 = cont_bucket->oid;

                char *format = (char *)malloc(sizeof(char) * 25);

                format = get_format(cont_bucket->tipo);
                *prog = appcode(*prog, makeread(INP, format, env1, oid1));
                cont = cont->brother;
            }
            p->is_gen = 1;
            break;

        case N_WRITE_STAT:

            count_expr = p->child->brother->child;
            int num_expr;
            num_expr = conta_fratelli(count_expr, 0);

            char *write_format = (char *)malloc(sizeof(char) * 25);

            while (count_expr != NULL)
            {
                generateCode(count_expr, symbtab, prog);
                write_format = strcat(write_format, get_format(count_expr->sem_type));
                count_expr = count_expr->brother;
            }

            if (p->op_code == T_WRITELN)
            {
                write_format = strcat(write_format, "n");
            }

            *prog = appcode(*prog, makeout(OUT, num_expr, write_format));
            p->is_gen = 1;

            break;

        case N_FUNC_CALL:

            expr_list = p->child->brother;

            int num_formals;

            if (expr_list != NULL)
            {
                count_bro = expr_list->child;
                num_formals = conta_fratelli(count_bro, 0);

                while (count_bro != NULL)
                {
                    generateCode(count_bro, symbtab, prog);
                    count_bro = count_bro->brother;
                }
            }
            else
            {
                num_formals = 0;
            }

            int num_variables;
            num_variables = get_func_num_variables(p->child->value.sval);

            int entry;
            entry = get_func_entry_point(current_prog, p->child->value.sval);

            *prog = appcode(*prog, make_psh_pop(num_formals, num_variables, entry));

            p->is_gen = 1;
            break;

        case N_WHILE_STAT:
            while_expr = (struct SCode *)malloc(sizeof(struct SCode));
            *while_expr = endcode();
            generateCode(p->child, symbtab, while_expr);

            int while_expr_len = while_expr->num;
            *prog = appcode(*prog, *while_expr);

            struct SCode *sub_prog3 = (struct SCode *)malloc(sizeof(struct SCode));
            *sub_prog3 = endcode();
            generateCode(p->child->brother, symbtab, sub_prog3);

            int offset;
            offset = sub_prog3->num;

            struct SCode *sub_prog_while = (struct SCode *)malloc(sizeof(struct SCode));
            *sub_prog_while = endcode();

            *sub_prog_while = appcode(*sub_prog_while, makecode1(JMF, offset + 2));
            *sub_prog_while = appcode(*sub_prog_while, *sub_prog3);
            *sub_prog_while = appcode(*sub_prog_while, makecode1(JMP, -(offset + while_expr_len + 1)));
            *sub_prog_while = appcode(*sub_prog_while, makecode1(JMP, 1));
            correct_breaks(sub_prog_while);

            *prog = appcode(*prog, *sub_prog_while);
            p->is_gen = 1;

            break;

        case N_IF_STAT:
            generateCode(p->child, symbtab, prog);

            if (p->child->brother->brother != NULL)
            {

                struct SCode *sub_prog7 = (struct SCode *)malloc(sizeof(struct SCode));
                *sub_prog7 = endcode();
                generateCode(p->child->brother, symbtab, sub_prog7);
                int if_offset = sub_prog7->num + 2;

                *prog = appcode(*prog, makecode1(JMF, if_offset));
                *prog = appcode(*prog, *sub_prog7);

                struct SCode *sub_prog8 = (struct SCode *)malloc(sizeof(struct SCode));
                *sub_prog8 = endcode();
                generateCode(p->child->brother->brother, symbtab, sub_prog8);
                int if_exit = sub_prog8->num + 1;

                *prog = appcode(*prog, makecode1(JMP, if_exit));
                *prog = appcode(*prog, *sub_prog8);
            }
            else
            {

                struct SCode *sub_prog9 = (struct SCode *)malloc(sizeof(struct SCode));
                *sub_prog9 = endcode();
                generateCode(p->child->brother, symbtab, sub_prog9);
                int if_exit1 = sub_prog9->num + 1;

                *prog = appcode(*prog, makecode1(JMF, if_exit1));
                *prog = appcode(*prog, *sub_prog9);
            }

            p->is_gen = 1;
            break;

        case N_FOR_STAT:

            generateCode(p->child->brother, symbtab, prog);
            char *index_id = p->child->value.sval;

            struct bucket *index_bucket = find_in_chain_senza_errore(index_id, &symbtab[hash(index_id)]);
            env2 = symbtab == symbol_table ? 0 : 1;

            if (index_bucket == NULL)
            {
                index_bucket = find_in_chain(index_id, &symbol_table[hash(index_id)]);
                env2 = 0;
            }
            oid2 = index_bucket->oid;

            *prog = appcode(*prog, makecode2(STO, env2, oid2));

            generateCode(p->child->brother->brother, symbtab, prog);

            int oid3 = create_int_temp(symbtab, &oidl);
            int env3 = symbtab == symbol_table ? 0 : 1;

            *prog = appcode(*prog, makecode2(STO, env3, oid3));
            *prog = appcode(*prog, makecode2(LOD, env2, oid2));
            *prog = appcode(*prog, makecode2(LOD, env3, oid3));
            *prog = appcode(*prog, makecode(LEI));

            struct SCode *sub_prog10 = (struct SCode *)malloc(sizeof(struct SCode));
            *sub_prog10 = endcode();

            generateCode(p->child->brother->brother->brother, symbtab, sub_prog10);

            struct SCode *for_stats = (struct SCode *)malloc(sizeof(struct SCode));
            *for_stats = endcode();

            int for_exit = sub_prog10->num;

            *for_stats = appcode(*for_stats, makecode1(JMF, for_exit + 3));
            *for_stats = appcode(*for_stats, *sub_prog10);
            *for_stats = appcode(*for_stats, makecode2(INC, env2, oid2));
            *for_stats = appcode(*for_stats, makecode1(JMP, -(for_exit + 5)));

            correct_breaks(for_stats);
            *prog = appcode(*prog, *for_stats);
            p->is_gen = 1;

            break;

        case N_FUNC_DECL:

            func_bc = find_in_chain(p->child->value.sval, &symbol_table[hash(p->child->value.sval)]);
            oidl = count_var(func_bc->env.local_env) + func_bc->formali.num;
            *prog = appcode(*prog, makecode1(ENT, func_bc->oid));

            struct SCode *func_body = (struct SCode *)malloc(sizeof(struct SCode));
            *func_body = endcode();

            if (p->child->brother->value.ival == N_OPT_PARAM_LIST)
            {
                generateCode(p->child->brother->brother->brother, func_bc->env.local_env, prog);
                generateCode(p->child->brother->brother->brother->brother, func_bc->env.local_env, func_body);
            }
            else
            {
                generateCode(p->child->brother->brother, func_bc->env.local_env, prog);
                generateCode(p->child->brother->brother->brother, func_bc->env.local_env, func_body);
            }

            int num_return = 1;
            if (func_bc->tipo == S_VOID_)
            {
                num_return = 0;
            }
            *func_body = appcode(*func_body, makecode1(RET, num_return));
            correct_returns(func_body);

            *prog = appcode(*prog, *func_body);

            *current_prog = *prog;

            p->is_gen = 1;
            break;

        case N_RETURN_STAT:
            if (p->child != NULL)
            {

                generateCode(p->child, symbtab, prog);
            }

            cont_stat3 = p->brother;

            struct SCode *sub_prog14 = (struct SCode *)malloc(sizeof(struct SCode));
            *sub_prog14 = endcode();

            while (cont_stat3 != NULL)
            {
                generateCode(cont_stat3, symbtab, sub_prog14);
                cont_stat3 = cont_stat3->brother;
            }
            return_jump = sub_prog14->num + 1;
            *prog = appcode(*prog, makecode1(NIK, return_jump));
            *prog = appcode(*prog, *sub_prog14);

            p->is_gen = 1;
            break;

        default:

            break;
        }

        if (p->child != NULL && !p->is_gen)
        {
            generateCode(p->child, symbtab, prog);

            Pnode temp_node = p->child->brother;
            while (temp_node != NULL)
            {
                generateCode(temp_node, symbtab, prog);
                temp_node = temp_node->brother;
            }
        }
    }
}

void correct_breaks(struct SCode *sub_cycle)
{
    int cycle_len = sub_cycle->num;
    struct Stat *cont_stat = sub_cycle->first;

    int k = 0;
    while (cont_stat != NULL)
    {
        if (cont_stat->op == BRK)
        {
            cont_stat->op = JMP;
            cont_stat->args[0].ival = cycle_len - k;
        }
        cont_stat = cont_stat->next;
        k++;
    }
}

void correct_returns(struct SCode *func_body)
{
    int body_len = func_body->num;
    struct Stat *cont_stat = func_body->first;

    int k = 0;
    while (cont_stat != NULL)
    {
        if (cont_stat->op == NIK)
        {
            cont_stat->op = JMP;
            cont_stat->args[0].ival = body_len - k - 1;
        }
        cont_stat = cont_stat->next;
        k++;
    }
}

int get_func_num_variables(char *id)
{
    struct bucket *bc = find_in_chain(id, &symbol_table[hash(id)]);
    return count_var(bc->env.local_env);
}

int get_func_entry_point(struct SCode *prog, char *id)
{

    int func_oid;
    struct bucket *func_bc = find_in_chain(id, &symbol_table[hash(id)]);

    func_oid = func_bc->oid;

    int entry_point = 5;

    struct Stat *cont_stat = prog->first;

    while (cont_stat != NULL)
    {
        if (cont_stat->op == ENT && cont_stat->args[0].ival == func_oid)
        {
            return entry_point;
        }
        cont_stat = cont_stat->next;
        entry_point++;
    }
    return entry_point;
}

void relocate_address(struct SCode code, int offset)
{
    struct Stat *p = code.first;
    int i;

    for (i = 1; i <= code.num; i++)
    {
        p->address += offset;
        p = p->next;
    }
}

struct SCode appcode(struct SCode code1, struct SCode code2)
{
    if (code1.num == 0)
    {
        return code2;
    }
    else if (code2.num == 0)
    {
        return code1;
    }

    struct SCode rescode;

    relocate_address(code2, code1.num);
    rescode.first = code1.first;
    rescode.last = code2.last;
    code1.last->next = code2.first;
    rescode.num = code1.num + code2.num;
    return rescode;
}

struct SCode endcode()
{
    struct SCode code = {NULL, 0, NULL};
    return code;
}

struct SCode concode(struct SCode code1, struct SCode code2, ...)
{
    struct SCode rescode = code1;
    struct SCode *pcode = &code2;

    while (pcode->first != NULL)
    {
        rescode = appcode(rescode, *pcode);
        pcode++;
    }
    return rescode;
}

struct Stat *newstat(Operator op)
{
    struct Stat *pstat;

    pstat = (struct Stat *)malloc(sizeof(struct Stat));
    pstat->address = 0;
    pstat->op = op;
    pstat->next = NULL;
    return pstat;
}

struct SCode makeread(Operator op, char *format, int arg1, int arg2)
{
    struct SCode code;
    code = makecode(op);
    code.first->args[0].sval = newstring(format);
    code.first->args[1].ival = arg1;
    code.first->args[2].ival = arg2;

    return code;
}

struct SCode makeout(Operator op, int n, char *format)
{
    struct SCode code;
    code = makecode1(op, n);

    code.first->args[1].sval = format;
    return code;
}

struct SCode makecode(Operator op)
{
    struct SCode code;

    code.first = code.last = newstat(op);
    code.num = 1;
    return code;
}

struct SCode makecode_from_stat(struct Stat stat)
{
    struct SCode code;
    code.first = code.last = &stat;
    code.num = 1;
    return code;
}

struct SCode makecode1(Operator op, int arg)
{
    struct SCode code;

    code = makecode(op);
    code.first->args[0].ival = arg;
    return code;
}

struct SCode makecode2(Operator op, int arg1, int arg2)
{
    struct SCode code;

    code = makecode1(op, arg1);
    code.first->args[1].ival = arg2;
    return code;
}

struct SCode makecode3(Operator op, int arg1, int arg2, int arg3)
{
    struct SCode code;

    code = makecode2(op, arg1, arg2);
    code.first->args[2].ival = arg3;
    return code;
}

struct SCode make_psh_pop(int num_formals, int num_variables, int entry)
{
    struct SCode code;
    code = appcode(makecode2(PSH, num_formals, num_variables), makecode1(GOT, entry));
    code = appcode(code, makecode(POP));
    return code;
}

struct SCode make_lci(int i)
{
    return makecode1(LCI, i);
}

struct SCode make_lcr(float r)
{
    struct SCode code;

    code = makecode(LCR);
    code.first->args[0].fval = r;
    return code;
}

struct SCode make_lcs(char *s)
{
    struct SCode code;

    code = makecode(LCS);
    code.first->args[0].sval = s;
    return code;
}

char *get_format(symb_type txpe)
{
    switch (txpe)
    {
    case S_REAL:
        return "r";
        break;
    case S_INTEGER:
        return "i";
        break;

    case S_BOOLEAN_:
        return "b";
        break;

    case S_STRING:
        return "s";
        break;

    default:
        fprintf(stderr,"ERRORE: NON è POSSIBILE STAMPARE DATI VOID\n");
        exit(-1);
    }
}

int get_type_size(Typenode type)
{

    switch (type)
    {
    case T_BOOLEAN:
        return 4;
        break;
    case T_INTEGER:
        return 4;
        break;
    case T_STRING:
        return 16;
        break;
    case T_REAL:
        return 8;
        break;

    default:
        return 8;
        break;
    }
}

int is_const(Pnode p)
{
    switch (p->type)
    {
    case T_INTCONST:
        return 0;
        break;
    case T_BOOLCONST:
        return 1;
        break;
    case T_STRCONST:
        return 2;
        break;
    case T_REALCONST:
        return 3;
        break;

    default:
        return 4;
        break;
    }
}

void generateID_Code(Pnode p, struct bucket *symbtab, struct SCode *prog)
{
    int oid;
    int env = symbtab == symbol_table ? 0 : 1;

    struct bucket *bc = find_in_chain_senza_errore(p->value.sval, &symbtab[hash(p->value.sval)]);
    if (bc == NULL)
    {
        bc = find_in_chain(p->value.sval, &symbol_table[hash(p->value.sval)]);
        env = 0;
    }
    oid = bc->oid;
    *prog = appcode(*prog, makecode2(LOD, env, oid));
}
