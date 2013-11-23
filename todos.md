Mousing Todos
=============

  * Track scrolling use ?
    * This seems to need another X11 library ... ?
  * Clean up code (refactor), and merge variables into arrays etc.
      * Try to find the best datastorage 'structure' for the main mouse properties.
        * Use structs ? 
        * Use arrays ?
  * Reset the counters every midnight. This to prevent counters from previous day to leak onto the next day.

Known bugs
==========

  * Every time the program is opened the movement counter seems to increment by 1919...


Mousing Future tech
===================

  * Export data and generate som pretty graphs/plots.
  * Make better use of ncurses with centered information, and panels (date, help, menus).
