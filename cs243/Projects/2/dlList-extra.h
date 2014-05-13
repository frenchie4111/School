#ifndef _DLLIST_EXTRA_ADT_H_
#define _DLLIST_EXTRA_ADT_H_

#include "dlList.h"

/**
 * Returns the value that the cursor is pointing at
 * @param  lst The list to perform the operation on
 * @return     The current value
 */
void *dll_current( DlList_T lst );

/**
 * Sets the cursor to the first value, and returns the first
 * value
 * @param  lst The list to perform the operation on
 * @return     Returns the first value in the list
 */
void *dll_first( DlList_T lst );

/**
 * Sets the cursor to the last value, and returns the last value
 * @param  lst The list to perform the operation on
 * @return     Returns the last value in the list
 */
void *dll_last( DlList_T lst );

/**
 * Returns the index value of the cursor
 * @param  lst The list to perform the operation on
 * @return     Returns the current position of the cursor
 */
int dll_get_cursor_index( DlList_T lst );

/**
 * Pops the value at the cursor
 * @param  lst The list to perform the operation on 
 * @return     The data that the popped node refered to.
 *                  caller is responsible for freeing
 */
void *dll_pop_cursor( DlList_T lst );

#endif

// $Log: $ 
// commit f6a06bb03cf1a4ec0a799f56396cbe1621263ae3
// Author: Mike Lyons <mdl0394@gmail.com>
// Date:   Fri Apr 18 19:30:03 2014 -0400
// 
//     Added comments
// 
// commit 582e0c65b60e06b271c974fe094ae5537f6e9e0b
// Author: Mike Lyons <mdl0394@gmail.com>
// Date:   Wed Apr 16 20:53:32 2014 -0400
// 
//     Code complete. Working with valgrind
// 


