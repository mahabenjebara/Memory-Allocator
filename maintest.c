//
//  main.c
//  mgeeks-mem-alloc
//
//  Created by Maha BENJEBARA on 19/11/2015.
//  Copyright (c) 2015 mgeeks. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include "mem.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");


    Mem_Init(80);
    printAll(freeList() -> first);
//    printAll(allocatedList() -> first);
    void* ptr1 = Mem_Alloc(28);
    printf("\nptr 1= %p\n", ptr1);
    printf("############## Free list #############\n");
    printAll(freeList() -> first);

//    printf("############## Allocated list #############\n");
//    printAll(allocatedList() -> first);

//    printf("############## Allocated list #############\n");
//    printAll(allocatedList() -> first);

//    printf("get next free adress %p \n", freeList()->first);
//    printf("get next free size %d\n ", freeList()->first->size);
//    assert(getLinkedList()->first->state == ALLOCATED);
    void* ptr2 = Mem_Alloc(7);
    printf("ptr 2= %p\n", ptr2);
//    printf("get next free adress %p \n", freeList()->first);
//    printf("get next free size %d\n ", freeList()->first->size);
//    printf("############## Free list #############\n");
//    Mem_free(ptr2);
    printf("############## Free list #############\n");
    printAll(freeList() -> first);


//    printf("############## Allocated list #############\n");
//    printAll(allocatedList() -> first);

//    printf("############## Allocated list #############\n");
//    printAll(allocatedList() -> first);
//
    void* ptr3 = Mem_Alloc(104);
    void* ptr4 = Mem_Alloc(24);
    void* ptr5 = Mem_Alloc(56);
    void* ptr6 = Mem_Alloc(78);
//
    printf("############## Free list #############\n");
    printAll(freeList() -> first);

    printf("############## Allocated list #############\n");
    printAll(allocatedList() -> first);

    Mem_Free(ptr3);
    Mem_Free(ptr4);
    Mem_Free(ptr5);
    Mem_Free(ptr6);
//
    printf("############## Free list #############\n");
    printAll(freeList() -> first);

    printf("############## Allocated list #############\n");
    printAll(allocatedList() -> first);

    void* ptr8 = Mem_Alloc(104);

    printf("############## Free list #############\n");
    printAll(freeList() -> first);

    printf("############## Allocated list #############\n");
    printAll(allocatedList() -> first);

    Mem_IsValid(ptr1);
    Mem_GetSize(ptr1);

    return 0;
}
