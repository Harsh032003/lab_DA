DECLARE
    v_ssn CHAR(9);
BEGIN
    v_ssn := '&employee_ssn';
    
    DELETE FROM Employee 
    WHERE SSN_NUMBER = v_ssn;

    IF SQL%ROWCOUNT > 0 THEN
        DBMS_OUTPUT.PUT_LINE('Employee record with SSN ' || v_ssn || ' has been deleted.');
    ELSE
        DBMS_OUTPUT.PUT_LINE('No employee found with SSN ' || v_ssn);
    END IF;
    
    COMMIT;
END;
/
