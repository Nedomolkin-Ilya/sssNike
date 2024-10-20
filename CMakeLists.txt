cmake_minimum_required(VERSION 2.8)
project(sssNike)


# Исходник
set(SOURCES 
	src/main.c
)

# Исполняемый файл
add_executable(sssnike ${SOURCES})

# Openssl
find_package(OpenSSL REQUIRED)
target_link_libraries(sssnike OpenSSL::Crypto)
