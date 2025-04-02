# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.
# For more examples on how to use CMake, see https://github.com/android/ndk-samples.

# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.22.1)

include_directories(C:/Users/Administrator/AndroidStudioProjects/md5sha/app/src/main/openssl/include)


#动态方式加载
add_library(openssl STATIC IMPORTED )
add_library(ssl STATIC IMPORTED )

#引入第三方.so库，根据${ANDROID_ABI} 引用不同的库
set_target_properties(openssl PROPERTIES IMPORTED_LOCATION C:/Users/Administrator/AndroidStudioProjects/md5sha/app/src/main/openssl/lib/${ANDROID_ABI}/libcrypto.so)
set_target_properties(ssl PROPERTIES IMPORTED_LOCATION C:/Users/Administrator/AndroidStudioProjects/md5sha/app/src/main/openssl/lib/${ANDROID_ABI}/libssl.so)
# Declares the project name. The project name can be accessed via ${ PROJECT_NAME},
# Since this is the top level CMakeLists.txt, the project name is also accessible
# with ${CMAKE_PROJECT_NAME} (both CMake variables are in-sync within the top level
# build script scope).
project("md5sha")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
#
# In this top level CMakeLists.txt, ${CMAKE_PROJECT_NAME} is used to define
# the target library name; in the sub-module's CMakeLists.txt, ${PROJECT_NAME}
# is preferred for the same purpose.
#
# In order to load a library into your app from Java/Kotlin, you must call
# System.loadLibrary() and pass the name of the library defined here;
# for GameActivity/NativeActivity derived applications, the same library name must be
# used in the AndroidManifest.xml file.
add_library(${CMAKE_PROJECT_NAME} SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        native-lib.cpp)


# Specifies libraries CMake should link to your target library. You
# can link libraries from various origins, such as libraries defined in this
# build script, prebuilt third-party libraries, or Android system libraries.
target_link_libraries(${CMAKE_PROJECT_NAME}
        # List libraries link to the target library
        android
        openssl
        ssl
        log)

set(CMAKE_ANDROID_ARCH_ABI armeabi-v7a arm64-v8a x86 x86_64)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/src/main/openssl/lib/${ANDROID_ABI})
message(STATUS "ANDROID_ABI: ${ANDROID_ABI}")