//
//  mem.c
//  mgeeks-mem-alloc
//
//  Created by Maha Benjebara on 30/10/2015.
//  Copyright (c) 2015 mgeeks. All rights reserved.
//
#include "mem.h"
#include "debug.h"
#include "mem_manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <assert.h>
#include <fcntl.h>

#include <pthread.h>
#include <sys/mman.h>
#include <unistd.h>


#if !defined(MAP_ANONYMOUS) && defined(MAP_ANON)
# define MAP_ANONYMOUS MAP_ANON
#endif

#if !defined(MAP_FAILED)
# define MAP_FAILED ((char*)-1)
#endif

#ifndef MAP_NORESERVE
#ifdef MAP_AUTORESRV
#define MAP_NORESERVE MAP_AUTORESRV
#else
#define MAP_NORESERVE 0
#endif
#endif

// Global variable
static mem_manager* manager;
static Node *firstNode;
static int page_size = -1;

static unsigned int g_mem_size;
static unsigned int first_call = 0;

int Mem_Init(unsigned int sizeOfRegion) {

    if ( page_size < 0 ) {
        page_size = getpagesize();
        debug("System page size: %d\n", page_size);
    }
    unsigned int size = sizeOfRegion * page_size;
    debug("Memory reserved: %d\n", size);

    void* map = mmap(0, size, PROT_NONE, MAP_PRIVATE|MAP_NORESERVE|MAP_ANONYMOUS, -1, 0);

    if ( map  == MAP_FAILED) {
        log_err(ERROR_1);
        exit(EXIT_FAILURE);
    }

    debug("First adress memory of the heap: %p\n", map);
    if(mprotect(map , size, PROT_READ|PROT_WRITE) != 0)
    {
        munmap(map, size);
        log_err(ERROR_1);
        exit(EXIT_FAILURE);
    }

    g_mem_size = size;
    manager = createManager();
    firstNode = newNode();
    firstNode -> addr = map;
    firstNode -> size = size;
    manager -> free_block = init(firstNode);
    //    manager -> allocated_block = init(NULL);
    //    manager -> allocated_block -> size = 0;
    manager -> free_block -> size = sizeOfRegion;

    debug("First adress memory of the free_list: %p\n", firstNode -> addr);
    debug("sizeOfRegion = %d\n",  manager -> free_block -> size );
    debug("size of first free node : %d\n",  manager -> free_block -> first -> size);
    return 0;
}

void *Mem_Alloc(unsigned int size) {
    Node* block;
    Node* temp;
    if (size <= 0) {
        log_err(ERROR_2);
        return NULL;
    }
    if (!manager -> free_block) {
        log_err(ERROR_3);
        return NULL;
    }


    debug("Find free space with size");
    block = findFreeNode(size);
    debug("Size free_block['%p'] with size ['%d']", block -> addr, block -> size);
    if (!block) { // Failed to find free block.
        log_err(ERROR_4);
        return NULL;
    } else {      // Found free block
        // TODO: consider splitting block here.
        int newFreeSize =   block -> size - size;
        temp = newNode();
        temp -> addr = block -> addr;
        temp -> size = size;
        if(first_call == 0) {
            debug("First call");
            manager -> allocated_block = init(temp);
            debug("block memory ['%p']", block);
            debug("New block['%p'] is try to allocated with size['%d']", manager -> allocated_block ->first -> addr, size);
            first_call = 1;
        } else {
            addFirst(manager -> allocated_block, temp);
        }
        //            block -> size = size;

        block -> addr = (((char*) block -> addr) + 1 + size);
        //            debug("New block calcule ['%p']", (char*) block ->next);
        block -> size = newFreeSize;
        //            debug("New block['%p'] is try to allocated with size['%d']", block, size);

    }

    return temp -> addr;
}

int Mem_Free(void* ptr) {
    if(!ptr) {
        log_err(NULL_POINTER_ERROR);
        return -1;
    }
    debug("Trying to free the pointer ['%p']", ptr);
    Node* findBlock = findNode(manager -> allocated_block, (void*) ptr);
    if(!findBlock) {
        log_err(POINTER_NOT_FOUND_ERROR);
        return -1;
    }
    debug("Find to free the pointer ['%p']", findBlock);
    removeNode(manager -> allocated_block, findBlock);
    addFirst(manager ->free_block, findBlock);
    return 0;
}

int Mem_IsValid(void* ptr) {
    if(!ptr) {
        log_err(NULL_POINTER_ERROR);
        return -1;
    }
    debug("Trying to find the pointer ['%p']", ptr);
    Node* findBlock = findNode(manager -> allocated_block, ptr);
    if(!findBlock) {
        log_err(POINTER_NOT_FOUND_ERROR);
        return -1;
    }
    return 1;
}

int Mem_GetSize(void* ptr) {
    if(!ptr) {
        log_err(NULL_POINTER_ERROR);
        return -1;
    }
    debug("Trying to find the size of the pointer ['%p']", ptr);
    Node* findBlock = findNode(manager -> allocated_block, ptr);
    if(!findBlock) {
        log_err(POINTER_NOT_FOUND_ERROR);
        return -1;
    }
    debug("The size of the pointer ['%p'] is ['%d']", findBlock, findBlock ->size);
    return findBlock ->size;
}

Node *findFreeNode(int size) {
    debug("Trying to find free block with the size ['%d']...", size);
    Node *current = manager -> free_block -> first;
    while (current && !(current->size >= size)) {
        current = current -> next;
    }
    if (current == manager -> free_block -> first) {
        if(size > current -> size) {
            return NULL;
        }
    }
    return current;
}

LinkedList* freeList() {
    if (manager -> free_block == NULL) {
        exit(EXIT_FAILURE);
    }
    return manager -> free_block;
}
LinkedList* allocatedList() {
    if (manager -> allocated_block == NULL) {
        exit(EXIT_FAILURE);
    }
    return manager -> allocated_block;
}
