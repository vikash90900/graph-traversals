#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

// Stack
#define MAX_SIZE 10

typedef struct {
    int items[MAX_SIZE];
    int top;
} Stack;

Stack* create_stack();
int is_empty(Stack* stack);
int is_full(Stack* stack);
void push(Stack* stack, int item);
int pop(Stack* stack);
void destroy_stack(Stack* stack);

Stack* create_stack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if(stack == NULL) {
        printf("Memory Allocation Failed.");
    }
    stack->top = -1;
    return stack;
}

int is_empty(Stack* stack) {
    return stack->top == -1;
}

int is_full(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

void push(Stack* stack, int item) {
    if(is_full(stack)) {
        printf("Stack is Full. Cannot puch %d.");
        return;
    }
    stack->items[++stack->top] = item;
}

int pop(Stack* stack) {
    if(is_empty(stack)) {
        printf("Stack is empty. Cannot pop.");
        return -1;
    }

    return stack->items[stack->top--];
}

void destroy_stack(Stack* stack) {
    free(stack);
}

typedef struct {
    int *arr;
    int frontIdx;
    int rearIdx;
    int size;
} Queue;

Queue* create_queue();
void enqueue(Queue* qu, int data);
int deque(Queue* qu);
bool isFull(Queue* qu);
bool isEmpty(Queue* qu);

bool isFull(Queue* qu) {
    return qu->rearIdx == MAX_SIZE - 1;
}

bool isEmpty(Queue* qu) {
    return (qu->frontIdx == -1 && qu->rearIdx == -1);
}

void enqueue(Queue* qu, int data) {
    if(isFull(qu)) {
        printf("Queue is Full.");
        return;
    }
    if(qu->frontIdx == -1) {
        qu->frontIdx = 0;
    }
    qu->arr[++qu->rearIdx] = data;
    qu->size++; 
}

int deque(Queue* qu) {
    if(isEmpty(qu)) {
        printf("Queue is empty.");
        exit(1);
    }
    qu->size--;
    return qu->arr[qu->frontIdx++];   
}

//  Grapgh List
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct {
    int num_vertices;
    Node **adj_list;
} GraphList;


GraphList* create_graph_list(int vertices) {
    GraphList* graph = malloc(sizeof(GraphList));
    graph->num_vertices = vertices;
    graph->adj_list = malloc(sizeof(Node*) * vertices);

    for(int i = 0; i < graph->num_vertices; i++) {
        graph->adj_list[i] = NULL;
    }

    return graph;
}

int add_edge_list(GraphList* graph, int src, int dest) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = graph->adj_list[src];
    graph->adj_list[src] = newNode;

    newNode = malloc(sizeof(Node));
    newNode->vertex = src;
    newNode->next = graph->adj_list[dest];
    graph->adj_list[dest] = newNode;

    return 0;
}

int print_graph_list(GraphList* graph) {
    for(int i = 0; i < graph->num_vertices; i++) {
        Node* temp = graph->adj_list[i];
        printf("\nAdjacency List of vertex %d head ", i);
        while(temp) {
            printf("-> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
    return 0;
}

void dfs_iterative(GraphList* graph, int start_vertex) { // depth first search
    int curr_vertex;
    int visited[graph->num_vertices];

    for(int i = 0; i < graph->num_vertices; i++) {
        visited[i] = 0;
    }

    Stack* stack = create_stack();
    push(stack, start_vertex);

    while(!is_empty(stack)) {
        curr_vertex = pop(stack);
        if(!visited[curr_vertex]) {
            visited[curr_vertex] = 1;
            printf("visited %d\n", curr_vertex);
        }

        Node* temp = graph->adj_list[curr_vertex]; 
        while(temp != NULL) {
            int adj_vertex = temp->vertex;
            if(!visited[adj_vertex]) {
                push(stack, adj_vertex);
            }
            temp = temp->next;
        }
    }

}

void dfs_recursive_0(GraphList* graph, Node* temp, Stack* stack, int *arr) {
   if(temp == NULL) {
    return;
   }
   int adj_vertex = temp->vertex;
   if(!arr[adj_vertex]) {
    push(stack, adj_vertex);
   }
   temp = temp->next;
   dfs_recursive_0(graph, temp, stack, arr);
}

void dfs_recursive(GraphList* graph, Stack* stack, int *arr, int start_vertex, int curr_vertex) {
    if(is_empty(stack)) {
        return;
    }
    curr_vertex = pop(stack);
    if(!arr[curr_vertex]) {
        arr[curr_vertex] = 1;
        printf("Visited %d \n", curr_vertex);
    }

    Node* temp = graph->adj_list[curr_vertex];
    dfs_recursive_0(graph, temp, stack, arr);
    dfs_recursive(graph, stack, arr, start_vertex, curr_vertex);
}


int main() {
    GraphList* graph = create_graph_list(5);
    add_edge_list(graph, 0, 1);
    add_edge_list(graph, 0, 2);
    add_edge_list(graph, 0, 3);
    add_edge_list(graph, 1, 2);
    add_edge_list(graph, 3, 4);

    Stack* stack = create_stack();
    push(stack, 0);
    int arr[5] = {0, 0, 0, 0, 0};

    dfs_recursive(graph, stack, arr, 0, 0);

    printf("\n\n");

    dfs_iterative(graph, 0);

    return 0;
}
