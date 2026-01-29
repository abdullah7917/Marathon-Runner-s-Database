//Abdullah Ali Khan, cs 163 - in person, 11/30/2025
//This file defines teh classes and the struct
#include <cstring>
#include <iostream>
using namespace std;

struct stream
{
    char * stream_id;
    char * name;
    char * game;
    int    viewers;
    int    duration;
    char * language;
    char * region;
    char * category;
    char * start_time;
};

struct node
{
    stream data;
    node * left;
    node * right;
};


class table
{
public:
    table();
    ~table();
    
    
    int insert(const stream & to_add);
    int display_all() const;
    int remove(const char * streamer_name, const char * game);
    int retrieve(const char * streamer_name, const char * stream_id, stream & found) const;
    int display_game(const char * game) const;
    int height() const;
    int remove_all();
    void destroy_stream(stream & data);

private:
    node * root;

   
    int insert(node *& root, const stream & to_add);
    int display_all(node * root) const;

    int remove(node *& root, const char * name, const char * game);

    int retrieve(node * root, const char * name, const char * stream_id, stream & found) const;
    int display_game(node * root, const char * game) const;

    int height(node * root) const;

    int remove_all(node *& root);

    void copy_stream(stream & dest, const stream & src)const;

 

};

