#include<iostream>
using namespace std;

// classe que representa a página (nó em uma árvore B)
class BTreeNode
{
    int *keys;  // Array com as chaves da página
    int t;      // ordem da página
    BTreeNode **C; // Array com os ponteiros para as páginas filhas
    int n;     // Número de chaves na página
    bool leaf; // Flag que indica se a página é folha

public:

    BTreeNode(int _t, bool _leaf);   // Construtor da classe

    // Função para percorrer todas as páginas filhas
    void traverse();

    // Função para buscar a chave k nas páginas filhas
    BTreeNode *search(int k);   // retorna nulo se a chave não está na árvore

    // Função para retornar o índice da primeira chave maior ou igual à k
    int findKey(int k);

    // Função utilitária para inserir uma nova chave na página.
    // function is called
    void insertNonFull(int k);

    // Função para realizar o split (divisão) do filho y dessa página
    // i é o indice de y no array de filhos
    void splitChild(int i, BTreeNode *y);

    // Função auxiliar para remover a chave k na Página ou seus filhos
    void remove(int k);

    // Função para remover chave na posição idx da página folha
    void removeFromLeaf(int idx);

    // Funçao para remover chave na posição idx da página não folha
    void removeFromNonLeaf(int idx);

    // Função que pega o antecessor da chave que se encontra na posição idx da página
    int getPred(int idx);

    // Função para pegar o sucessor da chave que se encontra na posição idx da página
    int getSucc(int idx);

    // Função para preencher o filho apontado pelo ponteiro da posição idx
    void fill(int idx);

    // Função para pegar emprestado a chave do filho apontado por idx-1 e colocar no filho apontado
    // por idx
    void borrowFromPrev(int idx);

    // Função para pegar emprestado a chave do filho apontado por idx+1
    // e colocar no filho apontado por idx
    void borrowFromNext(int idx);

    // função para juntar o filho apontado por idx com o filho apontado por idx+1
    void merge(int idx);

    // torna as classes amigas para permitir acesso aos membros privados
    friend class BTree;
};

class BTree
{
    BTreeNode *root; // Pointeiro para raiz
    int t;  // ordem
public:

    // Construtor (inicializa árvore vazia)
    BTree(int _t)
    {
        root = NULL;
        t = _t;
    }

    void traverse()
    {
        if (root != NULL) root->traverse();
    }

    // função para procurar a chave na árvore
    BTreeNode* search(int k)
    {
        return (root == NULL)? NULL : root->search(k);
    }

    // Função principal de inserção
    void insert(int k);

    // função principal de remoção
    void remove(int k);

};

BTreeNode::BTreeNode(int t1, bool leaf1)
{
    // Inicializa ordem e a flag de folha
    t = t1;
    leaf = leaf1;

    // Aloca memória para o máximo de filhos e chaves possíveis
    keys = new int[2*t-1];
    C = new BTreeNode *[2*t];

    // Inicializa o número de chaves na página
    n = 0;
}

// Função utilitária que retorna o indice da primeira chave maior ou igual a k
int BTreeNode::findKey(int k)
{
    int idx=0;
    while (idx<n && keys[idx] < k)
        ++idx;
    return idx;
}

// Função para remover a chave k nas páginas filhas da página em questão
void BTreeNode::remove(int k)
{
    int idx = findKey(k);

    // Verifica se a chave a ser removida está nessa página
    if (idx < n && keys[idx] == k)
    {

        // verifica se é um nó folha e chama a função de remoção respectiva
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    }
    else
    {

        // Chave não encontrada na árvore (nó folha e todas as folhas estão no mesmo nível)
        if (leaf)
        {
            cout << "Chave "<< k <<" nao existe na arvore!\n";
            return;
        }

        // Chave se encontra em um filho da página atual
        // Flag indica se a chave se encontra na última página filha
        bool flag = ( (idx==n)? true : false );

        // Se a página filha onde a chave supostamente se encontra tem menos chaves do que
        // a ordem o a página filha é preenchida
        if (C[idx]->n < t)
            fill(idx);

        // If a última página filha foi agrupada, ela foi agrupada com a filha anterior,
        // então realizamos uma chamada recursiva à (idx-1). Caso contrário chamomos
        // recursivamente remoção na filha idx
        if (flag && idx > n)
            C[idx-1]->remove(k);
        else
            C[idx]->remove(k);
    }
    return;
}

