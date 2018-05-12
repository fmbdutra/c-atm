#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Fabiano Dutra e Cleber Weishimer


struct Produto
{
	int Id;    /* código produto */ 
	float precoProd;          /* preco produto */
	char nome[50];       /* nome produto */
};

typedef struct Produto CadProd; //cria um tipo Produto

FILE *arq; //declarar arquivo universal

int Cadastrar(char nome[50], float preco); //funcao cadastro

CadProd BuscarRef(int reg); // funcao buscar por referencia

CadProd BuscarNome(char nome[50]); // funcao buscar por nome

int regc; //Id confere no txt
float precoc; //preco confere no txt
char nomec[50]; // nome confere no txt
	
int main (int argc, char *argv[])
{
	
	int i, input, ncad, ref, dec;
	char nome[50], bNome[50];
	float preco;
	CadProd busca, retNome;

	do{
	//monta o cabecalho de informações 
		system("cls");
		printf("FABIANO DUTRA E CLEBER WEISHIMER - TRABALHO 4\n\n");
		for(i=0; i <= 50; i++){
		printf("*");
		if((i > 25) && (i < 27)){
		printf("\n*   CADASTRO DE PRODUTOS  *");
		printf("\n* ");
		for(i=0; i <= 22; i++){
		printf("-");
		if(i == 22){
		printf(" *");
		}
		}
		printf("\n* ( 1 ) CADASTRAR         *" );
		printf("\n* ( 2 ) CONSULTAR         *");
		printf("\n* ( 0 ) SAIR              *\n");
		for(i=0; i <= 26; i++){
		printf("*");
		if(i == 26){
		printf("\n");
		}
		}
		scanf("%d", &input);
	// fim cabeçalho

	//CADASTRAR DE PRODUTOS---------------------------------
		if(input == 1){
			printf("\n ---- CADASTRAR  PRODUTOS ----- \n ---------------------------------");
			printf("\nDIGITE O NOME DO PRODUTO: ");
			fflush(stdin); //limpa buffer do teclado
			scanf("%s", &nome);
			
			printf("\nDIGITE O PRECO DO PRODUTO: ");
			fflush(stdin); //limpa buffer do teclado
			scanf("%f", &preco);
		

			ncad=Cadastrar(nome,preco);
			
			printf("\nID   : %0.5d\nNOME : %s\nPRECO: R$ %0.2f",ncad,strupr(nome),preco);
			printf("\n\n************ PRODUTO CADASTRADO COM SUCESSO ! **************");
			sleep(5);	
		}
	//FIM DO CADASTRO-------------------------------------------
	//----------------------------------------------------------
	//BUSCA DE PRODUTOS ----------------------------------------
		if(input == 2){
			//int dec; // para definir se 1 para buscar Id ou 2 para buscar nome
			printf("\n ---- BUSCAR PRODUTOS ----- \n -----------------------------------");
			printf("\n( 1 ) REFERENCIA\n");
			printf("\n( 2 ) NOME\n");
			printf("-----------------------------------\n");
			scanf("%d", &dec);
			
			//BUSCA POR REFERENCIA------------------------
			if(dec==1){
						
				printf("\nDIGITE O REFERENCIA DESEJADA: ");
				fflush(stdin); //limpa buffer do teclado
				scanf("%d", &ref);
				
				busca=BuscarRef(ref);
				
				if(ref==busca.Id){
				printf("\n**** ITEM %d ENCONTRADO ****\n", ref);	
				printf("ID   : %0.5d\nNOME : %s\nPRECO: R$ %0.2f", busca.Id,strupr(busca.nome),busca.precoProd);
				}
				else{
				printf("\nITEM NAO ENCONTRADO");
				}
				
				sleep(6);
			}
		
		//BUSCA POR NOME--------------------------------------------
			else if(dec==2){
						
				printf("\nDIGITE O NOME DESEJADO: ");
				fflush(stdin); //limpa buffer do teclado
				scanf("%s", &bNome);
				strupr(bNome);
	
				retNome=BuscarNome(bNome);
				
				if(strcmp(bNome,retNome.nome)==0)//compara strings
				{
				printf("\n**** ITEM %s ENCONTRADO ****\n", strupr(bNome));	
				printf("ID   : %0.5d\nNOME : %s\nPRECO: R$ %0.2f", retNome.Id,strupr(retNome.nome),retNome.precoProd);
				}
				else{
				printf("\nITEM NAO ENCONTRADO"); //quando retorna 0
				}
				
				sleep(6);
	}
	}
	//FIM DA BUSCA------------------------------------------
	}
	}
		if(input==0){
		return 0;
	}
	}while(input=!0||input>=3 );
	return 0;
}



int Cadastrar(char nome[50], float preco){

	int reg;
	
	//inicio de conferência do último registro para fazer +1 do último (se foi 10, vai ser 11) 
	
	arq= fopen("dados.txt", "r+");
	
	if(arq == NULL){
		arq= fopen("dados.txt", "a"); // cria txt, "r" só le e buga se nao existir
		regc=0; //coloca Id 0 para somar com 1 e ficar o primeiro item 00001
		fclose(arq);		
	}
	
	//conferencia
	else{
		while (!feof(arq)) //le arquivo até o fim	
			{
				fscanf(arq,"%d %f %s",&regc, &precoc, &nomec); //0004 2.50 nome
				reg=regc; //pega última variável inteira do txt
			}
			fclose(arq);
	}
	//fim conferência
	
	reg+=1; //atribui +1 na última Id
	
	arq= fopen("dados.txt", "a"); //o "a" faz ele escrever no final do arquivo, para isso a conferencia
	
	fprintf(arq,"%.5d %.2f %s\n",reg,preco,strupr(nome));  //grava no arquivo
	
	fclose(arq); //fecha arquivo
	
	return reg; //retorna o número da Id
}

CadProd BuscarRef(int reg){
	
	CadProd BuscaId;

	arq= fopen("dados.txt", "r");
	
	if(arq == NULL){
	BuscaId.Id=0;
	fclose(arq);		
	}
	else{
	
	while (!feof(arq))
	{
		fscanf(arq,"%d %f %s",&regc,&precoc,&nomec);
		 //se o id que digitou foi igual ao reg, ele atribui
		if(reg==regc){
			BuscaId.Id=regc; // pega o id, nome e preco do reg igual
			BuscaId.precoProd=precoc;
			strcpy(BuscaId.nome, nomec);	
		}

	}
}
	return BuscaId; //joga id, nome e valor de volta pra main

}


CadProd BuscarNome(char nome[50]){
	
	CadProd BuscaN;

	arq= fopen("dados.txt", "r");
	
	if(arq == NULL){
	BuscaN.Id=0;
	}
	else{
	while (!feof(arq))
		{
			fscanf(arq, "%d %f %s", &regc, &precoc, &nomec);
			//se o nome que digitou for igual a algum que passou, joga pra struct
			if(strcmp(nome,nomec)==0){
				BuscaN.Id=regc;
				BuscaN.precoProd=precoc;
				strcpy(BuscaN.nome, nomec);
			}
		}
	}
	return BuscaN; //retorna 

}
