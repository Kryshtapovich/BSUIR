CREATE OR REPLACE PROCEDURE replace_object(
    dev_schema_name   IN VARCHAR2, 
    prod_schema_name  IN VARCHAR2, 
    object_type       IN VARCHAR2, 
    object_name       IN VARCHAR2
)
IS
    query_string VARCHAR2(100);
BEGIN
    FOR src IN 
                (SELECT  LINE, TEXT 
                 FROM    ALL_SOURCE 
                 WHERE   OWNER = dev_schema_name AND NAME = object_name)

    LOOP
        IF src.LINE = 1 THEN
            query_string := 'CREATE OR REPLACE '                                     ||
                             REPLACE(src.TEXT, LOWER(object_name), prod_schema_name  ||
                             '.'                                                     || 
                             object_name);
        ELSE
            query_string := query_string || src.TEXT; 
        END IF;
    END LOOP;

    EXECUTE IMMEDIATE query_string; 
END;

CREATE OR REPLACE PROCEDURE create_object(
    dev_schema_name   IN VARCHAR2, 
    prod_schema_name  IN VARCHAR2,
    object_type       IN VARCHAR2, 
    object_name       IN VARCHAR2
)
IS
    query_string VARCHAR2(100);
BEGIN
    FOR src IN 
                (SELECT  LINE, TEXT 
                 FROM    ALL_SOURCE 
                 WHERE   OWNER = dev_schema_name AND NAME = object_name)
    LOOP
        IF src.LINE =1 THEN
            query_string := 'CREATE ' || 
                            REPLACE(src.TEXT, LOWER(object_name), prod_schema_name  || 
                                                                  '.'               || 
                                                                  object_name);
        ELSE
            query_string := query_string || src.TEXT;
        END IF;
    END LOOP;

    EXECUTE IMMEDIATE query_string; 
END;

CREATE OR REPLACE PROCEDURE delete_object(
    dev_schema_name  IN VARCHAR2, 
    object_type      IN VARCHAR2, 
    object_name      IN VARCHAR2
)
IS
    delete_query VARCHAR(100); 
BEGIN
    delete_query := 'DROP '          || 
                    object_type      || 
                    ' '              || 
                    dev_schema_name  || 
                    '.'              || 
                    object_name; 
    EXECUTE IMMEDIATE delete_query;
END;

CREATE OR REPLACE PROCEDURE compare_objects(
    dev_schema_name   IN VARCHAR2, 
    prod_schema_name  IN VARCHAR2, 
    object_type       IN VARCHAR2
)
IS
    diff NUMBER := 0;
BEGIN
    FOR pair IN 
                (SELECT  obj1.NAME AS name1, obj2.NAME AS name2 
                 FROM 
                        (SELECT OBJECT_NAME name FROM ALL_OBJECTS
                         WHERE  OBJECT_TYPE = object_type AND OWNER = dev_schema_name) obj1 
                 FULL JOIN
                        (SELECT  OBJECT_NAME name 
                         FROM    ALL_OBJECTS
                         WHERE   OBJECT_TYPE = object_type AND OWNER = prod_schema_name) obj2 
                 ON      obj1.NAME = obj2.NAME) 
    LOOP
        IF pair.name1 IS NULL THEN
            delete_object(prod_schema_name, object_type, pair.name2); 
        ELSIF pair.name2 IS NULL THEN
            create_object(dev_schema_name, prod_schema_name, object_type, pair.name1); 
        ELSE
            SELECT     COUNT(*) 
            INTO       diff 
            FROM       ALL_SOURCE src1 
            FULL JOIN  ALL_SOURCE src2 
            ON         src1.NAME = src2.NAME
            WHERE      src1.NAME = pair.name1 
                        AND src1.LINE = src2.LINE 
                        AND src1.TEXT != src2.TEXT
                        AND src1.OWNER = dev_schema_name 
                        AND src2.OWNER = prod_schema_name;

            IF diff > 0 THEN 
                replace_object(dev_schema_name,prod_schema_name,object_type,pair.name1); 
            END IF; 
        END IF;
    END LOOP;
END;
