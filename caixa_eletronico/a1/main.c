#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

struct conta
{
	char nome[50];
	int nc; //5 dígitos
	int senha; //6 dígitos
	float saldo;
	int sd; //saque diario
	int lsd; //L imite de S aldo D iario
}conta[3];

char s[64]; //pra colocar hora

FILE *arq; //para abrir arquivo

int ncdep, saldodep, saque, sd, lsd;
int ncc, senha, dsenha; //na parte de quando pede num da conta e senha
float saldo, vdep;
char nome[50], nomedep[50];
//int dec=0, decs=0, decd=0; //partes que da loop, tipo while
int dec, decs, decd;

int y;


//----------------------------------------------------------------------------------

void ConfereContas(){ //parte pra pedir conta e senha

do{
dec=0;	
printf("\nDigite sua conta corrente: ");
scanf("%d", &ncc);

//AQUI, ELE LE O NUMERO DA CONTA E IMPORTA PARA VARIAVEIS PARA USAR UMA SÓ DAI
//SEMPRE QUE EU QUISER O NOME, EU USO UMA VARIAVEL, E NAO FICO MUDANDO ENTRE AS CONTAS
//SÓ ESCREVO nome E NAO CONTA[1] OU O NUMERO QUE FOR
if(ncc==conta[0].nc){
	strcpy(nome,conta[0].nome);
	saldo=conta[0].saldo;
	senha=conta[0].senha;
	sd=conta[0].sd;
	lsd=conta[0].lsd;
}

else if(ncc==conta[1].nc){
	strcpy(nome,conta[1].nome);
	saldo=conta[1].saldo;
	senha=conta[1].senha;
	sd=conta[1].sd;
	lsd=conta[1].lsd;
}

else if(ncc==conta[2].nc){
	strcpy(nome,conta[2].nome);
	saldo=conta[2].saldo;
	senha=conta[2].senha;
	sd=conta[2].sd;
	lsd=conta[2].lsd;
	break;
}

else if(ncc==conta[3].nc){
	strcpy(nome,conta[3].nome);
	saldo=conta[3].saldo;
	senha=conta[3].senha;
	sd=conta[3].sd;
	lsd=conta[3].lsd;
}

else{
	printf("Conta nao existente\n");
	dec=1;	
	sleep(3);
}
}while(dec!=0);

printf("\nOla %s!\n", nome);
sleep(2);

do{
dec=0;
printf("\nDigite sua senha: ");
scanf("%d", &dsenha);
if (dsenha!=senha){
	printf("\nSenha incorreta!!!!\n\n");
	sleep(2);
	dec=1;
}

}while(dec!=0);
}

//----------------------------------------------------------------------------------	

void Saldo(){
	
ConfereContas();

printf("\n\nProcessando...");
sleep(4);

printf("\n\n%s, o saldo disponivel na sua conta eh:\n\n ********* R$ %.2f *******",nome,saldo); 	

//ESCREVE NO LOG
arq= fopen("log.txt", "a"); 
fprintf(arq,"%s-%d-%s-'saldo verificado'\n",s,ncc,nome); 
fclose(arq);

sleep(6);
}


//---------------------------------------------------------------------------------------------

