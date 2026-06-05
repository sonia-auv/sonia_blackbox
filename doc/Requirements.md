# Node monitoring

The **BlackBox** node logs multiple systems information for debugging purposes. Using **ROS2** tools, the node is able to capture all published data and saves them at a location. The node manages the number and size of logs it will maintain in order to keep the system healthy. 

## Requirements

### Requirement 1
Titre : startBag\
PreCondition : NA.\
Post condition : Starts a recorder at launch and saves data at a specific location.

### Requirement 2
Titre : stopBag\
PreCondition : recorder is recording every information defined in the topic_list.yaml\
Post condition : Ends the recording and saves the recent recording on the system .

## Functional

### Exigence 1
Acces to the user directory and manage contents inside.

### Exigence 2
Enough storage on the system to maintain big log files.
