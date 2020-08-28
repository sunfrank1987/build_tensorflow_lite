# build_tensorflow_lite
# 
build static tensorflow lite for android(only "armeabi-v7a",'arm64-v8a')


1. tensorflow(tested tensorflow 2.3.0) 
   url: https://github.com/tensorflow/tensorflow/tags

2. NDK (ndkr20 tested)
    ndk download url: https://developer.android.google.cn/ndk/downloads/

    make standalone toolchain
    https://developer.android.google.cn/ndk/guides/standalone_toolchain
    # 
    $ $NDK/build/tools/make_standalone_toolchain.py \
    --arch arm --api 21 --install-dir /tmp/my-android-toolchain


3. build

3.1 clone build script

    git clone https://github.com/sunfrank1987/build_tensorflow_lite.git
    + tensorflow/
        - BUILD
    + tensorflow/lite/tools/make/
        - build_android_armv7a.sh*
        - build_android_armv8a.sh*
        - Makefile.android
        + target/
            - android_makefile.inc

3.2 copy script to tensorflow path
    + ${tensorflow_root}/tensorflow/lite/tools/make
    + ${tensorflow_root}/tensorflow/lite/tools/make/target


3.3 edit 

    edit build_android_armv7a.sh or build_android_armv8a.sh as you need:

        export ndk_standalone_root="/opt/ndk/standalone-toolchain/ndkr20-aarch64"

3.4 download tensorflow lite dependencies

    cd  ${tensorflow_root}/tensorflow/lite/tools/make

    # download tensorflow lite dependencies
    ./download_dependencies.sh
    #

#


3.5 build
    chmod +x build_android_armv7a.sh
    ./build_android_armv7a.sh
    

    result:
    + gen/android_armv7a 
        + bin/
            - benchmark_model
            - benchmark_model_performance_options
            - minimal
        + lib/
            - benchmark-lib.a
            - libtensorflow-lite.a
        + obj/
            + tensorflow/
                + core/
                    .........
                + lite/
                    .........


3.6 export include headers
    
    tensorflow bazel BUILD not support tensorflow lite headers export 

    copy build_tensorflow_lite/tensorflow/BUILD context  genrule install_lite_headers to ${tensorflow_root}/tensorflow/BUILD file

    $ bazel build --config=opt tensorflow:install_lite_headers


    header file stored:

    tensorflow lite headers
        ${tensorflow_root}/bazel-bin/tensorflow/include_lite/
    flatbuffers heades
        ${tensorflow_root}/bazel-tensorflow-2.3.0/external/flatbuffers/include/

3.7 Android Demo











