#include "Level.hpp"
#include <SDL2/SDL.h>
#include <thread>
#include <iostream>
#include <fstream>

wj::Level::Level()
{
    _position_sys = new PositionSystem;
    _graphics_sys = new GraphicsSystem;

    init_vm();
}

wj::Level::~Level()
{
    free_systems();
}

void wj::Level::load_define(std::string def_filepath)
{
    _level_lock.lock();

    // delete system data
    delete _position_sys;
    delete _graphics_sys;

    // create new system stuff
    _position_sys = new PositionSystem;
    _graphics_sys = new GraphicsSystem;
    init_vm();

    // load in data
    _vm.run(def_filepath);

    _level_lock.unlock();
}


void wj::Level::run(std::string level_filepath)
{
    // save and stop current level
    stop();

    _level_lock.lock();

    // load the level
    _level_filename = level_filepath;
    load_level();

    // set state
    _running = true;
    _paused = true;

    // start up position thread
    std::thread tposition(
        ([](PositionSystem *position_sys, bool *running){
            while (*running)
            {
                position_sys->update();
                SDL_Delay(100);
            }
        }),
        _position_sys,
        &_running
    ); tposition.detach();

    // start up graphics thread
    std::thread tgraphics(
        ([](GraphicsSystem *graphics_sys, bool *running){
            while (*running)
            {
                graphics_sys->update();
                SDL_Delay(100);
            }
        }),
        _graphics_sys,
        &_running
    ); tgraphics.detach();

    // un-pause game
    _paused = false;
    _level_lock.unlock();
    printf("Unlocked\n");
}

// Use when quitting the application
void wj::Level::stop()
{
    printf("Stop\n");
    _level_lock.lock();

    // stop the game
    _running = false;
    _paused = false;

    // wait for each system to finish its last update
    SDL_Delay(500);

    // save all level data
    save();

    // clear out all level data in each system
    _position_sys->clear_instance_data();
    _graphics_sys->clear_instance_data();

    _level_lock.unlock();
}


void wj::Level::free_systems()
{
    delete _graphics_sys;
    delete _position_sys;
}


void wj::Level::exit()
{
    stop();
    free_systems();
    SDL_Quit();
}


void wj::Level::init_vm()
{
    if (_position_sys == NULL)
    {
        printf("Error Position System Null in Level\n");
        assert(0);
    }

    if (_graphics_sys == NULL)
    {
        printf("Error Graphics System Null in Level\n");
        assert(0);
    }

    _vm.init(_position_sys);
    _vm.init(_graphics_sys);
}

static std::string get_next_word(std::string &str, uint64_t &i)
{
    std::string word = "";

    // find front of next word
    while (str[i] == ' ' || str[i] == '\n')
    {
        if (i >= str.size())
        {
            printf("Got word: EOF\n");
            return "EOF";
        }
        ++i;
    }

    // store word
    while (str[i] != ' ' && str[i] != '\n')
    {
        if (i >= str.size())
        {
            printf("Got word: EOF\n");
            return "EOF";
        }

        word.push_back(str[i]);
        ++i;
    }
    printf("Got word: %s\n", word.c_str());
    return word;
}

std::string file_to_str(const std::string &filename)
{
    std::FILE *fp = std::fopen(filename.c_str(), "rb");
    if (fp)
    {
        std::string contents;
        std::fseek(fp, 0, SEEK_END);
        contents.resize(std::ftell(fp));
        std::rewind(fp);
        std::fread(&contents[0], 1, contents.size(), fp);
        std::fclose(fp);
        return(contents);
    }
    assert(0);
}

void save_str_to_file(const std::string &str, const std::string &filename)
{
    std::ofstream file(filename);
    file << str;
    file.close();
}

void wj::Level::load_level()
{
    _save_lock.lock();
    std::string level_str(file_to_str(_level_filename));
    uint64_t i = 0;
    uint64_t instance_num = 0;

    _ent_data.clear();

    std::string word;
    while (i < (level_str.size() - 6))
    {
        EntData e;
        e.def_id = std::stoi(get_next_word(level_str, i));
        e.x = std::stod(get_next_word(level_str, i));
        e.y = std::stod(get_next_word(level_str, i));
        e.rotation = std::stod(get_next_word(level_str, i));
        e.layer = std::stoi(get_next_word(level_str, i));
        _ent_data[instance_num++] = e;
    }
    _save_lock.unlock();
}

// saves a level out to the file used to load level
void wj::Level::save()
{
    _save_lock.lock();

    // load contents of _ent_data into string
    std::string level_str;

    for (auto e : _ent_data)
    {
        std::string line = "";
        line += std::to_string(e.def_id) + " ";
        line += std::to_string(e.x) + " ";
        line += std::to_string(e.y) + " ";
        line += std::to_string(e.rotation) + " ";
        line += std::to_string(e.layer) + "\n";
    }

    // save string out to file
    save_str_to_file(level_str, _level_filename);
    _save_lock.unlock();
}
