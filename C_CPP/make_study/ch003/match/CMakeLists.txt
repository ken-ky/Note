cmake_minimum_required(VERSION 3.20)
project(MatchOrder)
set(a cache_var CACHE STRING "")
set(a normal_var)

message("\${a}: ${a}")
message("\$CACHE{a}: $CACHE{a}")