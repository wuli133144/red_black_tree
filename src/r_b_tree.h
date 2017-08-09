
 /*
 Copyright <YEAR> <COPYRIGHT HOLDER>
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/*jackwu  2017-8-9 14:23*/


#ifndef    __R_B_TREE_H
#define    __R_B_TREE_H

#define null       NULL

#include <stdio.h>
#include <stdlib.h>

typedef   enum{BLACK,RED}color_t;

typedef struct _rb_tree_node{
       int key;
       int value;
       void *ex; /*value*/
       struct  _rb_tree_node *lchild;
       struct _rb_tree_node  *rchild;
       color_t color;
}rbtree_node;


typedef struct _root_{
       struct __rb_tree_node rootnode;
}root_t;


/*globol */
root_t *root=null;

/*init black red tree*/
 void initroot(root_t *root){
        if(root==null){
             root=(root_t *)malloc(sizeof(root_t));
        }

        root->rootnode.color=BLACK;
        root->rootnode.lchild=null;
        root->rootnode.rchild=null; 
 }



        
    





#endif 


