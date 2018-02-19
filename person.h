/**
#Universidade Federal de Pelotas#
#Unidade: CDTEC
#Curso: Ciência da computação
#Disciplina: Algoritmos e Estruturas de Dados I
#Prof°: Raphael Peccin Torchelsen
#Aluno: Maicon de Menezes
#Projeto:Agenda com aritmética de ponteiros
#Módulo: principal
#Descrição:
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "menu.h"
/**<Gerenciamento de memória para variaveis globais*/
/**<-Definição das quantidades de memória*/
/**<--Define o tamanho do nome armazenado na agenda*/
#define sizeOfName 30
/**<--Define quantidade de memória para as variaveis do tipo 'char'*/
#define sizeOfCharVariables sizeOfName*sizeof(char)
/**<--Define quantidade de memória para as variaveis do tipo 'int'*/
#define sizeOfIntVariables (6*sizeof(int))
/**<--Define quantidade de memória total do inicio do Buffer*/
#define sizeOfpBufferHead sizeOfCharVariables+sizeOfIntVariables
/**<-Definição dos ponteiros para as variaveis globais*/
/**<--Define o ponteiro para 'sizeOfMemory' primeiro 'int' do Buffer
      sizeOfMemory-armazena a quantidade necessária para realocar a memória diposnível*/
#define pointerToSizeOfMemory (int *)pBuffer
/**<--Define o ponteiro para 'amountOfContacts' segundo 'int' do Buffer
      amountOfContact-armazena a quantidade total de contatos inserido na agenda*/
#define pointerToAmountOfContacts (int *)pointerToSizeOfMemory+sizeof(int)
/**<--Define o ponteiro para 'index' terceiro 'int' do Buffer
      index-iterador para laços de repetição*/
#define pointerToIndex (int *)pointerToAmountOfContacts+sizeof(int)
/**<--Define o ponteiro para 'index2' quarto 'int' do Buffer
      index2-iterador para laços de repetição aninhados*/
#define pointerToIndex2 (int *)pointerToIndex+sizeof(int)
/**<--Define o ponteiro para 'sortAlgoritmType' quinto 'int' do Buffer
      sortAlgoritmType-define o algoritmo de ordenação utilizado para classificar os contatos*/
#define pointerToSortAlgoritmType (int *)pointerToIndex2+sizeof(int)
/**<--Define o ponteiro para 'menuOption' sexto 'int' do Buffer
      menuOption-seleciona opções do menu de interação com o usuário*/
#define pointerToMenuOption (int *)pointerToSortAlgoritmType+sizeof(int)
/**<--Define o ponteiro para 'searchingName' primeiro 'char' do Buffer
      searchingName-Nome para pesquisa de um contato na agenda*/
#define pointerToSearchingName (char *)pointerToMenuOption+sizeof(int)
/**<--Define o ponteiro para o primeiro contato na memória*/
#define pointerToFirstContact (contact *)pointerToSearchingName+sizeOfCharVariables
/**<--Define o ponteiro para o primeiro contato na memória*/
#define pointerToLastContact pointerToFirstContact+(*amountOfContacts*(sizeof(contact)));
/**<--Define o ponteiro para o contato no meio da agenda*/
#define pointerToHalfContact pointerToFirstContact+((*amountOfContacts/2)*(sizeof(contact)));

