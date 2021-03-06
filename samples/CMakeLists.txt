# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License.

if (USE_LIBSGX)
  install(DIRECTORY remote_attestation local_attestation
    DESTINATION ${CMAKE_INSTALL_DATADIR}/openenclave/samples
    PATTERN "gen_pubkey_header.sh"
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
        GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ)
endif ()

install(DIRECTORY helloworld file-encryptor data-sealing
  DESTINATION ${CMAKE_INSTALL_DATADIR}/openenclave/samples)

install(FILES Makefile README.md
  DESTINATION ${CMAKE_INSTALL_DATADIR}/openenclave/samples)

# TODO: Remove this when the new script supports all the samples for
# both the CMake package and pkg-config.
add_test(samples_pkg_config
  sh ${CMAKE_CURRENT_SOURCE_DIR}/test-samples.sh -i ${PROJECT_BINARY_DIR} ${CMAKE_INSTALL_PREFIX} ${PROJECT_BINARY_DIR}/samples/samples-test)
set_property(TEST samples_pkg_config PROPERTY ENVIRONMENT "USE_LIBSGX=${USE_LIBSGX}")

# This script currently only tests data-sealing against the CMake package.
add_test(NAME samples
  COMMAND ${CMAKE_COMMAND} -DSOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR} -DBUILD_DIR=${PROJECT_BINARY_DIR} -DPREFIX_DIR=${CMAKE_INSTALL_PREFIX} -P ${CMAKE_CURRENT_SOURCE_DIR}/test-samples.cmake)
