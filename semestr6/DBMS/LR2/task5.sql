CREATE OR REPLACE PROCEDURE restore_data(start_time IN TIMESTAMP)
IS 
    CURSOR logs IS 
        SELECT    * 
        FROM      LOGS 
        WHERE     TIME >= start_time
        ORDER BY  TIME DESC;
BEGIN
    FOR log IN logs
    LOOP
        CASE
            WHEN log.COMMAND = 'INSERT' THEN
                DELETE FROM  STUDENTS 
                WHERE        ID = log.NEW_ID;

            WHEN log.COMMAND = 'UPDATE' THEN
                UPDATE  STUDENTS
                SET     ID       = log.OLD_ID,
                        NAME     = log.NAME,
                        GROUP_ID = log.GROUP_ID
                WHERE   ID = log.NEW_ID;

            WHEN log.COMMAND = 'DELETE' THEN
                INSERT INTO  STUDENTS 
                VALUES      (log.OLD_ID,
                             log.NAME,
                             log.GROUP_ID);
        END CASE;
        
        DELETE FROM  LOGS
        WHERE        TIME = log.TIME;
    END LOOP;
END;

CREATE OR REPLACE PROCEDURE restore_data_by_interval(int IN INTERVAL DAY TO SECOND)
IS 
BEGIN
    RESTORE(LOCALTIMESTAMP - int);
END;
