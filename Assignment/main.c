#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ============================================
   1. LINEAR DATA STRUCTURES
   ============================================ */

/* 1.1 Array - Static/Fixed Size */
typedef struct {
    int elements[100];
    int size;
} Array;

void array_display(Array *arr) {
    printf("Array: ");
    for (int i = 0; i < arr->size; i++) {
        printf("%d ", arr->elements[i]);
    }
    printf("\n");
}

/* 1.2 Linked List - Dynamic Size */
typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} LinkedList;

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void linkedlist_insert(LinkedList *list, int data) {
    Node *newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node *temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void linkedlist_display(LinkedList *list) {
    printf("Linked List: ");
    Node *temp = list->head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

/* 1.3 Stack - LIFO (Last In First Out) */
typedef struct {
    int elements[100];
    int top;
} Stack;

void stack_push(Stack *stack, int data) {
    if (stack->top < 99) {
        stack->elements[++stack->top] = data;
    }
}

int stack_pop(Stack *stack) {
    if (stack->top >= 0) {
        return stack->elements[stack->top--];
    }
    return -1;
}

void stack_display(Stack *stack) {
    printf("Stack (top to bottom): ");
    for (int i = stack->top; i >= 0; i--) {
        printf("%d ", stack->elements[i]);
    }
    printf("\n");
}

/* 1.4 Queue - FIFO (First In First Out) */
typedef struct {
    int elements[100];
    int front;
    int rear;
    int size;
} Queue;

void queue_enqueue(Queue *queue, int data) {
    if (queue->size < 100) {
        queue->elements[queue->rear] = data;
        queue->rear = (queue->rear + 1) % 100;
        queue->size++;
    }
}

int queue_dequeue(Queue *queue) {
    if (queue->size > 0) {
        int data = queue->elements[queue->front];
        queue->front = (queue->front + 1) % 100;
        queue->size--;
        return data;
    }
    return -1;
}

void queue_display(Queue *queue) {
    printf("Queue (front to rear): ");
    int idx = queue->front;
    for (int i = 0; i < queue->size; i++) {
        printf("%d ", queue->elements[idx]);
        idx = (idx + 1) % 100;
    }
    printf("\n");
}

/* ============================================
   2. NON-LINEAR DATA STRUCTURES
   ============================================ */

/* 2.1 Tree - Binary Tree Node */
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* tree_createNode(int data) {
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TreeNode* tree_insert(TreeNode *root, int data) {
    if (root == NULL) {
        return tree_createNode(data);
    }
    if (data < root->data) {
        root->left = tree_insert(root->left, data);
    } else {
        root->right = tree_insert(root->right, data);
    }
    return root;
}

void tree_inorder(TreeNode *root) {
    if (root != NULL) {
        tree_inorder(root->left);
        printf("%d ", root->data);
        tree_inorder(root->right);
    }
}

void tree_display(TreeNode *root) {
    printf("Binary Search Tree (In-order): ");
    tree_inorder(root);
    printf("\n");
}

/* 2.2 Graph - Adjacency List Representation */
typedef struct GraphNode {
    int vertex;
    struct GraphNode *next;
} GraphNode;

typedef struct {
    GraphNode **adjList;
    int numVertices;
} Graph;

Graph* graph_create(int numVertices) {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->adjList = (GraphNode**)malloc(numVertices * sizeof(GraphNode*));
    for (int i = 0; i < numVertices; i++) {
        graph->adjList[i] = NULL;
    }
    return graph;
}

void graph_addEdge(Graph *graph, int src, int dest) {
    GraphNode *newNode = (GraphNode*)malloc(sizeof(GraphNode));
    newNode->vertex = dest;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

void graph_display(Graph *graph) {
    printf("Graph (Adjacency List):\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("Vertex %d: ", i);
        GraphNode *temp = graph->adjList[i];
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

/* ============================================
   3. HASH-BASED DATA STRUCTURES
   ============================================ */

/* 3.1 Hash Table */
#define HASH_SIZE 10

typedef struct {
    int key;
    int value;
} HashEntry;

typedef struct {
    HashEntry **table;
    int size;
} HashTable;

int hash_function(int key) {
    return key % HASH_SIZE;
}

HashTable* hashtable_create() {
    HashTable *ht = (HashTable*)malloc(sizeof(HashTable));
    ht->table = (HashEntry**)malloc(HASH_SIZE * sizeof(HashEntry*));
    ht->size = HASH_SIZE;
    for (int i = 0; i < HASH_SIZE; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

void hashtable_insert(HashTable *ht, int key, int value) {
    int index = hash_function(key);
    HashEntry *entry = (HashEntry*)malloc(sizeof(HashEntry));
    entry->key = key;
    entry->value = value;
    ht->table[index] = entry;
}

void hashtable_display(HashTable *ht) {
    printf("Hash Table:\n");
    for (int i = 0; i < ht->size; i++) {
        if (ht->table[i] != NULL) {
            printf("Index %d: Key=%d, Value=%d\n", i, ht->table[i]->key, ht->table[i]->value);
        }
    }
}

/* ============================================
   4. MAIN DEMONSTRATION
   ============================================ */

int main() {
    printf("=== DATA STRUCTURES IN C ===\n\n");

    /* 1. Array */
    printf("--- 1. ARRAY ---\n");
    Array arr = {{0}, 0};
    for (int i = 0; i < 5; i++) {
        arr.elements[arr.size++] = (i + 1) * 10;
    }
    array_display(&arr);

    /* 2. Linked List */
    printf("\n--- 2. LINKED LIST ---\n");
    LinkedList list = {NULL};
    for (int i = 1; i <= 5; i++) {
        linkedlist_insert(&list, i * 10);
    }
    linkedlist_display(&list);

    /* 3. Stack */
    printf("\n--- 3. STACK (LIFO) ---\n");
    Stack stack = {{0}, -1};
    for (int i = 1; i <= 5; i++) {
        stack_push(&stack, i * 10);
    }
    stack_display(&stack);
    printf("Popped: %d\n", stack_pop(&stack));

    /* 4. Queue */
    printf("\n--- 4. QUEUE (FIFO) ---\n");
    Queue queue = {{0}, 0, 0, 0};
    for (int i = 1; i <= 5; i++) {
        queue_enqueue(&queue, i * 10);
    }
    queue_display(&queue);
    printf("Dequeued: %d\n", queue_dequeue(&queue));

    /* 5. Binary Search Tree */
    printf("\n--- 5. BINARY SEARCH TREE ---\n");
    TreeNode *root = NULL;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++) {
        root = tree_insert(root, values[i]);
    }
    tree_display(root);

    /* 6. Graph */
    printf("\n--- 6. GRAPH (Adjacency List) ---\n");
    Graph *graph = graph_create(4);
    graph_addEdge(graph, 0, 1);
    graph_addEdge(graph, 0, 2);
    graph_addEdge(graph, 1, 2);
    graph_addEdge(graph, 2, 0);
    graph_addEdge(graph, 2, 3);
    graph_addEdge(graph, 3, 3);
    graph_display(graph);



    printf("\n=== END OF DEMONSTRATION ===\n");

    return 0;
}
