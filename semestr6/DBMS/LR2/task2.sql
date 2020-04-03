CREATE OR REPLACE TRIGGER generate_student_id
BEFORE INSERT ON STUDENTS
FOR EACH ROW
BEGIN
    SELECT  students_id_sequence.NEXTVAL
    INTO    :new.ID
    FROM    dual;
END; 

CREATE OR REPLACE TRIGGER check_unique_student_id
BEFORE INSERT OR UPDATE OF NAME ON STUDENTS
FOR EACH ROW
DECLARE
    rowcount NUMBER;
    e_not_unique_student_id EXCEPTION;
    PRAGMA EXCEPTION_INIT(e_not_unique_student_id, -20001);
BEGIN
    SELECT  COUNT(*)
    INTO    rowcount
    FROM    STUDENTS
    WHERE   ID = :new.ID;

    IF rowcount != 0 THEN
        RAISE e_not_unique_student_id;
    END IF;
END; 

CREATE OR REPLACE TRIGGER generate_group_id
BEFORE INSERT ON GROUPS
FOR EACH ROW
BEGIN 
    SELECT  groups_id_sequence.NEXTVAL 
    INTO    :new.ID 
    FROM    dual;
END;

CREATE OR REPLACE TRIGGER check_unique_group_id
BEFORE INSERT OR UPDATE OF NAME ON GROUPS
FOR EACH ROW
DECLARE
    rowcount NUMBER;
    e_not_unique_group_id EXCEPTION;
    PRAGMA EXCEPTION_INIT(e_not_unique_group_id, -20001);
BEGIN 
    SELECT  COUNT(*) 
    INTO    rowcount 
    FROM    GROUPS 
    WHERE   ID = :new.ID;

    IF rowcount != 0  THEN
        RAISE e_not_unique_group_id;
    END IF;
END;

CREATE OR REPLACE TRIGGER check_unique_group_name
BEFORE INSERT OR UPDATE OF NAME ON GROUPS
FOR EACH ROW
DECLARE
    rowcount NUMBER;
    e_not_unique_group_name EXCEPTION;
    PRAGMA EXCEPTION_INIT(e_not_unique_group_name, -20002);
BEGIN
    SELECT  COUNT(*)
    INTO    rowcount
    FROM    GROUPS
    WHERE   NAME = :new.NAME;

    IF rowcount != 0 THEN
        RAISE e_not_unique_group_name;
    END IF;
END; 
