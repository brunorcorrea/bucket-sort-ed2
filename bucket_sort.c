#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void insert(struct Node** head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void insertionSort(struct Node** head) {
    struct Node* sorted = NULL;
    struct Node* current = *head;
    while (current != NULL) {
        struct Node* next = current->next;

        if (sorted == NULL || sorted->data >= current->data) {
            current->next = sorted;
            sorted = current;
        } else {
            struct Node* temp = sorted;
            while (temp->next != NULL && temp->next->data < current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }
    *head = sorted;
}

void bucketSort(int arr[], int n) {
    int max_value = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_value) {
            max_value = arr[i];
        }
    }

    const int num_buckets = 10;
    struct Node** buckets = (struct Node**)malloc(num_buckets * sizeof(struct Node*));
    for (int i = 0; i < num_buckets; i++) {
        buckets[i] = NULL;
    }

    for (int i = 0; i < n; i++) {
        int index = (arr[i] * num_buckets) / (max_value + 1);
        insert(&buckets[index], arr[i]);
    }

    for (int i = 0; i < num_buckets; i++) {
        insertionSort(&buckets[i]);
    }

    int index = 0;
    for (int i = 0; i < num_buckets; i++) {
        struct Node* current = buckets[i];
        while (current != NULL) {
            arr[index++] = current->data;
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }

    free(buckets);
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;

    printf("Digite o tamanho do array: ");
    scanf("%d", &n);

    int* arr = (int*)malloc(n * sizeof(int));

    printf("Digite os elementos do array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("\nArray original:\n");
    printArray(arr, n);

    bucketSort(arr, n);

    printf("\nArray ordenado:\n");
    printArray(arr, n);

    return 0;
}
