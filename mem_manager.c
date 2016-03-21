//
//  mem_manager.c
//  mgeeks-mem-alloc
//
//  Created by Maha BENJEBARA on 01/11/2015.
//  Copyright (c) 2015 mgeeks. All rights reserved.
//

#include "mem_manager.h"

mem_manager *createManager() {
    mem_manager *manager = malloc(sizeof(struct _mem_manager));
    manager -> free_block = NULL;
    manager -> allocated_block = NULL;
    return manager;
}

void managerDumpPrint(struct _mem_manager* manager) {

}
