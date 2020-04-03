USE DbmsProject
GO
CREATE PROCEDURE AddImage
	@ProductId UNIQUEIDENTIFIER,
	@Url NVARCHAR(2083)
AS
	INSERT INTO ProductImage (ProductId, Url)
	VALUES (@ProductId, @Url)
GO