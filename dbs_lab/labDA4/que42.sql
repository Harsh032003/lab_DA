DECLARE
    CURSOR emp_dept_cursor IS
        SELECT e.FIRST_NAME, e.MID_NAME, e.LAST_NAME, e.SSN_NUMBER, e.BIRTHDAY, e.ADDRESS, e.SEX, e.SALARY, e.SUPERVISOR_SSN, e.DEPARTMENT_NUMBER,
               d.DEPARTMENT_NAME, d.MANAGER_SSN, d.MANAGER_START_DATE
        FROM Employee e
        JOIN Department d ON e.DEPARTMENT_NUMBER = d.DEPARTMENT_NUMBER;

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
    v_dept_name Department.DEPARTMENT_NAME%TYPE;
    v_manager_ssn Department.MANAGER_SSN%TYPE;
    v_manager_start_date Department.MANAGER_START_DATE%TYPE;
BEGIN

    OPEN emp_dept_cursor;
    LOOP
        FETCH emp_dept_cursor INTO v_first_name, v_mid_name, v_last_name, v_ssn, v_birthday, v_address, v_sex, v_salary, v_supervisor_ssn, v_dept_number, v_dept_name, v_manager_ssn, v_manager_start_date;

        EXIT WHEN emp_dept_cursor%NOTFOUND;

        DBMS_OUTPUT.PUT_LINE('Employee: ' || v_first_name || ' ' || NVL(v_mid_name, '') || ' ' || v_last_name);
        DBMS_OUTPUT.PUT_LINE('SSN: ' || v_ssn);
        DBMS_OUTPUT.PUT_LINE('Birthday: ' || TO_CHAR(v_birthday, 'DD-MON-YYYY'));
        DBMS_OUTPUT.PUT_LINE('Address: ' || v_address);
        DBMS_OUTPUT.PUT_LINE('Sex: ' || v_sex);
        DBMS_OUTPUT.PUT_LINE('Salary: $' || v_salary);
        DBMS_OUTPUT.PUT_LINE('Supervisor SSN: ' || v_supervisor_ssn);
        DBMS_OUTPUT.PUT_LINE('Department Number: ' || v_dept_number);
        DBMS_OUTPUT.PUT_LINE('Department Name: ' || v_dept_name);
        DBMS_OUTPUT.PUT_LINE('Manager SSN: ' || v_manager_ssn);
        DBMS_OUTPUT.PUT_LINE('Manager Start Date: ' || TO_CHAR(v_manager_start_date, 'DD-MON-YYYY'));
        DBMS_OUTPUT.PUT_LINE('-----------------------------------------');
    END LOOP;

    CLOSE emp_dept_cursor;
END;
/