/**<Definição de Tipos*/
/**<-Tipo que armazena os dados de um contato na agenda*/
typedef struct PERSON{
    char name[sizeOfName];
    int  age;
}person;
/**<Assinatura de funções*/
/**<-Funções de gerenciamento de memória*/
/**<--Realoca uma quantidade de memória garantindo que não seja retornado um ponteiro nulo*/
void *reallocMemory(void *pBuffer, int *sizeOfMemory);
/**<-Funções de gerenciamento dos contatos*/
/**<--Inclui um novo contato na agenda*/
void includeContact(void *pBuffer, int *amountOfContacts, int *sizeOfMemory);
/**<--lista um todos contatos da agenda*/
void listContacts(void *pBuffer, int *amountOfContacts);
/**<--Pesquisa um contato na agenda pelo nome*/
contact *searchContact(void *pBuffer, int *amountOfContacts, char *searchingName);
/**<--Deleta um contato da agenda*/
void deleteContact(void *pBuffer, int *amountOfContacts, int *sizeOfMemory, char *searchingName);
/**<--Sobrescreve um contato pelo outro*/
void overwriteContact(contact *contactA, contact *contactB);
/**<--Troca dois contatos de posição na memória*/
void swapContact(void *pBuffer, int *amountOfContacts, contact *contactA, contact *contactB);
/**<-Funções de ordenamento dos contatos*/
/**<--Ordena os contatos em ordem crescente pelo nome utilizando o algoritmo de ordenação 'bubble sort'*/
void bubbleSortContacts(void *pBuffer, int *amountOfContacts);
/**<--Ordena os contatos em ordem crescente pelo nome utilizando o algoritmo de ordenação 'insertion sort'*/
void insertionSortContacts(void *pBuffer, int *amountOfContacts);
/**<--Ordena os contatos em ordem crescente pelo nome utilizando o algoritmo de ordenação 'selection sort'*/
void selectionSortContacts(void *pBuffer, int *amountOfContacts);
/**<--Ordena os contatos em ordem crescente pelo nome utilizando o algoritmo de ordenação 'merge sort'*/
void mergeSortContacts(void *pBuffer, int *amountOfContacts);
/**<--Ordena os contatos em ordem crescente pelo nome utilizando o algoritmo de ordenação 'quick sort'*/
void quickSortContacts(void *pBuffer, int *amountOfContacts);
/**<Funções implementadas*/
/**<-Funções de gerenciamento de memória*/
/*******************************************************************************
 * \brief Realoca uma quantidade de memória garantindo que não seja retornado um ponteiro nulo
 *
 * \param pBuffer = ponteiro para o Buffer de memória
 * \param sizeOfMemory = quantidade de memória necessária para realocar o Buffer
 *
 * \return Ponteiro para a nova posição de memória
 ********************************************************************************/
void *reallocMemory(void *pBuffer, int *sizeOfMemory){
    /**<realoca o Buffer*/
    pBuffer=realloc(pBuffer, *sizeOfMemory);
    /**<testa se 'pBuffer' é nulo*/
    if(pBuffer==NULL){
        printf("\nNão foi possível realocar a memória o programa será encerrado");
        exit(1);
    }else return pBuffer;
}
/**<-Funções de gerenciamento dos contatos*/
/*******************************************************************************
 * \brief Inclui um novo contato na agenda
 *
 * \param pBuffer = ponteiro para o Buffer de memória
 * \param amountOfContacts = quantidade de contatos já inseridos no sistema
 * \param sizeOfMemory = quantidade de memória necessária para realocar o Buffer
 *
 * \return Ponteiro para a nova posição de memória
 ********************************************************************************/
void includeContact(void *pBuffer, int *amountOfContacts, int *sizeOfMemory){
    /**<Definição de variaveis locais*/
    /**<-Ponteiro para o contato que será incluído*/
    contact *thisContact=NULL;
    /**<-Iniciação de variaveis*/
    /**<--Atualiza 'sizeOfMemory' com a quantidade de memória necessária para conter um novo contato*/
    *sizeOfMemory+=sizeof(contact);
    /**<--Aponta 'thisContact' para a primeira posição de memória livre para um novo contato*/
    thisContact=pointerToFirstContact+(*amountOfContacts*(sizeof(contact)));
    /**<Realoca 'pBuffer' para conter o novo contato*/
    pBuffer=reallocMemory(pBuffer, sizeOfMemory);
    /**<Interação com o usuário*/
    header(amountOfContacts, sizeOfMemory);
    printf("| Nome: ");
    scanf(" %[^\n]s", thisContact->name);
    printf("| Idade: ");
    scanf("%d", &thisContact->age);
    /**<incremento da quantidade de memória*/
    *amountOfContacts+=1;
     printf("|=========[Status: Contato incluido com sucesso %d contatos na agenda]=========|\n", *amountOfContacts);
     system("pause");
}
/*******************************************************************************
 * \brief lista um todos contatos da agenda
 *
 * \param pBuffer = ponteiro para o Buffer de memória
 * \param amountOfContacts = quantidade de contatos já inseridos no sistema
 *
 * \return esta função não possui retorno
 ********************************************************************************/
