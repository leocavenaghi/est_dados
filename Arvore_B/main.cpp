#include<iostream>
using namespace std;

// classe que representa a p�gina (n� em uma �rvore B)
class BTreeNode
{
    int *keys;  // Array com as chaves da p�gina
    int t;      // ordem da p�gina
    BTreeNode **C; // Array com os ponteiros para as p�ginas filhas
    int n;     // N�mero de chaves na p�gina
    bool leaf; // Flag que indica se a p�gina � folha

public:

    BTreeNode(int _t, bool _leaf);   // Construtor da classe

    // Fun��o para percorrer todas as p�ginas filhas
    void traverse();

    // Fun��o para buscar a chave k nas p�ginas filhas
    BTreeNode *search(int k);   // retorna nulo se a chave n�o est� na �rvore

    // Fun��o para retornar o �ndice da primeira chave maior ou igual � k
    int findKey(int k);

    // Fun��o utilit�ria para inserir uma nova chave na p�gina.
    // function is called
    void insertNonFull(int k);

    // Fun��o para realizar o split (divis�o) do filho y dessa p�gina
    // i � o indice de y no array de filhos
    void splitChild(int i, BTreeNode *y);

    // Fun��o auxiliar para remover a chave k na P�gina ou seus filhos
    void remove(int k);

    // Fun��o para remover chave na posi��o idx da p�gina folha
    void removeFromLeaf(int idx);

    // Fun�ao para remover chave na posi��o idx da p�gina n�o folha
    void removeFromNonLeaf(int idx);

    // Fun��o que pega o antecessor da chave que se encontra na posi��o idx da p�gina
    int getPred(int idx);

    // Fun��o para pegar o sucessor da chave que se encontra na posi��o idx da p�gina
    int getSucc(int idx);

    // Fun��o para preencher o filho apontado pelo ponteiro da posi��o idx
    void fill(int idx);

    // Fun��o para pegar emprestado a chave do filho apontado por idx-1 e colocar no filho apontado
    // por idx
    void borrowFromPrev(int idx);

    // Fun��o para pegar emprestado a chave do filho apontado por idx+1
    // e colocar no filho apontado por idx
    void borrowFromNext(int idx);

    // fun��o para juntar o filho apontado por idx com o filho apontado por idx+1
    void merge(int idx);

    // torna as classes amigas para permitir acesso aos membros privados
    friend class BTree;
};

class BTree
{
    BTreeNode *root; // Pointeiro para raiz
    int t;  // ordem
public:

    // Construtor (inicializa �rvore vazia)
    BTree(int _t)
    {
        root = NULL;
        t = _t;
    }

    void traverse()
    {
        if (root != NULL) root->traverse();
    }

    // fun��o para procurar a chave na �rvore
    BTreeNode* search(int k)
    {
        return (root == NULL)? NULL : root->search(k);
    }

    // Fun��o principal de inser��o
    void insert(int k);

    // fun��o principal de remo��o
    void remove(int k);

};

BTreeNode::BTreeNode(int t1, bool leaf1)
{
    // Inicializa ordem e a flag de folha
    t = t1;
    leaf = leaf1;

    // Aloca mem�ria para o m�ximo de filhos e chaves poss�veis
    keys = new int[2*t-1];
    C = new BTreeNode *[2*t];

    // Inicializa o n�mero de chaves na p�gina
    n = 0;
}

// Fun��o utilit�ria que retorna o indice da primeira chave maior ou igual a k
int BTreeNode::findKey(int k)
{
    int idx=0;
    while (idx<n && keys[idx] < k)
        ++idx;
    return idx;
}

