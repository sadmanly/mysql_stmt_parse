#include"Main_act.h"

void Main_mode()
{
    if(_Global.mode == GET_MODE)
    {
        Str_cut_for_real_alias(_Global.field_name,&_Global.database_name,&_Global.table_alias_name,&_Global.real_field_name);
        Connect_enum_main();
        Show_the_filed_info(_Global.field_name);
    }
    else if(_Global.mode == ALL_MODE)
    {
        Connect_enum_main();
        Show_stmt_info();
    }
    else if(_Global.mode == PHYSICAL_MODE)
    {
        Connect_enum_main();
        Show_all_physical_table();
    }
    else if(_Global.mode == TEST_MODE)
    {
        printf("%s",_Global.ptr_chache->chache);
    }
    else if(_Global.mode == BACK_STMT)
    {
        Connect_enum_main();
        Get_back_stmt(&_stmt);
    }
    else if(_Global.mode == LIUYU_MODE)
    {


    }

}

void Init_stmt_vector()
{
    _stmt.vector_stmt = Init_vector(10);
    _Global.count=0;
    _Global.ptr_chache = (chache_stmt*)calloc(sizeof(chache_stmt),1);
    Init_chache_stmt();
}

void Init_chache_stmt()
{
    _Global.ptr_chache->size = STMT_MAX;
    _Global.ptr_chache->now_offset = 0;
    _Global.ptr_chache->chache = (char*)calloc(_Global.ptr_chache->size,1);   
    if(_Global.ptr_chache->chache == NULL)
    {
        exit(0);
    }
}

void Expend_chache()
{
    _Global.ptr_chache->chache = (char*)realloc(_Global.ptr_chache->chache,_Global.ptr_chache->size*2);
    if(_Global.ptr_chache->chache == NULL)
    {
        exit(0);
    }
}

void Show_string(_String* string)
{
    int         i;

    for(i = 0;i<string->string_size;i++)
    {
        printf("%c",string->string_ptr[i]);
    }
}

void Init_select_info_vector(select_info* select_con)
{
    //  select_con->vector_test = Init_vector(10);
     select_con->vector_where = Init_vector(20); 
     select_con->vector_field = Init_vector(10);  
     select_con->vector_table = Init_vector(10); 
     select_con->vector_group_by = Init_vector(10);
     select_con->vector_opt = Init_vector(10);
     select_con->vector_having = Init_vector(10);
     select_con->vector_oder_by = Init_vector(10);;
}

void Del_stmt_vector()
{
    Del_vector(_stmt.vector_stmt);
    _stmt.vector_stmt = NULL;
}

void Del_select_info_vector()
{
    int i;
    for(i=0;i<_stmt.vector_stmt->curr_size;i++)
    {
        select_info* select_con = (select_info*)Vetor_get(_stmt.vector_stmt,i);
        Del_vector(select_con->vector_field);
        select_con->vector_field = NULL;
        Del_vector(select_con->vector_table);
        select_con->vector_table = NULL;
        Del_vector(select_con->vector_where);
        select_con->vector_where = NULL;
        Del_vector(select_con->vector_group_by);
        select_con->vector_group_by = NULL;
        Del_vector(select_con->vector_opt);
        select_con->vector_opt = NULL;
        Del_vector(select_con->vector_having);
        select_con->vector_having = NULL;
        Del_vector(select_con->vector_oder_by);
        select_con->vector_oder_by = NULL;
    }
}

void Main_struct(Tree_Node* enum_man,char* name)
{
    if(enum_man == NULL) return;
    if(enum_man->type == END)
    {
        select_info* select_con= (select_info*)malloc(sizeof(select_info));
        memset(select_con,0,sizeof(select_info));
        memcpy(select_con->name,name,strlen(name)+1);
        Init_select_info_vector(select_con);
        Get_select_info(enum_man,select_con);
        Vector_push_back(_stmt.vector_stmt,select_con);
        return;
    }
    Main_struct(enum_man->L_child,name);
    Main_struct(enum_man->R_child,name);
}

void Get_select_info(Tree_Node* enum_man,select_info* select_con)
{
    
    Get_opt_info(enum_man->R_child->L_child,select_con); //得到选项信息
    Tree_Node* tem = enum_man->R_child->R_child;
    // printf("%s" ,tem->RHS);
    if(tem->L_child == NULL)      //处理是*的字段信息
    {
        field_info* tem_struct = (field_info*)malloc(sizeof(field_info));
        if(tem_struct == NULL)
        {
            printf("malloc NULL");
            exit(0);
        }
        tem_struct->type = 0;
        tem_struct->field_name = tem;
        Vector_push_back(select_con->vector_field,tem_struct);
    }
    Get_field_info(tem->L_child,select_con);   //处理普通字段信息
    /*按照特定的规则遍历得到表的信息*/
    tem = tem->R_child;  
    if(tem == NULL)
    {
        return;
    }
    Get_table_info(tem->L_child,select_con);  //处理表信息
    tem = tem->R_child;
    Enum_get_opt_where_condition(tem,select_con);
    tem = tem->R_child;
    Enum_get_group_by(tem,select_con);
    tem = tem->R_child;
    Enum_get_having(tem,select_con);
    tem = tem->R_child;
    Enum_get_oder_by(tem,select_con);
}

void Get_opt_info(Tree_Node* enum_man,select_info* select_con)
{
    if(enum_man == NULL)
    {
        return;
    }
    Get_opt_info(enum_man->R_child,select_con);
    if(enum_man->type == SELECT_OPT)
    {
        Vector_push_back(select_con->vector_opt,enum_man);
    }
    Get_opt_info(enum_man->L_child,select_con);
}

