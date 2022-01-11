**Banco de Dados - Árvore B**
=

## **Instruções e referências para o uso do código**

O algoritmo atual deste repositório foi construído utilizando a linguagem C, através do sistema operacional Windows 11 operando em ambiente Linux (WSL2 - Ubuntu-20.04). A compilação pode ser feita por meio do comando "make" e executado com "make run". O "output" e objetos (*-o) podem ser removidos com "make clean" em caso de algum erro imprevisto com compilações passadas.

## **Funcionamento**

Ao inicializar o programa é feito o carregamento dos arquivos de dados e inserção de itens na árvore bem como a criação de páginas ordenadas, que podem ser localizadas dentro da pasta "organizador" e são provenientes das bases carregadas de nome e cpf. A pasta "organizador" irá funcionar apenas como o recipiente de índices que contém 10 entradas agrupadas das bases originais de nome e CPF. Fazendo uma analogia, ela pode ser vista como um livro de 100 folhas (100 arquivos .txt) que apresentará cada folha com 10 itens em cada (dados dos clientes). Essa é a forma na qual os dados serão armazenados e dispostos nesse processo e a partir disso é possível alcançar o menu e fazer as opções para manipulação das estruturas. O menu conta com inserção, remoção e pesquisa.

### **MENU**
* **Opção 1 (INSERIR)**: incompleta...

* **Opção 2 (REMOVER)**: A remoção é feita a partir de uma pesquisa no diretório para encontrar o CPF correspondente. Encontrado o diretório que contém o CPF, os dados do arquivo com 10 entradas são copiados como backup, armazenados e sobrepostos em um outro arquivo, descartando apenas o cliente desejado.

* ***Opção 3 (PESQUISAR)**: A pesquisa é feita de forma que se encontre o diretório que contém o CPF. Encontrado o diretório que o contém, o arquivo é aberto e é feita a localização da linha referente ao CPF procurado e com isso o nome e idade são também localizados.

* **Opção 0 (SAIR)**: Termina o programa.