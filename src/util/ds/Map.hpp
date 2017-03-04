#ifndef __MAP_H__
#define __MAP_H__

#include <map>

namespace wj
{
    template <typename K, typename V>
    class Map
    {
    public:

        Map()
        {}

        Map(const Map &) = delete;

        ~Map()
        {}

        V& operator[] (const K &key)
        {
            return _map[key];
        }

        bool has (const K &key)
        {
            if (_map.find(key) == _map.end()) return false;
            return true;
        }

    private:

        std::map<K, V> _map;

    };
};

#endif /* end of include guard: __MAP_H__ */
