CREATE TABLE Log (
	Id UNIQUEIDENTIFIER PRIMARY KEY DEFAULT NEWID() NOT NULL,
	Date SMALLDATETIME NOT NULL,
	Info NVARCHAR(1000) NOT NULL
);