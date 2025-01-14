/* Include the system headers we need */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* Include our header */
#include "ex7_vector.h"

/* Define what our struct is */
struct vector_t {
    size_t size;
    int *data;
};

/* Utility function to handle allocation failures. In this
   case we print a message and exit. */
static void allocation_failed() {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
}

/* Bad example of how to create a new vector */
vector_t *bad_vector_new() {
    /* Create the vector and a pointer to it */
    vector_t *retval, v;
    retval = &v;

    /* Initialize attributes */
    retval->size = 1;
    retval->data = malloc(sizeof(int));
    if (retval->data == NULL) {
        allocation_failed();
    }

    retval->data[0] = 0;
    return retval;
}

/* Create a new vector with a size (length) of 1 and set its single component to zero... the
   right way */
/* TODO: uncomment the code that is preceded by // */
vector_t *vector_new() {
    /* Declare what this function will return */
    vector_t *retval;

    /* First, we need to allocate memory on the heap for the struct */
    retval = (vector_t*)malloc(sizeof(vector_t));

    /* Check our return value to make sure we got memory */
     if (retval == NULL) {
         allocation_failed();
     }

    /* Now we need to initialize our data.
       Since retval->data should be able to dynamically grow,
       what do you need to do? */
     retval->size = 1;
     retval->data = (int*)malloc(sizeof(int));

    /* Check the data attribute of our vector to make sure we got memory */
     if (retval->data == NULL) {
         free(retval);				//Why is this line necessary?
         allocation_failed();
     }

    /* Complete the initialization by setting the single component to zero */
    retval->data[0] = 0;

    /* and return... */
    return retval; /* UPDATE RETURN VALUE */
}

/* Return the value at the specified location/component "loc" of the vector */
int vector_get(vector_t *v, size_t loc) {

    /* If we are passed a NULL pointer for our vector, complain about it and exit. */
    if(v == NULL) {
        fprintf(stderr, "vector_get: passed a NULL vector.\n");
        abort();
    }

    /* If the requested location is higher than we have allocated, return 0.
     * Otherwise, return what is in the passed location.
     */
    if(loc >= v->size){
        return 0;
    }
    return v->data[loc];
}

/* Free up the memory allocated for the passed vector.
   Remember, you need to free up ALL the memory that was allocated. */
void vector_delete(vector_t *v) {
    if(v != NULL){
        free(v ->data);
        free(v);
    }
}

/* Set a value in the vector, allocating additional memory if necessary. 
   If the extra memory allocation fails, call allocation_failed(). */
void vector_set(vector_t *v, size_t loc, int value) {
    /* What do you need to do if the location is greater than the size we have
     * allocated?  Remember that unset locations should contain a value of 0.
     */
    if (v == NULL) {  
        fprintf(stderr, "vector_set: passed a NULL vector.\n");  
        return;  
    }  
    if(loc >= v->size){
        size_t newSize = loc + 1;
        int* newData = realloc(v->data, sizeof(int)* newSize);
        if(newData == NULL){
            allocation_failed();
        }
        v->data = newData;
        for (size_t i = v->size; i < newSize; i++)
        {
            v->data[i] = 0;
        }
        v->size = newSize;
    }
    v->data[loc] = value;
}
void test_vector() {  
    // 创建一个新的向量  
    vector_t *v = vector_new();  
    assert(v != NULL); // 确保向量被成功创建  
    assert(v->size == 1); // 确保初始大小为1  
    assert(vector_get(v, 0) == 0); // 确保初始元素为0  

    // 设置新值  
    vector_set(v, 0, 10);  
    assert(vector_get(v, 0) == 10); // 确保设置正确  

    // 设置超出当前大小的值，测试动态扩展  
    vector_set(v, 1, 20);  
    assert(v->size == 2); // 确保向量的大小已扩展到2  
    assert(vector_get(v, 1) == 20); // 确保正确值被设置  
    assert(vector_get(v, 2) == 0); // 检查未设置的位置返回0  

    // 清理资源  
    vector_delete(v);  
}  

void test_empty_vector() {  
    // 创建一个空向量并进行基本操作  
    vector_t *v = vector_new();  
    vector_set(v, 5, 50); // 增加到第6个元素  
    assert(v->size == 6); // 确保向量大小已扩展到6  
    assert(vector_get(v, 5) == 50); // 确保设置的值是正确的  

    // 清理资源  
    vector_delete(v);  
}  

int main() {  
    test_vector();  
    test_empty_vector();  

    printf("所有测试均通过！\n");  
    return 0;  
}  