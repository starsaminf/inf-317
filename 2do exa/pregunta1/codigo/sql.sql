/** Update en los registros originales**/


SELECT * FROM [AdventureWorks2012].[Person].[PersonPhone]  WHERE BusinessEntityID = 20777

UPDATE [AdventureWorks2012].[Person].[PersonPhone]  SET PhoneNumber= '1 (11) 500 555-0129'  WHERE BusinessEntityID = 20777

SELECT * FROM [AdventureWorks2012].[Person].[PersonPhone]  WHERE BusinessEntityID = 20777


SELECT * FROM [adventureWorksReplicador].[dbo].[PersonPhone]  WHERE BusinessEntityID = 20777

