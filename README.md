# CRUD
Using C++ to manipulate MySQL.

Visual Studio:
1. Go to Project Properties
2. Select Platform: X64
3. Configuration Properties -> VC++ Directories ->
                                                  Include Directories: Add C:\Program Files\MySQL\MySQL Server 8.0\include
                                                  Library Directories: Add C:\Program Files\MySQL\MySQL Server 8.0\lib
4. Linker -> General -> Additional Library Directories: Add libmysql.lib
             Input -> Additional Dependencies: Add libmysql.lib
5. Place libmysql.dll in the project directory.
