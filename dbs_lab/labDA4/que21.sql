-- DECLARE
--     num1 NUMBER := &num1;
--     num2 NUMBER := &num2;
--     num3 NUMBER := &num3;
--     greatest NUMBER;
-- BEGIN
    
--     IF num1 >= num2 AND num1 >= num3 THEN
--         greatest := num1;
--     ELSIF num2 >= num1 AND num2 >= num3 THEN
--         greatest := num2;
--     ELSE
--         greatest := num3;
--     END IF;

--     DBMS_OUTPUT.PUT_LINE('The greatest of the three numbers is: ' || greatest);
-- END;
-- /


DECLARE
    num1 NUMBER;
    num2 NUMBER;
    num3 NUMBER;
    greatest NUMBER;
BEGIN

    num1 := '&num1';
    num2 := '&num2';
    num3 := '&num3';
    
    IF num1 >= num2 AND num1 >= num3 THEN
        greatest := num1;
    ELSIF num2 >= num1 AND num2 >= num3 THEN
        greatest := num2;
    ELSE
        greatest := num3;
    END IF;

    DBMS_OUTPUT.PUT_LINE('The greatest of the three numbers is: ' || greatest);
END;
/

