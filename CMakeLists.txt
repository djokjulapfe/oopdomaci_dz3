cmake_minimum_required(VERSION 3.9)
project(dz3)

set(CMAKE_CXX_STANDARD 11)

add_executable(dz3 main.cpp
               FSObject.h
               FSVisitor.h
               File.h
               Folder.h
               SearchVisitor.h
               FSOperation.h
               FSException.h
               AccessException.h
               OperationFailedException.h
               NameCollisionException.h
               WriteFailedException.h
               Filesystem.h
               AccessDescriptor.h
               FSObject.cpp
               File.cpp
               Folder.cpp
               SearchVisitor.cpp
               FSOperation.cpp
               FSException.cpp
               AccessException.cpp
               OperationFailedException.cpp
               NameCollisionException.cpp
               WriteFailedException.cpp
               Filesystem.cpp
               AccessDescriptor.cpp
               FSVisitor.cpp ProtectedOperation.cpp ProtectedOperation.h)