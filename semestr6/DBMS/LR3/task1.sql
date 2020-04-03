CREATE OR REPLACE PROCEDURE compare_tables_structure(
    dev_schema_name   IN VARCHAR2, 
    prod_schema_name  IN VARCHAR2
) 
IS
    diff NUMBER := 0;
BEGIN
    FOR same_table IN 
                        (SELECT  TABLE_NAME 
                         FROM    ALL_TABLES tables1 
                         WHERE   OWNER = dev_schema_name
                         INTERSECT
                         SELECT  tables2.TABLE_NAME 
                         FROM    ALL_TABLES tables2 
                         WHERE   OWNER = prod_schema_name) 
    LOOP
        SELECT  COUNT(*)
        INTO    diff 
        FROM
            (SELECT  table1.COLUMN_NAME, table1.DATA_TYPE 
             FROM    ALL_TAB_COLUMNS table1 
             WHERE   OWNER = dev_schema_name AND TABLE_NAME = same_table.TABLE_NAME) columns1
        FULL JOIN
                (SELECT  table2.COLUMN_NAME name, table2.DATA_TYPE 
                 FROM    ALL_TAB_COLUMNS table2 
                 WHERE   OWNER = prod_schema_name AND TABLE_NAME = same_table.TABLE_NAME) columns2
        ON      columns1.NAME = columns2.NAME
        WHERE   columns1.NAME IS NULL OR columns2.NAME IS NULL;


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
END;
 
CREATE OR REPLACE PROCEDURE compare_tables(
    dev_schema_name   IN VARCHAR2, 
    prod_schema_name  IN VARCHAR2
) 
IS
BEGIN
    FOR diff_table IN 
                        (SELECT  tables1.TABLE_NAME name 
                         FROM    ALL_TABLES tables1 
                         WHERE   tables1.OWNER = dev_schema_name
                         MINUS
                         SELECT  tables2.TABLE_NAME  
                         FROM    ALL_TABLES tables2 
                         WHERE   tables2.OWNER = prod_schema_name) 
    LOOP
        DBMS_OUTPUT.PUT_LINE('Table '          || 
                             diff_table.name   || 
                             ' is in '         || 
                             dev_schema_name   || 
                             ' but not in '    || 
                             prod_schema_name);
    END LOOP;

    FOR diff_table IN 
                        (SELECT  tables2.TABLE_NAME name 
                         FROM    ALL_TABLES tables2 
                         WHERE   tables2.OWNER = prod_schema_name
                         MINUS
                         SELECT  tables1.TABLE_NAME  
                         FROM    ALL_TABLES tables1 
                         WHERE   tables1.OWNER = dev_schema_name) 
    LOOP
        DBMS_OUTPUT.PUT_LINE('Table '          || 
                             diff_table.name   || 
                             ' is in '         || 
                             prod_schema_name  ||
                             ' but not in '    || 
                             dev_schema_name);
    END LOOP;
END;
