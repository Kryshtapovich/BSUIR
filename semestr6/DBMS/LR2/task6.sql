CREATE OR REPLACE TRIGGER change_students 
AFTER INSERT OR DELETE OR UPDATE ON STUDENTS
FOR EACH ROW
DECLARE
    rowcount NUMBER;
BEGIN
    CASE
        WHEN INSERTING THEN
            UPDATE  GROUPS
            SET     C_VAL = C_VAL + 1
            WHERE   ID    = :new.GROUP_ID;

        WHEN UPDATING THEN
            UPDATE  GROUPS
            SET     C_VAL = C_VAL + 1
            WHERE   ID    = :new.GROUP_ID;
        
            UPDATE  GROUPS
            SET     C_VAL = C_VAL - 1
            WHERE   ID    = :old.GROUP_ID;

        WHEN DELETING THEN
            UPDATE  GROUPS
            SET     C_VAL = C_VAL - 1
            WHERE   ID    = :old.GROUP_ID;
    END CASE;
END;
