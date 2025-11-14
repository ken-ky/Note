set(json [=[{
    "a": {
        "x": 0,
        "y": {}
    },
    "b": [0, 1, 2, 3, 4],
    "c": "cmake"
}]=])

string(JSON res LENGTH ${json})
message("total size:\t${res}")

string(JSON res LENGTH ${json} a)
message("json-a size:\t${res}")

string(JSON res LENGTH ${json} b)
message("json-b size:\t${res}")

string(JSON res ERROR_VARIABLE err LENGTH ${json} c)
if(${err})
    message("json-c err:\t${err}")
else()
    message("json-c size:\t${res}")
endif()