// Fun��o para remover a chave k nas p�ginas filhas da p�gina em quest�o
void BTreeNode::remove(int k)
{
    int idx = findKey(k);

    // Verifica se a chave a ser removida est� nessa p�gina
    if (idx < n && keys[idx] == k)
    {

        // verifica se � um n� folha e chama a fun��o de remo��o respectiva
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    }
    else
    {

        // Chave n�o encontrada na �rvore (n� folha e todas as folhas est�o no mesmo n�vel)
        if (leaf)
        {
            cout << "Chave "<< k <<" nao existe na arvore!\n";
            return;
        }

        // Chave se encontra em um filho da p�gina atual
        // Flag indica se a chave se encontra na �ltima p�gina filha
        bool flag = ( (idx==n)? true : false );

        // Se a p�gina filha onde a chave supostamente se encontra tem menos chaves do que
        // a ordem o a p�gina filha � preenchida
        if (C[idx]->n < t)
            fill(idx);

        // If a �ltima p�gina filha foi agrupada, ela foi agrupada com a filha anterior,
        // ent�o realizamos uma chamada recursiva � (idx-1). Caso contr�rio chamomos
        // recursivamente remo��o na filha idx
        if (flag && idx > n)
            C[idx-1]->remove(k);
        else
            C[idx]->remove(k);
    }
    return;
}

// Fun��o que remove a chave de indice idx da p�gina (n� folha)
void BTreeNode::removeFromLeaf (int idx)
{

    // Desloca todas as chaves depois da chave removida
    for (int i=idx+1; i<n; ++i)
        keys[i-1] = keys[i];

    // Decrementa a quantidade de chaves na p�gina
    n--;
    return;
}

// Fun��o para remover a chave de indice idx da p�gina (n� n�o folha)
void BTreeNode::removeFromNonLeaf(int idx)
{

    int k = keys[idx];

    // If a p�gina filha que precede a chave k tem pelo menos quantidade de chaves
    // igual a ordem, acha a chave predecessora de k na p�gina apontada pelo indice idx.
    // Substitui k por sua prdecessora e remove recursivamente a predecessora na p�gina filha idx
    if (C[idx]->n >= t)
    {
        int pred = getPred(idx);
        keys[idx] = pred;
        C[idx]->remove(pred);
    }

    // Senao, se p�gina filha idx tem menos chaves do que a ordem, olhe para p�gina idx+1.
    // Se p�gina idx+1 tem quantidade de chaves pelo menos igual a ordem, ache a chave sucessora
    // de k nessa p�gina, substitua k pela sua sucessora e delete recursivamente a sucessora na
    // p�gina filha idx+1;
    else if  (C[idx+1]->n >= t)
    {
        int succ = getSucc(idx);
        keys[idx] = succ;
        C[idx+1]->remove(succ);
    }

    // Sen�o, tanto a p�gina filha idx como a idx+1 tem menos chaves do que a ordem, ent�o junte
    // k com as chaves de idx+1 em idx. libere a mem�ria da filha idx+1 e remova k de idx recursivamente.
    else
    {
        merge(idx);
        C[idx]->remove(k);
    }
    return;
}

// Fun��o para pegar o predecessor da chave de indice idx
int BTreeNode::getPred(int idx)
{
    // Olha na dire��o da p�gina filha mais a direita at� achar uma p�gina folha
    BTreeNode *cur=C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];

    // Retorna a �ltima chave desse n� folha
    return cur->keys[cur->n-1];
}

// Fun��o para pegar o sucessor da chave de indice  idx
int BTreeNode::getSucc(int idx)
{

    // olha na dire��o da p�gina filha mais a esquerda�at� achar uma p�gina folha
    BTreeNode *cur = C[idx+1];
    while (!cur->leaf)
        cur = cur->C[0];

    // Retorna a primeira chave dessa p�gina folha
    return cur->keys[0];
}

// Fun��o para preencher p�gina idx com menos chaves do que a ordem -1
void BTreeNode::fill(int idx)
{

    // Se a p�gina idx-1 tem mais que ordem -1 chaves, pegue uma emprestado
    if (idx!=0 && C[idx-1]->n>=t)
        borrowFromPrev(idx);

    // Se a p�gina idx+1 tem mais que ordem -1 chaves, pegue uma emprestado
    else if (idx!=n && C[idx+1]->n>=t)
        borrowFromNext(idx);

    // Sen�o junte p�gina idx com sua irma, se idx � a �ltima filha, junte ela a p�gina anterior
    // caso contr�rio com a pr�xima p�gina
    else
    {
        if (idx != n)
            merge(idx);
        else
            merge(idx-1);
    }
    return;
}

