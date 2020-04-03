USE DbmsProject
GO
CREATE PROCEDURE UpdateProduct
	@ProductId UNIQUEIDENTIFIER,
	@CategoryId UNIQUEIDENTIFIER = NULL,
	@ProductName VARCHAR(30) = NULL,
	@ProductDescription NVARCHAR(1000) = NULL,
	@ProductPrice MONEY = NULL
AS
	IF NOT (@CategoryId IS NULL)
		UPDATE Product SET CategoryId = @CategoryId WHERE Id = @ProductId
	IF NOT (@ProductName IS NULL)
		UPDATE Product SET Name = @ProductName WHERE Id = @ProductId
	IF NOT (@ProductDescription IS NULL)
		UPDATE Product SET Description = @ProductDescription WHERE Id = @ProductId
	IF NOT (@ProductPrice IS NULL)
		UPDATE Product SET Price = @ProductPrice WHERE Id = @CategoryId
GO