void Get_field_info(Tree_Node* enum_man,select_info* select_con)
{
    if(enum_man == NULL) return;
    if(enum_man->type == FIELD_INFO_BEGIN && enum_man->L_child->type != FIELD_INFO_BEGIN)
    {
        Get_field_info_child(enum_man->R_child,select_con);  
        Get_field_info_child(enum_man->L_child,select_con);    
        return;
    }
    else if(enum_man->type == FIELD_INFO_BEGIN && enum_man->L_child->type == FIELD_INFO_BEGIN)
    {
        Get_field_info_child(enum_man->R_child,select_con);    
    }
    else
    {
        Get_field_info_child(enum_man,select_con);    
        return;
    }
    Get_field_info(enum_man->L_child,select_con);
}

void Get_field_info_child(Tree_Node* enum_man,select_info* select_con)
{
    Tree_Node* tem = enum_man->L_child;
    field_info* tem_struct = (field_info*)malloc(sizeof(field_info)); 
    memset(tem_struct,0,sizeof(field_info));

    if(tem->type == SELECT_SELECT)
    {
        tem->RHS = (char *)realloc(tem->RHS,strlen(tem->RHS)+30);
        sprintf(tem->RHS,"%s%d)",tem->RHS,_Global.count);
        tem_struct->field_name = tem;
        _Global.count++;
        Main_struct(tem,tem->RHS);
    }
    else
    {
        tem_struct->field_name = tem;
    }
    tem = enum_man->L_child->R_child;
    tem_struct->field_alias = tem;
    Vector_push_back(select_con->vector_field,tem_struct);
}

void Get_table_info(Tree_Node* enum_man,select_info* select_con)
{
    if(enum_man == NULL) return;
    
    if(enum_man->type == TABLE_INFO && enum_man->L_child->type != TABLE_INFO )
    {
       
        Get_table_info_child(enum_man->R_child,select_con);    
        Get_table_info_child(enum_man->L_child,select_con);    
        return;
    }
    else if(enum_man->type == TABLE_INFO && enum_man->L_child->type == TABLE_INFO )
    {
        Get_table_info_child(enum_man->R_child,select_con);    
    }
    else 
    {
        Get_table_info_child(enum_man,select_con);
        return;
    }
    Get_table_info(enum_man->L_child,select_con);
}

void Get_table_info_child(Tree_Node* enum_man,select_info* select_con)
{
   if(enum_man->type == NORMAL_TABLE)
   {
        Normal_get_info(enum_man->L_child,select_con);
   }
   else if(enum_man->type == JOIN_TABLE)
   {
        Join_get_info(enum_man->L_child,select_con);
   }
}

void Normal_get_info(Tree_Node* enum_man,select_info* select_con)
{
    Tree_Node* tem = enum_man;
    obj_info* tem_struct = (obj_info*)malloc(sizeof(obj_info));
    memset(tem_struct,0,sizeof(obj_info));

    if(tem->R_child != NULL && tem->R_child->type == JOIN_CONDITION)
    {
        tem_struct->obj_condition = tem->R_child;
    }

    if(tem->type == TABLE_SUB || tem->type == TABLE_REFERENCE)
    {
        tem = tem->L_child;
    }

    if(tem->type == SELECT_SELECT)
    {
        tem->RHS = (char *)realloc(tem->RHS,strlen(tem->RHS)+30);
        sprintf(tem->RHS,"%s%d)",tem->RHS,_Global.count);
        tem_struct->obj_name = tem;
        _Global.count++;
        Main_struct(tem,tem->RHS);
    }
    else
    {
        tem_struct->obj_name = tem;
    }

    if(enum_man->type == TABLE_SUB || enum_man->type == TABLE_REFERENCE)
    {
        tem =tem->R_child;
    }
    else tem = tem->L_child;
    tem_struct->obj_alias = tem;
    Vector_push_back(select_con->vector_table,tem_struct);
}

void Join_get_info(Tree_Node* enum_man,select_info* select_con)
{
    //处理 table_reference 这个点
    Tree_Node* tem = enum_man->L_child;
  
    Get_table_info(tem,select_con);
    if(enum_man->type == JOIN_TABLE_1)
    {
        tem = tem->R_child->R_child;
    }
    else if(enum_man->type == JOIN_TABLE_2)
    {
        tem = tem->R_child;
    }
    else if(enum_man->type == JOIN_TABLE_3)
    {
        tem = tem->R_child;
    }
    else if(enum_man->type == JOIN_TABLE_4)
    {
        tem = tem->R_child->R_child->R_child;
    }
    else if(enum_man->type == JOIN_TABLE_5)
    {
        tem = tem->R_child->R_child;
    }
    Normal_get_info(tem,select_con);
}

 void Enum_get_opt_where_condition(Tree_Node* enum_man,select_info* select_con)
 {

     if(enum_man->type == OPT_WHERE)
     {

        if(enum_man->L_child != NULL &&  enum_man->L_child->type == SELECT_SELECT)
        {
            enum_man->L_child->RHS = (char*)realloc(enum_man->L_child->RHS,strlen(enum_man->L_child->RHS)+10);
            sprintf(enum_man->L_child->RHS,"%s%d)",enum_man->L_child->RHS,_Global.count);
            _Global.count++;
            char* tem_name = strchr(enum_man->L_child->RHS,'(');
            Main_struct(enum_man->L_child,tem_name);
        }
        Vector_push_back(select_con->vector_where,enum_man->L_child);
     }
 }

