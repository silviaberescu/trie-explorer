#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

#define MAX_LEN 100

// Function to initialize a new tree node
Tree initTree(char litera)
{
    Tree tree = (Tree)malloc(sizeof(Node));
    tree->value = litera;
    for (int i = 0; i < MAX; i++)
    {
        tree->children[i] = NULL;
    }
    return tree;
}
// Function to recursively destroy a tree
void destroyTree(Tree tree)
{
    if (tree == NULL)
    {
        return;
    }
    for (int i = 0; i < MAX; i++)
    {
        destroyTree(tree->children[i]);
    }
    free(tree);
}
// Function to initialize a compact tree node
CTree initCTree(char *sir)
{
    CTree compact_tree = (CTree)malloc(sizeof(CNode));
    compact_tree->value = (char *)malloc(sizeof(char) * (strlen(sir) + 1));
    strcpy(compact_tree->value, sir);
    for (int i = 0; i < MAX; i++)
    {
        compact_tree->children[i] = NULL;
    }
    return compact_tree;
}
// Function to recursively destroy a compact tree
void destroyCTree(CTree compact)
{
    if (compact == NULL)
    {
        return;
    }
    for (int i = 0; i < MAX; i++)
    {
        destroyCTree(compact->children[i]);
    }
    free(compact->value);
    free(compact);
}

