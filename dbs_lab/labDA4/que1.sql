-- DECLARE
--     v_ssn CHAR(9);
--     v_salary NUMBER(7);
-- BEGIN
    
--     v_ssn := '&emp_ssn';
    
--     SELECT SALARY INTO v_salary 
--     FROM Employee 
--     WHERE SSN_NUMBER = v_ssn;

--     DBMS_OUTPUT.PUT_LINE('Salary of employee with SSN ' || v_ssn || ' is: ' || v_salary);
-- EXCEPTION
--     WHEN NO_DATA_FOUND THEN
--         DBMS_OUTPUT.PUT_LINE('No employee found with SSN ' || v_ssn);
-- END;
-- /

DECLARE
    v_ssn char(9);
    v_salary number(7);

BEGIN
    v_ssn := '&emp_ssn';
    SELECT salary into v_salary
    from Employee
    where SSN_NUMBER = v_ssn;
    dbms_output.put_line('salary of employee with ssn' || v_ssn || ' is: ' || v_salary);
    
    EXCEPTION
        when NO_DATA_FOUND THEN
            dbms_output.put_line('No employee found with SSN ' || v_ssn);

END;
/

