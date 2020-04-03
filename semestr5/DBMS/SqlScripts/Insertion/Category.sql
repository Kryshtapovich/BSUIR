USE DbmsProject
GO 
CREATE PROCEDURE AddCategory
	@Name VARCHAR(30)
AS
	INSERT INTO ProductCategory (Name)
	VALUES (@Name)
GO