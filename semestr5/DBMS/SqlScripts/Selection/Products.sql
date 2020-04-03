USE DbmsProject
GO
CREATE PROCEDURE GetProducts
AS
BEGIN
	SELECT Product.Id, Product.Name, Description, Price, ProductCategory.Name AS CategoryName FROM Product
		JOIN ProductCategory ON ProductCategory.Id = CategoryId
END