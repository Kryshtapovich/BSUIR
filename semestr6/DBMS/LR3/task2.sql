CREATE OR REPLACE PROCEDURE compare_table_structure_by_object(
    dev_schema_name   IN VARCHAR2, 
    prod_schema_name  IN VARCHAR2, 
    object_type       IN VARCHAR2
)
IS
    diff NUMBER := 0;
BEGIN
    FOR obj_type IN ('PROCEDURE', 'PACKAGE', 'INDEX', 'TABLE') 
    LOOP
        FOR same_object IN 
                            (SELECT  objects1.OBJECT_NAME 
                             FROM    ALL_OBJECTS objects1 
                             WHERE   OWNER = dev_schema_name AND object_type = obj_type
                             INTERSECT
                             SELECT  objects2.TABLE_NAME 
                             FROM    ALL_OBJECTS objects2 
                             WHERE   OWNER = prod_schema_name AND object_type = obj_type)
        LOOP
            SELECT  COUNT(*) 
            INTO    diff 
            FROM 
                    (SELECT  object1.OBJECT_NAME, table1.DATA_TYPE 
                     FROM    ALL_TAB_COLUMNS table1 
                     WHERE   OWNER = dev_schema_name AND TABLE_NAME = same_table.TABLE_NAME) cols1
            FULL JOIN
                    (SELECT  object2.OBJECT_NAME name, table2.DATA_TYPE 
                     FROM    ALL_TAB_COLUMNS table2 
                     WHERE   OWNER = prod_schema_name AND TABLE_NAME = same_table.TABLE_NAME) cols2
            ON      cols1.NAME = cols2.NAME
            WHERE   cols1.NAME IS NULL OR cols2.NAME IS NULL;


            IF diff > 0 THEN
                DBMS_OUTPUT.PUT_LINE('Table structure of '  || 
                                     same_table.TABLE_NAME  || 
                                     ' is different in '    || 
                                     dev_schema_name        || 
                                     ' and '                || 
                                     prod_schema_name);
            ELSE
                DBMS_OUTPUT.PUT_LINE('Table structure of '  || 
                                     same_table.TABLE_NAME  || 
                                     ' the same'); 
            END IF;
        END LOOP;
    END LOOP;
END;

CREATE OR REPLACE PROCEDURE compare_tables(
    dev_schema_name   IN VARCHAR2, 
    prod_schema_name  IN VARCHAR2
) 
IS
BEGIN
    FOR diff_table IN 
                       (SELECT  tables1.TABLE_NAME 
                        FROM    ALL_TABLES tables1 
                        WHERE   tables1.OWNER = dev_schema_name
                        MINUS
                        SELECT  tables2.TABLE_NAME 
                        FROM    ALL_TABLES tables2 
                        WHERE   tables2.OWNER = prod_schema_name) 
    LOOP
        DBMS_OUTPUT.PUT_LINE('Table '          ||
                             diff_table.NAME   || 
                             ' is in '         || 
                             dev_schema_name   || 
                             ' but not in '    || 
                             prod_schema_name);
    END LOOP;

    FOR diff_table IN 
                       (SELECT  tables2.TABLE_NAME 
                        FROM    ALL_TABLES tables2 
                        WHERE   tables2.OWNER = prod_schema_name
                        MINUS
                        SELECT  tables1.TABLE_NAME 
                        FROM    ALL_TABLES tables1 
                        WHERE   tables1.OWNER = dev_schema_name) 
    LOOP
        DBMS_OUTPUT.PUT_LINE('Table '          || 
                             diff_table.NAME   || 
                             ' is in '         || 
                             prod_schema_name  || 
                             ' but not in '    || 
                             dev_schema_name);
    END LOOP;
END;
