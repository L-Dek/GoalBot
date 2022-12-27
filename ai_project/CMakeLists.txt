add_library(ai_project)

configure_file(AgentName.in.cpp AgentName.cpp)

target_sources(ai_project PRIVATE
    Agent.h
    public_define.h
    AIBaseClass.h

    botroutine.h
    goalcreator.h
    inforetriever.h
    infomatrix.h
    memorycontainer.h
    pathfinder.h
    safetymatrix.h
    goals/goal.h
    goals/dontgetkilledgoal.h
    goals/makeroomgoal.h
    goals/goalfactory.h
    goals/dontgetkilledfactory.h
    goals/makeroomfactory.h
    utils.h 
    AStar.hpp




    Agent.cpp
    AIBaseClass.cpp
    AgentName.cpp

    botroutine.cpp
    goalcreator.cpp
    inforetriever.cpp
    infomatrix.cpp
    pathfinder.cpp
    safetymatrix.cpp
    goals/goal.cpp
    goals/dontgetkilledgoal.cpp
    goals/makeroomgoal.cpp
    goals/goalfactory.cpp
    goals/dontgetkilledfactory.cpp
    goals/makeroomfactory.cpp
    utils.cpp
    AStar.cpp
)

target_include_directories(ai_project PUBLIC ${CMAKE_CURRENT_LIST_DIR})
