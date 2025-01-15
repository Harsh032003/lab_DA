 declare 
   vdate date; 
    begin 
    vdate:=to_date('aug 19 ,2005','mon dd,yyyy'); 
    dbms_output.put_line(vdate); 
   end; 
 / 