// ----------------------------------------------------------------------------
// DO NOT CHANGE THIS FILE, it's part of the interface to the bomberman server.
// ----------------------------------------------------------------------------

#ifndef PUBLIC_DEFINE_H
#define PUBLIC_DEFINE_H

#include <string>
#include <vector>

enum class ActionType { Hold, Up, Right, Down, Left, Bomb };

// Structs used in library and AI's
struct Location
{
    int x;
    int y;

    Location() :
        x(),
        y()
    {}

    Location( int x_, int y_ ) :
        x( x_ ),
        y( y_ )
    {}
};

// Structs used for inter library communication
struct EntityStruct
{
    Location loc;
    std::string type;
    int duration;

    EntityStruct() :
        loc(),
        type(),
        duration()
    {}

    EntityStruct( const Location& loc_, const std::string& type_, int duration_ ) :
        loc( loc_ ),
        type( type_ ),
        duration( duration_ )
    {}
};

struct TileStruct
{
    Location loc;
    bool crate;
    std::string type;

    TileStruct() :
        loc(),
        crate(),
        type()
    {}

    TileStruct( const Location& loc_, bool crate_, const std::string& type_ ) :
        loc( loc_ ),
        crate( crate_ ),
        type( type_ )
    {}
};

// Structs for Json Communiction
struct JPlayerLobbyStruct
{
    std::string playerName;

    std::string playerAttribute;

    JPlayerLobbyStruct() :
        playerName(),
        playerAttribute()
    {}

    JPlayerLobbyStruct( const std::string& playerName_, const std::string& playerAttribute_ ) :
        playerName( playerName_ ),
        playerAttribute( playerAttribute_ )
    {}

    virtual ~JPlayerLobbyStruct(){}
};

struct JPlayerStruct : JPlayerLobbyStruct
{
    bool alive;

    Location loc;

    JPlayerStruct() :
        JPlayerLobbyStruct(),
        alive(),
        loc()
    {}

    JPlayerStruct( const std::string& playerName_, const std::string& playerAttribute_, bool alive_, const Location& loc_ ) :
        JPlayerLobbyStruct( playerName_, playerAttribute_ ),
        alive( alive_ ),
        loc( loc_ )
    {}
};

// Input argument of AI
struct GameStateContainer
{
    int cycle;
    int width;
    int height;

    std::vector<JPlayerStruct> players;
    std::vector<EntityStruct> entities;
    std::vector<TileStruct> tiles;

    GameStateContainer() :
        cycle(),
        width(),
        height(),
        players(),
        entities(),
        tiles()
    {}

    GameStateContainer( int cycle_, int width_, int height_, const std::vector<JPlayerStruct>& players_, const std::vector<EntityStruct>& entities_, const std::vector<TileStruct>& tiles_ ) :
        cycle( cycle_ ),
        width( width_ ),
        height( height_ ),
        players( players_ ),
        entities( entities_ ),
        tiles( tiles_ )
    {}
};

#endif // PUBLIC_DEFINE_H
