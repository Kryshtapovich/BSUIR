USE DbmsProject
GO
CREATE PROCEDURE AddStore
	@Name VARCHAR(30),
	@Address VARCHAR(100)
AS
	INSERT INTO Store (Name, Address)
	VALUES (@Name, @Address)
GO