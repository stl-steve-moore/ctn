/* CreateTBLTestTables.script 1.0 8-Mar-94 */
/* set nocount on */
print " "
go
print " "
go


use TBLTest
go
	create table TBL_Persons
	(
	FNAME		char(50) not null,
	LNAME		char(50) not null,
	AGE		int not null,
	ZIP		int not null,
	WEIGHT		real not null,
	)
go
print "Created TBL_Persons Table"
go
	create table UniqueNumbers
	(
	NumberName	char(50) not null,
	UniqueNumber	int not null,
	)
go

	create table TBL_DataTypes
	(
	T_TEXT		text,
	T_INT		int
	)
go

INSERT INTO UniqueNumbers VALUES ("UN1",0)
go
INSERT INTO UniqueNumbers VALUES ("UN2",0)
go
INSERT INTO UniqueNumbers VALUES ("UN3",0)
go
print "Created and Initialized UniqueNumbers Table"
go
print " "
go
print " "
go
