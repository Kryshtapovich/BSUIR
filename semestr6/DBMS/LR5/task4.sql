CREATE OR REPLACE PROCEDURE create_audit(table_names IN string_array) 
AS 
BEGIN
    FOR i IN 1..table_names.count 
    LOOP
        EXECUTE IMMEDIATE 'ALTER TRIGGER ' || table_names(i) || '_AUDIT_TRIGGER' || ' DISABLE';
    END LOOP;

    FOR audit_script_row IN (SELECT script 
                             FROM audit_scripts 
                             ORDER BY ID DESC) 
    LOOP 
        DBMS_OUTPUT.PUT_LINE('EXECUTING:' || audit_script_row.script);
        EXECUTE IMMEDIATE audit_script_row.script; 
    END LOOP;

    DELETE FROM audit_scripts;

    FOR i IN 1..table_names.count 
    LOOP
        EXECUTE IMMEDIATE 'ALTER TRIGGER ' || table_names(i)|| '_AUDIT_TRIGGER' || ' ENABLE';
    END LOOP;

    DELETE FROM audit_scripts;
END;

CREATE OR REPLACE FUNCTION html_create(
    table_names IN string_array, 
    ts          IN TIMESTAMP) 
RETURN VARCHAR2 
AS
    html_document VARCHAR2(500) := '<!DOCTYPE html>
                                        <html>
                                            <head>
                                                <title>Title</title>
                                            </head>
                                            <body> ';
    operation_count NUMBER;
    sys_ref_c SYS_REFCURSOR;
    operation_name VARCHAR(20); 
BEGIN
    FOR i IN 1..table_names.count 
    LOOP
        html_document := html_document || '<h1>' || table_names(i) || '</h1>';
        OPEN sys_ref_c 

        FOR 'SELECT operation,COUNT(*) FROM '                        || 
            table_names(i)                                           || 
            '_AUDIT '                                                || 
            'WHERE is_reverted=0 AND change_time > TO_TIMESTAMP('''  || 
            TO_CHAR(ts,'DD-MM- YYYY HH:MI:SS')                       || 
            ''', ''DD-MM-YYYYHH:MI:SS'') GROUP BY operation';
        LOOP
            FETCH sys_ref_c INTO operation_name,operation_count; 
            EXIT WHEN sys_ref_c%NOTFOUND;
            html_document := html_document || operation_name || ':' || operation_count || '<p>'; 
        END LOOP;

        CLOSE sys_ref_c; 
    END LOOP;

    html_document := html_document || '</body></html>'; 
    RETURN html_document;
END;