void listContacts(void *pBuffer, int *amountOfContacts){
    /**<Definição de variaveis locais*/
    /**<-Ponteiro para o contato que será impresso*/
    contact *thisContact=NULL;
    /**<Indice para percorrer todos contatos da memória*/
    int *index;
    int *sizeOfMemory;
    sizeOfMemory=pointerToSizeOfMemory;
    /**<-Iniciação de variaveis*/
    /**<--Aponta 'thisContact' para o primeiro contato da memória*/
    thisContact=pointerToFirstContact;
    /**<--Aponta 'index' para a posição de memória reservada para ele*/
    index=pointerToIndex;
    header(amountOfContacts, sizeOfMemory);
    /**<Laço de repetição que percorre todos contatos da agenda imprimindo cada um deles*/
    for(*index=0;*index<*amountOfContacts;*index+=1){
        printf("|N:%3d|Nome:                         %30.30s| Idade:%3d|\n", *index, thisContact->name, thisContact->age);
       /**<incrementa o contato atual*/
        thisContact+=sizeof(contact);
        system("pause");
    }
    footer();
    system("pause");
}
/*******************************************************************************
 * \brief Pesquisa um contato na agenda pelo nome
 *
 * \param pBuffer = ponteiro para o Buffer de memória
 * \param amountOfContacts = quantidade de contatos já inseridos no sistema
 * \param searchingName = nome do contato a ser pesquisado
 *
 * \return Ponteiro para o último contato com o nome pesquisado ou 'NULL' caso não seja encontrado nenhum contato
 ********************************************************************************/
contact *searchContact(void *pBuffer, int *amountOfContacts, char *searchingName){
	/**<Definição de variaveis locais*/
    /**<-Ponteiro para o primeiro contato da agenda*/
    contact *thisContact=NULL;
    /**<-Ponteiro para o contato pesquisado*/
    contact *searchedContact=NULL;
    /**<Indice para percorrer todos contatos da memória*/
    int *index;
    int *sizeOfMemory;
    /**<Iniciação de variaveis*/
    /**<-aponta 'searchedContact' para o ultimo endereço de memória*/
    searchedContact=pointerToLastContact;
    /**<-aponta 'sizeOfMemory' para o endereço de memória reservado para ele*/
    sizeOfMemory=pointerToSizeOfMemory;
    /**<-armazena em 'sizeOfMemory' a quantidade de memória necessária para armazenar todos contatos +1*/
    *sizeOfMemory=sizeOfpBufferHead+(*amountOfContacts+1)*(sizeof(contact));
    /**<Realoca 'pBuffer' para armazenar os dados de'temporaryContact' no ultimo endereço de memória*/
    reallocMemory(pBuffer, sizeOfMemory);
    /**<--Aponta 'thisContact' para o primeiro contato da memória*/
    thisContact=pointerToFirstContact;
    /**<--Aponta 'index' para a posição de memória reservada para ele*/
    index=pointerToIndex;
    /**<Laço de repetição que percorre todos contatos da agenda comparando com o nome pesquisado*/
    for(*index=0;*index<*amountOfContacts;*index+=1){
		/**<Compara o nome pesquisado com o nome do contato atual*/
		if(strcmp(searchingName, thisContact->name)==0){
			/**<Sobrescreve 'searchedContact'caso o nome pesquisado for igual ao nome do contato atual*/
			overwriteContact(searchedContact, thisContact);
		}
		/**<Incrementa o ponteiro 'thisContact'*/
		thisContact+=sizeof(contact);
	}
    return searchedContact;
}
/*******************************************************************************
 * \brief Deleta um contato da agenda pesquisando pelo nome
 *
 * \param pBuffer = ponteiro para o Buffer de memória
 * \param amountOfContacts = quantidade de contatos já inseridos no sistema
 * \param sizeOfMemory = quantidade de memória necessária para realocar o Buffer
 * \param searchingName = nome do contato a ser deletado
 *
 * \return Ponteiro para o último contato com o nome pesquisado ou 'NULL' caso não seja encontrado nenhum contato
 ********************************************************************************/
