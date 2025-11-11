math(EXPR a 10*10 OUTPUT_FORMAT DECIMAL)
math(EXPR b "0x7FFFFFFFFFFFFFFF + 0x7FFFFFFFFFFFFFFF")
math(EXPR c "16" OUTPUT_FORMAT HEXADECIMAL)
math(EXPR d "~16" OUTPUT_FORMAT HEXADECIMAL)

message("a: ${a}\nb: ${b}\nc: ${c}\nd: ${d}")
# math(EXPR err "0xFFFFFFFFFFFFFFFF") # math cannot evaluate the expression: "0xFFFFFFFFFFFFFFFF": a numeric value is out of range.