USE DbmsProject
GO
CREATE PROCEDURE UpdateProductImage
	@ProductId UNIQUEIDENTIFIER,
	@ImageId UNIQUEIDENTIFIER,
	@ImageUrl NVARCHAR(2083)
AS
	UPDATE ProductImage SET Url = @ImageUrl WHERE Id = @ImageId AND ProductId = @ProductId
GO