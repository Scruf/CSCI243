#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
int str_to_int( char str_score[] ) {

        int value = 0;
        for ( int j = 0; str_score[j] != '\0'; ++j ) {

                if ( isdigit( str_score[j] ) ) {
                        value = value * 10 + (str_score[j] - '0');

                }
                else if(str_score[j]=='-') {
                        continue;
                }
                else {
                        // stop on finding the first non-numeric digit.
                        break; // the value is not an integer.
                }
        }
        return value;
}
void insert_node_helper(TreeNode **root,int el){
        if(*root==0) {
                *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
                (*root)->data = el;
                (*root)->left=NULL;
                (*root)->right=NULL;

        }
        else{
                if(el>(*root)->data)
                        insert_node_helper(&((*root)->right),el);
                else{
                        if(el<(*root)->data)
                                insert_node_helper(&((*root)->left),el);
                        else
                                printf("duplicate value");
                }
        }
}
void build_tree(TreeNode** root, const int elements[], const int count){
        for(int i=0; i<count; i++) {
                insert_node_helper(root,elements[i]);
        }
}

void traverse(const TreeNode* root, const TraversalType type){

        switch(type) {
        case INORDER:
              if(root!=0){
                traverse((root)->left,INORDER);
                printf("%d\n",(root)->data);
                traverse((root)->right,INORDER);

              }
        }

}
int main(int argc, char *argv[]){
        if (argc<2) {
                printf("Usage: bst #");
                exit(-1);
        }
        int number_of_elements=0;
        //  check if the number is negative
        char temp[sizeof(argv[1])];
        strcpy(temp,argv[1]);
        if (temp[0]=='-')
        {
                number_of_elements=str_to_int(temp)*(-1);
        }
        else {
                number_of_elements=str_to_int(argv[1]);
        }
        if(number_of_elements<=0) {
                printf ("%d must be greater than 0",number_of_elements);
        }
        int bst_array[number_of_elements];
        printf("Enter %d integers values to place in the tree:\n",number_of_elements);
        for (int i=0; i<number_of_elements; i++) {
                char number[2];
                scanf("%s",number);
                int num = str_to_int(number);
                bst_array[i]=num;
        }
        printf("\nInput Values:\n");
        for(int i=0; i<number_of_elements; i++) {
                printf("%d\n",bst_array[i]);
        }
        TreeNode *root= NULL;
        build_tree(&root,bst_array,number_of_elements);
        printf("Inorder traversal\n");
        traverse(root,INORDER);
        return 0;
}
