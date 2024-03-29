CREATE TABLE [Order] (
	Id UNIQUEIDENTIFIER PRIMARY KEY DEFAULT NEWID() NOT NULL,
	AccountId UNIQUEIDENTIFIER REFERENCES Account (Id) NOT NULL,
	ProductId UNIQUEIDENTIFIER REFERENCES Product (Id) NOT NULL,
	StoreName VARCHAR(30) NOT NULL,
	[Date] SMALLDATETIME NOT NULL
);