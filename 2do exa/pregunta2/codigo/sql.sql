/****** Antes de insertar datos******/
SELECT count(*) FROM [adventureWorksReplicador].[Person].[Address]
SELECT count(*) FROM [adventureWorksReplicador].[Person].[CountryRegion]

/****** Insertando datos en la base de datos AdventureWorks2012 ******/

INSERT INTO [AdventureWorks2012].[Person].[Address]
    (AddressLine1, AddressLine2, City, StateProvinceID, PostalCode, SpatialLocation, rowguid, ModifiedDate)
VALUES
    ('323 Main Street....', NULL, 'Anytown', 1, '12345', NULL, NEWID(), GETDATE())

INSERT INTO [AdventureWorks2012].[Person].[CountryRegion]
    (CountryRegionCode, Name, ModifiedDate)
VALUES
    ('03', 'New Country4', GETDATE());

/****** Despues de insertar datos, verificamos los datos del replicador ******/

waitfor delay '00:00:10'

SELECT count(*) FROM [adventureWorksReplicador].[Person].[Address]
SELECT count(*) FROM [adventureWorksReplicador].[Person].[CountryRegion]


/****** Prueba del Update ******/
/****** Busca el dato y muestra ******/
select * from  [AdventureWorks2012].[Person].[Address]  WHERE AddressID = 32538

/****** Busca el dato y muestra en la replica ******/
select * from  [adventureWorksReplicador].[Person].[Address] WHERE AddressID = 32538

update  [AdventureWorks2012].[Person].[Address] set AddressLine1 = 'tes test test 123'  WHERE AddressID = 32538

waitfor delay '00:00:10'

/****** Busca el dato y muestra ******/
select * from  [AdventureWorks2012].[Person].[Address] WHERE AddressID = 32538

/****** Busca el dato y muestra en la replica ******/
select * from  [adventureWorksReplicador].[Person].[Address] WHERE AddressID = 32538