void  Enum_get_group_by(Tree_Node* enum_man,select_info* select_con)
{

    if(enum_man->type == OPT_GROUP_BY)
    {
        if(enum_man->L_child != NULL &&  enum_man->L_child->type == SELECT_SELECT)
        {
            enum_man->L_child->RHS = (char*)realloc(enum_man->L_child->RHS,strlen(enum_man->L_child->RHS)+10);
            sprintf(enum_man->L_child->RHS,"%s%d)",enum_man->L_child->RHS,_Global.count);
            _Global.count++;
            char* tem_name = strchr(enum_man->L_child->RHS,'(');
            Main_struct(enum_man->L_child,tem_name);
        }
        Vector_push_back(select_con->vector_group_by,enum_man);
    }
}

void Enum_get_having(Tree_Node* enum_man,select_info* select_con)
{
    if(enum_man->type == HAVING)
    {
        if(enum_man->L_child != NULL &&  enum_man->L_child->type == SELECT_SELECT)
        {
            enum_man->L_child->RHS = (char*)realloc(enum_man->L_child->RHS,strlen(enum_man->L_child->RHS)+10);
            sprintf(enum_man->L_child->RHS,"%s%d)",enum_man->L_child->RHS,_Global.count);
            _Global.count++;
            char* tem_name = strchr(enum_man->L_child->RHS,'(');
            Main_struct(enum_man->L_child,tem_name);
        }
        Vector_push_back(select_con->vector_having,enum_man);
    }
}

void Enum_get_oder_by(Tree_Node* enum_man,select_info* select_con)
{
    if(enum_man->type == ORDER)
    {
        if(enum_man->L_child != NULL &&  enum_man->L_child->type == SELECT_SELECT)
        {
            enum_man->L_child->RHS = (char*)realloc(enum_man->L_child->RHS,strlen(enum_man->L_child->RHS)+10);
            sprintf(enum_man->L_child->RHS,"%s%d)",enum_man->L_child->RHS,_Global.count);
            _Global.count++;
            char* tem_name = strchr(enum_man->L_child->RHS,'(');
            Main_struct(enum_man->L_child,tem_name);
        }
        Vector_push_back(select_con->vector_oder_by,enum_man);
    }
}

/*-------------------------打印每一层的所有存储的信息----------------------*/
void Show_stmt_info()
{
    int            i,j,k;
    Tree_Node*     field_physical_info_tem;

    for(i=0;i<_stmt.vector_stmt->curr_size;i++)
    {
        select_info* tem_stmt = (select_info*)Vetor_get(_stmt.vector_stmt,i);
        printf("%s \n",tem_stmt->name);
        // printf("%d",tem_stmt->vector_table->curr_size);
        if(tem_stmt->vector_table->curr_size !=0 ) printf("TABLE : ");
        for(j=0;j<tem_stmt->vector_table->curr_size;j++)
        {
            int c = 0;
            obj_info* tem_obj = (obj_info*)Vetor_get(tem_stmt->vector_table,j);
            if(tem_obj->obj_alias == NULL) c=1; 
            printf("%s ALIAS %s \t",tem_obj->obj_name->RHS,c?"NULL":tem_obj->obj_alias->RHS);
            if ((Tree_Node*)tem_obj->obj_condition != NULL)
            {
                printf("---->条件 :  %s",((Tree_Node*)tem_obj->obj_condition)->RHS);
            }
        }
        if(tem_stmt->vector_table->curr_size !=0 ) printf("\n");

        if(tem_stmt->vector_field->curr_size !=0 ) printf("FIELD : ");
        for(j=0;j<tem_stmt->vector_field->curr_size;j++)
        {
            int c = 0;
            field_info* tem_field = (field_info*)Vetor_get(tem_stmt->vector_field,j);
            if(tem_field->field_alias == NULL) c=1; 
            printf("%s ALIAS %s \t",(tem_field->field_name)->RHS,c?"NULL":tem_field->field_alias->RHS);
            

            for(k = 0;k<tem_field->field_physical_info->curr_size;k++)
            {
                field_physical_info_tem = Vetor_get(tem_field->field_physical_info,k);
                printf("实际联系的物理表测试  ： %s  ",field_physical_info_tem->RHS);
            }

            // if(tem_field->field_table_info == NULL)
            // {
                
            //     printf("属于该层所有表\t");
            // }
            // else
            // {
            //     printf("属于 : %s \t ",tem_field->field_table_info->RHS);
            // }

            printf("\n");

        }
        if(tem_stmt->vector_field->curr_size !=0 ) printf("\n");
       
        if(tem_stmt->vector_where->curr_size != 0 ) printf("条件 : ");
        for(j=0;j<tem_stmt->vector_where->curr_size;j++)
        {
            printf("%s ",((Tree_Node*)Vetor_get(tem_stmt->vector_where,j))->RHS);
        }
        if(tem_stmt->vector_where->curr_size !=0 ) printf("\n");

        if(tem_stmt->vector_group_by->curr_size != 0 ) printf("GROUP_BY : ");
        for(j=0;j<tem_stmt->vector_group_by->curr_size;j++)
        {
            printf("%s ",((Tree_Node*)Vetor_get(tem_stmt->vector_group_by,j))->RHS);
        }
        if(tem_stmt->vector_group_by->curr_size !=0 ) printf("\n");

        if(tem_stmt->vector_having->curr_size != 0 ) printf("HAVING : ");
        for(j=0;j<tem_stmt->vector_having->curr_size;j++)
        {
            printf("%s ",((Tree_Node*)Vetor_get(tem_stmt->vector_having,j))->RHS);
        }
        if(tem_stmt->vector_having->curr_size !=0 ) printf("\n");

        if(tem_stmt->vector_oder_by->curr_size != 0 ) printf("ORDER_BY : ");
        for(j=0;j<tem_stmt->vector_oder_by->curr_size;j++)
        {
            printf("%s ",((Tree_Node*)Vetor_get(tem_stmt->vector_oder_by,j))->RHS);
        }
        if(tem_stmt->vector_oder_by->curr_size !=0 ) printf("\n");

        printf("\n\n");
    }

}

