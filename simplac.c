#include "def.h"
#include <string.h>

int main(int argc, char **argv)
{
  symbol_table = init_symbol_table(SYMTAB_SIZE);
  temp_env = init_symbol_table(SYMTAB_SIZE);
  temp_descr = (struct bucket **)malloc(25 * sizeof(struct bucket *));
  current_env = symbol_table; 
  id_func = (char *)malloc(140);
  current_oid = &oid_g;
  sub_prog10 = (struct SCode *)malloc(sizeof(struct SCode));
  tot_prog = (struct SCode *)malloc(sizeof(struct SCode));
  current_prog = (struct SCode *)malloc(sizeof(struct SCode));
  int result;

  for (int i = 0; i < SYMTAB_SIZE; i++)
  {
    lista_id[i] = (char * )malloc(140);
  }

  if (argc >= 2) {
    if ((yyin = fopen(argv[1], "r")) == NULL){
       fprintf(stderr,"ERRORE SIMPLAC: FILE NON ESISTE!");
       // Program exits if the file pointer returns NULL.
       exit(-1);
   }
  }
  else {
      fprintf(stderr,"ERRORE SIMPLAC: INDICARE FILE DA COMPILARE");
       // Program exits if the file pointer returns NULL.
       exit(-1);
  }
    

  if ((result = yyparse()) == 0) {
    //Togliere commento sulla funzione treeprint per visualizzare l'albero sintattico astratto a video
    //treeprint(root, 0);

    //print_symbol_table(symbol_table);
    
    analizza(root, symbol_table);
    
    *sub_prog10 = endcode();
    generateCode(root, symbol_table, sub_prog10);
    int size;
    size = sub_prog10->num;

    *tot_prog = appcode(makecode1(SIZ,size), make_psh_pop(0, count_var(symbol_table), get_func_entry_point(sub_prog10,"smain")));
    *tot_prog = appcode(*tot_prog, makecode(STP));
    *tot_prog = appcode(*tot_prog,*sub_prog10);

    printf("---- Compilazione di Codice SimpLA avvenuta con successo -----\n");
    //Togliere commento sulla funzione codeprint per visualizzare il codice intermedio SCode a video
    //codeprint(tot_prog);

    char *s_filename = strcat(argv[1],".sim");
    save_to_txt(tot_prog, s_filename);

    //printf("---- Test Code: -----\n");
    //get_scode_from_file(s_filename);

    //executeSCode(s_filename);
  }
  
  return(result);
}