void Saque(){
	
	ConfereContas();

	if(sd<=0||lsd<=0){
	//SD - SAQUE DIARIO (ATE 3)
	//LSD - LIMITE DE SAQUE DIARIO - 700 REAIS
		printf("\nVoce ultrapassou o limite de saldo diario");
	}
	else if(saldo<=0){
		printf("%s, sua conta nao tem saldo\n",nome);
		printf("Realize um deposito na sua conta\n\n");
		sleep(3);
	}
	else{
		do{
		printf("\n%s, o saldo da sua conta eh:\n\n ********* R$ %.2f *******\n\n",nome,saldo);
		printf("Digite a quantia a qual voce deseja sacar\n(Apenas multiplos de 5)\n ");
		printf("(Notas de R$5.00, R$50.00 e R$100.00)\n(R$) ");
		scanf("%d", &saque);
		if (saque%5==0){
			//COMO E VALOR DE NOTAS DE 100, 50 OU 5
			//ELE DIVIDE POR 5 E SE O RESTO FOR 0, É DIVISÍVEL POR 5
			//ENTAO OS VALORES PODEM SER DADOS NO MINIMO NOTAS DE 5
			//SE ELE DIGITAR "52 REAIS", NAO VAI DAR, PORQUE NAO DA PRA DIVIDIR POR 5
			//E A MAQUINA NAO TEM NOTAS DE 2 - SÓ 5, 100 E 50
			
			if (saque>saldo){
				printf("\nSaldo insuficiente para saque");	
				decs=1;
			}
			else if (saque>lsd){
				printf("Seu saque nao pode ser maior que R$700.00 diarios\n");
				printf("Voce pode sacar até ***R$%d.00*** nas proximas 24 horas\n",lsd);
				decs=1;
				}
			else{
				printf("\nCalculando notas...\n");
				sleep(2);
				
				saldo=saldo-saque;
				lsd=lsd-saque;//tu começa com 700, aqui ele tira o que tu sacou dos 700
				sd=sd-1;//tu começa com limite 3, aqui diminui 1 cada vez que tu saca
				
				//GRAVA NO ARQUIVO						
				arq= fopen("log.txt", "a");
				fprintf(arq,"%s-%d-%s-'saque efetuado'-R$%d.00\n",s,ncc,nome,saque);
				fclose(arq);
					
				printf("\nDinheiro sacado com sucesso!\n");
				
				//SE BATER OS LIMITES, AVISA
				if(lsd==0||sd==0){
					printf("%s, seu limite de saques foi atingido.\nVoce podera sacar novamente somente amanha apos as %s\n\n", nome,__TIME__);//TIME É PRA APARECER SÓ A HORA
				}
				else{
				printf("%s, voce ainda pode realizar %d saques\nde no maximo R$%.2d nas proximas 24 horas\n\n",nome,sd,lsd);
				}
				sleep(7);
				printf("Saldo atual: \n\n********* R$ %.2f ********\n",saldo);
				
				//ESSE É PRA RETORNAR OS VALORES
				//O NOVO SALDO E NOVOS LIMITES
				//TENHO QUE RETORNAR PRA ELES PORQUE SE EU FOR ABRIR DE OUTRO CARA E DE NOVO O QUE EU FIZ, NAO VAI MUDAR
				//ELE JOGA DE VOLTA PRAS STRUCTS DO CARA OS VALORES DELE
				if(ncc==conta[0].nc){
				conta[0].saldo=saldo;
				conta[0].sd=sd;
				conta[0].lsd=lsd;
				break;
				}
				
				else if(ncc==conta[1].nc){
				conta[1].saldo=saldo;
				conta[1].sd=sd;
				conta[1].lsd=lsd;
				break;
				}
				
				else if(ncc==conta[2].nc){
					conta[2].saldo=saldo;
					conta[2].sd=sd;
					conta[2].lsd=lsd;
					break;
				}
				
				else if(ncc==conta[3].nc){
					conta[3].saldo=saldo;
					conta[3].sd=sd;
					conta[3].lsd=lsd;
					break;
				}
				else{
					break;
				}
				decs=0;
			}
	}		
	else{
	printf("Valor nao eh multiplo de 5");
	decs=1;
}

}while(decs!=0);
	
}
}
//------------------------------------------------------------------------------------------

