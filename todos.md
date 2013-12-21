Mousing Todos
=============
* Track scrolling use ?
    * This seems to need another X11 library ... ?
* Introduce a config library like libconfig. Make use of this to move configuration out
  of the binary files in into users dotfiles.
    * Place a sample config file into directory
    * Use default configurations, but let configfile override this settings.
* Support different storage types as Plain File, PostgreSQL and so forth.

Known bugs
==========
* If the mouse is clicked but not moved, the save to the database does not work as expected.

Mousing Future Tech
===================
  * Export data and generate some pretty graphs/plots.
