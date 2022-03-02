# Netflix
Simple Netflix app built using some data structures (lists, stacks, queues).

  The basic structure used in the implementation of the project is the list of queues used for series management. For each category of series
a single list is used, which will then have as elements the queues of seasons, which in turn will have as elements the queues of episodes. The series information will be stored in the queues of episodes (serial structure, with the fields id, name, rating and total_minutes). The first field will represent the criteria according to which the series will be distributed in categories, except for the top_10 category, which will not have an explicit id. The total_minutes field will contain information about
the total duration of a serial, but will not be initialized until the last episode of the last season, as later, as a serial has new seasons, the new queue
episodes to have information about the total duration of the series in the last cell. This justifies why a large part of the functions related to displaying and
season addition only the end of the queues is accessed, the functions not being so intuitive at first sight. The watch_later queue receives the series from the 4 lists which
are added here, and the add function in the queue also receives the address of the position at which a series is inserted in the queue, and this will be incremented to
each insert, and decremented when the serial was removed from the queue and added to the currently_watching / history stack.
  The top_10 category is special because it cannot have more than 10 series inserted. The top_10 insertion function searches the list for the position where the serial should be inserted and adds it in the list, and if there are more than 10 series (11) the last series is eliminated (the series pushed to position 11). In the situation where a series is inserted on position 10, the field of the ant-> urm variable will point badly to position 10, remaining one step behind, so that in this situation ant-> umr-> urm will receive NULL. The add_sez command adds seasons to series that are not in history, so there are 3 functions that can do this: a function that inserts seasons into series in one of the 4 categories, a function that inserts seasons in the series in the watch_later queue and a function that inserts seasons in the series currently in the stack_watching.
  The 3 functions are not very easy to understand due to the fact that they have to be "mined" to the last element in the last queue to have access to the total duration of the series. In fact, some variables are used to keep the beginning of the queue and the top of the stack, because by changing them they change. In the last part they are donedeletions and insertions from / in currently_watching stack and later queue. For the watch_later queue, item by item is removed from the beginning, the minutes are subtractedfrom the series received on watch order and it is tested if they have been watched completely (in case they arrive in history) or partially (in case they arrive incurrently_watching). In fact, the position in watch_later is decremented. At the end, the queue is restored with the help of the ConcatQ function. For currently_watching stackproceed similarly, remove the elements from the top and test whether the series have been watched completely or not. The difference comes here if a series has not yet been completely watched, in which case its address is retained, and later, when the stack is redone, this series goes to the top of the same stack.

