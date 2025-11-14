string(
    JSON res EQUAL 
    [[{"b": 0, "a": 1}]]
    [[{"a": 1, "b": 0}]]
)
message(${res})

string(
    JSON res EQUAL
    [[{"b": null, "a": 1}]]
    [[{"a": 1}]]
)
message(${res})