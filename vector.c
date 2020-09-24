//
// Created by root on 2020/8/31.
//

#include "vector.h"

void Del_vector(c_vector* cv)
{
    if(cv->value != NULL)
    {
        free(cv->value);
    }
    free(cv);
}

c_vector* Init_vector(const size_t _size)
{
    c_vector * cv;
    cv = (c_vector*)malloc(sizeof(c_vector));
    if(cv == NULL)
    {
        printf("ERROR\n");
        return NULL;
    }
    memset(cv,0,sizeof(c_vector));
    cv->value = malloc(_size* MIN_VECTOR_SIZE);
    memset(cv->value,0,_size* MIN_VECTOR_SIZE);
    cv->curr_size = 0;
    cv->totol_size = _size;
    cv->cap_space = _size * MIN_VECTOR_SIZE;
    return cv;
}

int Vector_push_back(c_vector* cv,const void* value)
{
    cv = Expend_vector(cv);
    memcpy(cv->value+cv->curr_size * MIN_VECTOR_SIZE,value,MIN_VECTOR_SIZE);
    cv->curr_size ++;
    return cv->curr_size;
}

void* Vetor_get(c_vector* cv,size_t size)
{
    return (cv->value+size*MIN_VECTOR_SIZE);
}

c_vector * Expend_vector(c_vector* cv)
{
    if(cv->curr_size < cv->totol_size)
    {
        return cv;
    }
    cv->value = realloc(cv->value,cv->totol_size*2*MIN_VECTOR_SIZE);
    cv->totol_size *= 2;
    cv->cap_space *= 2;
    return cv;
}


