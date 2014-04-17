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

void *dll_pop_cursor( DlList_T lst );

int dll_get_cursor_index( DlList_T lst );

#endif