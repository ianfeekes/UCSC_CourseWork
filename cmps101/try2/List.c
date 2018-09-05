#include "List.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct NodeObj {

    struct NodeObj * prev;
    struct NodeObj * next;
    int data;
} NodeObj;

typedef struct NodeObj Node;

typedef struct ListObj {

    Node * front_node;
    Node * back_node;
    Node * cursor_node;

    int cursor_index;
    int num_nodes;

} ListObj;

Node * newNode(void) {
    Node * new_node = malloc(sizeof(struct NodeObj));
    if(new_node == NULL) {
        fprintf(stderr, "Error : Malloc returned null node");
        exit(1);
    }
    new_node->prev = NULL;
    new_node->next = NULL;
    new_node->data = -1;
    return new_node;
}

List newList(void) {
    List new_list = malloc(sizeof(struct ListObj));
    if(new_list == NULL) {
      fprintf(stderr, "Error : Malloc Fail in Append");
    }
    new_list->front_node = NULL;
    new_list->back_node = NULL;
    new_list->cursor_node = NULL;
    new_list->num_nodes = 0;
    new_list->cursor_index = -1;
    return new_list;
}

void freeList(List* pL) {
    if(pL == NULL || *pL == NULL) {
        fprintf(stderr, "Error : Null List in freeList() \n");
        exit(1);
    }
    clear(*pL);
    free(*pL);
    *pL = NULL;
}

int length(List L) {
    if(L == NULL) {
        fprintf(stderr, "Error : Null List in length() \n");
        exit(1);
    }
    return L->num_nodes;
}

int getIndex(List L) {
    if(L == NULL) {
        fprintf(stderr, "Error : Null List in getIndex() \n");
        exit(1);
    }
    return L->cursor_index;
}

int front(List L) {
    if(L == NULL) {
        fprintf(stderr, "Error : Null List in front() \n");
        exit(1);
    }
    if(L->front_node == NULL) {
        fprintf(stderr, "Error : Empty List in front() \n");
        exit(1);
    }
    return L->front_node->data;
}

int back(List L) {
    if(L == NULL || L->back_node == NULL) {
        fprintf(stderr, "Error : Null List in back() \n");
        exit(1);
    }
    if(L->back_node == NULL) {
        fprintf(stderr, "Error : Empty List in back() \n");
        exit(1);
    }
    return L->back_node->data;
}

int getElement(List L) {
    if(L == NULL) {
        fprintf(stderr, "Error : Null List \n");
        exit(1);
    }
if(L->cursor_node == NULL || L->cursor_index == -1) {
        fprintf(stderr, "Error : Invalid Cursor Index getElement() \n");
        exit(1);
    }

    return L->cursor_node->data;
}

int equals(List A, List B) {
    if(A == NULL || B == NULL) {
        fprintf(stderr, "Error : Null List/Invalid cursor \n");
        exit(1);
    }

int saved_index1 = A->cursor_index;
    int saved_index2 = B->cursor_index;
if(A->num_nodes != B->num_nodes)
        return 0;

    for(int i = 0; i < A->num_nodes; i++) {
        moveTo(A, i);
        moveTo(B, i);

        if(A->cursor_node == NULL || A->cursor_node->data != B->cursor_node->data)
            return 0;
    }

    moveTo(A, saved_index1);
    moveTo(B, saved_index2);
    return 1;
}

void clear(List L) {
    if(L == NULL) {
        return;
    }
    Node * walker = L->front_node;
    while(L->front_node != NULL) {
        walker = L->front_node;
        L->front_node = L->front_node->next;
        free(walker);
        walker = NULL;
        L->num_nodes--;
    }
 L->front_node = NULL;
    L->back_node = NULL;

}

void moveTo(List L, int i) {
    if(L == NULL) {
        fprintf(stderr, "List null in moveTo");
        exit(1);
    }
    if(i < 0 || i > L->num_nodes-1)  {// pre-condition assertion
        L->cursor_index = -1;
        L->cursor_node = NULL;
        return;
    }

    if(i == L->num_nodes-1) {
        L->cursor_node = L->back_node;
        L->cursor_index = L->num_nodes-1;
        return;
    }

    if(L->cursor_index == -1) {
        if(i < L->num_nodes/2) {
            L->cursor_index = 0;
            L->cursor_node = L->front_node;
        }
        else {
            L->cursor_index = L->num_nodes-1;
            L->cursor_node = L->back_node;
        }
    }

    int diff = i - L->cursor_index;

    if(diff == 0) {
        return;
    }
    else if(diff > 0) { // we need to move forward
        while(L->cursor_index != i && L->cursor_node != NULL) {
            L->cursor_node = L->cursor_node->next;
            L->cursor_index++;
        }
        return;
    }
    else {
        while(L->cursor_index != i && L->cursor_node != NULL) {
            L->cursor_node = L->cursor_node->prev;
            L->cursor_index--;
        }
        return;
    }
}

void movePrev(List L) {
    if(L == NULL) {
        fprintf(stderr, "Error : Null List in movePRev \n");
        exit(1);
    }
 if(L->cursor_index < 1 || L->cursor_node == NULL) {
        L->cursor_index = -1;
        L->cursor_node = NULL;
        return;
    }
    L->cursor_index--;
    L->cursor_node = L->cursor_node->prev;
}

void moveNext(List L) {
    if(L == NULL) {
        return;
    }
    if(L->cursor_index >= L->num_nodes-1 || L->cursor_index == -1 || L->cursor_node == NULL) {
        L->cursor_index = -1;
        L->cursor_node = NULL;
        return;
    }

    L->cursor_node = L->cursor_node->next;
    L->cursor_index++;
}

