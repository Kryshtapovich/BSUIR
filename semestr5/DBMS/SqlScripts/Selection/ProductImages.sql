USE DbmsProject
GO
CREATE PROCEDURE GetProductImages
	@ProductId UNIQUEIDENTIFIER
AS
BEGIN
	SELECT * FROM ProductImage WHERE ProductId = @ProductId
END