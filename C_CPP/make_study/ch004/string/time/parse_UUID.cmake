set(namespace d5c54b4a-2500-47f2-87a3-c35a5ca5abb6)

string(UUID res NAMESPACE ${namespace} NAME a TYPE MD5)
message(${res})

string(UUID res NAMESPACE ${namespace} NAME b TYPE SHA1 UPPER)
message(${res})