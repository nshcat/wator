#pragma once

#include <stddef.h>
#include <stdint.h>


/* Hashmap key and value type */
#define KEYTYPE uint32_t
#define VALUETYPE voidptr_t
#define NOTFOUND NULL /* returned if element is not found */
#define HASHFUNC(x,y) hashfunc_int(x,y)
#define KEYCMP(x,y) keycmp_int(x,y)
/**/


// Typeless pointer
typedef void* voidptr_t;


// Structure holding hashmap entry information
typedef struct _mapelem_t
{
	KEYTYPE key;
	VALUETYPE data;
	int8_t deleted;
	int8_t used;
} mapelem_t, *mapelemptr_t;

// Main ptrmap structure
typedef struct _ptrmap_t
{
	mapelemptr_t data;
	size_t length;
	size_t numelems;
} ptrmap_t, *ptrmapptr_t;


ptrmapptr_t ptrmap_create(size_t);
void ptrmap_destroy(ptrmapptr_t);

void ptrmap_realloc(ptrmapptr_t, size_t);
void ptrmap_add(ptrmapptr_t, KEYTYPE, VALUETYPE);
VALUETYPE ptrmap_get(ptrmapptr_t, KEYTYPE);
void ptrmap_remove(ptrmapptr_t, KEYTYPE);

int8_t ptrmap_contains_key(ptrmapptr_t, KEYTYPE);


// Default hash function for int
size_t hashfunc_int(uint32_t, size_t);

// Default compare function for int
int8_t keycmp_int(uint32_t, uint32_t);
