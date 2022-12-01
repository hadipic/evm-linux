var id;
function timer() {
    print('hello');
    clearInterval(id)
}

id = setInterval(timer, 1000);