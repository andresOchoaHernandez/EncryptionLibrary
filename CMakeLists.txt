project(EncryptedCommunication)

cmake_minimum_required(VERSION 3.16)

find_package(OpenSSL REQUIRED)

find_package(Doxygen)

if(DOXYGEN_FOUND)
    
    set(DOXYGEN_IN  ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target( 
        doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating TestMvb documentation with Doxygen"
    )

else(DOXYGEN_FOUND)

    message("Doxygen not found, cannot generate documentation")

endif()

add_executable(ec ${PROJECT_SOURCE_DIR}/Main.cpp)

target_include_directories(
    ec
    
    PRIVATE ${PROJECT_SOURCE_DIR}/include
    
    PRIVATE ${PROJECT_SOURCE_DIR}/src
)

target_sources(
    ec
    
    PUBLIC ${PROJECT_SOURCE_DIR}/include/AES256EncryptorHandler.hpp
    PUBLIC ${PROJECT_SOURCE_DIR}/include/RSAEncryptorHandler.hpp

    PRIVATE ${PROJECT_SOURCE_DIR}/include/CryptoHandler.hpp

    PRIVATE ${PROJECT_SOURCE_DIR}/src/AES256EncryptorHandler.cpp
    PRIVATE ${PROJECT_SOURCE_DIR}/src/RSAEncryptorHandler.cpp
)

target_link_libraries(ec OpenSSL::SSL)