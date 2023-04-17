var BELL =   "\007";
var CRLF =   "\r\n";
var RIGHT=   "\033[C";
var LEFT =   "\010";
var buf = "";
console.write(">>>");

function repl_input_enter() {
    console.log('');
    try{
        console.log(eval(buf));
    } catch(e) {
        console.log(e);
    }    
    buf = '';
    console.write(">>>");
}

function repl_input_delete() {
    if( buf.length == 0 )
        return;
    console.write(LEFT);
    console.write(" ");
    console.write(LEFT);
    buf = buf.slice(0, buf.length - 1)
}

function repl_input_char(ch) {
    ch = String.fromCodePoint(ch);
    console.write(ch);
    buf += ch;
}

while(true) {
    ch = console.getc();
    if( ch == 127 ){
        repl_input_delete();
    } if( ch == 10 || ch == 13) {
        if( buf == 'quit' ){
            console.log('')
            console.log('quit repl')
            break;
        }
        
        repl_input_enter();
    }
    else if(ch > 0){
        repl_input_char(ch);
    }
}
