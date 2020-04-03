USE DbmsProject
GO
CREATE PROCEDURE AddProduct
	@CategoryName VARCHAR(30),
	@StoreName VARCHAR(30),
	@Name VARCHAR(30),
	@Description NVARCHAR(1000),
	@Price Money
AS
	DECLARE @ProductId UNIQUEIDENTIFIER = NEWID() 
	DECLARE @CategoryId UNIQUEIDENTIFIER = (SELECT Id FROM ProductCategory WHERE Name = @CategoryName)
	DECLARE @StoreId UNIQUEIDENTIFIER = (SELECT Id FROM Store WHERE Name = @StoreName)

	INSERT INTO Product (Id, CategoryId, Name, Description, Price)
	VALUES (@ProductId, @CategoryId, @Name, @Description, @Price)

	INSERT INTO ProductToStore (ProductId, StoreId)
	VALUES (@ProductId, @StoreId)
GO
	