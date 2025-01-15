DECLARE
    CURSOR min_salary_cursor IS
        SELECT FIRST_NAME, LAST_NAME, SALARY
        FROM Employee
        WHERE SALARY > 1000;
BEGIN
    FOR emp IN min_salary_cursor LOOP
        DBMS_OUTPUT.PUT_LINE('Employee: ' || emp.FIRST_NAME || ' ' || emp.LAST_NAME || ' has a salary of $' || emp.SALARY);
    END LOOP;
END;
/