void prepend(List L, int data) {
    if(L == NULL) {
      fprintf(stderr, "Error : L null in prepend\n");
      exit(1);
    }

Node * new_node = newNode();
    if(new_node == NULL) {
      fprintf(stderr, "Error : Malloc Fail in prepend");
    }
    new_node->data = data;
if(L->num_nodes == 0 || L->front_node == NULL) {
        L->front_node = new_node;
        L->back_node = new_node;
        L->num_nodes++;
        return;
    }
    L->front_node->prev = new_node;
    if(L->front_node->prev != NULL) {
      L->front_node->prev->next = L->front_node;
    }
    L->front_node = new_node;
    if(L->cursor_index != -1) {
        L->cursor_index++;
    }
    L->num_nodes++;
}

void append(List L, int data) {
    if(L == NULL) {
        fprintf(stderr, "Error : L null in append\n");
        exit(1);
    }

    Node * new_node = newNode();
    if(new_node == NULL) {
      fprintf(stderr, "Error : Malloc Fail in Append");
    }
    new_node->data = data;

    if(L->num_nodes == 0) {
        L->front_node = new_node;
        L->back_node = new_node;
        L->num_nodes++;
        return;
    }
    new_node->prev = L->back_node;

    if(L->back_node != NULL) {
        L->back_node->next = new_node;
    }
    L->back_node = new_node;
    L->num_nodes++;
}

void insertBefore(List L, int data) {
    if(L == NULL) {
        return;
    }
    if(L->cursor_index < 0 || L->num_nodes < 1 ) {
        L->cursor_index = -1;
        L->cursor_node = NULL;
        fprintf(stderr, "Error : Cursor index is NULL\n");
        exit(1);
    }

     Node * new_node = newNode();
    if(new_node == NULL) {
      fprintf(stderr, "Error : Malloc Fail in insertBefore");
    }
    new_node->data = data;

    if(L->cursor_node->prev != NULL) {
        L->cursor_node->prev->next = new_node;
    }
    new_node->prev = L->cursor_node->prev;
    L->cursor_node->prev = new_node;
    new_node->next = L->cursor_node;
    if(L->cursor_index != -1) {
        L->cursor_index++;
    }

    if(L->front_node == L->cursor_node) {
        L->front_node = L->cursor_node->prev;
    }
    L->num_nodes++;
}

void insertAfter(List L, int data) {
    if(L == NULL) {
        return;
    }
    if(L->cursor_index < 0 || L->num_nodes < 1 || L->cursor_node == NULL) {
        L->cursor_index = -1;
        L->cursor_node = NULL;
        fprintf(stderr, "Error : Invalid index to insert after\n");
        exit(1);
    }
Node * new_node = newNode();
    new_node->data = data;

    if(L->cursor_node->next != NULL) {
        L->cursor_node->next->prev = new_node;
    }
    new_node->next = L->cursor_node->next;
    L->cursor_node->next = new_node;
    new_node->prev = L->cursor_node;

    if(L->back_node == L->cursor_node) {
        L->back_node = L->cursor_node->next;
    }

    L->num_nodes++;
}

void deleteFront(List L) {
    if(L == NULL) {
        return;
    }
    if(L->num_nodes < 1 || L->front_node == NULL) {
        L->cursor_index = -1;
        L->cursor_node = NULL;
        fprintf(stderr, "Front node is NULL/ length = 0");
    }

    Node * to_delete = L->front_node;
    if(L->front_node != NULL) {
      L->front_node = L->front_node->next;
    }
    if(L->front_node != NULL) {
      L->front_node->prev = NULL;
    }
    L->num_nodes--;
    free(to_delete);
    to_delete = NULL;
}

void deleteBack(List L) {
    if(L == NULL) {
        return;
    }
    if(L->num_nodes < 1 || L->back_node == NULL) {
        L->cursor_index = -1;
        L->cursor_node = NULL;
        fprintf(stderr, "Back node is NULL/ length = 0");
    }

    Node * to_delete = L->back_node;
    L->back_node = L->back_node->prev;
    L->back_node->next = NULL;
    L->num_nodes--;
    free(to_delete);
    to_delete = NULL;
}

void delete(List L) {
    if(L == NULL) {
        return;
    }
    if(L->cursor_index < 0 || L->cursor_node == NULL || L->num_nodes == 0) {
        L->cursor_index = -1;
        L->cursor_node = NULL;
        fprintf(stderr, "Error : Cannot delete NULL cursor\n");
        exit(1);
    }

    if(L->cursor_node->next != NULL)
        L->cursor_node->next->prev = L->cursor_node->prev;
    if(L->cursor_node->prev != NULL) 
        L->cursor_node->prev->next = L->cursor_node->next;

   Node * to_delete = L->cursor_node;
    free(to_delete);
    to_delete = NULL;
    L->cursor_node = NULL;
    L->cursor_index = -1;
    L->num_nodes--;
}

void printList(FILE* out, List L) {
    if(L == NULL || out == NULL) {
        return;
    }
    Node * walker = L->front_node;

    while(walker != NULL) {
        int x = walker->data;
        fprintf(out, "%d ", x);
        walker = walker->next;
    }
}

List copyList(List L) {
    if(L == NULL) {
        printf("List null in copyList\n");
        exit(1);
    }
    Node * walker = L->front_node;
    List ret_list = newList();
    while(walker != NULL) {
        append(ret_list, walker->data);
        walker = walker->next;
    }
    return ret_list;
}

void insertSorted(List L, int val) {
  if(L == NULL) {
    fprintf(stderr, "Error : List NULL in insertSorted");
  }
  for(moveTo(L, 0); getIndex(L) >= 0; moveNext(L)) {
    if(getElement(L) > val) {
      insertBefore(L, val);
      return;
    }
  }

  append(L, val);

}
