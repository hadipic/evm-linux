var result = 0;

result = 1 & 2;
assert(result == 0);
print(result)

result = 1 | 2;
assert(result == 3);
print(result)

result = 2 ^ 2;
assert(result == 0);
print(result)

result = 2 << 2;
assert(result == 8);
print(result)

result = 8 >> 2;
assert(result == 2);
print(result)

result = 1;
result &= 2;
assert(result == 0);
print(result)

result |= 2;
assert(result == 2);
print(result)

result ^= 4;
assert(result == 6);
print(result);

result <<= 2;
assert(result == 24);
print(result);

result >>= 2;
assert(result == 6);
print(result)
