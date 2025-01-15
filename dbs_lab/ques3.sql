 declare 
    v_name varchar2(10); 
    V_count binary_integer:=10; 
    V_totalsal number(9,2); 
    v_orderdate date:=sysdate; 
    c_tax constant number(3,2):=6.23; 
    v_valid boolean not null:=true; 
    v_regno number default 23; 
    begin 
   v_name:='venkat'; 
   v_totalsal:=10000.23; 
   dbms_output.put_line(v_name); 
   dbms_output.put_line(v_count); 
   dbms_output.put_line(v_orderdate); 
   dbms_output.put_line(c_tax); 
   dbms_output.put_line(v_regno); 
  end; 
  / 