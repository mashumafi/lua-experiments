include(FetchContent)

FetchContent_Declare(
    boost_static_assert
    GIT_REPOSITORY https://github.com/boostorg/static_assert.git
    GIT_TAG boost-1.71.0
)

FetchContent_MakeAvailable(boost_static_assert)