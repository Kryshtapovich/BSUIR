USE DbmsProject
GO
CREATE PROCEDURE GetLogs
AS
BEGIN
	SELECT * FROM Log
END