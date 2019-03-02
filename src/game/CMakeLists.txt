#
# This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#

set(LIBRARY_NAME game)

add_definitions(-DDT_POLYREF64)
add_definitions(-D__ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES=0)

# include additionals headers
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/vmap
  ${CMAKE_CURRENT_SOURCE_DIR}/AuctionHouseBot
  ${CMAKE_CURRENT_SOURCE_DIR}/BattleGround
  ${CMAKE_CURRENT_SOURCE_DIR}/OutdoorPvP
  ${CMAKE_BINARY_DIR}
)

# Find all the input files
FILE(GLOB_RECURSE LIBRARY_SRCS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.h" "*.cpp")

if(NOT BUILD_SCRIPTDEV)
  # exclude script folder for faster build time (used for dev mode)
  set (EXCLUDE_DIR "AI/ScriptDevAI/scripts/")
  foreach (TMP_PATH ${LIBRARY_SRCS})
      string (FIND ${TMP_PATH} ${EXCLUDE_DIR} EXCLUDE_DIR_FOUND)
      if (NOT ${EXCLUDE_DIR_FOUND} EQUAL -1)
          list(REMOVE_ITEM LIBRARY_SRCS ${TMP_PATH})
      endif ()
  endforeach()
endif()

# Create visual studio groups using folder structure
foreach(source ${LIBRARY_SRCS})
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()

add_library(${LIBRARY_NAME} STATIC
  ${LIBRARY_SRCS}
)

target_link_libraries(${LIBRARY_NAME}
  PRIVATE shared
  PRIVATE g3dlite
  PRIVATE detour
  PRIVATE ${ZLIB_LIBRARIES}
)

# include additionals headers
set(ADDITIONAL_INCLUDE_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/vmap
  ${CMAKE_CURRENT_SOURCE_DIR}/AuctionHouseBot
  ${CMAKE_CURRENT_SOURCE_DIR}/BattleGround
  ${CMAKE_CURRENT_SOURCE_DIR}/OutdoorPvP
  ${CMAKE_CURRENT_SOURCE_DIR}/playerbot
  ${CMAKE_BINARY_DIR}
)

target_include_directories(${LIBRARY_NAME}
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  PRIVATE ${ADDITIONAL_INCLUDE_DIRS}
  PRIVATE ${Boost_INCLUDE_DIRS}
)

if(BUILD_PLAYERBOT)
    include_directories(
        ${CMAKE_SOURCE_DIR}/src/modules/Bots/playerbot
        ${CMAKE_SOURCE_DIR}/src/modules/Bots/ahbot
        ${CMAKE_SOURCE_DIR}/src/game
        ${CMAKE_SOURCE_DIR}/src/game/AI
        ${CMAKE_SOURCE_DIR}/src/game/Accounts
        ${CMAKE_SOURCE_DIR}/src/game/Addons
        ${CMAKE_SOURCE_DIR}/src/game/Arena
        ${CMAKE_SOURCE_DIR}/src/game/AuctionHouse
        ${CMAKE_SOURCE_DIR}/src/game/BattleGround
        ${CMAKE_SOURCE_DIR}/src/game/Chat
        ${CMAKE_SOURCE_DIR}/src/game/ChatCommands
        ${CMAKE_SOURCE_DIR}/src/game/Combat
        ${CMAKE_SOURCE_DIR}/src/game/DBScripts
        ${CMAKE_SOURCE_DIR}/src/game/Entities
        ${CMAKE_SOURCE_DIR}/src/game/GMTickets
        ${CMAKE_SOURCE_DIR}/src/game/GameEvents
        ${CMAKE_SOURCE_DIR}/src/game/Globals
        ${CMAKE_SOURCE_DIR}/src/game/Grids
        ${CMAKE_SOURCE_DIR}/src/game/Groups
        ${CMAKE_SOURCE_DIR}/src/game/Guilds
        ${CMAKE_SOURCE_DIR}/src/game/LFG
        ${CMAKE_SOURCE_DIR}/src/game/Loot
        ${CMAKE_SOURCE_DIR}/src/game/Mails
        ${CMAKE_SOURCE_DIR}/src/game/Maps
        ${CMAKE_SOURCE_DIR}/src/game/MotionGenerators
        ${CMAKE_SOURCE_DIR}/src/game/Movement
        ${CMAKE_SOURCE_DIR}/src/game/Object
        ${CMAKE_SOURCE_DIR}/src/game/OutdoorPvP
        ${CMAKE_SOURCE_DIR}/src/game/Pools
        ${CMAKE_SOURCE_DIR}/src/game/Quests
        ${CMAKE_SOURCE_DIR}/src/game/References
        ${CMAKE_SOURCE_DIR}/src/game/Reputation
        ${CMAKE_SOURCE_DIR}/src/game/Server
        ${CMAKE_SOURCE_DIR}/src/game/Server
        ${CMAKE_SOURCE_DIR}/src/game/Skills
        ${CMAKE_SOURCE_DIR}/src/game/Social
        ${CMAKE_SOURCE_DIR}/src/game/Spells
        ${CMAKE_SOURCE_DIR}/src/game/Tools
        ${CMAKE_SOURCE_DIR}/src/game/Trade
        ${CMAKE_SOURCE_DIR}/src/game/VoiceChat
        ${CMAKE_SOURCE_DIR}/src/game/Warden
        ${CMAKE_SOURCE_DIR}/src/game/Weather
        ${CMAKE_SOURCE_DIR}/src/game/World
        ${CMAKE_SOURCE_DIR}/src/game/WorldHandlers
        ${CMAKE_SOURCE_DIR}/src/game/movement
        ${CMAKE_SOURCE_DIR}/src/game/vmap
        ${CMAKE_SOURCE_DIR}/src/shared
        ${CMAKE_SOURCE_DIR}/src/shared/Auth
        ${CMAKE_SOURCE_DIR}/src/shared/Config
        ${CMAKE_SOURCE_DIR}/src/shared/Common
        ${CMAKE_SOURCE_DIR}/src/shared/Database
        ${CMAKE_SOURCE_DIR}/src/shared/DataStores
        ${CMAKE_SOURCE_DIR}/src/shared/Utilities
        ${CMAKE_SOURCE_DIR}/src/shared/Log
        ${CMAKE_SOURCE_DIR}/src/shared/Threading
    )
    target_link_libraries(${LIBRARY_NAME} PUBLIC Bots)
    add_dependencies(${LIBRARY_NAME} Bots)
endif()

if(BUILD_IMMERSIVE)
    include_directories(
        ${CMAKE_SOURCE_DIR}/src/modules/Immersive
        ${CMAKE_SOURCE_DIR}/src/modules/Immersive
    )
    target_link_libraries(${LIBRARY_NAME} PUBLIC Immersive)
    add_dependencies(${LIBRARY_NAME} Immersive)
endif()

if(UNIX)
  # Both systems don't have libdl and don't need them
  if (NOT (CMAKE_SYSTEM_NAME STREQUAL "FreeBSD" OR CMAKE_SYSTEM_NAME STREQUAL "NetBSD"))
    target_link_libraries(${LIBRARY_NAME} PUBLIC dl)
  endif()
endif()

# Define BUILD_SCRIPTDEV if need
if (BUILD_SCRIPTDEV)
  add_definitions(-DBUILD_SCRIPTDEV)
endif()

# Define ENABLE_PLAYERBOTS if need
if (BUILD_PLAYERBOT)
  add_definitions(-DENABLE_PLAYERBOTS)
endif()

# Define ENABLE_IMMERSIVE if need
if (BUILD_IMMERSIVE)
  add_definitions(-DENABLE_IMMERSIVE)
endif()

# Generate precompiled header
if(PCH)
  if (MSVC)
    set(PCHBaseName "pchdef")
    set(PrecompiledBinary "$(IntDir)/${PCHBaseName}.pch")
    set(PrecompiledHeader "${PCHBaseName}.h")
    set(PrecompiledSource "${PCHBaseName}.cpp")
    #set_property(TARGET ${LIBRARY_NAME} PROPERTY COMPILE_FLAGS " /Yu\"${PrecompiledHeader}\" /FI\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\"")
    #set_property(SOURCE ${PrecompiledSource} PROPERTY COMPILE_FLAGS "/Yc\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\"")
    set_target_properties(${LIBRARY_NAME} PROPERTIES COMPILE_FLAGS " /Yu\"${PrecompiledHeader}\" /FI\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\" /bigobj")
    set_source_files_properties(${PrecompiledSource} PROPERTIES COMPILE_FLAGS "/Yc\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\"")
    set_target_properties(${LIBRARY_NAME} PROPERTIES PROJECT_LABEL "Game")
  elseif(NOT MINGW)
    # TODO: Resolve issues with order of includes before enabling Cotire for MinGW builds
    cotire(${LIBRARY_NAME})
  endif()
  include_directories(${CMAKE_CURRENT_BINARY_DIR})
endif()

# confi file should come from bots directory
#install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/aiplayerbot.conf.dist.in DESTINATION ${CONF_DIR} RENAME playerbot.conf.dist)
