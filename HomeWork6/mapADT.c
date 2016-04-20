#include <stdbool.h>
#include <stdlib.h>
//@param keys - will hold the key
//@param value - will hold  the value
//@param size will hold the size


struct mapADT {
        void **keys;
        void **values;
        bool (*equals)(const void *a,const void *b);
        int size;
};
typedef struct mapADT *MapADT;
#define _MAP_IMPL_
#include "mapADT.h"
/// Create a MapADT which uses the supplied function as a equals
/// routine.
MapADT map_create( bool (*equals)(const void *a,const void *b) ){
        MapADT map;
        map = (MapADT)malloc(sizeof(struct mapADT));
        if(map!=0) {
                map->equals = equals;
        }
        return (map);


}
/// Tear down and deallocate the supplied MapADT.
///
/// @param map - the MapADT to be manipulated
void map_destroy( MapADT map ){

      free(map->keys);
      free(map->values);



}
/// Remove all contents from the supplied MapADT.
///
/// @param map - the MapADT to be manipuated

void map_clear( MapADT map ){
        map->size = 0;
        map->keys = realloc(map->keys,0);
        map->values = realloc(map->values,0);



      }
      /// Check if the specified entry exists in the map
      ///
      /// Uses the map's equals function to determine if an entry with
      /// the same key already exists in the map. If so, then return
      /// true.
bool map_contains(MapADT map, void *key){
        for ( int i = 0; i < map->size ;i++) {

                  if (map->equals(key,map->keys[i]))
                          return true;
                }
        return false;
}
/// Put the specified entry into the Map
///
/// Uses the map's equals function to determine if an entry with
/// the same key already exists in the map. If so, then replace it
/// and return a pointer to the old value.
///
void* map_put( MapADT map, void *key, void *value){
        if (map_contains(map,key)) {

                const void *temp = map_get(map,key);
                void *temp_val = (unsigned *)map_get(map,key);
                temp_val=value;
                return (unsigned *)temp;
        }else{

                map->size++;
                map->keys=realloc(map->keys,sizeof(void*)*map->size);
                map->values=realloc(map->values,sizeof(void*)*map->size);
                map->keys[map->size-1]=key;
                map->values[map->size-1]=value;

              }
}
/// Find the entry specified by the key and return a pointer to the value
///
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

/// Find the entry specified by the key and remove it from the MapADT,
/// returning the value pointer.
void *map_delete( MapADT map, void *key ){
        if (map_empty(map)) {
                exit(EXIT_FAILURE);
        }else{
        for ( int i = 0; i < map->size; i++) {
                if (map->equals(key,map->keys[i])) {
                        map->size--;
                        void *value = map->values[i];
                        free(map->keys[i]);
                        return value;
                }
        }
      }
        return NULL;


}
bool map_empty( MapADT map ){
        return map->size==0;
}
