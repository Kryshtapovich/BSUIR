CREATE OR REPLACE FUNCTION task6(salary IN NUMBER, prem IN NUMBER)
RETURN NUMBER
IS
    result NUMBER;
BEGIN
    result := ( 1 + prem / 100 ) * 12 * salary;

    RETURN result;
END;

DECLARE
    salary       NUMBER;
    prem         NUMBER;
    type_info_1  VARCHAR2(200);
    type_info_2  VARCHAR2(200);

BEGIN
    salary := 100;
    prem   := 10;

    SELECT  DUMP(salary)
    INTO    type_info_1
    FROM    dual;

    SELECT  DUMP(prem)
    INTO    type_info_2
    FROM    dual;

    type_info_1 := SUBSTR(type_info_1, 0, 6);
    type_info_2 := SUBSTR(type_info_2, 0, 6);

    IF type_info_1 = 'Typ=2' AND type_info_2 = 'Typ=2' THEN
        DBMS_OUTPUT.PUT_LINE(Task6(salary, prem));
    ELSE
        DBMS_OUTPUT.PUT_LINE('Type Error');
    END IF;
END; 

BEGIN
    salary := 100;
    prem   := 'qwerty';

    SELECT  DUMP(salary)
    INTO    type_info_1
    FROM    dual;

    SELECT  DUMP(prem)
    INTO    type_info_2
    FROM    dual;

    type_info_1 := SUBSTR(type_info_1, 0, 6);
    type_info_2 := SUBSTR(type_info_2, 0, 6);

    IF type_info_1 = 'Typ=2' AND type_info_2 = 'Typ=2' THEN
        DBMS_OUTPUT.PUT_LINE(Task6(salary, prem));
    ELSE
        DBMS_OUTPUT.PUT_LINE('Type Error');
    END IF;
END; 
