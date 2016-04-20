#include <stdbool.h>
#include <stdlib.h>
struct mapADT {
        void **keys;
        void **values;
        bool (*equals)(const void *a,const void *b);
        int size;
};
typedef struct mapADT *MapADT;
#define _MAP_IMPL_
#include "mapADT.h"
MapADT map_create( bool (*equals)(const void *a,const void *b) ){
        MapADT map;
        map = (MapADT)malloc(sizeof(struct mapADT));
        if(map!=0) {
                map->equals = equals;
        }
        return (map);


}
void map_destroy( MapADT map ){
        for(unsigned int i = 0; i < map->size; i++) {
                free(map->keys[i]);
                free(map->values[i]);
                free(map->equals);
                free(map);

        }
}
void map_clear( MapADT map ){
        map->size = 0;
        map->keys = realloc(map->keys,0);
        map->values = realloc(map->values,0);
        map->equals = realloc(map->equals,0);
}
bool map_contains(MapADT map, void *key){
        for (unsigned int i = 0; i < map->size; i++) {

                if (map->equals(key,map->keys[i]))
                        return true;
        }
        return false;
}
void* map_put( MapADT map, void *key, void *value){
        if (map_contains(map,key)) {

                const void *old = map_get(map,key);
                void *r = (unsigned int*)map_get(map,key);
                r=value;
                return (unsigned *)old;
        }else{

                map->size++;
                map->keys=realloc(map->keys,sizeof(void*)*map->size);
                map->values=realloc(map->values,sizeof(void*)*map->size);
                map->keys[map->size-1]=key;
                map->values[map->size-1]=value;
                return value;
              }
}
const void *map_get( MapADT map, void *key ){
        if (map_empty(map)) {
                exit(EXIT_FAILURE);
        }
        for (unsigned int i = 0; i <map->size; i++) {
                if (map->equals(key,map->keys[i]))
                        return map->values[i];
        }
        return NULL;
}

//user mapclear
void *map_delete( MapADT map, void *key ){
        if (map_empty(map)) {
                exit(EXIT_FAILURE);
        }
        for (unsigned int i = 0; i < map->size; i++) {
                if (map->equals(key,map->keys[i])) {
                        map->size--;
                        return map->values[i];
                }
        }
        return NULL;
}
bool map_empty( MapADT map ){
        return map->size==0;
}
