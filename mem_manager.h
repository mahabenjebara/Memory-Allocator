//
//  mem_manager.h
//  mgeeks-mem-alloc
//
//  Created by Benjebara Zakaria on 01/11/2015.
//  Copyright (c) 2015 Maha BENJEBARA. All rights reserved.
//

#ifndef __mgeeks_mem_alloc__mem_manager__
#define __mgeeks_mem_alloc__mem_manager__

#include <stdio.h>
#include "List.h"

typedef struct _mem_manager{
    LinkedList *free_block;//nodes non alloues
    LinkedList *allocated_block;//nodes allouees
} mem_manager;

mem_manager *createManager();
void managerDumpPrint(struct _mem_manager* manager);

#endif /* defined(__mgeeks_mem_alloc__mem_manager__) */
