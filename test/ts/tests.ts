//test class
class Person {
	function constructor() {
		this.name = 'EVM';
		this.age = 10;
	}
	function add(a, b) {
		return a + b;
	}
}

var person = new Person();
print(person.name);

var result = 0;

//arithmetics
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
print(result)

//test for loop
for(result = 0; result < 3; result = result + 1) {
	print(result);
}
assert(result == 3);

//test while loop
result = 3;
while(result) {
	print(result);
	result = result - 1;
}
assert(result == 0);

// test function
function addInt(a:int, b:int): int {
	return a + b;
}

function addFloat(a:number, b:number): number {
	return a + b;
}

function add(a, b) {
	print(this);
	return a + b;
}
debug();
var result = addFloat(2, 3);
assert(result == 5);
print(result);

var result = addInt(1, 2);
assert(result == 3);
print(result);

var result = add(1, 2);
assert(result == 3);
print(result);

//test if condition
if( result > 3 ){
	print('result > 3');
} else {
	print('result < 3');
}

//test dict
var dict = {'a': 1, 'b': 2};
print(dict.a);
debug();
dict.add = add;
result = dict.add(1, 2);
assert(result == 3);
print(result);
gc();

