DECLARE
    counter NUMBER;
BEGIN
    counter := 1;

    LOOP
        INSERT INTO  MyTable
        VALUES      (counter, DBMS_RANDOM.RANDOM());
        
        counter := counter + 1;
        EXIT WHEN counter > 10000;
    END LOOP;
END; 
