Brief instructions for installing the Travel Agency program.
Instructions for program version 0.4 (prototype).
The program is written in Embarcadero C ++ Builder XE.

1). Create a Software directory on the C: \ drive.
2). Move the file with the AgencyBase.mdb database from the Database folder of the program directory to the C: \ Software folder.
3). Run the Check ODBC Base.vbs script from the Database \ Scripts folder to check for the existence of a custom DSN. If there is a message about the existence of the DSN: "User DSN 'TouristAgency Base' exists.", Then the configuration is complete. Otherwise, go to step 3 *.
3 *). Add to the DSN with the name "TouristAgency Base", a driver for working with * .mdb, specifying the path to the database (by default C: \ Software \ AgencyBase.mdb). To automate this process, you can use the * .reg file ODBC TouristAgency Base.reg from the Database \ Scripts folder.
4). The program is launched by executing the TouristAgency.exe file from the Release folder.

P.S .: When uninstalling the program, do not forget to delete the custom DSN.
