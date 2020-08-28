







# root build of tensorflow for export includes
genrule(
    name = "install_lite_headers",
    srcs = [
        "//tensorflow/lite:core/macros.h",
        "//tensorflow/lite:core/subgraph.h",
        "//tensorflow/lite/core/api:profiler.h",
        "//tensorflow/lite/core/api:error_reporter.h",
        "//tensorflow/lite/core/api:flatbuffer_conversions.h",
        "//tensorflow/lite/core/api:op_resolver.h",
        "//tensorflow/lite/core/api:tensor_utils.h",
        #
        "//tensorflow/lite/kernels:register.h",

        "//tensorflow/lite/c:c_api.h",
        "//tensorflow/lite/c:c_api_internal.h",
        "//tensorflow/lite/c:common.h",
        "//tensorflow/lite/c:builtin_op_data.h",
        "//tensorflow/lite/c:c_api_experimental.h",
        # 
        "//tensorflow/lite:allocation.h",
        "//tensorflow/lite:arena_planner.h",
        "//tensorflow/lite:builtin_ops.h",
        "//tensorflow/lite:context.h",
        "//tensorflow/lite:context_util.h",
        "//tensorflow/lite:error_reporter.h",
        "//tensorflow/lite:external_cpu_backend_context.h",
        "//tensorflow/lite:graph_info.h",
        "//tensorflow/lite:interpreter.h",
        "//tensorflow/lite:interpreter_builder.h",
        "//tensorflow/lite:memory_planner.h",
        "//tensorflow/lite:minimal_logging.h",
        "//tensorflow/lite:model.h",
        "//tensorflow/lite:model_builder.h",
        "//tensorflow/lite:mutable_op_resolver.h",
        "//tensorflow/lite:op_resolver.h",
        "//tensorflow/lite:optional_debug_tools.h",
        "//tensorflow/lite:simple_memory_arena.h",
        "//tensorflow/lite:stderr_reporter.h",
        "//tensorflow/lite:string_type.h",
        "//tensorflow/lite:string_util.h",
        "//tensorflow/lite:tflite_with_xnnpack_optional.h",
        "//tensorflow/lite:type_to_tflitetype.h",
        "//tensorflow/lite:version.h",
        "//tensorflow/lite:util.h",
        #
        # "//tensorflow/lite/core/api:error_reporter.h",
        # "//tensorflow/lite/core/api:flatbuffer_conversions.h",
        # "//tensorflow/lite/core/api:op_resolver.h",
        # "//tensorflow/lite/core/api:tensor_utils.h",
        #"//tensorflow/lite/core:macros.h",
        #"//tensorflow/lite/core:subgraph.h",
        # "//tensorflow/lite:core/subgraph.h",
        # 
        "//tensorflow/lite/delegates/nnapi:nnapi_delegate.h",
        "//tensorflow/lite/delegates:utils.h",
        "//tensorflow/lite/delegates:status.h",
        "//tensorflow/lite/delegates:interpreter_utils.h",
        "//tensorflow/lite/experimental/resource:resource_base.h",
        # 
        "//tensorflow/lite/nnapi:nnapi_util.h",
        "//tensorflow/lite/nnapi:nnapi_implementation.h",
        "//tensorflow/lite/nnapi:nnapi_handler.h",
        "//tensorflow/lite/nnapi:NeuralNetworksTypes.h",
        "//tensorflow/lite/nnapi:NeuralNetworksShim.h",
        # 
        "//tensorflow/lite/schema:schema_generated.h",
        "//tensorflow/core/public:version.h"
        #
        # "//third_party/flatbuffers:public_headers"
    ],
    outs = ["include_lite"],
    # outs = [""],
    cmd = """
    mkdir $@
    for f in $(SRCS); do
      d="$${f%/*}"
      d="$${d#bazel-out/*/genfiles/}"
      d="$${d#bazel-out/*/bin/}"

      if [[ $${d} == *local_config_* ]]; then
        continue
      fi

      if [[ $${d} == external* ]]; then
        extname="$${d#*external/}"
        extname="$${extname%%/*}"
        if [[ $${TF_SYSTEM_LIBS:-} == *$${extname}* ]]; then
          continue
        fi

        d="$${d#*external/farmhash_archive/src}"
        d="$${d#*external/$${extname}/}"
      fi

      mkdir -p "$@/$${d}"
      cp "$${f}" "$@/$${d}/"
    done
    """,
    tags = ["manual"],
    visibility = ["//visibility:public"],
)