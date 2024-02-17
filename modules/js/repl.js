/*
 * This file is part of the EVM project.
 * QQ Group: 399011436
 * Git: https://gitee.com/scriptiot/evm
 *
 * MIT License
 *
 * Copyright (c) 2023 Zhe Wang
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
var BELL =   "\007";
var CRLF =   "\r\n";
var RIGHT=   "\033[C";
var LEFT =   "\010";
var buf = "";
console.log("Github: https://gitee.com/scriptiot/evm")
console.log("Copyright (C) 2023")
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
