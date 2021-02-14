#include <stdlib.h>
#include "string.h"
#include "def.h"

extern struct bucket *symbol_table;
struct symb_type return_type = (struct symb_type){S_VOID_, 1, NULL};
int is_loop = 0;

bool compare_types(struct symb_type type1, struct symb_type type2)
{
    if (type1.dim != type2.dim || type1.stipo != type2.stipo)
    {
        return false;
    }
    if (type1.sub_type == NULL && type2.sub_type == NULL)
    {
        return true;
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
        //TODO: sembra esserci un problema con gli lhs che non hanno piu un reference a un id
    case N_ASSIGN_STAT:

        if (node->child->type != T_ID)
        {
            break;
        }

        if (strcmp(node->child->value.sval, id) == 0)
        {
            fprintf(stderr, "ERRORE: L'INDICE NON SI PUO' ASSEGNARE NEL FOR\n");
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
            fprintf(stderr, "ERRORE: L'INDICE NON SI PUO' ASSEGNARE NEL READ\n");
            exit(-1);
        }

        Pnode nodo_indice = node->child->child;

        while (nodo_indice->brother != NULL)
        {
            /* code */
            if (strcmp(nodo_indice->brother->value.sval, id) == 0)
            {
                /* code */
                fprintf(stderr, "ERRORE: L'INDICE NON SI PUO' ASSEGNARE NEL READ\n");
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
    while (fratello != NULL)
    {
        contatore++;
        fratello = fratello->brother;
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

    nodo_id->sem_type = bc_1->bucket_type; //TODO: Check it out
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

//FIXME: cambiare dove necessarrio il confronto di tipi con compare_types();
void analizza(Pnode root, struct bucket symbtab[])
{
    int n_expr;
    struct bucket *bc_6;
    struct bucket *bc_5;
    struct bucket *bc_4;
    struct bucket *bc_3;
    struct bucket *bc_2;
    struct bucket *bc_1;
    struct bucket *bc;

    if (root->type == T_ID)
    {

        analizza_id(root, symbtab);
    }
    else if (root->type == T_BREAK)
    {
        if (!is_loop)
        {
            fprintf(stderr, "ERRORE: BREAK NON CONCESSO\n");
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
                fprintf(stderr, "ERRORE: TIPO VOID APPLICABILE SOLO A FUNZIONI\n");
                exit(-1);
            }
            break;

        case N_LOGIC_EXPR:
            if (root->op_code != T_AND && root->op_code != T_OR)
            {
                fprintf(stderr, "ERRORE: OPERATORE LOGICO ERRATO\n");
                exit(-1);
            }

            analizza(root->child, symbtab);
            analizza(root->child->brother, symbtab);
            if (root->child->sem_type.stipo != S_BOOLEAN_ || root->child->brother->sem_type.stipo != S_BOOLEAN_)
            {
                fprintf(stderr, "ERRORE: OPERATORE RELAZIONALE ERRATO\n");
                exit(-1);
            }

            root->sem_type.stipo = S_BOOLEAN_; //TODO: make sure not gives SIGSEV

            break;

        case N_REL_EXPR:
            analizza(root->child, symbtab);
            analizza(root->child->brother, symbtab);
            if (root->child->sem_type.stipo != root->child->brother->sem_type.stipo)
            {
                fprintf(stderr, "ERRORE: CONDIZIONE RELAZIONALE ERRATA\n");
                exit(-1);
            }
            root->sem_type.stipo = S_BOOLEAN_;

            break;

        case N_MATH_EXPR:
            analizza(root->child, symbtab);
            analizza(root->child->brother, symbtab);
            if (root->child->sem_type.stipo != root->child->brother->sem_type.stipo)
            {
                fprintf(stderr, "ERRORE: OPERAZIONE TRA TIPI DIFFERENTI\n");
                exit(-1);
            }

            if (root->child->sem_type.stipo != S_INTEGER && root->child->sem_type.stipo != S_REAL)
            {
                fprintf(stderr, "ERRORE: TIPO NON CONFORME ALL'ESPRESSIONE\n");
                exit(-1);
            }

            root->sem_type = root->child->sem_type;
            break;

        case N_NEG_EXPR:

            analizza(root->child, symbtab);
            if (root->op_code == T_MINUS && root->child->sem_type.stipo == S_BOOLEAN_)
            {

                fprintf(stderr, "ERRORE: OPERATORE DI SOTTRAZIONE NON USATO CORRETTAMENTE\n");
                exit(-1);
            }
            else if (root->op_code == T_NOT && root->child->sem_type.stipo != S_BOOLEAN_)
            {

                fprintf(stderr, "ERRORE: OPERATORE DI NEGAZIONE NON USATO CORRETTAMENTE\n");
                exit(-1);
            }

            root->sem_type = root->child->sem_type;

            break;

        case N_LHS:

            analizza(root->child, symbtab);
            if (root->child->type == T_ID)
            {
                bc_6 = find_index_in_env(root->child->value.sval, symbtab);

                if (bc_6->classe == FUN)
                {
                    fprintf(stderr, "ERRORE: NON E' POSSIBILE INDICIZZARE UNA FUNZIONE\n");
                    exit(-1);
                }
                /* code */
            }

            //tecnicamente potrei fare questo controllo con N_TVECTOR prima di arrivare qua
            if (root->child->sem_type.sub_type->stipo == S_VOID_)
            {
                fprintf(stderr, "ERRORE: NON E' POSSIBILE CREARE VETTORI DI TIPO VOID\n");
                exit(-1);
            }

            if (root->child->sem_type.stipo == S_VECTOR && root->child->brother->sem_type.stipo == S_INTEGER)
            {
                root->sem_type = *(root->child->sem_type.sub_type);
            }

            break;

        //TODO: fare TYPE INFERENCE e checking che siano tutte expr dello stesso bucket_type
        case N_VEC_CONSTR:

            if (root->child != NULL)
            {
                n_expr = conta_fratelli(root->child->child);
            }

            struct symb_type expr_type;
            if (n_expr > 0)
            {
                Pnode iter_expr = root->child->child;
                analizza(iter_expr,symbtab);
                expr_type = root->child->child->sem_type;
                for (int i = 0; i < n_expr; i++)
                {
                    /* code */
                    analizza(iter_expr,symbtab); //FIXME: magari non ripetere
                    if (!compare_types(iter_expr->sem_type, expr_type))
                    {
                        fprintf(stderr, "ERRORE: VETTORE NON PROPRIAMENTE COSTRUITO\n");
                        exit(-1);
                    }
                    iter_expr = iter_expr->brother;
                }
                root->sem_type = (struct symb_type){S_VECTOR, n_expr, &expr_type};
            }
            else
            {
                root->sem_type = (struct symb_type){S_VECTOR, 0, NULL};
            }

            break;

            /*case N_TVECTOR: //TODO: verificare se serve veramente per analisi semantica
            break;*/

        case N_FUNC_CALL:
            bc_3 = find_in_chain(root->child->value.sval, &symbol_table[hash(root->child->value.sval)]);

            if (bc_3->classe != FUN)
            {
                fprintf(stderr, "ERRORE: FUNZIONE NON ESISTENTE\n");
                exit(-1);
            }

            int n = 0;
            if (root->child->brother != NULL)
            {
                n = conta_fratelli(root->child->brother->child);
            }

            if (n != bc_3->formali.num)
            {
                fprintf(stderr, "ERRORE: IL NUMERO DI PARAMETRI E' ERRATO\n");
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
                    fprintf(stderr, "ERRORE: TIPI DI DATI NON COMPATIBILI\n");
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
                fprintf(stderr, "ERRORE: CONDIZIONE ERRATA\n");
                exit(-1);
            }

            analizza(root->child->brother, symbtab);
            analizza(root->child->brother->brother, symbtab);
            if (root->child->brother->sem_type.stipo != root->child->brother->brother->sem_type.stipo)
            {
                fprintf(stderr, "ERRORE: CONDIZIONE ERRATA\n");
                exit(-1);
            }

            root->sem_type = root->child->brother->sem_type;

            break;

        case N_CASTING:
            analizza(root->child, symbtab);
            if (root->child->sem_type.stipo != S_INTEGER && root->child->sem_type.stipo != S_REAL)
            {
                /* code */
                fprintf(stderr, "ERRORE: CASTING ERRATO\n");
                exit(-1);
            }
            if (root->child->sem_type.stipo == S_INTEGER && root->op_code == T_INTEGER)
            {
                fprintf(stderr, "ERRORE: CASTING SUPERFLUO\n");
                exit(-1);
            }
            if (root->child->sem_type.stipo == S_REAL && root->op_code == T_REAL)
            {
                fprintf(stderr, "ERRORE: CASTING SUPERFLUO\n");
                exit(-1);
            }
            root->sem_type.stipo = root->op_code == T_INTEGER ? S_INTEGER : S_REAL;
            break;

        case N_ASSIGN_STAT: //FIXME: change for lhs

            analizza(root->child, symbtab);
            analizza(root->child->brother, symbtab);
            //FIXME: Usare magari compare_types
            if (root->child->sem_type.stipo != root->child->brother->sem_type.stipo) //TODO: POsso assegnare vettori interni?
            {
                fprintf(stderr, "ERRORE: ASSEGNAMENTO NON CONSENTITO (TIPI DIFFERENTI)\n");
                exit(-1);
            }

            break;

        case N_IF_STAT:

            analizza(root->child, symbtab);
            if (root->child->sem_type.stipo != S_BOOLEAN_)
            {
                fprintf(stderr, "ERRORE: IF NON CORRETTO\n");
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
                fprintf(stderr, "ERRORE: WHILE NON CORRETTO\n");
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
                fprintf(stderr, "ERRORE: NON E' POSSIBILE UTILIZZARE UNA FUNZIONE COME INDICE\n");
                exit(-1);
            }

            analizza(root->child, symbtab);

            if (root->child->sem_type.stipo != S_INTEGER)
            {
                fprintf(stderr, "ERRORE: INDICE DEL CICLO DEVE ESSERE INTERO \n");
                exit(-1);
            }

            analizza(root->child->brother, symbtab);
            analizza(root->child->brother->brother, symbtab);

            if (root->child->brother->sem_type.stipo != S_INTEGER || root->child->brother->brother->sem_type.stipo != S_INTEGER)
            {
                fprintf(stderr, "ERRORE: TIPO DELL' ESPRESSIONE DEV'ESSERE INTERO\n");
                exit(-1);
            }
            find_index_in_statlist(root->child->value.sval, root->child->brother->brother->brother->child);
            analizza(root->child->brother->brother->brother, symbtab);
            is_loop--;
            break;

        case N_RETURN_STAT:
            if (root->child == NULL)
            {
                root->sem_type.stipo = S_VOID_; //TODO: Check for SIGSEV
            }
            else
            {
                analizza(root->child, symbtab);
                root->sem_type = root->child->sem_type;
            }

            if (return_type.stipo != root->sem_type.stipo)
            {
                fprintf(stderr, "ERRORE:RETURN NON CORRETTO\n");
                exit(-1);
            }
            break;

        case N_READ_STAT:
            analizza(root->child, symbtab);
            Pnode temp_node_1 = root->child;
            while (temp_node_1->brother != NULL)
            {
                analizza(temp_node_1->brother, symbtab);
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
                    return_type.stipo = S_VOID_; //TODO: CHECK FOR SIGSEV
                }
            }
            break;
        }
    }
}
