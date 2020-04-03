DROP TYPE XMLRecord;
CREATE TYPE XMLRecord IS TABLE OF VARCHAR2(1000);

CREATE OR REPLACE FUNCTION get_value_from_xml(
    xml_string  IN VARCHAR2, 
    xpath       IN VARCHAR2
)
RETURN XMLRecord 
AS
    i               NUMBER       := 1;
    records_length  NUMBER       := 0; 
    current_record  VARCHAR2(50) := ' '; 
    xml_property    XMLRecord    := XMLRecord(); 
BEGIN
    SELECT  EXTRACTVALUE(XMLTYPE(xml_string), xpath || '[' || i || ']') 
    INTO    current_record 
    FROM    dual;

    WHILE current_record IS NOT NULL 
    LOOP i := i+1;
        records_length := records_length + 1;
        xml_property.extend;
        xml_property(records_length) := REPLACE(TRIM(current_record), ' ', '');

        SELECT  EXTRACTVALUE(XMLTYPE(xml_string), xpath || '[' || i || ']') 
        INTO    current_record 
        FROM    dual;
    END LOOP;

    RETURN xml_property; 
END;

CREATE OR REPLACE PACKAGE xml_package 
AS
    FUNCTION xml_select(xml_string in VARCHAR2) RETURN VARCHAR2;
    FUNCTION process_select(xml_string IN VARCHAR2) RETURN sys_refcursor;
    FUNCTION where_property(xml_string in VARCHAR2) RETURN VARCHAR2;
END;

CREATE OR REPLACE PACKAGE BODY xml_package 
AS
    FUNCTION process_select(xml_string IN VARCHAR2) RETURN sys_refcursor
AS
    cur sys_refcursor; 
BEGIN
    OPEN cur FOR xml_select(xml_string); 
    RETURN cur;
END;
    
FUNCTION xml_select(xml_string in VARCHAR2 ) RETURN VARCHAR2
AS
    join_type       VARCHAR2(100); 
    join_condition  VARCHAR2(100);
    select_query    VARCHAR2(1000) := 'SELECT'; 
    tables_list     XMLRecord      := XMLRecord(); 
    columns_list    XMLRecord      := XMLRecord(); 
    filters         XMLRecord      := XMLRecord(); 
BEGIN
    IF xml_string IS NULL THEN 
        RETURN NULL;
    END IF;


    tables_list  := get_value_from_xml(xml_string, 'Operation/Tables/Table');
    columns_list := get_value_from_xml(xml_string, 'Operation/OutputColumns/Column');
    select_query := select_query || ' ' || columns_list(1);

    FOR col_index IN 2..columns_list.count 
    LOOP
        select_query := select_query || ', ' || columns_list(col_index); 
    END LOOP;

        select_query := select_query || ' FROM ' || tables_list(1); 

    FOR indx IN 2..tables_list.count
    LOOP
        SELECT  EXTRACTVALUE(XMLTYPE(xml_string), 'Operation/Joins/Join'  || 
                                                  '['                     || 
                                                  (indx - 1)              ||
                                                  ']/Type') 
        INTO    join_type 
        FROM    dual;

        SELECT  EXTRACTVALUE(XMLTYPE(xml_string), 'Operation/Joins/Join'  || 
                                                  '['                     || 
                                                  (indx - 1)              || 
                                                  ']/Condition') 
        INTO    join_condition 
        FROM    dual;

        select_query := select_query       || 
                        ' '                || 
                        join_type          || 
                        ' '                || 
                        tables_list(indx)  || 
                        ' ON '             || 
                        join_condition;
    END LOOP;

    select_query := select_query || where_property(xml_string); 
    DBMS_OUTPUT.PUT_LINE(select_query);

    RETURN select_query; 
END;

FUNCTION where_property(xml_string in VARCHAR2 ) RETURN VARCHAR2 
AS
    sub_query           VARCHAR(1000); 
    sub_query1          VARCHAR(1000); 
    condition_operator  VARCHAR(100); 
    condition_body      VARCHAR2(100);
    current_record      VARCHAR2(1000); 
    where_clouse        VARCHAR2(1000) := ' WHERE'; 
    i                   NUMBER         := 0; 
    records_length      NUMBER         := 0;
    where_filters       XMLRecord      := XMLRecord(); 
BEGIN
    SELECT  EXTRACT(XMLTYPE(xml_string), 'Operation/Where/Conditions/Condition').getStringVal() 
    INTO    current_record 
    FROM    dual;
    
    WHILE current_record IS NOT NULL 
    LOOP 
        i := i + 1;
        records_length := records_length + 1; 
        where_filters.extend;
        where_filters(records_length) := TRIM(current_record);

        SELECT  EXTRACT(XMLTYPE(xml_string), 'Operation/Where/Conditions/Condition'  || 
                                             '['                                     || 
                                             i                                       || 
                                             ']').getStringVal() 
        INTO    current_record 
        FROM    dual; 
    END LOOP;

    FOR i IN 2..where_filters.count 
    LOOP
        SELECT  EXTRACTVALUE(XMLTYPE(where_filters(i)), 'Condition/Body') 
        INTO    condition_body 
        FROM    dual;
        
        SELECT  EXTRACT(XMLTYPE(where_filters(i)), 'Condition/Operation').getStringVal() 
        INTO    sub_query 
        FROM    dual;

        SELECT  EXTRACTVALUE(XMLTYPE(where_filters(i)), 'Condition/ConditionOperator') 
        INTO    condition_operator 
        FROM    dual;

        sub_query1 := xml_select(sub_query);

        IF sub_query1 IS NOT NULL THEN 
            sub_query1:= '('|| sub_query1 || ')';
        END IF;

        where_clouse := where_clouse              || 
                        ' '                       || 
                        TRIM(condition_body)      || 
                        ' '                       || 
                        sub_query1                || 
                        TRIM(condition_operator)  || 
                        ' ';
    END LOOP;


    IF where_filters.count = 0 THEN 
        RETURN ' ';
    ELSE
        RETURN where_clouse; 
    END IF;
END;