void Deposito(){
	
	do{
	printf("\nDigite o valor que queira depositar: (R$) ");
	scanf("%f", &vdep);
		printf("Digite o numero da conta o qual deseja depositar: ");
	
	//-------parte nova ----------------
		scanf("%d", &ncc);
	
		if(ncc==conta[0].nc){
		strcpy(nome,conta[0].nome);
		saldo=conta[0].saldo;
		break;
		}
			
		else if(ncc==conta[1].nc){
		strcpy(nome,conta[1].nome);
		saldo=conta[1].saldo;
		break;
		}
		
		else if(ncc==conta[2].nc){
		strcpy(nome,conta[2].nome);
		saldo=conta[2].saldo;
		break;
		}

		else if(ncc==conta[3].nc){
		strcpy(nome,conta[3].nome);
		saldo=conta[3].saldo;
		break;
		}
		
			
		else{
		printf("Conta nao existente\n");
		dec=1;	
		sleep(6);
		}
	}while(dec!=0);
	
		printf("\nValor: R$%.2f\nConta: %d\nNome : %s\n\nVoce deseja depositar?\n",vdep,ncc,nome);
		printf("\nDigite 1 para confirmar ou 2 para cancelar\n");
		scanf("%d", &decd);

		if(decd==1){
			printf("Procesando....");
			sleep(3);
			saldo=saldo+vdep;
			
			//GRAVA ARQUIVO....
			arq= fopen("log.txt", "a");
			fprintf(arq,"%s-%d-%s-'deposito efetuado'-R$%.2f\n",s,ncc,nome,vdep);
			fclose(arq);
			
			//RETORNA O NOVO SALDO PARA AS VARIAVEIS DO CARA
			if(ncc==conta[0].nc){
				conta[0].saldo=saldo;
			}
		
			else if(ncc==conta[1].nc){
				conta[1].saldo=saldo;
			}
			
			else if(ncc==conta[2].nc){
				conta[2].saldo=saldo;
			}
			
			else if(ncc==conta[3].nc){
				conta[3].saldo=saldo;
			}

			printf("\n\nDeposito realizado com sucesso\n");
		}
		else{
			printf("Operacao cancelada");
		}

}
	

//---------------------------------------------------------------------


void Transferencia(){
	
	ConfereContas();
	
	printf("\nDigite o valor que queira transferir: (R$) ");
	scanf("%f", &vdep);
	if(vdep>saldo){
		printf("\nSaldo indisponivel na sua conta");
	}
	else{
		do{
		dec=0;
		printf("Digite o numero da conta o qual deseja tranferir: ");
		scanf("%d", &ncdep);
		//AQUI PEGA OS DADAS DO CARA QUE VAI ENTRAR O DINHEIRO
		//SE TU DEPOSITA DINEHIRO PRA MIM, ALEM DE SAIR DINHEIRO DA TUA CONTA
		//ELE CALCULA QUANDO VAI ENTRAR NA MINHA			
		if(ncdep==ncc){
			printf("\n\nVoce nao fazer transferencia para sua prorpia conta\n\n");
			sleep(3);
			dec=1;
		}
		else {
			if(ncdep==conta[0].nc){
			strcpy(nomedep,conta[0].nome);
			saldodep=conta[0].saldo;
			}
			
			else if(ncdep==conta[1].nc){
			strcpy(nomedep,conta[1].nome);
			saldodep=conta[1].saldo;
			}
			
			else if(ncdep==conta[2].nc){
			strcpy(nomedep,conta[2].nome);
			saldodep=conta[2].saldo;
			}
			
			else if(ncdep==conta[3].nc){
			strcpy(nomedep,conta[3].nome);
			saldodep=conta[3].saldo;
			}
			else{
			printf("Conta nao existente\n");
			dec=1;	
			sleep(4);
			}
		}
	}while(dec!=0);
	
		printf("\nValor: R$%.2f\nConta: %d\nNome : %s\n\nVoce deseja tranferir?\n",vdep,ncdep,nomedep);
		printf("\nDigite 1 para confirmar ou 2 para cancelar\n");
		scanf("%d", &decd);
		if(decd==1){
			printf("Procesando....");
			sleep(3);
			saldodep=saldodep+vdep;//CALCULA O SALDO DO CARA QUE ****VAI ENTRAR**** DINHEIRO
			saldo=saldo-vdep; //CALCULA O SALDO DO CARA QUE ****SAIU**** O DINHEIRO
			
			//GRAVA ARQUIVO
			arq= fopen("log.txt", "a");
			fprintf(arq,"%s-%d-%s-%d-%s-R$%.2f\n",s,ncc,nome,ncdep,nomedep,vdep);
			fclose(arq);

			printf("\n\nTranferencia realizada com sucesso\n");
			printf("%s, seu saldo atual eh R$ %.2f ", nome, saldo);
			
			//RETORNA VALORES
			//RETORNA NOVO SALDO DO QUE TRANSFERIU
			if(ncc==conta[0].nc){
			conta[0].saldo=saldo;
			}
		
			if(ncc==conta[1].nc){
			conta[1].saldo=saldo;
			}
			
			else if(ncc==conta[2].nc){
				conta[2].saldo=saldo;
			}
			
			else if(ncc==conta[3].nc){
				conta[3].saldo=saldo;
			}

			//------------------------
			//RETORNA NOVO SALDO DE QUEM RECEBEU
			if(ncdep==conta[0].nc){
				conta[0].saldo=saldodep;
			}
			
			else if(ncdep==conta[1].nc){
				conta[1].saldo=saldodep;
			}

			else if(ncdep==conta[2].nc){
				conta[2].saldo=saldodep;
			}
			
			else if(ncdep==conta[3].nc){
				conta[3].saldo=saldodep;
			}
			//--------------------
			
		}
		else{
			printf("Operacao cancelada");
		}
}


	sleep(5);
}
//---------------------------------------------------------------------------

