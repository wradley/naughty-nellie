#ifndef __LIST_H__
#define __LIST_H__

// T            operator[] (uint64_t index)
// bool         exists (uint64_t index)
// void         remove (uint64_t index)
// void         clear ()
// std::string  debug_to_string ()

#include <cstdint>
#include <cstdio>
#include <string>

static const int START_SIZE = 16;

namespace wj
{
    template <typename T>
    class List
    {
    public:

        List()
        {
            _item_size = sizeof(T);
            _length = START_SIZE;
            _data_list  = new    T [_length];
            _valid_list = new bool [_length];
            for (int i = 0; i < _length; ++i) _valid_list[i] = false;
        }

        List(const List &other) = delete;
        void operator= (const List &other) = delete;

        ~List()
        {
            if (_data_list)  delete [] _data_list;
            if (_valid_list) delete [] _valid_list;
        }

        T& operator[] (uint64_t index)
        {
            // check for possible resize
            while (index >= _length)
            {
                _length *= 2;

                // reference old lists
                T *old_data_list = _data_list;
                bool *old_valid_list = _valid_list;

                // make new ones
                _data_list  = new    T [_length];
                _valid_list = new bool [_length];

                // copy over data
                int i;
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
            }

            // now that this index has been accessed it will be valid
            _valid_list[index] = true;
            return _data_list[index];
        }

        bool exists(uint64_t index)
        {
            if (index < _length)
            {
                return _valid_list[index];
            }
            return false;
        }

        void remove(uint64_t index)
        {
            if (index < _length)
            {
                _valid_list[index] = false;
            }
        }

        void clear()
        {
            for (int i = 0; i < _length; ++i) _valid_list[i] = false;
        }

        std::string debug_to_string()
        {
            std::string ret_str;

            for (int i = 0; i < _length; ++i)
            {
                if (_valid_list[i])
                {
                    ret_str += std::to_string(i) + ") Size: " + std::to_string(_item_size) + "\n";
                }
            }
            ret_str.pop_back();
            return ret_str;
        }

    private:

        T *_data_list;
        bool *_valid_list;
        uint64_t _length, _item_size;

    };
};

#endif /* end of include guard: __LIST_H__ */
