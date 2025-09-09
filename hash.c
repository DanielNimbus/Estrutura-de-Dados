#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SIZE 10

typedef struct{
    char nome[20];
} pessoa;

pessoa* hashtable[MAX_SIZE];

int hashing(char* nome){
    int hash = 0;

    for(int i = 0; i < strlen(nome); i++){
        hash += nome[i];
    }

    hash = hash % MAX_SIZE;
    return hash;
}

void inicializa_hashtable(){
    for(int i = 0; i < MAX_SIZE; i++){
        hashtable[i] = NULL;
    }
}

// com resolução de colisão em O(n)
bool inserir_na_hash(pessoa* p){
    int hash_index = hashing(p->nome);

    if(hashtable[hash_index] == NULL){
        hashtable[hash_index] = p;
        return true;
    }
    else{
        for(int i = 1; (hash_index+i)%MAX_SIZE != hash_index; i++){
            int pos = (hash_index+i)%MAX_SIZE;

            if(hashtable[pos] == NULL){
                hashtable[pos] = p;
                return true;
            }
        }
        return false;
    }
}

void deletar_na_hash(char* nome){
    int indice = hashing(nome);

    hashtable[indice] = NULL;
}

int achar_na_hash(char* nome){
    int indice_procura = hashing(nome);
    if(hashtable[indice_procura] != NULL){
        printf("Achei %s\n", nome);
        return indice_procura;
    }
    else{
        printf("Não achei %s. Sobrou nada...\n", nome);
        return -1;
    }
}

void print_hash(){
    for(int i = 0; i < MAX_SIZE; i++){
        if(hashtable[i] != NULL){
            printf("Nome: %s\n", hashtable[i]->nome);
        }
        else{
            printf("Nome: ---\n");
        }
    }
    printf("\n\n");
}


int main(){

    inicializa_hashtable(hashtable);
    pessoa dani = {.nome = "daniel"};
    pessoa eliane = {.nome = "eliane"};
    pessoa jhon = {.nome = "jhon"};
    pessoa beatriz = {.nome = "beatriz"};
    pessoa lara = {.nome = "lara"};

    inserir_na_hash(&dani);
    inserir_na_hash(&eliane);
    inserir_na_hash(&jhon);
    inserir_na_hash(&lara);
    inserir_na_hash(&beatriz);

    print_hash();

    achar_na_hash("lara");
    achar_na_hash("Steve");

    deletar_na_hash("lara");

    print_hash();
    achar_na_hash("lara");


}