int main(int argc, char *argv[]) {
//NAO CONSEGUI COLOCAR AS CONTAS FORA DA MAIN
//ELE NAO TAVA RETORNANDO OS VALORES

//Conta Maria
conta[0].nc=10293;	
strcpy (conta[0].nome,"MARIA MARIA");
conta[0].senha=102938;
conta[0].saldo=0;
conta[0].sd=3;
conta[0].lsd=700;

//Conta do Fabiano
conta[1].nc=12345;	
strcpy (conta[1].nome,"FABIANO DUTRA");
conta[1].senha=123456;
conta[1].saldo=0;
conta[1].sd=3;
conta[1].lsd=700;

//Conta do Daniel
conta[2].nc=54321;	
strcpy (conta[2].nome,"DANIEL A.");
conta[2].senha=543210;
conta[2].saldo=0;
conta[2].sd=3;
conta[2].lsd=700;


//Conta do Taciano
conta[3].nc=98765;	
strcpy (conta[3].nome,"PROF. TACIANO");
conta[3].senha=987654;
conta[3].saldo=0;
conta[3].sd=3;
conta[3].lsd=700;
//Fim contas**********************************************
//O X É SÓ PRA TER UMA VARIAVEL PRO LOOPING
//DEPOIS QUE EU LIGO O CAIXA ELE NUNCA DESLIGA, VAI TA SEMPRE LIGADO
int x, opcao;

for(x=0;x==0;){

//ESSAS COISAS SAO PRA HORA
time_t t = time(NULL);
struct tm *tm = localtime(&t);
strftime(s, sizeof(s), "%c", tm);
printf("%s\n\n", s);

system("cls");
printf("TRABALHO FINAL - FABIANO E DANIEL\n---------------------------------\n\n");
printf("Bem vindo ao Banco\n\n");

printf("POR FAVOR,\n");
printf("\nSELECIONE A OPCAO DESEJADA ABAIXO:\n");
printf("\n ( 1 ) DEPOSITO       ");
printf("\n ( 2 ) SALDO          ");
printf("\n ( 3 ) SAQUE          ");
printf("\n ( 4 ) TRANSFERENCIA\n\n");
scanf("%d", &opcao);

switch(opcao){
	case 1:
		system("cls");
		printf("*** DEPOSITO ***\n");
		Deposito();
 		break;
	case 2:
		system("cls");
		printf("*** CONFERENCIA DE SALDO ***\n");
		Saldo();
		break;
		
	case 3:
		system("cls");
		printf("*** SAQUE ***\n");
		Saque();
		break;
	
	case 4:
		system("cls");
		printf("*** TRANFERENCIAS ***\n");
		Transferencia();
		break;
	default:
		break;
}

printf("\n\nObrigado! Volte sempre.");

sleep(7);
}
}
