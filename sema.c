#include <stdlib.h>
#include "string.h"
#include "def.h"

extern struct bucket *symbol_table;
symb_type return_type = S_VOID_;
int is_loop = 0;

void find_index_in_statlist(char *id, Pnode node)
{
    
    switch (node->value.ival)
    {
    case N_ASSIGN_STAT:
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

int conta_fratelli(Pnode fratello, int contatore)
{
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

    nodo_id->sem_type = bc_1->tipo;
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

void analizza(Pnode root, struct bucket symbtab[])
{
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
            if (root->child->sem_type != S_BOOLEAN_ || root->child->brother->sem_type != S_BOOLEAN_)
            {
                fprintf(stderr, "ERRORE: OPERATORE RELAZIONALE ERRATO\n");
                exit(-1);
            }

            root->sem_type = S_BOOLEAN_;

            break;

        case N_REL_EXPR:
            analizza(root->child, symbtab);
            analizza(root->child->brother, symbtab);
            if (root->child->sem_type != root->child->brother->sem_type)
            {
                fprintf(stderr, "ERRORE: CONDIZIONE RELAZIONALE ERRATA\n");
                exit(-1);
            }
            root->sem_type = S_BOOLEAN_;

            break;

        case N_MATH_EXPR:
            analizza(root->child, symbtab);
            analizza(root->child->brother, symbtab);
            if (root->child->sem_type != root->child->brother->sem_type)
            {
                fprintf(stderr, "ERRORE: OPERAZIONE TRA TIPI DIFFERENTI\n");
                exit(-1);
            }

            if (root->child->sem_type != S_INTEGER && root->child->sem_type != S_REAL)
            {
                fprintf(stderr, "ERRORE: TIPO NON CONFORME ALL'ESPRESSIONE\n");
                exit(-1);
            }

            root->sem_type = root->child->sem_type;
            break;

        case N_NEG_EXPR:

            analizza(root->child, symbtab);
            if (root->op_code == T_MINUS && root->child->sem_type == S_BOOLEAN_)
            {

                fprintf(stderr, "ERRORE: OPERATORE DI SOTTRAZIONE NON USATO CORRETTAMENTE\n");
                exit(-1);
            }
            else if (root->op_code == T_NOT && root->child->sem_type != S_BOOLEAN_)
            {

                fprintf(stderr, "ERRORE: OPERATORE DI NEGAZIONE NON USATO CORRETTAMENTE\n");
                exit(-1);
            }

            root->sem_type = root->child->sem_type;

            break;

        case N_FUNC_CALL:
            bc_3 = find_in_chain(root->child->value.sval, &symbol_table[hash(root->child->value.sval)]);

            if (bc_3->classe != FUN)
            {
                fprintf(stderr, "ERRORE: FUNZIONE NON ESISTENTE\n");
                exit(-1);
            }

            int cont = 0;
            int n = 0;
            if (root->child->brother != NULL)
            {
                n = conta_fratelli(root->child->brother->child, cont);
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
                if (bc_3->formali.descr[i]->tipo != temp_node->sem_type)
                {
                    fprintf(stderr, "ERRORE: TIPI DI DATI NON COMPATIBILI\n");
                    exit(-1);
                }

                if (temp_node->brother != NULL)
                    temp_node = temp_node->brother;
            }
            root->sem_type = bc_3->tipo;
            break;

        case N_COND_EXPR:
            analizza(root->child, symbtab);
            if (root->child->sem_type != S_BOOLEAN_)
            {
                fprintf(stderr, "ERRORE: CONDIZIONE ERRATA\n");
                exit(-1);
            }

            analizza(root->child->brother, symbtab);
            analizza(root->child->brother->brother, symbtab);
            if (root->child->brother->sem_type != root->child->brother->brother->sem_type)
            {
                fprintf(stderr, "ERRORE: CONDIZIONE ERRATA\n");
                exit(-1);
            }

            root->sem_type = root->child->brother->sem_type;

            break;

        case N_CASTING:
            analizza(root->child, symbtab);
            if (root->child->sem_type != S_INTEGER && root->child->sem_type != S_REAL)
            {
                /* code */
                fprintf(stderr, "ERRORE: CASTING ERRATO\n");
                exit(-1);
            }

            root->sem_type = root->op_code == T_INTEGER ? S_INTEGER : S_REAL;
            break;

        case N_ASSIGN_STAT:

            bc_2 = find_index_in_env(root->child->value.sval, symbtab);

            if (bc_2->classe == FUN)
            {
                fprintf(stderr, "ERRORE: NON E' POSSIBILE ASSEGNARE UNA FUNZIONE\n");
                exit(-1);
            }

            analizza(root->child, symbtab);
            analizza(root->child->brother, symbtab);
            if (root->child->sem_type != root->child->brother->sem_type)
            {
                fprintf(stderr, "ERRORE: ASSEGNAMENTO NON CONSENTITO (TIPI DIFFERENTI)\n");
                exit(-1);
            }

            break;


        case N_IF_STAT:

            analizza(root->child, symbtab);
            if (root->child->sem_type != S_BOOLEAN_)
            {
                fprintf(stderr, "ERRORE: IF NON CORRETTO\n");
                exit(-1);
            }
            analizza(root->child->brother->child, symbtab);


            if (root->child->brother->brother != NULL)
            {
                /* code */
                analizza(root->child->brother->brother->child, symbtab);
            }

            break;

        case N_WHILE_STAT:
            is_loop++;
            analizza(root->child, symbtab);
            if (root->child->sem_type != S_BOOLEAN_)
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

            if (root->child->sem_type != S_INTEGER)
            {
                fprintf(stderr, "ERRORE: INDICE DEL CICLO DEVE ESSERE INTERO \n");
                exit(-1);
            }

            analizza(root->child->brother, symbtab);
            analizza(root->child->brother->brother, symbtab);

            if (root->child->brother->sem_type != S_INTEGER || root->child->brother->brother->sem_type != S_INTEGER)
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
                root->sem_type = S_VOID_;
            }
            else
            {
                analizza(root->child, symbtab);
                root->sem_type = root->child->sem_type;
            }

            if (return_type != root->sem_type)
            {
                fprintf(stderr, "RETURN NON CORRETTO\n");
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
                return_type = bc_5->tipo;
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
                    return_type = S_VOID_;

                }
                
            }
            break;
        }
    }
}
