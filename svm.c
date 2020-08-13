//
// Created by Parampal on 10/08/2020.
//
#include "def.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void save_to_file(struct SCode *prog, char *filename) {
    FILE *fptr;
    fptr = fopen(filename, "wb");

    int num_stat = prog->num;
    printf("Dimensione programma prog: %d\n", num_stat);
    fwrite(&num_stat, sizeof(int), 1, fptr);

    struct Stat *save_stat = prog->first;
    for (int i = 0; i < num_stat; i++)
    {
        fwrite(save_stat, sizeof(struct Stat), 1, fptr);
        save_stat = save_stat->next;
    }

    fclose(fptr);
}

void save_to_txt(struct SCode *prog, char *filename) {
    FILE *fptr;
    fptr = fopen(filename, "w");

    int num_stat = prog->num;
    printf("Dimensione programma prog: %d\n", num_stat);
    fprintf(fptr,"%d\n", num_stat);

    struct Stat *save_stat = prog->first;
    for (int i = 0; i < num_stat; i++)
    {
        fprintf(fptr,"%d %s\n",save_stat->op, save_args(*save_stat));
        save_stat = save_stat->next;
    }

    fclose(fptr);
}

char *save_args(struct Stat stat) {
    char * str_args = (char*)malloc(512*sizeof(char));

    switch (stat.op)
    {
        case VARI:
            sprintf(str_args, "%d",stat.args[0].ival);
            break;

        case LCI:
            sprintf(str_args, "%d",stat.args[0].ival);
            break;

        case LCR:
            sprintf(str_args, "%f",stat.args[0].fval);
            break;

        case LCS:
            //printf("Inizio LCS\n");
            sprintf(str_args, "%s",stat.args[0].sval);
            break;

        case LOD:
            sprintf(str_args, "%d %d",stat.args[0].ival, stat.args[1].ival);
            break;

        case STO:
            sprintf(str_args, "%d %d",stat.args[0].ival, stat.args[1].ival);
            break;

        case JMF:
            sprintf(str_args, "%d",stat.args[0].ival);
            break;

        case JMP:
            sprintf(str_args, "%d",stat.args[0].ival);
            break;

        case PSH:
            sprintf(str_args, "%d %d",stat.args[0].ival, stat.args[1].ival);
            break;

        case GOT:
            sprintf(str_args, "%d",stat.args[0].ival);
            break;

        case INP:
            sprintf(str_args, "%s %d %d",stat.args[0].sval, stat.args[1].ival, stat.args[2].ival);
            break;

        case OUT:
            sprintf(str_args, "%d %s",stat.args[0].ival, stat.args[1].sval);
            break;

        case ENT:
            sprintf(str_args, "%d",stat.args[0].ival);
            break;

        case INC:
            sprintf(str_args, "%d %d",stat.args[0].ival, stat.args[1].ival);
            break;

        case RET:
            sprintf(str_args, "%d",stat.args[0].ival);
            break;

        case SIZ:
            sprintf(str_args,"%d",stat.args[0].ival);
            break;

        default: sprintf(str_args,"%s","");
            break;
    }
    return str_args;
}

struct Stat *get_scode_from_txt(char *filename)
{
    FILE *fptr;
    if ((fptr = fopen(filename, "r")) == NULL)
    {
        fprintf(stderr,"ERRORE SIMPLAVM: FILE NON ESISTE!");
        // Program exits if the file pointer returns NULL.
        exit(-1);
    }
    int prog_len;
    fscanf(fptr,"%d\n", &prog_len);
    //printf("DIM PROG: %d\n", prog_len);

    char *str_args = malloc(sizeof(char) * 512);
    struct Stat *code_mem = (struct Stat *)calloc(prog_len, sizeof(struct Stat));

    for (int i = 0; i < prog_len; i++) {
        fscanf(fptr,"%d",&code_mem[i].op);
        get_args_from_str(&code_mem[i],fgets(str_args,512,fptr));
    }

    /*for (int i = 0; i < prog_len; i++) {
        printf("OP: %s \n",print_args(code_mem[i]));
    }*/

    fclose(fptr);



    return code_mem;
}

void get_args_from_str(struct Stat *stat, char *str_args) {
    //printf("ARGS: %s\n", str_args);
    switch (stat->op)
    {
        case VARI:
            sscanf(str_args,"%d",&stat->args[0].ival);
            break;

        case LCI:
            sscanf(str_args,"%d",&stat->args[0].ival);
            break;

        case LCR:
            sscanf(str_args,"%f",&stat->args[0].fval);
            break;

        case LCS:
            //printf("stringa param: %s\n",str_args);
            stat->args[0].sval = malloc(sizeof(char) * (strlen(str_args) - 1));

            int j = 0;
            for (int i = 1; i < strlen(str_args) - 1; i++) {
                stat->args[0].sval[j] = str_args[i];
                j++;
            }
            //strcpy(stat->args[0].sval,str_args);
            break;

        case LOD:
            sscanf(str_args,"%d %d",&stat->args[0].ival,&stat->args[1].ival);
            break;

        case STO:
            sscanf(str_args,"%d %d",&stat->args[0].ival,&stat->args[1].ival);
            break;

        case JMF:
            sscanf(str_args,"%d",&stat->args[0].ival);
            break;

        case JMP:
            sscanf(str_args,"%d",&stat->args[0].ival);
            break;

        case PSH:
            sscanf(str_args,"%d %d",&stat->args[0].ival,&stat->args[1].ival);
            break;

        case GOT:
            sscanf(str_args,"%d",&stat->args[0].ival);
            break;

        case INP:
            stat->args[0].sval = malloc(sizeof(char) * 128);
            sscanf(str_args,"%s %d %d",stat->args[0].sval,&stat->args[1].ival,&stat->args[2].ival);
            //printf("%s\n",stat->args[0].sval);
            break;

        case OUT:
            //printf("stringa param: %s\n",str_args);
            stat->args[1].sval = malloc(sizeof(char) * 128);
            sscanf(str_args,"%d %s",&stat->args[0].ival,stat->args[1].sval);
            //printf("%s\n",stat->args[1].sval);
            break;

        case ENT:
            sscanf(str_args,"%d",&stat->args[0].ival);
            break;

        case INC:
            sscanf(str_args,"%d %d",&stat->args[0].ival,&stat->args[1].ival);
            break;

        case RET:
            sscanf(str_args,"%d",&stat->args[0].ival);
            break;

        case SIZ:
            sscanf(str_args,"%d",&stat->args[0].ival);
            break;

        default:
            break;
    }
}

struct Stat *get_scode_from_file(char *filename)
{
    FILE *fptr;
    //struct SCode int_scode = endcode();

    if ((fptr = fopen(filename, "rb")) == NULL)
    {
        fprintf(stderr,"ERRORE SIMPLAVM: FILE NON ESISTE!");
        // Program exits if the file pointer returns NULL.
        exit(-1);
    }
    int prog_len;
    fread(&prog_len, sizeof(int), 1, fptr);
    //printf("Prog _len : %d\n",prog_len);

    struct Stat *code_mem = (struct Stat *)calloc(prog_len, sizeof(struct Stat));

    for (int i = 0; i < prog_len; i++) {
        fread(&code_mem[i],sizeof(struct Stat), 1, fptr);
    }

    fclose(fptr);

    /*for (int i = 0; i < prog_len; i++) {
        printf("OP: %s \n",print_args(code_mem[i]));
    }*/
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
    return code_mem;
}