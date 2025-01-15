BEGIN
    DELETE FROM Employee
    WHERE SALARY < 2000;

    DBMS_OUTPUT.PUT_LINE(SQL%ROWCOUNT || ' records deleted for employees with salary less than $2000.');
    
    COMMIT;
END;
/
