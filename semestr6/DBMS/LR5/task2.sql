CREATE OR REPLACE TRIGGER table1_audit_trigger 
BEFORE DELETE OR INSERT OR UPDATE ON Table1 
FOR EACH ROW
BEGIN 
    CASE
        WHEN INSERTING THEN
            INSERT INTO table1_audit(operation, change_time, is_reverted, testcolumn, id_row) 
            VALUES ('INSERT', CURRENT_TIMESTAMP, 0, :NEW.testcolumn, :NEW.id);
        WHEN DELETING THEN
            INSERT INTO table1_audit(operation, change_time, is_reverted, testcolumn, id_row) 
            VALUES ('DELETE', CURRENT_TIMESTAMP, 0, :OLD.testcolumn, :OLD.id);
        WHEN UPDATING THEN
            INSERT INTO table1_audit(operation, change_time ,is_reverted, testcolumn, id_row) 
            VALUES ('UPDATE', CURRENT_TIMESTAMP, 0, :OLD.testcolumn, :OLD.id);
    END CASE;
END;

CREATE OR REPLACE TRIGGER table2_audit_trigger 
BEFORE DELETE OR INSERT OR UPDATE ON Table2 
FOR EACH ROW
BEGIN 
    CASE
        WHEN INSERTING THEN
            INSERT INTO table2_audit(operation, change_time, is_reverted, testcolumn, id_row) 
            VALUES ('INSERT', CURRENT_TIMESTAMP, 0, :NEW.testcolumn, :NEW.id);
        WHEN DELETING THEN
            INSERT INTO table2_audit(operation, change_time, is_reverted, testcolumn, id_row) 
            VALUES ('DELETE', CURRENT_TIMESTAMP, 0, :OLD.testcolumn, :OLD.id);
        WHEN UPDATING THEN
            INSERT INTO table2_audit(operation, change_time ,is_reverted, testcolumn, id_row) 
            VALUES ('UPDATE', CURRENT_TIMESTAMP, 0, :OLD.testcolumn, :OLD.id);
    END CASE;
END;

CREATE OR REPLACE TRIGGER table3_audit_trigger 
BEFORE DELETE OR INSERT OR UPDATE ON Table3 
FOR EACH ROW
BEGIN 
    CASE
        WHEN INSERTING THEN
            INSERT INTO table3_audit(operation, change_time, is_reverted, testcolumn, id_row) 
            VALUES ('INSERT', CURRENT_TIMESTAMP, 0, :NEW.testcolumn, :NEW.id);
        WHEN DELETING THEN
            INSERT INTO table3_audit(operation, change_time, is_reverted, testcolumn, id_row) 
            VALUES ('DELETE', CURRENT_TIMESTAMP, 0, :OLD.testcolumn, :OLD.id);
        WHEN UPDATING THEN
            INSERT INTO table3_audit(operation, change_time ,is_reverted, testcolumn, id_row) 
            VALUES ('UPDATE', CURRENT_TIMESTAMP, 0, :OLD.testcolumn, :OLD.id);
    END CASE;
END;
