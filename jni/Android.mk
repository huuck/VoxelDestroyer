LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := NativeVoxelPrototype
LOCAL_SRC_FILES := NativeVoxelPrototype.cpp utils/matrix.cpp Engine/Display/VoxelVolume.cpp Engine/Display/Object3D.cpp Engine/Render/GLRenderer.cpp Engine/Scene/Scene3D.cpp Actors/Spaceship.cpp Actors/Bullet.cpp Actors/Asteroid.cpp Actors/ActorBase.cpp
LOCAL_LDLIBS 	:= -llog -lGLESv2
include $(BUILD_SHARED_LIBRARY)
