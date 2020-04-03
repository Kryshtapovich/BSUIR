USE DbmsProject
GO
CREATE PROCEDURE UpdateAccount
	@AccountId UNIQUEIDENTIFIER,
	@FirstName VARCHAR(20) = NULL,
	@LastName VARCHAR(20) = NULL,
	@Email NVARCHAR(50) = NULL,
	@PasswordHash NVARCHAR(50) = NULL 
AS
	IF NOT (@FirstName IS NULL)
		UPDATE Account SET FirstName = @FirstName WHERE Id = @AccountId
	IF NOT (@LastName IS NULL)
		UPDATE Account SET LastName = @LastName WHERE Id = @AccountId
	IF NOT (@Email IS NULL)
		UPDATE Account SET Email = @Email WHERE Id = @AccountId
	IF NOT (@PasswordHash IS NULL)
		UPDATE Account SET PasswordHash = @PasswordHash WHERE Id = @AccountId
GO