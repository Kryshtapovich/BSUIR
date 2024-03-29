USE [ErrorLogs]
GO
/****** Object:  StoredProcedure [dbo].[AddError]    Script Date: 14.12.2020 0:01:30 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
ALTER PROCEDURE [dbo].[AddError]
	@Source NVARCHAR(MAX),
	@Message NVARCHAR(MAX),
	@StackTrace NVARCHAR(MAX),
	@Time DATETIME
AS
BEGIN
	INSERT INTO Errors(Source, Message, StackTrace, Time)
	VALUES(@Source, @Message, @StackTrace, @Time)
END