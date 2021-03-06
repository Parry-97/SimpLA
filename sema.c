#include <stdlib.h>
#include "string.h"
#include "def.h"

extern struct bucket *symbol_table;
struct symb_type return_type = (struct symb_type){S_VOID_, 1, NULL};
int is_loop = 0;


bool compare_types(struct symb_type type1, struct symb_type type2)
{
    if (type1.dim != type2.dim)
    {
        return false;
    }
    else if (type1.stipo != type2.stipo)
    {
        return false;
    }
    else if (type1.sub_type == NULL && type2.sub_type == NULL)
    {
        return true;
    }
    else if (type1.sub_type == NULL || type2.sub_type == NULL)
    {
        return false;
    }
    else
    {
        return compare_types(*(type1.sub_type), *(type2.sub_type));
    }
}

void find_index_in_statlist(char *id, Pnode node)
{

    switch (node->value.ival)
    {
    case N_ASSIGN_STAT:

        if (node->child->type != T_ID)
        {
            break;
        }

        if (strcmp(node->child->value.sval, id) == 0)
        {
            fprintf(stderr, "LOOP ERROR: L'INDICE NON SI PUO' ASSEGNARE NEL FOR\n");
            exit(-1);
        }
        break;

    case N_FOR_STAT:
        find_index_in_statlist(id, node->child->brother->brother->brother->child);
        break;

    case N_WHILE_STAT:
        find_index_in_statlist(id, node->child->brother->child);
        break;

    case N_READ_STAT:
        if (strcmp(node->child->child->value.sval, id) == 0)
        {
            fprintf(stderr, "LOOP ERROR: L'INDICE NON SI PUO' ASSEGNARE NEL READ\n");
            exit(-1);
        }

        Pnode nodo_indice = node->child->child;

        while (nodo_indice->brother != NULL)
        {
            /* code */
            if (strcmp(nodo_indice->brother->value.sval, id) == 0)
            {
                /* code */
                fprintf(stderr, "LOOP ERROR: L'INDICE NON SI PUO' ASSEGNARE NEL READ\n");
                exit(-1);
            }
            nodo_indice = nodo_indice->brother;
        }

        break;

    case N_IF_STAT:
        find_index_in_statlist(id, node->child->brother->child);

        if (node->child->brother->brother != NULL)
        {
            /* code */
            find_index_in_statlist(id, node->child->brother->brother->child);
        }

        break;

    default:
        break;
    }

    if (node->brother != NULL)
    {
        /* code */
        find_index_in_statlist(id, node->brother);
    }
}

struct bucket *find_in_chain_senza_errore(char *id, struct bucket *bc)
{
    if (strcmp(bc->nome, id) == 0)
    {
        return bc;
    }
    else if (bc->next == NULL)
    {
        return NULL;
    }
    else
    {
        return find_in_chain_senza_errore(id, bc->next);
    }
}

int conta_fratelli(Pnode fratello)
{
    int contatore = 0;
    Pnode temp = fratello;

    while (temp != NULL)
    {
        contatore++;
        temp = temp->brother;
    }
    return contatore;
}

void analizza_id(Pnode nodo_id, struct bucket symbtab[])
{

    struct bucket *bc_1;

    bc_1 = find_in_chain_senza_errore(nodo_id->value.sval, &symbtab[hash(nodo_id->value.sval)]);

    if (bc_1 == NULL)
    {
        bc_1 = find_in_chain(nodo_id->value.sval, &symbol_table[hash(nodo_id->value.sval)]);
    }

    nodo_id->sem_type = bc_1->bucket_type;
}

struct bucket *find_index_in_env(char *id, struct bucket symbtab[])
{
    struct bucket *bc = find_in_chain_senza_errore(id, &symbtab[hash(id)]);
    if (bc == NULL)
    {
        /* code */
        bc = find_in_chain(id, &symbol_table[hash(id)]);
    }

    return bc;
}

