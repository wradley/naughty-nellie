#include "Stack.hpp"
#include <cstdlib>
#include <cassert>

#define START_STACK_SIZE 1024

// What the stack "looks" like

//      |       42      | <- head
//      | DATATYPE::INT |
//      |      '/0'     |
//      |      'o'      |
//      |      'l'      |
//      |      'l'      |
//      |      'e'      |
//      |      'h'      |
//      | DATATYPE::STR |
//      |      3.14     |
//      | DATATYPE::FLT | <- tail
//      |               |
//      |               |
//      |               |
//      |               | <- max size

wj::Stack::Stack() : _head(NULL), _tail(NULL), _max_size_ptr(NULL), _max_size(START_STACK_SIZE)
{
    _head = malloc(START_STACK_SIZE);
    if (_head == NULL)
    {
        printf("ERROR [Stack constructor] -> malloc returned NULL\n");
        assert(0);
    }

    char *max = (char*) _head;
    max += START_STACK_SIZE;
    _max_size_ptr = max;

    _tail = _head;
}

wj::Stack::~Stack()
{
    if (_head != NULL)
        free(_head);
}

std::string wj::Stack::debug_to_string()
{
    std::string ret_string;

    void *head = _head;
    void *tail = _tail;

    while (tail > head)
    {
        DataType *data_type = (DataType*) tail;
        --data_type;
        tail = (void*) data_type;

        if (*data_type == DataType::INT) {

            ret_string = "[ INTEGER ]\n" + ret_string;
            int64_t *val = (int64_t*) tail;
            --val;
            ret_string = std::to_string(*val) + '\n' + ret_string;
            tail = (void*) val;

        } else if (*data_type == DataType::FLT) {

            ret_string = "[  FLOAT  ]\n" + ret_string;
            double *val = (double*) tail;
            --val;
            ret_string = std::to_string(*val) + '\n' + ret_string;
            tail = (void*) val;

        } else if (*data_type == DataType::STR){

            ret_string = "[  STRING ]\n" + ret_string;
            char *val = (char*) tail;
            --val;
            std::string word;
            while (*val != 0)
            {
                word.push_back(*val--);
            }
            word.push_back('\n');
            ret_string = word + ret_string;
            tail = (void*) --val;
        }
    }

    return ret_string;
}

void wj::Stack::push_int(int64_t num)
{
    // make sure there is enough room
    while (space_left() < sizeof(int64_t) + 10) resize();

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
    while (space_left() < sizeof(double) + 10) resize();

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
    // find back of str
    int i = 0;
    while (str[i] != 0) ++i;
    int length = i + 2;

    // make sure there is enough room
    while (space_left() < i + 10) resize();

    // copy data
    char *tail_ptr = (char*) _tail;
    *tail_ptr = 0; ++tail_ptr; // set null char end
    while (i >= 0)
    {
        *tail_ptr = str[i--];
        ++tail_ptr;
    }

    // adjust tail
    char *tail = (char*) _tail;
    tail += length;
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
    int64_t ret_val = 0;

    // type check
    DataType *data_type = (DataType*) _tail;
    --data_type;
    _tail = (void*) data_type;

    // make sure it's an int
    if (*data_type == DataType::INT)
    {
        int64_t *val = (int64_t*) _tail;
        --val;
        ret_val = *val;
        _tail = (void*) val;
    }

    else
    {
        printf("Tried to pop an int but that was not the value on the stack\n");
        assert(0);
    }

    return ret_val;
}


double wj::Stack::pop_flt()
{
    double ret_val = 0.0;

    // type check
    DataType *data_type = (DataType*) _tail;
    --data_type;
    _tail = (void*) data_type;

    // make sure it's an int
    if (*data_type == DataType::FLT)
    {
        double *val = (double*) _tail;
        --val;
        ret_val = *val;
        _tail = (void*) val;
    }

    else
    {
        printf("Tried to pop double but that was not the value on the stack\n");
        assert(0);
    }

    return ret_val;
}


std::string wj::Stack::pop_str()
{
    std::string ret_string;

    // type check
    DataType *data_type = (DataType*) _tail;
    --data_type;
    _tail = (void*) data_type;

    if (*data_type == DataType::STR)
    {
        char *val = (char*) _tail;
        --val;
        while (*val != 0)
        {
            ret_string.push_back(*val--);
        }
        ret_string.push_back(0);
        _tail = (void*) --val;
    }

    else
    {
        printf("Tried to pop string but that was not the value on the stack\n");
        assert(0);
    }

    return ret_string;
}


int wj::Stack::space_left()
{
    char *max = (char*) _max_size_ptr;
    char *curr = (char*) _tail;
    return max - curr;
}


void wj::Stack::resize()
{
    uint64_t tail_size = (char*) _tail - (char*) _head;

    // resize array
    _max_size *= 2;
    void *old_head = _head;
    _head = malloc(_max_size);
    if (_head == NULL)
    {
        printf("ERROR [Stack resize] -> realloc returned NULL\n");
        assert(0);
    }
    char *nptr = (char*) _head;
    char *optr = (char*) old_head;
    for (int i = 0; i < _max_size; ++i)
    {
        *nptr = *optr;
        ++nptr; ++optr;
    }
    free(old_head);

    // set up ptrs
    char *max = (char*) _head;
    max += _max_size;
    _max_size_ptr = max;

    char *tail = (char*) _head;
    tail += tail_size;
    _tail = tail;
}
