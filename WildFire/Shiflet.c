#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "display.h"
#include "helper.h"
#include "Shiflet.h"
void init_forest(int size,char forest[size][size]){
        for(int i=0; i<size; i++) {
                for(int j=0; j<size; j++) {
                        forest[i][j]='Y';
                }
        }

}
float calc_neighbors(int row,int col,char forest[row][col]){
        const int NEIGHBOR = 8;
        int trees_fire = 0,count = 0;
        if (row-1<0 || col-1 <0|| forest[row-1][col-1]==' ')
                count++;
        else if(forest[row-1][col-1]=='*')
                trees_fire++;
        if (row<0 || col-1<0 || forest[row][col-1]==' ')
                count++;
        else if(forest[row][col-1]=='*')
                trees_fire++;
        if(row+1<0 || col-1<0 || forest[row+1][col-1]==' ')
                count++;
        else if(forest[row+1][col-1]=='*')
                trees_fire++;
        if(row-1<0 || col<0 || forest[row-1][col]==' ')
                count++;
        else if(forest[row-1][col]=='*')
                trees_fire++;
        if(row+1<0 ||col<0 || forest[row+1][col]== ' ')
                count++;
        else if(forest[row+1][col]== '*')
                trees_fire++;
        if(row-1< 0 || col+1< 0 || forest[row-1][col+1] == ' ')
                count++;
        else if(forest[row-1][col+1] == '*')
                trees_fire++;
        if(row<0 || col+1< 0 || forest[row][col+1]== ' ')
                count++;
        else if(forest[row][col+1]== '*')
                trees_fire++;
        if(row+1<0 || col+1<0 || forest[row+1][col+1] == ' ')
                count++;
        else if(forest[row+1][col+1] == '*')
              trees_fire++;
        float total = (NEIGHBOR-count)/100;
        float percent = ((float)trees_fire/total);

}
int spread(int row,int col, char forest [row][col],double probability){
        if(calc_neighbors(row,col,forest)>26 && forest[row][col]=='Y') {
                return rand()%101 < probability ? 1 : 0;
        }
}
