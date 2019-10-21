include(FetchContent)

FetchContent_Declare(
    boost_type_traits
    GIT_REPOSITORY https://github.com/boostorg/type_traits.git
    GIT_TAG boost-1.71.0
)

FetchContent_MakeAvailable(boost_type_traits)