// Fun��o para pegar chave emprestada de idx-1 e inserir em idx
void BTreeNode::borrowFromPrev(int idx)
{

    BTreeNode *child=C[idx];
    BTreeNode *sibling=C[idx-1];

    // �ltima chave da p�gina idx-1 vai para p�gina pai e chave idx-1 do pai vai como primeira chave
    // da pagina idx

    // Movimenta as chaves da p�gina idx um espa�o de mem�ria
    for (int i=child->n-1; i>=0; --i)
        child->keys[i+1] = child->keys[i];

    // if p�gina idx n�o � folha, move os ponteiros para p�ginas filhas
    if (!child->leaf)
    {
        for(int i=child->n; i>=0; --i)
            child->C[i+1] = child->C[i];
    }

    // Atribui primeira chave de idx
    child->keys[0] = keys[idx-1];

    // Move irm�s da �ltima filha (idx-1) como primeira filha de idx
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
// Fun��o para pegar emprestado chave de p�gina idx-1 e coloca-la em p�gina idx
void BTreeNode::borrowFromNext(int idx)
{

    BTreeNode *child=C[idx];
    BTreeNode *sibling=C[idx+1];

    // chave idx inserida como �ltima chave de p�gina idx
    child->keys[(child->n)] = keys[idx];

    // primeira p�gina de p�gina idx+1 inserida como �ltima p�gina de p�gina idx
    if (!(child->leaf))
        child->C[(child->n)+1] = sibling->C[0];

    // primeira chave de idx+1 inserida como chave idx
    keys[idx] = sibling->keys[0];

    // move todas as chaves de p�gina idx+1 um passo atraz
    for (int i=1; i<sibling->n; ++i)
        sibling->keys[i-1] = sibling->keys[i];

    // move ponteiro de filhas um passo atraz se p�gina n�o folha
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

// Fun��o para juntar p�gina idx e p�gina idx+1 liberando mem�ria de idx+1
void BTreeNode::merge(int idx)
{
    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx+1];

    // pega chave de p�gina atual e insere na posi��o t-1 de p�gina idx
    child->keys[t-1] = keys[idx];

    // copiando chaves de p�gina idx+1 para o final de p�gina idx
    for (int i=0; i<sibling->n; ++i)
        child->keys[i+t] = sibling->keys[i];

    // copiando os ponteiros de filhos de p�gina idx+1 para p�gina idx
    if (!child->leaf)
    {
        for(int i=0; i<=sibling->n; ++i)
            child->C[i+t] = sibling->C[i];
    }

    // movendo todas as chaves ap�s chave idx de p�gina atual um passo atraz
    for (int i=idx+1; i<n; ++i)
        keys[i-1] = keys[i];

    // move ponteiros para p�ginas filho depois de idx+1 um passo atraz
    for (int i=idx+2; i<=n; ++i)
        C[i-1] = C[i];

    // atualiza quantidade de chaves de p�gina atual e p�gina idx+1
    child->n += sibling->n+1;
    n--;

    // libera mem�ria de p�gina idx+1
    delete(sibling);
    return;
}

// fun��o principal que insere nova chave na �rvore B
void BTree::insert(int k)
{
    // Se �rvore vazia
    if (root == NULL)
    {
        // aloca memoria para raiz
        root = new BTreeNode(t, true);
        root->keys[0] = k;  // Insere chave k
        root->n = 1;  // atualiza n�mero de chaves na raiz
    }
    else // �rvore n�o vazia
    {
        // Se raiz alcan�ou limite arvore cresce em altura (split)
        if (root->n == 2*t-1)
        {
            // Aloca memoria para nova raiz
            BTreeNode *s = new BTreeNode(t, false);

            // Torna raiz antiga filha da nova raiz
            s->C[0] = root;

            // Realiza split da antiga raiz e move 1 chave para a nova raiz
            s->splitChild(0, root);

            // Nova raiz possui duas p�ginas filhas. Decide qual p�gina possui nova chave k
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);

            // Muda raiz
            root = s;
        }
        else  // se raiz n�o cheia insere na raiz
            root->insertNonFull(k);
    }
}

