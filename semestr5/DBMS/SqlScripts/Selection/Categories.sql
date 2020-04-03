USE DbmsProject
GO
CREATE PROCEDURE GetCategories
AS
BEGIN
	SELECT * FROM ProductCategory
END