program
   : value EOF #json_program
   ;

obj
   : '{' #json_new_object pair (',' pair)* '}' 
   | '{' #json_new_object '}'  
   ;

pair
   : STRING #json_key ':' value #json_add_pair
   ;

arr
   : '[' #json_new_array value #json_add_arr (',' value #json_add_arr)* ']'
   | '[' #json_new_array ']'
   ;

value
   : STRING #json_string_value
   | NUMBER #json_number_value
   | obj 
   | arr 
   | 'true' #json_true_value
   | 'false' #json_false_value
   | 'null' #json_null_value
   ;

