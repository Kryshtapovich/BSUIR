USE [AdventureWorks2019]
GO
/****** Object:  StoredProcedure [dbo].[GetPersons]    Script Date: 14.12.2020 0:00:42 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
ALTER PROCEDURE [dbo].[GetPersons]
	@Amount INT,
	@SortParameter INT,
	@OrderBy INT
AS
BEGIN
	SET NOCOUNT ON

SELECT TOP(@Amount)
		Person.FirstName AS 'Name', 
		Person.LastName AS 'Surname',
		Email.EmailAddress AS 'Email', 
		Phone.PhoneNumber,
		Province.Name AS 'State', 
		Position.City,
		Position.AddressLine1 AS 'Address'

FROM Person.Person AS Person
	JOIN Person.EmailAddress AS Email ON Email.BusinessEntityID = Person.BusinessEntityID
	JOIN Person.PersonPhone AS Phone ON Phone.BusinessEntityID = Person.BusinessEntityID
	JOIN Person.BusinessEntityAddress AS EA ON EA.BusinessEntityID = Person.BusinessEntityID
	JOIN Person.Address AS Position ON Position.AddressID = EA.AddressID
	JOIN Person.StateProvince AS Province ON Province.StateProvinceID = Position.StateProvinceID

ORDER BY 
		CASE WHEN @OrderBy = 1 THEN
			CASE @SortParameter
				WHEN 1 THEN FirstName
				WHEN 2 THEN LastName
				WHEN 3 THEN EmailAddress
				WHEN 4 THEN PhoneNumber
				WHEN 5 THEN Province.Name
				WHEN 6 THEN City
				WHEN 7 THEN AddressLine1
			END 
		END ASC,
    	CASE WHEN @OrderBy = -1 THEN
			CASE @SortParameter
				WHEN 1 THEN FirstName
				WHEN 2 THEN LastName
				WHEN 3 THEN EmailAddress
				WHEN 4 THEN PhoneNumber
				WHEN 5 THEN Province.Name
				WHEN 6 THEN City
				WHEN 7 THEN AddressLine1
			END
		END DESC

		SET NOCOUNT OFF
END											