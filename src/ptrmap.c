#include <ptrmap.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>



size_t hashfunc_int(uint32_t x, size_t len)
{
	return x % len;
}

int8_t keycmp_int(uint32_t x, uint32_t y)
{
	return x == y;
}


ptrmapptr_t ptrmap_create(size_t length)
{
	int i;

	ptrmapptr_t x = (ptrmapptr_t)malloc(sizeof(ptrmap_t));
	x->length = length;
	x->numelems = 0;

	x->data = (mapelemptr_t)malloc(sizeof(mapelem_t) * length);


	for(i = 0; i < length; i++)
	{
		x->data[i].data = NULL;
		x->data[i].deleted = 0;
		x->data[i].key = 0;
		x->data[i].used = 0;
	}

	return x;
}

void ptrmap_destroy(ptrmapptr_t map)
{
	free(map->data);

	free(map);

	return;
}


void ptrmap_add(ptrmapptr_t map, KEYTYPE key, VALUETYPE elem)
{
	size_t counter, hash;

	// Check if more or equal than 3/4 of the array would be occupied
	if(map->numelems+1 > (3.f/4.f)*map->length)
	{
		// We have to reallocate, we double the size
		ptrmap_realloc(map, map->length);
	}

	// Compute the hash
	hash = HASHFUNC(key, map->length);


	for(counter = 0; map->data[hash].used; hash = (hash+1)%map->length, counter++)
	{
		if(counter >= map->length) return; // No free space (should not happen!)

		if(map->data[hash].deleted)
		{
			map->data[hash].deleted = 0;
			map->data[hash].data = elem;
			map->data[hash].key = key;
			map->data[hash].used = 1;

			map->numelems++;

			return;
		}

		// If a cell is holding our key pointer, we would add double keys which is forbidden
		if(KEYCMP(map->data[hash].key, key)) return; 
	}

	map->data[hash].data = elem;
	map->data[hash].key = key;
	map->data[hash].deleted = 0;
	map->data[hash].used = 1;
	map->numelems++;

	return;
}


VALUETYPE ptrmap_get(ptrmapptr_t map, KEYTYPE key)
{
	size_t counter, hash;

	hash = HASHFUNC(key, map->length);

	for(counter = 0; counter < map->length && map->data[hash].used; counter++, hash = (hash+1)%map->length)
	{
		if(KEYCMP(map->data[hash].key, key) && !map->data[hash].deleted)
			return map->data[hash].data;
	}

	return NOTFOUND;
}

int8_t ptrmap_contains_key(ptrmapptr_t map, KEYTYPE key)
{
	return ptrmap_get(map,key) != NOTFOUND;
}

void ptrmap_realloc(ptrmapptr_t map, size_t additional)
{
	// Save old data
	size_t counter,i;
	size_t oldlen = map->length;
	mapelemptr_t x = (mapelemptr_t)malloc(sizeof(mapelem_t)*map->length);
	memcpy_s(x, sizeof(mapelem_t)*map->length, map->data, sizeof(mapelem_t)*map->length);

	// Reallocate 
	free(map->data);

	map->data = (mapelemptr_t)malloc(sizeof(mapelem_t)*(map->length + additional));
	map->length += additional;
	map->numelems = 0;

	for(i = 0; i < map->length; i++)
	{
		map->data[i].data = NULL;
		map->data[i].deleted = 0;
		map->data[i].used = 0;
	}


	// Re-add entries
	for(counter = 0; counter < oldlen; counter++)
	{
		if(!x[counter].deleted && x[counter].used)
		{
			ptrmap_add(map, x[counter].key, x[counter].data);
		}	
	}

	// Free temp
	free(x);

	return;
}



void ptrmap_remove(ptrmapptr_t map, KEYTYPE key)
{
	size_t hash,counter;

	hash = HASHFUNC(key, map->length);

	for(counter = 0; counter < map->length && map->data[hash].used; counter++, hash = (hash+1)%map->length)
	{
		if(KEYCMP(map->data[hash].key, key))
		{
			if(!map->data[hash].deleted)
			{
				map->data[hash].deleted = 1;
				return;
			}
			return; // Already deleted
		}
	}

	return; // Not found
}