USE DbmsProject
GO
CREATE PROCEDURE GetAccountOrders
	@AccountId UNIQUEIDENTIFIER
AS
BEGIN
	SELECT [Order].Id, Name AS ProductName, StoreName, Date FROM [Order] 
	JOIN Product ON Product.Id = ProductId
	WHERE AccountId = @AccountId
END