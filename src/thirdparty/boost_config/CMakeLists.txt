include(FetchContent)

FetchContent_Declare(
    boost_config
    GIT_REPOSITORY https://github.com/boostorg/config.git
    GIT_TAG boost-1.71.0
)

FetchContent_MakeAvailable(boost_config)