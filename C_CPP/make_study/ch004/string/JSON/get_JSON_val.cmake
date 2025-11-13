set(json [=[{
    "a": {
        "b": ["x","y","z"],
        "c": true,
        "d": null
    }
}]=])

string(JSON res ERROR_VARIABLE err GET ${json} a b)
message("a.b=\t${res}")

string(JSON res ERROR_VARIABLE err GET ${json} a b 1)
message("a.b[1]=\t${res}")

string(JSON res ERROR_VARIABLE err GET ${json} a c)
message("a.c=\t${res}")

string(JSON res ERROR_VARIABLE err GET ${json} a d)
message("a.d=\t${res}")

string(JSON res ERROR_VARIABLE err GET ${json} a e)
message("a.e=\t${res}, ${err}")