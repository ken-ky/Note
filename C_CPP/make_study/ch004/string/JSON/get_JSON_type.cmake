set(json [=[{
    "a": {},
    "b": [],
    "c": 123,
    "d": "123",
    "e": false,
    "f": null
}]=])

string(JSON res TYPE ${json})
message(${res})

foreach(key a b c d e f)
    string(JSON res TYPE ${json} ${key})
    message("${key}: ${res}")
endforeach()