// Função que remove a chave de indice idx da página (nó folha)
void BTreeNode::removeFromLeaf (int idx)
{

    // Desloca todas as chaves depois da chave removida
    for (int i=idx+1; i<n; ++i)
        keys[i-1] = keys[i];

    // Decrementa a quantidade de chaves na página
    n--;
    return;
}

// Função para remover a chave de indice idx da página (nó não folha)
void BTreeNode::removeFromNonLeaf(int idx)
{

    int k = keys[idx];

    // If a página filha que precede a chave k tem pelo menos quantidade de chaves
    // igual a ordem, acha a chave predecessora de k na página apontada pelo indice idx.
    // Substitui k por sua prdecessora e remove recursivamente a predecessora na página filha idx
    if (C[idx]->n >= t)
    {
        int pred = getPred(idx);
        keys[idx] = pred;
        C[idx]->remove(pred);
    }

    // Senao, se página filha idx tem menos chaves do que a ordem, olhe para página idx+1.
    // Se página idx+1 tem quantidade de chaves pelo menos igual a ordem, ache a chave sucessora
    // de k nessa página, substitua k pela sua sucessora e delete recursivamente a sucessora na
    // página filha idx+1;
    else if  (C[idx+1]->n >= t)
    {
        int succ = getSucc(idx);
        keys[idx] = succ;
        C[idx+1]->remove(succ);
    }

    // Senão, tanto a página filha idx como a idx+1 tem menos chaves do que a ordem, então junte
    // k com as chaves de idx+1 em idx. libere a memória da filha idx+1 e remova k de idx recursivamente.
    else
    {
        merge(idx);
        C[idx]->remove(k);
    }
    return;
}

// Função para pegar o predecessor da chave de indice idx
int BTreeNode::getPred(int idx)
{
    // Olha na direção da página filha mais a direita até achar uma página folha
    BTreeNode *cur=C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];

    // Retorna a última chave desse nó folha
    return cur->keys[cur->n-1];
}

// Função para pegar o sucessor da chave de indice  idx
int BTreeNode::getSucc(int idx)
{

    // olha na direção da página filha mais a esquerda´até achar uma página folha
    BTreeNode *cur = C[idx+1];
    while (!cur->leaf)
        cur = cur->C[0];

    // Retorna a primeira chave dessa página folha
    return cur->keys[0];
}

// Função para preencher página idx com menos chaves do que a ordem -1
void BTreeNode::fill(int idx)
{

    // Se a página idx-1 tem mais que ordem -1 chaves, pegue uma emprestado
    if (idx!=0 && C[idx-1]->n>=t)
        borrowFromPrev(idx);

    // Se a página idx+1 tem mais que ordem -1 chaves, pegue uma emprestado
    else if (idx!=n && C[idx+1]->n>=t)
        borrowFromNext(idx);

    // Senão junte página idx com sua irma, se idx é a última filha, junte ela a página anterior
    // caso contrário com a próxima página
    else
    {
        if (idx != n)
            merge(idx);
        else
            merge(idx-1);
    }
    return;
}

// Função para pegar chave emprestada de idx-1 e inserir em idx
void BTreeNode::borrowFromPrev(int idx)
{

    BTreeNode *child=C[idx];
    BTreeNode *sibling=C[idx-1];

    // última chave da página idx-1 vai para página pai e chave idx-1 do pai vai como primeira chave
    // da pagina idx

    // Movimenta as chaves da página idx um espaço de memória
    for (int i=child->n-1; i>=0; --i)
        child->keys[i+1] = child->keys[i];

    // if página idx não é folha, move os ponteiros para páginas filhas
    if (!child->leaf)
    {
        for(int i=child->n; i>=0; --i)
            child->C[i+1] = child->C[i];
    }

    // Atribui primeira chave de idx
    child->keys[0] = keys[idx-1];

    // Move irmãs da última filha (idx-1) como primeira filha de idx
    if (!leaf)
        child->C[0] = sibling->C[sibling->n];

    // Move chave da irma para o pai
    keys[idx-1] = sibling->keys[sibling->n-1];

    child->n += 1;
    sibling->n -= 1;

    return;
}

