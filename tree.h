#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define CHARSIZE 500

enum
{
 TABLE_NAME = 2048,
 ALIAS_NAME,
 SKIP_OPT,
 FIELD_NAME,
 EXPRESSION,
 SELECT_OPT,
 FIELD_INFO_BEGIN,
 SELECT_OPT_BEGIN, 
 STRING_NAME,
 SELECT_SELECT,
 STRING_NUM,
 CONCAT_BEGIN,
 CASE_BEGIN,
 FLOOR_BEGIN,
 FIELD_NODE,

 TABLE_REFERENCE,
 TABLE_INFO,
 NORMAL_TABLE,
 JOIN_TABLE,
 JOIN_CONDITION,
 TABLE_SUB,
 JOIN_TABLE_1,
 JOIN_TABLE_2,
 JOIN_TABLE_3,
 JOIN_TABLE_4,
 JOIN_TABLE_5,
 OPT_WHERE,
 OPT_GROUP_BY,
};


typedef struct Tree_Node
{
   char* RHS;
   int type;
   struct  Tree_Node*  Parent;
   struct  Tree_Node*  L_child;
   struct  Tree_Node*  R_child;
}Tree_Node;


typedef struct Tree
{
   char* name;
   Tree_Node* Root;
}Tree;


Tree* New_tree(char* name,int type,char* RHS);
void Delete_tree(Tree_Node* delete_man);
void Delete(Tree* tem);
void Delete_node(Tree_Node* tem);
Tree_Node* Insert_tree_as_L(Tree_Node* parent,int type,char* RHS);
Tree_Node* Insert_tree_as_R(Tree_Node* parent,int type,char* RHS);
void Enum_tree_node_deep(Tree_Node* enum_man);
void Enum_tree(Tree* tem);
Tree_Node* Create_new_node(int type,char* RHS);
