#include "def.h"
#include "string.h"


int oid_g = 0;

int create_int_temp(struct bucket *env, int *oid_l) {
    if (env[SYMTAB_SIZE - 1].oid == 0)
    {
        env[SYMTAB_SIZE - 1].nome = NULL;
        env[SYMTAB_SIZE - 1].tipo = S_INTEGER;
        env[SYMTAB_SIZE - 1].classe = VAR;
        if (env != symbol_table)
        {
            env[SYMTAB_SIZE - 1].oid = ++*oid_l;
        } else
        {
            env[SYMTAB_SIZE - 1].oid = ++oid_g;
        }
        
        return env[SYMTAB_SIZE - 1].oid;
    }
    
    int chain_oid = env == symbol_table? oid_g: *oid_l;

    return add_temp_in_chain(env[SYMTAB_SIZE - 1].next, &chain_oid);
}

int add_temp_in_chain(struct bucket *bc,int *oid_l) {
    if (bc == NULL)
    {
        bc = init_bucket();
        bc->nome = NULL;
        bc->tipo = S_INTEGER;
        bc->classe = VAR;
        bc->oid = ++*oid_l;
        return bc->oid;
    }
    return add_temp_in_chain(bc->next, oid_l);
}

int count_var(struct bucket *table) {
    
    int contavar = 0;
    struct bucket *chain_start;
    
    for (int i = 0; i < SYMTAB_SIZE - 1; i++)
    {

        if (table[i].classe == VAR && strcmp(table[i].nome, "") != 0)
        {
            contavar++;
        }

        if (table[i].next != NULL)
        {
            /* code */
            chain_start = table[i].next;
        }

        if (table[i].next == NULL)
        {
            continue;
        }
    
        contavar += count_var_in_chain(chain_start);
    }
    
    return contavar;
}

int count_var_in_chain(struct bucket *bc) {
    
    int chain_vars = 0;

    while (bc != NULL)
    {
        if (bc->classe == VAR)
        {
            chain_vars++;
        }
        bc = bc->next;
        
    }
    return chain_vars;
}

struct bucket *find_in_chain(char *id, struct bucket *bc) {
    if (strcmp(bc->nome,id) == 0)
    {
        return bc;

    } else if (bc->next == NULL)
    {
        fprintf(stderr, "ID %s ::NON PRESENTE\n",id);
        exit(-1);
    } else
    {
        return find_in_chain(id,bc->next);
    }
}


void print_symbol_table(struct bucket symbtab[]) {

    if (symbtab == NULL)
    {
        printf("no local_env\n");
        return;
    }
    
    for (int j = 0; j < SYMTAB_SIZE; j++)
    {
        if (strlen(symbtab[j].nome) == 0)
            continue;

        printf("%d) elem_id: %s", j, symbtab[j].nome);
        printf("    elem_classe: %d", symbtab[j].classe);
        printf("    elem_tipo: %d", symbtab[j].tipo);
        printf("    elem_oid: %d\n", symbtab[j].oid);

        if (symbtab[j].classe == FUN) {
            printf("    elem_num_p: %d\n", symbtab[j].formali.num);
            print_symbol_table(symbtab[j].env.local_env);

            for (int i = 0; i < symbtab[j].formali.num; i++)
            {
                if (strlen(symbtab[j].formali.descr[i]->nome) == 0)
                    continue;
                printf("DESCR ( %d ): %s\n", i, symbtab[j].formali.descr[i]->nome);
            }
        }

        if (symbtab[j].next != NULL)
        {
            print_bucket(symbtab[j].next);
        }
        printf("\n");
    }
}

struct param_formali init_pf(int numero_param)
{
    if (numero_param == 0)
    {
        return (struct param_formali){0,NULL};
    }
    
    struct bucket **descr = (struct bucket **)malloc(numero_param * sizeof(struct bucket *));
    for (int i = 0; i < numero_param; i++)
    {
        descr[i] = init_bucket();
    }

    struct param_formali pf = {numero_param, descr};
    return pf;
}

struct bucket* init_symbol_table(int num) {
    struct bucket *table = (struct bucket *)malloc(num * sizeof(struct bucket));
    for (int i = 0; i < num; i++)
    {
        table[i] = *init_bucket();
    }
    return table;
}

int hash(const char *id)
{
    int h = 0, i;
    for (i = 0; id[i] != '\0'; i++)
        h = ((h << SHIFT) + id[i]) % (SYMTAB_SIZE - 1);
    return abs(h);
}

struct bucket *init_bucket()
{
    struct bucket *b = malloc(sizeof(struct bucket));
    *b = (struct bucket){(char *)malloc(140), C_NULL, 0, T_NULL, (struct bucket *)malloc(100 * sizeof(struct bucket)), 0,(struct bucket **) calloc(20, sizeof(struct bucket*)), malloc(sizeof(struct bucket))};
    b->nome = "";
    b->next = NULL;
    return b;
}

void insert_by_ID(char *id, struct bucket symbtab[])
{
    if (strcmp(symbtab[hash(id)].nome, "") == 0)
    {
        symbtab[hash(id)].nome = newstring(id);
    }
    else if (strcmp(symbtab[hash(id)].nome, id) == 0)
    {
        fprintf(stderr, "ERRORE::ID GIA PRESENTE");
        exit(-1);
    }
    else if (symbtab[hash(id)].next == NULL)
    {
        symbtab[hash(id)].next = init_bucket();
        symbtab[hash(id)].next->nome = newstring(id);
    }
    else
    {
        add_in_chain(id, symbtab[hash(id)].next);
    }
}

