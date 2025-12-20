function assert(){

}

var result = addFloat(2, 3);
assert(result == 5);
print(result);

//test class
class Person {
	constructor() {
		this.name = 'EVM';
		this.age = 10;
	}
	add(a, b) {
		return a + b;
	}
}

var person = new Person();
print(person.name);

var result = 0;

//arithmetics
result = 1 - 2;
print(result)
assert(result == -1);


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
function addInt(a, b){
	return a + b;
}

function addFloat(a, b) {
	print(a)
	return a + b;
}

function add(a, b) {
	print(this);
	return a + b;

}

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

dict.add = add;
result = dict.add(1, 2);
assert(result == 3);
print(result);


//new function
function Foo() {
	this.a = 10;
	this.b = 20;
}

var obj = new Foo();
print(obj.a)

var a = 100;
print(++a);
assert(a == 101);
print(--a);
assert(a == 100);

print(a++);
assert(a == 101);
print(a--);
assert(a == 100);


var obj = {
	count: 1
}

print(++obj.count)
assert(obj.count == 2)
print(--obj.count)
assert(obj.count == 1)

print(obj.count++)
assert(obj.count == 2)
print(obj.count--)
assert(obj.count == 1)

var arr = [1, 2];
print(arr[0]);

print(++arr[0])
assert(arr[0] == 2)
print(--arr[0])
assert(arr[0] == 1)

print(arr[0]++)
assert(arr[0] == 2)
print(arr[0]--)
assert(arr[0] == 1)

var bbb = 101
print(obj.count)
Object.defineProperty(obj, 'count', {
	get: function() {
		return bbb;
	}
});
print(obj.count)

//for in
print(obj)
for(var a in obj) {
	print(a)
}

print(arr)
for(var a in arr) {
	print(a)
}

//native test
print("----------native test-----------")
var a = parseInt("10");
print(a);
assert(a == 10);

a = parseFloat("10.33")
print(a);
assert(a == 10.33);

var uri="my test.php?name=ståle&car=saab";
a = encodeURI(uri)
print(a);

a = decodeURI(uri)
print(a);

var uri="https://www.runoob.com/my test.php?name=ståle&car=saab";
a=encodeURIComponent(uri);
print(a)
a = decodeURIComponent(a);
print(a);

print(Math.sin(Math.PI/6))