// Fun�o utilit�ria para inserir chave em p�gina n�o cheia
void BTreeNode::insertNonFull(int k)
{
    // inicializa indice como mais a direita
    int i = n-1;

    // Se � uma p�gina folha
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
    else // Se p�gina n�o folha
    {
        // Acha a p�gina filha onde a chave deve ser inserida
        while (i >= 0 && keys[i] > k)
            i--;

        // Verifica se a p�gina encontrada est� cheia
        if (C[i+1]->n == 2*t-1)
        {
            // Caso esteja realiza o split
            splitChild(i+1, C[i+1]);

            // Ap�s o split a chave intermediaria da p�gina � promovida
            // como chave da p�gina pai e a p�gina pai � dividade em duas
            // Verifica qula das duas novas p�ginas conter� a nova chave
            if (keys[i+1] < k)
                i++;
        }
        C[i+1]->insertNonFull(k);
    }
}

// Fun��o auxiliar para realizar o split na p�gina filha y da p�gina atual
// observe que y deve estar cheia quando essa fun��o � chamada
void BTreeNode::splitChild(int i, BTreeNode *y)
{
    // Cria nova p�gina que armazenar� t-1 chaves de y
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    // copia as �ltima t-1 chaves de y para a nova p�gina (z)
    for (int j = 0; j < t-1; j++)
        z->keys[j] = y->keys[j+t];

    // Copy the last t children of y to z
    // copia as �ltimas t filhas de y para a nova p�gina (z)
    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j+t];
    }

    // atualiza o n�mero de chaves em y
    y->n = t - 1;

    // Como a p�gina atual possui nova filha, cria o espa�o para a mesma
    for (int j = n; j >= i+1; j--)
        C[j+1] = C[j];

    // atualiza o ponteiro para a nova filha (z)
    C[i+1] = z;

    // uma chave de y deve mover para a p�gina atual, ache o local correto e mova as demais chaves
    for (int j = n-1; j >= i; j--)
        keys[j+1] = keys[j];

    // copia a chave intermediaria de y para a p�gina atual
    keys[i] = y->keys[t-1];

    // atualiza a quantidade de chaves na p�gina atual
    n = n + 1;
}

// Fun��o para percorrer todas as subp�ginas da p�gina atual
void BTreeNode::traverse()
{
    // There are n keys and n+1 children, travers through n keys
    // and first n children
    // existem n chaves e n+1 subp�ginas,
    // percorre as n chaves e primeiras n subp�ginas
    int i;
    for (i = 0; i < n; i++)
    {
        // Se essa n�o � uma p�gina folha, imprima a chave i
        // percorra a subp�gina i
        if (leaf == false)
            C[i]->traverse();
        cout << " " << keys[i];
    }

    // imprima a ultima subp�gina
    if (leaf == false)
        C[i]->traverse();
}

// Fun��o para procurar a chave k nas subp�ginas da p�gina atual
BTreeNode *BTreeNode::search(int k)
{
    // Acha a primeira chave maior ou igual � k
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    // se achou a chave retorna a p�gina atual
    if (keys[i] == k)
        return this;

    // se a chave n�o foi encontrada e � um n� folha ela n�o est� na arvore
    if (leaf == true)
        return NULL;

    // vai para a subp�gina correta
    return C[i]->search(k);
}

void BTree::remove(int k)
{
    if (!root)
    {
        cout << "Arvore vazia!\n";
        return;
    }

    // chama a fun��o de remo��o para a raiz
    root->remove(k);

    // se a raiz n�o possui chaves, verifique se possui filhas.
    // se possuir torne a primeira filha como nova raiz, do contr�rio atribua null a raiz
    if (root->n==0)
    {
        BTreeNode *tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->C[0];

        // desaloca a mem�ria da antiga raiz
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
