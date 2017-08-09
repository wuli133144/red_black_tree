
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


#include  <stdio.h>  /*standard io lib*/
#include  <malloc.h> /* malloc lib*/

#include <assert.h>
#define null       NULL


#define DEBUG_P(condition) do{                                     \
             fprintf(stdout,">>>>>>%d%-60s-",__LINE__,#condition);\
             if(condition){puts("ok\n");}else{puts("failed\n");}     \
} while(0);




typedef   enum{BLACK,RED}color_t;


typedef struct _rb_tree_node{
       int key;
       int value;
       int count;
       struct _rb_tree_node *parent;
       int flag;
       void *ex; /*value*/
       struct  _rb_tree_node *lchild;
       struct  _rb_tree_node  *rchild;
       color_t color;
}rbtree_node;


//struct _rb_tree_node 



/*globol */
 

/*init black red tree*/
 void initroot(struct _rb_tree_node **_root,int key){
        if((*_root)==null){
             (*_root)=(struct _rb_tree_node*)malloc(sizeof(struct _rb_tree_node));
        }
        
        (*_root)->color=BLACK;
        (*_root)->lchild=null;
        (*_root)->rchild=null;
        (*_root)->parent=null;
        (*_root)->key=key;
        (*_root)->count=0;
        (*_root)->flag=1;/*1 express parent root*/
 }


/*left rotate 
  graph:
        a                                         b
                                                  /\
        / \                                      a    y
                                                 /\
       c   b        =====>                       c  z  
           /\
           z y
*/

void left_rotate(rbtree_node *root,rbtree_node *node){
       DEBUG_P(node->rchild==null);
      
                             rbtree_node *x=node->rchild;
                             if(x!=null){
                                    color_t c=node->color;
                                    node->rchild=x->lchild;
                                    x->lchild->parent=node;
                                   
                              }
                              x->lchild=node; /*x is not null*/
                              if(x->parent=node->parent){
                                       if(node==node->parent->rchild){
                                             node->parent->rchild=x;
                                       }else {
                                             node->parent->lchild=x;
                                       }
                                }else{
                                    root=x;
                                }

                              node->parent=x;
      
}



/*right_rotate
  graph:
        a                                b
        /\                              /\
       b  e            =======>        c   a
      /  \                                /  \
    c     d                               d   e
        
*/
void right_rotate(rbtree_node *root,rbtree_node *node){
      rbtree_node *x=node->lchild;
      if(x!=null){
                  node->lchild=x->rchild;
                  x->rchild->parent=node;
                
      }
      x->rchild=node;
      if(x->parent=node->parent){
            if(node==node->parent->lchild){
                  node->parent->lchild=x;
            }else{
                  node->parent->rchild=x;
            }
      }
      if(x->parent==null){/*x is root*/
           root=x;
      }
      node->parent=x;        
}    


rbtree_node *alloc(int value){
      rbtree_node *item=(rbtree_node *)malloc(sizeof(rbtree_node));
      item->value=value;
      item->parent=item->lchild=item->rchild=null;
      item->flag=0;/*express child node*/
      item->color=RED;
      item->count=0;
      
      return item;
}

void print(struct _rb_tree_node *node){
     fprintf(stdout,"[(%d,%d)(count:%d)(color:%d)]\n",node->key,node->value,node->count,node->color);
     return;
}

void showinfo(struct _rb_tree_node *root){
     //assert(root==null);
     
     while(root!=null){
            showinfo(root->lchild);
            print(root);
            showinfo(root->rchild);
     }
     

}


#define set_red(x)              x->color==RED
#define set_black(x)            x->color==BLACK

/*return suitable position*/
struct _rb_tree_node *find_suit_node(struct _rb_tree_node *root,int value){

        struct _rb_tree_node *item=root;
        if(item->count==0){return null;}/*just root node*/
        while(item){
                  if(item->key>value){
                        item=item->lchild;
                  }else if(item->key<value){
                        item=item->rchild;
                  }else{
                        DEBUG_P(item->key==value)
                        return NULL;
                  }
        }
        struct _rb_tree_node *temp=item->parent;
        return temp;
}


void insert(struct _rb_tree_node *_root/*head root*/,int value){
       
       rbtree_node *node=alloc(value);
       rbtree_node *parent_temp=find_suit_node(_root,value);

       /*如果只有一个2节点*/
       if(_root->count==0)/*just one */
       {     
           
           if(value>_root->key){/**/
                _root->rchild=node;
                left_rotate(_root,node);/*left rotate root node*/

           }else{
                 _root->lchild=node;
           }
           _root->count++;
       }else{/*2-node and 3-node*/
            
            /*only 2 node*/
            if(parent_temp->color==BLACK){/*just 2 node transfor 3 node it's ok*/
             if(parent_temp->key>value){
                   parent_temp->lchild=node;
                   node->parent=parent_temp;
                   _root->count++;
             }else{
                   parent_temp->rchild=node;
                   node->parent=parent_temp;
                   _root->count++;
             }
               /*don't modify color because node is red*/
            }else if(parent_temp->color==RED&&parent_temp->parent->color==RED){/*many kinds of isues*/
                   /*error there is 4 node*/
                   if(parent_temp->key>value){
                   parent_temp->lchild=node;
                   node->parent=parent_temp;
                   
                   right_rotate(_root,parent_temp);
                   set_black(parent_temp);/*set color*/
                   //set_red(parent_temp->parent);
                   _root->count++;
                  }else{
                         parent_temp->lchild=node;
                         node->parent=parent_temp;
                         left_rotate(_root,parent_temp);
                         set_black(parent_temp);/*set color*/
                        _root->count++;
                  } 

            }else if(parent_temp->color==RED&&parent_temp->parent->color==BLACK){

                  



            }


          


       
}


#endif 


