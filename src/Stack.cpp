#include "Stack.hpp"
#include <cstdlib>
#include <cassert>

#define START_STACK_SIZE 1024

// What the stack "looks" like

//      |       42      | <- head
//      | DATATYPE::INT |
//      |      'l'      |
//      |      'i'      |
//      |      'f'      |
//      |      'e'      |
//      |      '/0'     |
//      | DATATYPE::STR |
//      |      3.14     |
//      | DATATYPE::FLT | <- tail
//      |               |
//      |               |
//      |               |
//      |               | <- max size

wj::Stack::Stack() : _head(NULL), _tail(NULL), _max_size(NULL)
{
    _head = malloc(START_STACK_SIZE);
    if (_head == NULL)
    {
        printf("ERROR [Stack constructor] -> malloc returned NULL\n");
        assert(1);
    }

    char *max = (char*) _head;
    max += START_STACK_SIZE;
    _max_size = max;

    _tail = _head;
}

wj::Stack::~Stack()
{
    if (_head != NULL)
        free(_head);
}


void wj::Stack::push_int(int64_t num)
{
    // make sure there is enough room
    while (space_left() < sizeof(int64_t)) resize();

    // copy data
    int64_t *tail_ptr = (int64_t*) _tail;
    *tail_ptr = num;

    // adjust tail
    char *tail = (char*) _tail;
    tail += sizeof(int64_t);
    _tail = (void*) tail;

    // push type on for type checking
    push_type(DataType::INT);
}


void wj::Stack::push_flt(double num)
{
    // make sure there is enough room
    while (space_left() < sizeof(double)) resize();

    // copy data
    double *tail_ptr = (double*) _tail;
    *tail_ptr = num;

    // adjust tail
    char *tail = (char*) _tail;
    tail += sizeof(double);
    _tail = (void*) tail;

    // push type on for type checking
    push_type(DataType::FLT);
}


void wj::Stack::push_str(const char *str)
{
    // make sure there is enough room
    int str_size = strlen(str) + 1;
    while (space_left() < str_size) resize();

    // copy data
    char *tail_ptr = (char*) _tail;
    strcpy(tail_ptr, str);

    // adjust tail
    char *tail = (char*) _tail;
    tail += str_size;
    _tail = (void*) tail;

    // push type on for type checking
    push_type(DataType::STR);
}


void wj::Stack::push_type(DataType type)
{
    // make sure there is enough room
    while (space_left() < sizeof(DataType)) resize();

    // copy data
    DataType *tail_ptr = (DataType*) _tail;
    *tail_ptr = type;

    // adjust tail
    char *tail = (char*) _tail;
    tail += sizeof(DataType);
    _tail = (void*) tail;
}


int64_t wj::Stack::pop_int()
{
    return 0;
}


double wj::Stack::pop_flt()
{
    return 0;
}


char* wj::Stack::pop_str()
{
    return NULL;
}


int wj::Stack::space_left()
{
    char *max = (char*) _max_size;
    char *curr = (char*) _tail;
    return max - curr;
}


void wj::Stack::resize()
{

}