// Function to insert a child node into a tree
Tree insertChild(Tree tree, char value)
{
    if (tree == NULL)
        return initTree('\0');
    int index = (int)value - 97 + 1; // Determine the index for the child array
    // If the child at the calculated index is NULL, create a new child
    if (tree->children[index] == NULL)
    {
        Tree node = initTree(value);
        tree->children[index] = node;
        return tree;
    }
    return tree;
}
// Function to insert a word into the tree
Tree insertWord(Tree tree, char *word, int index)
{
    if (index == strlen(word))
    {
        return tree;
    }

    if (index == (strlen(word) - 1))
    { // daca se ajunge la finalul wordului
        if (tree->children[0] == NULL)
        { // se adaugă un copil cu valoarea $
            Tree node = initTree('$');
            tree->children[0] = node;
            return tree;
        }
        return tree;
    }

    Tree child = tree->children[(int)word[index] - 97 + 1];
    if (child == NULL)
    {
        tree = insertChild(tree, word[index]);
        child = tree->children[(int)word[index] - 97 + 1];
    }
    child = insertWord(child, word, index + 1);
    return tree;
}
// Function to get the suffix of a word starting from a specified index
char *getSuffix(char *word, int index)
{
    char *suffix = (char *)malloc((strlen(word) - index + 1) * sizeof(char)); // +1 pentru terminatorul null
    int suffixIndex = 0;
    for (int i = index; i < strlen(word); i++)
    {
        suffix[suffixIndex] = word[i];
        suffixIndex++;
    }
    suffix[suffixIndex] = '\0'; // Termină sufixul
    return suffix;
}
// Function to print the tree level by level
void print_tree(Tree tree, FILE *fout)
{
    if (tree == NULL)
        return;
    Queue *queue = createQueue();
    for (int i = 0; i < MAX; i++)
    {
        if (tree->children[i] != NULL)
        {
            enqueue(queue, tree->children[i]);
        }
    }
    while (!isEmpty(queue))
    {
        int size = queue->size;
        for (int i = 0; i < size; i++)
        {
            Tree tmp = queue->front->elem;
            fprintf(fout, "%c ", tmp->value);
            dequeue(queue);
            for (int j = 0; j < MAX; j++)
            {
                if (tmp->children[j] != NULL)
                {
                    enqueue(queue, tmp->children[j]);
                }
            }
        }
        fprintf(fout, "\n");
    }
    destroyQueue(queue);
}
// Function to count the number of leaf nodes in the tree
int number_leaves(Tree tree)
{
    if (tree == NULL)
        return 0;
    Queue *queue = createQueue();
    int cnt = 0;
    for (int i = 0; i < MAX; i++)
    {
        if (tree->children[i] != NULL)
        {
            enqueue(queue, tree->children[i]);
        }
    }
    while (!isEmpty(queue))
    {
        int size = queue->size; // Numărul de noduri pe nivelul curent
        for (int i = 0; i < size; i++)
        {
            Tree tmp = queue->front->elem;
            if (tmp->value == '$')
                cnt++;
            dequeue(queue);
            for (int j = 0; j < MAX; j++)
            {
                if (tmp->children[j] != NULL)
                {
                    enqueue(queue, tmp->children[j]);
                }
            }
        }
    }
    destroyQueue(queue);
    return cnt;
}
// Function to count the maximum number of descendants for any node in the tree
int nr_max_descendents(Tree tree)
{
    int max_desc = 0;
    if (tree == NULL)
        return 0;
    Queue *queue = createQueue();
    enqueue(queue, tree);
    while (!isEmpty(queue))
    {
        int size = queue->size; // Numărul de noduri pe nivelul curent
        for (int i = 0; i < size; i++)
        {
            Tree tmp = queue->front->elem;
            dequeue(queue);
            int cnt = 0;
            for (int k = 0; k < MAX; k++)
            {
                if (tmp->children[k] != NULL)
                {
                    cnt++;
                    enqueue(queue, tmp->children[k]);
                }
            }
            if (cnt > max_desc)
            {
                max_desc = cnt;
            }
        }
    }
    destroyQueue(queue);
    return max_desc;
}
// Function to count the number of suffixes in the tree of a given length k
int number_sufixes(Tree tree, int k)
{
    if (tree == NULL)
        return 0;
    if (k == 0 && tree->children[0] != NULL)
        return 1;
    int count = 0;
    if (tree->value == '$')
        return 0;
    for (int i = 0; i < MAX; i++)
    {
        if (tree->children[i] != NULL)
        {
            count += number_sufixes(tree->children[i], k - 1);
        }
    }
    return count;
}
// Function to check if a given suffix exists in the tree
int check_sufix(Tree tree, char *sufix)
{
    Tree tmp = tree;
    int i;
    for (i = 0; i < strlen(sufix) - 1; i++)
    {
        // If the child node for the current character does not exist, the suffix is not found
        if (tmp->children[sufix[i] - 97 + 1] == NULL)
        {
            return 0;
        }
        tmp = tmp->children[sufix[i] - 97 + 1];
    }
    // Check if the last character of the suffix is a terminal marker ('$')
    if (i == strlen(sufix) - 1 && tmp->children[0] != NULL)
        return 1;
    else
        return 0;
}
// Function to compact the tree into a more efficient structure
CTree compact_tree(Tree tree, CTree cTree)
{
    Tree tmp = tree;
    if (tree == NULL)
    {
        return NULL;
    }

    if (cTree == NULL)
    {
        cTree = initCTree("\0");
    }

    // Count the number of non-null child nodes
    int cnt = 0, aux = -1;
    for (int i = 0; i < MAX; i++)
    {
        if (tmp->children[i] != NULL)
        {
            cnt++;
            aux = i;
        }
    }
    if (cnt == 0)
    {
        return cTree;
    }

    // If there's only one child and it's not the terminal marker
    if (tmp->children[0] == NULL && cnt == 1)
    {
        cTree->value = (char *)realloc(cTree->value, sizeof(char) * (strlen(cTree->value) + 2));
        char ch = tmp->children[aux]->value;
        char str[2];
        str[0] = ch;
        str[1] = '\0';
        strcat(cTree->value, str);
        compact_tree(tmp->children[aux], cTree); // Recur for the child
    }

    // If the only child is the terminal marker
    if (tmp->children[0] != NULL && cnt == 1)
    {
        char str[2];
        str[0] = '$';
        str[1] = '\0';
        cTree->children[0] = initCTree(str);
        compact_tree(tmp->children[0], cTree->children[0]);
    }

    // If there are multiple children
    if (cnt > 1)
    {
        for (int i = 0; i < MAX; i++)
        { // Iterate over all possible children
            if (tree->children[i] != NULL)
            {
                if (cTree->children[i] == NULL)
                {
                    char ch = tree->children[i]->value;
                    char str[2];
                    str[0] = ch;
                    str[1] = '\0';
                    cTree->children[i] = initCTree(str);
                }
                compact_tree(tree->children[i], cTree->children[i]);
            }
        }
    }
    return cTree;
}
// Function to display the compact tree level by level
void print_compact_tree(CTree compact, FILE *fout)
{
    if (compact == NULL)
        return;
    Queue2 *queue = createQueue2(); // Create a queue for level order traversal
    for (int i = 0; i < MAX; i++)
    {
        if (compact->children[i] != NULL)
        {
            enqueue2(queue, compact->children[i]);
        }
    }
    while (!isEmpty2(queue))
    {
        int size = queue->size;
        for (int i = 0; i < size; i++)
        {
            CTree tmp = queue->front->elem;
            fprintf(fout, "%s ", tmp->value);
            dequeue2(queue);
            for (int j = 0; j < MAX; j++)
            {
                if (tmp->children[j] != NULL)
                {
                    enqueue2(queue, tmp->children[j]);
                }
            }
        }
        fprintf(fout, "\n"); // Move to the next level by printing a newline
    }
    destroyQueue2(queue);
}

// Main function to handle command-line arguments and execute corresponding functionalities

