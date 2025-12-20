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
print(person.age);