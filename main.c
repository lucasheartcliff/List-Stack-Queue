#include <stdio.h>
#include <stdlib.h>

/*Estrutura do Conteúdo do Array*/
typedef struct element{
    struct element *back;
    int value;
    struct element *next;
}element;

/*Estrutura do Array*/
typedef struct{
    element *object;
    int lenght;
}list;

/*New_list() inicializa uma nova lista*/
list* new_list(void){
    list *ls = (list *) malloc(sizeof(list));

    if(ls == NULL){
        printf("Memória Cheia");
        return NULL;
    }else{
        /*Definindo o valor padrão de criação*/
        ls->lenght = 0;
        return ls;
    }
}

/*Get_space()  os valore no fim da lista*/
int get_space(list *ls){
    if(ls->lenght == 0){
        ls->object = (element*) malloc(2 *sizeof(element)); //Malloc usado para criar o 1° elemento da lista e o Cabeçalho
        ls->lenght += 1;
    }else{
        ls->object = (element*) realloc(ls->object, (ls->lenght + 1) * sizeof(element) ); //Realloc usado para aumentar o tamanho da lista
    }

    if(ls->object == NULL){
        printf("Memória cheia");
        free(ls->object);
        return 0;
    }else{
        return 1;
    }
}
/*Push() insere os valore no fim da lista*/
void push(list *ls,int value){
    if( get_space(ls) ){
        if(ls->lenght == 1){
            ls->object[0].back = &ls->object[1]; //Definindo endereço do objeto anterior no cabeçalho
            ls->object[0].next = &ls->object[1]; //Definindo endereço do objeto seguinte no cabeçalho
            
            ls->object[1].value = value; //Definindo valor do 1° Item
            ls->object[1].next = &ls->object[0]; //Definindo endereço do objeto seguinte
            ls->object[1].back = &ls->object[0]; //Definindo endereço do objeto anterior
        }else{
            /*Colocando os endereços do próximo e do anterior no objeto criado*/
            ls->object[ ls->lenght ].next = &ls->object[0];
            ls->object[ ls->lenght ].back = ls->object[0].back;

            ls->object[ ls->lenght ].value = value;//Colocando o valor do parâmetro no elemento

            /*Atualizando o endereço do novo objeto nos elementos: Anterior e Próximo*/
            ls->object[0].back->next = &ls->object[ ls->lenght ];
            ls->object[0].back = &ls->object[ ls->lenght ];
        }
        ls->lenght++; //Incrementa + 1 no tamanho do lista
    }
}

/*Unshift() insere os valore no inicio da lista*/
void unshift(list *ls,int value){
    if( get_space(ls) ){
        if(ls->lenght == 1){
            ls->object[0].back = &ls->object[1]; //Definindo endereço do objeto anterior no cabeçalho
            ls->object[0].next = &ls->object[1]; //Definindo endereço do objeto seguinte no cabeçalho
            
            ls->object[1].value = value; //Definindo valor do 1° Item
            ls->object[1].next = &ls->object[0]; //Definindo endereço do objeto seguinte
            ls->object[1].back = &ls->object[0]; //Definindo endereço do objeto anterior
        }else{
            /*Colocando os endereços do próximo e do anterior no objeto criado*/
            ls->object[ ls->lenght ].next = ls->object[0].next;
            ls->object[ ls->lenght ].back = &ls->object[0];

            ls->object[ ls->lenght ].value = value; //Colocando o valor do parâmetro no elemento

            /*Atualizando o endereço do novo objeto nos elementos: Anterior e Próximo*/
            ls->object[0].next->back = &ls->object[ ls->lenght ];
            ls->object[0].next = &ls->object[ ls->lenght ];
        }
        ls->lenght++;
    }
}

void pop(list *ls){
    if(ls->lenght > 1){
        element *this = ls->object[0].back; //Armazena o endereço do ultimo elemento da lista

        ls->object[0].back = ls->object[0].back->back; //Altera o endereço 
        ls->object[0].back-> = &ls->object[0];

        free(this);
        ls->lenght--;
    }
}

/*Exibe o Array (lista, pilha, fila e etc)*/
void echoArray(list *ls, int flow){ // O Parâmetro "Flow" é usado para definir o fuxo da exibiçao 
    element *pl;
    int i=0;

    if(!flow){
        /*Exibir os valores partindo do início ao fim - Se o Flow for igual à 0*/
        for(pl = ls->object[0].next ; pl!= &ls->object[0] && (ls->lenght - 2) >= i; pl = pl->next){
            i++;
            printf("Posição - %i | Valor - %i\n",i , pl->value);
        }
    }else{
        /*Exibir os valores partindo do fim ao início - Se o Flow for igual à 1*/
        for(pl = ls->object[0].back ; pl!= &ls->object[0] && (ls->lenght - 2) >= i; pl = pl->back){
            i++;
            printf("Posição - %i | Valor - %i\n",i , pl->value);
        }
    }
}

int main(){
    int i;
    list *ls = new_list();
    for(i=0;i<10;i++){
        push(ls,i);
    }
    for(int j=10; j<20;j++){
        unshift(ls,j);
    }
    echoArray(ls,0);
    return 0;
}