void deleteContact(void *pBuffer, int *amountOfContacts, int *sizeOfMemory, char *searchingName){
	/**<Definição de variaveis locais*/
    /**<-Ponteiro para o contato a ser deletado*/
    contact *deletedContact=NULL;
    /**<-Ponteiro para o próximo contato*/
    contact *nextContact=NULL;
    /**<Indice para percorrer todos contatos da memória*/
    int *index;
    /**<-Iniciação de variaveis*/
    /**<--Aponta 'index' para a posição de memória reservada para ele*/
    index=pointerToIndex;
    /**<Interação com o usuário*/
    header(amountOfContacts, sizeOfMemory);
    printf("Digite o nome do contato que deseja excluir:");
    scanf(" %[^\n]s", searchingName);
    /**<--Atualiza 'deletedContact' com o valor de retorno da função 'deletedContact'*/
    deletedContact=searchContact(pBuffer, amountOfContacts, searchingName);
    /**<Verifica se existe o contato para excluir*/
    if(deletedContact!=NULL){
        nextContact=deletedContact+sizeof(contact);
		/**<Percorre todos contatos a partir do contato a ser deletado sobrescrevendo o contato deletado, deslocando todo contatos uma poisção para esquerda*/
		for(*index=0;*index<*amountOfContacts-1;*index+=1){
			/**<sobrescreve o contato atual pelo próximo*/
			overwriteContact(deletedContact, nextContact);
			/**<incrementa o ponteiro do contato atual*/
			deletedContact+=sizeof(contact);
			/**<atualiza 'nextContact' com o valor do contato atual +1 contato*/
			nextContact+=sizeof(contact);
	    }
	    *amountOfContacts-=1;
	    *sizeOfMemory=sizeOfpBufferHead+((*amountOfContacts)*sizeof(contact));
	    reallocMemory(pBuffer, sizeOfMemory);
	    printf("|=========[Status: Contato excluído com sucesso %d contatos na agenda]=========|\n", *amountOfContacts);
	    system("pause");
	}
}
/*******************************************************************************
 * \brief Sobrescreve um contato pelo outro
 *
 * \param contactA = contato que será sobrescrito
 * \param contactB = contato que contém os dados que sobrescrevem 'contactA'
 *
 * \return esta função não possui retorno
 ********************************************************************************/
void overwriteContact(contact *contactA, contact *contactB){
	/**<copia o nome de 'contactB' para 'contactA'*/
	strcpy(contactA->name, contactB->name);
	/**<copia a idade de 'contactB' para 'contactA''*/
	contactA->age=contactB->age;
}
/*******************************************************************************
 * \brief Troca dois contatos de posição na memória
 *
 * \param contactA = primeiro contato da troca
 * \param contactB = segundo contato da troca
 *
 * \return esta função não possui retorno
 ********************************************************************************/
