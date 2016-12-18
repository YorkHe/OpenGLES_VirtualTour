LOCAL_PATH := $(call my-dir)


include $(CLEAR_VARS)
LOCAL_MODULE := assimp
LOCAL_SRC_FILES := ./assimp/libassimp.so
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)

LOCAL_MODULE := SOIL
LOCAL_SRC_FILES := ./SOIL/image_helper.c ./SOIL/stb_image_aug.c ./SOIL/image_DXT.c ./SOIL/SOIL.c
LOCAL_LDFLAGS := -v
LOCAL_LDLIBS := -lGLESv3
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := NativeGLES

LOCAL_SRC_FILES := NativeGLES.cpp Shader.cpp Camera.cpp Mesh.cpp Model.cpp ./glm/detail/*.* ./glm/gtc/*.* ./glm/gtx/*.* ./glm/simd/*.* ./glm/*.*

LOCAL_LDLIBS := -lGLESv3 -llog
LOCAL_SHARED_LIBRARIES:= SOIL assimp
LOCAL_LDFLAGS := -v


include $(BUILD_SHARED_LIBRARY)
