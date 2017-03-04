#ifndef __LIST_H__
#define __LIST_H__

// T            operator[] (uint64_t index)
// bool         exists (uint64_t index)
// void         remove (uint64_t index)
// void         clear ()
// std::string  debug_to_string ()

// ** includes an iterator;

#include <cstdint>
#include <cstdio>
#include <string>
#include <cassert>

static const int START_SIZE = 16;

namespace wj
{
    template <typename T>
    class ListItr;

    template <typename T>
    class List
    {
    public:

        List()
        {
            _item_size = sizeof(T);
            _length = START_SIZE + 1;
            _data_list  = new    T [_length];
            _valid_list = new bool [_length];
            for (int i = 0; i < _length; ++i) _valid_list[i] = false;
            _valid_list[_length-1] = true;
        }

        List(const List &other)
        {
            _length = other._length;
            _item_size = other._item_size;

            // copy over data
            for (uint64_t i = 0; i < _length; ++i)
            {
                _data_list[i] = other._data_list[i];
                _valid_list[i] = other._valid_list[i];
            }
        }

        void operator= (const List &other)
        {
            _length = other._length;
            _item_size = other._item_size;

            // copy over data
            for (uint64_t i = 0; i < _length; ++i)
            {
                _data_list[i] = other._data_list[i];
                _valid_list[i] = other._valid_list[i];
            }
        }

        ~List()
        {
            if (_data_list)  delete [] _data_list;
            if (_valid_list) delete [] _valid_list;
        }

        T& operator[] (uint64_t index)
        {
            // check for possible resize
            while (index+1 >= _length)
            {
                _valid_list[_length-1] = false;
                _length *= 2;

                // reference old lists
                T *old_data_list = _data_list;
                bool *old_valid_list = _valid_list;

                // make new ones
                _data_list  = new    T [_length];
                _valid_list = new bool [_length];

                // copy over data
                uint64_t i;
                for (i = 0; i < _length/2; ++i)
                {
                    _data_list[i] = old_data_list[i];
                    _valid_list[i] = old_valid_list[i];
                }

                // set rest of valid list to false
                for (; i < _length; ++i) _valid_list[i] = false;

                // delete old ones
                delete [] old_data_list;
                delete [] old_valid_list;

                // add a dummy value to end of list for iterator
                _valid_list[_length-1] = true;
            }

            // now that this index has been accessed it will be valid
            _valid_list[index] = true;
            return _data_list[index];
        }

        bool exists(uint64_t index)
        {
            if (index < _length-1)
            {
                return _valid_list[index];
            }
            return false;
        }

        void remove(uint64_t index)
        {
            if (index < _length-1) _valid_list[index] = false;
        }

        void clear()
        {
            for (int i = 0; i < _length; ++i) _valid_list[i] = false;
        }

        std::string debug_to_string()
        {
            std::string ret_str;
            for (int i = 0; i < _length-1; ++i)
            {
                if (_valid_list[i])
                {
                    ret_str += std::to_string(i) + ") Size: " + std::to_string(_item_size) + "\n";
                }
            }
            ret_str.pop_back();
            return ret_str;
        }

        ListItr<T> begin()
        {
            ListItr<T> i(0, *this);
            return i;
        }

        ListItr<T> end()
        {
            ListItr<T> i(_length-1, *this);
            return i;
        }

    private:

        friend class ListItr<T>;
        T *_data_list;
        bool *_valid_list;
        uint64_t _length, _item_size;

    };

    // -- Iterator -- //
    template <typename T>
    class ListItr
    {
    public:

        // CTOR (if given an invalid index-search for next element)
        ListItr(uint64_t index, List<T> &list) :
        _list(list),
        _element(index)
        {
            if (!_list._valid_list[index])
            {
                _element = find_next(index);
            }
        }

        // CTOR - copy
        ListItr(const ListItr &other) :
        _list(other._list),
        _element(other._element)
        {}

        // DTOR
        ~ListItr() {}

        ListItr& operator= (const ListItr& other)
        {
            _list = other._list;
            _element = other._element;
        }

        ListItr& operator++ ()
        {
            _element = find_next(_element);
            return *this;
        }

        bool operator!= (const ListItr &other)
        {
            return (_element != other._element);
        }

        T& operator* ()
        {
            return _list._data_list[_element];
        }

        T& operator-> ()
        {
            return _list._data_list[_element];
        }

    private:

        List<T> &_list;
        uint64_t _element;

        // finds next valid index - same index if none are left
        uint64_t find_next(uint64_t i)
        {
            uint64_t old_index = i;
            ++i;
            // search remaining list
            for (; i < _list._length; ++i)
            {
                if (_list._valid_list[i]) return i;
            }
            return old_index;
        }

    };
};

#endif /* end of include guard: __LIST_H__ */