// A function to borrow a key from the C[idx+1] and place
// it in C[idx]
// Função para pegar emprestado chave de página idx-1 e coloca-la em página idx
void BTreeNode::borrowFromNext(int idx)
{

    BTreeNode *child=C[idx];
    BTreeNode *sibling=C[idx+1];

    // chave idx inserida como última chave de página idx
    child->keys[(child->n)] = keys[idx];

    // primeira página de página idx+1 inserida como última página de página idx
    if (!(child->leaf))
        child->C[(child->n)+1] = sibling->C[0];

    // primeira chave de idx+1 inserida como chave idx
    keys[idx] = sibling->keys[0];

    // move todas as chaves de página idx+1 um passo atraz
    for (int i=1; i<sibling->n; ++i)
        sibling->keys[i-1] = sibling->keys[i];

    // move ponteiro de filhas um passo atraz se página não folha
    if (!sibling->leaf)
    {
        for(int i=1; i<=sibling->n; ++i)
            sibling->C[i-1] = sibling->C[i];
    }

    // ajusta os contadores de chaves de idx e idx+1
    child->n += 1;
    sibling->n -= 1;

    return;
}

// Função para juntar página idx e página idx+1 liberando memória de idx+1
void BTreeNode::merge(int idx)
{
    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx+1];

    // pega chave de página atual e insere na posição t-1 de página idx
    child->keys[t-1] = keys[idx];

    // copiando chaves de página idx+1 para o final de página idx
    for (int i=0; i<sibling->n; ++i)
        child->keys[i+t] = sibling->keys[i];

    // copiando os ponteiros de filhos de página idx+1 para página idx
    if (!child->leaf)
    {
        for(int i=0; i<=sibling->n; ++i)
            child->C[i+t] = sibling->C[i];
    }

    // movendo todas as chaves após chave idx de página atual um passo atraz
    for (int i=idx+1; i<n; ++i)
        keys[i-1] = keys[i];

    // move ponteiros para páginas filho depois de idx+1 um passo atraz
    for (int i=idx+2; i<=n; ++i)
        C[i-1] = C[i];

    // atualiza quantidade de chaves de página atual e página idx+1
    child->n += sibling->n+1;
    n--;

    // libera memória de página idx+1
    delete(sibling);
    return;
}

// função principal que insere nova chave na árvore B
void BTree::insert(int k)
{
    // Se árvore vazia
    if (root == NULL)
    {
        // aloca memoria para raiz
        root = new BTreeNode(t, true);
        root->keys[0] = k;  // Insere chave k
        root->n = 1;  // atualiza número de chaves na raiz
    }
    else // árvore não vazia
    {
        // Se raiz alcançou limite arvore cresce em altura (split)
        if (root->n == 2*t-1)
        {
            // Aloca memoria para nova raiz
            BTreeNode *s = new BTreeNode(t, false);

            // Torna raiz antiga filha da nova raiz
            s->C[0] = root;

            // Realiza split da antiga raiz e move 1 chave para a nova raiz
            s->splitChild(0, root);

            // Nova raiz possui duas páginas filhas. Decide qual página possui nova chave k
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);

            // Muda raiz
            root = s;
        }
        else  // se raiz não cheia insere na raiz
            root->insertNonFull(k);
    }
}

// Funão utilitária para inserir chave em página não cheia
void BTreeNode::insertNonFull(int k)
{
    // inicializa indice como mais a direita
    int i = n-1;

    // Se é uma página folha
    if (leaf == true)
    {
        // Acha local onde nova chave deve ser inserida
        // Move todas as chaves maiores um passo
        while (i >= 0 && keys[i] > k)
        {
            keys[i+1] = keys[i];
            i--;
        }

        // Insere nova chave em seu local mantendo ordem
        keys[i+1] = k;
        n = n+1;
    }
    else // Se página não folha
    {
        // Acha a página filha onde a chave deve ser inserida
        while (i >= 0 && keys[i] > k)
            i--;

        // Verifica se a página encontrada está cheia
        if (C[i+1]->n == 2*t-1)
        {
            // Caso esteja realiza o split
            splitChild(i+1, C[i+1]);

            // Após o split a chave intermediaria da página é promovida
            // como chave da página pai e a página pai é dividade em duas
            // Verifica qula das duas novas páginas conterá a nova chave
            if (keys[i+1] < k)
                i++;
        }
        C[i+1]->insertNonFull(k);
    }
}