void swapContact(void *pBuffer, int *amountOfContacts, contact *contactA, contact *contactB){
	/**<Definição de variaveis locais*/
    /**<-Ponteiro para armazenar temporariamente os dados de um contato para efetuar a troca*/
    contact *temporaryContact=NULL;
    int *sizeOfMemory;
    /**<Iniciação de variaveis*/
    /**<-aponta 'temporaryContact' para o ultimo endereço de memória*/
    temporaryContact=pointerToLastContact;
    /**<-aponta 'sizeOfMemory' para o endereço de memória reservado para ele*/
    sizeOfMemory=pointerToSizeOfMemory;
    /**<-armazena em 'sizeOfMemory' a quantidade de memória necessária para armazenar todos contatos +1*/
    *sizeOfMemory=sizeOfpBufferHead+(*amountOfContacts+1)*(sizeof(contact));
    /**<Realoca 'pBuffer' para armazenar os dados de'temporaryContact' no ultimo endereço de memória*/
    reallocMemory(pBuffer, sizeOfMemory);
    /**<sobrescreve'temporaryContact' com os dados de 'contactA'*/
    overwriteContact(temporaryContact, contactA);
    /**<sobrescreve'contactA' com os dados de 'contactB'*/
    overwriteContact(contactA, contactB);
    /**<sobrescreve'contactB' com os dados de 'temporaryContact' que contem os valores de 'contactA' antes de ser sobreescrito*/
    overwriteContact(contactB, temporaryContact);
}
/**<-Funções de ordenamento dos contatos*/
/*******************************************************************************
 * \brief Ordena os contatos em ordem crescente pelo nome utilizando o algoritmo de ordenação 'bubble sort'
 *
 * \param pBuffer = ponteiro para o Buffer de memória
 * \param amountOfContacts = quantidade de contatos já inseridos no sistema
 *
 * \return esta função não possui retorno
 ********************************************************************************/
