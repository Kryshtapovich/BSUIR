CREATE OR REPLACE FUNCTION task3
RETURN VARCHAR2    
IS
    even    NUMBER;
    odd     NUMBER;
    result  VARCHAR2(20);
BEGIN
    SELECT  COUNT(*)
    INTO    even
    FROM    MyTable
    WHERE   REMAINDER(val, 2) = 0;

    SELECT  COUNT(*)
    INTO    odd
    FROM    MyTable
    WHERE   REMAINDER(val, 2) = 1;

    IF even > odd THEN
        result := 'TRUE';
    ELSIF even < odd THEN
        result := 'FALSE';
    ELSE
        result := 'EQUAL';
    END IF;

    RETURN result;
END;

BEGIN
    DBMS_OUTPUT.PUT_LINE(task3());
END; 
