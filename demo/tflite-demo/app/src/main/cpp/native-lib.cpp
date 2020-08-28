#include <jni.h>
#include <string>
#include <memory>
#include<sstream>

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"

#include <android/log.h>

#define  LOG_TAG "fz"
#ifndef SOURCE_PATH_SIZE
#define SOURCE_PATH_SIZE 0
#endif

#define __FILE_NAME__ ((char*)__FILE__+SOURCE_PATH_SIZE)

#define LOGI(format, ...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "[%s %s:%d] " format, __FILE_NAME__,  __FUNCTION__, __LINE__ , ##__VA_ARGS__)
#define LOGD(format, ...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, "[%s %s:%d] " format, __FILE_NAME__,  __FUNCTION__, __LINE__ , ##__VA_ARGS__)
#define LOGW(format, ...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, "[%s %s:%d] " format,  __FILE_NAME__,__FUNCTION__, __LINE__ , ##__VA_ARGS__)
#define LOGE(format, ...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "[%s %s:%d] " format,  __FILE_NAME__,__FUNCTION__, __LINE__ , ##__VA_ARGS__)
#define LOGV(format, ...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "[%s %s:%d] " format,  __FILE_NAME__,__FUNCTION__, __LINE__ , ##__VA_ARGS__)

class TfliteDemo {
public:
    TfliteDemo() { }

    ~TfliteDemo() {
        //
        model.reset(nullptr);
        interpreter.reset(nullptr);
        if (asset) {
            AAsset_close(asset);
        }
    }
    //

    std::unique_ptr<tflite::Interpreter> interpreter = nullptr;
    std::unique_ptr<tflite::FlatBufferModel> model = nullptr;
    AAsset *asset = nullptr;
    TfLiteTensor *input_tensor = nullptr;

    bool test(AAssetManager *asset_manager, const char *model_file_path, std::string &output) {
        output.append("AAssetManager_open:");
        output.append(model_file_path);
        output.append(".\n");

        asset = AAssetManager_open(asset_manager, model_file_path, AASSET_MODE_BUFFER);
        //
        if (asset == nullptr) {
            LOGE("invalid argument, model file open failed. \"%s\"\n", model_file_path);
            return false;
        }
        auto modelLength = static_cast<size_t >(AAsset_getLength(asset));
        auto modelBuffer = (const char *) AAsset_getBuffer(asset);

        //
        if (model == nullptr)
            model = tflite::FlatBufferModel::VerifyAndBuildFromBuffer(modelBuffer, modelLength);

        if (interpreter == nullptr) {
            auto resolver = std::unique_ptr<tflite::ops::builtin::BuiltinOpResolver>(
                new tflite::ops::builtin::BuiltinOpResolver());
            LOGD("InterpreterBuilder");
            TfLiteStatus status = tflite::InterpreterBuilder(*model, *(resolver.get()))(
                &interpreter, 1);
            if (status != kTfLiteOk) {
                LOGE("%s Failed to create interpreter!", __FUNCTION__);
                return false;
            }
        }
        LOGD("AllocateTensors:%p", interpreter.get());
        if (interpreter->AllocateTensors() != kTfLiteOk) {
            LOGD("%s Failed to allocate tensors!", __FUNCTION__);
            return false;
        }
        //interpreter->SetNumThreads(1);
        std::stringstream sstream;
        input_tensor = interpreter->tensor(interpreter->inputs()[0]);
        // input_tensor->t
        sstream << "tensors_size:" << interpreter->tensors_size() << "\n";
        sstream << "nodes_size:" << interpreter->nodes_size() << "\n";

        int input_width = input_tensor->dims->data[2];
        int input_height = input_tensor->dims->data[1];
        int input_channels = input_tensor->dims->data[3];
        sstream << "intput:" << "\n";
        sstream << "dims[1]\t:" << input_height << "\n";
        sstream << "dims[2]\t:" << input_width << "\n";
        sstream << "dims[3]\t:" << input_channels << "\n";
        output.append(sstream.str());
        LOGI("%d %d %d", input_width, input_height, input_channels);
        return true;
    }
};

extern "C" JNIEXPORT jstring JNICALL
Java_com_fz_tflite_MainActivity_stringFromJNI(
    JNIEnv *env,
    jobject _thisjobj,
    jobject assetManager,
    jstring modelPath,
    jstring labelPath) {
    std::string hello; // = "Hello from C++";
    TfliteDemo t;
    //
    AAssetManager *casset = AAssetManager_fromJava(env, assetManager);
    char *_modelPath = (char *) env->GetStringUTFChars(modelPath, 0);
    char *_labelPath = (char *) env->GetStringUTFChars(labelPath, 0);
    t.test(casset, _modelPath, hello);
    return env->NewStringUTF(hello.c_str());
}

// TfLiteTensor *input_tensor = nullptr;