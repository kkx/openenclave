# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License.

# Use the edger8r to generate C bindings from the EDL file.
add_custom_command(OUTPUT datasealing_t.h datasealing_t.c
  COMMAND openenclave::oeedger8r --trusted ${CMAKE_SOURCE_DIR}/datasealing.edl)

# Create a library common to each of our three enclaves.
add_library(common OBJECT dispatcher.cpp keys.cpp ${CMAKE_CURRENT_BINARY_DIR}/datasealing_t.c)
set_property(TARGET common PROPERTY CXX_STANDARD 11)
target_link_libraries(common PUBLIC openenclave::oeenclave openenclave::oelibcxx)
target_include_directories(common PUBLIC ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
