USE DbmsProject
GO 
CREATE PROCEDURE GetProductStores
	@ProductId UNIQUEIDENTIFIER
AS
BEGIN
	SELECT Id, Name, Address FROM ProductToStore
	JOIN Store ON Id = StoreId
	WHERE ProductId = @ProductId
END