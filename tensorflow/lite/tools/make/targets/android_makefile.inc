# Settings for generic aarch64 boards such as Odroid C2 or Pine64.
ifeq ($(TARGET), android_armv8a)
  # The aarch64 architecture covers all 64-bit ARM chips. This arch mandates
  # NEON, so FPU flags are not needed below.
  TARGET_ARCH := aarch64
  TARGET_TOOLCHAIN_PREFIX := aarch64-linux-android-
  TARGET_OUT_DIR := android_armv8a

  CXXFLAGS += \
    -march=armv8-a \
    -funsafe-math-optimizations \
    -ftree-vectorize \
    -fPIC

  CFLAGS += \
    -march=armv8-a \
    -funsafe-math-optimizations \
    -ftree-vectorize \
    -fPIC

  LDFLAGS := \
    -Wl,--no-export-dynamic \
    -Wl,--exclude-libs,ALL \
    -Wl,--gc-sections \
    -Wl,--as-needed \
    -static-libstdc++ \


  LIBS := \
    -latomic \
    -lm \
    -ldl

#     -lpthread \


endif

ifeq ($(TARGET), android_armv7a)
    TARGET_ARCH := aarch32
    TARGET_TOOLCHAIN_PREFIX := arm-linux-androideabi-
    TARGET_OUT_DIR := android_armv7a

  CXXFLAGS += \
    -march=armv7-a \
    -mfpu=neon \
    -funsafe-math-optimizations \
    -ftree-vectorize \
    -fPIC

  CFLAGS += \
    -march=armv7-a \
    -mfpu=neon \
    -funsafe-math-optimizations \
    -ftree-vectorize \
    -fPIC

  LDFLAGS := \
    -Wl,--no-export-dynamic \
    -Wl,--exclude-libs,ALL \
    -Wl,--gc-sections \
    -Wl,--as-needed \
    -static-libstdc++ \

# del     
# -lrt

  LIBS := \
    -latomic \
    -lm \
    -ldl \

# del    
#    -lpthread \    

endif
