USE DbmsProject 
GO
CREATE PROCEDURE UpdateStore
	@StoreId UNIQUEIDENTIFIER,
	@StoreName VARCHAR(30) = NULL,
	@Address VARCHAR(30) = NULL
AS
	IF NOT(@StoreId IS NULL)
		UPDATE Store SET Name = @StoreName WHERE Id = @StoreId
	IF NOT(@Address IS NULL)
		UPDATE Store SET Address = @Address WHERE Id = @StoreId
GO