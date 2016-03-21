//
//  LinkedListImp.c
//  CollectionProject
//
//  Created by Maha BENJEBARA on 01/11/15.
//  Copyright (c) 2013 mgeeks. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include "List.h"
#include "debug.h"

LinkedList* init(Node* node){
    debug("Trying to initilize the list...");
    LinkedList *newList = malloc(sizeof(struct _LinkedList));
    newList -> size = 1;
    newList -> first = node;
//    newList -> first -> next = NULL;
    return newList;
}

Node* newNode() {
    debug("Trying to initilize new node...");
    Node *newNode = malloc(sizeof(struct _Node));
    newNode->addr = NULL;
    newNode->size = 0;
    newNode->next = NULL;
    return newNode;
}

static int isNull(Node* node) {
    if (node == NULL) {
        log_err(NULL_POINTER_ERROR);
        return 1;
    }
    return 0;
}

int isEmpty(LinkedList* list) {
    if (list == NULL) {
        log_err(NULL_POINTER_ERROR);
        exit(EXIT_FAILURE);
    }
    return (list->size == 0) ? 1 : 0;
}

int lenght(LinkedList* list) {
    int l = 0;
    if (!isEmpty(list)) {
        Node *current = list->first;
        while (current->next != NULL) {
            current = current->next;
            l++;
        }
    }
    return l;
}

Node* findNode(LinkedList *list, void *addr) {
    debug("Trying to find node['%p']...", addr);
    Node *current = list -> first;
    while (current) {
        if (current -> addr == addr) {
            debug("Node was found!");
            return current;
        }
        current = current -> next;
    }
    debug("Node not exist!");
    return NULL;
}

Node* findLast(LinkedList *list) {
    debug("Trying to find last node...");
    Node *current = list -> first;
    while (current ->next != NULL) {
        current = current->next;
    }
    return current;
}

void addFirst(LinkedList* list, Node* node) {
    debug("Trying to addFirst node['%p']...", node);
    if(isEmpty(list)) {
        debug("The list is empty");
        list -> first = node;
        list -> first -> next = NULL;
    } else {
        debug("The list is not empty");
        Node* temp = list -> first;
        debug("firstNode['%p']...", temp);
        node -> next = temp;
        list -> first = node;
        debug("firstNode after update['%p']...", list -> first);
        debug("firstNode -> next after update['%p']...", list -> first -> next );
    }
    list -> size = list -> size + 1;
}

void removeNode(LinkedList* list , Node* target) {
    if (isEmpty(list)) {
        return;
    }
    Node* origin = list -> first;
    if(isNull(origin) || isNull(target)){
        log_err(EMPTY_LIST_ERROR);
        return;
    } else {
        if (origin == target) {
            Node* temp = origin -> next;
            list -> first = temp;
            return;
        }
        Node* current = origin;
        while (current -> next != target) {
            current = current -> next;
        }
        if (isNull(current)) {
            log_err(NULL_POINTER_ERROR);
        } else {
            current->next = current->next->next;
            list ->size--;
        }
    }
}

void addLast(LinkedList* list, Node* newNode) {

    if(isEmpty(list)) {
        addFirst(list, newNode);
    } else {
        Node* current = list -> first;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
        newNode->next = NULL;
        list -> size++;
    }
}

void removeFirst(LinkedList* list) {

    if(!isEmpty(list)){

        Node* removeNode = list -> first;

        list -> first = list -> first -> next;

        free(removeNode);
    }
}

void removeLast(LinkedList* list) {
    if(!isEmpty(list)){
        Node* current = list -> first;
        while (current->next->next != NULL) {
            current = current->next;
        }
        free(current->next->next);
        current->next = NULL;
    }
}

void removeFrom(LinkedList* list, int position){
    if(isEmpty(list) && position >= 1){
        log_err(EMPTY_LIST_ERROR);
    }else {
        Node* current = list -> first;
        for (int i= 1; i < position - 1 ; i++) {
            current = current->next;
        }
        if (isNull(current)) {
            log_err(NULL_POINTER_ERROR);
        } else {
            current->next = current->next->next;
            free(current->next);
        }
    }
}

int exist(Node* origin, Node* element) {

    if (isNull(origin) || isNull(element)) {
        log_err(NULL_POINTER_ERROR);
        return 0;
    }
    if (origin == element) {
        return 1;
    } else {
        return exist(origin -> next, element);
    }
}

void printAll(Node* list) {
    if (!list) {
        log_err(NULL_POINTER_ERROR);
        return;
    }
    Node *current = list;
    while(current != NULL)
    {
        // call print dump
        dumpPrint(current);
        printf("\t \t \t \t \t \t \t  ||\n");
        printf("\t \t \t \t \t \t \t  ||\n");
        printf("\t \t \t \t \t \t \t  \\/\n");
        // next to be printed if exist
        current = current -> next;
    }
    printf("\t \t \t \t \t \t \t NULL \n ");
}

void dumpPrint(Node* node) {
    if (node->size < 0) {
        log_err(NULL_POINTER_ERROR);
        return;
    }
    if (isNull(node)) {
        log_err(NULL_POINTER_ERROR);
        return;
    }
//    debug("the node ads ['%p']", node);
    printf("***********************************************************\n");
    printf("* Adress:                   %p                   *\n", node -> addr);
    printf("***********************************************************\n");
    printf("*   Size:                   %5d                         *\n", node->size);
    printf("***********************************************************\n");
    if (node->next) {
        printf("*   next:                   %p                   *\n", node-> next -> addr);
    } else {
        printf("*   next:                   NULL                           *\n");
    }
    printf("***********************************************************\n");
}


