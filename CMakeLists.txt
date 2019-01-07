cmake_minimum_required(VERSION 3.12)
project(helloSFML)

set(CMAKE_CXX_STANDARD 11)
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
add_executable(helloSFML main.cpp Head.cpp Head.h Body.cpp Body.h Agents/Agent.cpp Agents/Agent.h Agents/EventAgent.cpp Agents/EventAgent.h Game.cpp Game.h Effect.cpp Effect.h GameEffects.cpp GameEffects.h PowerUp.cpp PowerUp.h)
target_link_libraries(helloSFML sfml-graphics sfml-window sfml-system)