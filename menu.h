/**
#Universidade Federal de Pelotas#
#Unidade: CDTEC
#Curso: Ciência da computação
#Disciplina: Algoritmos e Estruturas de Dados I
#Prof°: Raphael Peccin Torchelsen
#Aluno: Maicon de Menezes
#Projeto:Agenda com aritmética de ponteiros
#Módulo: menu
#Descrição:
**/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int *amountOfContacts;
int *sizeOfMemory ;


void header(int *amountOfContacts, int *sizeOfMemory){
    system("cls");
    printf("|===================================[Agenda]==================================|\n");
    printf("|===================[Contatos: %03d | Memoria: %06dBytes]====================|\n", *amountOfContacts, *sizeOfMemory);
}
void footer(){
	printf("|===========[developed by: @maicondmenezes | version 0.1 | dez/17]============|\n");
}
void mainMenu(int *amountOfContacts, int *sizeOfMemory){
	header(amountOfContacts, sizeOfMemory);
	printf("| 1-Novo contato\n");
	printf("| 2-Listar contatos\n");
	printf("| 3-Ordenar contatos\n");
	printf("| 4-Excluir contato\n");
	printf("| 5-Sair\n");
	footer();
	printf("Selecione uma das opcoes: ");
}
