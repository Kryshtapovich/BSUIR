USE DbmsProject
GO
CREATE PROCEDURE AddOrder
	@AccountId UNIQUEIDENTIFIER,
	@ProductId UNIQUEIDENTIFIER,
	@StoreId UNIQUEIDENTIFIER,
	@Date SMALLDATETIME
AS
	DECLARE @StoreName VARCHAR(30) = (SELECT TOP 1 Name FROM Store WHERE Id = @StoreId)
	DECLARE @Product_Id UNIQUEIDENTIFIER = (SELECT TOP 1 ProductId FROM ProductToStore WHERE ProductId = @ProductId AND StoreId = @StoreId)
	DECLARE @Store_Id UNIQUEIDENTIFIER = (SELECT TOP 1 ProductId FROM ProductToStore WHERE ProductId = @ProductId AND StoreId = @StoreId)

	IF NOT (@Product_Id IS NULL) AND NOT (@Store_Id IS NULL)
		INSERT INTO [Order] (AccountId, ProductId, StoreName, Date)
		VALUES (@AccountId, @Product_Id, @StoreName, @Date)
GO