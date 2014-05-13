/**
 * File: dll_mike.h
 * dll_mike library header file
 * @author mdl7240 : Mike Lyons
 */

#ifndef DLL_MIKE_H
#define DLL_MIKE_H

#ifndef _DLL_IMPL_

typedef struct { } * dll;

#endif

/**
 * @brief Creates dll
 * @details Builds and mallocs a dll struct
 * @return malloced and nulled dll struct
 */
dll dll_create();

/**
 * @brief Destroys a dll
 * @details Destroys dll, frees all memory used
 * 
 * @param list The dll to destroy
 */
void dll_destroy( dll list );

/**
 * @brief Clears dll, rmeoving all items
 * @details Clears dll, removing all items,
 * 		leaves dll so you can add more items
 * 
 * @param list dll to clear
 */
void dll_clear( dll list );

/**
 * @brief Pushes item onto end of dll
 * @details Pushes item onto the end of a dll
 * 			item that is pushed is owned by dll
 * 
 * @param list list to push to
 * @param item item to push to
 */
void dll_push( dll list, void *item );

/**
 * @brief Pushes item onto beginning of dll
 * @details Pushes item onto the beginning of a dll
 * 			item that is pushed is owned by dll
 * 
 * @param list list to push to
 * @param item item to push to
 */
void dll_push_first( dll list, void *item );

/**
 * @brief Pushes item onto index of dll
 * @details Pushes item onto the end of a dll
 * 			item that is pushed is owned by dll
 * 
 * @param list list to push to
 * @param item item to push to
 */
void dll_insert( dll list, void *item, int index );

/**
 * @brief Returns the first item on dll
 * @details Returns the first item on dll
 * 			item is still owned by dll
 * 
 * @param list the list to get the item from
 * @return item at beginning of list
 */
void *dll_first( dll list );

/**
 * @brief Returns the last item on dll
 * @details Returns the last item on dll
 * 			item is still owned by dll
 * 
 * @param list the list to get the item from
 * @return item at end of list
 */
void *dll_last( dll list );

/**
 * @brief Gets item at index
 * @details Returns item at index from list
 *          item still owned by dll
 * 
 * @param list list to get the item from
 * @param index index to remove at
 * 
 * @return item at index, still owned by dll
 */
void *dll_get( dll list, int index );

/**
 * @brief Removes and returns item at end of list
 * @details Removes and returns item at end of list
 *          Item is now owned by caller of this function
 * 
 * @param list list to pop item off of
 * @return Item that was removed, owned by caller after
 */
void *dll_pop( dll list );

/**
 * @brief Removes and returns item at beginning of list
 * @details Removes and returns item at end of list
 *          Item is now owned by caller of this function
 * 
 * @param list list to pop item off of
 * @return Item that was removed, owned by caller after
 */
void *dll_pop_first( dll list );

/**
 * @brief Removes and returns item at index
 * @details Removes and returns item at end of list
 *          Item is now owned by caller of this function
 * 
 * @param list list to pop item off of
 * @param index the index to remove the item from
 * @return Item that was removed, owned by caller after
 */
void *dll_remove( dll list, int index );

/**
 * @brief Reutrns how many items are in dll
 * @details Returns how many items are in dll
 * 
 * @param list list to return count of
 * @return How many items are in dll
 */
int dll_count( dll list );

/**
 * @brief Resets the cursor position to beginning of list
 * @details Resets cursor position to first item in list
 * 
 * @param list List to return cursor of
 */
void dll_curs_reset( dll list );

/**
 * @brief Cursor returns current item and skips to next
 * @details Moves to next item and returns current. Doesn't
 * 			doesn't move if at end of list
 * 
 * @param list list to move cursor on
 * @return Item at cursor
 */
void *dll_curs_next( dll list );

/**
 * @brief Returns if the cursor points to valid position
 * @details Returns true if cursor points to valie position
 * 
 * @param list The list to asses the cursor on
 * @return Returns true if cursor points to valid position
 */
int dll_curs_has_next( dll list );

/**
 * @brief Prints out dll information
 * @details Prints out dll information assumes all values
 * 			are char *
 * 
 * @param list Prints out dll information
 */
void dll_print( dll list );

#endif
