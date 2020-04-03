USE DbmsProject
GO
CREATE PROCEDURE GetProductsByCategory
	@CategoryName VARCHAR(30)
AS
BEGIN
	DECLARE @CategoryId UNIQUEIDENTIFIER = (SELECT TOP 1 Id FROM ProductCategory WHERE Name = @CategoryName)
	SELECT Product.Id, Product.Name, Description, Price, ProductCategory.Name AS CategoryName FROM Product
		JOIN ProductCategory ON ProductCategory.Id = CategoryId
		WHERE CategoryId = @CategoryId
END