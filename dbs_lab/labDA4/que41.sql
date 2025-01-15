DECLARE
    
    CURSOR emp_cursor IS
        SELECT FIRST_NAME, MID_NAME, LAST_NAME, SSN_NUMBER, BIRTHDAY, ADDRESS, SEX, SALARY, SUPERVISOR_SSN, DEPARTMENT_NUMBER
        FROM Employee;

    v_first_name Employee.FIRST_NAME%TYPE;
    v_mid_name Employee.MID_NAME%TYPE;
    v_last_name Employee.LAST_NAME%TYPE;
    v_ssn Employee.SSN_NUMBER%TYPE;
    v_birthday Employee.BIRTHDAY%TYPE;
    v_address Employee.ADDRESS%TYPE;
    v_sex Employee.SEX%TYPE;
    v_salary Employee.SALARY%TYPE;
    v_supervisor_ssn Employee.SUPERVISOR_SSN%TYPE;
    v_dept_number Employee.DEPARTMENT_NUMBER%TYPE;
BEGIN
    
    OPEN emp_cursor;
    LOOP
        FETCH emp_cursor INTO v_first_name, v_mid_name, v_last_name, v_ssn, v_birthday, v_address, v_sex, v_salary, v_supervisor_ssn, v_dept_number;
        
        EXIT WHEN emp_cursor%NOTFOUND;

        DBMS_OUTPUT.PUT_LINE('Employee: ' || v_first_name || ' ' || NVL(v_mid_name, '') || ' ' || v_last_name);
        DBMS_OUTPUT.PUT_LINE('SSN: ' || v_ssn);
        DBMS_OUTPUT.PUT_LINE('Birthday: ' || TO_CHAR(v_birthday, 'DD-MON-YYYY'));
        DBMS_OUTPUT.PUT_LINE('Address: ' || v_address);
        DBMS_OUTPUT.PUT_LINE('Sex: ' || v_sex);
        DBMS_OUTPUT.PUT_LINE('Salary: $' || v_salary);
        DBMS_OUTPUT.PUT_LINE('Supervisor SSN: ' || v_supervisor_ssn);
        DBMS_OUTPUT.PUT_LINE('Department Number: ' || v_dept_number);
        DBMS_OUTPUT.PUT_LINE('-----------------------------------------');
    END LOOP;

    CLOSE emp_cursor;
END;
/
