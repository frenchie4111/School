#ifndef DLL_MIKE_H
#define DLL_MIKE_H

#ifndef _DLL_IMPL_

typedef struct { } * dll;

#endif

dll dll_create();
void dll_destroy( dll list );
void dll_clear( dll list );

// Adds to end
void dll_push( dll list, void *item );
// Adds to begginning
void dll_push_first( dll list, void *item );
// Inserts at index
void dll_insert( dll list, void *item, int index );

void *dll_first( dll list );
void *dll_last( dll list );
void *dll_get( dll list, int index );

// Pops off end
void *dll_pop( dll list );
void *dll_pop_first( dll list );
void *dll_remove( dll list, int index );

// Count
int dll_count( dll list );

void dll_curs_reset( dll list );
void *dll_curs_next( dll list );
int dll_curs_has_next( dll list );

void dll_print( dll list );

#endif