# A basic installer setup.
#
# This cmake file introduces two targets
#  bstep-products:      moves all the built assets to a well named directory
#  bstep-installer:   depends on bstep-products, builds an installer
#
# Right now bstep-installer builds just the crudest zip file but this is the target
# on which we will hang the proper installers later

set(BSTEP_PRODUCT_DIR ${CMAKE_BINARY_DIR}/bstep-products)
file(MAKE_DIRECTORY ${BSTEP_PRODUCT_DIR})

add_custom_target(bstep-products ALL)
add_custom_target(bstep-installer)

function(bstep_package format)
    get_target_property(output_dir B-Step RUNTIME_OUTPUT_DIRECTORY)

    if (TARGET B-Step_${format})
        add_dependencies(bstep-products B-Step_${format})
        add_custom_command(
                TARGET bstep-products
                POST_BUILD
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMAND echo "Installing ${output_dir}/${format} to ${BSTEP_PRODUCT_DIR}"
                COMMAND ${CMAKE_COMMAND} -E copy_directory ${output_dir}/${format}/ ${BSTEP_PRODUCT_DIR}/
        )
    endif ()
endfunction()

bstep_package(VST3)
bstep_package(VST)
bstep_package(LV2)
bstep_package(AU)
bstep_package(CLAP)
bstep_package(Standalone)

if (WIN32)
    message(STATUS "Including special windows cleanup installer stage")
    add_custom_command(TARGET bstep-products
            POST_BUILD
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMAND ${CMAKE_COMMAND} -E echo "Cleaning up windows goobits"
            COMMAND ${CMAKE_COMMAND} -E rm -f "${BSTEP_PRODUCT_DIR}/Shortcircuit XT.exp"
            COMMAND ${CMAKE_COMMAND} -E rm -f "${BSTEP_PRODUCT_DIR}/Shortcircuit XT.ilk"
            COMMAND ${CMAKE_COMMAND} -E rm -f "${BSTEP_PRODUCT_DIR}/Shortcircuit XT.lib"
            COMMAND ${CMAKE_COMMAND} -E rm -f "${BSTEP_PRODUCT_DIR}/Shortcircuit XT.pdb"
            )
endif ()

add_dependencies(bstep-installer bstep-products)

add_custom_command(
        TARGET bstep-installer
        POST_BUILD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMAND echo "Installing LICENSE and so forth to ${BSTEP_PRODUCT_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/LICENSE ${BSTEP_PRODUCT_DIR}/
        # COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Installer/ZipReadme.txt ${BSTEP_PRODUCT_DIR}/Readme.txt
)

find_package(Git)

if (Git_FOUND)
    execute_process(
            COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE VERSION_CHUNK
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
else ()
    set(VERSION_CHUNK "unknownhash")
endif ()

string(TIMESTAMP BSTEP_DATE "%Y-%m-%d")
if (WIN32)
    math(EXPR BITS "8*${CMAKE_SIZEOF_VOID_P}")
    set(BSTEP_ZIP BStep-${BSTEP_DATE}-${VERSION_CHUNK}-${CMAKE_SYSTEM_NAME}-${BITS}bit.zip)
else ()
    set(BSTEP_ZIP BStep-${BSTEP_DATE}-${VERSION_CHUNK}-${CMAKE_SYSTEM_NAME}.zip)
endif ()


if (APPLE)
    message(STATUS "Configuring for mac installer.")
    add_custom_command(
            TARGET bstep-installer
            POST_BUILD
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${CMAKE_COMMAND} -E make_directory installer
            COMMAND ${CMAKE_SOURCE_DIR}/libs/sst/sst-plugininfra/scripts/installer_mac/make_installer.sh "B-Step" ${CMAKE_BINARY_DIR}/bstep-products ${CMAKE_SOURCE_DIR}/resources/installer_mac ${CMAKE_BINARY_DIR}/installer "${BSTEP_DATE}-${VERSION_CHUNK}"
    )
elseif (WIN32)
    message(STATUS "Basic Installer: Target is installer/${BSTEP_ZIP}")
    add_custom_command(
            TARGET bstep-installer
            POST_BUILD
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${CMAKE_COMMAND} -E make_directory installer
            COMMAND 7z a -r installer/${BSTEP_ZIP} ${BSTEP_PRODUCT_DIR}/
            COMMAND ${CMAKE_COMMAND} -E echo "Installer in: installer/${BSTEP_ZIP}")
else ()
    message(STATUS "Basic Installer: Target is installer/${BSTEP_ZIP}")
    add_custom_command(
            TARGET bstep-installer
            POST_BUILD
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${CMAKE_COMMAND} -E make_directory installer
            COMMAND ${CMAKE_COMMAND} -E tar cvf installer/${BSTEP_ZIP} --format=zip ${BSTEP_PRODUCT_DIR}/
            COMMAND ${CMAKE_COMMAND} -E echo "Installer in: installer/${BSTEP_ZIP}")
endif ()
