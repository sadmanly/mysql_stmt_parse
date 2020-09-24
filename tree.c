#include"tree.h"

Tree* New_tree(char* name,int type,char* RHS)
{
    Tree* tem = (Tree*)malloc(sizeof(Tree));
    if(tem == NULL) return NULL;
    tem->name = (char*)malloc(strlen(name));
    if(tem->name == NULL) return NULL;
    memcpy(tem->name,name,strlen(name));
    tem->Root = (Tree_Node*)malloc(sizeof(Tree_Node));
    if(tem->Root == NULL) return NULL;
    memset(tem->Root,0,sizeof(Tree_Node));
    tem->Root->L_child = NULL;
    tem->Root->R_child = NULL;
    tem->Root->Parent = NULL;
    tem->Root->type = type;

    tem->Root->RHS = (char*)malloc(strlen(RHS)+1); 
    memcpy(tem->Root->RHS,RHS,strlen(RHS));
    return tem;
}

void Delete_tree(Tree_Node* delete_man)
{
    if(delete_man == NULL)
    {
        return;
    }
    Delete_tree(delete_man->R_child);
    Delete_tree(delete_man->L_child);
    free(delete_man->RHS);
    delete_man->RHS=NULL;
    free(delete_man);
    delete_man = NULL;
}

void Delete(Tree* tem)
{
    free(tem->name);
    Delete_tree(tem->Root);
}

void Delete_node(Tree_Node* tem)
{
    free(tem);
}

Tree_Node* Insert_tree_as_L(Tree_Node* parent,int type,char* RHS)
{
    Tree_Node* L_child =  (Tree_Node*)malloc(sizeof(Tree_Node));
    L_child->Parent = parent;
    parent->L_child = L_child;
    L_child->L_child = NULL;
    L_child->R_child = NULL;
    L_child->type = type;

    L_child->RHS = (char*)malloc(strlen(RHS)+1); 
    memcpy(L_child->RHS,RHS,strlen(RHS));
    return L_child;
}


Tree_Node* Insert_tree_as_R(Tree_Node* parent,int type,char* RHS)
{
    Tree_Node* R_child =  (Tree_Node*)malloc(sizeof(Tree_Node));
    R_child->Parent = parent;
    parent->R_child = R_child;
    R_child->L_child = NULL;
    R_child->R_child = NULL;
    R_child->type = type;

    R_child->RHS = (char*)malloc(strlen(RHS)+1); 
    memcpy(R_child->RHS,RHS,strlen(RHS));
    return R_child;
}

void Enum_tree_node_deep(Tree_Node* enum_man)
{
    if(enum_man == NULL)
    {
        return;
    }
    Enum_tree_node_deep(enum_man->L_child);
    printf("%s\n",enum_man->RHS);
   // printf("RHS : %s\n",enum_man->RHS);
   // printf("type : %d\n",enum_man->type);
    Enum_tree_node_deep(enum_man->R_child);
}


void Enum_tree(Tree* tem)
{
    printf("Tree name: %s\n",tem->name);
    Enum_tree_node_deep(tem->Root);
}

Tree_Node* Create_new_node(int type,char* RHS)
{
    Tree_Node* tem = (Tree_Node*)malloc(sizeof(Tree_Node));
    if(tem == NULL)
        return NULL;
    tem->L_child = NULL;
    tem->R_child = NULL;
    tem->Parent = NULL;
    tem->type = type;
    tem->RHS = (char*)malloc(strlen(RHS)+1);    
    memcpy(tem->RHS,RHS,strlen(RHS)+1);
    return tem;
}



