declare 
   v_name varchar2(10); 
   v_regno number; 
   begin 
  v_name:='venkat'; 
   v_regno:=39; 
  dbms_output.put_line( 'the name is' || v_name); 
  dbms_output.put_line('the no is' || v_regno); 
end; 