void Show_all_physical_table()
{
    int            i,j,k;
    Tree_Node*     field_physical_info_tem;

    for(i=0;i<_stmt.vector_stmt->curr_size;i++)
    {
        select_info* tem_stmt = (select_info*)Vetor_get(_stmt.vector_stmt,i);
        printf("%s \n",tem_stmt->name);
        for(j=0;j<tem_stmt->vector_field->curr_size;j++)
        {
            field_info* tem_field = (field_info*)Vetor_get(tem_stmt->vector_field,j);
            printf("实际表字段  ：  %20s     实际的物理表  ： ",(tem_field->field_name)->RHS);
            for(k = 0;k<tem_field->field_physical_info->curr_size;k++)
            {
                field_physical_info_tem = Vetor_get(tem_field->field_physical_info,k);
                printf("%30s ",field_physical_info_tem->RHS);
            }
            printf("\n");
        }
        printf("\n\n");
    }

}
/*----------------------------------------------------------------------*/

/*--------------------------查询一个字段实际的物理表----------------------------*/
void Show_the_filed_info()
{
    int             i,j;
    select_info*    tem_stmt;                       //语句的存储结构 
    field_info*     tem_field;                      //字段信息的存储结构
    char*           database_name_tem = NULL;       //将拿出来的字段进行拆分之后的存储位置          ##这里没有释放
    char*           table_alias_name_tem = NULL; 
    char*           real_field_name_tem = NULL;

    for(i=0;i<_stmt.vector_stmt->curr_size;i++)
    {
        tem_stmt = (select_info*)Vetor_get(_stmt.vector_stmt,i);
        /*这里会默认从主函数开始匹配你输入的字段*/
        if(strcmp(tem_stmt->name,"MAIN") == 0)                     
        {
            for(j=0;j<tem_stmt->vector_field->curr_size;j++)
            {
                tem_field = (field_info*)Vetor_get(tem_stmt->vector_field,j);
                Str_cut_for_real_alias(tem_field->field_name->RHS,&database_name_tem,&table_alias_name_tem,&real_field_name_tem);
                if(strcmp(real_field_name_tem,_Global.real_field_name) == 0 || strcmp(real_field_name_tem,"*") == 0)
                {
                    if(tem_field->field_table_info == NULL)   //对应全部表
                    {
                        All_table(tem_stmt);
                    }
                    else     //对应该节点的表
                    {
                        if(tem_field->field_table_info->type == SELECT_SELECT)
                        {
                            Single_search_stmt(tem_field->field_table_info->RHS);
                        }
                        else
                            printf("最终物理表 : %s \t",tem_field->field_table_info->RHS);
                    }

                }

            }
        }
    }
}

/*
* 查询 stmt 层的信息，语句层信息
*/
int Single_search_stmt(char* search)    //遇到select_select会调用该函数
{
    int             i;
    select_info*    tem_stmt;
    int             num_of_stmt = _stmt.vector_stmt->curr_size;    //这个是总的select数量

    for(i=0;i<num_of_stmt;i++)
    {
        tem_stmt = (select_info*)Vetor_get(_stmt.vector_stmt,i);
        if( 0 == strcmp(tem_stmt->name,search))
        {
            //找到子查询的所有信息，找到对应的表
            Search_select_info_table(tem_stmt);   //找到这个表之后继续找对应的字段
        }
    }
    return -1;
}

/*
*  查询 select_info 层表信息    //通过全局变量里面的字段存储了所有信息，得到
*/

int Search_select_info_table(select_info* tem_stmt)
{
    int             i;
    field_info*     tem_field;  //找到字段对应的表，这里应该 _Global.field_name 里面存储了 字段信息
    char*           database_name_tem = NULL;
    char*           table_alias_name_tem = NULL;
    char*           real_field_name_tem = NULL;  //存储输入的信息
    
    //找到该字段 或者 *  之后拿到 字段的别名的表  如果没有就把这一层所有的表输出

    for(i=0;i<tem_stmt->vector_field->curr_size;i++)
    {
        tem_field = (field_info*)Vetor_get(tem_stmt->vector_field,i);
        Str_cut_for_real_alias(tem_field->field_name->RHS,&database_name_tem,&table_alias_name_tem,&real_field_name_tem);
        if(strcmp(real_field_name_tem,_Global.real_field_name) == 0 || strcmp(real_field_name_tem,"*") == 0)
        {
            if(tem_field->field_table_info == NULL)   //对应全部表
            {
                All_table(tem_stmt);
            }
            else     //对应该节点的表
            {
                if(tem_field->field_table_info->type == SELECT_SELECT)
                {
                    Single_search_stmt(tem_field->field_table_info->RHS);
                }
                else
                    printf("最终物理表 : %s \t",tem_field->field_table_info->RHS);
            }
        }
    }
    return 1;
}

void All_table(select_info* tem_stmt)
{
    int             i;
    obj_info*       tem_obj;

    //找到该字段 或者 *  之后拿到 字段的别名的表  如果没有就把这一层所有的表输出

    for(i=0;i<tem_stmt->vector_table->curr_size;i++)
    {
        tem_obj = (obj_info*)Vetor_get(tem_stmt->vector_table,i);               
        if(tem_obj->obj_name->type == SELECT_SELECT)
        {
            Single_search_stmt(tem_obj->obj_name->RHS);
        }
        else
            printf("最终物理表 : %s \t",tem_obj->obj_name->RHS);
    }
}

