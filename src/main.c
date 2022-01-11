#include "btree.h"
#include "lista.h"

void MesclarDados(Lista *l, Pagina **btree);
void pesquisarNoArquivo(char *arquivo, int cpf);
void removerNoArquivo(char *arquivo, int cpf, char *dados);

int main() {
	/*=====================================================
	inicialização e preparação dos arquivos*/
	
	Lista lista;
	FLVazia(&lista);
	Record r;
	Pagina *btree = CreateBTree();
	
	FILE *nome, *cpf, *file;
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
	char *palavras;
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
				// incompleto
				printf("#INSERIR\n");
				break;
			
			case 2:
				printf("#REMOVER\n");
				printf("CPF que deseja remover: ");
				scanf("%d", &r.key);
				Pesquisa(btree, &r);
				// faz a pesquisa, se retornar -1 não foi encontrado
				if (r.key != -1) {
					printf("Diretório -> %s\n", r.nome);
					palavras = (char*)malloc(500 * sizeof(char));
					removerNoArquivo(r.nome, r.key, palavras);
					file = fopen(r.nome, "w");
					if (file != NULL) {
						fputs(palavras, file);
						printf("Cliente removido!\n");
					}
					fclose(file);
				}
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
		// mescla cpf, idade e nome na variável
		strcat(item.aux, texto);
		strcat(item.aux, salvar);
		strcat(item.aux, aux->data.nome);
		
		if (++contador == 10) {
			r.nome = (char*)malloc(50 * sizeof(char));
			y = aux->data.val;
			// nome do arquivo depende do limite inferior e superior do arquivo pois será o índice de procura
			sprintf(str, "src/data/organizador/%d-%d.txt", x, y);

			// cria cada arquivo com 10 entradas de dados
			file = fopen(str, "w");
			if (file != NULL)
				fputs(item.aux, file);
			fclose(file);

			r.key = x;
			r.lim = y;
			strcpy(r.nome, str);
			// insere os intervalos na árvore
			Insere(btree, r);
			item.aux = (char*)malloc(50 * 10 * sizeof(char));
			contador = 0;
		}
		aux = aux->prox;
	}
}

void removerNoArquivo(char *arquivo, int cpf, char *dados) {
	FILE *file;
	char bkp[80];
	int controle = 1;
	char *result, linha[100];
	const char sep[] = "-";
	char *tokens;

	file = fopen(arquivo, "r");

	// abrir arquivos da pesquisa
	if (file == NULL)
		printf("Falha ao abrir arquivo de pesquisa!\n");
	else {
		while (!feof(file)) {
			// monta a linha
			result = fgets(linha, 100, file);
			if (result) {
				strcpy(bkp, linha);
				tokens = strtok(linha, sep);
				while(tokens != NULL) {
					// linha que será desconsiderada no backup para efetuar a remoção
					if (cpf == atoi(tokens)) {
						// variável de controle = 0 para garantir
						controle = 0;
					}
					break;
				}
				// volta o controle para 1 e acaba a cópia dos valores
				if (controle == 1)
					strcat(dados, bkp);
				else
					controle = 1;
			}
		}
	}
	fclose(file);
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
			// monta a linha
			result = fgets(linha, 100, file);
			if (result) {
				tokens = strtok(linha, sep);
				index = 0;
				while(tokens != NULL) {
					// cpf é o primeiro valor no arquivo e por isso index deve ser 0
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
