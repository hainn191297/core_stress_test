FROM alpine
RUN apk add --no-cache build-base cmake boost-dev imagemagick-dev protobuf-dev

# dev dependencies
# glog: none
# CppCMS: pcre-dev icu-dev openssl-dev
# uuid: util-linux-dev
# google/dense_hash_map: sparsehash
# libidn-dev


# normal dependencies
# boost imagemagick protobuf
# pcre icu openssl (? need test)