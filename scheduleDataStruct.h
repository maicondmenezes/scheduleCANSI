/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   scheduleDataStruct.h
 * Author: Maicon de Menezes
 *
 * Created on 1 de Fevereiro de 2018, 04:15
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define sizeOfName 30
typedef struct HEAD{
    /*Armazena a quantidade de memória total utilizada pela agenda*/
    int *sizeOfMemory;
    /*Armazena a quantidade de pessoas inseridas na agenda*/
    int *amountOfContacts;
    /*iteradores utilizados em laços de repetição*/
    int *index;
    int *index2;
    /*Flag que seleciona o tipo algoritmo utilzado para ordenar a agenda*/
    int *sortAlgoritmType;
    /*Flag que seleciona as opções de menu na interface do usuário*/
    int *menuOption;
    /*Armazena um nome a ser pesquisado na agenda*/
    char *searchingName[sizeOfName];
    /*Inicio da lista*/
    contact *firstContact;
    /*Final da fila*/
    contact *lastContact;
    /*Contato atual utilizado para itereações na lista*/
    contact *thisContact;
}list;

typedef struct contact{
    char name[sizeOfName];
    int  age;
    struct contact *previous;
    struct contact *next;    
}data;

void storeContact(struct contact *newContact){
    inputContactData(newContact);
    /*Caso o contasto inserido for o primeiro da lista é apontado para o primeiro e o último*/
    if(!list->firstContact) list->firstContact=newContact;
    if(!list->lastContact) list->lastContact=newContact;
    /*Caso contrário é inserido no fim da lista*/
    else list->lastContact->next=newContact;
    newContact->next=NULL;
    newContact->previous=list->lastContact;
    list->lastContact=newContact;   
    list->amountOfContacts=list->amountOfContacts+1;
}
/*Lista todos contatos a partir do primeiro*/
void listContacts(){
    list->index=0;
    list->thisContact=list->firstContact;
    
    while(list->thisContact){
        printf("|N:%3d|Nome:%30.30s| Idade:%3d|\n", list->index, list->thisContact->name, list->thisContact->age);
        list->thisContact=list->thisContact->next;
        list->index=list->index+1;
    }
}

/*Pesquisa um contato a partir do nome*/
struct contact *searchContact(char *searchingName[sizeOfName]){
    
    list->thisContact=list->firstContact;
    while(list->thisContact){
        if(!strcmp(searchingName, list->thisContact->name)) return list->thisContact;
        list->thisContact=list->thisContact->next;
    }
}

void deleteContact(char *searchingName[sizeOfName]){
    
    contact *deletedContact;
    deletedContact=searchContact(searchingName);
    if(deletedContact->previous) deletedContact->previous->next=deletedContact->next;
    else{
        list->firstContact=deletedContact->next;
        if(list->firstContact) list->firstContact->previous=NULL;
    }
    if(deletedContact->next) deletedContact->next->previous=deletedContact->previous;
    else list->lastContact=deletedContact->previous;
}

void inputContactData(struct contact *thisContact){
    printf("| Nome: ");
    scanf(" %[^\n]s", thisContact->name);
    printf("| Idade: ");
    scanf("%d", &thisContact->age);
}

void overwriteContact(contact *contactA, contact *contactB){
	/**<copia o nome de 'contactB' para 'contactA'*/
	strcpy(contactA->name, contactB->name);
	/**<copia a idade de 'contactB' para 'contactA''*/
	contactA->age=contactB->age;
}

void swapContact(contact *contactA, contact *contactB){
    /**<sobrescreve'temporaryContact' com os dados de 'contactA'*/
    overwriteContact(list->thisContact, contactA);
    /**<sobrescreve'contactA' com os dados de 'contactB'*/
    overwriteContact(contactA, contactB);
    /**<sobrescreve'contactB' com os dados de 'temporaryContact' que contem os valores de 'contactA' antes de ser sobreescrito*/
    overwriteContact(contactB, list->thisContact);
}