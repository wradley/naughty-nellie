#ifndef __SLIST_H__
#define __SLIST_H__

#include <cstdint>
#include <string>

// - SList (Small List/Slow List) should be used if you need an array indices are far and few bewteen.
//   SList is slower than FList but it saves a lot more space and with few elements can be accessed quickly

namespace wj
{
    template <typename T>
    struct SListElement
    {
        uint64_t index;
        T data;
        SListElement *prev, *next;
    };

    template <typename T>
    class SList
    {
    public:

        SList()
        {
            _num_nodes = 0;
            _head = _tail = nullptr;
        }

        ~SList() { clear(); }

        T& operator[] (uint64_t index)
        {
            SListElement<T> *ret_node = nullptr;

            // List is empty (node needs to be created)
            if (_num_nodes == 0)
            {
                _head = new SListElement<T>;
                _head->index = index;
                _head->next = _head->prev = nullptr;
                _tail = _head;
                ret_node = _head;
                ++_num_nodes;
            }

            // List has 1 node
            else if (_num_nodes == 1)
            {
                // if the node exists
                if (_head->index == index) return _head->data;

                // if it doesn't -- create it
                else
                {
                    // if the node should be put before the head
                    if (index < _head->index)
                    {
                        _head = new SListElement<T>;
                        _head->index = index;
                        _head->next = _tail;
                        _head->prev = nullptr;
                        _tail->prev = _head;
                        ret_node = _head;
                        ++_num_nodes;
                    }

                    // if the node should be put after the head
                    else
                    {
                        _tail = new SListElement<T>;
                        _tail->index = index;
                        _tail->next = nullptr;
                        _tail->prev = _head;
                        _head->next = _tail;
                        ret_node = _tail;
                        ++_num_nodes;
                    }
                }
            }

            // if list is >= 2 long
            else
            {
                // index is smaller than head's index (should be first in list)
                if (index < _head->index)
                {
                    SListElement<T> *node = new SListElement<T>;
                    node->index = index;
                    node->prev = nullptr;
                    node->next = _head;
                    _head->prev = node;
                    _head = node;
                    ret_node = _head;
                    ++_num_nodes;
                }

                // index is lasrger than tail's index (should be last in list)
                else if (index > _tail->index)
                {
                    SListElement<T> *node = new SListElement<T>;
                    node->index = index;
                    node->next = nullptr;
                    node->prev = _tail;
                    _tail->next = node;
                    _tail = node;
                    ret_node = _tail;
                    ++_num_nodes;
                }

                // else it should be somewhere in middle
                else
                {
                    SListElement<T> *node = _head;
                    for (int i = 0; i < _num_nodes; ++i)
                    {
                        // if the node exists
                        if (node->index == index)
                        {
                            ret_node = node;
                            break;
                        }

                        // if the node does not exist
                        else if (node->index > index)
                        {
                            node = node->prev;
                            SListElement<T> *n = new SListElement<T>;
                            n->index = index;
                            n->prev = node;
                            n->next = node->next;
                            node->next = n;
                            ret_node = n;
                            ++_num_nodes;
                            break;
                        }

                        node = node->next;
                    }
                }
            }

            return ret_node->data;
        }

        bool exists(uint64_t index)
        {
            SListElement<T> *curr = _head;
            while (curr)
            {
                if (curr->index == index) return true;
                if (curr->index > index) return false;
                curr = curr->next;
            }
            return false;
        }

        void remove(uint64_t index)
        {
            // find element
            SListElement<T> *curr = _head;
            while (curr)
            {
                if (curr->index == index) // found
                {
                    SListElement<T> *prev = curr->prev;
                    prev->next = curr->next;
                    curr->next->prev = prev;
                    delete curr;
                }
                if (curr->index > index) break; // not in list
                curr = curr->next;
            }
        }

        void clear()
        {
            while (_head)
            {
                SListElement<T> *curr = _head;
                _head = _head->next;
                delete curr;
            }
            _num_nodes = 0;
            _head = _tail = nullptr;
        }

        std::string debug_to_string()
        {
            std::string ret_str;

            SListElement<T> *curr = _head;
            while (curr)
            {
                ret_str += curr->data.to_string() + "\n";
                curr = curr->next;
            }

            ret_str.pop_back();

            return ret_str;
        }

    private:

        SListElement<T> *_head, *_tail;
        uint64_t _num_nodes;

    };
};

#endif /* end of include guard: __SLIST_H__ */
