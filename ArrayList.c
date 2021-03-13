#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    struct Node* next;
    void* data;
} Node;

typedef struct ArrayList{
    struct Node* first;
    struct Node* last;
    int size;
} ArrayList;


typedef int boolean;
int true = 1, false = 0;

boolean Array_delete(void** list, int size){
    for (int i = 0; i < size; i++){
        free(list[i]);
    }
    free(list);
}

Node* Node_new(Node* next, Node* prev, void* data){
    Node* node = malloc(sizeof(Node));
    node->next = next;
    node->data = data;
    if (next != NULL){
    }
    if (prev != NULL){
        prev->next = node;
    }
    return node;
}

void* Node_get(Node* list, int index){
    if (index == 0){
        return list->data;
    }
    else if (list->next != NULL){
        return Node_get(list->next, index - 1);
    }
    else{
        return NULL;
    }
}

boolean Node_set(Node* node, int index, void* value){
    if (index == 0){
        node->data = value;
        return true;
    }
    if (node->next == NULL){
        return false;
    }
    else{
        return Node_set(node->next, index - 1, value);
    }
}

Node* Node_add_to_next(Node* node, void* value){
    Node* newNode = Node_new(NULL, node, value);
    return newNode;
}

void* ArrayList_get(ArrayList* list, int index){
    return Node_get(list->first, index);
}

boolean ArrayList_set(ArrayList* list, int index, void* value){
    return Node_set(list->first, index, value);
}

boolean ArrayList_add_to_back(ArrayList* list, void* value){
    if (list->size == 0){
        list->first->data = value;
        list->size++;
        return true;
    }
    list->last = Node_add_to_next(list->last, value);
    list->size++;
    return true;
}

void* ArrayList_to_array(ArrayList* list){
    if (list->size == 0){
        return NULL;
    }
    void** array = malloc(list->size * sizeof(list->first->data));
    Node* current = list->first;
    int i = 0;
    array[i] = current->data;
    while (current->next != NULL){
        i++;
        Node* temp = current->next;
        current = temp;
        array[i] = current->data;
    }
    return array;
}

boolean ArrayList_print_ints(ArrayList* list){
    void** array = ArrayList_to_array(list);
    printf("[");
    for (int i = 0; i < list->size; i++){
        printf("%d", *((int*) array[i]));
        if (i != list->size - 1){
            printf(", ");
        }
    }
    free(array);
    printf("]\n");
    return true;
}

boolean ArrayList_print_chars(ArrayList* list){
    void** array = ArrayList_to_array(list);
    printf("[");
    for (int i = 0; i < list->size; i++){
        printf("%c", *((char*) array[i]));
        if (i != list->size - 1){
            printf(", ");
        }
    }
    free(array);
    printf("]\n");
    return true;
}

ArrayList* ArrayList_new(){
    ArrayList* arraylist = malloc(sizeof(ArrayList));
    Node* first = malloc(sizeof(ArrayList));
    first->next = NULL;
    first->data = NULL;
    arraylist->first = first;
    arraylist->last = first;
    arraylist->size = 0;
    return arraylist;
}

ArrayList* ArrayList_new_from_array(void** array, int size){
    ArrayList* arr = ArrayList_new();
    for (int i = 0; i < size; i++){
        ArrayList_add_to_back(arr, array[i]);
    }
    return arr;
}

void** Array_int_to_ref(int* array, int size){
    void** arr = malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++){
        arr[i] = &array[i];
    }
    return arr;
}

ArrayList* ArrayList_new_from_int_array(int* array, int size){
    void** arr = Array_int_to_ref(array, size);
    ArrayList* list = ArrayList_new_from_array(arr, size);
    free(arr);
    return list;
}

boolean ArrayList_delete(ArrayList* list){
    Node* current = list->first;
    while (current->next != NULL){
        Node* temp = current->next;
        free(current);
        current = temp;
    }
    free(current);
    free(list);
    return true;
}




int main() {

    int nums[] = {1,2,3,4,5,6,7,8,9,10};
    ArrayList* list = ArrayList_new_from_int_array(nums, 10);
    ArrayList_print_ints(list);

    int x = 12;
    ArrayList_set(list, 4, &x);
    printf("%d\n", *(int*) ArrayList_get(list, 6));
    int t = 14;
    ArrayList_add_to_back(list, &t);
    ArrayList_print_ints(list);

    ArrayList_delete(list);
}



