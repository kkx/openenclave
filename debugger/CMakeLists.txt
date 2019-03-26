# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License.

add_subdirectory(ptraceLib)
add_subdirectory(pythonExtension)

# During build do an install of debugger to the output folder
set(CMAKE_INSTALL_PREFIX_BAK ${CMAKE_INSTALL_PREFIX})

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/output)
configure_file(oegdb.in ${OE_BINDIR}/oegdb)

# Reset variables
set(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX_BAK})

# Patch oe-gdb script based on install location.
configure_file(oegdb.in oegdb-for-install)

# Install and rename oe-gdb-for-install
install (PROGRAMS ${CMAKE_BINARY_DIR}/debugger/oegdb-for-install DESTINATION ${CMAKE_INSTALL_BINDIR}
         RENAME oegdb)
