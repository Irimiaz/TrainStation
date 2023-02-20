# TrainStation

TrainStation is the structure that represents the train station. The station has several platforms, and on each platform can park a train. The platforms_no field represents the number of platforms of the station, and the platforms field is a vector containing the platforms and the stopped trains. Is not it is mandatory that there is a train stationed on each platform at a certain time.

Train is the structure that represents a train. Each train consists of a locomotive and a
sequence of wagons. The locomotive_power field represents the maximum weight it can carry
transport the locomotive. If the total weight of the wagons exceeds this value, the train does not
will be able to leave the station. The train_cars field represents the first carriage in the sequence of carriages a
the train (it is the wagon attached to the locomotive).

TrainCar is the structure that represents a train car. Each wagon has an associated weight which
is retained in the weight field. The next field represents the next wagon in the sequence of
train cars.

* Open train station function

Provides memory to the station and set the number of platforms, the number that is transmitted as a parameter
Gives memory to each platform and set it to NULL, which means no locomotive

* Close train station function

It frees all the used memory.

* Show existing trains function

Goes through all the platforms in a station, and if a platform is not NULL, it displays the power of the locomotive. Later, if there are wagons, it will display, in turn, the weight of each wagon.

* Arrive train function

Checks if there is already a locomotive on the platform with the platform number. Only if the platform is empty, memory will be provided to the locomotive and the power of the locomotive will be initialized. Considering that there are no wagons, the train_cars pointer will point to NULL.

* Leave train function

Checks if the sky platform is empty, and if so, nothing will be done. If there is a train there, the memory will be freed.

* Add train car function

Adds a wagon only if there is already a locomotive on that platform. The position in which the wagon is inserted requires a different implementation If there are no wagons, it inserts the given wagon at the beginning, giving it memory first. If so, it goes through the wagons until it finds NULL, and then insert the given wagon

* Removes train cars function

Checks if there are wagons on the given platform. If it finds a wagon with the given weight, the program deletes it from the memory, with free, but only after restoring the links to its neighbors If it has to delete the first wagon, it will set train_cars on the next wagon, and then give free to the first

* Move train cars function

Checks if there are wagons on the platform where it wants to take the wagons. If there are, and they can be extracted without exceeding the list of wagons, it will store the first and last wagon in 2 pointer variables.It goes through the platform where we want to insert the wagons, and if the position is valid, it will redo the links so that all the wagons are moved. If the moving process takes place successfully, it needs to restore the links in the first platform so that it can continue to be used

* Find express train function

It goes through each platform separately and calculate the difference between the power of the locomotive and the sum of the weights of the wagonsThe express train will be the one with the biggest difference.

* Find overload train function

It will work similar to the previous function, only it is looking for the train that has a locomotive with less power than the sum of the weights of the wagons

* Optimal train function

Also, as in the previous function, it will find the train that has the difference between the power of the locomotive and the sum of the weights of the wagons as small as possible, but positive.

* Find heaviest sequence train function

It will go through each wagon separately, from a platform, and starting from that wagon it will calculate the sum of the weights of the following cars_no wagons. Finally, it returns the platform number and a pointer to the first car in the sequence found

* Order train function

It will check that the train has carriages. If it finds 2 wagons that are in increasing positions, but have decreasing weight, it will exchange them.

* Fixed overload train function

It will go through the station and find the platform where the overloaded train is. Going through each carriage in that train, it will find out which carriage must be eliminated so that the train becomes an optimal one.
