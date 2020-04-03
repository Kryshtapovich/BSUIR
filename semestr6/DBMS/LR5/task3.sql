CREATE OR REPLACE TYPE string_array AS VARRAY(3) OF VARCHAR2(10);

CREATE OR REPLACE PROCEDURE restore_child( 
    table_name IN VARCHAR2, 
    restore_until TIMESTAMP
)
AS
    child_array string_array; 
BEGIN
    child_array := get_dependent_tables(table_name); 
    restore_data(child_array,restore_until);
END;

CREATE OR REPLACE FUNCTION get_dependent_tables(
    in_table_name IN VARCHAR2
) 
RETURN string_array 
AS
    indx NUMBER;
    dependent_tables string_array := string_array(); 
BEGIN
    FOR relation IN (SELECT  p.table_name, ch.table_name child 
                     FROM    user_cons_columns p
                     JOIN    user_constraints ch ON p.constraint_name = ch.r_constraint_name 
                     WHERE   p.table_name = in_table_name) 
    LOOP
        dependent_tables.extend; 
        indx := indx + 1;
        dependent_tables(indx) := relation.child; 
    END LOOP;
    
    RETURN dependent_tables; 
END;

CREATE OR REPLACE PROCEDURE restore_table1(restore_until TIMESTAMP) 
AS
BEGIN
    FOR	audit_row IN (SELECT  id, operation, testcolumn, id_row, change_time 
                      FROM    TABLE1_AUDIT
                      WHERE   change_time > restore_until AND is_reverted = 0) 
    LOOP
        CASE audit_row.operation 
            WHEN 'UPDATE' THEN
                DBMS_OUTPUT.PUT_LINE('UPDATE Table1 SET column1 = '  || 
                                     audit_row.testcolumn            || 
                                     ' WHERE id = '                  || 
                                     audit_row.id_row);

                INSERT INTO audit_scripts(operation,script) 
                VALUES ('UPDATE', 'UPDATE Table1 SET column1 = '  || 
                                  audit_row.testcolumn            || 
                                  ' WHERE id = '                  || 
                                  audit_row.id_row);

            WHEN 'DELETE' THEN
                DBMS_OUTPUT.PUT_LINE('INSERT INTO Table1(testcolumn) VALUES ('  || 
                                     audit_row.testcolumn                       || 
                                     ')');

                INSERT INTO audit_scripts(operation,script)  
                VALUES ('DELETE', 'INSERT INTO Table1(testcolumn) VALUES ('  || 
                                  audit_row.testcolumn                       || 
                                  ')');

                restore_child('Table1',audit_row.change_time); 

            WHEN 'INSERT' THEN
                DBMS_OUTPUT.PUT_LINE('DELETE FROM Table1 WHERE id = ' || audit_row.id_row);

                INSERT INTO audit_scripts(operation,script) 
                VALUES ('INSERT','DELETE FROM Table1 WHERE id = ' || audit_row.id_row );

                restore_child('Table1',audit_row.change_time); 
        END CASE;
    END LOOP;

    UPDATE  TABLE1_AUDIT
    SET     is_reverted = 1
    WHERE   change_time > restore_until; 
END;

CREATE OR REPLACE PROCEDURE restore_table2(restore_until TIMESTAMP) 
AS 
BEGIN
    FOR	audit_row IN (SELECT  id, operation, testcolumn, id_row, change_time 
                      FROM    TABLE2_AUDIT
                      WHERE   change_time > restore_until AND is_reverted = 0) 
    LOOP
        CASE audit_row.operation 
            WHEN 'UPDATE' THEN
                DBMS_OUTPUT.PUT_LINE('UPDATE Table2	SET column1 = '  ||
                                     audit_row.testcolumn            || 
                                     ' WHERE id = '                  || 
                                     audit_row.id_row);

                INSERT INTO audit_scripts(operation,script) 
                VALUES ('UPDATE', 'UPDATE Table2 SET column1 = '  || 
                                  audit_row.testcolumn            || 
                                  ' WHERE id = '                  || 
                                  audit_row.id_row);

            WHEN 'DELETE' THEN
                DBMS_OUTPUT.PUT_LINE('INSERT INTO Table2(testcolumn) VALUES ('  || 
                                     audit_row.testcolumn                       || 
                                     ')');

                INSERT INTO  audit_scripts(operation,script)  
                VALUES ('DELETE', 'INSERT INTO Table2(testcolumn) VALUES ('  || 
                                  audit_row.testcolumn                       || 
                                  ')');

                restore_child('Table2', audit_row.change_time); 

            WHEN 'INSERT' THEN
                DBMS_OUTPUT.PUT_LINE('DELETE FROM Table2 WHERE id = ' || audit_row.id_row);

                INSERT INTO	audit_scripts(operation,script) 
                VALUES ('INSERT', 'DELETE FROM Table2 WHERE id = ' || audit_row.id_row );

                restore_child('Table2', audit_row.change_time); 
        END CASE;
    END LOOP;

    UPDATE  TABLE2_AUDIT
    SET     is_reverted = 1
    WHERE   change_time > restore_until; 
