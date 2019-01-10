load(
    ":build_defs.bzl",
    "generated_file_staleness_test",
    "lua_binary",
    "lua_cclibrary",
    "lua_library",
    "lua_test",
    "make_shell_script",
    "upb_amalgamation",
    "upb_proto_library",
    "upb_proto_reflection_library",
)

# Remove once our C++ wrappers are more sane.
CXX_COPTS = ["-Wno-unused-private-field"]

# C/C++ rules ##################################################################

cc_library(
    name = "upb",
    srcs = [
        "google/protobuf/descriptor.upb.c",
        "upb/decode.c",
        "upb/def.c",
        "upb/encode.c",
        "upb/handlers.c",
        "upb/handlers-inl.h",
        "upb/msg.c",
        "upb/msgfactory.c",
        "upb/port_def.inc",
        "upb/port_undef.inc",
        "upb/sink.c",
        "upb/structs.int.h",
        "upb/table.c",
        "upb/table.int.h",
        "upb/upb.c",
    ],
    hdrs = [
        "google/protobuf/descriptor.upb.h",
        "upb/decode.h",
        "upb/def.h",
        "upb/encode.h",
        "upb/generated_util.h",
        "upb/handlers.h",
        "upb/msg.h",
        "upb/msgfactory.h",
        "upb/sink.h",
        "upb/upb.h",
    ],
    copts = [
        "-std=c89",
        "-pedantic",
        "-Wno-long-long",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "upb_pb",
    srcs = [
        "upb/pb/compile_decoder.c",
        "upb/pb/decoder.c",
        "upb/pb/decoder.int.h",
        "upb/pb/encoder.c",
        "upb/pb/textprinter.c",
        "upb/pb/varint.c",
        "upb/pb/varint.int.h",
    ],
    hdrs = [
        "upb/pb/decoder.h",
        "upb/pb/encoder.h",
        "upb/pb/textprinter.h",
    ],
    copts = [
        "-std=c89",
        "-pedantic",
        "-Wno-long-long",
    ],
    deps = [
        ":upb",
    ],
)

cc_library(
    name = "upb_json",
    srcs = [
        "upb/json/parser.c",
        "upb/json/printer.c",
    ],
    hdrs = [
        "upb/json/parser.h",
        "upb/json/printer.h",
    ],
    copts = [
        "-std=c89",
        "-pedantic",
        "-Wno-long-long",
    ],
    deps = [
        ":upb",
        ":upb_pb",
    ],
)

cc_library(
    name = "upb_cc_bindings",
    hdrs = [
        "upb/bindings/stdc++/string.h",
    ],
    deps = [":upb"],
)

# Amalgamation #################################################################

py_binary(
    name = "amalgamate",
    srcs = ["tools/amalgamate.py"],
)

upb_amalgamation(
    name = "gen_amalgamation",
    outs = [
        "upb.c",
        "upb.h",
    ],
    amalgamator = ":amalgamate",
    libs = [
        ":upb",
        ":upb_pb",
        ":upb_json",
    ],
)

cc_library(
    name = "amalgamation",
    srcs = ["upb.c"],
    hdrs = ["upb.h"],
)

# C/C++ tests ##################################################################

cc_library(
    name = "upb_test",
    testonly = 1,
    srcs = [
        "tests/testmain.cc",
    ],
    hdrs = [
        "tests/test_util.h",
        "tests/upb_test.h",
    ],
)

cc_test(
    name = "test_varint",
    srcs = ["tests/pb/test_varint.c"],
    deps = [
        ":upb_pb",
        ":upb_test",
    ],
)

upb_proto_reflection_library(
    name = "descriptor_upbproto",
    upbc = ":protoc-gen-upb",
    deps = ["descriptor_proto"],
)

cc_test(
    name = "test_handlers",
    srcs = ["tests/test_handlers.c"],
    deps = [
        ":descriptor_upbproto",
        ":upb_pb",
        ":upb_test",
    ],
)

proto_library(
    name = "test_decoder_proto",
    srcs = [
        "tests/pb/test_decoder.proto",
    ],
)

upb_proto_reflection_library(
    name = "test_decoder_upbproto",
    upbc = ":protoc-gen-upb",
    deps = ["test_decoder_proto"],
)

cc_test(
    name = "test_decoder",
    srcs = ["tests/pb/test_decoder.cc"],
    deps = [
        ":test_decoder_upbproto",
        ":upb_pb",
        ":upb_test",
    ],
)

cc_test(
    name = "test_encoder",
    srcs = ["tests/pb/test_encoder.cc"],
    copts = CXX_COPTS,
    data = ["google/protobuf/descriptor.pb"],
    deps = [
        ":upb_cc_bindings",
        ":upb_pb",
        ":upb_test",
    ],
)

proto_library(
    name = "test_cpp_proto",
    srcs = [
        "tests/test_cpp.proto",
    ],
)

upb_proto_reflection_library(
    name = "test_cpp_upbproto",
    upbc = ":protoc-gen-upb",
    deps = ["test_cpp_proto"],
)

cc_test(
    name = "test_cpp",
    srcs = ["tests/test_cpp.cc"],
    copts = CXX_COPTS,
    deps = [
        ":test_cpp_upbproto",
        ":upb",
        ":upb_pb",
        ":upb_test",
    ],
)

cc_test(
    name = "test_table",
    srcs = ["tests/test_table.cc"],
    deps = [
        ":upb",
        ":upb_test",
    ],
)

proto_library(
    name = "test_json_proto",
    srcs = ["tests/json/test.proto"],
)

upb_proto_reflection_library(
    name = "test_json_upbproto",
    upbc = ":protoc-gen-upb",
    deps = ["test_json_proto"],
)

cc_test(
    name = "test_json",
    srcs = [
        "tests/json/test_json.cc",
    ],
    copts = CXX_COPTS,
    deps = [
        ":test_json_upbproto",
        ":upb_json",
        ":upb_test",
    ],
)

upb_proto_library(
    name = "conformance_proto_upb",
    upbc = ":protoc-gen-upb",
    deps = [
        "@com_google_protobuf//:conformance_proto",
        "@com_google_protobuf//:test_messages_proto3_proto",
    ],
)

cc_binary(
    name = "conformance_upb",
    srcs = [
        "tests/conformance_upb.c",
    ],
    copts = ["-Ibazel-out/k8-fastbuild/bin"],
    deps = [
        ":conformance_proto_upb",
        ":upb",
    ],
)

make_shell_script(
    name = "gen_test_conformance_upb",
    out = "test_conformance_upb.sh",
    contents = "$(rlocation com_google_protobuf/conformance_test_runner) $(rlocation upb/conformance_upb)",
)

sh_test(
    name = "test_conformance_upb",
    srcs = ["test_conformance_upb.sh"],
    data = [
        "tests/conformance_upb_failures.txt",
        ":conformance_upb",
        "@bazel_tools//tools/bash/runfiles",
        "@com_google_protobuf//:conformance_test_runner",
    ],
)

# Lua libraries. ###############################################################

lua_cclibrary(
    name = "lua/upb_c",
    srcs = [
        "upb/bindings/lua/def.c",
        "upb/bindings/lua/msg.c",
        "upb/bindings/lua/upb.c",
    ],
    hdrs = [
        "upb/bindings/lua/upb.h",
    ],
    deps = [
        "upb",
        "upb_pb",
    ],
)

lua_library(
    name = "lua/upb",
    srcs = ["upb/bindings/lua/upb.lua"],
    luadeps = ["lua/upb_c"],
    strip_prefix = "upb/bindings/lua",
)

lua_cclibrary(
    name = "lua/upb/pb_c",
    srcs = ["upb/bindings/lua/upb/pb.c"],
    luadeps = ["lua/upb_c"],
    deps = ["upb_pb"],
)

lua_library(
    name = "lua/upb/pb",
    srcs = ["upb/bindings/lua/upb/pb.lua"],
    luadeps = [
        "lua/upb",
        "lua/upb/pb_c",
    ],
    strip_prefix = "upb/bindings/lua",
)

# Lua tests. ###################################################################

lua_test(
    name = "lua/test_upb",
    luadeps = ["lua/upb"],
    luamain = "tests/bindings/lua/test_upb.lua",
)

lua_test(
    name = "lua/test_upb_pb",
    luadeps = ["lua/upb/pb"],
    luamain = "tests/bindings/lua/test_upb.pb.lua",
)

# upb compiler #################################################################

cc_library(
    name = "upbc_generator",
    srcs = [
        "upbc/generator.cc",
        "upbc/message_layout.cc",
        "upbc/message_layout.h",
    ],
    hdrs = ["upbc/generator.h"],
    deps = [
        "@absl//absl/strings",
        "@com_google_protobuf//:protobuf",
        "@com_google_protobuf//:protoc_lib",
    ],
)

cc_binary(
    name = "protoc-gen-upb",
    srcs = ["upbc/main.cc"],
    deps = [
        ":upbc_generator",
        "@com_google_protobuf//:protoc_lib",
    ],
)

# Test the CMake build #########################################################

make_shell_script(
    name = "gen_run_cmake_build",
    out = "run_cmake_build.sh",
    contents = "mkdir build && cd build && cmake .. && make -j8 && make test",
)

sh_test(
    name = "cmake_build",
    srcs = ["run_cmake_build.sh"],
    data = glob([
        "CMakeLists.txt",
        "google/**/*",
        "upbc/**/*",
        "upb/**/*",
        "tests/**/*",
    ]) + [
        "@bazel_tools//tools/bash/runfiles",
    ],
)

# Generated files ##############################################################

exports_files(["tools/staleness_test.py"])

py_library(
    name = "staleness_test_lib",
    testonly = 1,
    srcs = ["tools/staleness_test_lib.py"],
)

genrule(
    name = "make_dynasm_decoder",
    srcs = [
        "third_party/dynasm/dynasm.lua",
        "third_party/dynasm/dasm_x64.lua",
        "third_party/dynasm/dasm_x86.lua",
        "upb/pb/compile_decoder_x64.dasc",
    ],
    outs = ["generated/upb/pb/compile_decoder_x64.h"],
    cmd = "LUA_PATH=third_party/dynasm/?.lua $(location @lua//:lua) third_party/dynasm/dynasm.lua -c upb/pb/compile_decoder_x64.dasc > $@",
    tools = ["@lua"],
)

py_binary(
    name = "make_cmakelists",
    srcs = ["tools/make_cmakelists.py"],
)

proto_library(
    name = "descriptor_proto",
    srcs = [
        "google/protobuf/descriptor.proto",
    ],
)

genrule(
    name = "copy_upb_descriptor_pb",
    srcs = [":descriptor_proto"],
    outs = ["generated/google/protobuf/descriptor.pb"],
    cmd = "cp $< $@",
)

genrule(
    name = "gen_cmakelists",
    srcs = [
        "BUILD",
        "WORKSPACE",
    ],
    outs = ["generated/CMakeLists.txt"],
    cmd = "$(location :make_cmakelists) $@",
    tools = [":make_cmakelists"],
)

proto_library(
    name = "google_descriptor_proto",
    srcs = [
        "google/protobuf/descriptor.proto",
    ],
)

genrule(
    name = "generate_descriptor_c",
    srcs = ["google/protobuf/descriptor.proto"],
    outs = [
        "generated/google/protobuf/descriptor.upb.h",
        "generated/google/protobuf/descriptor.upb.c",
    ],
    cmd = "$(location @com_google_protobuf//:protoc) $< --upb_out=$(GENDIR)/generated --plugin=protoc-gen-upb=$(location :protoc-gen-upb)",
    tools = [
        ":protoc-gen-upb",
        "@com_google_protobuf//:protoc",
    ],
)

proto_library(
    name = "json_test_proto",
    srcs = ["tests/json/test.proto"],
)

genrule(
    name = "copy_json_test_proto",
    srcs = [":json_test_proto"],
    outs = ["generated/tests/json/test.proto.pb"],
    cmd = "cp $< $@",
)

genrule(
    name = "generate_json_ragel",
    srcs = ["upb/json/parser.rl"],
    outs = ["generated/upb/json/parser.c"],
    cmd = "$(location @ragel//:ragel) -C -o upb/json/parser.c $< && mv upb/json/parser.c $@",
    tools = ["@ragel"],
)

generated_file_staleness_test(
    name = "test_generated_files",
    outs = [
        "CMakeLists.txt",
        "google/protobuf/descriptor.pb",
        "google/protobuf/descriptor.upb.c",
        "google/protobuf/descriptor.upb.h",
        "tests/json/test.proto.pb",
        "upb/json/parser.c",
        "upb/pb/compile_decoder_x64.h",
    ],
    generated_pattern = "generated/%s",
)