/*----------------------------------------------------------------------*/
/*将同一层的表 的 字段信息指向他们对应的表  ，这里默认* 会指向所有表*/

void Connect_enum_main()
{   
    int             i=0;
    select_info*    tem_stmt;

    for(i = 0;i < _stmt.vector_stmt->curr_size; i++)
    {
        tem_stmt = Vetor_get(_stmt.vector_stmt,i);
        Connect_field_table(tem_stmt);
    }
}

int Connect_field_table(select_info* tem_stmt)
{
    int             i,size;
    obj_info*       tem_obj;
    field_info*     tem_field;

    size = tem_stmt->vector_field->curr_size;
    for(i = 0;i < size ; i++)
    {
        tem_field = (field_info*)Vetor_get(tem_stmt->vector_field,i);
        tem_field->field_physical_info = Init_vector(10);
        tem_field -> field_table = tem_stmt->vector_table;
        Connect_field_table_child(tem_stmt,tem_field);
    }
    size = tem_stmt->vector_table->curr_size;
    for(i = 0;i < size ; i++)
    {
        tem_obj = (obj_info*)Vetor_get(tem_stmt->vector_table,i);
        tem_obj -> obj_field = tem_stmt->vector_field;
    }
    return 1;
}

int Connect_field_table_child(select_info* tem_stmt,field_info* tem_field)
{
    char*       database_name = NULL;
    char*       table_alias_name = NULL;
    char*       real_field_name = NULL;
    char*       is_l_fun = NULL;
    char*       is_r_fun = NULL;
    int         mode,i = 0;
    obj_info*   tem_obj;

    mode = Str_cut_for_real_alias(tem_field->field_name->RHS,&database_name,&table_alias_name,&real_field_name);

    //如果是函数，就默认用他的别名取查找
    is_l_fun = strchr(tem_field->field_name->RHS,'(');
    is_r_fun = strchr(tem_field->field_name->RHS,')');

    if(
        (tem_field->field_alias != NULL && is_r_fun && is_l_fun && tem_field->field_name->RHS[0]!='(') ||
        (tem_field->field_alias != NULL && is_r_fun && is_l_fun && tem_field->field_name->RHS[1] =='C')     ) 
    {
        free(real_field_name);
        real_field_name = NULL;
        real_field_name = tem_field->field_alias->RHS;
    }

    if(mode == 1)
    {
        tem_field->field_table_info = NULL;
    }
    else
    {
        for(i = 0; i<tem_stmt->vector_table->curr_size ;i++)
        {
            tem_obj = Vetor_get(tem_stmt->vector_table,i);
            if(strcmp(tem_obj -> obj_alias ->RHS,table_alias_name) == 0)
            {
                tem_field->field_table_info = tem_obj->obj_name;
                if(tem_obj->obj_name->type == SELECT_SELECT)
                {
                    Subquery_get_info(tem_obj->obj_name->RHS,real_field_name,tem_field);   //找到该名字的子查询
                }
                else
                {
                    Vector_push_back(tem_field->field_physical_info,tem_obj->obj_name);                   
                }
            }
        }
    }

    if(tem_field->field_table_info == NULL)
    {
        All_table_this_floor(tem_stmt,real_field_name,tem_field);
    }
    return 1;
}


void Subquery_get_info(char* search,char* real_field_name,field_info* save_field)
{
    int             i = 0,j = 0,k = 0,mode_tem = 0;
    int             Flag = 0;
    select_info*    tem_stmt;
    int             num_of_stmt = _stmt.vector_stmt->curr_size;    //这个是总的select数量
    obj_info*       tem_obj;
    field_info*     tem_field;
    char*           database_name_tem = NULL;
    char*           table_alias_name_tem = NULL;
    char*           real_field_name_tem = NULL;  //存储输入的信息        

    //得到原始的字段信息

    for(i=0;i<num_of_stmt;i++)
    {
        tem_stmt = (select_info*)Vetor_get(_stmt.vector_stmt,i);
        if( 0 == strcmp(tem_stmt->name,search))
        {
            //这个为子查询对应的层数
            //匹配该字段
            for(j=0;j<tem_stmt->vector_field->curr_size;j++)
            {
                tem_field = Vetor_get(tem_stmt->vector_field,j);
                mode_tem = Str_cut_for_real_alias(tem_field->field_name->RHS,&database_name_tem,&table_alias_name_tem,&real_field_name_tem);

                if(tem_field->field_alias != NULL && strcmp(tem_field->field_alias->RHS,"NULL") != 0) 
                {
                    free(real_field_name_tem);
                    real_field_name_tem = NULL;
                    real_field_name_tem = tem_field->field_alias->RHS;
                }

                //拿到每一个字段信息的真实名字，和穿进来的比较如果满足和源字段 就匹配相应的表
                
                if(strcmp(real_field_name,real_field_name_tem) == 0 || strcmp("*",real_field_name_tem) == 0)     //如果匹配到相应的表就
                {

                    if(mode_tem == 1)
                    {
                        Flag = 0;
                    }
                    else
                    {
                        
                         for(k=0;k<tem_stmt->vector_table->curr_size;k++)
                         {
                            tem_obj = Vetor_get(tem_stmt->vector_table,k);
                            if( tem_obj->obj_alias != NULL && strcmp(table_alias_name_tem,tem_obj->obj_alias->RHS)==0)
                            {
                                Flag = 1;
                                if(tem_obj->obj_name->type == SELECT_SELECT)
                                {
                                    Subquery_get_info(tem_obj->obj_name->RHS,real_field_name,save_field);   //找到该名字的子查询
                                }
                                else
                                {
                                    Vector_push_back(save_field->field_physical_info,tem_obj->obj_name);                   
                                }
                            }

                         }

                    }

                    if(Flag == 0)
                    {
                        All_table_this_floor(tem_stmt,real_field_name,save_field); 
                    }
                    Flag = 0;
                }
              
            }
        }
    }
}

