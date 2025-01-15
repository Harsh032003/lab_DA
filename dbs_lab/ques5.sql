 declare 
    v_a number:=3; 
    begin 
    declare 
    v_b number:=4; 
    begin 
    dbms_output.put_line(v_b); 
     dbms_output.put_line(v_a); 
    end; 
    dbms_output.put_line(v_a); 
   end; 
 / 