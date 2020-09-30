#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include"vector.h"
#include"tree.h"
#include<getopt.h>

#define STMT_MAX 1024*1024

typedef struct _String
{
    u_int64_t   string_size;
    char*       string_ptr;
}_String;

typedef struct stmt
{
   int stmt_statment;
   c_vector* vector_stmt;
}stmt;

typedef struct chache_stmt
{
    u_int64_t   now_offset;
    u_int64_t   size;   
    char* chache;
}chache_stmt;

typedef struct Global
{
    int mode;
    char* field_name;
    char* table_alias_name;
    char* database_name;
    char* real_field_name;
    char* file_name;
    
    int count;
    Tree_Node* root;                //语句序列的ROOT节点
    chache_stmt* ptr_chache;
}Global;

enum
{
    ALL_MODE,
    GET_MODE,
    PHYSICAL_MODE,
    TEST_MODE,
    BACK_STMT,
    LIUYU_MODE,
};

typedef struct select_info
{
    char name[30];
    c_vector* vector_field;         //field_info
    c_vector* vector_opt;           //Node*
    c_vector* vector_table;
    c_vector* vector_where;
    c_vector* vector_group_by;
    c_vector* vector_having;
    c_vector* vector_oder_by;
}select_info;

typedef struct obj_info
{
    int type;                       //用来标记是否为子查询
    Tree_Node* obj_name;            //记录字段的名字
    Tree_Node* obj_alias;           //记录字段的别名
    Tree_Node* obj_condition;       //记录改字段的条件
    c_vector* obj_field;            //指向同一个SELECT下面可能对应的字段信息
    Tree_Node* select_select;       //记录为子查询的节点（no use）
}obj_info;

typedef struct field_info
{
    int type;
    Tree_Node* field_name;
    Tree_Node* field_alias;
    c_vector* field_table;
    Tree_Node* field_table_info;
    c_vector* field_physical_info;
    Tree_Node* select_select;
}field_info;

struct Global _Global;
struct stmt _stmt;

void usage();                                           //提示怎么输入的提示函数
FILE* parse_getopt(int argc,char** argv);                 //命令行解析函数和
void Init_stmt_vector();
void Init_select_info_vector(select_info* select_con);
void Del_stmt_vector();
void Del_select_info_vector();

void Main_mode();

void Main_struct(Tree_Node* enum_man,char* name);
void Get_select_info(Tree_Node* enum_man,select_info* select_con);
void Get_opt_info(Tree_Node* enum_man,select_info* select_con);
void Get_field_info(Tree_Node* enum_man,select_info* select_con);
void Get_field_info_child(Tree_Node* enum_man,select_info* select_con);
void Get_table_info(Tree_Node* enum_man,select_info* select_con);
void Get_table_info_child(Tree_Node* enum_man,select_info* select_con);
void Normal_get_info(Tree_Node* enum_man,select_info* select_con);
void Join_get_info(Tree_Node* enum_man,select_info* select_con);
void Enum_get_opt_where_condition(Tree_Node* enum_man,select_info* select_con);
void Enum_get_group_by(Tree_Node* enum_man,select_info* select_con);
void Enum_get_having(Tree_Node* enum_man,select_info* select_con);
void Enum_get_oder_by(Tree_Node* enum_man,select_info* select_con);

void Show_stmt_info();
void Show_the_filed_info();
void Show_all_physical_table();

int Single_search_stmt(char* search);
void All_table(select_info* tem_stmt);
int Search_select_info_table(select_info* tem_stmt);
/*
*   将每一层抽象里面的表和字段的vector对应起来
*/
int Connect_field_table(select_info* tem_stmt);
void Connect_enum_main();
int Connect_field_table_child(select_info* tem_stmt,field_info* tem_field);

void Subquery_get_info(char* search,char* real_field_name,field_info* save_field);

//将字段信息切割 为 database table filed 的格式
int Str_cut_for_real_alias(char* field_name,char** database_name,char** table_alias_name,char** real_field_name);
void All_table_this_floor(select_info* tem_stmt,char* real_field_name,field_info* save_field);

void Get_back_stmt(stmt* back_stmt);
void Find_main(stmt* back_stmt,c_vector* main_select_info);
int Show_select_info(select_info* main_select,c_vector* union_stmt,stmt* back_stmt);
char* Get_subquery_stmt(char* search,stmt* back_stmt);
void Find_sub(stmt* back_stmt,c_vector* main_select_info,char* search);
void Init_chache_stmt();
_String* Insert_str(char* str);
void Expend_chache();
void Show_string(_String* string);