END;

CREATE OR REPLACE PROCEDURE restore_table3(restore_until TIMESTAMP) 
AS 
BEGIN
    FOR	audit_row IN (SELECT id, operation, testcolumn, id_row, change_time 
                      FROM TABLE3_AUDIT
                      WHERE change_time > restore_until AND is_reverted = 0 ) 
    LOOP 
        CASE audit_row.operation
            WHEN 'UPDATE' THEN
                DBMS_OUTPUT.PUT_LINE('UPDATE Table3 SET column1 = '  ||
                                     audit_row.testcolumn            || 
                                     ' WHERE id = '                  || 
                                     audit_row.id_row);

                INSERT INTO audit_scripts(operation,script) 
                VALUES ('UPDATE', 'UPDATE Table3 SET column1 = '  || 
                                  audit_row.testcolumn            || 
                                  ' WHERE id = '                  || 
                                  audit_row.id_row);

            WHEN 'DELETE' THEN
                DBMS_OUTPUT.PUT_LINE('INSERT INTO Table3(testcolumn) VALUES ('  || 
                                     audit_row.testcolumn                       || 
                                     ')');

                INSERT  INTO  audit_scripts(operation,script)  
                VALUES	('DELETE', 'INSERT INTO Table3(testcolumn) VALUES ('  || 
                                   audit_row.testcolumn                       || 
                                   ')');

                restore_child('Table3',audit_row.change_time); 

            WHEN 'INSERT' THEN
                DBMS_OUTPUT.PUT_LINE('DELETE FROM Table3 WHERE id = ' || audit_row.id_row );

                INSERT INTO audit_scripts(operation,script) 
                VALUES ('INSERT', 'DELETE FROM Table3 WHERE id = ' || audit_row.id_row );

                restore_child('Table3',audit_row.change_time); 
        END CASE;
    END LOOP;

    UPDATE  TABLE3_AUDIT
    SET     is_reverted = 1
    WHERE   change_time > restore_until; 
END;

CREATE OR REPLACE package body restore_pkg 
AS
    PROCEDURE db_back(
        rollback_timestamp IN timestamp, 
        table_names string_array
    ) 
    AS 
    BEGIN
        restore_data(table_names, rollback_timestamp); 
    END;

    PROCEDURE db_rollback(
        rollback_millisecond IN number, 
        table_names string_array
    ) 
    AS 
        rollback_timestamp timestamp;
    BEGIN
        SELECT  current_timestamp - interval '0.001' second * rollback_millisecond 
        INTO    rollback_timestamp 
        FROM    dual;
    END; 
END;

CREATE OR REPLACE PROCEDURE restore_data (
    input_tables  IN string_array,
    input_ts      IN TIMESTAMP
) 
AS 
BEGIN
    FOR i IN 1..input_tables.count 
    LOOP EXECUTE IMMEDIATE 'BEGIN RESTORE_'                           || 
                           input_tables(i)                            || 
                           '( TO_TIMESTAMP('''                        || 
                           TO_CHAR(input_ts, 'DD-MM- YYYY HH:MI:SS')  || 
                           ''', ''DD-MM-YYYYHH:MI:SS'')); END;';
    END LOOP;
END;
