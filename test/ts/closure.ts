function test() {
	var a = 10;
	function abc(){
		print(a);
	}
	return abc;
}
var aaa = function() {
	print('test');
}
aaa();
var func = test();
func();