void bubbleSortContacts(void *pBuffer, int *amountOfContacts){
	/**<Definição de variaveis locais*/
    /**<-Ponteiro para o contato atual*/
    contact *thisContact=NULL;
    /**<-Ponteiro para o próximo contato*/
    contact *nextContact=NULL;
    /**<Indice para percorrer laço de repetição externo*/
    int *index;
    /**<Indice para percorrer laço de repetição interno*/
    int *index2;
    /**<-Iniciação de variaveis*/
    /**<--Aponta 'thisContact' para o primeiro contato da memória*/
    thisContact=pointerToFirstContact;
    /**<--Aponta 'index' para a posição de memória reservada para ele*/
    index=pointerToIndex;
    /**<--Aponta 'index2' para a posição de memória reservada para ele*/
    index2=pointerToIndex2;
    /**<Laço de repetição externo percorre do primeiro ao penúltimo contato*/
    for(*index=0;*index<(*amountOfContacts-1);*index+=1){
		/**<Laço de repetição interno percorre do primeiro contato até o contato anteior ao atual*/
        for (*index2=0;*index2<*amountOfContacts-*index-1;*index2+=1){
            /**<Atualiza 'nextContact' com o valor do próximo contato*/
				nextContact=thisContact+sizeof(contact);
            /**<compara se o nome do contato atual é menor que o próximo contato*/
            if (strcmp(thisContact->name, nextContact->name)>0){
				/**<Troca os contatos de posição caso o atual seja maior que o próximo*/
                swapContact(pBuffer, amountOfContacts, thisContact, nextContact);
                listContacts(pBuffer, amountOfContacts);
                system("pause");
            }
            /**<Incrementa o contato atual*/
            thisContact+=sizeof(contact);
        }
        thisContact=pointerToFirstContact;
    }
    printf("|========[Status: Contatos ordenados com sucesso %d contatos na agenda]========|\n", *amountOfContacts);
    system("pause");
}
/**<--Ordena os contatos em ordem crescente pelo nome utilizando o algoritmo de ordenação 'insertion sort'*/
void insertionSortContacts(void *pBuffer, int *amountOfContacts){
    /**<Definição de variaveis locais*/
    /**<-Ponteiro para o contato atual*/
    contact *thisContact;
    contact *contactsIndex;
    contact *contactsIndex2;
    /**<-Ponteiro para o próximo contato*/
    contact *nextContact;
    /**<Indice para percorrer laço de repetição externo*/
    int *index;
    /**<Indice para percorrer laço de repetição interno*/
    int *index2;
    int *sizeOfMemory;
    /**<Iniciação de variaveis*/
    /**<-aponta 'temporaryContact' para o ultimo endereço de memória*/
    thisContact=pointerToLastContact;
    /**<-aponta 'sizeOfMemory' para o endereço de memória reservado para ele*/
    sizeOfMemory=pointerToSizeOfMemory;
    /**<-armazena em 'sizeOfMemory' a quantidade de memória necessária para armazenar todos contatos +1*/
    *sizeOfMemory=sizeOfpBufferHead+(*amountOfContacts+1)*(sizeof(contact));
    /**<Realoca 'pBuffer' para armazenar os dados de'temporaryContact' no ultimo endereço de memória*/
    reallocMemory(pBuffer, sizeOfMemory);
    /**<-Iniciação de variaveis*/
    /**<--Aponta 'thisContact' para o primeiro contato da memória*/
    contactsIndex=pointerToFirstContact+sizeof(contact);
    contactsIndex2=pointerToFirstContact;
    /**<--Aponta 'index' para a posição de memória reservada para ele*/
    index=pointerToIndex;
    /**<--Aponta 'index2' para a posição de memória reservada para ele*/
    index2=pointerToIndex2;
    *index=1;
    /**<Laço de repetição externo percorre do primeiro ao penúltimo contato*/
    for(*index=1;*index<(*amountOfContacts-1);*index+=1){         //{for( j=1; j < tamanhoVetor; j++ )
        overwriteContact(thisContact, contactsIndex);//valorAtual = vetorDesordenado[j];
        *index2=*index-1;//i = j-1;
        while(*index2>=0 &&(strcmp(contactsIndex2->name, thisContact->name)>0)){//  while(i >= 0 && vetorDesordenado[i] > valorAtual)
            nextContact=contactsIndex2+sizeof(contact);//vetorDesordenado[i+1] = vetorDesordenado[i];
            swapContact(pBuffer, amountOfContacts, nextContact, contactsIndex2);
            *index2-=1;//i--;
            contactsIndex2-=sizeof(contact);
        }
        swapContact(pBuffer, amountOfContacts, nextContact, thisContact);//vetorDesordenado[i+1] = valorAtual;
        contactsIndex+=sizeof(contact);
    }
    printf("|=========[Status: Contatos ordenados com sucesso %d contatos na agenda]========|\n", *amountOfContacts);
    system("pause");
}
/**<--Ordena os contatos em ordem crescente pelo nome utilizando o algoritmo de ordenação 'selection sort'*/
void selectionSortContacts(void *pBuffer, int *amountOfContacts){}
/**<--Ordena os contatos em ordem crescente pelo nome utilizando o algoritmo de ordenação 'merge sort'*/
void mergeSortContacts(void *pBuffer, int *amountOfContacts){}
/**<--Ordena os contatos em ordem crescente pelo nome utilizando o algoritmo de ordenação 'quick sort'*/
void quickSortContacts(void *pBuffer, int *amountOfContacts){}
/**<--Ordena os contatos em ordem crescente pelo nome utilizando o algoritmo de ordenação passado em 'sortAlgoritmType'*/
void sortContacts(void *pBuffer, int *amountOfContacts, int *sortAlgoritmType){
	switch(*sortAlgoritmType){
			case 0:bubbleSortContacts(pBuffer, amountOfContacts);
			break;
			case 1:insertionSortContacts(pBuffer, amountOfContacts);
			break;
			case 2:selectionSortContacts(pBuffer, amountOfContacts);
			break;
			case 3:mergeSortContacts(pBuffer, amountOfContacts);
			break;
			case 4:quickSortContacts(pBuffer, amountOfContacts);
			break;
			default: printf("\n|=====================[Erro: Selecione um numero de 1 a 5]=====================|\n");
            break;
		}
}
