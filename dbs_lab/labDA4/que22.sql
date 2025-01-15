DECLARE
    mark1 NUMBER := &mark1;
    mark2 NUMBER := &mark2;
    mark3 NUMBER := &mark3;
    average NUMBER;
    grade CHAR(1);
BEGIN
    average := (mark1 + mark2 + mark3) / 3;

    CASE 
        WHEN average >= 90 THEN grade := 'A';
        WHEN average >= 80 THEN grade := 'B';
        WHEN average >= 70 THEN grade := 'C';
        WHEN average >= 60 THEN grade := 'D';
        ELSE grade := 'F';
    END CASE;

    DBMS_OUTPUT.PUT_LINE('The student''s grade is: ' || grade);
END;
/
