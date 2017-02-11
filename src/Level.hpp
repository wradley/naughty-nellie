#ifndef __LEVEL_H__
#define __LEVEL_H__

namespace wj
{
    class Level
    {
    public:

        Level();
        ~Level();

        // returns false if file is not found
        bool set_level_file(const std::string &level_file_path);
        bool set_defs_file(const std::string &def_file_path);

        bool is_loading();
        bool is_saving();

        void run();
        void stop();

    private:

        bool load_defs();
        bool load_level();
        bool save_level();

        bool _running, _loading, _saving, _needs_save, _paused;
        std::string _level_file, _def_file;

    };
};

#endif /* end of include guard: __LEVEL_H__ */
