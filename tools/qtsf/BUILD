licenses(["notice"])  # Apache 2

load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_binary",
    "envoy_cc_platform_dep",
    "envoy_package",
)

envoy_package()

envoy_cc_binary(
    name = "HelloQtsf",
    srcs = ["HelloQtsf.cc"],
    deps = [
        "//source/common/buffer:buffer_lib",
    ],
)