int main(int argc, char *argv[])
{
    char *cerinta = argv[1]; // Command line argument for operation type
    int N = 0, M = 0;

    // Case 1: Insert words and display tree level by level
    if (strcmp(cerinta, "-c1") == 0)
    {
        char *input_file = argv[2];  // Input file containing words
        char *output_file = argv[3]; // Output file for displaying the tree

        FILE *fin = fopen(input_file, "r");
        if (fin == NULL)
        {
            printf("The file could not be opened.\n");
            return 1;
        }

        FILE *fout = fopen(output_file, "w");
        if (fout == NULL)
        {
            printf("The file could not be opened.\n");
            return 1;
        }

        fscanf(fin, "%d", &N);
        fgetc(fin);

        char word[MAX_LEN]; // Buffer for reading each word

        Tree tree = initTree('\0'); // Initialize the tree

        for (int i = 0; i < N; i++)
        {
            fgets(word, sizeof(word), fin);
            word[strlen(word) - 1] = '\0';
            strcat(word, "$"); // Append terminal marker to the word
            for (int index = strlen(word) - 1; index >= 0; index--)
            {
                char *sufix;
                sufix = getSuffix(word, index);
                tree = insertWord(tree, sufix, 0);
                free(sufix);
            }
        }
        print_tree(tree, fout);
        destroyTree(tree);
        fclose(fin);
        fclose(fout);
    }
    // Case 2: Count and output various statistics of the tree
    else if (strcmp(cerinta, "-c2") == 0)
    {
        int K = atoi(argv[2]);
        char *input_file = argv[3];
        char *output_file = argv[4];

        FILE *fin = fopen(input_file, "r");
        if (fin == NULL)
        {
            printf("The file could not be opened.\n");
            return 1;
        }

        FILE *fout = fopen(output_file, "w");
        if (fout == NULL)
        {
            printf("The file could not be opened.\n");
            return 1;
        }

        fscanf(fin, "%d", &N);
        fgetc(fin);

        char word[MAX_LEN];

        Tree tree = initTree('\0');
        for (int i = 0; i < N; i++)
        {
            fgets(word, sizeof(word), fin);
            word[strlen(word) - 1] = '\0';
            strcat(word, "$");
            for (int index = strlen(word) - 1; index >= 0; index--)
            {
                char *sufix;
                sufix = getSuffix(word, index);
                tree = insertWord(tree, sufix, 0);
                free(sufix);
            }
        }

        // Output the statistics to the output file
        fprintf(fout, "%d\n", number_leaves(tree));
        fprintf(fout, "%d\n", number_sufixes(tree, K));
        fprintf(fout, "%d\n", nr_max_descendents(tree));
        destroyTree(tree);
        fclose(fin);
        fclose(fout);
    }
    // Case 3: Check if specific suffixes exist
    else if (strcmp(cerinta, "-c3") == 0)
    {
        char *input_file = argv[2];
        char *output_file = argv[3];

        FILE *fin = fopen(input_file, "r");
        if (fin == NULL)
        {
            printf("The file could not be opened.\n");
            return 1;
        }

        FILE *fout = fopen(output_file, "w");
        if (fout == NULL)
        {
            printf("The file could not be opened.\n");
            return 1;
        }

        fscanf(fin, "%d", &N);
        fgetc(fin);
        fscanf(fin, "%d", &M);
        fgetc(fin);

        char word[MAX_LEN], sufix[MAX_LEN]; // Buffers for words and suffixes
        Tree tree = initTree('\0');

        for (int i = 0; i < N; i++)
        {
            fgets(word, sizeof(word), fin);
            word[strlen(word) - 1] = '\0';
            strcat(word, "$");
            for (int index = strlen(word) - 1; index >= 0; index--)
            {
                char *sufix;
                sufix = getSuffix(word, index);
                tree = insertWord(tree, sufix, 0);
                free(sufix);
            }
        }

        // Loop to read each suffix query and check for its existence in the tree
        for (int i = 0; i < M; i++)
        {
            fgets(sufix, sizeof(sufix), fin);
            sufix[strlen(sufix) - 1] = '\0';
            strcat(sufix, "$");
            fprintf(fout, "%d\n", check_sufix(tree, sufix));
        }

        destroyTree(tree);
        fclose(fin);
        fclose(fout);
    }
    // Case 4: Compact the tree and display it
    else if (strcmp(cerinta, "-c4") == 0)
    {
        char *input_file = argv[2];
        char *output_file = argv[3];

        FILE *fin = fopen(input_file, "r");
        if (fin == NULL)
        {
            printf("The file could not be opened.\n");
            return 1;
        }

        FILE *fout = fopen(output_file, "w");
        if (fout == NULL)
        {
            printf("The file could not be opened.\n");
            return 1;
        }

        fscanf(fin, "%d", &N);
        fgetc(fin);

        char word[MAX_LEN];
        Tree tree = initTree('\0');
        CTree cTree = initCTree("\0"); // Initialize the compact tree

        for (int i = 0; i < N; i++)
        {
            fgets(word, sizeof(word), fin);
            word[strlen(word) - 1] = '\0';
            strcat(word, "$");
            for (int index = strlen(word) - 1; index >= 0; index--)
            {
                char *sufix;
                sufix = getSuffix(word, index);
                tree = insertWord(tree, sufix, 0);
                free(sufix);
            }
        }
        cTree = compact_tree(tree, cTree);
        print_compact_tree(cTree, fout);
        destroyTree(tree);
        destroyCTree(cTree);
        fclose(fin);
        fclose(fout);
    }
    // Handle invalid option case
    else
    {
        printf("Invalid option!\n");
    }
    return 0;
}