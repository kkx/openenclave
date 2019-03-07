# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License.


add_executable(qv host.c)

target_include_directories(qv PRIVATE ${CMAKE_CURRENT_BINARY_DIR} /home/oeadmin/openenclave -g -O0)
target_link_libraries(qv oehostapp)
