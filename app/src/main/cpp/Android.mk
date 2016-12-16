LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := NativeGLES

LOCAL_SRC_FILES := NativeGLES.cpp Shader.cpp Camera.cpp ./glm/detail/*.* ./glm/gtc/*.* ./glm/gtx/*.* ./glm/simd/*.* ./glm/*.*

LOCAL_LDLIBS := -lGLESv3 -llog

include $(BUILD_SHARED_LIBRARY)
