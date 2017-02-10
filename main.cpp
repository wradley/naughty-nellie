class Game
{
public:

    bool set_level_file(const std::string &level_file_path);
    bool set_defs_file(const std::string &def_file_path);

    bool is_loading();
    bool is_saving();

    void run()
    {
        // Make sure to stop and save previous levels
        stop();

        _running = true;
        load_level();
        _needs_save = true;
        while (is_loading()); // wait to finish load

        // start each system update function on its own thread
        std::thread position_sys_thread(_position_sys.update, _running, _paused);

        // detach each system
        position_sys_thread.detach();
    }

    void stop()
    {
        _running = false;

        // save old data if previous level was loaded
        if (_needs_save)
        {
            // let system threads finish their last updates
            sleep(100);
            save_level();
        }

        while (is_saving()); // wait to finish save
    }

private:

    bool load_defs();
    bool load_level();
    bool save_level();

    bool _running, _loading, _saving, _needs_save, _paused;
    std::string _level_file, _def_file;

};

int main(int argc, char const *argv[])
{


    return 0;
}