void insert(char *id, symb_class classe, symb_type tipo, struct bucket symbtab[], int *oid_gg)
{
    if (strlen(symbtab[hash(id)].nome) == 0)
    {
        symbtab[hash(id)].nome = newstring(id);
        symbtab[hash(id)].classe = classe;
        symbtab[hash(id)].tipo = tipo;
        symbtab[hash(id)].oid = ++*oid_gg;
    }
    else if (strcmp(symbtab[hash(id)].nome, id) == 0)
    {
        fprintf(stderr, "ERRORE::ID GIA PRESENTE");
        exit(-1);
    }
    else if (symbtab[hash(id)].next == NULL)
    {
        symbtab[hash(id)].next = init_bucket();
        symbtab[hash(id)].next->nome = newstring(id);
        symbtab[hash(id)].next->classe = classe;
        symbtab[hash(id)].next->tipo = tipo;
        symbtab[hash(id)].next->oid = ++*oid_gg;
    }
    else
    {
        add_in_chain_args(id, classe, tipo, symbtab[hash(id)].next, oid_gg);
    }
}

void insert_func(char *id, symb_type tipo, struct param_formali formali, struct bucket local_env[], struct bucket symbtab[])
{
    if (strcmp(symbtab[hash(id)].nome, "") == 0)
    {
        symbtab[hash(id)].nome = newstring(id);
        symbtab[hash(id)].classe = FUN;
        symbtab[hash(id)].tipo = tipo;
        symbtab[hash(id)].oid = ++oid_g;
        symbtab[hash(id)].formali = formali;
        symbtab[hash(id)].env.local_env = local_env;
    }
    else if (strcmp(symbtab[hash(id)].nome, id) == 0)
    {
        fprintf(stderr, "ERRORE::ID GIA PRESENTE");
        exit(-1);
    }
    else if (symbtab[hash(id)].next == NULL)
    {
        symbtab[hash(id)].next = init_bucket();
        symbtab[hash(id)].next->nome = newstring(id);
        symbtab[hash(id)].next->classe = FUN;
        symbtab[hash(id)].next->tipo = tipo;
        symbtab[hash(id)].next->oid = ++oid_g;
        symbtab[hash(id)].next->formali = formali;
        symbtab[hash(id)].next->env.local_env = local_env;
    }
    else
    {
        add_func_in_chain_args(id, tipo, formali, local_env,symbtab[hash(id)].next, &oid_g);
    }
}

void add_func_in_chain_args(char *id, symb_type tipo, struct param_formali formali, struct bucket local_env[] ,struct bucket *bc, int *oid_gg)
{
    if (strcmp(bc->nome, id) == 0)
    {
        fprintf(stderr, "ERRORE::ID GIA PRESENTE");
        exit(-1);
    }

    if (bc->next == NULL)
    {
        bc->next = init_bucket();
        bc->next->nome = newstring(id);
        bc->next->classe = FUN;
        bc->next->tipo = tipo;
        bc->next->oid = ++*oid_gg;
        bc->next->formali = formali;
        bc->next->env.local_env = local_env;
    }
    else
    {
        add_func_in_chain_args(id, tipo, formali,local_env, bc->next, oid_gg);
    }
}

void add_in_chain_args(char *id, symb_class classe, symb_type tipo, struct bucket *bc, int *oid_gg)
{
    if (strcmp(bc->nome, id) == 0)
    {
        fprintf(stderr, "ERRORE::ID GIA PRESENTE");
        exit(-1);
    }

    if (bc->next == NULL)
    {
        bc->next = init_bucket();
        bc->next->nome = newstring(id);
        bc->next->classe = classe;
        bc->next->tipo = tipo;
        bc->next->oid = ++*oid_gg;
    }
    else
    {
        add_in_chain_args(id, classe, tipo, bc->next, oid_gg);
    }
}

void add_in_chain(char *id, struct bucket *bc)
{
    if (strcmp(bc->nome, id) == 0)
    {
        fprintf(stderr, "ERRORE::ID GIA PRESENTE");
        exit(-1);
    }
    if (bc->next == NULL)
    {
        bc->next = init_bucket();
        bc->next->nome = newstring(id);
    }
    else
    {
        add_in_chain(id, bc->next);
    }
}

void print_bucket(struct bucket *bucket)
{
    if (strlen(bucket->nome) == 0)
    {
        return;
    }
    else
    {
        printf("elem_id: %s", bucket->nome);
        printf("    elem_classe: %d", bucket->classe);
        printf("    elem_tipo: %d", bucket->tipo);
        printf("    elem_oid: %d", bucket->oid);

        if (bucket->classe == FUN)
        {
            printf("    elem_num_p: %d\n", bucket->formali.num);
            print_symbol_table(bucket->env.local_env);

            for (int i = 0; i < bucket->formali.num; i++)
            {
                if (strlen(bucket->formali.descr[i]->nome) == 0)
                    continue;
                    
                printf("DESCR ( %d ): %s\n",i,bucket->formali.descr[i]->nome);
            }
            
        }

        printf("\n");
    }
    if (bucket->next == NULL)
        return;
    else
        print_bucket(bucket->next);
}