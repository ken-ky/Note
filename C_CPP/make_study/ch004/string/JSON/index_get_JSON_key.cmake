set(json [=[{
    "a": {
        "b": {
            "b0": true,
            "b1": "str"
        },
        "c": {}
    },
    "d": {}
}]=])

string(JSON res MEMBER ${json} 0)
message(${res})

string(JSON res MEMBER ${json} 1)
message(${res})

string(JSON res MEMBER ${json} a 0)
message(${res})

string(JSON res MEMBER ${json} a 1)
message(${res})

string(JSON res ERROR_VARIABLE err MEMBER ${json} a b 0)
if(${err})
    message("err: ${err}")
else()
    message("key: ${res}")
endif()
