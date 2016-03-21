//
//  List.h
//  CollectionProject
//
//  Created by Maha Benjebara on 01/11/15.
//  Copyright (c) 2013 mgeeks. All rights reserved.
//

/**
 *
 *  Double LinkedList for storing information about the memory allocation blocks
 *
 */
#ifndef CollectionProject_List_h
#define CollectionProject_List_h

#define META_SIZE sizeof(struct _Node)

#define EMPTY_LIST_ERROR "The linked list must be not empty!"

#define SIZE_NODE_ERROR "Node size must be superior from 0"

#define NODE_NOT_FOUND "Element not exist in the list"

/**
 *  Enumeration for storing block state
 */
typedef enum {
    FREE,
    ALLOCATED
} BlockState;

/**
 * The node that contain the memory block storage information
 */
typedef struct _Node
{
    void* addr;
    unsigned int size;
    struct _Node *next;
} Node;

/**
 * The linked list that store the first element of the list and the size
 */
typedef struct _LinkedList{
    int size;
    Node *first;
} LinkedList;

// LinkedList costructor
LinkedList* init(Node *node);

// Node costructor
Node* newNode();

/*
 * Verify if the linked list is empty
 *
 * @param list the reference of the linked list
 * @return 1 if the linked list is empty 0 otherwise.
**/
int isEmpty(LinkedList *list);

/*
 * The number of nodes in the linked
 *
 * @param list the reference of the linked list
 * @return the size of the linked list.
 **/
int lenght(LinkedList *list);

/*
 * Find a node by addr attribute
 *
 * @param list the reference of the linked list
 * @return pointer to the searched node.
 **/
Node* findNode(LinkedList *list, void *addr);

/*
 * Find the last node of the target list
 *
 * @param list the reference of the linked list
 * @return pointer to the last node of the list.
 **/
Node* findLast(LinkedList *list);

/*
 * Add a node to the first of the target list
 *
 * @param list the reference of the linked list
 * @return void.
 **/
void addFirst(LinkedList *list, Node* data);

/*
 * Add a node to the last of the target list
 *
 * @param list the reference of the linked list
 * @return void.
 **/
void addLast(LinkedList *list, Node* data);

/*
 * Delete the first element from the reference list
 *
 * @param list the reference of the linked list
 * @return void.
 **/
void removeFirst(LinkedList *list);

/*
 * Delete the last element from the reference list
 *
 * @param list the reference of the linked list
 * @return void.
 **/
void removeLast(LinkedList *list);

/*
 * Delete the i-element from the reference list
 *
 * @param list the reference of the linked list
 * @return void.
 **/
void removeFromPosition(LinkedList *list, int position);

/*
 * Delete the referenced element from the list
 *
 * @param list the reference of the linked list
 * @return void.
 **/
void removeNode(LinkedList *list, Node* data);

/*
 * Print all the element of the list
 *
 * @param list the first element from linked list
 * @return void.
 **/
void printAll(Node* list);

/*
 * A simple representation of a node element
 *
 * @param the refrenced node
 * @return void.
 **/
void dumpPrint(Node* node);

#endif
