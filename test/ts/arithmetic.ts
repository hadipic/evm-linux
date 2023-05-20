var result = 0;

result = 1 - 2;
assert(result == -1);
print(result)

result = 1 + 2;
assert(result == 3);
print(result)

result = 2 * 2;
assert(result == 4);
print(result)

result = 2 / 2;
assert(result == 1);
print(result)


result = 1 % 2;
assert(result == 1);
print(result);


result = 0;
result += 1;
assert(result == 1);
print(result);


result -= 1;
assert(result == 0);
print(result)

result = 2;
result *= 2;
assert(result == 4);
print(result)

result /= 2;
assert(result == 2);
print(result)

result %= 2;
assert(result == 0);
print(result)