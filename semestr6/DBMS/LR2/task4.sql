CREATE TABLE LOGS
(
    TIME      TIMESTAMP NOT NULL,
    COMMAND   VARCHAR2(10) NOT NULL,
    NEW_ID    NUMBER,
    OLD_ID    NUMBER,
    NAME      VARCHAR2(50),
    GROUP_ID  NUMBER
); 

CREATE OR REPLACE TRIGGER logger
AFTER INSERT OR DELETE OR UPDATE ON STUDENTS
FOR EACH ROW
BEGIN
    CASE
        WHEN INSERTING THEN
            INSERT INTO  LOGS
            VALUES      (SYSTIMESTAMP,
                         'INSERT',
                         :new.ID,
                         NULL,
                         NULL,
                         NULL);
        WHEN UPDATING THEN
            INSERT INTO  LOGS
            VALUES      (SYSTIMESTAMP,
                         'UPDATE',
                         :new.ID,
                         :old.ID,
                         :old.NAME,
                         :old.GROUP_ID);
        WHEN DELETING THEN
            INSERT INTO  LOGS
            VALUES      (SYSTIMESTAMP,
                         'DELETE',
                         NULL,
                         :old.ID,
                         :old.NAME,
                         :old.GROUP_ID);
    END CASE;
END; 
