#include "Stack.hpp"
#include <cstdlib>

#define START_STACK_SIZE 1024

// What the stack "looks" like

//      |       42      | <- head
//      | DATATYPE::INT |
//      |      'b'      |
//      |      'u'      |
//      |      't'      |
//      |      't'      |
//      |      '/0'     |
//      | DATATYPE::STR |
//      |      3.14     |
//      | DATATYPE::FLT | <- tail
//      |               |
//      |               |
//      |               |
//      |               | <- max size

namespace
{
    enum DataType
    {
        INT = 0, FLT, STR
    };
};

wj::Stack::Stack() : _head(NULL), _tail(NULL), _max_size(NULL)
{
    _head = malloc(START_STACK_SIZE);
    if (_head == NULL)
    {
        printf("ERROR [Stack constructor] -> malloc returned NULL\n");
        assert(1);
    }

    char *max = _head;
    max += START_STACK_SIZE;
    _max_size = max;

    _tail = _head;
}

wj::Stack::~Stack()
{
    if (_head != NULL)
        free(_head);
}


void wj::Stack::push_int(uint64_t num)
{
    // make sure there is enough room
    while (space_left() < sizeof(uint64_t)) resize();

    // copy data
    uint64_t *tail_ptr = _tail;
    *_tail = num;

    // adjust tail
    char *tail = (char*) _tail;
    tail += sizeof(uint64_t);
    _tail = (void*) tail;

    // push type on for type checking
    push_type(_tail, DataType::INT);
}


void wj::Stack::push_flt(double num)
{
    // make sure there is enough room
    while (space_left() < sizeof(double)) resize();

    // copy data
    double *tail_ptr = _tail;
    *_tail = num;

    // adjust tail
    char *tail = (char*) _tail;
    tail += sizeof(double);
    _tail = (void*) tail;

    // push type on for type checking
    push_type(_tail, DataType::FLT);
}


void wj::Stack::push_str(const char *str)
{
    // make sure there is enough room
    int str_size = strlen(str) + 1;
    while (space_left() < str_size) resize();

    // copy data
    char *tail_ptr = _tail;
    strcpy(tail_ptr, str);

    // adjust tail
    char *tail = (char*) _tail;
    tail += str_size;
    _tail = (void*) tail;

    // push type on for type checking
    push_type(_tail, DataType::STR);
}


uint64_t wj::Stack::pop_int()
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
