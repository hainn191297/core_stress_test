#!/bin/bash
# script to build protobuffer

protoc -I=api/ --cpp_out=src/protobuf/ api/*.proto
protoc -I=api/ -I=model/ --cpp_out=src/protobuf/ model/*.proto
