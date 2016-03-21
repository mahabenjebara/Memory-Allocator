//
//  mgeeks_mem.h
//  mgeeks-mem-alloc
//
//  Created by Maha BENJEBARA on 30/10/2015.
//  Copyright (c) 2015 Maha mgeeks. All rights reserved.
//

#include "List.h"

#ifndef mgeeks_mem_alloc_mem_h
#define mgeeks_mem_alloc_mem_h

#define MAX_MEM_SIZE 1048576

#define ERROR_1 "Error 1"
#define ERROR_2 "Error 2"
#define ERROR_3 "Error 3"
#define ERROR_4 "Error 4"
#define POINTER_NOT_FOUND_ERROR "Pointer not found in the allocated list"

/* System parameters */

#define NODE_MAP_PATH "/dev/zero"

#define NODE_UNUSED 0
#define NODE_USED 1
#define NODE_SPLIT 2
#define NODE_FULL 3

int Mem_Init(unsigned int sizeOfRegion);
void *Mem_Alloc(unsigned int size);
int Mem_Free(void* ptr);
int Mem_IsValid(void* ptr);
int Mem_GetSize(void* ptr);

Node *findFreeNode(int size);
LinkedList* freeList();
LinkedList* allocatedList();
#endif
