/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
/**
 * @author nossa empresa ACESS FOR ALL
 * Trabalho PIM- desenvolvimento linguagem programador C
 * Analise e desenvolvimento de sistema- UNIP PAULISTA
 *
 *
 * @copyright Copyright (c) 2022
 */
 
/*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define N 100
#define TRUE			1
#define FALSE 		0

typedef unsigned char boolean;

typedef char string[50];

struct Aniversario //estrutura de data de nascimento
{
  int dia;
  int mes;
  int ano;
};

typedef struct Funcionario //estrutura ficha de funcionario
{
  string nome;
  string cidade;
  float salario;
  struct Aniversario aniversario; //aninhamento de estrutura
  struct Funcionario *prox;
} funcionario;

int matricula=0; // variavel de controle do numero de funcionarios cadastrados
float salariomin = 1500.00; // variavel com o valor do salario minino

//declaração das funções que seram utilizadas no codigo
int menu();
funcionario* adicionar();
void insere_item(funcionario **lista, funcionario *item);
void atualizar(funcionario* lista);
void relatorio(funcionario* lista);
void consultar(funcionario* lista);
void comparar(funcionario* lista);
void relacionar(funcionario* lista);
void cidade(funcionario* lista);
void deletar(funcionario **lista);
void apaga_todos_os_dados(funcionario **lista);
void exporta_dados_arquivo_txt(funcionario *lista);
void importa_dados_arquivo_txt(funcionario **lista);
void salva_dados_arquivo_bin(funcionario *lista);
void recupera_dados_arquivo_bin(funcionario **lista);
void remove_enter(char s[N]);
boolean lista_esta_vazia(funcionario *lista);

int main(){

  funcionario *lista = NULL, *novo;
  
  int varwhile = 1; //loop para sempre voltar pro menu
  int opc; // variavel de escolha do menu

  //importa dados salvos anteriormente
  recupera_dados_arquivo_bin(&lista);
  
  while(varwhile){
    //system(“cls”);
    
    opc = menu();
    switch(opc){
      case 1:
        printf("\n Adicionar ficha de funcionario:  \n");
        novo = adicionar();
        insere_item(&lista, novo);
        break;
      case 2:
        printf("\n Atualizar ficha de funcionario: \n");
        atualizar(lista);
        break;
      case 3:
        printf("\n Relatorio de funcionarios: \n");
        relatorio(lista);
        break;
      case 4:
        printf("\n Consultar funcionario: \n");
        consultar(lista);
        break;
      case 5:
        printf("\n Comparar salarios dos funcionarios com um valor escolhido: \n");
        comparar(lista);
        break;
      case 6:
        printf("\n Relacionar o salario dos funcionarios com o salario minimo: \n");
        relacionar(lista);
        break;
      case 7:
        printf("\n Relatorio do numero de funcionarios por cidade: \n");
        cidade(lista);
        break;
      case 8:
        printf("\n Deletar um funcionario: \n");
        deletar(&lista);
        break;
      case 9:
        printf("\n Importar dados de um arquivo txt \n");
        importa_dados_arquivo_txt(&lista);
        break;
      case 10:
        printf("\n Exportar dados para um arquivo txt \n");
        exporta_dados_arquivo_txt(lista);
        break;
      case 11:
        printf("\n Apaga todos os dados cadastrados \n");
        apaga_todos_os_dados(&lista);
        break;
      case 12:
        printf("\n encerrando programa... \n");
        //salva dados em um arquivo binario
        salva_dados_arquivo_bin(lista);
        varwhile = 0; //quebra o loop
        break;
      default:
        printf("opção inválida. ");
        break;
      }
  }
  return 0;
}

int menu()
{
    int opc;
  
    printf("\n ---------------- MENU ------------------");
    printf("\n 1. Adicionar ficha de funcionario \n");
    printf("\n 2. Atualizar ficha de funcionario \n");
    printf("\n 3. Relatorio de funcionarios \n");
    printf("\n 4. Consultar funcionario \n");
    printf("\n 5. Comparar salarios dos funcionarios \n");
    printf("\n 6. Relacionar o salario dos funcionarios com o salario minimo \n");
    printf("\n 7. Relatorio do numero de funcionarios por cidade \n");
    printf("\n 8. Deletar um funcionario \n");
    printf("\n 9. Importar dados para um arquivo txt \n");
    printf("\n 10. Exportar dados para um arquivo txt \n");
    printf("\n 11. Apaga todos os dados cadastrados \n");
    printf("\n 12. Fechar programa \n"); //quebra o loop
    printf("\n------------------------------------------ \n\n opcao: ");
    scanf("%i", &opc);

  return opc;
}

funcionario* adicionar()
{
  funcionario *no = (funcionario*)malloc(sizeof(funcionario));
  
  if(matricula==N) 
    // impede o usuario de cadastrar mais funcionarios após atingir o limite
  {
    printf("\ndesculpe, jah temos o limite de funcionarios cadastrados!\n");
  }
  else
  {
    matricula++; 
    //adiciona mais um numero na matricula para contar mais um funcionario no sistema.
      getchar();
      printf("\n nome do funcionario: ");
        fgets(no->nome, 50, stdin);
        remove_enter(no->nome);
      printf(" cidade do funcionario: ");
        fgets(no->cidade, 50, stdin);
        remove_enter(no->cidade);
      printf(" dia de nascimento do funcionario: ");
        scanf("%d", &no->aniversario.dia);
      printf(" mes de nascimento do funcionario: ");
        scanf("%d", &no->aniversario.mes);
      printf(" ano de nascimento do funcionario: ");
        scanf("%d", &no->aniversario.ano);
      printf(" salario do funcionario: ");
        scanf("%f", &no->salario);
      printf("\n A matricula de %s eh: %i \n", no->nome, matricula);

      no->prox = NULL;
  }
  return no;
}

void insere_item(funcionario **lista, funcionario *item)
{
  funcionario *aux;
	if (lista_esta_vazia(*lista) == TRUE) 
  {
		*lista = item;
	}
	else 
  {
		aux = *lista;
		while (aux->prox != NULL) 
    {
      aux = aux->prox;
    }
		  aux->prox = item;
	}
}

void atualizar(funcionario* lista)
{
  funcionario* aux = lista;
  string alterar;//ficha a ser alterada
  int varencontrada=0; //variavel que diz se a ficha a ser alterada foi encontrada

  if(aux==NULL)
  {
    printf("\nnao existe nenhum funcionario cadastrado no sistema. \n");
  }
  else
  {
    printf("\n Digite o nome do funcionario que deseja alterar a ficha: ");
    scanf("%s", alterar);

      while(aux!=NULL)
      {
        if(strcmp(alterar, aux->nome) == 0)
        {
          varencontrada++; //valida para dizer se o funcionario foi encontrado
          getchar();
          printf("\n nome do funcionario: ");
            fgets(aux->nome, 50, stdin);
            remove_enter(aux->nome);
          printf(" cidade do funcionario: ");
            fgets(aux->cidade, 50, stdin);
            remove_enter(aux->cidade);
          printf(" dia de nascimento do funcionario: ");
            scanf("%d", &aux->aniversario.dia);
          printf(" mes de nascimento do funcionario: ");
            scanf("%d", &aux->aniversario.mes);
          printf(" ano de nascimento do funcionario: ");
            scanf("%d", &aux->aniversario.ano);
          printf(" salario do funcionario: ");
            scanf("%f", &aux->salario);
          printf("\n ficha do funcionario %s, atualizada!\n", aux->nome);
          return; 
        }
        aux=aux->prox;
      }
      if(varencontrada==0)
      {
        printf("\nfuncionario nao encontrado. ");
      }
  }
  return;
}

void relatorio(funcionario *lista)
{
  funcionario *aux = lista;
  
  //verifica se a lista está vazia
  if(aux==NULL)
  {
    printf("\nnao existe nenhum funcionario cadastrado no sistema. \n");
  }
  else
  {
    while(aux!=NULL)
    {
      //estrutura que extrai a data do sistema
      time_t mytime;
      mytime = time(NULL);
      struct tm tm = *localtime(&mytime);
      int idade = 365*(tm.tm_year + 1900) + 30*(tm.tm_mon + 1) + (tm.tm_mday) - 365*(aux->aniversario.ano) - 30*(aux->aniversario.mes - aux->aniversario.dia);
      
      // imprime a ficha de funcionario por funcionario
      printf("Nome: %s - ", aux->nome);
      printf("Cidade: %s - ", aux->cidade);
  	  printf("Nascimento: %d/%d/%d - ", aux->aniversario.dia, aux->aniversario.mes, aux->aniversario.ano);
      printf("idade: %d anos - ", idade/365);
  	  printf("Salario: %.2f ", aux->salario);
  	  printf("\n");
  	  
  		aux = aux->prox;
    }
  }
}

void consultar(funcionario *lista)
{
  funcionario *aux = lista;
  string buscafunc; //variavel para procurar um funcionario
  int varbusca=0; //variavel de controle de busca encontrada ou não

  if(aux==NULL)
  {
    printf("\nnao existe nenhum funcionario cadastrado no sistema. \n");
  }
  else
  {
    printf("\n por qual funcionario voce procura: ");
    scanf(" %s", buscafunc);

    while(aux!=NULL)
    {
      if(strcmp(aux->nome, buscafunc)==0)
      {
        //estrutura que extrai a data do sistema
        time_t mytime;
        mytime = time(NULL);
        struct tm tm = *localtime(&mytime);
        int idade = 365*(tm.tm_year + 1900) + 30*(tm.tm_mon + 1) + (tm.tm_mday) - 365*(aux->aniversario.ano) - 30*(aux->aniversario.mes - aux->aniversario.dia);
        
        varbusca++; //variavel auxiliar que informa se o funcionario buscado foi encontrado
        printf("\n Funcionario: %s encontrado, segue ficha ", aux->nome);
        printf("\n Cidade: %s  ", aux->cidade);
        printf("\n Nascimento: %i/%i/%i ", aux->aniversario.dia, aux->aniversario.mes, aux->aniversario.ano);
        printf("\n Idade: %d anos - ", idade/365);
        printf("\n Salario: %.2f reais", aux->salario);
      }
      aux=aux->prox;
    }
      if(varbusca==0)
      {
      printf("\nesse funcionario nao consta nos funcionarios cadastrados.");
      }
  }

  return;
}

void comparar(funcionario* lista)
{
  funcionario *aux = lista;
  float scompara; //salario de comparação
  int menor=0; //variaveis contadoras

  if(aux==NULL)
  {
    printf("\nnao existe nenhum funcionario cadastrado no sistema. \n");
  }
  else
  {
    printf("\n Digite um valor para buscar salarios maiores ou iguais: \n::");
    scanf("%f", &scompara);

    while(aux!=NULL)
    {
      if(aux->salario >= scompara)
      {
        printf("\n %s recebe %f", aux->nome, aux->salario);
      }
      else
      {
        menor++;
      }
      aux=aux->prox;
    }
    if(menor==matricula)
    {
      printf("\n nenhum funcionario registrado atualmente tem o salario maior ou igual ao digitado.");
    }
  }
  return;
}

void relacionar(funcionario* lista)
{
  funcionario *aux = lista;
  int sinicial=0, smedio=0, salto=0; //variaveis de contagem dos grupos

  if(matricula==0)
  {
    printf("\nnao existe nenhum funcionario cadastrado no sistema. \n");
  }
  else
  {
     while(aux!=NULL)
    {
      if(aux->salario < salariomin)
      {
        sinicial++;
      }
      if(aux->salario > salariomin && aux->salario < (3 * salariomin))
      {
        smedio++;
      }
      if(aux->salario > (3 * salariomin))
      {
        salto++;
      }
      aux=aux->prox;
    }
    printf("\n %i funcionarios recebem menos de um salario minimo.", sinicial);
    printf("\n %i funcionarios recebem de um salario minimo a tres.", smedio);
    printf("\n %i funcionarios recebem mais de 3 salarios minimos.", salto);
  }

  return;
}

void cidade(funcionario* lista)
{
  funcionario *aux = lista, *i = lista, *j = lista;
  int variguais=0, varanterior=0; //variaveis de controle

  if(lista==NULL)
  {
    printf("\nnao existe nenhum funcionario cadastrado no sistema. \n");
  }
  else
  {
    while(i!=NULL) // fixa um funcionario e compara com os outros
    {
      varanterior = 0; variguais = 0;
      j = lista;
      while(j!=i)// ve se esta cidade já foi contada anteriormente
      {
        if(strcmp(i->cidade, j->cidade)==0)
        {
          varanterior++;
        }
        j=j->prox;
      }
      if(varanterior<1)
      {
        j=i;
        while(j!=NULL) //procura quantas vezes essa cidade foi citada
        {
          if(strcmp(i->cidade, j->cidade)==0)
          {
            variguais++;
          }
          j=j->prox;
        }
        printf("\n %s com %d funcionarios\n", i->cidade, variguais);
      }
      i=i->prox;
    }
  }
  return;
}

void deletar(funcionario** lista)
{
  funcionario *aux, *percorre = *lista; //ponteiro que aponta para o elemento que aponta para 
  string deletar; //variavel contadora e variavel que armazena qual funcionario deletar
  int varencontrada=0; //variavel que indica se o funcionario a ser deletado esta cadastrado

  if((*lista)==NULL)
  {
    printf("\nnao existe nenhum funcionario cadastrado no sistema. \n");
  }
  else
  {
    getchar();
    printf("\n digite o nome do funcionario que deseja deletar a ficha: ");
    fgets(deletar, 50, stdin);
    remove_enter(deletar);
    
      while(percorre!=NULL)
      {
        if(strcmp(deletar, percorre->nome)==0)
        {
          varencontrada++;
          matricula--;
          //verifica se o elemento é o primeiro da lista
          if(percorre->prox == (*lista)->prox)
          {
            funcionario* auxp = (*lista)->prox;
            free(*lista);
            *lista = auxp;
            printf("\nfuncionario deletado!");
            break;
          }
          //verifica se o elemento é o ultimo da lista
          else if(percorre->prox == NULL)
          {
            aux->prox = NULL;
            free(percorre);
            printf("\nfuncionario deletado!");
            break;
          }
          //verifica se é um item valido
          else
          {
            aux->prox = percorre->prox;
            free(percorre);
            printf("\nfuncionario deletado!");
            break;
          }
          printf("\n ficha do funcionario deletada!\n"); 
        }
        aux = percorre;
        percorre=percorre->prox;
      }
        if(varencontrada==0)
        {
        printf("\n funcionario nao encontrado. ");
        }
  }
  return;
}

void apaga_todos_os_dados(funcionario **lista)
{
	funcionario *aux;
	
	while (*lista != NULL) 
  {
		aux = *lista;
		*lista = (*lista)->prox;
		printf("Apagando o item %s\n", aux->nome);		
		free(aux);
	}	
}

void exporta_dados_arquivo_txt(funcionario *lista)
{
	FILE* arq_funcionarios;
  funcionario *aux = lista;
  //abre arquivo texto
  arq_funcionarios = fopen("registro_funcionarios.txt", "w+");
  
  if(arq_funcionarios == NULL)
  {
    printf("não foi possivel abrir o arquivo.\n");
    exit(0);
  }

	while(aux!=NULL) 
  {
    printf("kjsnukfjsd");
		fprintf(arq_funcionarios, "%s\n", aux->nome);
		fprintf(arq_funcionarios, "%s\n", aux->cidade);
		fprintf(arq_funcionarios, "%d\n", aux->aniversario.dia);
    fprintf(arq_funcionarios, "%d\n", aux->aniversario.mes);
    fprintf(arq_funcionarios, "%d\n", aux->aniversario.ano);
		fprintf(arq_funcionarios, "%.2f\n\n", aux->salario);
    aux=aux->prox;
	}
	fclose(arq_funcionarios);
}

void importa_dados_arquivo_txt(funcionario **lista)
{
  if(*lista!=NULL)
  {
    printf("\nvocê não pode importar um arquivo texto porque já existem arquivos cadastrados na base de dados.");
  }
    
  else
  {
    funcionario *aux;
    FILE* arq_funcionarios;
    //abre arquivo texto
    arq_funcionarios = fopen("registro_funcionarios.txt", "a+");
    
    if(arq_funcionarios == NULL)
    {
      printf("não foi possivel abrir o arquivo.\n");
      exit(0);
    }
    //passa os dados do arquivo para o programa
  	while(!feof(arq_funcionarios))
    {
      aux = (funcionario*)malloc(sizeof(funcionario));
      fscanf(arq_funcionarios, "%s\n", aux->nome);
  		fscanf(arq_funcionarios, "%s\n", aux->cidade);
  		fscanf(arq_funcionarios, "%d\n", &aux->aniversario.dia);
      fscanf(arq_funcionarios, "%d\n", &aux->aniversario.mes);
      fscanf(arq_funcionarios, "%d\n", &aux->aniversario.ano);
  		fscanf(arq_funcionarios, "%f\n\n", &aux->salario);
      aux->prox=NULL;
      insere_item(lista, aux);
      matricula++;
  	}
  	fclose(arq_funcionarios);
  }
  
   return;
}

void salva_dados_arquivo_bin(funcionario *lista)
{
  	FILE* arq_funcionarios;
    funcionario *aux = lista;
  //abre arquivo binario
  arq_funcionarios = fopen("base_de_dados", "w+b");
  
  if(arq_funcionarios == NULL)
  {
    printf("ERROR.\n");
    exit(0);
  }
  
  while(aux!= NULL)
  {
  		fwrite(aux->nome, sizeof(string), 1, arq_funcionarios);
  		fwrite(aux->cidade, sizeof(string), 1, arq_funcionarios);
  		fwrite(&aux->aniversario.dia, sizeof(int), 1,arq_funcionarios);
      fwrite(&aux->aniversario.mes, sizeof(int), 1, arq_funcionarios);
      fwrite(&aux->aniversario.ano, sizeof(int), 1, arq_funcionarios);
  		fwrite(&aux->salario, sizeof(float), 1, arq_funcionarios);
      aux=aux->prox;
  	}
  	fclose(arq_funcionarios); 
}

void recupera_dados_arquivo_bin(funcionario **lista)
{ 
  FILE* arq_funcionarios;
  funcionario *aux;
  
    //abre arquivo texto
    arq_funcionarios = fopen("base_de_dados", "a+b");
    
    if(arq_funcionarios == NULL)
    {
      printf("ERROR\n");
      exit(0);
    }

    //passa os dados do arquivo para o programa
  	while(!feof(arq_funcionarios))
    {
      aux = (funcionario*)malloc(sizeof(funcionario));
      fread(aux->nome, sizeof(string), 1, arq_funcionarios);
  		fread(aux->cidade, sizeof(string), 1, arq_funcionarios);
  		fread(&aux->aniversario.dia, sizeof(int), 1,arq_funcionarios);
      fread(&aux->aniversario.mes, sizeof(int), 1, arq_funcionarios);
      fread(&aux->aniversario.ano, sizeof(int), 1, arq_funcionarios);
  		fread(&aux->salario, sizeof(float), 1, arq_funcionarios);
      aux->prox=NULL;
      if (!feof(arq_funcionarios)) 
      {
        matricula++;
        insere_item(lista, aux);
  	  }
      else
      {
        free(aux);
      }
      
  	}
    matricula--;
  	fclose(arq_funcionarios);
}

void remove_enter(char s[N])
{
	int tamanho = strlen(s);
	s[tamanho-1] = '\0';
}

boolean lista_esta_vazia(funcionario *lista)
{
	if (lista == NULL) return TRUE;
	return FALSE;
}