//FIXME: Diversificare meglio gli errori, troppo simili!
void analizza(Pnode root, struct bucket symbtab[])
{
    int n_expr = 0;
    struct bucket *bc_6;
    struct bucket *bc_5;
    struct bucket *bc_4;
    struct bucket *bc_3;
    struct bucket *bc_2;
    struct bucket *bc_1;
    struct bucket *bc;
    Pnode temp_node_1;

    if (root->type == T_ID)
    {

        analizza_id(root, symbtab);
    }
    else if (root->type == T_BREAK)
    {
        if (!is_loop)
        {
            fprintf(stderr, "LOOP ERROR: BREAK NON CONCESSO\n");
            exit(-1);
        }
    }
    else if (root->type == T_NONTERMINAL)
    {

        switch (root->value.ival)
        {

        case N_VAR_DECL:
            if (root->child->brother->type == T_VOID)
            {
                fprintf(stderr, "DECL_ERROR: TIPO VOID APPLICABILE SOLO A FUNZIONI\n");
                exit(-1);
            }
            break;

        case N_LOGIC_EXPR:
            if (root->op_code != T_AND && root->op_code != T_OR)
            {
                fprintf(stderr, "LOGIC ERROR: OPERATORE LOGICO ERRATO\n");
                exit(-1);
            }

            analizza(root->child, symbtab);
            analizza(root->child->brother, symbtab);
            if (root->child->sem_type.stipo != S_BOOLEAN_ || root->child->brother->sem_type.stipo != S_BOOLEAN_)
            {
                fprintf(stderr, "LOGIC ERROR : TIPI LOGICI NON CONSENTITI\n");
                exit(-1);
            }

            root->sem_type = (struct symb_type){S_BOOLEAN_, 1, NULL};
            break;

        case N_REL_EXPR:
            analizza(root->child, symbtab);
            analizza(root->child->brother, symbtab);

            if ((root->child->sem_type.stipo == S_VECTOR || root->child->brother->sem_type.stipo == S_VECTOR))
            {
                if (root->op_code != T_IN)
                {
                    fprintf(stderr, "REL_ERROR: CONDIZIONE RELAZIONALE ERRATA \n");
                    exit(-1);
                }
                else if (!compare_types(root->child->sem_type, *(root->child->brother->sem_type.sub_type)))
                {

                    fprintf(stderr, "REL_ERROR: CONDIZIONE RELAZIONE ERRATA \n");
                    exit(-1);
                }
            }
            else if (root->child->sem_type.stipo != root->child->brother->sem_type.stipo)
            {
                fprintf(stderr, "REL_ERROR: CONDIZIONE RELAZIONALE ERRATA\n");
                exit(-1);
            }
            root->sem_type = (struct symb_type){S_BOOLEAN_,1,NULL};

            break;

        case N_MATH_EXPR:
            analizza(root->child, symbtab);
            analizza(root->child->brother, symbtab);
            if (root->child->sem_type.stipo != root->child->brother->sem_type.stipo)
            {
                fprintf(stderr, "MATH ERROR: OPERAZIONE TRA TIPI DIFFERENTI\n");
                exit(-1);
            }

            if (root->child->sem_type.stipo != S_INTEGER && root->child->sem_type.stipo != S_REAL)
            {
                fprintf(stderr, "MATH ERROR: TIPO NON CONFORME ALL'ESPRESSIONE\n");
                exit(-1);
            }

            root->sem_type = root->child->sem_type;
            break;

        case N_NEG_EXPR:

            analizza(root->child, symbtab);
            if (root->op_code == T_MINUS && root->child->sem_type.stipo == S_BOOLEAN_)
            {

                fprintf(stderr, "NEG_ERROR: OPERATORE DI SOTTRAZIONE NON USATO CORRETTAMENTE\n");
                exit(-1);
            }
            else if (root->op_code == T_NOT && root->child->sem_type.stipo != S_BOOLEAN_)
            {

                fprintf(stderr, "NEG_ERROR: OPERATORE DI NEGAZIONE NON USATO CORRETTAMENTE\n");
                exit(-1);
            }

            root->sem_type = root->child->sem_type;

            break;


        case N_LHS:
            
            analizza(root->child, symbtab);
            analizza(root->child->brother, symbtab);

            if (root->child->type == T_ID)
            {
                bc_6 = find_index_in_env(root->child->value.sval, symbtab);

                if (bc_6->classe == FUN)
                {
                    fprintf(stderr, "LHS_ERROR: NON E' POSSIBILE INDICIZZARE UNA FUNZIONE\n");
                    exit(-1);
                }
                /* code */
                root->sem_type = root->child->sem_type;
            }

            if (root->child->sem_type.sub_type->stipo == S_VOID_)
            {
                fprintf(stderr, "LHS_ERROR: NON E' POSSIBILE CREARE VETTORI DI TIPO VOID\n");
                exit(-1);
            }

            if (root->child->sem_type.stipo == S_VECTOR && root->child->brother->sem_type.stipo == S_INTEGER)
            {
                root->sem_type = *(root->child->sem_type.sub_type);
            } else
            {
                fprintf(stderr, "LHS_ERROR: ERRORE IN INDICIZZAZIONE\n");
                exit(-1);
            }
            break;

        case N_VEC_CONSTR:

            n_expr = conta_fratelli(root->child->child);
            Pnode iter_expr = root->child->child;
            while (iter_expr != NULL)
            {
                analizza(iter_expr, symbtab);
                iter_expr = iter_expr->brother;
            }
            iter_expr = root->child->child->brother;

            while (iter_expr != NULL)
            {
                if (!compare_types(iter_expr->sem_type, root->child->child->sem_type))
                {
                    fprintf(stderr, "VEC_ERROR: VETTORE NON PROPRIAMENTE COSTRUITO\n");
                    exit(-1);
                }

                iter_expr = iter_expr->brother;
            }
            root->sem_type = (struct symb_type){S_VECTOR, n_expr, &(root->child->child->sem_type)};
            break;

        case N_FUNC_CALL:
            bc_3 = find_in_chain(root->child->value.sval, &symbol_table[hash(root->child->value.sval)]);

            if (bc_3->classe != FUN)
            {
                fprintf(stderr, "FUNC_ERROR: FUNZIONE NON ESISTENTE\n");
                exit(-1);
            }

            int n = 0;
            if (root->child->brother != NULL)
            {
                n = conta_fratelli(root->child->brother->child);
            }

            if (n != bc_3->formali.num)
            {
                fprintf(stderr, "FUNC_ERROR: IL NUMERO DI PARAMETRI E' ERRATO\n");
                exit(-1);
            }

            Pnode temp_node;
            if (n != 0)
            {
                temp_node = root->child->brother->child;
            }

            for (int i = 0; i < n; i++)
            {
                analizza(temp_node, symbtab);
                if (bc_3->formali.descr[i]->bucket_type.stipo != temp_node->sem_type.stipo)
                {
                    fprintf(stderr, "FUNC_ERROR: TIPI DI PARAM NON COMPATIBILI\n");
                    exit(-1);
                }

                if (temp_node->brother != NULL)
                    temp_node = temp_node->brother;
            }
            root->sem_type = bc_3->bucket_type;
            break;

        case N_COND_EXPR:
            analizza(root->child, symbtab);
            if (root->child->sem_type.stipo != S_BOOLEAN_)
            {
                fprintf(stderr, "COND_ERROR: CONDIZIONE ERRATA\n");
                exit(-1);
            }

            analizza(root->child->brother, symbtab);
            analizza(root->child->brother->brother, symbtab);
            if (root->child->brother->sem_type.stipo != root->child->brother->brother->sem_type.stipo)
            {
                fprintf(stderr, "COND_ERROR: CONDIZIONE ERRATA\n");
                exit(-1);
            }

            root->sem_type = root->child->brother->sem_type;

            break;

        case N_CASTING:
            analizza(root->child, symbtab);
            if (root->child->sem_type.stipo != S_INTEGER && root->child->sem_type.stipo != S_REAL)
            {
                /* code */
                fprintf(stderr, "CAST_ERROR: CASTING ERRATO\n");
                exit(-1);
            }
            if (root->child->sem_type.stipo == S_INTEGER && root->op_code == T_INTEGER)
            {
                fprintf(stderr, "CAST_ERROR: CASTING SUPERFLUO\n");
                exit(-1);
            }
            if (root->child->sem_type.stipo == S_REAL && root->op_code == T_REAL)
            {
                fprintf(stderr, "CAST_ERROR: CASTING SUPERFLUO\n");
                exit(-1);
            }
            int tipos = root->op_code == T_INTEGER ? S_INTEGER : S_REAL;
            root->sem_type = (struct symb_type){tipos, 1, NULL};
            break;

        case N_ASSIGN_STAT:

            analizza(root->child, symbtab);
            analizza(root->child->brother, symbtab);
            if (!compare_types(root->child->sem_type, root->child->brother->sem_type))
            {
                fprintf(stderr, "ASSIGN_ERROR: ASSEGNAMENTO NON CONSENTITO (TIPI DIFFERENTI)\n");
                exit(-1);
            }

            break;

        case N_IF_STAT:

            analizza(root->child, symbtab);
            if (root->child->sem_type.stipo != S_BOOLEAN_)
            {
                fprintf(stderr, "IF_ERROR: IF NON CORRETTO\n");
                exit(-1);
            }
            analizza(root->child->brother, symbtab);

            if (root->child->brother->brother != NULL)
            {
                /* code */
                analizza(root->child->brother->brother, symbtab);
            }

            break;

        case N_WHILE_STAT:
            is_loop++;
            analizza(root->child, symbtab);
            if (root->child->sem_type.stipo != S_BOOLEAN_)
            {
                fprintf(stderr, "WHILE_ERROR: WHILE NON CORRETTO\n");
                exit(-1);
            }
            analizza(root->child->brother, symbtab);
            is_loop--;
            break;

        case N_FOR_STAT:
            is_loop++;
            bc = find_index_in_env(root->child->value.sval, symbtab);

            if (bc->classe == FUN)
            {
                fprintf(stderr, "FOR_ERROR: NON E' POSSIBILE UTILIZZARE UNA FUNZIONE COME INDICE\n");
                exit(-1);
            }

            analizza(root->child, symbtab);

            if (root->child->sem_type.stipo != S_INTEGER)
            {
                fprintf(stderr, "FOR_ERROR: INDICE DEL CICLO DEVE ESSERE INTERO \n");
                exit(-1);
            }

            analizza(root->child->brother, symbtab);
            analizza(root->child->brother->brother, symbtab);

            if (root->child->brother->sem_type.stipo != S_INTEGER || root->child->brother->brother->sem_type.stipo != S_INTEGER)
            {
                fprintf(stderr, "FOR_ERROR: TIPO DELL' ESPRESSIONE DEV'ESSERE INTERO\n");
                exit(-1);
            }
            find_index_in_statlist(root->child->value.sval, root->child->brother->brother->brother->child);
            analizza(root->child->brother->brother->brother, symbtab);
            is_loop--;
            break;

        case N_RETURN_STAT:
            if (root->child == NULL)
            {
                root->sem_type.stipo = S_VOID_;
            }
            else
            {
                analizza(root->child, symbtab);
                root->sem_type = root->child->sem_type;
            }

            if (return_type.stipo != root->sem_type.stipo)
            {
                fprintf(stderr, "RET_ERROR: RETURN NON CORRETTO\n");
                exit(-1);
            }
            break;

        case N_READ_STAT:
            temp_node_1 = root->child->child;
            while (temp_node_1 != NULL)
            {
                analizza(temp_node_1, symbtab);
                if (temp_node_1->sem_type.stipo == S_VECTOR)
                {
                    /* code */
                    fprintf(stderr, "READ ERROR: READ DIRETTA DI VETTORE NON PERMESSA !\n");
                    exit(-1);
                }

                temp_node_1 = temp_node_1->brother;
            }

            break;

        case N_WRITE_STAT:
            temp_node_1 = root->child->brother->child;
            while (temp_node_1 != NULL)
            {
                analizza(temp_node_1, symbtab);
                if (temp_node_1->sem_type.stipo == S_VECTOR)
                {
                    /* code */
                    fprintf(stderr, "WRITE ERROR: WRITE DIRETTA DI VETTORE NON PERMESSA !\n");
                    exit(-1);
                }

                temp_node_1 = temp_node_1->brother;
            }

            break;

        default:

            if (root->value.ival == N_FUNC_DECL)
            {
                bc_5 = find_in_chain(root->child->value.sval, &symbol_table[hash(root->child->value.sval)]);
                symbtab = bc_5->env.local_env;
                return_type = bc_5->bucket_type;
            }

            if (root->child != NULL)
            {

                analizza(root->child, symbtab);

                Pnode temp_node2 = root->child->brother;
                while (temp_node2 != NULL)
                {
                    analizza(temp_node2, symbtab);
                    temp_node2 = temp_node2->brother;
                }
                if (root->value.ival == N_FUNC_DECL)
                {
                    /* code */
                    return_type.stipo = S_VOID_;
                }
            }
            break;
        }
    }
}
