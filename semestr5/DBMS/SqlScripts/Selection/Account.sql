USE DbmsProject
GO
CREATE PROCEDURE GetAccount
	@Email NVARCHAR(50),
	@PasswordHash NVARCHAR(50)
AS
BEGIN
	
	SELECT Account.Id, Role.Type AS [Role], FirstName, LastName, Email, PasswordHash FROM Account
		JOIN Role ON Account.RoleId = Role.Id
		WHERE Email = @Email AND PasswordHash = @PasswordHash 
END