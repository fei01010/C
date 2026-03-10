#include <stdio.h>
#include <string.h>

#define maxsize 5

typedef struct spacestr {
    char name[10];
    int next;
} Spacestr;

void initlist(Spacestr stu[], int *head, int *free_head) {
    for (int i = 0; i < maxsize - 1; i++) {
        stu[i].next = i + 1;
    }
    stu[maxsize - 1].next = -1;
    *head = -1;
    *free_head = 0;
}

int alloc_node(Spacestr stu[], int *free_head) {
    if (*free_head == -1) {
        return -1;
    }

    int index = *free_head;
    *free_head = stu[index].next;
    stu[index].next = -1;
    return index;
}

void free_node(Spacestr stu[], int *free_head, int index) {
    stu[index].next = *free_head;
    *free_head = index;
}

int length(Spacestr stu[], int head) {
    int count = 0;
    int p = head;
    while (p != -1) {
        count++;
        p = stu[p].next;
    }
    return count;
}

int insert(Spacestr stu[], int *head, int *free_head, int pos, const char name[]) {
    int len = length(stu, *head);
    if (pos < 1 || pos > len + 1) {
        printf("insert failed: invalid position\n");
        return 0;
    }

    int new_index = alloc_node(stu, free_head);
    if (new_index == -1) {
        printf("insert failed: no free node\n");
        return 0;
    }

    strncpy(stu[new_index].name, name, sizeof(stu[new_index].name) - 1);
    stu[new_index].name[sizeof(stu[new_index].name) - 1] = '\0';

    if (pos == 1) {
        stu[new_index].next = *head;
        *head = new_index;
        return 1;
    }

    int prev = *head;
    for (int i = 1; i < pos - 1; i++) {
        prev = stu[prev].next;
    }

    stu[new_index].next = stu[prev].next;
    stu[prev].next = new_index;
    return 1;
}

int remove_at(Spacestr stu[], int *head, int *free_head, int pos, char removed_name[]) {
    int len = length(stu, *head);
    if (pos < 1 || pos > len) {
        printf("remove failed: invalid position\n");
        return 0;
    }

    int target;
    if (pos == 1) {
        target = *head;
        *head = stu[target].next;
    } else {
        int prev = *head;
        for (int i = 1; i < pos - 1; i++) {
            prev = stu[prev].next;
        }
        target = stu[prev].next;
        stu[prev].next = stu[target].next;
    }

    strcpy(removed_name, stu[target].name);
    free_node(stu, free_head, target);
    return 1;
}

int find_by_name(Spacestr stu[], int head, const char name[]) {
    int p = head;
    int pos = 1;
    while (p != -1) {
        if (strcmp(stu[p].name, name) == 0) {
            return pos;
        }
        p = stu[p].next;
        pos++;
    }
    return -1;
}

void print_list(Spacestr stu[], int head) {
    int p = head;
    printf("List: ");
    while (p != -1) {
        printf("[%s|%d] ", stu[p].name, p);
        p = stu[p].next;
    }
    printf("\n");
}

int main() {
    Spacestr stu[maxsize];
    int head;
    int free_head;
    char removed[10];

    initlist(stu, &head, &free_head);

    insert(stu, &head, &free_head, 1, "Tom");
    insert(stu, &head, &free_head, 2, "Amy");
    insert(stu, &head, &free_head, 2, "Bob");
    print_list(stu, head);

    printf("position of Amy: %d\n", find_by_name(stu, head, "Amy"));

    if (remove_at(stu, &head, &free_head, 2, removed)) {
        printf("removed: %s\n", removed);
    }
    print_list(stu, head);

    return 0;
}
//ai跑出来的，anyway,看不懂，先放着