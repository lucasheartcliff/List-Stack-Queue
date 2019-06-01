#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TAM 10

typedef struct element{
    struct element *back;
    int value;
    struct element *next;
}element;

typedef struct{
    element *header;
    element *object;
    element *footer;

    int lenght;
}list;

list* new_list(void){
    list *ls = (list *) malloc(sizeof(list));
    ls->header = (element*) malloc(sizeof(element));
    ls->footer = (element*) malloc(sizeof(element));
    

    if(ls == NULL || ls->header == NULL || ls->footer == NULL ){
        printf("Memória Cheia");
        return NULL;
    }else{
        /*Definindo o valor padrão de criação*/
        ls->lenght = 0;

        /*Criando uma Lista*/
        ls->header->next = NULL;
        ls->footer->next = NULL;

        ls->header->back = NULL;
        ls->footer->back = NULL;
        
        return ls;
    }
}

int get_space(list *ls){
    if(ls->lenght == 0){
        ls->object = (element*) malloc(sizeof(element));
    }else{
        ls->object = (element*) realloc(ls->object, (ls->lenght + 1) * sizeof(element) );
    }

    if(ls->object == NULL){
        printf("Memória cheia");
        return 0;
    }else{
        return 1;
    }
}

void push(list *ls,int value){
    if( get_space(ls) ){
        if(ls->lenght == 0){
            ls->object[0].value = value;

            ls->object[0].next = &ls->footer[0];
            ls->object[0].back = &ls->header[0];

            ls->header->next = &ls->object[0];
            ls->footer->back = &ls->object[0];
        }else{
            ls->object[ ls->lenght ].next = &ls->footer[0];
            ls->object[ ls->lenght ].back = &ls->footer->back[0];

            ls->object[ ls->lenght ].value = value;

            ls->footer->back = &ls->object[ ls->lenght ];
        }
        ls->lenght++;
    }
}

void unshift(list *ls,int value){
    if( get_space(ls) ){
        if(ls->lenght == 0){
            ls->object[0].value = value;

            ls->object[0].next = &ls->footer[0];
            ls->object[0].back = &ls->header[0];

            ls->header->next = &ls->object[0];
            ls->footer->back = &ls->object[0];
        }else{
             ls->object[ ls->lenght ].back = &ls->header[0];
             ls->object[ ls->lenght ].next = &ls->header->next[0];

            ls->object[ ls->lenght ].value = value;

            ls->header->next = &ls->object[ ls->lenght ]; 
        }
        ls->lenght++;
    }
}

void echoArray(list *ls){
    element *pl;
    int i=0;

    for(pl = ls->header->next ; pl!= ls->footer; pl = pl->next){
        i++;
        printf("Posição - %i | Valor - %i\n",i , pl->value);
    }
}

int main(){
    int i=0;
    list *ls;
    ls = new_list();
    for(i=0;i<10;i++){
        unshift(ls,i);
        //printf("%i\n",ls->object[i].value);
    }
    push(ls,17);

    echoArray(ls);
    return 0;
}
