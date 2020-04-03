CREATE OR REPLACE PROCEDURE custom_insert(id IN NUMBER, val IN NUMBER)
IS
BEGIN
    INSERT INTO MyTable VALUES (id, val)
END;

CREATE OR REPLACE PROCEDURE custom_update(updateId IN NUMBER, newVal IN NUMBER)
IS
BEGIN
    UPDATE  MyTable
    SET     val = newVal
    WHERE   id  = updateId;
END;

CREATE OR REPLACE PROCEDURE custom_delete(deleteId IN NUMBER)
IS
BEGIN
    DELETE FROM  MyTable
    WHERE        id = deleteId;
END;

BEGIN
    custom_insert(10001, 3);
    custom_update(10001, 7);
    custom_delete(10001);
END;
