cmake_minimum_required(VERSION 3.12)
# use a compiled version of wxWidgets: https://docs.wxwidgets.org/trunk/overview_cmake.html
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

include_directories(/usr/include/zebra-camera/multi-client)
include_directories(/usr/include/zebra-camera/image_converter)
include_directories(/usr/include/zebra-camera/device_manager)
include_directories(/usr/include/zebra-camera/monochrome_sdk)
include_directories(/usr/include/zebra-camera/imaging_library)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

include_directories("/usr/local/include/opencv4/")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
SET(OPENCV_LIB_DIR "/usr/local/lib")
LINK_DIRECTORIES("/usr/local/lib")
SET(ZEBRA_LIB_DIR "/usr/lib/zebra-camera")



SET(GCC_COVERAGE_LINK_FLAGS    "-lpng")
include_directories(/usr/include/zebra-camera/multi_client)
include_directories(/usr/include/zebra-camera/camera_sdk)

# sources
file(GLOB SOURCE "*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
add_executable(multi_client_zebra_camera_demo ${SOURCE})

target_link_libraries(multi_client_zebra_camera_demo ${wxWidgets_LIBRARIES})
target_link_libraries(multi_client_zebra_camera_demo ${ZEBRA_LIB_DIR}/libcamera_imaging_lib.so)
target_link_libraries(multi_client_zebra_camera_demo ${ZEBRA_LIB_DIR}/libmonochrome-sdk.so)
target_link_libraries(multi_client_zebra_camera_demo ${ZEBRA_LIB_DIR}/libclient_message_handler.so)
target_link_libraries(multi_client_zebra_camera_demo ${ZEBRA_LIB_DIR}/libuvc_adapter.so)
target_link_libraries(multi_client_zebra_camera_demo ${ZEBRA_LIB_DIR}/libdevice_manager.so)
target_link_libraries(multi_client_zebra_camera_demo ${ZEBRA_LIB_DIR}/libzebra_camera_client.so)
target_link_libraries(multi_client_zebra_camera_demo ${ZEBRA_LIB_DIR}/libdevmgr_adapter.so)
target_link_libraries(multi_client_zebra_camera_demo ${ZEBRA_LIB_DIR}/libzebra_camera_manager_client.so)
target_link_libraries(multi_client_zebra_camera_demo ${ZEBRA_LIB_DIR}/libzebracam.so)
target_link_libraries(multi_client_zebra_camera_demo ${ZEBRA_LIB_DIR}/libimage_converter.so)
target_link_libraries(multi_client_zebra_camera_demo ${ZEBRA_LIB_DIR}/libmessage_parser.so)




# link libraries

target_link_libraries(multi_client_zebra_camera_demo ${OPENCV_LIB_DIR}/libopencv_core.so)
target_link_libraries(multi_client_zebra_camera_demo ${OPENCV_LIB_DIR}/libopencv_imgproc.so)
target_link_libraries(multi_client_zebra_camera_demo ${OPENCV_LIB_DIR}/libopencv_video.so)
target_link_libraries(multi_client_zebra_camera_demo ${OPENCV_LIB_DIR}/libopencv_imgcodecs.so)
target_link_libraries(multi_client_zebra_camera_demo ${OPENCV_LIB_DIR}/libopencv_features2d.so)
target_link_libraries(multi_client_zebra_camera_demo ${OPENCV_LIB_DIR}/libopencv_videoio.so)
target_link_libraries(multi_client_zebra_camera_demo ${OPENCV_LIB_DIR}/libopencv_highgui.so)