//匹配所有的表
void All_table_this_floor(select_info* tem_stmt,char* real_field_name,field_info* save_field)
{
    int         k=0;
    obj_info*   tem_obj;

    for(k=0;k<tem_stmt->vector_table->curr_size;k++)
    {
        tem_obj = Vetor_get(tem_stmt->vector_table,k);
        if(tem_obj->obj_name->type == SELECT_SELECT)
        {
            Subquery_get_info(tem_obj->obj_name->RHS,real_field_name,save_field);   //找到该名字的子查询
        }
        else
        {
            Vector_push_back(save_field->field_physical_info,tem_obj->obj_name);                   
        }
    }

}


/*----------------------------------------------------------------------*/
/*field_name 必须有空间  其他不要空间 传出参数 只需要传入一个指针 ，记得最后释放*/
//返回的为 装的个数， a 返回 1  t.a  返回2  liuyu.t.c 返回3
int Str_cut_for_real_alias(char* field_name,char** database_name_cpy,char** table_alias_name_cpy,char** real_field_name_cpy)
{
    char*       tem_ptr = NULL;
    char*       tem_ptr_ptr = NULL;
    char*       table_alias_name = NULL;
    char*       database_name = NULL;
    char*       real_field_name = NULL;


    tem_ptr = strchr(field_name,'.');
    if(tem_ptr != NULL)
        tem_ptr_ptr = strchr(tem_ptr+1,'.');
    if(tem_ptr == NULL)  //处理 a
    {
        real_field_name = (char*)calloc(strlen(field_name)+1,1);
        memcpy(real_field_name,field_name,strlen(field_name)+1);
        database_name = NULL;
        table_alias_name = NULL;

        *database_name_cpy = database_name;
        *table_alias_name_cpy = table_alias_name;
        *real_field_name_cpy = real_field_name;
        return 1;
    }
    else if(tem_ptr != NULL && tem_ptr_ptr == NULL)  //处理 t.a
    {
        table_alias_name = (char*)malloc(tem_ptr-field_name+1);
        memset(table_alias_name ,0,tem_ptr-field_name+1);
        memcpy(table_alias_name,field_name,tem_ptr-field_name);
        
        database_name = NULL;

        real_field_name = (char*)calloc(1,strlen(tem_ptr+1)+1);
        memcpy(real_field_name,tem_ptr+1,strlen(tem_ptr+1));

        *database_name_cpy = database_name;
        *table_alias_name_cpy = table_alias_name;
        *real_field_name_cpy = real_field_name;
        return 2;
    }
    else if(tem_ptr != NULL && tem_ptr_ptr != NULL)  //处理 liuyu.t.a
    {
        database_name = (char*)calloc(tem_ptr-field_name+1,1);
        memcpy(database_name,field_name,tem_ptr-field_name);

        table_alias_name = (char*)calloc(tem_ptr_ptr - tem_ptr,1);
        memcpy(table_alias_name,tem_ptr+1,tem_ptr_ptr - tem_ptr - 1);

        real_field_name = (char*)calloc(strlen(tem_ptr_ptr+1)+1,1);
        memcpy(real_field_name,tem_ptr_ptr + 1,strlen(tem_ptr_ptr + 1));

        *database_name_cpy = database_name;
        *table_alias_name_cpy = table_alias_name;
        *real_field_name_cpy = real_field_name;
        return 3;
    }
    // if(table_alias_name)
    //     printf("Table : %s ",table_alias_name);
    // if(database_name)
    //     printf("Database : %s ",database_name);
    // if(real_field_name)
    //     printf("Field ： %s ",real_field_name);
    return 1;
}

/*----------------------------------------------------------------------*/
FILE* parse_getopt(int argc,char** argv)
{
    int     opt = 0;
    FILE*   tem_open = NULL;

    if(argc<2)
    {
        usage();
        exit(0);
    }

    struct option opt_choose[] =
            {
                    {"getinfo",1,NULL,'g'},
                    {"all",0,NULL,'a'},
                    {"physical_mode",0,NULL,'p'},
                    {"file",1,NULL,'f'},
                    {"test",0,NULL,'t'},
                    {"back",0,NULL,'b'},
                    {"liuyu",0,NULL,'l'},
            };

    while ((opt = getopt_long(argc,argv,"g:apf:bt:l",opt_choose,NULL))!=-1)
    {
        switch (opt)
        {
            case 'g':
                _Global.mode = GET_MODE;
                _Global.field_name = optarg;
                break;
            case 'a':
                _Global.mode = ALL_MODE;
                break;
            case 'p':
                _Global.mode = PHYSICAL_MODE;
                break;
            case 'f':
                _Global.mode = ALL_MODE;
                _Global.file_name = optarg;
                break;
            case 't':
                _Global.mode = TEST_MODE;
                break;
            case 'b':
                _Global.mode = BACK_STMT;
                break;
            case 'l':
                _Global.mode = LIUYU_MODE;
                break;
            default:
                usage();
                exit(0);
                break;
        }
    }

    if(_Global.file_name == NULL)
    {
        usage();
        exit(0);
    }
    else
    {
        tem_open = fopen(_Global.file_name,"r");
    }

    return tem_open;
}

