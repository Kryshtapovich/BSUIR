CREATE OR REPLACE FUNCTION task4(id IN NUMBER)
RETURN VARCHAR2
IS
    str1  VARCHAR2(50);
    str2  VARCHAR2(50);
BEGIN
    str1 := 'INSERT INTO MyTable VALUES(';
    str1 := CONCAT(str1, TO_CHAR(id));
    str1 := CONCAT(str1, ',');
    str2 := TO_CHAR(DBMS_RANDOM.RANDOM());
    str2 := CONCAT(str1, str2);

   RETURN str2;
END;

BEGIN
    DBMS_OUTPUT.PUT_LINE(task4(50));
END; 
