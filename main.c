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
}array;

void clear(void){
    system("cls");
}

/*New_array() inicializa uma nova array*/
array* new_array(void){
    array *arr = (array *) malloc(sizeof(array));

    if(arr == NULL){
        printf("Memória Cheia");
        return NULL;
    }else{
        /*Definindo o valor padrão de criação*/
        arr->lenght = 0;
        return arr;
    }
}

/*Get_space()  os valore no fim da array*/
int get_space(array *arr){
    if(arr->lenght == 0){
        arr->object = (element*) malloc(2 *sizeof(element)); //Malloc usado para criar o 1° elemento da array e o Cabeçalho
        arr->lenght += 1;
    }else{
        arr->object = (element*) realloc(arr->object, (arr->lenght + 1) * sizeof(element) ); //Realloc usado para aumentar o tamanho da array
    }

    if(arr->object == NULL){
        printf("Memória cheia");
        free(arr->object);
        return 0;
    }else{
        return 1;
    }
}
/*Push() insere os valore no fim da array*/
void push(array *arr,int value){
    if( get_space(arr) ){
        if(arr->lenght == 1){
            arr->object[0].back = &arr->object[1]; //Definindo endereço do objeto anterior no cabeçalho
            arr->object[0].next = &arr->object[1]; //Definindo endereço do objeto seguinte no cabeçalho
            
            arr->object[1].value = value; //Definindo valor do 1° Item
            arr->object[1].next = &arr->object[0]; //Definindo endereço do objeto seguinte
            arr->object[1].back = &arr->object[0]; //Definindo endereço do objeto anterior
        }else{
            /*Colocando os endereços do próximo e do anterior no objeto criado*/
            arr->object[ arr->lenght ].next = &arr->object[0];
            arr->object[ arr->lenght ].back = arr->object[0].back;

            arr->object[ arr->lenght ].value = value; //Colocando o valor do parâmetro no elemento

            /*Atualizando o endereço do novo objeto nos elementos: Anterior e Próximo*/
            arr->object[0].back->next = &arr->object[ arr->lenght ];
            arr->object[0].back = &arr->object[ arr->lenght ];
        }
        arr->lenght++; //Incrementa + 1 no tamanho do array
    }
}

/*Unshift() insere os valore no inicio da array*/
void unshift(array *arr,int value){
    if( get_space(arr) ){
        if(arr->lenght == 1){
            arr->object[0].back = &arr->object[1]; //Definindo endereço do objeto anterior no cabeçalho
            arr->object[0].next = &arr->object[1]; //Definindo endereço do objeto seguinte no cabeçalho
            
            arr->object[1].value = value; //Definindo valor do 1° Item
            arr->object[1].next = &arr->object[0]; //Definindo endereço do objeto seguinte
            arr->object[1].back = &arr->object[0]; //Definindo endereço do objeto anterior
        }else{
            /*Colocando os endereços do próximo e do anterior no objeto criado*/
            arr->object[ arr->lenght ].next = arr->object[0].next;
            arr->object[ arr->lenght ].back = &arr->object[0];

            arr->object[ arr->lenght ].value = value; //Colocando o valor do parâmetro no elemento

            /*Atualizando o endereço do novo objeto nos elementos: Anterior e Próximo*/
            arr->object[0].next->back = &arr->object[ arr->lenght ];
            arr->object[0].next = &arr->object[ arr->lenght ];
        }
        arr->lenght++;
    }
}

/*Pop() Remove o ultimo objeto e retorna o seu valor*/
int pop(array *arr){
    if(arr->lenght > 1){
        element *object = arr->object[0].back; //Armazena o endereço do ultimo objeto da array
        int value = arr->object[0].back->value; //Armazena valor do ultimo objeto da array

        arr->object[0].back = arr->object[0].back->back; //Altera o endereço do cabeçalho/rodapé para o penúltimo objeto do array
        arr->object[0].back->next = &arr->object[0]; //Altera o endereço do penúltimo objeto para o cabeçalho/rodapé do array

        free(object); //Libera a ultima posição

        arr->lenght--; //Decrementa 1 na quantidade

        return value;
    }else{
        return NULL;
    }
}

/*Shift() Remove o ultimo objeto e retorna o seu valor*/
int shift(array *arr){
    if(arr->lenght > 1){
        element *object = arr->object[0].next; //Armazena o endereço do ultimo objeto da array
        int value = arr->object[0].next->value; //Armazena valor do ultimo objeto da array

        arr->object[0].next = arr->object[0].next->next; //Altera o endereço do cabeçalho/rodapé para o penúltimo objeto do array
        arr->object[0].next->back = &arr->object[0]; //Altera o endereço do penúltimo objeto para o cabeçalho/rodapé do array

        free(object); //Libera a ultima posição

        arr->lenght--; //Decrementa 1 na quantidade

        return value;
    }else{
        return NULL;
    }
}

/*findIndex() Busca no array a posiçao do 1° valor correspondente ao passado no parâmetro*/
int findIndex(array *arr, int value){
    if(arr->lenght > 1){
        int index = 1;
        element *parr;

        for(parr = arr->object[0].next; parr != &arr->object[0] && index < (arr->lenght - 1); parr = parr->next ){
            if(value == parr->value){
                return index; //Retorna a POSIÇÂO (Indice [0] == Posição 1) do valor achado
            }
            index++;
        }
        return 0; //Se não achar retorna 0
    }else{
        return 0; //Se não houver objetos no array retorna 0
    }
}

/*find() Busca no array o 1° valor correspondente ao passado no parâmetro*/
int find(array *arr, int index){
    if(arr->lenght > 1 && arr->lenght > index ){
        int i=1;
        element *parr;

        for(parr = arr->object[0].next; parr != &arr->object[0] && i < index ; parr = parr->next ){
            i++;
        }
        return parr->value; //Retorna valor achado na posiçao
    }
    return NULL; //Se não houver objetos no array retorna 0
}

/*Exibe o Array (array, pilha, fila e etc)*/
void echoArray(array *arr, int flow){ //O parâmetro "Flow" é usado para definir o fuxo da exibição 
    element *parr;
    int i=0;

    if(!flow){
        /*Exibir os valores partindo do início ao fim - Se o Flow for igual à 0*/
        for(parr = arr->object[0].next ; parr!= &arr->object[0] && i < (arr->lenght - 1); parr = parr->next){
            i++;
            printf("Posição - %i | Valor - %i\n",i , parr->value);
        }
    }else{
        /*Exibir os valores partindo do fim ao início - Se o Flow for igual à 1*/
        for(parr = arr->object[0].back; parr!= &arr->object[0] && i < (arr->lenght - 1); parr = parr->back){
            i++;
            printf("Posição - %i | Valor - %i\n",i , parr->value);
        }
    }
}

int main(){
    int i;
    array *arr = new_array();
    /* for(i=0;i<10;i++){
        push(arr,i);
    }
    for(int j=10; j<20;j++){
        unshift(arr,j);
    } */
    push(arr,13);
    push(arr,143);
    clear();
    printf("%i\n",arr->lenght);
    printf("%i\n", find(arr,1) );
    
    echoArray(arr,0);
    return 0;
}