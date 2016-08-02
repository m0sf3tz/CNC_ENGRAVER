frequency   = 10
steps       = 4
stop        = 0

val = frequency | (steps <<12) | (stop<<30)

print val

print val>>0    & 0xFF
print val>>8    & 0xFF
print val>>16   & 0xFF
print val>>24   & 0xFF
