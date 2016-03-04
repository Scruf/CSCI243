#ifndef SHIFLET_H
#define SHIFLET_H
void init_forest(int size,char forest[size][size]);
int spread(int row,int col,char forest[row][col],double probability);
void apply_burn(int size,char forest[size][size],int arguments,int changes,double probability,double density,double proportion,int pn_option);
float calc_percent(int row,int col,char forest[row][col]);
void apply_fire(int size,char arr[size][size],int density, int proportion);
#endif