// Função auxiliar para realizar o split na página filha y da página atual
// observe que y deve estar cheia quando essa função é chamada
void BTreeNode::splitChild(int i, BTreeNode *y)
{
    // Cria nova página que armazenará t-1 chaves de y
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    // copia as última t-1 chaves de y para a nova página (z)
    for (int j = 0; j < t-1; j++)
        z->keys[j] = y->keys[j+t];

    // Copy the last t children of y to z
    // copia as últimas t filhas de y para a nova página (z)
    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j+t];
    }

    // atualiza o número de chaves em y
    y->n = t - 1;

    // Como a página atual possui nova filha, cria o espaço para a mesma
    for (int j = n; j >= i+1; j--)
        C[j+1] = C[j];

    // atualiza o ponteiro para a nova filha (z)
    C[i+1] = z;

    // uma chave de y deve mover para a página atual, ache o local correto e mova as demais chaves
    for (int j = n-1; j >= i; j--)
        keys[j+1] = keys[j];

    // copia a chave intermediaria de y para a página atual
    keys[i] = y->keys[t-1];

    // atualiza a quantidade de chaves na página atual
    n = n + 1;
}

// Função para percorrer todas as subpáginas da página atual
void BTreeNode::traverse()
{
    // There are n keys and n+1 children, travers through n keys
    // and first n children
    // existem n chaves e n+1 subpáginas,
    // percorre as n chaves e primeiras n subpáginas
    int i;
    for (i = 0; i < n; i++)
    {
        // Se essa não é uma página folha, imprima a chave i
        // percorra a subpágina i
        if (leaf == false)
            C[i]->traverse();
        cout << " " << keys[i];
    }

    // imprima a ultima subpágina
    if (leaf == false)
        C[i]->traverse();
}

// Função para procurar a chave k nas subpáginas da página atual
BTreeNode *BTreeNode::search(int k)
{
    // Acha a primeira chave maior ou igual à k
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    // se achou a chave retorna a página atual
    if (keys[i] == k)
        return this;

    // se a chave não foi encontrada e é um nó folha ela não está na arvore
    if (leaf == true)
        return NULL;

    // vai para a subpágina correta
    return C[i]->search(k);
}

void BTree::remove(int k)
{
    if (!root)
    {
        cout << "Arvore vazia!\n";
        return;
    }

    // chama a função de remoção para a raiz
    root->remove(k);

    // se a raiz não possui chaves, verifique se possui filhas.
    // se possuir torne a primeira filha como nova raiz, do contrário atribua null a raiz
    if (root->n==0)
    {
        BTreeNode *tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->C[0];

        // desaloca a memória da antiga raiz
        delete tmp;
    }
    return;
}


int main()
{
    BTree t(3); // Arvore B de ordem 3

    t.insert(1);
    t.insert(3);
    t.insert(7);
    t.insert(10);
    t.insert(11);
    t.insert(13);
    t.insert(14);
    t.insert(15);
    t.insert(18);
    t.insert(16);
    t.insert(19);
    t.insert(24);
    t.insert(25);
    t.insert(26);
    t.insert(21);
    t.insert(4);
    t.insert(5);
    t.insert(20);
    t.insert(22);
    t.insert(2);
    t.insert(17);
    t.insert(12);
    t.insert(6);

    cout << "Percurso da arvore construida e:\n";
    t.traverse();
    cout << endl;

    t.remove(6);
    cout << "Percurso da arvore apos remover 6:\n";
    t.traverse();
    cout << endl;

    t.remove(13);
    cout << "Percurso da arvore apos remover 13:\n";
    t.traverse();
    cout << endl;

    t.remove(7);
    cout << "Percurso da arvore apos remover 7:\n";
    t.traverse();
    cout << endl;

    t.remove(4);
    cout << "Percurso da arvore apos remover 4:\n";
    t.traverse();
    cout << endl;

    t.remove(2);
    cout << "Percurso da arvore apos remover 2:\n";
    t.traverse();
    cout << endl;

    t.remove(16);
    cout << "Percurso da arvore apos remover 16:\n";
    t.traverse();
    cout << endl;

    return 0;
}