void usage()
{
    printf("-f  <FILE>              --file       <FILE>                指定读入sql的文件名称\n");
    printf("-p                      --physical                         查看所有的字段和其对应的物理表\n");
    printf("-a                      --all                              将所有的语句分层显示，对应关系显示\n");
    printf("-g  <FIELD>             --getinfo    <FIELD>               查找输入字段对应的物理表\n");
    printf("-b                      --back                             还原语句\n");
    printf("-t                      --test                             还原语句---完全还原 保留注释\n");
    printf("-l                      --liuyu                            刘宇开发者模式\n");
}

/*-------------------------还原语句---------------------------------*/

void Get_back_stmt(stmt* back_stmt)
{
    c_vector*           main_select_info = Init_vector(10);
    c_vector*           union_stmt = Init_vector(10);
    select_info*        main_select = NULL;
    int                 i = 0;
    u_int64_t           stmt_size = 0;
    char*               stmt_stmt = NULL;
    char**               tem_stmt = NULL;

    //拿到每一个mian的函数开始
    Find_main(back_stmt,main_select_info);
    for(i = 0;i<main_select_info->curr_size;i++)
    {
        main_select = Vetor_get(main_select_info,i);
        stmt_size += Show_select_info(main_select,union_stmt,back_stmt);    //让这个函数返回这个语句的大小
    }

    if(union_stmt->curr_size < 1)   //容错
    {
        return;
    }

    stmt_stmt = (char*)malloc(stmt_size+7*(union_stmt->curr_size-1)+10);
    tem_stmt = Vetor_get(union_stmt,0);
    sprintf(stmt_stmt,"%s",*tem_stmt);
    for(i = 1;i<union_stmt->curr_size;i++)
    {
        tem_stmt = (char**)Vetor_get(union_stmt,i);
        sprintf(stmt_stmt,"%s UNION %s",stmt_stmt,*tem_stmt);
    }

    printf("原来的语句 ： %s\n",stmt_stmt);
}


void Find_main(stmt* back_stmt,c_vector* main_select_info)
{
    int             i = 0;
    select_info*    tem_stmt;

    for(i=0;i<back_stmt->vector_stmt->curr_size;i++)
    {
        tem_stmt = Vetor_get(back_stmt->vector_stmt,i);
        if(strcmp(tem_stmt->name,"MAIN") == 0)
        {
            Vector_push_back(main_select_info,tem_stmt);
        }
    }
}


