USE DbmsProject
GO
CREATE PROCEDURE UpdateCategory
	@CategoryId UNIQUEIDENTIFIER,
	@CategoryName VARCHAR(30)
AS
	UPDATE ProductCategory SET Name = @CategoryName WHERE Id = @CategoryId
GO