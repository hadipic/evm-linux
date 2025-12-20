var result = 0;
for(result = 0; result < 3; result = result + 1) {
	print(result);
}
assert(result == 3);

result = 3;
while(result) {
	print(result);
	result = result - 1;
}
assert(result == 0);

for(result = 0; result < 3; result = result + 1) {
    if( result == 1 )
        break;
}
print(result);
assert(result == 1);

for(result = 0; result < 3; result = result + 1) {
    if( result == 0 )
        continue;
    else
        break;
}
print(result);
assert(result == 1);