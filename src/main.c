#include "btree.h"
#include "lista.h"

void MesclarDados(Lista *l, Pagina **btree);
void pesquisarNoArquivo(char *arquivo, int cpf);

int main() {
	/*=====================================================
	inicialização e preparação dos arquivos*/
	
	Lista lista;
	FLVazia(&lista);
	Record r;
	Pagina *btree = CreateBTree();
	
	FILE *nome, *cpf;
	char *result, linha[100];
	int cpfs[1000];

	cpf = fopen("src/data/cpf.txt", "r");
	nome = fopen("src/data/nome.txt", "r");
	int index = 0;

	// abrir arquivos com CPF
	if (cpf == NULL)
		printf("Falha ao abrir banco de CPF!\n");
	else {
		while (!feof(cpf)) {
			result = fgets(linha, 100, cpf);
			if (result) {
				cpfs[index++] = atoi(linha);
			}
		}
	}
	
	// abrir arquivos com nomes
	if (nome == NULL)
		printf("Falha ao abrir banco de NOMES!\n");
	else {
		Item item;
		index = 0;
		while (!feof(nome)) {
			result = fgets(linha, 100, nome);
			if (result) {
				item.nome = (char*)malloc(50 * sizeof(char));
				item.val = cpfs[index++];
				strcpy(item.nome, linha);
				LInsert(&lista, item);
			}
		}
	}
	fclose(cpf);
	fclose(nome);

	// mescla nomes, cpfs e idades e armazena nas páginas para B-Tree
	MesclarDados(&lista, &btree);
	/*=====================================================*/

	// menu
	int opcao;
	do {
		printf("\nMENU\n");
		printf("1 - INSERIR\n");
		printf("2 - REMOVER\n");
		printf("3 - PESQUISAR\n");
		printf("0 - SAIR\n");
		printf("Opção: ");
		scanf("%d", &opcao);

		switch (opcao) {
			case 1:
				printf("#INSERIR\n");
				break;
			
			case 2:
				printf("#REMOVER\n");
				// lerArquivo(r.nome, r.key);
				remove(r.nome);
				break;

			case 3:
				printf("#PESQUISA\n");
				printf("CPF que deseja pesquisar: ");
				scanf("%d", &r.key);
				Pesquisa(btree, &r);
				if (r.key != -1) {
					printf("Diretório -> %s\nCliente: ", r.nome);
					pesquisarNoArquivo(r.nome, r.key);
				}
				break;
			
			case 0:
				printf("SAIR\n");
				break;
		
			default:
				printf("OPÇÃO INVÁLIDA\n");
				break;
		}
	} while (opcao != 0);
	return 0;
}

void MesclarDados(Lista *l, Pagina **btree) {
	Record r;
	Item item;
	Block *aux;
	FILE *file;

	int contador = 0;
	int x = 0, y = 0;
	char salvar[25];
	char texto[25];
	char *str = (char*)malloc(20 * sizeof(char));
	item.aux  = (char*)malloc(50 * 10 * sizeof(char)); //recebe tudo

	aux = l->first->prox;
	while(aux != NULL) {
		if (contador == 0) 
			x = aux->data.val;

		sprintf(texto, "%d-", aux->data.val); // cpf
		sprintf(salvar, "%d-", 12 + (rand() % 90)); // idade
		strcat(item.aux, texto);
		strcat(item.aux, salvar);
		strcat(item.aux, aux->data.nome);
		
		if (++contador == 10) {
			r.nome = (char*)malloc(50 * sizeof(char));
			y = aux->data.val;
			sprintf(str, "src/data/organizador/%d-%d.txt", x, y);

			file = fopen(str, "w");
			if (file != NULL)
				fputs(item.aux, file);
			fclose(file);

			r.key = x;
			r.lim = y;
			strcpy(r.nome, str);
			Insere(btree, r);
			item.aux = (char*)malloc(50 * 10 * sizeof(char)); //recebe tudo
			contador = 0;
		}

		aux = aux->prox;
	}
}

void pesquisarNoArquivo(char *arquivo, int cpf) {
	FILE *file;
	int index = 0;
	char *result, linha[100];
	const char sep[] = "-";
	char *tokens;

	file = fopen(arquivo, "r");

	// abrir arquivos da pesquisa
	if (file == NULL)
		printf("Falha ao abrir arquivo de pesquisa!\n");
	else {
		while (!feof(file)) {
			result = fgets(linha, 100, file);
			if (result) {
				tokens = strtok(linha, sep);
				index = 0;
				while(tokens != NULL) {
					if (cpf != atoi(tokens) && index == 0) {
						break;
					}
					printf(" %s", tokens);
					tokens = strtok(NULL, sep);
					index++;
				}
			}
		}
	}
	fclose(file);
}