int Show_select_info(select_info* main_select,c_vector* union_stmt,stmt* back_stmt)
{
    int             i = 0;
    char*           stmt = (char*)calloc(1,STMT_MAX);  //默认一条语句最大1M
    field_info*     tem_field = NULL;
    obj_info*       tem_obj = NULL;
    Tree_Node*      tem_node;

    sprintf(stmt,"SELECT");
    for(i = 0 ;i<main_select->vector_opt->curr_size;i++)
    {        
        tem_node = Vetor_get(main_select->vector_opt,i);
        sprintf(stmt,"%s %s",stmt,tem_node->RHS);
    }

    if(main_select->vector_field->curr_size>=1)
    {
        tem_field = Vetor_get(main_select->vector_field,0);
     
        if(tem_field->field_name->type == SELECT_SELECT)
        {
            sprintf(stmt,"%s (%s)",stmt,Get_subquery_stmt(tem_field->field_name->RHS,back_stmt));
        }
        else
        {
            sprintf(stmt,"%s %s",stmt,tem_field->field_name->RHS);
        }

        if(tem_field->field_alias != NULL && strcmp(tem_field->field_alias->RHS,"NULL") != 0)
        {
            sprintf(stmt,"%s %s",stmt,tem_field->field_alias->RHS);
        }
    }
    for(i = 1 ;i<main_select->vector_field->curr_size;i++)
    {
        tem_field = Vetor_get(main_select->vector_field,i);

        if(tem_field->field_name->type == SELECT_SELECT)
        {
            sprintf(stmt,"%s , (%s)",stmt,Get_subquery_stmt(tem_field->field_name->RHS,back_stmt));
        }
        else
        {
            sprintf(stmt,"%s , %s",stmt,tem_field->field_name->RHS);
        }
     
        if(tem_field->field_alias != NULL && strcmp(tem_field->field_alias->RHS,"NULL") != 0)
        {
            sprintf(stmt,"%s %s",stmt,tem_field->field_alias->RHS);
        }
    }

    sprintf(stmt,"%s FROM",stmt);

    if(main_select->vector_table->curr_size>=1)
    {
        tem_obj = Vetor_get(main_select->vector_table,0);


        if(tem_obj->obj_condition != NULL && strcmp(tem_obj->obj_condition->RHS,"NULL") != 0)
        {
            if(tem_obj->obj_name->type == SELECT_SELECT)
            {
                sprintf(stmt,"%s LEFT JOIN (%s)",stmt,Get_subquery_stmt(tem_obj->obj_name->RHS,back_stmt));
            }
            else
            {
                sprintf(stmt,"%s LEFT JOIN %s",stmt,tem_obj->obj_name->RHS);
            }

            if(tem_obj->obj_alias != NULL && strcmp(tem_obj->obj_alias->RHS,"NULL") != 0)
            {
                sprintf(stmt,"%s %s",stmt,tem_obj->obj_alias->RHS);
            }

            sprintf(stmt,"%s %s",stmt,tem_obj->obj_condition->RHS);
        }

        else
        {
            if(tem_obj->obj_name->type == SELECT_SELECT)
            {
                sprintf(stmt,"%s (%s)",stmt,Get_subquery_stmt(tem_obj->obj_name->RHS,back_stmt));
            }
            else
            {
                sprintf(stmt,"%s %s",stmt,tem_obj->obj_name->RHS);
            }

            if(tem_obj->obj_alias != NULL && strcmp(tem_obj->obj_alias->RHS,"NULL") != 0)
            {
                sprintf(stmt,"%s %s",stmt,tem_obj->obj_alias->RHS);
            }
        }
        
    }
    for(i = 1 ;i<main_select->vector_table->curr_size;i++)
    {
        tem_obj = Vetor_get(main_select->vector_table,i);

        if(tem_obj->obj_condition != NULL && strcmp(tem_obj->obj_condition->RHS,"NULL") != 0)
        {
            if(tem_obj->obj_name->type == SELECT_SELECT)
            {
                sprintf(stmt,"%s LEFT JOIN (%s)",stmt,Get_subquery_stmt(tem_obj->obj_name->RHS,back_stmt));
            }
            else
            {
                sprintf(stmt,"%s LEFT JOIN %s",stmt,tem_obj->obj_name->RHS);
            }

            if(tem_obj->obj_alias != NULL && strcmp(tem_obj->obj_alias->RHS,"NULL") != 0)
            {
                sprintf(stmt,"%s %s",stmt,tem_obj->obj_alias->RHS);
            }

            sprintf(stmt,"%s %s",stmt,tem_obj->obj_condition->RHS);
        }

        else
        {
            if(tem_obj->obj_name->type == SELECT_SELECT)
            {
                sprintf(stmt,"%s (%s)",stmt,Get_subquery_stmt(tem_obj->obj_name->RHS,back_stmt));
            }
            else
            {
                sprintf(stmt,"%s %s",stmt,tem_obj->obj_name->RHS);
            }

            if(tem_obj->obj_alias != NULL && strcmp(tem_obj->obj_alias->RHS,"NULL") != 0)
            {
                sprintf(stmt,"%s %s",stmt,tem_obj->obj_alias->RHS);
            }
        }
    }

    for(i = 0 ;i<main_select->vector_where->curr_size;i++)
    {
         tem_node = Vetor_get(main_select->vector_where,i);
         sprintf(stmt,"%s WHERE %s",stmt,tem_node->RHS);
    }

    for(i = 0 ;i<main_select->vector_group_by->curr_size;i++)
    {
         tem_node = Vetor_get(main_select->vector_group_by,i);
         sprintf(stmt,"%s GROUP BY %s",stmt,tem_node->RHS);
    }

    for(i = 0 ;i<main_select->vector_having->curr_size;i++)
    {
         tem_node = Vetor_get(main_select->vector_having,i);
         sprintf(stmt,"%s HAVING %s",stmt,tem_node->RHS);
    }
    for(i = 0 ;i<main_select->vector_oder_by->curr_size;i++)
    {
         tem_node = Vetor_get(main_select->vector_oder_by,i);
         sprintf(stmt,"%s ODER　BY %s",stmt,tem_node->RHS);
    }


    Vector_push_back(union_stmt,&stmt);
    return strlen(stmt);
}


char* Get_subquery_stmt(char* search,stmt* back_stmt)
{
    c_vector*           main_select_info = Init_vector(10);
    c_vector*           union_stmt = Init_vector(10);
    select_info*        main_select = NULL;
    int                 i = 0;
    u_int64_t           stmt_size = 0;
    char*               stmt_stmt = NULL;
    char**              tem_stmt = NULL;

    //拿到每一个mian的函数开始
    Find_sub(back_stmt,main_select_info,search);
    for(i = 0;i<main_select_info->curr_size;i++)
    {
        main_select = Vetor_get(main_select_info,i);
        stmt_size += Show_select_info(main_select,union_stmt,back_stmt);    //让这个函数返回这个语句的大小
    }

    if(union_stmt->curr_size < 1)   //容错
    {
        return NULL;
    }

    stmt_stmt = (char*)malloc(stmt_size+7*(union_stmt->curr_size-1)+10);
    tem_stmt = Vetor_get(union_stmt,0);
    sprintf(stmt_stmt,"%s",*tem_stmt);
    for(i = 1;i<union_stmt->curr_size;i++)
    {
        tem_stmt = (char**)Vetor_get(union_stmt,i);
        sprintf(stmt_stmt,"%s UNION %s",stmt_stmt,*tem_stmt);
    }

    return stmt_stmt;
}


void Find_sub(stmt* back_stmt,c_vector* main_select_info,char* search)
{
    int             i = 0;
    select_info*    tem_stmt;

    for(i=0;i<back_stmt->vector_stmt->curr_size;i++)
    {
        tem_stmt = Vetor_get(back_stmt->vector_stmt,i);
        if(strcmp(tem_stmt->name,search) == 0)
        {
            Vector_push_back(main_select_info,tem_stmt);
        }
    }
}


_String* Insert_str(char* str)
{
    if( _Global.ptr_chache->now_offset + strlen(str) >= _Global.ptr_chache->size)
    {
        Expend_chache();    
    }
    memcpy(_Global.ptr_chache->chache + _Global.ptr_chache->now_offset,str,strlen(str));
   
    _String* String_tem = (_String*)malloc(sizeof(_String));
    String_tem -> string_ptr = _Global.ptr_chache->chache + _Global.ptr_chache->now_offset;
    String_tem -> string_size = strlen(str);

    _Global.ptr_chache->now_offset += strlen(str);
    return String_tem;
}
