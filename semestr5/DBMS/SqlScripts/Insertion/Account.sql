USE DbmsProject
GO
CREATE PROCEDURE AddAccount
	@FirstName VARCHAR(20),
	@LastName VARCHAR(20),
	@Email NVARCHAR(50),
	@PasswordHash NVARCHAR(50)
AS
	DECLARE @RoleId UNIQUEIDENTIFIER = (SELECT MAX(Id) FROM Role WHERE Name = 'user')
	
	INSERT INTO Account (RoleId, FirstName, LastName, Email, PasswordHash)
	VALUES (@RoleId, @FirstName, @LastName, @Email, @PasswordHash)
GO