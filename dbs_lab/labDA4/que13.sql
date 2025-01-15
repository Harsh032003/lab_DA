BEGIN
    DELETE FROM Employee
    WHERE (SYSDATE - BIRTHDAY) / 365 > 60;

    DBMS_OUTPUT.PUT_LINE(SQL%ROWCOUNT || ' records deleted for employees older than 60.');
    
    COMMIT;
END;
/
