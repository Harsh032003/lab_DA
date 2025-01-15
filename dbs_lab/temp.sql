create or replace function fact(n in number)
return number
is
v_fact number:=1;
begin

if n < 0 then
return -1;

elsif n=0 then return 1;
end if;

for i in 1..n loop
v_fact := v_fact * i;
end loop;

return v_fact;

end fact;
/

declare 

a number := 4;
answer number;

begin

answer := fact(a);

dbms_output.put_line('fact of 4 : '|| answer);

end;
/


