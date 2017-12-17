cmake_minimum_required(VERSION 3.9)
project(dz3)

set(CMAKE_CXX_STANDARD 11)

add_executable(dz3 main.cpp FSObject.cpp FSObject.h FSVisitor.cpp FSVisitor.h File.cpp File.h Folder.cpp Folder.h SearchVisitor.cpp SearchVisitor.h FSOperation.cpp FSOperation.h FSException.cpp FSException.h AccessException.cpp AccessException.h OperationFailedException.cpp OperationFailedException.h NameCollisionException.cpp NameCollisionException.h WriteFailedException.cpp WriteFailedException.h Filesystem.cpp Filesystem.h AccessDescriptor.cpp AccessDescriptor.h)