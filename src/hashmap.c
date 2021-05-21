#include "hashmap.h"
#include "vector.h"
#include <stdio.h>

int init_hashmap(hashmap_t *hashmap, size_t element_size, int size,
                 int (*compare)(const void *a, const void *b),
                 int (*hash)(const void *a),
                 int (*exists)(const void *a),
                 void (*init)(const void *a))
{
    init_vector(&hashmap->map, size, element_size);

    if (init != NULL)
    {
        int i;
        for (i = 0; i < hashmap->map.capacity; i++)
        {
            init(vector_get(hashmap->map, i));
        }
    }
    hashmap->compare = compare;
    hashmap->hash = hash;
    hashmap->exists = exists;
    return 0;
}

int free_hashmap(hashmap_t *hashmap)
{
    free_vector(hashmap->map);
    return 0;
}

int hashmap_set(hashmap_t hashmap, void *item)
{
    int hash = hashmap.hash(item);
    if (vector_set(hashmap.map, item, hash))
    {
        printf("Error: Hashmap cannot set");
    }
    return 0;
}

void *hashmap_get(hashmap_t hashmap, void *item)
{
    int hash = hashmap.hash(item);
    void *item_maybe = vector_get(hashmap.map, hash);
    if (hashmap.exists(item_maybe) && hashmap.compare(item, item_maybe)){
        return item_maybe;
    }
    return NULL;
}

int hashmap_convert_to_vector(hashmap_t hashmap, vector_t *vector)
{
    int i;
    for (i = 0; i < hashmap.map.capacity; i++)
    {
        void *item = vector_get(hashmap.map, i);
        if (hashmap.exists(item))
        {
            vector_push_back(vector, item);
        }
    }

    return 0;
}