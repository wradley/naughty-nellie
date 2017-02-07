#include "Stack.hpp"

namespace
{
    enum ListNodeType
    {
        INT = 0, FLT, STR
    };

    struct ListNode
    {
        virtual ~ListNode() {}
        virtual void* get_val() = 0;
        virtual ListNode* get_next() = 0;
        virtual ListNodeType type() = 0;
    };

    struct ListNodeInt : public ListNode
    {
        uint64_t val;
        ListNode *next;
        inline void* get_val() { return &val; }
        inline ListNode* get_next() { return next; }
        inline ListNodeType type() { return ListNodeType::INT; }
    };

    struct ListNodeFlt : public ListNode
    {
        double val;
        ListNode *next;
        inline void* get_val() { return &val; }
        inline ListNode* get_next() { return next; }
        inline ListNodeType type() { return ListNodeType::FLT; }
    };

    struct ListNodeStr : public ListNode
    {
        std::string val;
        ListNode *next;
        inline void* get_val() { return &val; }
        inline ListNode* get_next() { return next; }
        inline ListNodeType type() { return ListNodeType::STR; }
    };
};

wj::Stack::Stack() : _head(nullptr)
{}

wj::Stack::~Stack()
{
    clean_stack();
}

void wj::Stack::push_int(uint64_t num)
{
    ListNodeInt *node = new ListNodeInt;
    node->val = num;
    node->next = nullptr;
    _tail->next = node;
    _tail = node;
}

void wj::Stack::push_flt(double num)
{
    ListNodeFlt *node = new ListNodeFlt;
    node->val = num;
    node->next = nullptr;
    _tail->next = node;
    _tail = node;
}

void wj::Stack::push_str(const std::string str)
{
    ListNodeStr *node = new ListNodeStr;
    node->val = str;
    node->next = nullptr;
    _tail->next = node;
    _tail = node;
}

uint64_t wj::Stack::pop_int()
{
    uint64_t val;
    ListNode *tail = (ListNode*) _tail;
    if (tail->type() == ListNodeType::INT) {
        val = tail->val;
    } else {
        val = 0;
        printf("Tried to pop an int.");
        assert(1);
    }
    return val;
}

double wj::Stack::pop_flt()
{
    double val;
    ListNode *tail = (ListNode*) _tail;
    if (tail->type() == ListNodeType::FLT) {
        val = tail->val;
    } else {
        val = 0;
        printf("Tried to pop a flt.");
        assert(1);
    }
    return val;
}

std::string wj::Stack::pop_str()
{
    std::string val;
    ListNode *tail = (ListNode*) _tail;
    if (tail->type() == ListNodeType::STR) {
        val = tail->val;
    } else {
        val = "";
        printf("Tried to pop a str.");
        assert(1);
    }
    return val;
}
