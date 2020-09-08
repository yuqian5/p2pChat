CMAKE_MINIMUM_REQUIRED( VERSION 3.15 )
PROJECT( pchat )

SET( CMAKE_CXX_STANDARD 17 )

ADD_EXECUTABLE( pchat src/main.cpp src/GroupChatClient.cpp include/GroupChatClient.hpp src/GroupChatServer.cpp include/GroupChatServer.hpp src/ChatInterface.cpp include/ChatInterface.hpp src/SerializableMessagePackage.cpp include/SerializableMessagePackage.hpp include/TSQueue.hpp)

# link curses
FIND_PACKAGE( Curses REQUIRED )
INCLUDE_DIRECTORIES( ${CURSES_INCLUDE_DIR} )
TARGET_LINK_LIBRARIES( pchat ${CURSES_LIBRARIES} )

# link thread
FIND_PACKAGE( Threads REQUIRED )
TARGET_LINK_LIBRARIES ( pchat ${CMAKE_THREAD_LIBS_INIT} )

# link rt if on linux
IF( LINUX AND NOT APPLE )
    FIND_PACKAGE( RT REQUIRED )
    TARGET_LINK_LIBRARIES( pchat RT )
ENDIF( LINUX AND NOT APPLE )
