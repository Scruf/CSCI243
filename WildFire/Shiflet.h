#ifndef SHIFLET_H
#define SHIFLET_H
void init_forest(int size,char forest[size][size]);

void apply_burn(int size,char forest[size][size],int changes,float probability,float density,float proportion,int pn_option);

void apply_fire(int size,char arr[size][size],int density, float proportion);
#endif
